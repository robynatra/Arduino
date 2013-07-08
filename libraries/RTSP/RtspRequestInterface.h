#ifndef __RTSPREQUESTINTERFACE_H__
#define __RTSPREQUESTINTERFACE_H__
//#include <limits.h>
//#include <string.h>
#include <string>
//#include "Common.h"
//#include "RtspProtocolHitv.h"
#include "type.h"
#include "QTSSRTSPProtocol.h"
using namespace std;

#define RTSP_REQUEST_MSG_LEN_MAX 4096
//#define RTSP_REQUEST_CONTENT_LEN_MAX 2048
#define RTSP_FILE_PATH_LEN_MAX 256

//Transport Mode Define
enum
{
    TRAN_MOD_HIRTP_UDP,
    TRAN_MOD_RTP_UDP,
    TRAN_MOD_RTP_TCP,
    TRAN_MOD_MP2T_UDP,
    TRAN_MOD_MP2T_QAM,
    TRAN_MOD_ILLEGAL,
};


class RtspRequestInterface
{
public:
    RtspRequestInterface(){
        Clean();
    }
    /*
    RtspRequestInterface(char* Buf, int Len): m_iBufLen(Len)
    { 
        strncpy(m_sBuffer, Buf, RTSP_REQUEST_MSG_LEN_MAX);
        m_Speed = 100;
        m_Scale = 1;
        m_RangeStartTime = -1;
        m_RangeStopTime = -1;     
        m_TransportMode = TRAN_MOD_ILLEGAL;
        m_DstIP = 0;
        m_DstTTL = 0;
        m_ReasonCode = 0;
        m_NoticeCode = 0;
        m_BandWidth = 0;  //bps
        m_QamMod = 0;
        m_StatusCode = 0;
        m_bIsRequest = true;
        m_CSeq = 0;
    }
    */
    
    
    virtual ~RtspRequestInterface(){}

    void Clean()
    {
        memset(m_sBuffer, 0, RTSP_REQUEST_MSG_LEN_MAX);
        m_iBufLen = 0;
        
        
        //char m_sFileName[RTSP_FILE_PATH_LEN_MAX];
        memset(m_sFilePath, 0, RTSP_FILE_PATH_LEN_MAX); //
        memset(m_sFullFilePath, 0, RTSP_FILE_PATH_LEN_MAX);
        
        m_ClientPortA = 0;  
        m_ClientPortB = 0; 
        
        m_RangeStartTime = -1;
        m_RangeStopTime = -1;
        
        m_Speed = 100;
        m_Scale = 1;
        m_Method = qtssIllegalMethod;
        m_SessionID = 0;
        m_CSeq = -1;
        m_ContentLength = 0;
        //memset(m_sContent, 0, RTSP_REQUEST_CONTENT_LEN_MAX);
        m_TransportMode = TRAN_MOD_ILLEGAL;
        m_DstIP = 0;
        m_DstTTL = 0;
        m_Require = "";
        
        m_bIsRequest = true;
        
        //for response
        m_StatusCode = 0;
        m_ReasonPhrase = "";
        
        //NGOD
        m_ReasonCode = 0;
        m_NoticeCode = 0;
        m_ReasonDesc = "";
        m_NoticeDesc = "";
        m_BandWidth = 0;  //bps
        m_QamMod = 0;
        m_QamName = "";
        m_Client = "";
        m_SessionGroup = "";
        m_OnDemandSessionID = "";

    }

    //parse rtsp package, Req ture:request   false:response 
    virtual int ParseRtspPackage(char Buf[], int Size) = 0; //bool bReq = true
    //read request data 
    bool IsRequest() { return m_bIsRequest; }

    U8 GetMethod(){ return m_Method; }
    U32 GetSessionID(){ return m_SessionID; }
    U32 GetCSeq() { return m_CSeq; }
    
    //will be -1 unless there was a Range header. May have one or two values
    S64 GetStartTime(){ return m_RangeStartTime;}
    S64 GetStopTime(){ return m_RangeStopTime;}
    
    // Value of Speed: header in request
    U8 GetSpeed(){ return m_Speed;}
    S8 GetScale(){ return m_Scale;}
    U64 GetPlayTimePoint(){}

    U8 GetTransportMode(){ return m_TransportMode;}
        
    // these get set if there is a transport header
    U16 GetClientPortA()    { return m_ClientPortA; }
    U16 GetClientPortB()    { return m_ClientPortB; }
    U32 GetDstIP() { return m_DstIP; }
    void SetDstIP(U32 IP) { m_DstIP = IP; }

