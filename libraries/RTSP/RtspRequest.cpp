#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "RtspRequest.h"
#include "StringUtil.h"
#include "RTSPProtocol.h"
#include "StrPtrLen.h"
#include "StringTranslator.h"
//#include "Common.h"

#define CRLF "\r\n"
#define CRLF2 "\r\n\r\n"
//extern ConfigItem_t g_ConfigItem;

UInt8
RtspRequest::sURLStopConditions[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, //0-9      //'\t' is a stop condition
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, //10-19    //'\r' & '\n' are stop conditions
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //20-29
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, //30-39    //' '
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //40-49
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //50-59
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, //60-69   //'?' 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //70-79
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //80-89
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //90-99
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //100-109
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //110-119
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //120-129
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //130-139
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //140-149
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //150-159
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //160-169
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //170-179
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //180-189
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //190-199
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //200-209
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //210-219
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //220-229
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //230-239
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //240-249
    0, 0, 0, 0, 0, 0             //250-255
};

int RtspRequest::ParseRtspPackage(char Buf[], int Size) //bool bReq
{
    int ret = 0;
    StringArray_t saLine;
    StringPair_t spHeader;
    string Delim=CRLF;
    string sRequest(Buf, Size);
    U32 theHeader = 0;
    StringUtil::Trim(sRequest);
    StringUtil::Split(sRequest, Delim, saLine);
    //Request Line
    
    if(strncmp(saLine[0].c_str(), RTSPProtocol::GetVersionString(RTSPProtocol::k10Version).Ptr, RTSPProtocol::GetVersionString(RTSPProtocol::k10Version).Len) != 0) //bReq
    {    
        m_bIsRequest = true;
        ret = ParseRequestLine(saLine[0]);
        if(ret < 0)
        {
            return -1;
        }
    }
    else
    {
        m_bIsRequest = false;
        ret = ParseStatusLine(saLine[0]);
        if(ret < 0)
        {
            return -1;
        }    
    }
    //Parse Header
    for(int i=1; i<saLine.size(); i++)
    {           
        StringUtil::Split(saLine[i], ':', spHeader);
        theHeader = RTSPProtocol::GetRequestHeader(StrPtrLen((char*)spHeader.first.c_str()));
        if(qtssIllegalHeader != theHeader)
        {
            StringUtil::Trim(spHeader.second);
            m_HeaderDict[theHeader] = spHeader.second;
        }

        //some headers require some special processing. If this code begins
        //to get out of control, we made need to come up with a function pointer table
        switch (theHeader)
        {
            case qtssSessionHeader:             ParseSessionHeader(); break;
            case qtssCSeqHeader:                ParseCSeqHeader(); break;
            case qtssTransportHeader:           ParseTransportHeader(); break;
            case qtssRangeHeader:               ParseRangeHeader();     break;
            case qtssContentLengthHeader:       ParseContentLengthHeader();break;
            case qtssSpeedHeader:               ParseSpeedHeader();     break;
            case qtssScaleHeader:               ParseScaleHeader();     break;
            case qtssRequireHeader:             ParseRequireHeader();   break;
            case ngodNoticeHeader:              ParseNoticeHeader();    break;
            case ngodOnDemandSessionIdHeader:   ParseOnDemandSessionIdHeader(); break;
            case ngodReasonHeader:              ParseReasonHeader(); break;
            case ngodSessionGroupHeader:        ParseSessionGroupHeader(); break;
            default:    break;
        }

    }
    return 0;
}


/*
U8 RtspRequest::GetMethod()
{
}
U32 RtspRequest::GetSessionID()
{}

//will be -1 unless there was a Range header. May have one or two values
S64 RtspRequest::GetStartTime()
{}
S64 RtspRequest::GetStopTime()
{}
// Value of Speed: header in request
U8 RtspRequest::GetSpeed()
{
}
S8 RtspRequest::GetScale()
{
}
U64 RtspRequest::GetPlayTimePoint()
{
}
U8 RtspRequest::GetTransportMode()
{
}    */
// these get set if there is a transport header
//U16 RtspRequest::GetClientPortA()    { return m_ClientPortA; }
//U16 RtspRequest::GetClientPortB()    { return m_ClientPortB; }

