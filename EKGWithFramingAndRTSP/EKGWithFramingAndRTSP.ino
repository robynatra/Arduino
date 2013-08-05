#include <Scheduler.h>
#include <String.h>
#include "rtsp.h"
#include "rtsp_protocol.h"
#include <avr/pgmspace.h>


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
#define NUMCHANNELS 1  // 6
#define FrameHeaderLen 0
#define FRAMELEN (NUMCHANNELS * 2 + FrameHeaderLen)
#define SAMPFREQ 100                      // ADC sampling rate 256
//#define SAMPFREQ 25                       // ADC sampling rate 256

//#define SAMPFREQ 32                     // ADC sampling rate 256
//#define SAMPFREQ 256                    // ADC sampling rate 256
//#define TIMER2VAL (1024/(SAMPFREQ))       // Set 256Hz sampling frequency                    
#define TIMER2VAL (1000/(SAMPFREQ))       // Set 256Hz sampling frequency                    
#define LED1  13
#define CAL_SIG 9

// RTP definitions
#define RTPPacketHeaderLen 12
#define RTPPacketLEN RTPPacketHeaderLen + (FRAMELEN*4)  // RTP Packet length plus the length of the data from the ECG plus padding to bring it up to a multiple of 4 bytes (0 in this case)
#define RTPVersion 2
#define RTPCC 1
#define RTPPayloadType 1                          // RTPPayload type - a standard payload that the receiver can use to identify features of the media stream eg the media clock rate. In our case for example 256hz

// RTP Byte 0
#define RTPVersionMask 0xC0        // 11000000
#define RTPPaddingMask 0x20        // 00100000
#define RTPExtensionMask 0x20      // 00010000tipl
#define RTPCSRCMask 0x20           // 00001111

// RTP Byte 1
#define RTPMarkerBitMask 0x80      // 10000000
#define RTPPayloadTypeMask 0x7F    // 01111111


// Global constants and variables
//volatile unsigned char TXBuf[FRAMELEN];  //The transmission packet
volatile unsigned char TXBuf[FRAMELEN*4];    //The transmission packet
volatile unsigned char TXIndex;             //Next byte to write in the transmission packet.
volatile unsigned char CurrentCh;           //Current channel being sampled.
volatile unsigned char counter = 0;	    //Additional divider used to generate CAL_SIG
volatile unsigned int ADC_Value = 0;	    //ADC current value

int PacketCounter = 0;                      // Count of samples sent

//RTP Variables
//unsigned char RTPBuff[RTPPacketLEN];       //The RTP transmission packet
unsigned char RTPBuff[RTPPacketLEN + 1];         //The RTP transmission packet
volatile unsigned int RTPSeq     = 0;        // 16bit int 0-65,535 - used to identify jitter/packet loss by receiver
int  RTPMarkerBit                = 0;
long RTPTimeStamp                = 1000;     // 32bit timestamp.. used for playout - should be a random number at start of each session
int RTPCSRC                      = 0;        // Count of contributing sources = 0
long RTPSSRC                     = 0;        // Synchronization source identifer - should generate this using similar method as defined in RFC3550 (TBD).

// Framing variables
Framing framing;                            // JD: Add this framing object to package up data for transfer
const char type_rtp       = '1';
const char type_rtsp      = '2';
const char type_ack       = '3';
const char type_message   = '4';

// IO constants/variables
int io_taskstarted = 0;


// RTSP constants/variables
int rtsp_taskstarted = 0;
Scheduler scheduler = Scheduler();

//int rtsp_length = 0;
//int rtsp_buf_ready  = 1;
//char rtsp_buff[128];

// RTSP States
#define RTSPState_Ready       1
#define RTSPState_Recording   2
#define RTSPState_Init        3
#define RTSPState_Playing     4

// RTSP messaging variables
int RTSPCommandCount        = 0;
//int RSTPCurrentState        = RTSPState_Playing;
int RSTPCurrentState        = RTSPState_Init;
volatile unsigned char RTSP_RXBUF[1000];  // This buffer contains RTSP commands from clients


char* testPackets[3];
//rtsp_protocol protocol = rtsp_protocol();






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

  if((digitalRead(LED1))==HIGH){ 
    digitalWrite(LED1,LOW); 
  }
  else{ 
    digitalWrite(LED1,HIGH); 
  }

}


