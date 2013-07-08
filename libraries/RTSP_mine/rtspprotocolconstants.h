/*
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Copyright (c 1999-2008 Apple Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'. You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 *
 */
/*
    File:       QTSSRTSPProtocol.h

    Contains:   Constant & Enum definitions for RTSP protocol type parts
                of QTSS API.

    
*/



#ifndef RTSPPROTOCOL_CONSTANTS_H
#define RTSPPROTOCOL_CONSTANTS_H

#define RTSP_HEADER_COUNT 10
#define RTSP_STATUSCODE_COUNT						 10
#define RTSP_ANNOUNCECODE_COUNT 						9		


#define RTSP_METHOD_DESCRIBE		0
#define RTSP_METHOD_SETUP			1
#define RTSP_METHOD_TEARDOWN		2
#define RTSP_METHOD_PLAY			3
#define RTSP_METHOD_PAUSE			4
#define RTSP_METHOD_OPTIONS			5
#define RTSP_METHOD_Announce       	6
#define RTSP_METHOD_GetParameter   	7
#define RTSP_METHOD_SetParameter   	8
#define RTSP_METHOD_Redirect       	9
#define RTSP_METHOD_Record         	10

#define RTSP_METHOD_COUNT 			11
#define RTSP_METHOD_Illegal         11


#define RTSP_MAX_RESPONSE_SIZE	500
    

//These are the common request s (optimized)
#define RTSP_HEADER_Accept             0
#define RTSP_HEADER_CSeq               1
#define RTSP_HEADER_UserAgent          2
#define RTSP_HEADER_Transport          3
#define RTSP_HEADER_Session            4
#define RTSP_HEADER_Range              5
#define RTSP_HEADER_NumVIPs            6

//Other request s
#define RTSP_HEADER_AcceptEncoding     6
#define RTSP_HEADER_AcceptLanguage     7
#define RTSP_HEADER_Authorization      8        
#define RTSP_HEADER_Bandwidth          9
#define RTSP_HEADER_BlockSize          10
#define RTSP_HEADER_CacheControl       11
#define RTSP_HEADER_Conference         12       
#define RTSP_HEADER_Connection         13
#define RTSP_HEADER_ContentBase        14
#define RTSP_HEADER_ContentEncoding    15
#define RTSP_HEADER_ContentLanguage    16
#define RTSP_HEADER_ContentLength      17
#define RTSP_HEADER_ContentLocation    18
#define RTSP_HEADER_ContentType        19
#define RTSP_HEADER_Date               20
#define RTSP_HEADER_Expires            21
#define RTSP_HEADER_From               22
#define RTSP_HEADER_Host               23
#define RTSP_HEADER_IfMatch            24
#define RTSP_HEADER_IfModifiedSince    25
#define RTSP_HEADER_LastModified       26
#define RTSP_HEADER_Location           27
#define RTSP_HEADER_ProxyAuthenticate  28
#define RTSP_HEADER_ProxyRequire       29
#define RTSP_HEADER_Referer            30
#define RTSP_HEADER_RetryAfter         31
#define RTSP_HEADER_Require            32
#define RTSP_HEADER_RTPInfo            33
#define RTSP_HEADER_Scale              34
#define RTSP_HEADER_Speed              35
#define RTSP_HEADER_Timestamp          36
#define RTSP_HEADER_Vary               37
#define RTSP_HEADER_Via                38
#define RTSP_HEADER_NumRequests        39

//Additional response s
#define RTSP_HEADER_Allow              39
#define RTSP_HEADER_Public             40
#define RTSP_HEADER_Server             41
#define RTSP_HEADER_Unsupported        42
#define RTSP_HEADER_WWWAuthenticate    43
#define RTSP_HEADER_SameAsLast         44

//Newly added s
#define RTSP_HEADER_Extensions         45

#define RTSP_HEADER_XRetransmit        45
#define RTSP_HEADER_XAcceptRetransmit  46
#define RTSP_HEADER_XRTPMetaInfo       47
#define RTSP_HEADER_XTransportOptions  48
#define RTSP_HEADER_XPacketRange       49
#define RTSP_HEADER_XPreBuffer         50
#define RTSP_HEADER_XDynamicRate       51
#define RTSP_HEADER_XAcceptDynamicRate 52

// QT Player random data request
#define RTSP_HEADER_XRandomDataSize    		53

// 3gpp release 6
#define RTSP_HEADER_3GPPLinkChar       		54
#define RTSP_HEADER_3GPPAdaptation     		55
#define RTSP_HEADER_3GPPQOEFeedback         56
#define RTSP_HEADER_3GPPQOEMetrics          57

// 3gpp annex g
#define RTSP_HEADER_XPreDecBufSize          58
#define RTSP_HEADER_XInitPredecBufPeriod    59
#define RTSP_HEADER_XInitPostDecBufPeriod   60
#define RTSP_HEADER_3GPPVideoPostDecBufSize 61

//ngod
#define RTSP_HEADER_ngodNotice              62
#define RTSP_HEADER_ngodSessionGroup	    63
#define RTSP_HEADER_ngodReason             	64
#define RTSP_HEADER_ngodOnDemandSessionId  	65

