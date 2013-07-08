#include "arduino.h"

#ifndef rtsp_protocol_h
#include "rtsp_protocol.h"
#endif
 
	prog_char rtsp_methods_RTSP_METHOD_DESCRIBE		[]	PROGMEM = "DESCRIBE";
	prog_char rtsp_methods_RTSP_METHOD_SETUP		[]	PROGMEM = "SETUP";
	prog_char rtsp_methods_RTSP_METHOD_TEARDOWN		[]	PROGMEM = "TEARDOWN";
	prog_char rtsp_methods_RTSP_METHOD_PLAY			[]	PROGMEM = "PLAY";
	prog_char rtsp_methods_RTSP_METHOD_PAUSE		[]	PROGMEM = "PAUSE";
	prog_char rtsp_methods_RTSP_METHOD_OPTIONS		[]	PROGMEM = "OPTIONS";
	prog_char rtsp_methods_RTSP_METHOD_Announce    	[]	PROGMEM = "ANNOUNCE";
	prog_char rtsp_methods_RTSP_METHOD_GetParameter	[]	PROGMEM = "GET_PARAMETER";
	prog_char rtsp_methods_RTSP_METHOD_SetParameter	[]	PROGMEM = "SET_PARAMETER";
	prog_char rtsp_methods_RTSP_METHOD_Redirect    	[]	PROGMEM = "REDIRECT";
	prog_char rtsp_methods_RTSP_METHOD_Record      	[]	PROGMEM = "RECORD";	
	
	PROGMEM const char *rtsp_methods_table[] = 	   // change "string_table" name to suit
	{   
		rtsp_methods_RTSP_METHOD_DESCRIBE		,	
		rtsp_methods_RTSP_METHOD_SETUP			,	
		rtsp_methods_RTSP_METHOD_TEARDOWN		,
		rtsp_methods_RTSP_METHOD_PLAY			,
		rtsp_methods_RTSP_METHOD_PAUSE			,
		rtsp_methods_RTSP_METHOD_OPTIONS		,
		rtsp_methods_RTSP_METHOD_Announce    	,
		rtsp_methods_RTSP_METHOD_GetParameter	,
		rtsp_methods_RTSP_METHOD_SetParameter	,
		rtsp_methods_RTSP_METHOD_Redirect    	,
		rtsp_methods_RTSP_METHOD_Record      		
	};

	prog_char rtsp_headers_RTSP_HEADER_Accept    [] PROGMEM = "Accept";
	prog_char rtsp_headers_RTSP_HEADER_CSeq      [] PROGMEM = "Cseq";
	prog_char rtsp_headers_RTSP_HEADER_UserAgent [] PROGMEM = "User-Agent";
	prog_char rtsp_headers_RTSP_HEADER_Transport [] PROGMEM = "Transport";
	prog_char rtsp_headers_RTSP_HEADER_Session   [] PROGMEM = "Session";
	prog_char rtsp_headers_RTSP_HEADER_Range     [] PROGMEM = "Range";
					
	/*prog_char rtsp_headers_RTSP_HEADER_AcceptEncoding    [] PROGMEM = "Accept-Encoding";
	prog_char rtsp_headers_RTSP_HEADER_AcceptLanguage    [] PROGMEM = "Accept-Language";
	prog_char rtsp_headers_RTSP_HEADER_Authorization     [] PROGMEM = "Authorization";
	prog_char rtsp_headers_RTSP_HEADER_Bandwidth         [] PROGMEM = "Bandwidth";
	prog_char rtsp_headers_RTSP_HEADER_BlockSize         [] PROGMEM = "Blocksize";
	prog_char rtsp_headers_RTSP_HEADER_CacheControl      [] PROGMEM = "Cache-Control";
	prog_char rtsp_headers_RTSP_HEADER_Conference        [] PROGMEM = "Conference";
	prog_char rtsp_headers_RTSP_HEADER_Connection        [] PROGMEM = "Connection";
	prog_char rtsp_headers_RTSP_HEADER_ContentBase       [] PROGMEM = "Content-Base";
	prog_char rtsp_headers_RTSP_HEADER_ContentEncoding   [] PROGMEM = "Content-Encoding";
	prog_char rtsp_headers_RTSP_HEADER_ContentLanguage   [] PROGMEM = "Content-Language";
	prog_char rtsp_headers_RTSP_HEADER_ContentLength     [] PROGMEM = "Content-length";
	prog_char rtsp_headers_RTSP_HEADER_ContentLocation   [] PROGMEM = "Content-Location";
	prog_char rtsp_headers_RTSP_HEADER_ContentType       [] PROGMEM = "Content-Type";
	prog_char rtsp_headers_RTSP_HEADER_Date              [] PROGMEM = "Date";
	prog_char rtsp_headers_RTSP_HEADER_Expires           [] PROGMEM = "Expires";
	prog_char rtsp_headers_RTSP_HEADER_From              [] PROGMEM = "From";
	prog_char rtsp_headers_RTSP_HEADER_Host              [] PROGMEM = "Host";
	prog_char rtsp_headers_RTSP_HEADER_IfMatch           [] PROGMEM = "If-Match";
	prog_char rtsp_headers_RTSP_HEADER_IfModifiedSince   [] PROGMEM = "If-Modified-Since";
	prog_char rtsp_headers_RTSP_HEADER_LastModified      [] PROGMEM = "Last-Modified";
	prog_char rtsp_headers_RTSP_HEADER_Location          [] PROGMEM = "Location";
	prog_char rtsp_headers_RTSP_HEADER_ProxyAuthenticate [] PROGMEM = "Proxy-Authenticate";
	prog_char rtsp_headers_RTSP_HEADER_ProxyRequire      [] PROGMEM = "Proxy-Require";
	prog_char rtsp_headers_RTSP_HEADER_Referer           [] PROGMEM = "Referer";
	prog_char rtsp_headers_RTSP_HEADER_RetryAfter        [] PROGMEM = "Retry-After";
	prog_char rtsp_headers_RTSP_HEADER_Require           [] PROGMEM = "Require";
	prog_char rtsp_headers_RTSP_HEADER_RTPInfo           [] PROGMEM = "RTP-Info";
	prog_char rtsp_headers_RTSP_HEADER_Scale             [] PROGMEM = "Scale";
	prog_char rtsp_headers_RTSP_HEADER_Speed             [] PROGMEM = "Speed";
	prog_char rtsp_headers_RTSP_HEADER_Timestamp         [] PROGMEM = "Timestamp";
	prog_char rtsp_headers_RTSP_HEADER_Vary              [] PROGMEM = "Vary";
	prog_char rtsp_headers_RTSP_HEADER_Via               [] PROGMEM = "Via";
	prog_char rtsp_headers_RTSP_HEADER_Allow             [] PROGMEM = "Allow";
	prog_char rtsp_headers_RTSP_HEADER_Public            [] PROGMEM = "Public";
	prog_char rtsp_headers_RTSP_HEADER_Server            [] PROGMEM = "Server";
	prog_char rtsp_headers_RTSP_HEADER_Unsupported       [] PROGMEM = "Unsupported";
	prog_char rtsp_headers_RTSP_HEADER_WWWAuthenticate   [] PROGMEM = "WWW-Authenticate";
	
	// NGOD             
	prog_char rtsp_headers_RTSP_HEADER_XRetransmit       [] PROGMEM = "x-Retransmit";
	prog_char rtsp_headers_RTSP_HEADER_XAcceptRetransmit [] PROGMEM = "x-Accept-Retransmit";
	prog_char rtsp_headers_RTSP_HEADER_XRTPMetaInfo      [] PROGMEM = "x-RTP-Meta-Info";
	prog_char rtsp_headers_RTSP_HEADER_XTransportOptions [] PROGMEM = "x-Transport-Options";
	prog_char rtsp_headers_RTSP_HEADER_XPacketRange      [] PROGMEM = "x-Packet-Range";
	prog_char rtsp_headers_RTSP_HEADER_XPreBuffer        [] PROGMEM = "x-Prebuffer";
	prog_char rtsp_headers_RTSP_HEADER_XDynamicRate      [] PROGMEM = "x-Dynamic-Rate";
	prog_char rtsp_headers_RTSP_HEADER_XAcceptDynamicRate[] PROGMEM = "x-Accept-Dynamic-Rate";
	// DJM PROTOTYPE
	prog_char rtsp_headers_RTSP_HEADER_XRandomDataSize[] PROGMEM = "x-Random-Data-Size";
	
	//3gpp release 6 headers
	prog_char rtsp_headers_RTSP_HEADER_3GPPLinkChar    [] PROGMEM = "3GPP-Link-Char";
	prog_char rtsp_headers_RTSP_HEADER_3GPPAdaptation  [] PROGMEM = "3GPP-Adaptation";
	prog_char rtsp_headers_RTSP_HEADER_3GPPQOEFeedback [] PROGMEM = "3GPP-QoE-Feedback";
	prog_char rtsp_headers_RTSP_HEADER_3GPPQOEMetrics  [] PROGMEM = "3GPP-QoE-Metrics";
	
	//Annex G
	prog_char rtsp_headers_RTSP_HEADER_XPreDecBufSize          [] PROGMEM = "x-predecbufsize";
	prog_char rtsp_headers_RTSP_HEADER_XInitPredecBufPeriod    [] PROGMEM = "x-initpredecbufperiod";
	prog_char rtsp_headers_RTSP_HEADER_XInitPostDecBufPeriod   [] PROGMEM = "x-initpostdecbufperiod";
	prog_char rtsp_headers_RTSP_HEADER_3GPPVideoPostDecBufSize [] PROGMEM = "3gpp-videopostdecbufsize";
	
	//NGOD
	prog_char rtsp_headers_RTSP_HEADER_ngodNotice            [] PROGMEM = "Notice";
	prog_char rtsp_headers_RTSP_HEADER_ngodSessionGroup	  [] PROGMEM = "SessionGroup";
	prog_char rtsp_headers_RTSP_HEADER_ngodReason            [] PROGMEM = "Reason";
	prog_char rtsp_headers_RTSP_HEADER_ngodOnDemandSessionId [] PROGMEM = "OnDemandSessionId";*/

	PROGMEM const char *rtsp_headers_table[] = 	   // change "string_table" name to suit
	{   
		rtsp_headers_RTSP_HEADER_Accept    , 
		rtsp_headers_RTSP_HEADER_CSeq      , 
		rtsp_headers_RTSP_HEADER_UserAgent , 
		rtsp_headers_RTSP_HEADER_Transport , 
		rtsp_headers_RTSP_HEADER_Session   , 
		rtsp_headers_RTSP_HEADER_Range     };
