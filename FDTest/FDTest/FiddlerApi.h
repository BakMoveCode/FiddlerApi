#ifndef __FIDDLER_API__
#define __FIDDLER_API__

#include <list>
#include <string>
using namespace std;

#ifdef __FIDDLER_API_SOURCE
// FiddlerApi.def�ļ�����
#define __DECLSPEC    // __declspec(dllexport)  
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

struct FiddlerData;
#define  __FIDDLER_CALL  __stdcall
// ��Ϣ�ص�������
typedef bool(*lpCallBack)(FiddlerData& data);
void  inline  SafeFree(__in void* ptr);

void    SafeFree(__in void* ptr)
{
	if (!ptr)
	{
		return;
	}
	else
	{
		free(ptr);
		ptr = NULL;
	}

}

typedef struct HttpHeader
{
	string name;
	string value;
}*pHttpHeader;

// ֪ͨ����
enum NotifyType
{
	// ��֪ͨ�κ�����
	NOTIFY_NO_ALL = 0,
	// ����֮ǰ֪ͨ
	NOTIFY_BEFORE_SEND = 1,
	// ��Ӧ֮ǰ֪ͨ
	NOTIFY_BEFORE_RESPONSE = 2,
	// ��Ӧ���֪ͨ
	NOTIFY_COMPOLE_RESPONSE = 4,
	// ֪ͨ��������
	NOTIFY_ALL = NOTIFY_BEFORE_SEND | NOTIFY_BEFORE_RESPONSE | NOTIFY_COMPOLE_RESPONSE
};

// FiddlerData modifyFlags values
enum ModifyFlag
{
	// ���޸�����
	MODIFY_NO_ALL = 0,
	// �޸�Url
	MODIFY_URL = 1,
	// �޸�http body
	MODIFY_BODY = 2,
	// �޸�http ͷ
	MODIFY_HEADERS = 4,
	// �޸�֪ͨ����
	MODIFY_NOTIFY = 8,
	// �޸�url,http header�Լ�http body
	MODIFY_ALL = MODIFY_URL | MODIFY_BODY | MODIFY_HEADERS | MODIFY_NOTIFY
};

// FiddlerData event values
enum EventType
{
	// ���ݷ��ͽ׶�,���޸���������
	SEND = 0,
	// ���ݽ��ս׶�,���޸���Ӧ����
	RECV,
	// ���ݽ��ս׶�,���ݲ����޸�
	COMPLETE
};


enum LogLevel
{
	// ����ӡ��־,���ֻ����������־������ʹ��,�ڴ�ӡ��־�в�Ҫʹ��
	CLOSE = 0,
	//  ֻ��ӡERR������־ 
	ERR = 1,
	// ��ӡWARN��ERR������־
	WARN = 2 | ERR,
	// ��ӡINFO WARN ERR ������־
	INFO = 4 | WARN,
	// ��ӡDEBUIG NFO WARN ERR ������־
	DEBUG = 8 | INFO
};


typedef struct FiddlerData
{
	// id,ÿһ��http�����Ψһ��ʶ,����Ϣ�ص��в�Ҫ�޸�
	int id;
	// �ص���Ϣ���� 0��ʾ���ݷ��ͽ׶�,1���ݽ��ս׶�,2��ʾ���ݴ�����ɽ׶�.����׶ε����ݲ������޸���.ȡֵ��Ӧ��EVENT��ö��ֵ
	int event;
	// Http����Ľ���ID,�ڻص��в�Ҫ�޸�
	int processId;
	// �Ƿ�Ҫ�޸�Http��Ӧbody,�����Ҫ�޸���Ҫ�ڻص�����event=SEND(0)��ʱ���bModifyResponseBody�޸�Ϊtrue
	bool bModifyResponseBody;
	// �޸ĵ����ݱ�־ȡֵ��`ModifyFlag`��ö��ֵ,��Ҫ�޸Ķ����ֵ��ȡֵ������`MODIFY_BODY|MODIFY_HEADERS`������
	ModifyFlag modifyFlags;
	// ֪ͨ����
	NotifyType notifyType;
	// http�����url
	char*   url;
	// http����ʽ,GET POST CONNECT��
	char*   httpMethod;
	// httpЭ��汾,�� HTTP/1.1
	char*   httpVersion;
	// httpͷ��Ϣ,enevtΪSENDʱ��ʾ����ͷ,��������Ӧͷ 
	char*   header;
	// http ��������
	char*   body;

} *pFiddlerData;

