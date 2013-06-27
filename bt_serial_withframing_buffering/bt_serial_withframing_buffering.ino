#include <Framing.h>
#include <ByteBuffer.h>

ByteBuffer send_buffer;

Framing framing;

void setup() {
  Serial.begin(115200);          // start serial communication at 115200bps
  framing.setTimout(0.1);

  // Initialize the send buffer that we will use to send data
  send_buffer.init(30);
  
}

void loop() {
  byte input_buff[100];
  byte output_buff[100];
  int output_length, input_length, crc_valid;


  //framing.decode();
  

    // Send some dummy bytes  
    send_buffer.clear();
    send_buffer.put(65);
    send_buffer.put(66);
    send_buffer.put(67);
    send_buffer.put(68);
    send_buffer.put(69);
    send_buffer.put(70);

    //send_buffer.putInt(300);    
    //send_buffer.putLong(-100000);    
    //send_buffer.putFloat(3.14);    





  //framing.sendFramedData(output_buff,3);
  
  int len = send_buffer.getSize();
  
  for(int i=0;i<len;i++)
  {
    output_buff[i] = send_buffer.get();
  
    //Serial.write(output_buff[i]);
  }

  framing.sendFramedData(output_buff,len);
  //the values 1, 2, 3 have been sent through serial
  //framing.receiveFramedData(input_buff, input_length, crc_valid);
  //the input buffer has been filled with incoming serial data


  delay(4000);
}