/****************************************************/
/*  Function name: toggle_GAL_SIG                   */
/*  Parameters                                      */
/*    Input   :  No	                            */
/*    Output  :  No                                 */
/*    Action: Switches-over GAL_SIG.                */
/****************************************************/
void toggle_GAL_SIG(void){

  if(digitalRead(CAL_SIG) == HIGH){ 
    digitalWrite(CAL_SIG, LOW); 
  }
  else{ 
    digitalWrite(CAL_SIG, HIGH); 
  }

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

/*
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
  TXBuf[2 * NUMCHANNELS + FrameHeaderLen] =  0x01;	// Switches state
*/
  TXBuf[0] = 0x02;    //CH1 High Byte
  TXBuf[1] = 0x00;    //CH1 Low Byte
  TXBuf[2] = 0x02;    //CH1 High Byte
  TXBuf[3] = 0x00;    //CH1 Low Byte
  TXBuf[4] = 0x02;    //CH1 High Byte
  TXBuf[5] = 0x00;    //CH1 Low Byte
  TXBuf[6] = 0x02;    //CH1 High Byte
  TXBuf[7] = 0x00;    //CH1 Low Byte

/*
  TXBuf[0] = 0xa5;    //Sync 0
  TXBuf[1] = 0x5a;    //Sync 1
  TXBuf[2] = 0;       //Packet counter
  TXBuf[3] = 0x02;    //CH1 High Byte
  TXBuf[4] = 0x00;    //CH1 Low Byte
  TXBuf[5] = 0x01;    //End byte

  TXBuf[6] = 0xa5;    //Sync 0
  TXBuf[7] = 0x5a;    //Sync 1
  TXBuf[8] = 0;       //Packet counter
  TXBuf[9] = 0x02;    //CH1 High Byte
  TXBuf[10] = 0x00;    //CH1 Low Byte
  TXBuf[11] = 0x01;    //End byte



  TXBuf[12] = 0xa5;    //Sync 0
  TXBuf[13] = 0x5a;    //Sync 1
  TXBuf[14] = 0;       //Packet counter
  TXBuf[15] = 0x02;    //CH1 High Byte
  TXBuf[16] = 0x00;    //CH1 Low Byte
  TXBuf[17] = 0x01;    //End byte

  TXBuf[18] = 0xa5;    //Sync 0
  TXBuf[19] = 0x5a;    //Sync 1
  TXBuf[20] = 0;       //Packet counter
  TXBuf[21] = 0x02;    //CH1 High Byte
  TXBuf[22] = 0x00;    //CH1 Low Byte
  TXBuf[23] = 0x01;    //End byte
*/



  // Timer2
  // Timer2 is used to setup the analag channels sampling frequency and packet update.
  // Whenever interrupt occures, the current read packet is sent to the PC
  // In addition the CAL_SIG is generated as well, so Timer1 is not required in this case!
  // FlexiTimer uses timer 2 but at different rates than the usual 256Hz.
  // In this case we specify it in multiples of 1/1000 of a second.
  FlexiTimer2::set(TIMER2VAL, Timer2_Overflow_ISR);
  FlexiTimer2::start();



  // Serial Port
  //Serial.begin(9600);
  //Serial.begin(57600);
  //Set speed to 57600 bps
  Serial.begin(115200);

  framing.setTimout(0.1);

  // MCU sleep mode = idle.
  //outb(MCUCR,(inp(MCUCR) | (1<<SE)) & (~(1<<SM0) | ~(1<<SM1) | ~(1<<SM2)));

  interrupts();  // Enable all interrupts after initialization has been completed

  // RTSP Test Packets
  //testPackets[0] = "SETUP rtsp://example.com/foo/bar/baz.rm RTSP/1.0\r\n\r\nCSeq: 302\r\nTransport: RTP/AVP;unicast;client_port=4588-4589";
  // 65
  testPackets[0] = "SETUP rtsp://example.com/foo/bar/baz.rm RTSP/1.0\r\n\r\nCSeq: 302";
  //testPackets[0] = "PLAY rtsp://audio.example.com/audio RTSP/1.0\r\nCSeq: 835\r\nSession: 12345678\r\nRange: npt=10-15";   
  //testPackets[0] = "DESCRIBE rtsp://server.example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nAccept: application/sdp, application/rtsl, application/mheg";   

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
  for(CurrentCh=0;CurrentCh<NUMCHANNELS;CurrentCh++){
    ADC_Value = analogRead(CurrentCh);
    //TXBuf[(((PacketCounter%4)*6)  + (2*CurrentCh) + FrameHeaderLen)] = ((unsigned char)((ADC_Value & 0xFF00) >> 8));	// Write High Byte
    //TXBuf[(((PacketCounter%4)*6)  + (2*CurrentCh) + FrameHeaderLen + 1)] = ((unsigned char)(ADC_Value & 0x00FF));	// Write Low Byte
    TXBuf[(((PacketCounter%4)*2)  + (2*CurrentCh) + FrameHeaderLen)] = ((unsigned char)((ADC_Value & 0xFF00) >> 8));	// Write High Byte
    TXBuf[(((PacketCounter%4)*2)  + (2*CurrentCh) + FrameHeaderLen + 1)] = ((unsigned char)(ADC_Value & 0x00FF));	// Write Low Byte
  }
  // Increment the packet counter
  //TXBuf[(PacketCounter%4)*6 + 2] = (unsigned char) PacketCounter;

  //unsigned char toSend[17];
  //TxBuff
  //for(int i=0;i<FRAMELEN;i++)
  //RTPPacketData[i] = TXBuf[i];

  // Send the datat to the client if requested.
  // Could change this to a playout buffer
  if(RSTPCurrentState==RTSPState_Playing)
    // Package up data in an RTP packet and send
  {
    /*
    0               1               2               3
     0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |V=2|P|X|  CC   |M|     PT      |       sequence number         |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                           timestamp                           |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |           synchronization source (SSRC) identifier            |
     +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
     |            contributing source (CSRC) identifiers             |
     |                             ....                              |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                          payload data                         |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     
     */

    if((PacketCounter%4)==3)
    // Send an RTP packet data every 4th sample
    {
      if(RTPSeq<65535)
        RTPSeq++;
      else
        RTPSeq=0;

      RTPMarkerBit = 0;
      RTPTimeStamp = RTPTimeStamp + ((1000/256));          // increase the timestamp by 1.
      RTPCSRC = 0;            // no contributing sources other than the synchronisation source
      RTPSSRC = 1234;         // synchronization source - should be a random number

      //Write packet header and footer
      RTPBuff[0]  = (RTPVersion<<6) | (RTPCSRC & RTPCSRCMask);                         // Set Version bits (V) and CSCRC bits (CC). Set Padding bit (P) later if necessary. Leave extension bit (X) out for now.
      RTPBuff[1]  = ((1<<7)&RTPMarkerBit) | (RTPPayloadType&RTPPayloadTypeMask);       // Set marker bit (M) and set payload type;
      RTPBuff[2]  = (RTPSeq>>8) && 0xFF;     // Sequence number hi
      RTPBuff[3]  = RTPSeq & 0xFF;           // Sequence number lo
      RTPBuff[4]  = (RTPTimeStamp>>24) & 0xff;       // RTP TimesStamp byte 0
      RTPBuff[5]  = (RTPTimeStamp>>16) & 0xff;       // RTP TimesStamp byte 1
      RTPBuff[6]  = (RTPTimeStamp>>8) & 0xff;        // RTP TimesStamp byte 2
      RTPBuff[7]  = (RTPTimeStamp) & 0xff;           // RTP TimesStamp byte 3
      RTPBuff[8]  = (RTPSSRC>>24) & 0xff;       // SSRC byte 0
      RTPBuff[9]  = (RTPSSRC>>16) & 0xff;       // SSRC byte 1
      RTPBuff[10] = (RTPSSRC>>8) & 0xff;        // SSRC byte 2
      RTPBuff[11] = (RTPSSRC) & 0xff;           // SSRC byte 3
  
      /*
      for(int i=12;i< 36; i++)
      {
        RTPBuff[i] = TXBuf[i-12];           // SSRC byte 3
      }
      */  
      for(int i=12;i< 19; i++)
      {
        RTPBuff[i] = TXBuf[i-12];           // SSRC byte 3
      }
      
      
      //unsigned char  toSend[20];
      //for(int i=0;i<7;i++)
      //{
      //  toSend[i] = TXBuf[i];
      //}
  
      framing.sendFramedData((unsigned char*) RTPBuff, RTPPacketLEN, type_rtp);
  
      //Serial.println(RTPSeq);
      //framing.sendFramedData((unsigned char*) RTPBuff, RTPPacketLEN, type_rtp);

      //framing.sendFramedData(toSend,17, type_rtp);
      //framing.sendFramedData((unsigned char*) RTPBuff, 36, type_rtp);
      //framing.sendFramedData(toSend,7, type_rtp);
      //framing.sendFramedData((unsigned char*) TXBuf, 2 * NUMCHANNELS + FrameHeaderLen -1, type_rtp);
    }
  
    PacketCounter++;


  // Generate the CAL_SIGnal
  counter++;		// increment the devider counter
  if(counter == 12){	// 250/12/2 = 10.4Hz ->Toggle frequency
    counter = 0;
    toggle_GAL_SIG();	// Generate CAL signal with frequ ~10Hz
  }
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
    //scheduler.schedule(rtsp_task,1000);
  }
  if(io_taskstarted==0)
  {
    io_taskstarted=1;
    scheduler.schedule(io_task,100);
  }

  __asm__ __volatile__ ("sleep");
}