/*				
		rtsp_headers_RTSP_HEADER_AcceptEncoding    , 	
		rtsp_headers_RTSP_HEADER_AcceptLanguage    , 	
		rtsp_headers_RTSP_HEADER_Authorization     , 	
		rtsp_headers_RTSP_HEADER_Bandwidth         , 	
		rtsp_headers_RTSP_HEADER_BlockSize         , 	
		rtsp_headers_RTSP_HEADER_CacheControl      , 	
		rtsp_headers_RTSP_HEADER_Conference        , 	
		rtsp_headers_RTSP_HEADER_Connection        , 	
		rtsp_headers_RTSP_HEADER_ContentBase       , 	
		rtsp_headers_RTSP_HEADER_ContentEncoding   , 	
		rtsp_headers_RTSP_HEADER_ContentLanguage   , 	
		rtsp_headers_RTSP_HEADER_ContentLength     , 	
		rtsp_headers_RTSP_HEADER_ContentLocation   , 	
		rtsp_headers_RTSP_HEADER_ContentType       , 	
		rtsp_headers_RTSP_HEADER_Date              , 	
		rtsp_headers_RTSP_HEADER_Expires           , 	
		rtsp_headers_RTSP_HEADER_From              , 	
		rtsp_headers_RTSP_HEADER_Host              , 	
		rtsp_headers_RTSP_HEADER_IfMatch           , 	
		rtsp_headers_RTSP_HEADER_IfModifiedSince   , 	
		rtsp_headers_RTSP_HEADER_LastModified      , 	
		rtsp_headers_RTSP_HEADER_Location          , 	
		rtsp_headers_RTSP_HEADER_ProxyAuthenticate , 	
		rtsp_headers_RTSP_HEADER_ProxyRequire      , 	
		rtsp_headers_RTSP_HEADER_Referer           , 	
		rtsp_headers_RTSP_HEADER_RetryAfter        , 	
		rtsp_headers_RTSP_HEADER_Require           , 	
		rtsp_headers_RTSP_HEADER_RTPInfo           , 	
		rtsp_headers_RTSP_HEADER_Scale             , 	
		rtsp_headers_RTSP_HEADER_Speed             , 	
		rtsp_headers_RTSP_HEADER_Timestamp         , 	
		rtsp_headers_RTSP_HEADER_Vary              , 	
		rtsp_headers_RTSP_HEADER_Via               , 	
		rtsp_headers_RTSP_HEADER_Allow             , 	
		rtsp_headers_RTSP_HEADER_Public            , 	
		rtsp_headers_RTSP_HEADER_Server            , 	
		rtsp_headers_RTSP_HEADER_Unsupported       , 	
		rtsp_headers_RTSP_HEADER_WWWAuthenticate   , 	
			
					
		rtsp_headers_RTSP_HEADER_XRetransmit       , 	
		rtsp_headers_RTSP_HEADER_XAcceptRetransmit , 	
		rtsp_headers_RTSP_HEADER_XRTPMetaInfo      , 	
		rtsp_headers_RTSP_HEADER_XTransportOptions , 	
		rtsp_headers_RTSP_HEADER_XPacketRange      , 	
		rtsp_headers_RTSP_HEADER_XPreBuffer        , 	
		rtsp_headers_RTSP_HEADER_XDynamicRate      , 	
		rtsp_headers_RTSP_HEADER_XAcceptDynamicRate, 	
			
		rtsp_headers_RTSP_HEADER_XRandomDataSize, 
			
		rtsp_headers_RTSP_HEADER_3GPPLinkChar    , 	
		rtsp_headers_RTSP_HEADER_3GPPAdaptation  , 	
		rtsp_headers_RTSP_HEADER_3GPPQOEFeedback , 	
		rtsp_headers_RTSP_HEADER_3GPPQOEMetrics  , 	
			
			
		rtsp_headers_RTSP_HEADER_XPreDecBufSize       	,
		rtsp_headers_RTSP_HEADER_XInitPredecBufPeriod 	,
		rtsp_headers_RTSP_HEADER_XInitPostDecBufPeriod	,
		rtsp_headers_RTSP_HEADER_3GPPVideoPostDecBufSize	,
			
			
		rtsp_headers_RTSP_HEADER_ngodNotice           	,
		rtsp_headers_RTSP_HEADER_ngodSessionGroup	  ,	
		rtsp_headers_RTSP_HEADER_ngodReason           	,
		rtsp_headers_RTSP_HEADER_ngodOnDemandSessionId	
	};*/
	
	prog_char sStatusCodeStrings_TSP_STATUS_Continue                       [] PROGMEM = "Continue";                              //kContinue
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessOK                      [] PROGMEM = "OK";                                    //kSuccessOK
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessCreated                 [] PROGMEM = "Created";                               //kSuccessCreated
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessAccepted                [] PROGMEM = "Accepted";                              //kSuccessAccepted
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessNoContent               [] PROGMEM = "No Content";                            //kSuccessNoContent
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessPartialContent          [] PROGMEM = "Partial Content";                       //kSuccessPartialContent
	prog_char sStatusCodeStrings_TSP_STATUS_SuccessLowOnStorage            [] PROGMEM = "Low on Storage Space";                  //kSuccessLowOnStorage
	prog_char sStatusCodeStrings_TSP_STATUS_MultipleChoices                [] PROGMEM = "Multiple Choices";                      //kMultipleChoices
	prog_char sStatusCodeStrings_TSP_STATUS_RedirectPermMoved              [] PROGMEM = "Moved Permanently";                     //kRedirectPermMoved
	prog_char sStatusCodeStrings_TSP_STATUS_RedirectTempMoved              [] PROGMEM = "Found";                                 //kRedirectTempMoved
	prog_char sStatusCodeStrings_TSP_STATUS_RedirectSeeOther               [] PROGMEM = "See Other";                             //kRedirectSeeOther
	prog_char sStatusCodeStrings_TSP_STATUS_RedirectNotModified            [] PROGMEM = "Not Modified";                          //kRedirectNotModified
	prog_char sStatusCodeStrings_TSP_STATUS_UseProxy                       [] PROGMEM = "Use Proxy";                             //kUseProxy

	prog_char sStatusCodeStrings_TSP_STATUS_ClientBadRequest               [] PROGMEM = "Bad Request";                           //kClientBadRequest
	prog_char sStatusCodeStrings_TSP_STATUS_ClientUnAuthorized             [] PROGMEM = "Unauthorized";                          //kClientUnAuthorized
	prog_char sStatusCodeStrings_TSP_STATUS_PaymentRequired                [] PROGMEM = "Payment Required";                      //kPaymentRequired
	prog_char sStatusCodeStrings_TSP_STATUS_ClientForbidden                [] PROGMEM = "Forbidden";                             //kClientForbidden
	prog_char sStatusCodeStrings_TSP_STATUS_ClientNotFound                 [] PROGMEM = "Not Found";                             //kClientNotFound
	prog_char sStatusCodeStrings_TSP_STATUS_ClientMethodNotAllowed         [] PROGMEM = "Method Not Allowed";                    //kClientMethodNotAllowed
	prog_char sStatusCodeStrings_TSP_STATUS_NotAcceptable                  [] PROGMEM = "Not Acceptable";                        //kNotAcceptable
	prog_char sStatusCodeStrings_TSP_STATUS_ProxyAuthenticationRequired    [] PROGMEM = "Proxy Authentication Required";         //kProxyAuthenticationRequired
	prog_char sStatusCodeStrings_TSP_STATUS_RequestTimeout                 [] PROGMEM = "Request Time-out";                      //kRequestTimeout
	prog_char sStatusCodeStrings_TSP_STATUS_ClientConflict                 [] PROGMEM = "Conflict";                              //kClientConflict
	prog_char sStatusCodeStrings_TSP_STATUS_Gone                           [] PROGMEM = "Gone";                                  //kGone
	prog_char sStatusCodeStrings_TSP_STATUS_LengthRequired                 [] PROGMEM = "Length Required";                       //kLengthRequired
	prog_char sStatusCodeStrings_TSP_STATUS_PreconditionFailed             [] PROGMEM = "Precondition Failed";                   //kPreconditionFailed
	prog_char sStatusCodeStrings_TSP_STATUS_RequestEntityTooLarge          [] PROGMEM = "Request Entity Too Large";              //kRequestEntityTooLarge
	prog_char sStatusCodeStrings_TSP_STATUS_RequestURITooLarge             [] PROGMEM = "Request-URI Too Large";                 //kRequestURITooLarge
	prog_char sStatusCodeStrings_TSP_STATUS_UnsupportedMediaType           [] PROGMEM = "Unsupported Media Type";                //kUnsupportedMediaType
	prog_char sStatusCodeStrings_TSP_STATUS_ClientParameterNotUnderstood   [] PROGMEM = "Parameter Not Understood";              //kClientParameterNotUnderstood
	prog_char sStatusCodeStrings_TSP_STATUS_ClientConferenceNotFound       [] PROGMEM = "Conference Not Found";                  //kClientConferenceNotFound
	prog_char sStatusCodeStrings_TSP_STATUS_ClientNotEnoughBandwidth       [] PROGMEM = "Not Enough Bandwidth";                  //kClientNotEnoughBandwidth
	prog_char sStatusCodeStrings_TSP_STATUS_ClientSessionNotFound          [] PROGMEM = "Session Not Found";                     //kClientSessionNotFound
	prog_char sStatusCodeStrings_TSP_STATUS_ClientMethodNotValidInState    [] PROGMEM = "Method Not Valid in this State";        //kClientMethodNotValidInState
	prog_char sStatusCodeStrings_TSP_STATUS_ClientHeaderFieldNotValid      [] PROGMEM = "Header Field Not Valid For Resource";   //kClientHeaderFieldNotValid
	prog_char sStatusCodeStrings_TSP_STATUS_ClientInvalidRange             [] PROGMEM = "Invalid Range";                         //kClientInvalidRange
	prog_char sStatusCodeStrings_TSP_STATUS_ClientReadOnlyParameter        [] PROGMEM = "Parameter Is Read-Only";                //kClientReadOnlyParameter
	prog_char sStatusCodeStrings_TSP_STATUS_ClientAggregateOptionNotAllowed[] PROGMEM = "Aggregate Option Not Allowed";          //kClientAggregateOptionNotAllowed
	prog_char sStatusCodeStrings_TSP_STATUS_ClientAggregateOptionAllowed   [] PROGMEM = "Only Aggregate Option Allowed";         //kClientAggregateOptionAllowed
	prog_char sStatusCodeStrings_TSP_STATUS_ClientUnsupportedTransport     [] PROGMEM = "Unsupported Transport";                 //kClientUnsupportedTransport
	prog_char sStatusCodeStrings_TSP_STATUS_ClientDestinationUnreachable   [] PROGMEM = "Destination Unreachable";               //kClientDestinationUnreachable
	prog_char sStatusCodeStrings_TSP_STATUS_ServerInternal                 [] PROGMEM = "Internal Server Error";                 //kServerInternal
	prog_char sStatusCodeStrings_TSP_STATUS_ServerNotImplemented           [] PROGMEM = "Not Implemented";                       //kServerNotImplemented
	prog_char sStatusCodeStrings_TSP_STATUS_ServerBadGateway               [] PROGMEM = "Bad Gateway";                           //kServerBadGateway
	prog_char sStatusCodeStrings_TSP_STATUS_ServerUnavailable              [] PROGMEM = "Service Unavailable";                   //kServerUnavailable
	prog_char sStatusCodeStrings_TSP_STATUS_ServerGatewayTimeout           [] PROGMEM = "Gateway Timeout";                       //kServerGatewayTimeout
	prog_char sStatusCodeStrings_TSP_STATUS_RTSPVersionNotSupported        [] PROGMEM = "RTSP Version not supported";            //kRTSPVersionNotSupported
	prog_char sStatusCodeStrings_TSP_STATUS_ServerOptionNotSupported       [] PROGMEM = "Option Not Supported";                   //kServerOptionNotSupported
	//NGOD             
	prog_char sStatusCodeStrings_TSP_STATUS_InvalidRequest                 [] PROGMEM = "Setup Failed C Invalid Request";
	prog_char sStatusCodeStrings_TSP_STATUS_QAMBandwidthNotAvailable       [] PROGMEM = "Setup Failed C QAM Bandwidth Not Available";
	prog_char sStatusCodeStrings_TSP_STATUS_NetworkBandwidthNotAvailable   [] PROGMEM = "Setup Failed C Network Bandwidth Not Available";
	prog_char sStatusCodeStrings_TSP_STATUS_ProgramNotAvailable            [] PROGMEM = "Setup Failed C Program Not Available";
	prog_char sStatusCodeStrings_TSP_STATUS_ServiceGroupNotFound           [] PROGMEM = "Setup Failed C Service Group Not Found";
	prog_char sStatusCodeStrings_TSP_STATUS_QAMGroupsNotFound              [] PROGMEM = "Setup Failed C QAM Groups Not Found";
	prog_char sStatusCodeStrings_TSP_STATUS_QAMNotAvailable                [] PROGMEM = "Setup Failed C QAM Not Available";
	prog_char sStatusCodeStrings_TSP_STATUS_EdgeDeviceNotAvailable         [] PROGMEM = "Setup Failed -  Edge Device Not Availables";

	PROGMEM const char *rtsp_statusCodeStrings_table[] = 	   // change "string_table" name to suit
	{   
	 sStatusCodeStrings_TSP_STATUS_Continue                       ,
	 sStatusCodeStrings_TSP_STATUS_SuccessOK                      ,
	 sStatusCodeStrings_TSP_STATUS_SuccessCreated                 ,
	 sStatusCodeStrings_TSP_STATUS_SuccessAccepted                ,
	 sStatusCodeStrings_TSP_STATUS_SuccessNoContent               ,
	 sStatusCodeStrings_TSP_STATUS_SuccessPartialContent          ,
	 sStatusCodeStrings_TSP_STATUS_SuccessLowOnStorage            ,
	 sStatusCodeStrings_TSP_STATUS_MultipleChoices                ,
	 sStatusCodeStrings_TSP_STATUS_RedirectPermMoved              ,
	 sStatusCodeStrings_TSP_STATUS_RedirectTempMoved              ,
	 sStatusCodeStrings_TSP_STATUS_RedirectSeeOther               ,
	 sStatusCodeStrings_TSP_STATUS_RedirectNotModified            ,
	 sStatusCodeStrings_TSP_STATUS_UseProxy                       ,

	 sStatusCodeStrings_TSP_STATUS_ClientBadRequest               ,
	 sStatusCodeStrings_TSP_STATUS_ClientUnAuthorized             ,
	 sStatusCodeStrings_TSP_STATUS_PaymentRequired                ,
	 sStatusCodeStrings_TSP_STATUS_ClientForbidden                ,
	 sStatusCodeStrings_TSP_STATUS_ClientNotFound                 ,
	 sStatusCodeStrings_TSP_STATUS_ClientMethodNotAllowed         ,
	 sStatusCodeStrings_TSP_STATUS_NotAcceptable                  ,
	 sStatusCodeStrings_TSP_STATUS_ProxyAuthenticationRequired    ,
	 sStatusCodeStrings_TSP_STATUS_RequestTimeout                 ,
	 sStatusCodeStrings_TSP_STATUS_ClientConflict                 ,
	 sStatusCodeStrings_TSP_STATUS_Gone                           ,
	 sStatusCodeStrings_TSP_STATUS_LengthRequired                 ,
	 sStatusCodeStrings_TSP_STATUS_PreconditionFailed             ,
	 sStatusCodeStrings_TSP_STATUS_RequestEntityTooLarge          ,
	 sStatusCodeStrings_TSP_STATUS_RequestURITooLarge             ,
	 sStatusCodeStrings_TSP_STATUS_UnsupportedMediaType           ,
	 sStatusCodeStrings_TSP_STATUS_ClientParameterNotUnderstood   ,
	 sStatusCodeStrings_TSP_STATUS_ClientConferenceNotFound       ,
	 sStatusCodeStrings_TSP_STATUS_ClientNotEnoughBandwidth       ,
	 sStatusCodeStrings_TSP_STATUS_ClientSessionNotFound          ,
	 sStatusCodeStrings_TSP_STATUS_ClientMethodNotValidInState    ,
	 sStatusCodeStrings_TSP_STATUS_ClientHeaderFieldNotValid      ,
	 sStatusCodeStrings_TSP_STATUS_ClientInvalidRange             ,
	 sStatusCodeStrings_TSP_STATUS_ClientReadOnlyParameter        ,
	 sStatusCodeStrings_TSP_STATUS_ClientAggregateOptionNotAllowed,
	 sStatusCodeStrings_TSP_STATUS_ClientAggregateOptionAllowed   ,
	 sStatusCodeStrings_TSP_STATUS_ClientUnsupportedTransport     ,
	 sStatusCodeStrings_TSP_STATUS_ClientDestinationUnreachable   ,
	 sStatusCodeStrings_TSP_STATUS_ServerInternal                 ,
	 sStatusCodeStrings_TSP_STATUS_ServerNotImplemented           ,
	 sStatusCodeStrings_TSP_STATUS_ServerBadGateway               ,
	 sStatusCodeStrings_TSP_STATUS_ServerUnavailable              ,
	 sStatusCodeStrings_TSP_STATUS_ServerGatewayTimeout           ,
	 sStatusCodeStrings_TSP_STATUS_RTSPVersionNotSupported        ,
	 sStatusCodeStrings_TSP_STATUS_ServerOptionNotSupported       ,
	//NGOD             
	 sStatusCodeStrings_TSP_STATUS_InvalidRequest                 ,
	 sStatusCodeStrings_TSP_STATUS_QAMBandwidthNotAvailable       ,
	 sStatusCodeStrings_TSP_STATUS_NetworkBandwidthNotAvailable   ,
	 sStatusCodeStrings_TSP_STATUS_ProgramNotAvailable            ,
	 sStatusCodeStrings_TSP_STATUS_ServiceGroupNotFound           ,
	 sStatusCodeStrings_TSP_STATUS_QAMGroupsNotFound              ,
	 sStatusCodeStrings_TSP_STATUS_QAMNotAvailable                ,
	 sStatusCodeStrings_TSP_STATUS_EdgeDeviceNotAvailable         };
	
	prog_char sStatusCodeAsStrings_RTSP_STATUS_Continue                       [] PROGMEM = "100";       //kContinue
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessOK                      [] PROGMEM = "200";       //kSuccessOK
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessCreated                 [] PROGMEM = "201";       //kSuccessCreated
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessAccepted                [] PROGMEM = "202";       //kSuccessAccepted
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessNoContent               [] PROGMEM = "204";       //kSuccessNoContent
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessPartialContent          [] PROGMEM = "206";       //kSuccessPartialContent
	prog_char sStatusCodeAsStrings_RTSP_STATUS_SuccessLowOnStorage            [] PROGMEM = "250";       //kSuccessLowOnStorage
	prog_char sStatusCodeAsStrings_RTSP_STATUS_MultipleChoices                [] PROGMEM = "300";       //kMultipleChoices
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RedirectPermMoved              [] PROGMEM = "301";       //kRedirectPermMoved
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RedirectTempMoved              [] PROGMEM = "302";       //kRedirectTempMoved
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RedirectSeeOther               [] PROGMEM = "303";       //kRedirectSeeOther
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RedirectNotModified            [] PROGMEM = "304";       //kRedirectNotModified
	prog_char sStatusCodeAsStrings_RTSP_STATUS_UseProxy                       [] PROGMEM = "305";       //kUseProxy
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientBadRequest               [] PROGMEM = "400";       //kClientBadRequest
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientUnAuthorized             [] PROGMEM = "401";       //kClientUnAuthorized
	prog_char sStatusCodeAsStrings_RTSP_STATUS_PaymentRequired                [] PROGMEM = "402";       //kPaymentRequired
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientForbidden                [] PROGMEM = "403";       //kClientForbidden
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientNotFound                 [] PROGMEM = "404";       //kClientNotFound
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientMethodNotAllowed         [] PROGMEM = "405";       //kClientMethodNotAllowed
	prog_char sStatusCodeAsStrings_RTSP_STATUS_NotAcceptable                  [] PROGMEM = "406";       //kNotAcceptable
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ProxyAuthenticationRequired    [] PROGMEM = "407";       //kProxyAuthenticationRequired
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RequestTimeout                 [] PROGMEM = "408";       //kRequestTimeout
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientConflict                 [] PROGMEM = "409";       //kClientConflict
	prog_char sStatusCodeAsStrings_RTSP_STATUS_Gone                           [] PROGMEM = "410";       //kGone
	prog_char sStatusCodeAsStrings_RTSP_STATUS_LengthRequired                 [] PROGMEM = "411";       //kLengthRequired
	prog_char sStatusCodeAsStrings_RTSP_STATUS_PreconditionFailed             [] PROGMEM = "412";       //kPreconditionFailed
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RequestEntityTooLarge          [] PROGMEM = "413";       //kRequestEntityTooLarge
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RequestURITooLarge             [] PROGMEM = "414";       //kRequestURITooLarge
	prog_char sStatusCodeAsStrings_RTSP_STATUS_UnsupportedMediaType           [] PROGMEM = "415";       //kUnsupportedMediaType
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientParameterNotUnderstood   [] PROGMEM = "451";       //kClientParameterNotUnderstood
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientConferenceNotFound       [] PROGMEM = "452";       //kClientConferenceNotFound
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientNotEnoughBandwidth       [] PROGMEM = "453";       //kClientNotEnoughBandwidth
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientSessionNotFound          [] PROGMEM = "454";       //kClientSessionNotFound
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientMethodNotValidInState    [] PROGMEM = "455";       //kClientMethodNotValidInState
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientHeaderFieldNotValid      [] PROGMEM = "456";       //kClientHeaderFieldNotValid
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientInvalidRange             [] PROGMEM = "457";       //kClientInvalidRange
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientReadOnlyParameter        [] PROGMEM = "458";       //kClientReadOnlyParameter
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientAggregateOptionNotAllowed[] PROGMEM = "459";       //kClientAggregateOptionNotAllowed
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientAggregateOptionAllowed   [] PROGMEM = "460";       //kClientAggregateOptionAllowed
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientUnsupportedTransport     [] PROGMEM = "461";       //kClientUnsupportedTransport
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ClientDestinationUnreachable   [] PROGMEM = "462";       //kClientDestinationUnreachable
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerInternal                 [] PROGMEM = "500";       //kServerInternal
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerNotImplemented           [] PROGMEM = "501";       //kServerNotImplemented
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerBadGateway               [] PROGMEM = "502";       //kServerBadGateway
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerUnavailable              [] PROGMEM = "503";       //kServerUnavailable
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerGatewayTimeout           [] PROGMEM = "504";       //kServerGatewayTimeout
	prog_char sStatusCodeAsStrings_RTSP_STATUS_RTSPVersionNotSupported        [] PROGMEM = "505";       //kRTSPVersionNotSupported
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServerOptionNotSupported       [] PROGMEM = "551";       //kServerOptionNotSupported
		//NGOD           
	prog_char sStatusCodeAsStrings_RTSP_STATUS_InvalidRequest                 [] PROGMEM = "671"; //URM Setup Failed 每 Invalid Request
	prog_char sStatusCodeAsStrings_RTSP_STATUS_QAMBandwidthNotAvailable       [] PROGMEM = "672"; // URM Setup Failed 每 QAM Bandwidth Not Available
	prog_char sStatusCodeAsStrings_RTSP_STATUS_NetworkBandwidthNotAvailable   [] PROGMEM = "673"; // URM Setup Failed 每 Network Bandwidth Not Available
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ProgramNotAvailable            [] PROGMEM = "674"; // URM Setup Failed 每 Program Not Available
	prog_char sStatusCodeAsStrings_RTSP_STATUS_ServiceGroupNotFound           [] PROGMEM = "675"; // URM Setup Failed 每 Service Group Not Found
	prog_char sStatusCodeAsStrings_RTSP_STATUS_QAMGroupsNotFound              [] PROGMEM = "676"; // URM Setup Failed 每 QAM Groups Not Found
	prog_char sStatusCodeAsStrings_RTSP_STATUS_QAMNotAvailable                [] PROGMEM = "677"; // URM Setup Failed 每 QAM Not Available
	prog_char sStatusCodeAsStrings_RTSP_STATUS_EdgeDeviceNotAvailable         [] PROGMEM = "678";

	PROGMEM const char *rtsp_statusCodeAsStrings_table[] = 	   // change "string_table" name to suit
	{   
	 sStatusCodeAsStrings_RTSP_STATUS_Continue                       ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessOK                      ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessCreated                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessAccepted                ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessNoContent               ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessPartialContent          ,
	 sStatusCodeAsStrings_RTSP_STATUS_SuccessLowOnStorage            ,
	 sStatusCodeAsStrings_RTSP_STATUS_MultipleChoices                ,
	 sStatusCodeAsStrings_RTSP_STATUS_RedirectPermMoved              ,
	 sStatusCodeAsStrings_RTSP_STATUS_RedirectTempMoved              ,
	 sStatusCodeAsStrings_RTSP_STATUS_RedirectSeeOther               ,
	 sStatusCodeAsStrings_RTSP_STATUS_RedirectNotModified            ,
	 sStatusCodeAsStrings_RTSP_STATUS_UseProxy                       ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientBadRequest               ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientUnAuthorized             ,
	 sStatusCodeAsStrings_RTSP_STATUS_PaymentRequired                ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientForbidden                ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientNotFound                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientMethodNotAllowed         ,
	 sStatusCodeAsStrings_RTSP_STATUS_NotAcceptable                  ,
	 sStatusCodeAsStrings_RTSP_STATUS_ProxyAuthenticationRequired    ,
	 sStatusCodeAsStrings_RTSP_STATUS_RequestTimeout                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientConflict                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_Gone                           ,
	 sStatusCodeAsStrings_RTSP_STATUS_LengthRequired                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_PreconditionFailed             ,
	 sStatusCodeAsStrings_RTSP_STATUS_RequestEntityTooLarge          ,
	 sStatusCodeAsStrings_RTSP_STATUS_RequestURITooLarge             ,
	 sStatusCodeAsStrings_RTSP_STATUS_UnsupportedMediaType           ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientParameterNotUnderstood   ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientConferenceNotFound       ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientNotEnoughBandwidth       ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientSessionNotFound          ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientMethodNotValidInState    ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientHeaderFieldNotValid      ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientInvalidRange             ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientReadOnlyParameter        ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientAggregateOptionNotAllowed,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientAggregateOptionAllowed   ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientUnsupportedTransport     ,
	 sStatusCodeAsStrings_RTSP_STATUS_ClientDestinationUnreachable   ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerInternal                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerNotImplemented           ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerBadGateway               ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerUnavailable              ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerGatewayTimeout           ,
	 sStatusCodeAsStrings_RTSP_STATUS_RTSPVersionNotSupported        ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServerOptionNotSupported       ,

	 sStatusCodeAsStrings_RTSP_STATUS_InvalidRequest                 ,
	 sStatusCodeAsStrings_RTSP_STATUS_QAMBandwidthNotAvailable       ,
	 sStatusCodeAsStrings_RTSP_STATUS_NetworkBandwidthNotAvailable   ,
	 sStatusCodeAsStrings_RTSP_STATUS_ProgramNotAvailable            ,
	 sStatusCodeAsStrings_RTSP_STATUS_ServiceGroupNotFound           ,
	 sStatusCodeAsStrings_RTSP_STATUS_QAMGroupsNotFound              ,
	 sStatusCodeAsStrings_RTSP_STATUS_QAMNotAvailable                ,
	 sStatusCodeAsStrings_RTSP_STATUS_EdgeDeviceNotAvailable         };
	
	PROGMEM  prog_uint16_t statusCodes[] = {
		100,        //kContinue
	    200,        //kSuccessOK
	    201,        //kSuccessCreated
	    202,        //kSuccessAccepted
	    204,        //kSuccessNoContent
	    206,        //kSuccessPartialContent
	    250,        //kSuccessLowOnStorage
	    300,        //kMultipleChoices
	    301,        //kRedirectPermMoved
	    302,        //kRedirectTempMoved
	    303,        //kRedirectSeeOther
	    304,        //kRedirectNotModified
	    305,        //kUseProxy
	    400,        //kClientBadRequest
	    401,        //kClientUnAuthorized
	    402,        //kPaymentRequired
	    403,        //kClientForbidden
	    404,        //kClientNotFound
	    405,        //kClientMethodNotAllowed
	    406,        //kNotAcceptable
	    407,        //kProxyAuthenticationRequired
	    408,        //kRequestTimeout
	    409,        //kClientConflict
	    410,        //kGone
	    411,        //kLengthRequired
	    412,        //kPreconditionFailed
	    413,        //kRequestEntityTooLarge
	    414,        //kRequestURITooLarge
	    415,        //kUnsupportedMediaType
	    451,        //kClientParameterNotUnderstood
	    452,        //kClientConferenceNotFound
	    453,        //kClientNotEnoughBandwidth
	    454,        //kClientSessionNotFound
	    455,        //kClientMethodNotValidInState
	    456,        //kClientHeaderFieldNotValid
	    457,        //kClientInvalidRange
	    458,        //kClientReadOnlyParameter
	    459,        //kClientAggregateOptionNotAllowed
	    460,        //kClientAggregateOptionAllowed
	    461,        //kClientUnsupportedTransport
	    462,        //kClientDestinationUnreachable
	    500,        //kServerInternal
	    501,        //kServerNotImplemented
	    502,        //kServerBadGateway
	    503,        //kServerUnavailable
	    504,        //kServerGatewayTimeout
	    505,        //kRTSPVersionNotSupported
	    551,         //kServerOptionNotSupported
	    
	    671, //URM Setup Failed 每 Invalid Request
	    672, // URM Setup Failed 每 QAM Bandwidth Not Available
	    673, // URM Setup Failed 每 Network Bandwidth Not Available
	    674, // URM Setup Failed 每 Program Not Available
	    675, // URM Setup Failed 每 Service Group Not Found
	    676, // URM Setup Failed 每 QAM Groups Not Found
	    677, // URM Setup Failed 每 QAM Not Available
	    678  // URM Setup Failed 坼 Edge Device Not Available    
	};
	
	char* sVersionString;
	
	//Constructor Implementation
