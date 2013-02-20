/********************************************************************
	created   :		2011-3-5   0:59
	filename  : 	xlive_i.h
	author    :		Leanse.Lee
	
	descriptor:	

*********************************************************************/

#ifndef _XLIVE_I_H__
#define _XLIVE_I_H__

typedef void* XLIVE_HANDLE;
typedef XLIVE_HANDLE XLIVE_HFiles;
typedef XLIVE_HANDLE XLIVE_HFile;
typedef XLIVE_HANDLE XLIVE_HProgress;

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct 
{        
	INT max_file_size;
	LONGLONG quota_total;
	LONGLONG quota_used;
	LONGLONG quota_recycled;
} XUserExt;

typedef struct 
{        // version 0
	BOOL bList;
	INT file_limit;
	INT page;
	INT page_size;
	WCHAR filter_ext[128];
	INT sort_by;	// 0-date,1-name,2-size
} XMetadata;

typedef void (*pfFinishNotify)(unsigned int result);


//typedef void (*Upload_Call_Back_Func)(xlive_process process ,int result);



	/*
	*		下面每个接口都可能返回这些状态：
	*		@	XLIVE_OK						成功返回
	*		@   XLIVE_NOT_SUPPORTED				1 未支持的方法
	*		@	XLIVE_INVALID_PARAM				2 非法的参数 
	*		@   XLIVE_INVALID_OPTION			3 非法的选项 
	*		@	XLIVE_FAILED_RESOLVE			4 解析数据失败
	*		@	XLIVE_CANCLE_OPERATE			5 操作被取消 
	*		@	XLIVE_BAD_FILE					6 文件已损坏 
	*		@	XLIVE_ERR_BFS					7 文件系统遇到
	*		@	XLIVE_FAILED_API				8 API调用失败, 请使用 XLIVE_GetErrorInfo 获取详细错误信息
	*		@	XLIVE_ERR_NETWORK				9 遇到网络错误
	*/

	// 初始化sdk库
	STDMETHODIMP_(XLIVE_HANDLE) XLIVE_Init(
		BSTR bstrConsumerKey,
		BSTR bstrConsumerSecret,
		BSTR bstrRoot,
		BSTR bstrAccessToken,
		BSTR bstrAccessTokenSecret
		);

	// 销毁句柄
	STDMETHODIMP_(void) XLIVE_Destory(XLIVE_HANDLE xHandle);

	// 取得错误信息
	STDMETHODIMP_(void) XLIVE_GetErrorInfo(XLIVE_HANDLE xHandle, BSTR* pbstrErrmsg);

	/**
	*	@brief :		显示注册用户界面
	*
	*	@param (IN)		xHandle			XLIVE_HANDLE
	*
	*	@param (OUT)	pbstrUserName			返回的注册用户名
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_RegisterUser(
		XLIVE_HANDLE xHandle,
		BSTR* pbstrUserName
		);
	

	STDMETHODIMP XLIVE_VerificationURL(
		XLIVE_HANDLE xHandle,
		BSTR* pbstrUrl,
		BSTR* pbstrAuthId
		);

	/*
		直接注册
	*/
	STDMETHODIMP XLIVE_ThirdRegister(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserName,
		BSTR bstrPassword,
		BSTR bstrVerficationCode,
		BSTR bstrAuthId
		);



	/**
	*	@brief :		Oauth-reduced 协议，取得访问令牌,不需要快盘用户与密码，该令牌功能有限
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrUserOpenId			用户在第三方应用中的唯一id
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetrAccesToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserOpenId
		);

	/**
	*	@brief :		Xauth协议，取得访问令牌，可以操作该快盘用户下的所有资源 
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrUserName			快盘用户名
	*	@param (IN)		bstrPassword			快盘用户密码
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetxAccesToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserName,
		BSTR bstrPassword,
		BSTR* pbstrAccessToken,
		BSTR* pbstrAccessTokenSecret
		);

	/*
	*	@brief :		获取未授权的临时token
	*
	*	@param (IN)		xHandle							XLIVE_HANDLE
	*	@param (IN)		strOauthCallback				回调函数(URL ),可以为空(L"")
	*
	*	@param (OUT)	strOauthToken					未授权的token
	*	@param (OUT)	strOauthTokenSecret				对应secret
	*	@param (OUT)	strOauthCallbackConfirmed		True/False，callback是否接收
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetTempToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrOauthCallback,
		BSTR* pbstrOauthToken,
		BSTR* pbstrOauthTokenSecret,
		BSTR* pbstrOauthCallbackConfirmed
		);


	/*
	*	@brief :		要求用户转到网页上登录快盘并授权,登录后取得Verifier。
	*
	*	@param (IN)		bstrTempToken					XLIVE_GetTempToken得到的临时token
	*
	*	@param (OUT)	pbstrVerifier					校验码
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetAuthorize(
		BSTR bstrTempToken,
		BSTR* pbstrVerifier
		);


	/*
	*	@brief :		用临时token换取access token
	*
	*	@param (IN)		xHandle							XLIVE_HANDLE
	*	@param (IN)		bstrTempToken					临时Token
	*	@param (IN)		bstrTempTokenSecret				临时TokenSecret
	*	@param (IN)		bstrVerifier					网站获取的校验码
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetAccessToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrTempToken,
		BSTR bstrTempTokenSecret,
		BSTR bstrVerifier,
		BSTR* pbstrAccessToken,
		BSTR* pbstrAccessTokenSecret
		);

	
	/**
	*	@brief :		查看用户信息 
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*
	*	@param (OUT)	piUserId				标识用户的唯一id(不一定返回有效值)
	*	@param (OUT)	pbstrUserName			用户名称
	*	@param (OUT)	piMaxFileSize			允许上传最大文件
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_AccountInfo(
		XLIVE_HANDLE xHandle,
		INT* piUserId,
		BSTR* pbstrUserName,
		XUserExt* pUserExt
		);

	/**
	*	@brief 获取用户的最大空间和使用的空间
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE

	*	@param (OUT) plusedSize			已使用的空间 (单位: Byte)
	*	@param (OUT) pltotalSize		用户空间总量 (单位: Byte)
	*	@param (OUT) plrecycled			用户空间的回收站空间使用量 (单位: Byte)(不一定返回确定值)
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_GetSpace(
		XLIVE_HANDLE xHandle,
		LONGLONG* plusedSize,
		LONGLONG* pltotalSize,
		LONGLONG* plrecycled);


	/**
	*	@brief 	查看单个文件、文件夹信息
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrFileId			标志文件的唯一id
	*
	*	@param (OUT) phFiles			文件集合句柄 
	*
	*	@return	参考错误状态返回值    
	*/
	STDMETHODIMP XLIVE_Metadata(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		XLIVE_HFile* phFiles,
		BOOL bList);

	
	/**
	*	@brief 函数用于删除文件或者文件夹
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrPath			被删除文件路径
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Delete(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath
		);
	

	/**
	*	@brief 移动文件或文件夹
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrFileId			移动对象的文件Id
	*	@param (IN) bstrNewParentId		移动到的目标文件夹的Id
	*	@param (IN) bstrNewName			移动后的新文件名（可以传"",就不会改名）
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Move(
		XLIVE_HANDLE xHandle,
		BSTR bstrFromPath,
		BSTR bstrToPath);

	/**
	*	@brief 函数用于新建文件夹
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrParentID			父目录ID,0为根目录
	*	@param (IN)		bstrName				文件夹的名称(utf8编码，不能超过255个字符,其所在绝对路径长度也不能超过255)
	*
	*	@param (OUT)	pbstrFileId				新建文件夹的ID
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_CreateFolder(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		BSTR* pbstrFileId);


	/**
	*	@brief 复制文件，文件夹
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				要复制的文件的id
	*	@param (IN)		bstrParentID			目标目录id，0为根目录
	*	@param (IN)		bstrNewName				复制后的新文件名(传NULL，则不重命名新文件,使用原文件名)
	*
	*	@param (OUT)	pbstrNewFileId			复制后的新文件ID
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Copy(
		XLIVE_HANDLE xHandle,
		BSTR bstrFromPath,
		BSTR bstrToPath,
		BSTR* pbstrFileId);


	/**
	*	@brief 	分页看回收站的文件，暂时没对外开放
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		iPage					大于0，默认使用第1页
	*	@param (IN)		iPageSize				每页的大小，默认使用20，最大512
	*
	*	@param (OUT)	phFiles					返回的文件集合的句柄
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Recycle(
		XLIVE_HANDLE xHandle,
		UINT iPage ,
		UINT iPageSize,
		XLIVE_HFiles* phFiles);


	/**
	*	@brief 	返回特定目录下的一级子目录与文件列表。上限100000个。支持分页
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				目录的id，0为根目录	
	*	@param (IN)		iFilterType				默认0，0为显示全部内容,1为只显示文件，2为只显示目录
	*	@param (IN)		iPage					默认0，为0的时候显示全部内容；分页，和page_size一起使用，显示第page页的内容
	*	@param (IN)		iPageSize				默认0，最大512，每页的内容数量。
	*
	*	@param (OUT)	phFiles					返回的文件集合的句柄
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_EnumFiles(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileId,
		UINT iFilterType,
		INT iPage,
		INT iPageSize,
		XLIVE_HFiles* phFiles);


	/**
	*	@brief 恢复回收站指定文件到指定文件夹，重名会自动添加(n)，1<=n<=20
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				文件id
	*	@param (IN)		bstrParentId			指定文件夹Id，0为根目录	
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Recover(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileId,
		BSTR bstrParentId);

	
	/**
	*	@brief 清空回收站的文件
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileIds				文件id，0则清空全部回收站文件
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_CleanRecycle(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileIds);

	/**
	*	@brief 创建并获取一个文件的的分享链接。发布外链的文件会接受审核。
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				文件id
	*	@param (IN)		bstrName				外链的名字
	*	@param (IN)		iExpired				过期天数，0为不过期
	*
	*	@param (OUT)	pbstrOutlinkUrl			外链URL地址
	*	@param (OUT)	pbstrStatus				外链状态，CREATE，READY，PROCESSING，WAITING(不一定有效返回)
	*	@param (OUT)	pbstrOutlinkId			外链id(不一定有效返回)
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_Shares(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		BSTR bstrName,
		BSTR bstrAccessCode,
		BSTR* pbstrOutlinkUrl,
		BSTR* pbstrAccessCode);


	/**
	*	@brief 删除外链
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrOutlinkId			外链id
	*
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_DeleteShares(
		XLIVE_HANDLE xHandle,
		BSTR bstrOutlinkId);


	/**
	*	@brief 查看文件的历史版本
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				要查询的文件id，曾经修改过的文件才有历史版本
	*
	*	@param (OUT)	phFiles					返回的文件句柄（历史版本只有三个属性：文件id，修改时间和文件版本号）
	*	@return	参考错误状态返回值  
	*/
	STDMETHODIMP XLIVE_History(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		XLIVE_HFiles* phFiles);

	//---------------------------------------------------------

	/**
	*	@brief : 上传文件(注意：确保文件的路径和文件是存在的)
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN):	bstrParentId				父目录Id
	*	@param (IN):	bstrName					文件名	(如 "test.txt")
	*	@param (IN):	bstrFilePath				文件路径 (如 "D:\\testData\\uploadTest.txt")
	*	@param (IN):	bstrTempFolderPath			文件上传临时文件夹路径 ("D:\\testData\\Temp")
	*	@param (IN):	hProgress					上传进度句柄
	*	
	*	@param (IN):	upCallBackFunc				上传回调函数,若无，可设为NULL.暂定接口是void (*funcName)(void)
	*
	*	@param (OUT):	pbstrFileId					上传的文件的FileId
	*	@param (OUT):	pbstrFileVer				返回的文件的版本号
	*
	*	@return	参考错误状态返回值  
	*/
