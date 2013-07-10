#include <iterator>
//#include <vector>
#include <Time>

#include "arduino.h"
#include "rtsp.h"
//#include "QTSSRTSPProtocol.h"


int debug = 0;

//Constructor Implementation
rtsp::rtsp(rtsp_protocol r) {
	
	_protocol = r;
	_responseBuffLen = 0;
}


int rtsp::parseRequestLine(char* thisline)
{
	char* parts[20];

	// First split the line by space
	parts[0] = strtok(thisline, " ");

	int count=0;
	while (parts[count]!=NULL) {
		//Serial.println(parts[count]);
		count++;
		parts[count] = strtok(NULL, " ");
	}

	//for(int i=0;i<count;i++)
	//{
	//	Serial.println(i, DEC);
	//	Serial.println(parts[i]);
	//}

	if(!(parseURI(parts[1])<0))
	// Check URI
	{
		// Now check for a method
		for(int i=0;i<=RTSP_METHOD_COUNT;i++)
		{
			char* pmethod;
			pmethod = strstr(parts[0],_protocol.getMethod(i));

			if(pmethod)
			{
				setMethod(i);
				return 1;
			}
		}

		// Bad method
		return -1;
	}
	else
	// Bad URI
	{
		return -1;
	}

	return -1;
}


int rtsp::parseHeaderLine(char* thisline)
{
	char* parts[2];

	// First split the line by space
	parts[0] = strtok(thisline, ":");
	
	if(parts[0]!=NULL)
	{
		//Serial.println(parts[0]);
		parts[1] = strtok(NULL, ":");
	}
	
	//trim(parts[1]);
	
	//Serial.println(parts[1]);
	
	if(strstr(parts[0], "CSeq"))
	// Sequence number
	{
		//Serial.print("set CSeq to: ");
		//Serial.println(parts[1]);
		setCSeq(strtol(parts[1], NULL, 10));
	}
	else
	if(strstr(parts[0], "Session"))
	// SessionID
	{
		//Serial.print("set session to: ");
		//Serial.println(parts[1]);
		setSessionID(strtol(parts[1], NULL, 10));
	}
	else
	if(strstr(parts[0], "Transport"))
	// Transport
	{
		//Serial.print("set transport to: ");
		//Serial.println(parts[1]);
		setTransport(parts[1]);
	}
	//else
	//if(strstr(parts[0], "blah"))
	// etc
	//{
	//}

	// return -1 here if any header is bad
	return 0;
}

int rtsp::parseRtspPackage(char Buf[], int length) //bool bReq
{
    int ret = 0;
    //ch	ar* saLine[20][50];
    char* headers[MAXHEADERS];
	char* line[MAXLINES];
	char* prequest;
	int  bRequest;

	//Serial.print("_");
	//for(int j=0;j<length;j++)
	//{
	//	Serial.print(Buf[j]);
	//}

	// First split the package by linefeed. Note - start on the 4th character in the buffer
	line[0] = strtok(Buf, "\n");

	//Serial.write(line[0]);

	int lineCount=0;
	while (line[lineCount]!=NULL) {
	// Store the lines in the line array
		lineCount++;
		line[lineCount] = strtok(NULL, "\n");
	}
	// Total of lineCount lines
	
	//for(int j=0;j<lineCount;j++)
	//{
	//	Serial.print("_");
	//	Serial.print(line[j]);
	//}

	// Check if first line is a request
	prequest = strstr(line[0], "RTSP/1.0");

	//Serial.write(0);
	if(prequest)
	{
		if(debug) Serial.println("Have a request");
		//Request-Line = Method SP Request-URI SP RTSP-Version CRLF
	
		//if(this is a bad request)
		//return -1;

		if(parseRequestLine(line[0])<0)
		{
			bRequest = 0;

			//if(debug) Serial.println("Failed to find method");
			return -1;
		}
		else
		{
			//if(debug) Serial.println("Request found with the following values");
			//if(debug) Serial.print("Method: ");
			//if(debug) Serial.println(_protocol.getMethod(getMethod()));
			//if(debug) Serial.print("URI: ");
			//if(debug) Serial.println(getURI());

			bRequest = 1;

			////if(debug)
			//{				
				//Serial.println("Found method");
				//Serial.println(method, DEC);
				//Serial.println(_protocol.rtsp_methods[method]);
			//}
			
			// From here we will drop out of this section to check the rest of the lines in the header after the first line
		}
	}
	else
	{
		bRequest = 0;

		//if(debug) Serial.println("Bad line");
		//Status-Line =   RTSP-Version SP Status-Code SP Reason-Phrase CRLF

		//if(this is a bad status line)
		return -1;
	}

	for(int i=1;i<lineCount;i++)
	// Now parse the rest of the headers
	{
		if(parseHeaderLine(line[i]) <0 )
		return -1;
	}

	if(getMethod()==RTSP_METHOD_SETUP)
	{
		setSessionID(123);
		//Serial.print("New SessionID is");
		//Serial.println(getSessionID(), DEC);
	}


    return 0;
}