rtsp_protocol::rtsp_protocol() {

	sVersionString =	"RTSP/1.0";


	/*
	//NGOD announce code
	sAnnounceCodeStrings[] = 
	{
		"End of Stream Reached";            // 2101
		"Start of Stream Reached";          //2104
		"Error Reading Content Data";       //4400
		"Server Resources Unavailable";     //5200
		"Downstream Failure";               //5401
		"Client Session Terminated";        //5402
		"Internal Server Error";            //5502
		"Inband Stream Marker Mismatch";    // 5601
		"Session In Progress"              //5700
	};

	int sAnnounceCodes[] = 
	{
		2101; // End of Stream Reached
		2104; // Start of Stream Reached
		4400; // Error Reading Content Data
		5200; // Server Resources Unavailable
		5401; // Downstream Failure
		5402; // Client Session Terminated
		5502; // Internal Server Error
		5601; // Inband Stream Marker Mismatch
		5700 //Session In Progress
	};

	sAnnounceCodeAsStrings[] =
	{
		"2101"; // End of Stream Reached
		"2104"; // Start of Stream Reached
		"4400"; // Error Reading Content Data
		"5200"; // Server Resources Unavailable
		"5401"; // Downstream Failure
		"5402"; // Client Session Terminated
		"5502"; // Internal Server Error
		"5601"; // Inband Stream Marker Mismatch
		"5700"  // Session In Progress

	};*/

}