// 	STDMETHODIMP XLIVE_Upload(
// 		XLIVE_HANDLE		xHandle,
// 		BSTR				bstrParentId,
// 		BSTR				bstrName,
// 		BSTR				bstrFilePath,
// 		BSTR				bstrTempFolderPath,
// 		BSTR*				pbstrFileId,
// 		BSTR*				pbstrFileVer);



	STDMETHODIMP XLIVE_Upload(
		XLIVE_HANDLE		xHandle,
		BSTR				bstrFilePath,
		BSTR				bstrLocalFilePath,
		BSTR				bstrTempFolderPath,
		BSTR*				pbstrFileId,
		BSTR*				pbstrFileVer
		);

	/**
	*	@brief : 处理异步上传文件(注意：确保文件的路径和文件是存在的)
	*	
	*	param (IN) :	copy给子线程的句柄
	*			
	*		创建子线程来上传文件
	*		子线程创建成功立刻返回XLIVE_OK，但不代表成功上传
	*/
	STDMETHODIMP XLIVE_Multi_Upload(
		XLIVE_HANDLE		xHandle,
		BSTR				bstrFilePath,
		BSTR				bstrLocalFilePath,
		BSTR				bstrTempFolderPath,
		BSTR*				pbstrFileId,
		BSTR*				pbstrFileVer,
		pfFinishNotify		pFinishNotify
		);





	/**
	*	@brief 文件下载
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				被下载的文件Id
	*	@param (IN)		bstrLocalPath			下载文件的本地目录(如 L"E:\\TestData\\downloadData.txt")
	*	@param (IN)		bstrTempFolderPath		临时目录(如 L"D:\\testData\\Temp")
	*	@param (IN)		bstrFileVer				历史版本号,传空("")表示下载当前版本
	*	@param (IN)		hProgress				进度句柄
	*
	*	@return	参考错误状态返回值  
	*/
