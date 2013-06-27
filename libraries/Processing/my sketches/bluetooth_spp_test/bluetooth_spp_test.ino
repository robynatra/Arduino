char val;         // variable to receive data from the serial port


void setup() {
  Serial.begin(115200);          // start serial communication at 115200bps

}


void loop() {
  if( Serial.available() )         // if data is available to read
  {
    val = Serial.read();          // read it and store it in 'val'
  }
  
  if( val == 'H' )                     // if 'H' was received
  {
    Serial.println("123456789");
    Serial.println("abcdefghijklmnopqrstuvwxqz");
  } else { 
    Serial.println("low");
  }
  delay(1000);                         // wait 100ms for next reading
}

String byteStuffString(String string)
{
  for(int i=0;i=string.length;i++)
  {
    Serial.out(i);
  }
}
