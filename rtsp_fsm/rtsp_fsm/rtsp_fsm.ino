
#include <String.h>
#include "rtsp.h"
#include "rtsp_protocol.h"
#include <avr/pgmspace.h>

  
char* testPackets[3];
rtsp_protocol protocol = rtsp_protocol();
rtsp r = rtsp(protocol);

void setup() {  
  // put your setup code here, to run once:
  Serial.begin(115200);

  testPackets[0] = "SETUP rtsp://example.com/foo/bar/baz.rm RTSP/1.0\r\n\r\nCSeq: 302\r\nTransport: RTP/AVP;unicast;client_port=4588-4589";
  //testPackets[0] = "PLAY rtsp://audio.example.com/audio RTSP/1.0\r\nCSeq: 835\r\nSession: 12345678\r\nRange: npt=10-15";   
  //testPackets[0] = "DESCRIBE rtsp://server.example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nAccept: application/sdp, application/rtsl, application/mheg";   
}

void loop() {
  Serial.println("Start Main Loop");

  /*
  Serial.print("Method: ");
  Serial.println(protocol.getMethod(1));
  Serial.print("Header: ");
  Serial.println(protocol.getHeader(10));
  Serial.print("StatusCode: ");
  Serial.println(protocol.getStatusCodeString(20));
  Serial.print("StatusCodeAsString: ");
  Serial.println(protocol.getStatusCodeAsString(20));
  Serial.print("StatusCodeNumber: ");
  Serial.println(protocol.getStatusCode(20));
  //protocol.getStatusCode(0);
  rtsp r = rtsp(protocol);
  r.testFunc(); 
*/
  
    r.parseRtspPackage(testPackets[0]);

    if(r.getMethod() == RTSP_METHOD_SETUP)
    {
      Serial.print("M=");
      Serial.println(protocol.getMethod(r.getMethod()));
      Serial.print("U=");
      Serial.println(r.getURI());
      Serial.print("Sq=");
      Serial.println(r.getCSeq());
      Serial.print("SID=");
      Serial.println(r.getSessionID());
      Serial.print("t=");
      Serial.println(r.getTransport());
      
      r.putStatusLine(RTSP_STATUS_SuccessOK);
      r.appendCSeqHeader(r.getCSeq());
      r.appendSessionHeader(r.getSessionID());
      Serial.println(r.getResponse());
      
    }
    else
    if(r.getMethod() == RTSP_METHOD_DESCRIBE)
    {
      Serial.print("M=");
      Serial.println(protocol.getMethod(r.getMethod()));
      Serial.print("U=");
      Serial.println(r.getURI());
      Serial.print("Sq=");
      Serial.println(r.getCSeq());
      Serial.print("SID=");
      Serial.println(r.getSessionID());

      r.putStatusLine(RTSP_STATUS_SuccessOK);
      r.appendCSeqHeader(r.getCSeq());
      r.appendSessionHeader(r.getSessionID());
    }
    else
    {
      Serial.print("M=");
      Serial.println(protocol.getMethod(r.getMethod()));
      Serial.print("U=");
      Serial.println(r.getURI());
      Serial.print("Sq=");
      Serial.println(r.getCSeq());
      Serial.print("SID=");
      Serial.println(r.getSessionID());
    }
    delay(1000);
 
  
}
