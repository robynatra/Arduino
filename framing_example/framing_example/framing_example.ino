#include "Framing.h"

Framing framing;

void setup() {
  Serial.begin(9600);
  framing.setTimout(0.1);
}

void loop() {
  unsigned char input_buff[100];
  unsigned char output_buff[100];
  int output_length, input_length, crc_valid,framing_seq, dataType;
  char type_rtp = '1';
  char type_rtsp = '2';
  char type_ack = '3';
  char type_message = '4';
  

  output_buff[0]='a';
  output_buff[1]='b';
  output_buff[2]='c';
  output_length=3;

  //framing.sendFramedData(output_buff,3, type_rtsp);
  
  //the values 1, 2, 3 have been sent through serial
  //framing.receiveFramedData(input_buff, input_length, crc_valid);
    //framing.receiveFramedData(input_buff, input_length, crc_valid, framing_seq, dataType);
  //the input buffer has been filled with incoming serial data
 
    unsigned char message[ ] = "arduino";
    framing.sendFramedData(message,2, type_ack);

 /*
 if((crc_valid!=0) && (input_length>0))
  {
    output_buff[0]='1';
    output_length=1;
    framing.sendFramedData(output_buff,output_length, type_ack);


    unsigned char message[ ] = "arduino";
    //message.toCharArray(output_message, 0, 5);

    framing.sendFramedData(message,7, type_message);
  }*/


  delay(10000);
}
