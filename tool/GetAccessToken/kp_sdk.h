#pragma once

typedef void* XLIVE_HANDLE;
typedef XLIVE_HANDLE XLIVE_HFiles;
typedef XLIVE_HANDLE XLIVE_HFile;
typedef XLIVE_HANDLE XLIVE_HProgress;

//定义动态调用dll时用到的函数指针
typedef XLIVE_HANDLE (*kp_init)(BSTR bstrConsumerKey,
						BSTR bstrConsumerSecret,
						BSTR bstrRoot,
						BSTR bstrAccessToken,
						BSTR bstrAccessTokenSecret);

typedef HRESULT (*kp_get_temp_token)(XLIVE_HANDLE xHandle,
									 BSTR bstrOauthCallback,
									 BSTR* pbstrOauthToken,
									 BSTR* pbstrOauthTokenSecret,
									 BSTR* pbstrOauthCallbackConfirmed);

typedef HRESULT (*kp_get_authorize)(BSTR bstrTempToken,
									BSTR* pbstrVerifier);

typedef HRESULT (*kp_get_access_token)(XLIVE_HANDLE xHandle,
									   BSTR bstrTempToken,
									   BSTR bstrTempTokenSecret,
									   BSTR bstrVerifier,
									   BSTR* pbstrAccessToken,
									   BSTR* pbstrAccessTokenSecret);