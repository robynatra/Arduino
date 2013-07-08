#include <Scheduler.h>

//For proper communication packet format given below have to be supported:
////////// Packet Format Version 2 ////////////
// 17-byte packets are transmitted from Olimexino328 at 256Hz,
// using 1 start bit, 8 data bits, 1 stop bit, no parity, 57600 bits per second.

// Minimial transmission speed is 256Hz * sizeof(Olimexino328_packet) * 10 = 43520 bps.

/*
struct Olimexino328_packet
{
  uint8_t	sync0;		// = 0xa5
  uint8_t	sync1;		// = 0x5a
  uint8_t	version;	// = 2 (packet version)
  uint8_t	count;		// packet counter. Increases by 1 each packet.
  uint16_t	data[6];	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
  uint8_t	switches;	// State of PD5 to PD2, in bits 3 to 0.
};
*/
/**********************************************************/
#include "Framing.h"
#include <compat/deprecated.h>
#include <FlexiTimer2.h>
//http://www.arduino.cc/playground/Main/FlexiTimer2

// All definitions
#define NUMCHANNELS 6
#define HEADERLEN 4
#define PACKETLEN (NUMCHANNELS * 2 + HEADERLEN + 1)
//#define SAMPFREQ 1                      // ADC sampling rate 256
//#define SAMPFREQ 24                      // ADC sampling rate 256
#define SAMPFREQ 256                      // ADC sampling rate 256
#define TIMER2VAL (1024/(SAMPFREQ))       // Set 256Hz sampling frequency                    
#define LED1  13
#define CAL_SIG 9


// Global constants and variables
//volatile unsigned char TXBuf[PACKETLEN];  //The transmission packet
volatile unsigned char TXBuf[PACKETLEN];  //The transmission packet
volatile unsigned char TXIndex;           //Next byte to write in the transmission packet.
volatile unsigned char CurrentCh;         //Current channel being sampled.
volatile unsigned char counter = 0;	  //Additional divider used to generate CAL_SIG
volatile unsigned int ADC_Value = 0;	  //ADC current value


// Framing variables
Framing framing;                          // JD: Add this framing object to package up data for transfer
const char type_rtp = '1';
const char type_rtsp = '2';
const char type_ack = '3';
const char type_message = '4';

// IO constants/variables
int io_taskstarted = 0;


// RTSP constants/variables
int rtsp_taskstarted = 0;
Scheduler scheduler = Scheduler();

// RTSP States
#define RTSPState_Ready       1
#define RTSPState_Recording   2
#define RTSPState_Init        3
#define RTSPState_Playing     4

// RTSP Commands
#define RTSPCommand_Play      1
#define RTSPCommand_Pause     2
#define RTSPCommand_Record    3
#define RTSPCommand_Setup     4
#define RTSPCommand_Teardown  5

// RTSP messaging variables
int RTSPCommandCount        = 0;
int RSTPCurrentState        = RTSPState_Init;
volatile unsigned char RTSP_RXBUF[1000];  // This buffer contains RTSP commands from clients

//~~~~~~~~~~
// Functions
//~~~~~~~~~~

/****************************************************/
/*  Function name: Toggle_LED1                      */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Switches-over LED1.                   */
/****************************************************/
void Toggle_LED1(void){

 if((digitalRead(LED1))==HIGH){ digitalWrite(LED1,LOW); }
 else{ digitalWrite(LED1,HIGH); }
 
}


/****************************************************/
/*  Function name: toggle_GAL_SIG                   */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Switches-over GAL_SIG.                */
/****************************************************/
void toggle_GAL_SIG(void){
  
 if(digitalRead(CAL_SIG) == HIGH){ digitalWrite(CAL_SIG, LOW); }
 else{ digitalWrite(CAL_SIG, HIGH); }
 
}


/****************************************************/
/*  Function name: setup                            */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Initializes all peripherals           */
/****************************************************/
void setup() {

 noInterrupts();  // Disable all interrupts before initialization
 
 // LED1
 pinMode(LED1, OUTPUT);  //Setup LED1 direction
 digitalWrite(LED1,LOW); //Setup LED1 state
 pinMode(CAL_SIG, OUTPUT);
 
 //Write packet header and footer
 TXBuf[0] = 0xa5;    //Sync 0
 TXBuf[1] = 0x5a;    //Sync 1
 TXBuf[2] = 2;       //Protocol version
 TXBuf[3] = 0;       //Packet counter
 TXBuf[4] = 0x02;    //CH1 High Byte
 TXBuf[5] = 0x00;    //CH1 Low Byte
 TXBuf[6] = 0x02;    //CH2 High Byte
 TXBuf[7] = 0x00;    //CH2 Low Byte
 TXBuf[8] = 0x02;    //CH3 High Byte
 TXBuf[9] = 0x00;    //CH3 Low Byte
 TXBuf[10] = 0x02;   //CH4 High Byte
 TXBuf[11] = 0x00;   //CH4 Low Byte
 TXBuf[12] = 0x02;   //CH5 High Byte
 TXBuf[13] = 0x00;   //CH5 Low Byte
 TXBuf[14] = 0x02;   //CH6 High Byte
 TXBuf[15] = 0x00;   //CH6 Low Byte 
 TXBuf[2 * NUMCHANNELS + HEADERLEN] =  0x01;	// Switches state

 // Timer2
 // Timer2 is used to setup the analag channels sampling frequency and packet update.
 // Whenever interrupt occures, the current read packet is sent to the PC
 // In addition the CAL_SIG is generated as well, so Timer1 is not required in this case!
 FlexiTimer2::set(TIMER2VAL, Timer2_Overflow_ISR);
 FlexiTimer2::start();
 
 // Serial Port
 Serial.begin(115200);
 //Serial.begin(57600);
 //Set speed to 57600 bps
 
  framing.setTimout(0.1);

 // MCU sleep mode = idle.
 //outb(MCUCR,(inp(MCUCR) | (1<<SE)) & (~(1<<SM0) | ~(1<<SM1) | ~(1<<SM2)));

 interrupts();  // Enable all interrupts after initialization has been completed
}

