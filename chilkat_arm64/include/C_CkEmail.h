// This is a generated source file for Chilkat version 10.0.0
#ifndef _C_CkEmail_H
#define _C_CkEmail_H
#include "chilkatDefs.h"
#include "ck_inttypes.h"
#include "Chilkat_C.h"


CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_Create(void);
CK_C_VISIBLE_PUBLIC void CkEmail_Dispose(HCkEmail handle);
CK_C_VISIBLE_PUBLIC void CkEmail_getBody(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putBody(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_body(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getBounceAddress(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putBounceAddress(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_bounceAddress(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getCharset(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putCharset(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_charset(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getDebugLogFilePath(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putDebugLogFilePath(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_debugLogFilePath(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getDecrypted(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getEmailDate(HCkEmail cHandle, SYSTEMTIME * retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putEmailDate(HCkEmail cHandle, SYSTEMTIME *newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getEmailDateStr(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putEmailDateStr(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_emailDateStr(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getEncryptedBy(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_encryptedBy(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getFileDistList(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putFileDistList(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_fileDistList(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getFrom(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putFrom(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_from(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getFromAddress(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putFromAddress(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_fromAddress(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getFromName(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putFromName(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_fromName(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getHeader(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_header(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getLanguage(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_language(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getLastErrorHtml(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_lastErrorHtml(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getLastErrorText(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_lastErrorText(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getLastErrorXml(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_lastErrorXml(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getLastMethodSuccess(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putLastMethodSuccess(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getLocalDate(HCkEmail cHandle, SYSTEMTIME * retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putLocalDate(HCkEmail cHandle, SYSTEMTIME *newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getLocalDateStr(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putLocalDateStr(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_localDateStr(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getMailer(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putMailer(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_mailer(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumAlternatives(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumAttachedMessages(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumAttachments(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumBcc(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumCC(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumDaysOld(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumDigests(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumHeaderFields(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumRelatedItems(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumReplacePatterns(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumReports(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getNumTo(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getOaepHash(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putOaepHash(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_oaepHash(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getOaepMgfHash(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putOaepMgfHash(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_oaepMgfHash(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getOaepPadding(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putOaepPadding(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getOverwriteExisting(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putOverwriteExisting(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getPkcs7CryptAlg(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putPkcs7CryptAlg(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_pkcs7CryptAlg(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getPkcs7KeyLength(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putPkcs7KeyLength(HCkEmail cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getPreferredCharset(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putPreferredCharset(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_preferredCharset(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getPrependHeaders(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putPrependHeaders(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getReceivedEncrypted(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getReceivedSigned(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getReplyTo(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putReplyTo(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_replyTo(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getReturnReceipt(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putReturnReceipt(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getSendEncrypted(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putSendEncrypted(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getSender(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putSender(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_sender(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getSendSigned(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putSendSigned(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getSignaturesValid(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getSignedBy(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_signedBy(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getSigningAlg(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putSigningAlg(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_signingAlg(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getSigningHashAlg(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putSigningHashAlg(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_signingHashAlg(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC int CkEmail_getSize(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getSubject(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putSubject(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_subject(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getUidl(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_uidl(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_getUncommonOptions(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void CkEmail_putUncommonOptions(HCkEmail cHandle, const char *newVal);
CK_C_VISIBLE_PUBLIC const char *CkEmail_uncommonOptions(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getUnpackUseRelPaths(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putUnpackUseRelPaths(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getUtf8(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putUtf8(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_getVerboseLogging(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_putVerboseLogging(HCkEmail cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkEmail_getVersion(HCkEmail cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const char *CkEmail_version(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddAttachmentBd(HCkEmail cHandle, const char *filename, HCkBinData binData, const char *contentType);
CK_C_VISIBLE_PUBLIC void CkEmail_AddAttachmentHeader(HCkEmail cHandle, int index, const char *fieldName, const char *fieldValue);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddBcc(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddCC(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddDataAttachment(HCkEmail cHandle, const char *fileName, HCkByteData content);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddDataAttachment2(HCkEmail cHandle, const char *fileName, HCkByteData content, const char *contentType);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddEncryptCert(HCkEmail cHandle, HCkCert cert);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddFileAttachment(HCkEmail cHandle, const char *path, HCkString outStrContentType);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addFileAttachment(HCkEmail cHandle, const char *path);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddFileAttachment2(HCkEmail cHandle, const char *path, const char *contentType);
CK_C_VISIBLE_PUBLIC void CkEmail_AddHeaderField(HCkEmail cHandle, const char *fieldName, const char *fieldValue);
CK_C_VISIBLE_PUBLIC void CkEmail_AddHeaderField2(HCkEmail cHandle, const char *fieldName, const char *fieldValue);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddHtmlAlternativeBody(HCkEmail cHandle, const char *body);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddiCalendarAlternativeBody(HCkEmail cHandle, const char *icalContent, const char *methodName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddMultipleBcc(HCkEmail cHandle, const char *commaSeparatedAddresses);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddMultipleCC(HCkEmail cHandle, const char *commaSeparatedAddresses);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddMultipleTo(HCkEmail cHandle, const char *commaSeparatedAddresses);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddPfxSourceData(HCkEmail cHandle, HCkByteData pfxBytes, const char *pfxPassword);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddPfxSourceFile(HCkEmail cHandle, const char *pfxFilePath, const char *pfxPassword);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddPlainTextAlternativeBody(HCkEmail cHandle, const char *body);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedBd(HCkEmail cHandle, const char *filename, HCkBinData binData, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addRelatedBd(HCkEmail cHandle, const char *filename, HCkBinData binData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedBd2(HCkEmail cHandle, HCkBinData binData, const char *fileNameInHtml);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedData(HCkEmail cHandle, const char *fileName, HCkByteData inData, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addRelatedData(HCkEmail cHandle, const char *fileName, HCkByteData inData);
CK_C_VISIBLE_PUBLIC void CkEmail_AddRelatedData2(HCkEmail cHandle, HCkByteData inData, const char *fileNameInHtml);
#if !defined(CHILKAT_MONO)
CK_C_VISIBLE_PUBLIC void CkEmail_AddRelatedData2P(HCkEmail cHandle, const unsigned char *pBytes, unsigned long szBytes, const char *fileNameInHtml);
#endif
#if !defined(CHILKAT_MONO)
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedDataP(HCkEmail cHandle, const char *nameInHtml, const unsigned char *pBytes, unsigned long szBytes, HCkString outStrContentId);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addRelatedDataP(HCkEmail cHandle, const char *nameInHtml, const unsigned char *pBytes, unsigned long szBytes);
#endif
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedFile(HCkEmail cHandle, const char *path, HCkString outStrContentID);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addRelatedFile(HCkEmail cHandle, const char *path);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedFile2(HCkEmail cHandle, const char *filenameOnDisk, const char *filenameInHtml);
CK_C_VISIBLE_PUBLIC void CkEmail_AddRelatedHeader(HCkEmail cHandle, int index, const char *fieldName, const char *fieldValue);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddRelatedString(HCkEmail cHandle, const char *nameInHtml, const char *str, const char *charset, HCkString outCid);
CK_C_VISIBLE_PUBLIC const char *CkEmail_addRelatedString(HCkEmail cHandle, const char *nameInHtml, const char *str, const char *charset);
CK_C_VISIBLE_PUBLIC void CkEmail_AddRelatedString2(HCkEmail cHandle, const char *fileNameInHtml, const char *content, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddStringAttachment(HCkEmail cHandle, const char *path, const char *content);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddStringAttachment2(HCkEmail cHandle, const char *path, const char *content, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AddTo(HCkEmail cHandle, const char *friendlyName, const char *emailAddress);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AesDecrypt(HCkEmail cHandle, const char *password);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AesEncrypt(HCkEmail cHandle, const char *password);
CK_C_VISIBLE_PUBLIC void CkEmail_AppendToBody(HCkEmail cHandle, const char *str);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_ApplyFixups(HCkEmail cHandle, const char *fixups);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AspUnpack(HCkEmail cHandle, const char *prefix, const char *saveDir, const char *urlPath, BOOL cleanFiles);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AspUnpack2(HCkEmail cHandle, const char *prefix, const char *saveDir, const char *urlPath, BOOL cleanFiles, HCkByteData outHtml);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AttachEmail(HCkEmail cHandle, HCkEmail email);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_AttachMessage(HCkEmail cHandle, HCkByteData mimeBytes);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_BEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset, HCkString outEncodedStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_bEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_BEncodeString(HCkEmail cHandle, const char *str, const char *charset, HCkString outEncodedStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_bEncodeString(HCkEmail cHandle, const char *str, const char *charset);
CK_C_VISIBLE_PUBLIC void CkEmail_Clear(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_ClearBcc(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_ClearCC(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_ClearEncryptCerts(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_ClearTo(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_Clone(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_ComputeGlobalKey(HCkEmail cHandle, const char *encoding, BOOL bFold, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_computeGlobalKey(HCkEmail cHandle, const char *encoding, BOOL bFold);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_ComputeGlobalKey2(HCkEmail cHandle, const char *encoding, BOOL bFold, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_computeGlobalKey2(HCkEmail cHandle, const char *encoding, BOOL bFold);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_ConvertInlineImages(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_CreateDsn(HCkEmail cHandle, const char *humanReadableMessage, const char *xmlStatusFields, BOOL bHeaderOnly);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_CreateForward(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_CreateMdn(HCkEmail cHandle, const char *humanReadableMessage, const char *xmlStatusFields, BOOL bHeaderOnly);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_CreateReply(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_CreateTempMht(HCkEmail cHandle, const char *inFilename, HCkString outPath);
CK_C_VISIBLE_PUBLIC const char *CkEmail_createTempMht(HCkEmail cHandle, const char *inFilename);
CK_C_VISIBLE_PUBLIC void CkEmail_DropAttachments(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_DropRelatedItem(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC void CkEmail_DropRelatedItems(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_DropSingleAttachment(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkCert CkEmail_FindIssuer(HCkEmail cHandle, HCkCert cert);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GenerateFilename(HCkEmail cHandle, HCkString outStrFilename);
CK_C_VISIBLE_PUBLIC const char *CkEmail_generateFilename(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAlternativeBody(HCkEmail cHandle, int index, HCkString outStrBody);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAlternativeBody(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAlternativeBodyBd(HCkEmail cHandle, int index, HCkBinData binData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAlternativeBodyByContentType(HCkEmail cHandle, const char *contentType, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAlternativeBodyByContentType(HCkEmail cHandle, const char *contentType);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAlternativeContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAlternativeContentType(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAltHeaderField(HCkEmail cHandle, int index, const char *fieldName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAltHeaderField(HCkEmail cHandle, int index, const char *fieldName);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_GetAttachedMessage(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachedMessageAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachedMessageAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachedMessageFilename(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachedMessageFilename(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentBd(HCkEmail cHandle, int index, HCkBinData binData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentContentID(HCkEmail cHandle, int index, HCkString outStrContentID);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentContentID(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentContentType(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentData(HCkEmail cHandle, int index, HCkByteData outData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentFilename(HCkEmail cHandle, int index, HCkString outStrFilename);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentFilename(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentHeader(HCkEmail cHandle, int attachIndex, const char *fieldName, HCkString outFieldValue);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentHeader(HCkEmail cHandle, int attachIndex, const char *fieldName);
CK_C_VISIBLE_PUBLIC int CkEmail_GetAttachmentSize(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentString(HCkEmail cHandle, int index, const char *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentString(HCkEmail cHandle, int index, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetAttachmentStringCrLf(HCkEmail cHandle, int index, const char *charset, HCkString outStrData);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getAttachmentStringCrLf(HCkEmail cHandle, int index, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetBcc(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getBcc(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetBccAddr(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getBccAddr(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetBccName(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getBccName(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetCC(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getCC(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetCcAddr(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getCcAddr(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetCcName(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getCcName(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetDeliveryStatusInfo(HCkEmail cHandle, const char *fieldName, HCkString outFieldValue);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getDeliveryStatusInfo(HCkEmail cHandle, const char *fieldName);
CK_C_VISIBLE_PUBLIC HCkEmail CkEmail_GetDigest(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkStringArray CkEmail_GetDsnFinalRecipients(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkDateTime CkEmail_GetDt(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkCert CkEmail_GetEncryptCert(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkCert CkEmail_GetEncryptedByCert(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetFileContent(HCkEmail cHandle, const char *path, HCkByteData outData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetHeaderField(HCkEmail cHandle, const char *fieldName, HCkString outStrFieldData);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getHeaderField(HCkEmail cHandle, const char *fieldName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetHeaderFieldName(HCkEmail cHandle, int index, HCkString outStrFieldName);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getHeaderFieldName(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetHeaderFieldValue(HCkEmail cHandle, int index, HCkString outStrFieldValue);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getHeaderFieldValue(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetHtmlBody(HCkEmail cHandle, HCkString outStrBody);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getHtmlBody(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC unsigned long CkEmail_GetImapUid(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkStringArray CkEmail_GetLinkedDomains(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMbHeaderField(HCkEmail cHandle, const char *fieldName, const char *charset, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMbHtmlBody(HCkEmail cHandle, const char *charset, HCkByteData outData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMbPlainTextBody(HCkEmail cHandle, const char *charset, HCkByteData outData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMime(HCkEmail cHandle, HCkString outStrMime);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getMime(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMimeBd(HCkEmail cHandle, HCkBinData bindat);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMimeBinary(HCkEmail cHandle, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetMimeSb(HCkEmail cHandle, HCkStringBuilder sb);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetNthBinaryPartOfType(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments, HCkByteData outBytes);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetNthBinaryPartOfTypeBd(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments, HCkBinData bd);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetNthContentType(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getNthContentType(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetNthTextPartOfType(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getNthTextPartOfType(HCkEmail cHandle, int index, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments);
CK_C_VISIBLE_PUBLIC int CkEmail_GetNumPartsOfType(HCkEmail cHandle, const char *contentType, BOOL inlineOnly, BOOL excludeAttachments);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetPlainTextBody(HCkEmail cHandle, HCkString outStrBody);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getPlainTextBody(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedAttr(HCkEmail cHandle, int index, const char *fieldName, const char *attrName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedContentID(HCkEmail cHandle, int index, HCkString outStrContentID);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedContentID(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedContentLocation(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedContentLocation(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedContentType(HCkEmail cHandle, int index, HCkString outStrContentType);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedContentType(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedData(HCkEmail cHandle, int index, HCkByteData outBuffer);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedFilename(HCkEmail cHandle, int index, HCkString outStrFilename);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedFilename(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedHeader(HCkEmail cHandle, int index, const char *fieldName, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedHeader(HCkEmail cHandle, int index, const char *fieldName);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedString(HCkEmail cHandle, int index, const char *charset, HCkString outStrData);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedString(HCkEmail cHandle, int index, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetRelatedStringCrLf(HCkEmail cHandle, int index, const char *charset, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getRelatedStringCrLf(HCkEmail cHandle, int index, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetReplacePattern(HCkEmail cHandle, int index, HCkString outStrPattern);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getReplacePattern(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetReplaceString(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getReplaceString(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetReplaceString2(HCkEmail cHandle, const char *pattern, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getReplaceString2(HCkEmail cHandle, const char *pattern);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetReport(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getReport(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkCert CkEmail_GetSignedByCert(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkCertChain CkEmail_GetSignedByCertChain(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC HCkCert CkEmail_GetSigningCert(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetTo(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getTo(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetToAddr(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getToAddr(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetToName(HCkEmail cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getToName(HCkEmail cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_GetXml(HCkEmail cHandle, HCkString outStrXml);
CK_C_VISIBLE_PUBLIC const char *CkEmail_getXml(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_HasHeaderMatching(HCkEmail cHandle, const char *fieldName, const char *valuePattern, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_HasHtmlBody(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_HasPlainTextBody(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_IsMultipartReport(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_LoadEml(HCkEmail cHandle, const char *mimePath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_LoadTaskResult(HCkEmail cHandle, HCkTask task);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_LoadXml(HCkEmail cHandle, const char *xmlPath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_LoadXmlString(HCkEmail cHandle, const char *xmlStr);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_QEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset, HCkString outEncodedStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_qEncodeBytes(HCkEmail cHandle, HCkByteData inData, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_QEncodeString(HCkEmail cHandle, const char *str, const char *charset, HCkString outEncodedStr);
CK_C_VISIBLE_PUBLIC const char *CkEmail_qEncodeString(HCkEmail cHandle, const char *str, const char *charset);
CK_C_VISIBLE_PUBLIC void CkEmail_RemoveAttachedMessage(HCkEmail cHandle, int idx);
CK_C_VISIBLE_PUBLIC void CkEmail_RemoveAttachedMessages(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_RemoveAttachmentPaths(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_RemoveHeaderField(HCkEmail cHandle, const char *fieldName);
CK_C_VISIBLE_PUBLIC void CkEmail_RemoveHtmlAlternative(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC void CkEmail_RemovePlainTextAlternative(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveAllAttachments(HCkEmail cHandle, const char *dirPath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveAttachedFile(HCkEmail cHandle, int index, const char *dirPath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveEml(HCkEmail cHandle, const char *emlFilePath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveLastError(HCkEmail cHandle, const char *path);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveRelatedItem(HCkEmail cHandle, int index, const char *dirPath);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SaveXml(HCkEmail cHandle, const char *path);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetAttachmentCharset(HCkEmail cHandle, int index, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetAttachmentDisposition(HCkEmail cHandle, int index, const char *disposition);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetAttachmentFilename(HCkEmail cHandle, int index, const char *filename);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetBinaryBody(HCkEmail cHandle, HCkByteData byteData, const char *contentType, const char *disposition, const char *filename);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetDecryptCert(HCkEmail cHandle, HCkCert cert);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetDecryptCert2(HCkEmail cHandle, HCkCert cert, HCkPrivateKey key);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetDt(HCkEmail cHandle, HCkDateTime dt);
CK_C_VISIBLE_PUBLIC void CkEmail_SetEdifactBody(HCkEmail cHandle, const char *message, const char *name, const char *filename, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetEncryptCert(HCkEmail cHandle, HCkCert cert);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromMimeBd(HCkEmail cHandle, HCkBinData bindat);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromMimeBytes(HCkEmail cHandle, HCkByteData mimeBytes);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromMimeBytes2(HCkEmail cHandle, HCkByteData mimeBytes, const char *charset);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromMimeSb(HCkEmail cHandle, HCkStringBuilder sb);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromMimeText(HCkEmail cHandle, const char *mimeText);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetFromXmlText(HCkEmail cHandle, const char *xmlStr);
CK_C_VISIBLE_PUBLIC void CkEmail_SetHtmlBody(HCkEmail cHandle, const char *html);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetMbHtmlBody(HCkEmail cHandle, const char *charset, HCkByteData inData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetMbPlainTextBody(HCkEmail cHandle, const char *charset, HCkByteData inData);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetRelatedFilename(HCkEmail cHandle, int index, const char *path);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetReplacePattern(HCkEmail cHandle, const char *pattern, const char *replaceString);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetSigningCert(HCkEmail cHandle, HCkCert cert);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_SetSigningCert2(HCkEmail cHandle, HCkCert cert, HCkPrivateKey key);
CK_C_VISIBLE_PUBLIC void CkEmail_SetTextBody(HCkEmail cHandle, const char *bodyText, const char *contentType);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_UidlEquals(HCkEmail cHandle, HCkEmail e);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_UnpackHtml(HCkEmail cHandle, const char *unpackDir, const char *htmlFilename, const char *partsSubdir);
CK_C_VISIBLE_PUBLIC void CkEmail_UnSpamify(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_UnzipAttachments(HCkEmail cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_UseCertVault(HCkEmail cHandle, HCkXmlCertVault vault);
CK_C_VISIBLE_PUBLIC BOOL CkEmail_ZipAttachments(HCkEmail cHandle, const char *zipFilename);
#endif
