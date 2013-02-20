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
	//载入快盘openapi的dll
	HMODULE module = NULL;
	module = ::LoadLibrary(L"xlivesdk.dll");
	if (module == NULL)
	{
		cout << "xlivesdk.dll载入失败！" << endl;
		return 0;
	}
	kp_init XLIVE_Init = (kp_init)GetProcAddress(module, "XLIVE_Init");
	kp_get_temp_token XLIVE_GetTempToken = (kp_get_temp_token)GetProcAddress(module,
		"XLIVE_GetTempToken");
	kp_get_authorize XLIVE_GetAuthorize = (kp_get_authorize)GetProcAddress(module,
		"XLIVE_GetAuthorize");
	kp_get_access_token XLIVE_GetAccessToken = (kp_get_access_token)GetProcAddress(module,
		"XLIVE_GetAccessToken");

	//获取快盘sdk调用句柄
	BSTR consumer_key = ::SysAllocString(L"xcdmLvFFxrOpC8ro"); //需要申请
	BSTR consumer_secret = ::SysAllocString(L"VNXft52KzIHQdIwF"); //同上
	BSTR root = ::SysAllocString(L"app_folder");
	if (XLIVE_Init == NULL)
		return 0;
	XLIVE_HANDLE xhandle = XLIVE_Init(consumer_key, consumer_secret,
		root, NULL, NULL);

	//oauth第一步，获取tem_token
	CComBSTR tem_token_key;
	CComBSTR tem_token_secret;
	CComBSTR oauth_callback_confirmed;
	BSTR oauth_callback = ::SysAllocString(L"");
	if (XLIVE_GetTempToken == NULL)
		return 0;
	XLIVE_GetTempToken(xhandle, oauth_callback, &tem_token_key,
		&tem_token_secret, &oauth_callback_confirmed);

	//oauth第二步，弹出登录界面，等待用户输入用户名和密码
	CComBSTR verifier;
	if (XLIVE_GetAuthorize == NULL)
		return 0;
	XLIVE_GetAuthorize(tem_token_key, &verifier);

	//oauth第三步，用tem_token换取access_token
	CComBSTR access_token_key;
	CComBSTR access_token_secret;
	if (XLIVE_GetAccessToken == NULL)
		return 0;
	XLIVE_GetAccessToken(xhandle, tem_token_key, tem_token_secret, verifier,
		&access_token_key, &access_token_secret);

	cout << "获取access_token成功：\n";
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
		cout << "access_token写入文件成功！\n";
	}
	else
	{
		cout << "access_token写入文件失败！\n";
	}
	

	return 0;
}