// 	STDMETHODIMP XLIVE_Download(							  
// 		XLIVE_HANDLE		xHandle,
// 		BSTR				bstrFileId,
// 		BSTR				bstrLocalPath,
// 		BSTR				bstrTempFolderPath,
// 		BSTR				bstrFileVer
// 		);
	

	STDMETHODIMP XLIVE_Download(
		XLIVE_HANDLE		xHandle,
		BSTR				bstrFilePath,
		BSTR				bstrLocalFilePath,
		BSTR				bstrTempFolderPath,
		BSTR				bstrFileVer
		);


	/**
	*	@brief	: 处理异步下载文件
	*
	*	创建子线程来下载文件
	*	子线程创建成功立刻返回XLIVE_OK，但不代表下载成功
	*/
	STDMETHODIMP XLIVE_Multi_Download(
		XLIVE_HANDLE		xHandle,
		BSTR				bstrFilePath,
		BSTR				bstrLocalFilePath,
		BSTR				bstrTempFolderPath,
		BSTR				bstrFileVer,
		pfFinishNotify		pFinishNotify
		);


	/**
	*	@brif 处理异步请求
	**/
	unsigned int STDMETHODCALLTYPE threadAsyncPerform(PVOID pM);



	/**
	*	@brief ：查看上传、下载的进度
	*
	*	@param : hProgress	进度句柄
	*	@param : pdTotal	上传、下载的总进度
	*	@param ：pdNow		目前的进度
	*	@param : pdSpeed	上传、下载的进度
	*
	*	@return
	*		@ 成功 S_OK
	*/
	STDMETHODIMP XLIVE_QueryProgress(XLIVE_HANDLE xHandle, double* pdTotal, double* pdNow, double* pdSpeed);


	/*
	*	@brief :	异步查询进度
	*
	*	@param : filePath   查询的正在上传(下载)的快盘文件路径
	*	
	*	@return：
	*		@XLIVE_OK				: 查询成功
	*		@XLIVE_INVALID_PARAM	: 传入路径错误，或者上传(下载)任务已经完成
	*/
	STDMETHODIMP XLIVE_QueryProgressByPath(BSTR filePath, double* pdTotal, double* pdNow, double* pdSpeed);


	/**
	*	@brief : 取消上传、下载任务
	*
	*	@param : 进度句柄
	*
	*	@return
	*		@ 成功 S_OK
	*/
	STDMETHODIMP XLIVE_CancelTransport(XLIVE_HANDLE xHandle);


	/*
	*	@brief		: 根据文件路径取消上传、下载任务
	*	
	*	@param(IN)  : 文件路径：以快盘路径为准
	*	
	*	@return		: 
			@XLIVE_OK			 : 成功 	
			@XLIVE_INVALID_PARAM : 传入的文件路径错误或者上传（下载）任务已经完成
	*/
	STDMETHODIMP XLIVE_CancelTransportByPath(BSTR filePath);

	/**
	*	@brief 销毁文件集合句柄
	*
	*	@param (IN) hFiles	文件集合句柄
	*
	*/
	STDMETHODIMP_(void) XLIVE_DestoryFiles(XLIVE_HFiles hFiles);
	
	/**
	*	@brief 获取文件集合中文件的数量(包括文件夹)
	*
	*	@param (IN):	hFiles			文件句柄
	*
	*	@param (OUT):	fileNum			文件(包括文件夹)个数
	*
	*	@return	
	*		@ 返回文件集合的数量
	*/
	STDMETHODIMP_(void) XLIVE_GetFilesNum(XLIVE_HFiles hFiles, UINT* fileNum);

	STDMETHODIMP_(void) XLIVE_GetFolderPath(XLIVE_HFiles hFiles, BSTR* pbstrPath);

	STDMETHODIMP_(void) XLIVE_GetFolderHash(XLIVE_HFiles hFiles, BSTR* pbstrHash);

	/**
	*	@brief 获取文件类型
	*
	*	@param (IN)		hFiles 文件集合句柄, 句柄不允许传空
	*	@param (IN)		index 索引值（表示第几个文件，不能超过文件数量最大值，当目录是文件夹时，-1表示取文件夹的的属性） 
	
	*	@param (OUT):	fileType	文件类型(1表示文件 0表示文件夹)
	*	@return	
	*	@ 文件类型 1表示文件 0表示文件夹
	*/
	STDMETHODIMP_(void) XLIVE_GetFileType(XLIVE_HFiles hFiles, UINT index, UINT* fileType);

	/*
	*	@param (IN)		index 索引值（表示第几个文件，不能超过文件数量最大值，当目录是文件夹时，-1表示取文件夹的的属性） 
	*/
	STDMETHODIMP_(void) XLIVE_GetFileCreateTime(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);
	STDMETHODIMP_(void) XLIVE_GetFileModifyTime(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);

	STDMETHODIMP_(void) XLIVE_GetFileName(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);
	STDMETHODIMP_(void) XLIVE_GetFileRev(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrRev);
	STDMETHODIMP_(void) XLIVE_GetFileIsDeleted(XLIVE_HFiles hFiles, UINT index, BOOL* pbIsDeleted);

	STDMETHODIMP_(void) XLIVE_GetFileId(XLIVE_HFiles hFiles, UINT index, BSTR* pbIsDeleted);

	STDMETHODIMP_(void) XLIVE_GetFileSize(XLIVE_HFiles hFiles, UINT index, ULONG* plSzie);

	//不再提供使用
	STDMETHODIMP XLIVE_UfaUpload(
		BSTR				bstrRequestResult,
		BSTR				bstrFilePath,
		BSTR				bstrTempFolderPath,
		BSTR				bstrFileSize,
		XLIVE_HProgress		hProgress,
		BSTR*				pbstrFileId,
		BSTR*				pbstrFileVer,
		BSTR*				pbstrCommitInfo,
		BSTR*				pbstrStub);

	//不再提供使用
	STDMETHODIMP XLIVE_UfaDownload(
		BSTR				bstrRequestResult,
		BSTR				bstrFilePath,
		BSTR				bstrTempFolderPath,
		XLIVE_HProgress		hProgress,
		BSTR*				pbstrFileId, 
		BSTR*				pbstrFileVer,
		BSTR*				pbstrModTime,
		BSTR*				pbstrOpver);

	//////////////////////////////////////////////////////////////////////////
	// 活模板定制接口
	STDMETHODIMP XLIVE_RegisterAppPrevileges(BSTR strToken, BSTR strAppNo, BSTR strUserName, BSTR strKey);
	STDMETHODIMP XLIVE_GetAllContact(BSTR strToken, BSTR* pstrResult);
	STDMETHODIMP XLIVE_SendFile2Users(BSTR strToken, BSTR strFileId, BSTR strUserNames, BSTR strDestPath, BSTR* bstrResult);

#ifdef __cplusplus
}
#endif

#endif