void rtsp::setSessionID(int thisSessionID)
{
	_sessionID = thisSessionID;
}
int rtsp::getSessionID()
{
	return _sessionID;
}

void rtsp::setCSeq(int thisCSeq)
{
	_CSeq = thisCSeq;
}
int rtsp::getCSeq()
{
	return _CSeq;
}

void rtsp::setMethod(int thisMethod)
{
	_method = thisMethod;
}
int rtsp::getMethod()
{
	return _method;
}

void rtsp::setURI(char* thisURI)
{
	_URI = thisURI;
}
char* rtsp::getURI()
{
	return _URI;
}

void rtsp::setTransport(char* thisTransport)
{
	_transport = thisTransport;
}

char* rtsp::getTransport()
{
	//Serial.println("Current transport value: ");
	//Serial.println(_transport);
	return _transport;
}

int rtsp::parseURI(char* thisURI)
{
	setURI(thisURI);
	//rtsp::URI = thisURI;
	return 1;
}

// These methods are used to create the response packet

void  rtsp::putRequestLine(int method, const char* Uri)
{
    int ret = 0;
    
	memset(_responseBuff, 0, RTSP_MAX_RESPONSE_SIZE);
    _responseBuffLen = 0;
    
	ret = snprintf(_responseBuff,RTSP_MAX_RESPONSE_SIZE-_responseBuffLen, "%s %s %s\r\n", _protocol.getMethod(_method), _URI, _protocol.getVersionString());
    _responseBuffLen += ret;

    //AppendDateHeader();
}

void rtsp::putStatusLine(int rtspStatusCode)
{

    int ret = 0;

    memset(_responseBuff, 0, RTSP_MAX_RESPONSE_SIZE);
    _responseBuffLen = 0;
    ret = snprintf(_responseBuff,RTSP_MAX_RESPONSE_SIZE-_responseBuffLen, "%s %d %s\r\n",
        _protocol.getVersionString(),
        _protocol.getStatusCode(rtspStatusCode),
        _protocol.getStatusCodeString(rtspStatusCode));
    _responseBuffLen += ret;

    //AppendDateHeader();
}
void rtsp::appendCSeqHeader(int cSeq)
{

    int ret = 0;
	
	char toSend[MAX_HEADER_LENGTH-1];
	fillToSend(toSend, _protocol.getHeader(RTSP_HEADER_CSeq), MAX_HEADER_LENGTH);

	ret = snprintf(_responseBuff+_responseBuffLen, RTSP_MAX_RESPONSE_SIZE-_responseBuffLen, "%s: %u\r\n", toSend, RTSP_HEADER_CSeq);

	
    _responseBuffLen += ret;    
}
void rtsp::appendSessionHeader(long sessionID)
{
    int ret = 0;

	char toSend[MAX_HEADER_LENGTH-1];
	fillToSend(toSend, _protocol.getHeader(RTSP_HEADER_Session), MAX_HEADER_LENGTH);

	ret = snprintf(_responseBuff+_responseBuffLen, RTSP_MAX_RESPONSE_SIZE-_responseBuffLen, "%s: %u\r\n", toSend, _sessionID);

    _responseBuffLen += ret;
}
void rtsp::appendDateHeader()
{

    int ret = 0;
	//Time

/*
	// digital clock display of the time
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.print(" ");
	Serial.print(day());
	Serial.print(" ");
	Serial.print(month());
	Serial.print(" ");
	Serial.print(year()); 
	Serial.println(); */

/*
	char toSend[MAX_HEADER_LENGTH-1];
	fillToSend(toSend, _protocol.getHeader(RTSP_HEADER_CSeq), MAX_HEADER_LENGTH);

	ret = snprintf(_responseBuff+_responseBuffLen, RTSP_MAX_RESPONSE_SIZE-_responseBuffLen, "%s: %u\r\n", toSend, RTSP_HEADER_CSeq);

	
    _responseBuffLen += ret;    */
}


void rtsp::printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

char* rtsp::getResponse()
{
	//Serial.println("Current transport value: ");
	//Serial.println(_transport);
	return _responseBuff;
}

int rtsp::getResponseLength()
{
	//Serial.println("Current transport value: ");
	//Serial.println(_transport);
	return _responseBuffLen;
}

void rtsp::fillToSend(char* toSend, char* fromProtocol, int max)
// Need this function because the snprintf function above is returning incorrect values possibly because of the undefined length of the call to _protocol.getHeader
{
	int i=0;
	for(i=0;i<max;i++)
	{
		toSend[i] = fromProtocol[i];
	}
}

void rtsp::trim(char* str)
{
    if(!str)
        return;

    char* ptr = str;
    int len = strlen(ptr);

    while(len-1 > 0 && isspace(ptr[len-1]))
        ptr[--len] = 0;

    while(*ptr && isspace(*ptr))
        ++ptr, --len;

    memmove(str, ptr, len + 1);
}