    //virtual char* GetFileName(){}
    //virtual char* GetFileDir(){}
    virtual char* GetFilePath(){ return m_sFilePath; } //rtsp uri abs path
    //virtual char* GetFullFilePath(){};//file server full path
    //virtual int GetFileType() = 0;
    int GetContentLength() { return m_ContentLength; }
    //char* GetContent() { return m_sContent; }
    //void  SetContent(char Buf[], int Len) { strncpy(m_sContent, Buf, RTSP_REQUEST_CONTENT_LEN_MAX); }
    string GetRequire() { return m_Require; }

    //Response 
    U16 GetStatusCode() { return m_StatusCode; }
    string& GetReasonPhrase() { return m_ReasonPhrase; }

    //NGOD
    U16 GetReasonCode() { return m_ReasonCode; }
    string& GetReasonDesc() { return m_ReasonDesc; }
    U16 GetNoticeCode() { return m_NoticeCode; }
    string& GetNoticeDesc() { return m_NoticeDesc; }
    U32 GetBandWidth() { return m_BandWidth; }
    U16 GetQamMod() { return m_QamMod; }
    string& GetQamName() { return m_QamName; }
    string& GetClient() { return m_Client; }
    string& GetSessionGroup() { return m_SessionGroup; }
    string& GetOnDemandSessionId() { return m_OnDemandSessionID; }
    
    
    //package response msg
    virtual void PutRequestLine(U8 Method, const char* Uri, U8 RtspVer = 0) = 0;
    virtual void PutStatusLine(U16 RtspStatusCode, U16 RtspVersion) = 0;
    virtual void AppendCSeqHeader(U32 CSeq) = 0;
    virtual void AppendSessionHeader(U32 SessID) = 0;
    virtual void AppendTransportHeader(U16 SvrPortA, U16 SvrPortB) = 0;
    virtual void AppendUDPTransportHeader(const char* Client, const char* DestIP, U16 ClientPort, const char* EdgeInputGroup) = 0;
    virtual void AppendIPQamTransportHeader(const char* Client, const char* QamName, const char* QamGroup, U32 Frequency, U16 QamMode, U16 ProgramNumber) = 0;
    virtual void AppendRtpInfoHeader() = 0;
    virtual void AppendPublicHeader() = 0;
    virtual void AppendRequireHeader(const char* str) = 0;
    //virtual void AppendSDP(const char* sSDP, int Len) = 0;
    virtual void AppendContentType(const char* sConType) = 0;
    virtual void AppendContentLength(int Len) = 0;
    virtual int  AppendContent(const char* Buf, int Len) = 0;
    virtual void AppendCRLF() = 0;
    //ngod
    virtual void AppendNoticeHeader(U16 NoticeCode, const char* NoticeDesc) = 0;

    
    virtual char* GetResponsePacket(){ return m_sBuffer; }
    virtual int GetResponsePacketLen(){ return m_iBufLen; }
 
   #if 0 
    void AppendHeader();    
    void AppendTransportHeader();
    void AppendContentBaseHeader();
    void AppendRTPInfoHeader(); 
    void AppendContentLength();
    void AppendDateAndExpires();
    void AppendSessionHeaderWithTimeout();
    void AppendRetransmitHeader();
#endif 
    

protected:
    char  m_sBuffer[RTSP_REQUEST_MSG_LEN_MAX]; //full request msg
    int m_iBufLen;
    
    //char m_sFileName[RTSP_FILE_PATH_LEN_MAX];
    char m_sFilePath[RTSP_FILE_PATH_LEN_MAX]; //
    char m_sFullFilePath[RTSP_FILE_PATH_LEN_MAX];

    U16 m_ClientPortA;  
    U16 m_ClientPortB; 

    S64 m_RangeStartTime;
    S64 m_RangeStopTime;
    U8 m_Speed;
    S8 m_Scale; 
    U8 m_Method;
    U32 m_SessionID;
    S32 m_CSeq;
    int m_ContentLength;
    //char m_sContent[RTSP_REQUEST_CONTENT_LEN_MAX];
    U8 m_TransportMode;
    U32 m_DstIP;
    U8  m_DstTTL;
    string m_Require;

    bool m_bIsRequest;

    //for response
    U16 m_StatusCode;
    string m_ReasonPhrase;



    //NGOD
    U16 m_ReasonCode;
    U16 m_NoticeCode;
    string m_ReasonDesc;
    string m_NoticeDesc;
    U32 m_BandWidth;  //bps
    U16 m_QamMod;
    string m_QamName;
    string m_Client;
    string m_SessionGroup;
    string m_OnDemandSessionID;

};


#endif


