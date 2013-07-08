#ifndef __RTSPREQUEST_H__
#define __RTSPREQUEST_H__
#include <map>
#include <string>
#include "RtspRequestInterface.h"
#include "StringParser.h"
#include "RTSPProtocol.h"

using namespace std;

class RtspRequest : public RtspRequestInterface
{
public:
    //RtspRequest(char* Buf, int Len):RtspRequestInterface(Buf, Len){}
    RtspRequest(){}
    virtual ~RtspRequest(){}

    int ParseRtspPackage(char Buf[], int Size); //bool bReq = true
    
    //read request data 

    //U8 GetMethod();
    //U32 GetSessionID();

    //will be -1 unless there was a Range header. May have one or two values
    //S64 GetStartTime();
    //S64 GetStopTime();

    // Value of Speed: header in request
    //U8 GetSpeed();
    //S8 GetScale();
    //U64 GetPlayTimePoint();

    //U8 GetTransportMode();
        
    // these get set if there is a transport header
    //U16 GetClientPortA()    { return m_ClientPortA; }
    //U16 GetClientPortB()    { return m_ClientPortB; }

    //char* GetFileName(){}
    //char* GetFileDir(){}
    //char* GetFilePath(){ return m_sFilePath; } //full path
    //char* GetFullFilePath();
    //int GetFileType();

    //package request/response msg
    void PutRequestLine(U8 Method, const char* Uri, U8 RtspVer = 0);
    void PutStatusLine(U16 RtspStatusCode, U16 RtspVersion = 0);
    void AppendCSeqHeader(U32 CSeq);
    void AppendSessionHeader(U32 SessID);
    void AppendTransportHeader(U16 SvrPortA, U16 SvrPortB);
    void AppendUDPTransportHeader(const char* Client, const char* DestIP, U16 ClientPort, const char* EdgeInputGroup);
    void AppendIPQamTransportHeader(const char* Client, const char* QamName, const char* QamGroup, U32 Frequency, U16 QamMode, U16 ProgramNumber);
    void AppendRtpInfoHeader(); 
    void AppendDateHeader();
    void AppendPublicHeader();
    void AppendRequireHeader(const char* str);
    void AppendContentType(const char* sConType);
    void AppendContentLength(int Len);
    int  AppendContent(const char* Buf, int Len);
    //void AppendSDP(const char* sSDP, int Len);
    void AppendCRLF();

    void AppendNoticeHeader(U16 NoticeCode, const char* NoticeDesc);
    
    //U8* GetResponsePacket(){ return m_sBuffer; }
    //int GetResponsePacketLen(){ return m_iBufLen; }
private:
    int ParseStatusLine(string& sStatusLine);
    int ParseRequestLine(string& sReqLine);
    int ParseRtspURI(StringParser &parser);
    void ParseSessionHeader();
    void ParseCSeqHeader();
    void ParseRangeHeader();
    void ParseTransportHeader();
    //void ParseContentType();
    void ParseContentLengthHeader();
    void ParseSpeedHeader();
    void ParseScaleHeader();
    void ParseRequireHeader();
    void ParseSessionGroupHeader();
    void ParseOnDemandSessionIdHeader();
    void ParseReasonHeader();
    void ParseNoticeHeader();

private:
    map<U32, string> m_HeaderDict;
    static UInt8    sURLStopConditions[];
};

#endif //__RTSPREQUEST_H__