#define RTSP_HEADER_Nums				 	66 //62
#define RTSP_HEADER_Illegal 			 	66  //62

#define RTSP_HEADER_COUNT 67

//typedef int QTSS_RTSPMethod;
//typedef int QTSS_RTSPHeader;

#define RTSP_STATUS_Continue                         0        //100
#define RTSP_STATUS_SuccessOK                        1        //200
#define RTSP_STATUS_SuccessCreated                   2        //201
#define RTSP_STATUS_SuccessAccepted                  3        //202
#define RTSP_STATUS_SuccessNoContent                 4        //203
#define RTSP_STATUS_SuccessPartialContent            5        //204
#define RTSP_STATUS_SuccessLowOnStorage              6        //250
#define RTSP_STATUS_MultipleChoices                  7        //300
#define RTSP_STATUS_RedirectPermMoved                8        //301
#define RTSP_STATUS_RedirectTempMoved                9        //302
#define RTSP_STATUS_RedirectSeeOther                 10       //303
#define RTSP_STATUS_RedirectNotModified              11       //304
#define RTSP_STATUS_UseProxy                         12       //305
#define RTSP_STATUS_ClientBadRequest                 13       //400
#define RTSP_STATUS_ClientUnAuthorized               14       //401
#define RTSP_STATUS_PaymentRequired                  15       //402
#define RTSP_STATUS_ClientForbidden                  16       //403
#define RTSP_STATUS_ClientNotFound                   17       //404
#define RTSP_STATUS_ClientMethodNotAllowed           18       //405
#define RTSP_STATUS_NotAcceptable                    19       //406
#define RTSP_STATUS_ProxyAuthenticationRequired      20       //407
#define RTSP_STATUS_RequestTimeout                   21       //408
#define RTSP_STATUS_ClientConflict                   22       //409
#define RTSP_STATUS_Gone                             23       //410
#define RTSP_STATUS_LengthRequired                   24       //411
#define RTSP_STATUS_PreconditionFailed               25       //412
#define RTSP_STATUS_RequestEntityTooLarge            26       //413
#define RTSP_STATUS_RequestURITooLarge               27       //414
#define RTSP_STATUS_UnsupportedMediaType             28       //415
#define RTSP_STATUS_ClientParameterNotUnderstood     29       //451
#define RTSP_STATUS_ClientConferenceNotFound         30       //452
#define RTSP_STATUS_ClientNotEnoughBandwidth         31       //453
#define RTSP_STATUS_ClientSessionNotFound            32       //454
#define RTSP_STATUS_ClientMethodNotValidInState      33       //455
#define RTSP_STATUS_ClientHeaderFieldNotValid        34       //456
#define RTSP_STATUS_ClientInvalidRange               35       //457
#define RTSP_STATUS_ClientReadOnlyParameter          36       //458
#define RTSP_STATUS_ClientAggregateOptionNotAllowed  37       //459
#define RTSP_STATUS_ClientAggregateOptionAllowed     38       //460
#define RTSP_STATUS_ClientUnsupportedTransport       39       //461
#define RTSP_STATUS_ClientDestinationUnreachable     40       //462
#define RTSP_STATUS_ServerInternal                   41       //500
#define RTSP_STATUS_ServerNotImplemented             42       //501
#define RTSP_STATUS_ServerBadGateway                 43       //502
#define RTSP_STATUS_ServerUnavailable                44       //503
#define RTSP_STATUS_ServerGatewayTimeout             45       //504
#define RTSP_STATUS_RTSPVersionNotSupported          46       //505
#define RTSP_STATUS_ServerOptionNotSupported         47       //551
//ngod
#define RTSP_STATUS_InvalidRequest                   48       //671
#define RTSP_STATUS_QAMBandwidthNotAvailable         49       //672
#define RTSP_STATUS_NetworkBandwidthNotAvailable     50       //673
#define RTSP_STATUS_ProgramNotAvailable              51       //674
#define RTSP_STATUS_ServiceGroupNotFound             52       //675
#define RTSP_STATUS_QAMGroupsNotFound                53       //676
#define RTSP_STATUS_QAMNotAvailable                  54       //677
#define RTSP_STATUS_EdgeDeviceNotAvailable           55       //678
#define RTSP_STATUSCODE_COUNT						 56



// Announce Codes
#define RTSP_ANNOUNCECODE_EndofStreamReached			0
#define RTSP_ANNOUNCECODE_StartofStreamReached			1
#define RTSP_ANNOUNCECODE_ErrorReadingContentData		2
#define RTSP_ANNOUNCECODE_ServerResourcesUnavailable	3
#define RTSP_ANNOUNCECODE_DownstreamFailure				4
#define RTSP_ANNOUNCECODE_ClientSessionTerminated		5
#define RTSP_ANNOUNCECODE_InternalServerError			6
#define RTSP_ANNOUNCECODE_InbandStreamMarkerMismatch	7
#define RTSP_ANNOUNCECODE_SessionInProgress				8
#define RTSP_ANNOUNCECODE_COUNT 						9		


#endif