//char* RtspRequest::GetFileName(){}
//char* RtspRequest::GetFileDir(){}
//char* RtspRequest::GetFilePath(){ return m_sFilePath; } //full path
/*
char* RtspRequest::GetFullFilePath()
{
    snprintf(m_sFullFilePath, RTSP_FILE_PATH_LEN_MAX,"%s%s",
        g_ConfigItem.MediaRoot, m_sFilePath);
    return m_sFullFilePath;
}

int RtspRequest::GetFileType()
{
    char *extension = strrchr(m_sFilePath, '.');
    if(extension == NULL) 
        return HSS_MEDIA_TYPE_HITS;

    if(strcasecmp(extension, ".ts") == 0)
        return HSS_MEDIA_TYPE_MP2T;

    if(strcasecmp(extension, ".mp4") == 0)
        return HSS_MEDIA_TYPE_MP4;
}
*/

//package request/response msg

void  RtspRequest::PutRequestLine(U8 Method, const char* Uri, U8 RtspVer)
{
    int ret = 0;
    memset(m_sBuffer, 0, RTSP_REQUEST_MSG_LEN_MAX);
    m_iBufLen = 0;
    ret = snprintf(m_sBuffer,RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s %s %s\r\n",
        RTSPProtocol::GetMethodString(Method).Ptr,
        Uri, RTSPProtocol::GetVersionString(RTSPProtocol::k10Version).Ptr);
    m_iBufLen += ret;
    
    AppendDateHeader();
}

void RtspRequest::PutStatusLine(U16 RtspStatusCode, U16 RtspVersion)
{
    int ret = 0;
    memset(m_sBuffer, 0, RTSP_REQUEST_MSG_LEN_MAX);
    m_iBufLen = 0;
    ret = snprintf(m_sBuffer,RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s %d %s\r\n",
        RTSPProtocol::GetVersionString(RTSPProtocol::k10Version).Ptr,
        RTSPProtocol::GetStatusCode(RtspStatusCode),
        RTSPProtocol::GetStatusCodeString(RtspStatusCode).Ptr);
    m_iBufLen += ret;
    
    AppendDateHeader();
}
void RtspRequest::AppendCSeqHeader(U32 CSeq)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %u\r\n",
        RTSPProtocol::GetHeaderString(qtssCSeqHeader).Ptr, CSeq);
    m_iBufLen += ret;    
}
void RtspRequest::AppendSessionHeader(U32 SessID)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %u\r\n",
        RTSPProtocol::GetHeaderString(qtssSessionHeader).Ptr, SessID);
    m_iBufLen += ret;
}
void RtspRequest::AppendTransportHeader(U16 SvrPortA, U16 SvrPortB)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %s;server_port=%u-%u\r\n",
        RTSPProtocol::GetHeaderString(qtssTransportHeader).Ptr, 
        m_HeaderDict[qtssTransportHeader].c_str(), SvrPortA, SvrPortB);
    m_iBufLen += ret;
}
void RtspRequest::AppendUDPTransportHeader(const char* Client, const char* DestIP, U16 ClientPort, const char* EdgeInputGroup)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: MP2T/DVBC/UDP;unicast;client=%s;destination=%s;client_port=%d;edge_input_group=%s\r\n",
        RTSPProtocol::GetHeaderString(qtssTransportHeader).Ptr, 
        Client, DestIP, ClientPort, EdgeInputGroup);
    m_iBufLen += ret;
}
void RtspRequest::AppendIPQamTransportHeader(const char* Client, const char* QamName, const char* QamGroup, U32 Frequency, U16 QamMode, U16 ProgramNumber)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: MP2T/DVBC/QAM;unicast;client=%s;qam_destination=%d.%d;qam_name=%s;qam_group=%s;modulation=qam%d\r\n",
        RTSPProtocol::GetHeaderString(qtssTransportHeader).Ptr, 
        Client, Frequency, ProgramNumber, QamName, QamGroup, QamMode);
    m_iBufLen += ret;
}
void RtspRequest::AppendRtpInfoHeader()
{
}

void RtspRequest::AppendDateHeader()
{
    char buf[200];
    int ret = 0;
    time_t tt = time(NULL);
    strftime(buf, sizeof(buf), "Date: %a, %b %d %Y %H:%M:%S GMT\r\n", gmtime(&tt));

    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s", buf);
    m_iBufLen += ret;
}

//Public: OPTIONS,DESCRIBE,SETUP,TEARDOWN,PLAY,PAUSE,GET_PARAMETER,SET_PARAMETER
void RtspRequest::AppendPublicHeader()
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "Public: OPTIONS,SETUP,TEARDOWN,PLAY,PAUSE,GET_PARAMETER\r\n");
    m_iBufLen += ret;
}