typedef struct FiddlerConfig
{
	// Fiddler����˿�
	int iListenPort;
	// �Ƿ���ϵͳ����
	bool bRegisterAsSystemProxy;
	// Ĭ���Ƿ��޸�ResponseBody
	bool bAlwaysModifyResponseBody;
	// �Ƿ����https������,�����Ҫ����Fiddler�ĸ�֤��
	bool bDecryptSSL;
	// �Ƿ�����Զ������
	bool bAllowRemote;
	// https��������ʹ��
	int iSecureEndpointPort;
	// ��־����
	LogLevel logLevel;
	// ֪ͨ����
	NotifyType notifyType;
	// �ص�
	lpCallBack callBack;
	// szSecureEndpointHostname
	char *szSecureEndpointHostname;
	// ��־�ļ�ȫ·��
	char* szLogFileName;
	// ����PID����������ʽ,�ͽ���������������ʽֻҪ��һ��ƥ���Ͼͱ�ʾƥ����
	char* szRegexProcessId;
	// ����������������ʽ
	char* szRegexProcessName;

} *pFiddlerConfig;

#ifdef __cplusplus
extern "C" {
#endif //  _cplusplus

	// ����Fiddler
	__DECLSPEC bool __FIDDLER_CALL Start();
	// �ر�Fiddler
	__DECLSPEC bool __FIDDLER_CALL Close();
	// ��ȡ����
	__DECLSPEC  void __FIDDLER_CALL GetFiddlerConfig(__inout FiddlerConfig* const data);
	// ����Fiddler����, ע��,���Ҫ�� Start()֮ǰ���ò���Ч
	__DECLSPEC bool __FIDDLER_CALL SetFiddlerConfig(__in const FiddlerConfig* const);
	// ��ӻص�����
	__DECLSPEC bool __FIDDLER_CALL SetCallBack(__in const lpCallBack callBack);
	// �޸�Fiddler����
	__DECLSPEC bool __FIDDLER_CALL ModifyFiddlerData(__in const FiddlerData* const newData);
	// ����Fiddler��֤��
	__DECLSPEC bool __FIDDLER_CALL ExportRootCert(__in const char* const fileName);
	// ����������Fiddler��֤��,https��Ҫ
	__DECLSPEC bool __FIDDLER_CALL CreateAndTrustRootCert();
	// ɾ��fiddler���ɵ�֤��
	__DECLSPEC bool __FIDDLER_CALL RemoveCert(__in const bool bRemoveRoot);
	// �ͷ�FidderConfig
	__DECLSPEC void __FIDDLER_CALL FreeFiddlerConfig(__in FiddlerConfig* data);
	// �ͷ�FreeFiddlerData
	__DECLSPEC void __FIDDLER_CALL  FreeFiddlerData(__in FiddlerData* data);
	// д��־,ע��,���Ҫ�� Start()֮����ò���Ч
	__DECLSPEC void __FIDDLER_CALL WriteLog(LogLevel level, const char* const str);
	// д��־,ע��,���Ҫ�� Start()֮����ò���Ч
	__DECLSPEC void __FIDDLER_CALL WriteLogEx(LogLevel level, const char* const format, ...);
	// ��ʼ��Ĭ��Fiddler������Ϣ,DLL�������Զ���ʼ��,�ⲿ����Ҫ�����������
	__DECLSPEC  bool  InitConfig();

#ifdef __cplusplus
}
#endif //  _cplusplus

#define  CRLF "\r\n"
#define  COLON ":"
#define  SPACE " "

#endif