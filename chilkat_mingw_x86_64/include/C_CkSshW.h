// This is a generated source file for Chilkat version 10.0.0
#ifndef _C_CkSshWH
#define _C_CkSshWH
#include "chilkatDefs.h"

#include "ck_inttypes.h"
#include "Chilkat_C.h"


CK_C_VISIBLE_PUBLIC void CkSshW_setAbortCheck(HCkSshW cHandle, BOOL (*fnAbortCheck)(void));
CK_C_VISIBLE_PUBLIC void CkSshW_setPercentDone(HCkSshW cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_C_VISIBLE_PUBLIC void CkSshW_setProgressInfo(HCkSshW cHandle, void (*fnProgressInfo)(const wchar_t *name, const wchar_t *value));
CK_C_VISIBLE_PUBLIC void CkSshW_setTaskCompleted(HCkSshW cHandle, void (*fnTaskCompleted)(HCkTaskW hTask));

CK_C_VISIBLE_PUBLIC HCkSshW CkSshW_Create(void);
CK_C_VISIBLE_PUBLIC void CkSshW_Dispose(HCkSshW handle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getAbortCurrent(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putAbortCurrent(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getAuthFailReason(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getCaretControl(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putCaretControl(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getChannelOpenFailCode(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getChannelOpenFailReason(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_channelOpenFailReason(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getClientIdentifier(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putClientIdentifier(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_clientIdentifier(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getClientIpAddress(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putClientIpAddress(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_clientIpAddress(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getClientPort(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putClientPort(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getConnectTimeoutMs(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putConnectTimeoutMs(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getDebugLogFilePath(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putDebugLogFilePath(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_debugLogFilePath(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getDisconnectCode(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getDisconnectReason(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_disconnectReason(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getEnableCompression(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putEnableCompression(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getForceCipher(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putForceCipher(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_forceCipher(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getHeartbeatMs(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHeartbeatMs(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getHostKeyAlg(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHostKeyAlg(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_hostKeyAlg(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getHostKeyFingerprint(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_hostKeyFingerprint(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getHttpProxyAuthMethod(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyAuthMethod(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_httpProxyAuthMethod(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getHttpProxyDomain(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyDomain(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_httpProxyDomain(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getHttpProxyHostname(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyHostname(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_httpProxyHostname(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getHttpProxyPassword(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyPassword(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_httpProxyPassword(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getHttpProxyPort(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyPort(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getHttpProxyUsername(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putHttpProxyUsername(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_httpProxyUsername(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getIdleTimeoutMs(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putIdleTimeoutMs(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getIsConnected(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getKeepSessionLog(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putKeepSessionLog(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getLastErrorHtml(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_lastErrorHtml(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getLastErrorText(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_lastErrorText(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getLastErrorXml(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_lastErrorXml(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getLastMethodSuccess(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putLastMethodSuccess(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getMaxPacketSize(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putMaxPacketSize(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getNumOpenChannels(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getPasswordChangeRequested(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getPreferIpv6(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putPreferIpv6(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getReadTimeoutMs(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putReadTimeoutMs(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getReqExecCharset(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putReqExecCharset(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_reqExecCharset(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getServerIdentifier(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_serverIdentifier(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getSessionLog(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_sessionLog(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getSocksHostname(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSocksHostname(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_socksHostname(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getSocksPassword(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSocksPassword(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_socksPassword(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getSocksPort(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSocksPort(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getSocksUsername(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSocksUsername(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_socksUsername(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_getSocksVersion(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSocksVersion(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getSoRcvBuf(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSoRcvBuf(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkSshW_getSoSndBuf(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putSoSndBuf(HCkSshW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getStderrToStdout(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putStderrToStdout(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getStripColorCodes(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putStripColorCodes(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getTcpNoDelay(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putTcpNoDelay(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getUncommonOptions(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putUncommonOptions(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_uncommonOptions(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_getUserAuthBanner(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkSshW_putUserAuthBanner(HCkSshW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_userAuthBanner(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_getVerboseLogging(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void  CkSshW_putVerboseLogging(HCkSshW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkSshW_getVersion(HCkSshW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_version(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_AuthenticatePk(HCkSshW cHandle, const wchar_t *username, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_AuthenticatePkAsync(HCkSshW cHandle, const wchar_t *username, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_AuthenticatePw(HCkSshW cHandle, const wchar_t *login, const wchar_t *password);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_AuthenticatePwAsync(HCkSshW cHandle, const wchar_t *login, const wchar_t *password);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_AuthenticatePwPk(HCkSshW cHandle, const wchar_t *username, const wchar_t *password, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_AuthenticatePwPkAsync(HCkSshW cHandle, const wchar_t *username, const wchar_t *password, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_AuthenticateSecPw(HCkSshW cHandle, HCkSecureStringW login, HCkSecureStringW password);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_AuthenticateSecPwAsync(HCkSshW cHandle, HCkSecureStringW login, HCkSecureStringW password);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_AuthenticateSecPwPk(HCkSshW cHandle, HCkSecureStringW username, HCkSecureStringW password, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_AuthenticateSecPwPkAsync(HCkSshW cHandle, HCkSecureStringW username, HCkSecureStringW password, HCkSshKeyW privateKey);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelIsOpen(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC int CkSshW_ChannelPoll(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelPollAsync(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC int CkSshW_ChannelRead(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReadAsync(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC int CkSshW_ChannelReadAndPoll(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReadAndPollAsync(HCkSshW cHandle, int channelNum, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC int CkSshW_ChannelReadAndPoll2(HCkSshW cHandle, int channelNum, int pollTimeoutMs, int maxNumBytes);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReadAndPoll2Async(HCkSshW cHandle, int channelNum, int pollTimeoutMs, int maxNumBytes);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceivedClose(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceivedEof(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceivedExitStatus(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceiveToClose(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReceiveToCloseAsync(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceiveUntilMatch(HCkSshW cHandle, int channelNum, const wchar_t *matchPattern, const wchar_t *charset, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReceiveUntilMatchAsync(HCkSshW cHandle, int channelNum, const wchar_t *matchPattern, const wchar_t *charset, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelReceiveUntilMatchN(HCkSshW cHandle, int channelNum, HCkStringArrayW matchPatterns, const wchar_t *charset, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelReceiveUntilMatchNAsync(HCkSshW cHandle, int channelNum, HCkStringArrayW matchPatterns, const wchar_t *charset, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC void CkSshW_ChannelRelease(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelSendClose(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelSendCloseAsync(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelSendData(HCkSshW cHandle, int channelNum, HCkByteData byteData);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelSendDataAsync(HCkSshW cHandle, int channelNum, HCkByteData byteData);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelSendEof(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelSendEofAsync(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ChannelSendString(HCkSshW cHandle, int channelNum, const wchar_t *textData, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ChannelSendStringAsync(HCkSshW cHandle, int channelNum, const wchar_t *textData, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_CheckConnection(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC void CkSshW_ClearTtyModes(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_Connect(HCkSshW cHandle, const wchar_t *domainName, int port);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ConnectAsync(HCkSshW cHandle, const wchar_t *domainName, int port);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ConnectThroughSsh(HCkSshW cHandle, HCkSshW ssh, const wchar_t *hostname, int port);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ConnectThroughSshAsync(HCkSshW cHandle, HCkSshW ssh, const wchar_t *hostname, int port);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ContinueKeyboardAuth(HCkSshW cHandle, const wchar_t *response, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_continueKeyboardAuth(HCkSshW cHandle, const wchar_t *response);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ContinueKeyboardAuthAsync(HCkSshW cHandle, const wchar_t *response);
CK_C_VISIBLE_PUBLIC void CkSshW_Disconnect(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetAuthMethods(HCkSshW cHandle, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getAuthMethods(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_GetAuthMethodsAsync(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC int CkSshW_GetChannelExitStatus(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC int CkSshW_GetChannelNumber(HCkSshW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetChannelType(HCkSshW cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getChannelType(HCkSshW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetHostKeyFP(HCkSshW cHandle, const wchar_t *hashAlg, BOOL includeKeyType, BOOL includeHashName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getHostKeyFP(HCkSshW cHandle, const wchar_t *hashAlg, BOOL includeKeyType, BOOL includeHashName);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedData(HCkSshW cHandle, int channelNum, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedDataN(HCkSshW cHandle, int channelNum, int maxNumBytes, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC int CkSshW_GetReceivedNumBytes(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedStderr(HCkSshW cHandle, int channelNum, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedStderrText(HCkSshW cHandle, int channelNum, const wchar_t *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getReceivedStderrText(HCkSshW cHandle, int channelNum, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_GetReceivedTextS(HCkSshW cHandle, int channelNum, const wchar_t *substr, const wchar_t *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_getReceivedTextS(HCkSshW cHandle, int channelNum, const wchar_t *substr, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkSshW_LastJsonData(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_LoadTaskCaller(HCkSshW cHandle, HCkTaskW task);
CK_C_VISIBLE_PUBLIC int CkSshW_OpenCustomChannel(HCkSshW cHandle, const wchar_t *channelType);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_OpenCustomChannelAsync(HCkSshW cHandle, const wchar_t *channelType);
CK_C_VISIBLE_PUBLIC int CkSshW_OpenDirectTcpIpChannel(HCkSshW cHandle, const wchar_t *targetHostname, int targetPort);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_OpenDirectTcpIpChannelAsync(HCkSshW cHandle, const wchar_t *targetHostname, int targetPort);
CK_C_VISIBLE_PUBLIC int CkSshW_OpenSessionChannel(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_OpenSessionChannelAsync(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_PeekReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_peekReceivedText(HCkSshW cHandle, int channelNum, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC int CkSshW_QuickCmdCheck(HCkSshW cHandle, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_QuickCmdCheckAsync(HCkSshW cHandle, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC int CkSshW_QuickCmdSend(HCkSshW cHandle, const wchar_t *command);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_QuickCmdSendAsync(HCkSshW cHandle, const wchar_t *command);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_QuickCommand(HCkSshW cHandle, const wchar_t *command, const wchar_t *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_quickCommand(HCkSshW cHandle, const wchar_t *command, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_QuickCommandAsync(HCkSshW cHandle, const wchar_t *command, const wchar_t *charset);
CK_C_VISIBLE_PUBLIC int CkSshW_QuickShell(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_QuickShellAsync(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_ReKey(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_ReKeyAsync(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SaveLastError(HCkSshW cHandle, const wchar_t *path);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendIgnore(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendIgnoreAsync(HCkSshW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqExec(HCkSshW cHandle, int channelNum, const wchar_t *commandLine);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqExecAsync(HCkSshW cHandle, int channelNum, const wchar_t *commandLine);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqPty(HCkSshW cHandle, int channelNum, const wchar_t *termType, int widthInChars, int heightInChars, int widthInPixels, int heightInPixels);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqPtyAsync(HCkSshW cHandle, int channelNum, const wchar_t *termType, int widthInChars, int heightInChars, int widthInPixels, int heightInPixels);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqSetEnv(HCkSshW cHandle, int channelNum, const wchar_t *name, const wchar_t *value);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqSetEnvAsync(HCkSshW cHandle, int channelNum, const wchar_t *name, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqShell(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqShellAsync(HCkSshW cHandle, int channelNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqSignal(HCkSshW cHandle, int channelNum, const wchar_t *signalName);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqSignalAsync(HCkSshW cHandle, int channelNum, const wchar_t *signalName);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqSubsystem(HCkSshW cHandle, int channelNum, const wchar_t *subsystemName);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqSubsystemAsync(HCkSshW cHandle, int channelNum, const wchar_t *subsystemName);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqWindowChange(HCkSshW cHandle, int channelNum, int widthInChars, int heightInRows, int pixWidth, int pixHeight);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqWindowChangeAsync(HCkSshW cHandle, int channelNum, int widthInChars, int heightInRows, int pixWidth, int pixHeight);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqX11Forwarding(HCkSshW cHandle, int channelNum, BOOL singleConnection, const wchar_t *authProt, const wchar_t *authCookie, int screenNum);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqX11ForwardingAsync(HCkSshW cHandle, int channelNum, BOOL singleConnection, const wchar_t *authProt, const wchar_t *authCookie, int screenNum);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SendReqXonXoff(HCkSshW cHandle, int channelNum, BOOL clientCanDo);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_SendReqXonXoffAsync(HCkSshW cHandle, int channelNum, BOOL clientCanDo);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SetAllowedAlgorithms(HCkSshW cHandle, HCkJsonObjectW json);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_SetTtyMode(HCkSshW cHandle, const wchar_t *ttyName, int ttyValue);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_StartKeyboardAuth(HCkSshW cHandle, const wchar_t *login, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkSshW_startKeyboardAuth(HCkSshW cHandle, const wchar_t *login);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_StartKeyboardAuthAsync(HCkSshW cHandle, const wchar_t *login);
CK_C_VISIBLE_PUBLIC BOOL CkSshW_UnlockComponent(HCkSshW cHandle, const wchar_t *unlockCode);
CK_C_VISIBLE_PUBLIC int CkSshW_WaitForChannelMessage(HCkSshW cHandle, int pollTimeoutMs);
CK_C_VISIBLE_PUBLIC HCkTaskW CkSshW_WaitForChannelMessageAsync(HCkSshW cHandle, int pollTimeoutMs);
#endif