void RtspRequest::AppendContentType(const char* sConType)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %s\r\n",
        RTSPProtocol::GetHeaderString(qtssContentTypeHeader).Ptr, sConType);
    m_iBufLen += ret;
}    
void RtspRequest::AppendContentLength(int Len)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %d\r\n",
        RTSPProtocol::GetHeaderString(qtssContentLengthHeader).Ptr, Len);
    m_iBufLen += ret;
}

int RtspRequest::AppendContent(const char* Buf, int Len)
{
    int ret = 0;
    if(Len < (RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen))
    {
        memcpy(m_sBuffer+m_iBufLen, Buf, Len); 
        m_iBufLen += Len;  
        return 0;
    } 

    return -1;
}

void RtspRequest::AppendCRLF()
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, CRLF);
    m_iBufLen += ret;

}
/*
void RtspRequest::AppendSDP(const char* sSDP, int Len)
{
    int ret = 0;
    AppendContentType("application/sdp");
    AppendContentLength(Len);
    AppendCRLF();
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s", sSDP);
    m_iBufLen += ret;
}
*/
void RtspRequest::AppendRequireHeader(const char* str)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %s\r\n",
        RTSPProtocol::GetHeaderString(qtssRequireHeader).Ptr, str);
    m_iBufLen += ret;
}

void RtspRequest::AppendNoticeHeader(U16 NoticeCode, const char* NoticeDesc)
{
    int ret = 0;
    ret = snprintf(m_sBuffer+m_iBufLen, RTSP_REQUEST_MSG_LEN_MAX-m_iBufLen, "%s: %d \"%s\"\r\n",
        RTSPProtocol::GetHeaderString(ngodNoticeHeader).Ptr, NoticeCode, NoticeDesc);
    m_iBufLen += ret;    
}

//Status-Line =   RTSP-Version SP Status-Code SP Reason-Phrase CRLF
int RtspRequest::ParseStatusLine(string& sStatusLine)
{
    int ret = 0;
    StringPair_t StrPair;
    
    StringUtil::Split(sStatusLine, ' ', StrPair);
 
    if(strcmp(RTSPProtocol::GetVersionString(RTSPProtocol::k10Version).Ptr, StrPair.first.c_str()) != 0)
    {
        return -1;
    }    

    StringUtil::Split(StrPair.second, ' ', StrPair);
        
    m_StatusCode = atoi(StrPair.first.c_str());
    m_ReasonPhrase = StrPair.second;

    return 0;
}


//Request-Line = Method SP Request-URI SP RTSP-Version CRLF
int RtspRequest::ParseRequestLine(string& sReqLine)
{
    int ret = 0;
    //StringArray_t saReqLineParam;
    m_Method = qtssIllegalMethod;
#if 0    
    StringUtil::Split(sReqLine, ' ', saReqLineParam);
    if(saReqLineParam.size() == 3) 
    {    
        m_Method = RTSPProtocol::GetMethod(StrPtrLen(saReqLineParam[0].c_str()));
        if(qtssIllegalMethod != m_Method)
        {
            return -1;//qtssClientBadRequest;
        }

        ret = ParseRtspURI(saReqLineParam[1].c_str());
        if(ret < 0)
        {
            return -1;
        }

        StrPtrLen RtspVer = RTSPProtocol::GetVersionString(RTSPProtocol::k10Version);
        if(strcmp(RtspVer.Ptr, saReqLineParam[2].c_str()) != 0)
        {
            return -1;
        }
    }
#endif 
//first get the method
    StrPtrLen ReqLine((char*)sReqLine.c_str());
    StringParser parser(&ReqLine);
    StrPtrLen theParsedData;
    parser.ConsumeWord(&theParsedData);
    //this->SetVal(qtssRTSPReqMethodStr, theParsedData.Ptr, theParsedData.Len);


    //THIS WORKS UNDER THE ASSUMPTION THAT:
    //valid HTTP/1.1 headers are: GET, HEAD, POST, PUT, OPTIONS, DELETE, TRACE
    m_Method = RTSPProtocol::GetMethod(theParsedData);
    if (m_Method == qtssIllegalMethod)
        return -1;//QTSSModuleUtils::SendErrorResponse(this, qtssClientBadRequest, qtssMsgBadRTSPMethod, &theParsedData);

    //no longer assume this is a space... instead, just consume whitespace
    parser.ConsumeWhitespace();

    //now parse the uri
    ret = ParseRtspURI(parser);
    if (ret < 0)
        return -1;

    //no longer assume this is a space... instead, just consume whitespace
    parser.ConsumeWhitespace();

    //if there is a version, consume the version string
    StrPtrLen versionStr;
    parser.ConsumeUntil(&versionStr, StringParser::sEOLMask);

    //check the version
    if (versionStr.Len < 0 || RTSPProtocol::k10Version != RTSPProtocol::GetVersion(versionStr))
        return -1;

    //go past the end of line
    //if (!parser.ExpectEOL())
    //    return QTSSModuleUtils::SendErrorResponse(this, qtssClientBadRequest, qtssMsgNoRTSPVersion,&theParsedData);
    return 0;//QTSS_NoErr;

}