char* rtsp_protocol::getMethod(int method)
{
	char buffer[50];

    strcpy_P(buffer, (char*)pgm_read_word(&(rtsp_methods_table[method]))); // Necessary casts and dereferencing, just copy. 
	return buffer;
}

char* rtsp_protocol::getHeader(int header)
{
	char buffer[50];

    strcpy_P(buffer, (char*)pgm_read_word(&(rtsp_headers_table[header]))); // Necessary casts and dereferencing, just copy. 
	return buffer;
}

char* rtsp_protocol::getStatusCodeString(int statusCode)
{
	char buffer[100];

    strcpy_P(buffer, (char*)pgm_read_word(&(rtsp_statusCodeStrings_table[statusCode]))); // Necessary casts and dereferencing, just copy. 
	return buffer;
}

char* rtsp_protocol::getStatusCodeAsString(int statusCode)
{
	char buffer[50];

    strcpy_P(buffer, (char*)pgm_read_word(&(rtsp_statusCodeAsStrings_table[statusCode]))); // Necessary casts and dereferencing, just copy. 
	return buffer;
}

int rtsp_protocol::getStatusCode(int statusCode)
{
	int readValue;
	readValue = pgm_read_word_near(statusCodes + statusCode);
	return readValue;
}

char* rtsp_protocol::getVersionString()
{
	return sVersionString;
}