// Task
void io_task() 
// This task handles commands sent from the phone
// It deframes them and sends them to the appropriate device
{
  unsigned char input_buff[255];
  unsigned char output_buff[255];
  int output_length, input_length, crc_valid, framing_seq, dataType;
  input_length = 0;
  //unsigned char message[ ] = "abcdef";
  //framing.sendFramedData(message,6, type_message);

  //unsigned char message[] = {0x80};
  //framing.sendFramedData(message,1, type_message);


  //the values 1, 2, 3 have been sent through serial
  framing.receiveFramedData(input_buff, input_length, crc_valid, framing_seq, dataType);
  // the input buffer has been filled with incoming serial data
  // the data will be in input_buff[3] -> input_buff[input_length]

  if((crc_valid!=0) && (input_length>0))
  {
    //unsigned char message[ ] = input_buff;
    //framing.sendFramedData(input_buff,input_length, type_message);

    // To Send a message
    //unsigned char message[ ] = "RTSP/1.0 200 OK\n";
    //framing.sendFramedData(message,1, type_message);

    //unsigned char message[ ] = "abcd";
    //framing.sendFramedData(message,4, type_message);

    // Frame received correctly - send an ack with the sequence number of the frame being acked
    //unsigned char message[] = {framing_seq>>8,  framing_seq};
    //framing.sendFramedData(message,2, type_ack);

    //for(int i=0;i<input_length;i++)
    //{
    //  Serial.write(input_buff[i]);
    // }

    switch(dataType)
    {
    case type_rtp:
      {
        //unsigned char message[ ] = "rtp";
        //framing.sendFramedData(message,3, type_message);

        //unsigned char message[] = {framing_seq>>8,  framing_seq, 'r'};
        //framing.sendFramedData(message,message.length, type_ack);
        break;
      }
    case type_rtsp:
      {

        //unsigned char message[ ] = "rtsp";
        //framing.sendFramedData(message,4, type_message);


        // Block access to this section
        //rtsp_buf_ready = 0;

        rtsp_protocol protocol = rtsp_protocol();
        rtsp r = rtsp(protocol);

        //for(int i=0;i<input_length;i++)
        //Serial.write(input_buff[i]);

        //r.parseRtspPackage(testPackets[0], 65);
        if(r.parseRtspPackage((char*)input_buff+3, input_length-3)!=-1)
        {


          //Serial.write(r.getMethod());

          //char * test = "PLAY rtsp://example.com/ecg.ps RTSP/1.0\r\n";
          //r.parseRtspPackage(test, 43);

          //Serial.write(r.getMethod());


          if(r.getMethod() == RTSP_METHOD_SETUP)
          {
            PacketCounter = 0;
            RSTPCurrentState=RTSPState_Ready;

            //Serial.print("M=");
            //Serial.println(protocol.getMethod(r.getMethod()));
            //Serial.print("U=");
            //Serial.println(r.getURI());f
            //Serial.print("Sq=");
            //Serial.println(r.getCSeq());
            //Serial.print("SID=");
            //Serial.println(r.getSessionID());
            //Serial.print("t=");
            //Serial.println(r.getTransport());

            unsigned char message[] = {
              framing_seq>>8,  framing_seq, RSTPCurrentState            };
            framing.sendFramedData(message,7, type_ack);

            r.putStatusLine(RTSP_STATUS_SuccessCreated);
            //r.appendCSeqHeader(r.getCSeq());
            //r.appendSessionHeader(r.getSessionID());
            //Serial.println(r.getResponse());

            framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
          }
          else
            if(r.getMethod() == RTSP_METHOD_PLAY)
            {
              RSTPCurrentState=RTSPState_Playing;

              unsigned char message[] = {
                framing_seq>>8,  framing_seq, RSTPCurrentState};
              framing.sendFramedData(message,7, type_ack);

              //Serial.print("M=");
              //Serial.println(protocol.getMethod(r.getMethod()));
              //Serial.print("U=");
              //Serial.println(r.getURI());
              //Serial.print("Sq=");
              //Serial.println(r.getCSeq());
              //Serial.print("SID=");
              //Serial.println(r.getSessionID());
              //Serial.print("t=");
              //Serial.println(r.getTransport());


              //r.putStatusLine(RTSP_STATUS_SuccessOK);
              //r.appendCSeqHeader(r.getCSeq());
              //r.appendSessionHeader(r.getSessionID());
              //Serial.println(r.getResponse());

              //framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
            }
            else
              if(r.getMethod() == RTSP_METHOD_PAUSE)
              {
                RSTPCurrentState=RTSPState_Ready;

                unsigned char message[] = {
                  framing_seq>>8,  framing_seq, RSTPCurrentState                };
                framing.sendFramedData(message,7, type_ack);

                //Serial.print("M=");
                //Serial.println(protocol.getMethod(r.getMethod()));
                //Serial.print("U=");
                //Serial.println(r.getURI());
                //Serial.print("Sq=");
                //Serial.println(r.getCSeq());
                //Serial.print("SID=");
                //Serial.println(r.getSessionID());
                //Serial.print("t=");
                //Serial.println(r.getTransport());


                //r.putStatusLine(RTSP_STATUS_SuccessOK);
                //r.appendCSeqHeader(r.getCSeq());
                //r.appendSessionHeader(r.getSessionID());
                //Serial.println(r.getResponse());

                //framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
              }
              else
                if(r.getMethod() == RTSP_METHOD_TEARDOWN)
                {
                  PacketCounter = 0;
                  
                  RSTPCurrentState=RTSPState_Init;

                  unsigned char message[] = {
                    framing_seq>>8,  framing_seq, RSTPCurrentState                  };
                  framing.sendFramedData(message,7, type_ack);

                  r.putStatusLine(RTSP_STATUS_SuccessOK);
                  //r.appendCSeqHeader(r.getCSeq());
                  //r.appendSessionHeader(r.getSessionID());
                  //Serial.println(r.getResponse());

                  framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
                }
                else
                  if(r.getMethod() == RTSP_METHOD_DESCRIBE)
                  {
                    //RSTPCurrentState=RTSPState_Init;

                    unsigned char message[] = {
                      framing_seq>>8,  framing_seq, RSTPCurrentState                    };
                    framing.sendFramedData(message,7, type_ack);

                    //r.putStatusLine(RTSP_STATUS_SuccessOK);
                    //r.appendCSeqHeader(r.getCSeq());
                    //r.appendSessionHeader(r.getSessionID());
                    //Serial.println(r.getResponse());

                    //framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
                  }
        }
        else
          // failed to parse the request package
        {
          r.putStatusLine(RTSP_STATUS_ClientBadRequest);
          //r.appendCSeqHeader(r.getCSeq());
          //r.appendSessionHeader(r.getSessionID());
          //Serial.println(r.getResponse());

          framing.sendFramedData((unsigned char *) r.getResponse(),r.getResponseLength(), type_rtsp);
        }


        break;
      }
    case type_ack:
      {
        //unsigned char message[ ] = "ack";
        //framing.sendFramedData(message,3, type_message);

        unsigned char message[] = {
          framing_seq>>8,  framing_seq, RSTPCurrentState        };
        framing.sendFramedData(message,7, type_ack);

        break;
      }
    case type_message:
      {
        unsigned char message[ ] = "message";
        framing.sendFramedData(message,7, type_message);
        break;
      }
    }
  }


  scheduler.schedule(io_task,1000);
}