int RtspRequest::ParseRtspURI(StringParser &parser)//string& sRtspURI
{
    //read in the complete URL, set it to be the qtssAbsoluteURLParam
    StrPtrLen theAbsURL;
    //StringParser parser(StrPtrLen((char*)sRtspURI.c_str()));

    //  RTSPRequestInterface::sPathURLStopConditions stop on ? as well as sURLStopConditions
    parser.ConsumeUntil(&theAbsURL, sURLStopConditions );

    // set qtssRTSPReqAbsoluteURL to the URL throught the path component; will be : <protocol>://<host-addr>/<path>
    //this->SetVal(qtssRTSPReqAbsoluteURL, &theAbsURL);
    
    StringParser urlParser(&theAbsURL);
    
    //we always should have a slash before the uri.
    //If not, that indicates this is a full URI. Also, this could be a '*' OPTIONS request
    if ((*theAbsURL.Ptr != '/') && (*theAbsURL.Ptr != '*'))
    {
        //if it is a full URL, store the host name off in a separate parameter
        StrPtrLen theRTSPString;
        urlParser.ConsumeLength(&theRTSPString, 7); //consume "rtsp://"
        //assign the host field here to the proper QTSS param
        StrPtrLen theHost;
        urlParser.ConsumeUntil(&theHost, '/');
        //fHeaderDictionary.SetVal(qtssHostHeader, &theHost);
        ///save host
    }
    // don't allow non-aggregate operations indicated by a url/media track=id
// might need this for rate adapt   if (qtssSetupMethod != fMethod && qtssOptionsMethod != fMethod && qtssSetParameterMethod != fMethod) // any method not a setup, options, or setparameter is not allowed to have a "/trackID=" in the url.
    if (qtssSetupMethod != m_Method) // any method not a setup is not allowed to have a "/trackID=" in the url.
    {
        StrPtrLenDel tempCStr(theAbsURL.GetAsCString()); 
        StrPtrLen nonaggregate(tempCStr.FindString("/trackID="));
        if (nonaggregate.Len > 0) // check for non-aggregate method and return error
            return -1;//QTSSModuleUtils::SendErrorResponse(this, qtssClientAggregateOptionAllowed, qtssMsgBadRTSPMethod, &theAbsURL);
    }        
    // In case there is no URI at all... we have to fake it.
    static char* sSlashURI = "/";
        
    //whatever is in this position in the URL must be the URI. Store that
    //in the qtssURLParam. Confused?
    StrPtrLen theURLParam;
    UInt32 uriLen = urlParser.GetDataReceivedLen() - urlParser.GetDataParsedLen();
    if (uriLen > 0)
        ///this->SetVal(qtssRTSPReqURI, urlParser.GetCurrentPosition(), urlParser.GetDataReceivedLen() - urlParser.GetDataParsedLen());
        theURLParam.Set(urlParser.GetCurrentPosition(), urlParser.GetDataReceivedLen() - urlParser.GetDataParsedLen());
    else
        //
        // This might happen if there is nothing after the host at all, not even
        // a '/'. This is legal (RFC 2326, Sec 3.2). If so, just pretend that there
        // is a '/'
        ///this->SetVal(qtssRTSPReqURI, sSlashURI, 1);
        theURLParam.Set(sSlashURI, 1);

    // parse the query string from the url if present.
    // init qtssRTSPReqQueryString dictionary to an empty string
    StrPtrLen queryString;
    ///this->SetVal(qtssRTSPReqQueryString, queryString.Ptr, queryString.Len);
    
    if ( parser.GetDataRemaining() > 0 )
    {   
        if ( parser.PeekFast() == '?' )
        {       
            // we've got some CGI param
            parser.ConsumeLength(&queryString, 1); // toss '?'
            
            // consume the rest of the line..
            parser.ConsumeUntilWhitespace(&queryString);
            
            ///this->SetVal(qtssRTSPReqQueryString, queryString.Ptr, queryString.Len);
        }
    }
 
 
    //
    // If the is a '*', return right now because '*' is not a path
    // so the below functions don't make any sense.
    if ((*theAbsURL.Ptr == '*') && (theAbsURL.Len == 1))
    {
        //this->SetValue(qtssRTSPReqFilePath, 0, theAbsURL.Ptr, theAbsURL.Len, QTSSDictionary::kDontObeyReadOnly);
        strncpy(m_sFilePath, theAbsURL.Ptr, theAbsURL.Len);
        return 0;//QTSS_NoErr;
    }
    
    //path strings are statically allocated. Therefore, if they are longer than
    //this length we won't be able to handle the request.
    //StrPtrLen* theURLParam = this->GetValue(qtssRTSPReqURI);
    if (theURLParam.Len > RTSP_FILE_PATH_LEN_MAX)
        return -1; //QTSSModuleUtils::SendErrorResponse(this, qtssClientBadRequest, qtssMsgURLTooLong, theURLParam);

    //decode the URL, put the result in the separate buffer for the file path,
    //set the file path StrPtrLen to the proper value
    SInt32 theBytesWritten = StringTranslator::DecodeURL(theURLParam.Ptr, theURLParam.Len,
                                                m_sFilePath, RTSP_FILE_PATH_LEN_MAX);
    //if negative, an error occurred, reported as an QTSS_Error
    //we also need to leave room for a terminator.
    if ((theBytesWritten < 0) || (theBytesWritten == RTSP_FILE_PATH_LEN_MAX))
    {
        return -1;//QTSSModuleUtils::SendErrorResponse(this, qtssClientBadRequest, qtssMsgURLInBadFormat, theURLParam);
    }

    // Convert from a / delimited path to a local file system path
    ///StringTranslator::DecodePath(m_sFilePath, theBytesWritten);
    
    //setup the proper QTSS param
    m_sFilePath[theBytesWritten] = '\0';
    //this->SetVal(qtssRTSPReqFilePath, fFilePath, theBytesWritten);
    //this->SetValue(qtssRTSPReqFilePath, 0, fFilePath, theBytesWritten, QTSSDictionary::kDontObeyReadOnly);

    if (qtssSetupMethod == m_Method)
    {
        StrPtrLen thePathPtr(m_sFilePath);
        char *trackStr = thePathPtr.FindString("/trackID=");
        if (trackStr != NULL && *trackStr != 0)
        {
            *trackStr = 0; // terminate the string.
            //thePathPtr.Len = ::strlen(thePathPtr.Ptr);
        }
    }
    
    return 0;//QTSS_NoErr;
}