/****************************************************/
/*  Function name: Timer2_Overflow_ISR              */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Determines ADC sampling frequency.    */
/****************************************************/
void Timer2_Overflow_ISR()
{
  // Toggle LED1 with ADC sampling frequency /2
  Toggle_LED1();
  
  //Read the 6 ADC inputs and store current values in Packet
  for(CurrentCh=0;CurrentCh<6;CurrentCh++){
    ADC_Value = analogRead(CurrentCh);
    TXBuf[((2*CurrentCh) + HEADERLEN)] = ((unsigned char)((ADC_Value & 0xFF00) >> 8));	// Write High Byte
    TXBuf[((2*CurrentCh) + HEADERLEN + 1)] = ((unsigned char)(ADC_Value & 0x00FF));	// Write Low Byte
  }

  unsigned char toSend[17];
  //TxBuff
  for(int i=0;i<PACKETLEN;i++)
  toSend[i] = TXBuf[i];
  
  // Send the datat to the client if requested.
  // Could change this to a playout buffer
  if(RSTPCurrentState==RTSPState_Playing)
  framing.sendFramedData(toSend,17, type_rtp);
  
  // Increment the packet counter
  TXBuf[3]++;			
  
  // Generate the CAL_SIGnal
  counter++;		// increment the devider counter
  if(counter == 12){	// 250/12/2 = 10.4Hz ->Toggle frequency
    counter = 0;
    toggle_GAL_SIG();	// Generate CAL signal with frequ ~10Hz
  }
}


/****************************************************/
/*  Function name: loop                             */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Puts MCU into sleep mode.             */
/****************************************************/
void loop() {
  scheduler.update();                 //update the scheduler, maybe it is time to execute a function?

  if(rtsp_taskstarted==0)
  {
    rtsp_taskstarted=1;
    scheduler.schedule(rtsp_task,1000);
  }
  if(io_taskstarted==0)
  {
    io_taskstarted=1;
    scheduler.schedule(io_task,100);
  }

 __asm__ __volatile__ ("sleep");
}




// Task
void rtsp_task() 
{
  // temporarily set this
  int command = 1;

  if(RTSPCommandCount)
  {
    switch (command)
    {
      case RTSPCommand_Play:
      {
        switch(RSTPCurrentState)
        {
          case RTSPState_Ready:
          {
              // play
          }
        }
      }
    }
  }
  scheduler.schedule(rtsp_task,1000);
}


// Task
void io_task() 
// This task handles commands sent from the phone
// It deframes them and sends them to the appropriate device
{
  unsigned char input_buff[100];
  unsigned char output_buff[100];
  int output_length, input_length, crc_valid, framing_seq, dataType;

  //the values 1, 2, 3 have been sent through serial
  framing.receiveFramedData(input_buff, input_length, crc_valid, framing_seq, dataType);
  //the input buffer has been filled with incoming serial data

 if((crc_valid!=0) && (input_length>0))
  {
    // To Send a message
    //unsigned char message[ ] = "RTSP/1.0 200 OK\n";
    //framing.sendFramedData(message,1, type_message);

    //unsigned char message[ ] = "abcd";
    //framing.sendFramedData(message,4, type_message);

    // Frame received correctly - send an ack with the sequence number of the frame being acked
    //unsigned char message[] = {framing_seq>>8,  framing_seq};
    //framing.sendFramedData(message,2, type_ack);
    
    switch(dataType)
    {
      case type_rtp:
      {
        //unsigned char message[ ] = "rtp";
        //framing.sendFramedData(message,3, type_message);

        unsigned char message[] = {framing_seq>>8,  framing_seq, 'r'};
        framing.sendFramedData(message,message.length, type_ack);
      }
      case type_rtsp:
      {
        unsigned char message[] = {framing_seq>>8,  framing_seq, 'rtsp'};
        framing.sendFramedData(message,6, type_ack);
        
        //unsigned char message[ ] = "rtsp";
        //framing.sendFramedData(message,4, type_message);
      }
      case type_ack:
      {
        //unsigned char message[ ] = "ack";
        //framing.sendFramedData(message,3, type_message);
      }
      case type_message:
      {
        unsigned char message[ ] = "message";
        framing.sendFramedData(message,7, type_message);
      }
    }
  }

  scheduler.schedule(io_task,100);
}
