#include <avr/pgmspace.h>

#ifndef rtsp_protocol_h
#define rtsp_protocol_h

#ifndef RTSPPROTOCOL_CONSTANTS_H
#include "rtspprotocolconstants.h"
#endif



/* Definition of a class to implement a subset of RTSP RFC 2326 for use with an embedded sensor device  */

class rtsp_protocol
{

  public:
	// Constructor
	rtsp_protocol();

	// Public Variables
	//prog_char* sStatusCodeStrings[50] ;
	char* 	getMethod(int method);
	char* 	getHeader(int header);
	char* 	getStatusCodeString(int statusCode);
	char* 	getStatusCodeAsString(int statusCode);
	char* 	getVersionString();
	int 	getStatusCode(int statusCode);
  
  
  private:
	
};

#endif