void RtspRequest::ParseSessionHeader()
{
    U32 sid = 0;
    const char *fields = m_HeaderDict[qtssSessionHeader].c_str();
    if (sscanf(fields, "%u", &sid) == 1) {
      m_SessionID = sid;
    } else {
      //return False; // The header is malformed
    }   
}

void RtspRequest::ParseCSeqHeader()
{
    m_CSeq = atol(m_HeaderDict[qtssCSeqHeader].c_str());
}

void RtspRequest::ParseRangeHeader()
{
    double start, end;
    char *fields = (char*)m_HeaderDict[qtssRangeHeader].c_str();
    if (sscanf(fields, "npt=%lf-%lf", &start, &end) == 2) {
      m_RangeStartTime = start;
      m_RangeStopTime = end;
    } else if (sscanf(fields, "npt=%lf-", &start) == 1) {
      m_RangeStartTime = start;
      m_RangeStopTime = -1;
    } else if (strcmp(fields, "npt=now-") == 0) {
      m_RangeStartTime = -1;
      m_RangeStopTime = -1;
    } else {
      //return False; // The header is malformed
    }

}
void RtspRequest::ParseTransportHeader()
{
    char* fields = (char*)m_HeaderDict[qtssTransportHeader].c_str();
    char field[128] = "";
    U8 TTL;
    U16 PortA,PortB;
    m_TransportMode = TRAN_MOD_ILLEGAL;
    while (sscanf(fields, "%[^;]", field) == 1) 
    {
        if(strcmp(field, "RTP/AVP/UDP") == 0 || strcmp(field, "RTP/AVP") == 0)
        {
            m_TransportMode = TRAN_MOD_RTP_UDP;
        }
        //else if (strcmp(field, "HIRTP/AVP/UDP") == 0) 
        //{
        //    m_TransportMode = TRAN_MOD_HIRTP_UDP;
        //}
        else if (strcmp(field, "RTP/AVP/TCP") == 0) 
        {
            m_TransportMode = TRAN_MOD_RTP_TCP;
        }
        else if (strcmp(field, "RAW/RAW/UDP") == 0 ||
                    strcmp(field, "MP2T/H2221/UDP") == 0) 
        {
            m_TransportMode = TRAN_MOD_MP2T_UDP;
        } 
        else if(strcmp(field, "MP2T/DVBC/QAM") == 0)
        {
            m_TransportMode = TRAN_MOD_MP2T_QAM;
        }
        else if(strcmp(field, "unicast") == 0)
        {
            
        }
        else if (strncasecmp(field, "destination=", 12) == 0) 
        {        
            m_DstIP = ntohl(inet_addr(field+12));
        } 
        else if (sscanf(field, "ttl=%u", &TTL) == 1) 
        {
            m_DstTTL = (U8)TTL;
        } 
        else if (sscanf(field, "client_port=%hu-%hu", &PortA, &PortB) == 2) 
        {
            m_ClientPortA = PortA;
            m_ClientPortB= PortB;
        } 
        else if (sscanf(field, "client_port=%hu", &PortA) == 1) 
        {
            m_ClientPortA = PortA;
            m_ClientPortB= 0;
        } 
        else if(strncasecmp(field, "bandwidth=", 10) == 0)
        {
            m_BandWidth = atoi(field+10);
        }
        else if(strncasecmp(field, "client=", 7) == 0)
        {
            //strcpy(dest, field+7);
            m_Client = (field+7);
        }        
        else if(strncasecmp(field, "qam_name=", 9) == 0)
        {
            //strcpy(dest, field+9);
            m_QamName = (field+9);
        }       
        else if(strncasecmp(field, "modulation=qam", 14) == 0)
        {
            m_QamMod = atoi(field+14);
        }
        //else if (sscanf(field, "interleaved=%u-%u", &rtpCid, &rtcpCid) == 2) {
        //rtpChannelId = (unsigned char)rtpCid;
        //rtcpChannelId = (unsigned char)rtcpCid;
        //}

        fields += strlen(field);
        while (*fields == ';') ++fields; // skip over separating ';' chars
        if (*fields == '\0' || *fields == '\r' || *fields == '\n') break;
    }

}
void RtspRequest::ParseContentLengthHeader()
{
    int len = 0;
    const char *fields = m_HeaderDict[qtssContentLengthHeader].c_str();
    if (sscanf(fields, "%d", &len) == 1) {
      m_ContentLength = len;
    } else {
      //return False; // The header is malformed
    }

}
void RtspRequest::ParseSpeedHeader()
{
    float sp = 0;
    const char *fields = m_HeaderDict[qtssSpeedHeader].c_str();
    if (sscanf(fields, "%f", &sp) == 1) {
      m_Speed = sp*100;
    } else {
      //return False; // The header is malformed
    }
}
void RtspRequest::ParseScaleHeader()
{
    float sc = 0;
    const char *fields = m_HeaderDict[qtssScaleHeader].c_str();
    if (sscanf(fields, "%f", &sc) == 1) {
      m_Scale = sc;
    } else {
      //return False; // The header is malformed
    }
}

void RtspRequest::ParseRequireHeader()
{
    m_Require = m_HeaderDict[qtssRequireHeader];
}
void RtspRequest::ParseSessionGroupHeader()
{
    m_SessionGroup = m_HeaderDict[ngodSessionGroupHeader];
}
void RtspRequest::ParseOnDemandSessionIdHeader()
{
    m_OnDemandSessionID = m_HeaderDict[ngodOnDemandSessionIdHeader];
}
void RtspRequest::ParseReasonHeader()
{
    const char *fields = m_HeaderDict[ngodReasonHeader].c_str();
    StringPair_t StrPair;
    StringUtil::Split(m_HeaderDict[ngodReasonHeader], ' ', StrPair);
    m_ReasonCode = atoi(StrPair.first.c_str());
    m_ReasonDesc = StrPair.second;
}
void RtspRequest::ParseNoticeHeader()
{
    const char *fields = m_HeaderDict[ngodReasonHeader].c_str();
    StringPair_t StrPair;
    StringUtil::Split(m_HeaderDict[ngodReasonHeader], ' ', StrPair);
    m_NoticeCode = atoi(StrPair.first.c_str());
    m_NoticeDesc = StrPair.second;
}





