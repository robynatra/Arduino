#ifndef rtsp_h
#define rtsp_h


#ifndef RTSPPROTOCOL_CONSTANTS_H
#include "rtspprotocolconstants.h"
#endif

#ifndef rtsp_protocol_h
#include "rtsp_protocol.h"
#endif

#define CRLF "\r\n"
#define MAXLINES 64						// Maximum amount of lines accepted in the packet
#define MAXHEADERS 64					// Maximum amount of headers accepted
#define MAX_HEADER_LENGTH 18			// Maximum number of characters in a header string eg Proxy-Authenticate length is 18
#define MAX_SEQUENCE_LENGTH 6			// Maximum length of the CSeq number

typedef int QTSS_RTSPStatusCode;


  
/* Definition of a class to implement a subset of RTSP RFC 2326 for use with an embedded sensor device  */

class rtsp
{

  public:
    // Constructor
    rtsp(rtsp_protocol r);
	
	// Public Methods
	
	int 	parseRtspPackage(char buf[], int length); //bool bReq
	int 	getCSeq();
	void 	setCSeq(int thisCSeq);
	int 	getMethod();
	void 	setMethod(int thisMethod);
	int 	getSessionID();
	void 	setSessionID(int thisSessionID);
	char* 	getURI();
	void 	setURI(char* thisURI);
	char* 	getTransport();
	void 	setTransport(char* thisTransport);
	char* 	getResponse();
	int 	getResponseLength();
	
	// Methods to creates a response
	void 	putRequestLine(int method, const char* Uri);
	void 	putStatusLine(int rtspStatusCode);
	void 	appendCSeqHeader(int cSeq);
	void 	appendSessionHeader(long sessionID);
	void 	appendDateHeader();
	
  private:
	// Private variables
	// Variables from incoming request
	int 	_method;
	char* 	_URI;
	char* 	_transport;
	int 	_CSeq;
	int 	_sessionID;
	rtsp_protocol _protocol;

	// Private methods
	// Methods to read a request
	int 	parseRequestLine(char* line);
	int 	parseHeaderLine(char* line);
    int 	parseURI(char* line);



	void 	printDigits(int digits);
	void 	fillToSend(char* toSend, char* fromProtocol, int max);
	void 	trim(char* str);
	
	
  protected:
	// Protected variables
	// Variables for outgoing response
	char	_responseBuff[RTSP_MAX_RESPONSE_SIZE];
	int		_responseBuffLen;
	
};

#endif
