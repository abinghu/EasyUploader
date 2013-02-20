// easy_uploader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kp_sdk.h"
#include <fstream>


using namespace std;

//get from http://www.oschina.net/code/snippet_35713_5681
void ComBSTR_to_char(CComBSTR bstr,char *outdata,int maxlen)
{
	unsigned int i,len;
	len=bstr.Length();
	memset(outdata,0,maxlen);
	for(i=0;i<len;i++)
		*(outdata+i)=*(bstr.m_str+i);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//�������openapi��dll
	HMODULE module = NULL;
	module = ::LoadLibrary(L"xlivesdk.dll");
	if (module == NULL)
	{
		cout << "xlivesdk.dll����ʧ�ܣ�" << endl;
		return 0;
	}
	kp_init XLIVE_Init = (kp_init)GetProcAddress(module, "XLIVE_Init");
	kp_get_temp_token XLIVE_GetTempToken = (kp_get_temp_token)GetProcAddress(module,
		"XLIVE_GetTempToken");
	kp_get_authorize XLIVE_GetAuthorize = (kp_get_authorize)GetProcAddress(module,
		"XLIVE_GetAuthorize");
	kp_get_access_token XLIVE_GetAccessToken = (kp_get_access_token)GetProcAddress(module,
		"XLIVE_GetAccessToken");

	//��ȡ����sdk���þ��
	BSTR consumer_key = ::SysAllocString(L"xcdmLvFFxrOpC8ro"); //��Ҫ����
	BSTR consumer_secret = ::SysAllocString(L"VNXft52KzIHQdIwF"); //ͬ��
	BSTR root = ::SysAllocString(L"app_folder");
	if (XLIVE_Init == NULL)
		return 0;
	XLIVE_HANDLE xhandle = XLIVE_Init(consumer_key, consumer_secret,
		root, NULL, NULL);

	//oauth��һ������ȡtem_token
	CComBSTR tem_token_key;
	CComBSTR tem_token_secret;
	CComBSTR oauth_callback_confirmed;
	BSTR oauth_callback = ::SysAllocString(L"");
	if (XLIVE_GetTempToken == NULL)
		return 0;
	XLIVE_GetTempToken(xhandle, oauth_callback, &tem_token_key,
		&tem_token_secret, &oauth_callback_confirmed);

	//oauth�ڶ�����������¼���棬�ȴ��û������û���������
	CComBSTR verifier;
	if (XLIVE_GetAuthorize == NULL)
		return 0;
	XLIVE_GetAuthorize(tem_token_key, &verifier);

	//oauth����������tem_token��ȡaccess_token
	CComBSTR access_token_key;
	CComBSTR access_token_secret;
	if (XLIVE_GetAccessToken == NULL)
		return 0;
	XLIVE_GetAccessToken(xhandle, tem_token_key, tem_token_secret, verifier,
		&access_token_key, &access_token_secret);

	cout << "��ȡaccess_token�ɹ���\n";
	char token_key[50];
	ComBSTR_to_char(access_token_key, token_key, 50);
	cout << "access_token_key:" << token_key << endl;
	char token_secret[50];
	ComBSTR_to_char(access_token_secret, token_secret, 50);
	cout << "access_token_secret:" << token_secret << endl;

	ofstream fs;
	fs.open(L"access_token.txt");
	if (fs.good())
	{
		fs << "access_token_key:" << token_key << endl;
		fs << "access_token_secret:" << token_secret << endl;
		fs.close();
		cout << "access_tokenд���ļ��ɹ���\n";
	}
	else
	{
		cout << "access_tokenд���ļ�ʧ�ܣ�\n";
	}
	

	return 0;
}

