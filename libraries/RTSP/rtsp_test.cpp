#include "RtspRequestInterface.h"
#include "RtspRequest.h"
#include "RTSPProtocol.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;



int test_rtsp_request()
{  
    int ret = 0;
    string str;
    string str1="OPTIONS rtsp://172.16.132.29/backkom.ts RTSP/1.0\r\n";
    string str2 = "RTSP/1.0 404 Server Not Found\r\n";
    string str3 = "CSeq: 1\r\n";
    str3 += "Require: com.comcast.ngod.s6\r\n";
    str3 += "SessionGroup: Chicago.SouthBend.SM1\r\n";
    str3 += "OnDemandSessionId: be074250cc5a11d98cd50800200c9a66\r\n";
    str3 += "User-Agent: VLC media player (LIVE555 Streaming Media v2007.02.20)\r\n";
    //str += "Transport: RTP/AVP;unicast;client_port=2132-2133;destination=10.0.0.1\r\n";
    str3 += "Transport:MP2T/DVBC/QAM;unicast;client=00AF123456DE;bandwidth=2700000;"
            "qam_name=Chicago.SouthBend.5;modulation=qam64;"
            "client_port=2132-2133;destination=10.0.0.1\r\n";
    str3 += "Range: npt=0.000-\r\n";
    str3 += "Speed: 2\r\n";
    str3 += "Scale: 2\r\n";    
    str3 += "Reason: 200 \"User stop\"\r\n";
    str3 += "Notice: 5200 \"Server Resources Unavailable\"\r\n";
    str3 += "\r\n";

    string strSDP = "v=0\r\n";
    strSDP += "o=- 1311921727086674 1 IN IP4 172.16.132.29\r\n";
    strSDP += "s=MPEG Transport Stream, streamed by the LIVE555 Media Server\r\n";

    str = str2 + str3;
    RtspRequestInterface *pRtspReq = new RtspRequest();
    ret = pRtspReq->ParseRtspPackage((char*)str.c_str(), str.length());

    printf("statuscode=%d\n", pRtspReq->GetStatusCode());
    printf("phrase=%s\n", pRtspReq->GetReasonPhrase().c_str());
    printf("pa=%d,pb=%d,dstip=%x\n", pRtspReq->GetClientPortA(), 
                            pRtspReq->GetClientPortB(),
                            pRtspReq->GetDstIP());
    printf("range start=%d,stop=%d\n", pRtspReq->GetStartTime(),pRtspReq->GetStopTime());
    printf("speed=%d,scale=%d\n", pRtspReq->GetSpeed(), pRtspReq->GetScale());
    printf("require=%s\n", pRtspReq->GetRequire().c_str());
    printf("sessiongroup=%s\n", pRtspReq->GetSessionGroup().c_str());
    printf("ODSI=%s\n", pRtspReq->GetOnDemandSessionId().c_str());
    printf("reason code=%d, desc=%s \n", pRtspReq->GetReasonCode(), pRtspReq->GetReasonDesc().c_str());

    str = str1 + str3;
    pRtspReq = new RtspRequest();
    ret = pRtspReq->ParseRtspPackage((char*)str.c_str(), str.length());

    printf("method=%s\n", RTSPProtocol::GetMethodString(pRtspReq->GetMethod()).Ptr);
    printf("filepath=%s\n", pRtspReq->GetFilePath());
    printf("pa=%d,pb=%d,dstip=%x\n", pRtspReq->GetClientPortA(), 
                            pRtspReq->GetClientPortB(),
                            pRtspReq->GetDstIP());
    printf("range start=%d,stop=%d\n", pRtspReq->GetStartTime(),pRtspReq->GetStopTime());
    printf("speed=%d,scale=%d\n", pRtspReq->GetSpeed(), pRtspReq->GetScale());
    printf("require=%s\n", pRtspReq->GetRequire().c_str());
    printf("sessiongroup=%s\n", pRtspReq->GetSessionGroup().c_str());
    printf("ODSI=%s\n", pRtspReq->GetOnDemandSessionId().c_str());
    printf("reason code=%d, desc=%s \n", pRtspReq->GetReasonCode(), pRtspReq->GetReasonDesc().c_str());
    
    
    pRtspReq->PutStatusLine(ngodEdgeDeviceNotAvailable, 0);
    pRtspReq->AppendCSeqHeader(100);
    pRtspReq->AppendPublicHeader();
    pRtspReq->AppendSessionHeader(10001);
    pRtspReq->AppendIPQamTransportHeader("1010Client", "QamNameA", "QamGroupA", 474000, 1024, 0x30);
    pRtspReq->AppendUDPTransportHeader("1010Client", "10.0.0.1", 1024, "test_edge_group");
    pRtspReq->AppendNoticeHeader( RTSPProtocol::GetAnnounceCode(ngodErrorReadingContentData), RTSPProtocol::GetAnnounceCodeString(ngodErrorReadingContentData).Ptr);
    //pRtspReq->AppendSDP(strSDP.c_str(), strSDP.length());
    pRtspReq->AppendContentType("application/sdp");
    pRtspReq->AppendContentLength(strSDP.length());
    pRtspReq->AppendCRLF();
    pRtspReq->AppendContent(strSDP.c_str(), strSDP.length());

    printf("Len=%d %d \n%s", pRtspReq->GetResponsePacketLen(),
        strlen(pRtspReq->GetResponsePacket()),
        pRtspReq->GetResponsePacket());

    pRtspReq->PutRequestLine(qtssAnnounceMethod, "rtsp://127.0.0.1");
    pRtspReq->AppendPublicHeader();
    pRtspReq->AppendSessionHeader(10001);
    pRtspReq->AppendIPQamTransportHeader("1010Client", "QamNameA", "QamGroupA", 474000, 1024, 0x30);
    pRtspReq->AppendUDPTransportHeader("1010Client", "10.0.0.1", 1024, "test_edge_group");
    pRtspReq->AppendNoticeHeader( 5010, "Notice description");
    pRtspReq->AppendCRLF();
    printf("Len=%d %d \n%s", pRtspReq->GetResponsePacketLen(),
        strlen(pRtspReq->GetResponsePacket()),
        pRtspReq->GetResponsePacket());


    return 0;
}


int main(int argc, char**argv)
{
    test_rtsp_request();
    return 0;
}





