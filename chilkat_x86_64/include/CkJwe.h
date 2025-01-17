// CkJwe.h: interface for the CkJwe class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat 10.0.0

#define _CkVersion 10.0.0

#ifndef _CkJwe_H
#define _CkJwe_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkMultiByteBase.h"

class CkBinData;
class CkStringBuilder;
class CkJsonObject;
class CkPrivateKey;
class CkPublicKey;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif


#undef Copy

// CLASS: CkJwe
class CK_VISIBLE_PUBLIC CkJwe  : public CkMultiByteBase
{
    private:

	// Don't allow assignment or copying these objects.
	CkJwe(const CkJwe &);
	CkJwe &operator=(const CkJwe &);

    public:
	CkJwe(void);
	virtual ~CkJwe(void);

	static CkJwe *createNew(void);
	static CkJwe *createNew2(int progLang);		// Added in Chilkat v10.0.0
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	
		
	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The number of recipients for this JWE.
	int get_NumRecipients(void);

	// Controls whether the JWE Compact Serialization or JWE JSON Serialization is
	// preferred when creating JWEs. The default value is true, which is to use
	// compact serialization when possible. If multiple recipients exist, or if any
	// unprotected headers exist, then JWE JSON Serialization is used regardless of
	// this property setting.
	bool get_PreferCompact(void);
	// Controls whether the JWE Compact Serialization or JWE JSON Serialization is
	// preferred when creating JWEs. The default value is true, which is to use
	// compact serialization when possible. If multiple recipients exist, or if any
	// unprotected headers exist, then JWE JSON Serialization is used regardless of
	// this property setting.
	void put_PreferCompact(bool newVal);

