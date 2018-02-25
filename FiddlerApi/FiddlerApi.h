#pragma once

#include <list>
#include <string>
using namespace std;

#ifdef __FIDDLER_API_SOURCE

#define __DECLSPEC     __declspec(dllexport)  
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <map>
#include <sstream>
#include <msclr\marshal_cppstd.h>    
#using "..\\resources\\FiddlerCore4.dll"
using namespace System::Collections::Generic;
using namespace msclr::interop;
using namespace System;
using namespace Fiddler;
using namespace System::Threading;

#else
#define __DECLSPEC    __declspec(dllimport)  
#endif // __FIDDLER_API_SOURCE

#define  __FIDDLER_CALL _stdcall

typedef struct HttpHeader
{
	string name;
	string value;
}*pHttpHeader;

typedef struct FiddlerData
{
	// id
	const int id;
	// event is send(0), recv(1) or complete(2)
	const int event;
	// Http����Ľ���ID
	const int processId;
	// �Ƿ�Ҫ�޸�Http��Ӧbody,�����Ҫ�޸���Ҫ�ڻص�����event=SEND��ʱ���bModifyResponseBody�޸�Ϊtrue
	bool bModifyResponseBody;
	int modifyFlags;
	// url
	string*   url;
	string*   httpMethod;
	string*   httpVersion;
	// http header 
	string*   header;
	// http body
	string*   body;
} *pFiddlerData;

// FiddlerData modifyFlags values
enum ModifyFlag
{
	MODIFY_NO_ALL = 0,
	MODIFY_URL = 1,
	MODIFY_BODY = 2,
	MODIFY_HEADERS = 4,
	MODIFY_ALL = MODIFY_URL | MODIFY_BODY | MODIFY_HEADERS
};

// FiddlerData event values
enum EventType
{
	SEND = 0,
	RECV,
	COMPLETE
};


enum LogLevel
{
	CLOSE = 0,
	ERR = 1,
	WARN = 2 | ERR,
	INFO = 4 | WARN,
	DEBUG = 8 | INFO
};

typedef struct FiddlerConfig
{
	int iListenPort;
	bool bRegisterAsSystemProxy;
	// Ĭ���Ƿ��޸�ResponseBody
	bool bAlwaysModifyResponseBody;
	bool bDecryptSSL;
	bool bAllowRemote;
	int iSecureEndpointPort;
	LogLevel logLevel;
	char *sSecureEndpointHostname;
	char* szLogFileName;
} *pFiddlerConfig;

typedef struct Version
{
	// ��Ҫ�汾
	int major;
	// �ΰ汾
	int minor;
	// �ڲ��汾�ŵĲ�ͬ��ʾ����ͬԴ���������±���
	int build;
	// ���ơ����汾�źʹΰ汾�Ŷ���ͬ���޶��Ų�ͬ�ĳ���Ӧ����ȫ�ɻ����ġ����������޸���ǰ�����ĳ����еİ�ȫ©��
	int revision;
	// ����
	char*  name;

}*pVersion ,_Version;

// ��Ϣ�ص�������
typedef bool(*lpCallBack)(FiddlerData& data);

typedef struct  CallBackInfo
{
	// �ص�����
	lpCallBack lpAddr;
	// �汾��Ϣ
	pVersion version;

}*pCallBackData;
 
#ifdef __cplusplus
extern "C" {
#endif //  _cplusplus

	// ��ʼ��Fiddler
	__DECLSPEC bool __FIDDLER_CALL Start();
	// �ر�Fiddler
	__DECLSPEC bool __FIDDLER_CALL Close();
	// ��ӻص�����
	__DECLSPEC  bool __FIDDLER_CALL   AddSimpleCallBack(__in const lpCallBack callBack);
	// ��ӻص�����
	__DECLSPEC void __FIDDLER_CALL AddCallBack(__in const CallBackInfo&);
	// ����������Fiddler��֤��,https��Ҫ
	__DECLSPEC bool __FIDDLER_CALL CreateAndTrustRootCert();
	// ɾ��fiddler���ɵ�֤��
	__DECLSPEC bool __FIDDLER_CALL RemoveCert(bool bRemoveRoot);
	// д��־
	__DECLSPEC void __FIDDLER_CALL WriteLog(LogLevel level, const char* const str);
	// д��־
	__DECLSPEC void __FIDDLER_CALL WriteLogEx(__in LogLevel level, __in string& str);
	// ��ȡ����
	__DECLSPEC  void __FIDDLER_CALL GetFiddlerConfig(FiddlerConfig& data);
	// ����Fiddler����
	__DECLSPEC bool __FIDDLER_CALL SetFiddlerConfig(const FiddlerConfig&);
	// ��ʼ��Ĭ��Fiddler������Ϣ,DLL�������Զ���ʼ��,�ⲿ����Ҫ�����������
	 __DECLSPEC  bool  InitConfig();

#ifdef __cplusplus
}
#endif //  _cplusplus

#define  CRLF "\r\n"
#define  COLON ":"
#define  SPACE " "
