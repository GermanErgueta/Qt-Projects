// This is a generated source file for Chilkat version 10.0.0
#ifndef _C_CkJsonObjectWH
#define _C_CkJsonObjectWH
#include "chilkatDefs.h"

#include "ck_inttypes.h"
#include "Chilkat_C.h"


CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_Create(void);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_Dispose(HCkJsonObjectW handle);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getDebugLogFilePath(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putDebugLogFilePath(HCkJsonObjectW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_debugLogFilePath(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getDelimiterChar(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putDelimiterChar(HCkJsonObjectW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_delimiterChar(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_getEmitCompact(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putEmitCompact(HCkJsonObjectW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_getEmitCrLf(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putEmitCrLf(HCkJsonObjectW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_getI(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putI(HCkJsonObjectW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_getJ(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putJ(HCkJsonObjectW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_getK(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putK(HCkJsonObjectW cHandle, int newVal);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getLastErrorHtml(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_lastErrorHtml(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getLastErrorText(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_lastErrorText(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getLastErrorXml(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_lastErrorXml(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_getLastMethodSuccess(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putLastMethodSuccess(HCkJsonObjectW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_getLowerCaseNames(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putLowerCaseNames(HCkJsonObjectW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getPathPrefix(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putPathPrefix(HCkJsonObjectW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_pathPrefix(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_getSize(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getUncommonOptions(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putUncommonOptions(HCkJsonObjectW cHandle, const wchar_t *newVal);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_uncommonOptions(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_getVerboseLogging(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC void  CkJsonObjectW_putVerboseLogging(HCkJsonObjectW cHandle, BOOL newVal);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_getVersion(HCkJsonObjectW cHandle, HCkString retval);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_version(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddArrayAt(HCkJsonObjectW cHandle, int index, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddArrayCopyAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, HCkJsonArrayW jarr);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddBoolAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, BOOL value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddIntAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, int value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddNullAt(HCkJsonObjectW cHandle, int index, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddNumberAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, const wchar_t *numericStr);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddObjectAt(HCkJsonObjectW cHandle, int index, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddObjectCopyAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, HCkJsonObjectW jsonObj);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AddStringAt(HCkJsonObjectW cHandle, int index, const wchar_t *name, const wchar_t *value);
CK_C_VISIBLE_PUBLIC HCkJsonArrayW CkJsonObjectW_AppendArray(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendArrayCopy(HCkJsonObjectW cHandle, const wchar_t *name, HCkJsonArrayW jarr);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendBool(HCkJsonObjectW cHandle, const wchar_t *name, BOOL value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendInt(HCkJsonObjectW cHandle, const wchar_t *name, int value);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_AppendObject(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendObjectCopy(HCkJsonObjectW cHandle, const wchar_t *name, HCkJsonObjectW jsonObj);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendString(HCkJsonObjectW cHandle, const wchar_t *name, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_AppendStringArray(HCkJsonObjectW cHandle, const wchar_t *name, HCkStringTableW values);
CK_C_VISIBLE_PUBLIC HCkJsonArrayW CkJsonObjectW_ArrayAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkJsonArrayW CkJsonObjectW_ArrayOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_BoolAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_BoolOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_BytesOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *encoding, HCkBinDataW bd);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_Clear(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_Clone(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_DateOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, HCkDateTimeW dateTime);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Delete(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_DeleteAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_DeleteRecords(HCkJsonObjectW cHandle, const wchar_t *arrayPath, const wchar_t *relpath, const wchar_t *value, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_DtOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, BOOL bLocal, HCkDtObjW dt);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Emit(HCkJsonObjectW cHandle, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_emit(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_EmitBd(HCkJsonObjectW cHandle, HCkBinDataW bd);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_EmitSb(HCkJsonObjectW cHandle, HCkStringBuilderW sb);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_EmitWithSubs(HCkJsonObjectW cHandle, HCkHashtableW subs, BOOL omitEmpty, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_emitWithSubs(HCkJsonObjectW cHandle, HCkHashtableW subs, BOOL omitEmpty);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_FindObjectWithMember(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_FindRecord(HCkJsonObjectW cHandle, const wchar_t *arrayPath, const wchar_t *relPath, const wchar_t *value, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_FindRecordString(HCkJsonObjectW cHandle, const wchar_t *arrayPath, const wchar_t *relPath, const wchar_t *value, BOOL caseSensitive, const wchar_t *retRelPath, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_findRecordString(HCkJsonObjectW cHandle, const wchar_t *arrayPath, const wchar_t *relPath, const wchar_t *value, BOOL caseSensitive, const wchar_t *retRelPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_FirebaseApplyEvent(HCkJsonObjectW cHandle, const wchar_t *name, const wchar_t *data);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_FirebasePatch(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *jsonData);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_FirebasePut(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *value);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_GetDocRoot(HCkJsonObjectW cHandle);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_HasMember(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_IndexOf(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_IntAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_IntOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_IsNullAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_IsNullOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_JsonTypeOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Load(HCkJsonObjectW cHandle, const wchar_t *json);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_LoadBd(HCkJsonObjectW cHandle, HCkBinDataW bd);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_LoadFile(HCkJsonObjectW cHandle, const wchar_t *path);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_LoadPredefined(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_LoadSb(HCkJsonObjectW cHandle, HCkStringBuilderW sb);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_MoveMember(HCkJsonObjectW cHandle, int fromIndex, int toIndex);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_NameAt(HCkJsonObjectW cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_nameAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_ObjectAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC HCkJsonObjectW CkJsonObjectW_ObjectOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Predefine(HCkJsonObjectW cHandle, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Rename(HCkJsonObjectW cHandle, const wchar_t *oldName, const wchar_t *newName);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_RenameAt(HCkJsonObjectW cHandle, int index, const wchar_t *name);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SaveLastError(HCkJsonObjectW cHandle, const wchar_t *path);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetBoolAt(HCkJsonObjectW cHandle, int index, BOOL value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetBoolOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, BOOL value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetIntAt(HCkJsonObjectW cHandle, int index, int value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetIntOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, int value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetNullAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetNullOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetNumberAt(HCkJsonObjectW cHandle, int index, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetNumberOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetStringAt(HCkJsonObjectW cHandle, int index, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_SetStringOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *value);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_SizeOfArray(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC void CkJsonObjectW_Sort(HCkJsonObjectW cHandle, BOOL ascending, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_StringAt(HCkJsonObjectW cHandle, int index, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_stringAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_StringOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath, HCkString outStr);
CK_C_VISIBLE_PUBLIC const wchar_t *CkJsonObjectW_stringOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_StringOfEquals(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *value, BOOL caseSensitive);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_StringOfSb(HCkJsonObjectW cHandle, const wchar_t *jsonPath, HCkStringBuilderW sb);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_Swap(HCkJsonObjectW cHandle, int index1, int index2);
CK_C_VISIBLE_PUBLIC int CkJsonObjectW_TypeAt(HCkJsonObjectW cHandle, int index);
CK_C_VISIBLE_PUBLIC unsigned long CkJsonObjectW_UIntOf(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateBd(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *encoding, HCkBinDataW bd);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateBool(HCkJsonObjectW cHandle, const wchar_t *jsonPath, BOOL value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateInt(HCkJsonObjectW cHandle, const wchar_t *jsonPath, int value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateNewArray(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateNewObject(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateNull(HCkJsonObjectW cHandle, const wchar_t *jsonPath);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateNumber(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *numericStr);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateSb(HCkJsonObjectW cHandle, const wchar_t *jsonPath, HCkStringBuilderW sb);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateString(HCkJsonObjectW cHandle, const wchar_t *jsonPath, const wchar_t *value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_UpdateUInt(HCkJsonObjectW cHandle, const wchar_t *jsonPath, unsigned long value);
CK_C_VISIBLE_PUBLIC BOOL CkJsonObjectW_WriteFile(HCkJsonObjectW cHandle, const wchar_t *path);
#endif
