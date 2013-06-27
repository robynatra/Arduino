#include "Framing.h"

Framing framing;

void setup() {
  Serial.begin(115200);          // start serial communication at 115200bps
  framing.setTimout(0.1);
}

void loop() {
  byte input_buff[100];
  byte output_buff[100];
  int output_length, input_length, crc_valid;

  //output_buff[0]=0;
  //output_buff[1]=1;
  //output_buff[2]=2;
  //output_length=3;

  output_buff[0]=65;  // A
  output_buff[1]=66;  // B
  output_buff[2]=67;  // C
  output_length=3;

  framing.sendFramedData(output_buff,3);
  //the values 1, 2, 3 have been sent through serial
  framing.receiveFramedData(input_buff, input_length, crc_valid);
  //the input buffer has been filled with incoming serial data

  delay(4000);
}