	// Controls whether the flattened serialization is preferred when JWE JSON
	// Serialization is used. The default value is true, which is to use the
	// flattened serialization when possible. If multiple recipients exist, then the
	// general (non-flattened) JWE JSON Serialization is used regardless of this
	// property setting.
	bool get_PreferFlattened(void);
	// Controls whether the flattened serialization is preferred when JWE JSON
	// Serialization is used. The default value is true, which is to use the
	// flattened serialization when possible. If multiple recipients exist, then the
	// general (non-flattened) JWE JSON Serialization is used regardless of this
	// property setting.
	void put_PreferFlattened(bool newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Decrypts a JWE and returns the original (decrypted) string content. The byte
	// representation of the decrypted bytes is indicated by charset (such as "utf-8").
	// (The charset tells Chilkat how to intepret the decrypted bytes as characters.)
	// 
	// The index specifies which recipient key is used for decryption. (Most JWEs have
	// only a single recipent, and thus the index is typically 0.)
	// 
	// Supported Algorithms:
	//     RSAES OAEP 256 (using SHA-256 and MGF1 with SHA-256) encryption with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES OAEP (using SHA-1 and MGF1 with SHA-1) encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES-PKCS1-V1_5 encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     Direct symmetric key encryption with pre-shared key A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM and A256GCM
	//     A128KW, A192KW, A256KW encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     A128GCMKW, A192GCMKW, A256GCMKW encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     PBES2-HS256+A128KW, PBES2-HS384+A192KW, PBES2-HS512+A256KW with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	// 
	bool Decrypt(int index, const char *charset, CkString &outStr);

	// Decrypts a JWE and returns the original (decrypted) string content. The byte
	// representation of the decrypted bytes is indicated by charset (such as "utf-8").
	// (The charset tells Chilkat how to intepret the decrypted bytes as characters.)
	// 
	// The index specifies which recipient key is used for decryption. (Most JWEs have
	// only a single recipent, and thus the index is typically 0.)
	// 
	// Supported Algorithms:
	//     RSAES OAEP 256 (using SHA-256 and MGF1 with SHA-256) encryption with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES OAEP (using SHA-1 and MGF1 with SHA-1) encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES-PKCS1-V1_5 encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     Direct symmetric key encryption with pre-shared key A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM and A256GCM
	//     A128KW, A192KW, A256KW encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     A128GCMKW, A192GCMKW, A256GCMKW encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     PBES2-HS256+A128KW, PBES2-HS384+A192KW, PBES2-HS512+A256KW with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	// 
	const char *decrypt(int index, const char *charset);

	// Decrypts the loaded JWE and appends the decrypted bytes to the contents of bd.
	// The index specifies which recipient key is used for decryption. (Most JWEs have
	// only a single recipent, and thus the index is typically 0.)
	bool DecryptBd(int index, CkBinData &bd);


	// Decrypts the loaded JWE and appends the decrypted content to contentSb. The byte
	// representation of the decrypted bytes is indicated by charset (such as "utf-8").
	// (This tells Chilkat how to interpret the bytes as characters.)
	// 
	// The index specifies which recipient key is used for decryption. (Most JWEs have
	// only a single recipent, and thus the index is typically 0.)
	// 
	bool DecryptSb(int index, const char *charset, CkStringBuilder &contentSb);


	// Encrypts string content to produce a JWE. The byte representation of the content is
	// indicated by charset (such as "utf-8").
	// 
	// Supported Algorithms:
	//     RSAES OAEP 256 (using SHA-256 and MGF1 with SHA-256) encryption with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES OAEP (using SHA-1 and MGF1 with SHA-1) encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES-PKCS1-V1_5 encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     Direct symmetric key encryption with pre-shared key A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM and A256GCM
	//     A128KW, A192KW, A256KW encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     A128GCMKW, A192GCMKW, A256GCMKW encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     PBES2-HS256+A128KW, PBES2-HS384+A192KW, PBES2-HS512+A256KW with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	// 
	bool Encrypt(const char *content, const char *charset, CkString &outStr);

	// Encrypts string content to produce a JWE. The byte representation of the content is
	// indicated by charset (such as "utf-8").
	// 
	// Supported Algorithms:
	//     RSAES OAEP 256 (using SHA-256 and MGF1 with SHA-256) encryption with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES OAEP (using SHA-1 and MGF1 with SHA-1) encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     RSAES-PKCS1-V1_5 encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     Direct symmetric key encryption with pre-shared key A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM and A256GCM
	//     A128KW, A192KW, A256KW encryption with A128CBC-HS256, A192CBC-HS384,
	//     A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     A128GCMKW, A192GCMKW, A256GCMKW encryption with A128CBC-HS256,
	//     A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	//     PBES2-HS256+A128KW, PBES2-HS384+A192KW, PBES2-HS512+A256KW with
	//     A128CBC-HS256, A192CBC-HS384, A256CBC-HS512, A128GCM, A192GCM, A256GCM
	// 
	const char *encrypt(const char *content, const char *charset);

	// Encrypts the contents of contentBd to produce a JWE that is appended to the contents
	// of jweSb. (This method provides the means to produce a JWE from binary content.)
	bool EncryptBd(CkBinData &contentBd, CkStringBuilder &jweSb);


	// Encrypts the contents of contentSb to produce a JWE that is appended to the contents
	// of jweSb. The byte representation of the string to be encrypted is indicated by
	// charset (such as "utf-8").
	bool EncryptSb(CkStringBuilder &contentSb, const char *charset, CkStringBuilder &jweSb);


	// Finds the index of the recipient with a header parameter (paramName) equal to a
	// specified value (paramValue). Returns -1 if no recipient contains a header with the
	// given name/value. If caseSensitive is true, then the header param name/value
	// comparisons are case sensitive. Otherwise it is case insensitive.
	// 
	// The procedure for decrypting a JWE with multiple recipients is the following:
	//     Load the JWE via one of the Load* methods.
	//     Find the recipient index by some identifying header paramter. The typical
	//     case is via the "kid" header parameter. ("kid" is an arbitrary key ID
	//     applications can assign to identify keys.)
	//     Set the key for decryption at the found index by calling SetPrivateKey,
	//     SetWrappingKey, or SetPassword, depending on the type of key wrapping that is
	//     employed.
	//     Call Decrypt, DecryptSb, or DecryptBd to decrypt for the recipient (and key)
	//     at the given index.
	// 
	int FindRecipient(const char *paramName, const char *paramValue, bool caseSensitive);


	// Returns the JSON header from the JWE. The JSON header is loaded into json.
	bool GetHeader(CkJsonObject &json);


	// Returns the shared protected JSON header from the JWE. The shared protected
	// header is loaded into json.
	bool GetProtectedHeader(CkJsonObject &json);


	// Loads the contents of a JWE.
	bool LoadJwe(const char *jwe);


	// Loads the contents of a JWE from a StringBuilder object.
	bool LoadJweSb(CkStringBuilder &sb);


	// Sets the optional Additional Authenticated Data. This is only used for
	// non-compact serializations. The charset specifies the character encoding (such as
	// "utf-8") to be used for the byte representation for the additional authenticated
	// data.
	bool SetAad(const char *aad, const char *charset);


	// Sets the optional Additional Authenticated Data. This is only used for
	// non-compact serializations. This method provides a way for binary (non-text)
	// additional authenticated data to be used.
	bool SetAadBd(CkBinData &aad);


	// Sets the PBES2 password for key encryption or decryption. This is for the case
	// where the content encryption key (CEK) is encrypted using PBES2. An PBES2
	// password should be used in the cases where the "alg" header parameter value is
	// equal to one of the following:PBES2-HS256+A128KW
	// PBES2-HS384+A192KW
	// PBES2-HS512+A256KW The index is the index of the recipient, where the 1st
	// recipient is at index 0. (The typical use case for JWEs is for a single
	// recipient.)
	bool SetPassword(int index, const char *password);


	// Sets a private key for RSA key unwrapping/decryption. This is for the case where
	// the content encryption key (CEK) is encrypted using RSA. An RSA private key
	// should be used for decrypting in the cases where the "alg" header parameter
	// value is equal to one of the following:RSA1_5
	// RSA-OAEP
	// RSA-OAEP-256
	// RSA-OAEP-384  (added in Chilkat v9.5.0.71)
	// RSA-OAEP-512 (added in Chilkat v9.5.0.71) The index is the index of the
	// recipient, where the 1st recipient is at index 0. (The typical use case for JWEs
	// is for a single recipient.)
	bool SetPrivateKey(int index, CkPrivateKey &privKey);


	// Sets the JWE Protected Header.
	bool SetProtectedHeader(CkJsonObject &json);


	// Sets a public key for RSA key wrapping encryption. This is for the case where
	// the content encryption key (CEK) is encrypted using RSA. An RSA public key
	// should be used when encrypting for the cases where the "alg" header parameter
	// value is equal to one of the following:RSA1_5
	// RSA-OAEP
	// RSA-OAEP-256 The index is the index of the recipient, where the 1st recipient is
	// at index 0. (The typical use case for JWEs is for a single recipient.)
	bool SetPublicKey(int index, CkPublicKey &pubKey);


	// Sets a per-recipient unprotected header. This method would only be called if the
	// JWE is for multiple recipients. The 1st recipient is at index 0.
	bool SetRecipientHeader(int index, CkJsonObject &json);


	// Sets the JWE Shared Unprotected Header.
	bool SetUnprotectedHeader(CkJsonObject &json);


	// Sets the AES wrapping key for encryption or decryption. This is for the case
	// where the content encryption key (CEK) is encrypted using AES Key Wrap or AES
	// GCM. An AES key should be used in the cases where the "alg" header parameter
	// value is equal to one of the following:A128KW
	// A192KW
	// A256KW
	// A128GCMKW
	// A192GCMKW
	// A256GCMKW
	// dir The index is the index of the recipient, where the 1st recipient is at index
	// 0. (The typical use case for JWEs is for a single recipient.)
	// 
	// Note: This method also sets the shared direct symmetric key for the case when
	// the "alg" is equal to "dir". In this case, the key specified is not actualy a
	// key encryption key, but is the direct content encryption key.
	// 
	// The encoding indicates the representation, such as "base64", "hex", "base64url",
	// etc. of the encodedKey.
	// 
	bool SetWrappingKey(int index, const char *encodedKey, const char *encoding);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
