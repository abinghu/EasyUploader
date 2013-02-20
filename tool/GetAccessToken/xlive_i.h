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
	*		����ÿ���ӿڶ����ܷ�����Щ״̬��
	*		@	XLIVE_OK						�ɹ�����
	*		@   XLIVE_NOT_SUPPORTED				1 δ֧�ֵķ���
	*		@	XLIVE_INVALID_PARAM				2 �Ƿ��Ĳ��� 
	*		@   XLIVE_INVALID_OPTION			3 �Ƿ���ѡ�� 
	*		@	XLIVE_FAILED_RESOLVE			4 ��������ʧ��
	*		@	XLIVE_CANCLE_OPERATE			5 ������ȡ�� 
	*		@	XLIVE_BAD_FILE					6 �ļ����� 
	*		@	XLIVE_ERR_BFS					7 �ļ�ϵͳ����
	*		@	XLIVE_FAILED_API				8 API����ʧ��, ��ʹ�� XLIVE_GetErrorInfo ��ȡ��ϸ������Ϣ
	*		@	XLIVE_ERR_NETWORK				9 �����������
	*/

	// ��ʼ��sdk��
	STDMETHODIMP_(XLIVE_HANDLE) XLIVE_Init(
		BSTR bstrConsumerKey,
		BSTR bstrConsumerSecret,
		BSTR bstrRoot,
		BSTR bstrAccessToken,
		BSTR bstrAccessTokenSecret
		);

	// ���پ��
	STDMETHODIMP_(void) XLIVE_Destory(XLIVE_HANDLE xHandle);

	// ȡ�ô�����Ϣ
	STDMETHODIMP_(void) XLIVE_GetErrorInfo(XLIVE_HANDLE xHandle, BSTR* pbstrErrmsg);

	/**
	*	@brief :		��ʾע���û�����
	*
	*	@param (IN)		xHandle			XLIVE_HANDLE
	*
	*	@param (OUT)	pbstrUserName			���ص�ע���û���
	*
	*	@return	�ο�����״̬����ֵ  
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
		ֱ��ע��
	*/
	STDMETHODIMP XLIVE_ThirdRegister(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserName,
		BSTR bstrPassword,
		BSTR bstrVerficationCode,
		BSTR bstrAuthId
		);



	/**
	*	@brief :		Oauth-reduced Э�飬ȡ�÷�������,����Ҫ�����û������룬�����ƹ�������
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrUserOpenId			�û��ڵ�����Ӧ���е�Ψһid
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_GetrAccesToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserOpenId
		);

	/**
	*	@brief :		XauthЭ�飬ȡ�÷������ƣ����Բ����ÿ����û��µ�������Դ 
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrUserName			�����û���
	*	@param (IN)		bstrPassword			�����û�����
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_GetxAccesToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrUserName,
		BSTR bstrPassword,
		BSTR* pbstrAccessToken,
		BSTR* pbstrAccessTokenSecret
		);

	/*
	*	@brief :		��ȡδ��Ȩ����ʱtoken
	*
	*	@param (IN)		xHandle							XLIVE_HANDLE
	*	@param (IN)		strOauthCallback				�ص�����(URL ),����Ϊ��(L"")
	*
	*	@param (OUT)	strOauthToken					δ��Ȩ��token
	*	@param (OUT)	strOauthTokenSecret				��Ӧsecret
	*	@param (OUT)	strOauthCallbackConfirmed		True/False��callback�Ƿ����
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_GetTempToken(
		XLIVE_HANDLE xHandle,
		BSTR bstrOauthCallback,
		BSTR* pbstrOauthToken,
		BSTR* pbstrOauthTokenSecret,
		BSTR* pbstrOauthCallbackConfirmed
		);


	/*
	*	@brief :		Ҫ���û�ת����ҳ�ϵ�¼���̲���Ȩ,��¼��ȡ��Verifier��
	*
	*	@param (IN)		bstrTempToken					XLIVE_GetTempToken�õ�����ʱtoken
	*
	*	@param (OUT)	pbstrVerifier					У����
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_GetAuthorize(
		BSTR bstrTempToken,
		BSTR* pbstrVerifier
		);


	/*
	*	@brief :		����ʱtoken��ȡaccess token
	*
	*	@param (IN)		xHandle							XLIVE_HANDLE
	*	@param (IN)		bstrTempToken					��ʱToken
	*	@param (IN)		bstrTempTokenSecret				��ʱTokenSecret
	*	@param (IN)		bstrVerifier					��վ��ȡ��У����
	*
	*	@return	�ο�����״̬����ֵ  
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
	*	@brief :		�鿴�û���Ϣ 
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*
	*	@param (OUT)	piUserId				��ʶ�û���Ψһid(��һ��������Чֵ)
	*	@param (OUT)	pbstrUserName			�û�����
	*	@param (OUT)	piMaxFileSize			�����ϴ�����ļ�
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_AccountInfo(
		XLIVE_HANDLE xHandle,
		INT* piUserId,
		BSTR* pbstrUserName,
		XUserExt* pUserExt
		);

	/**
	*	@brief ��ȡ�û������ռ��ʹ�õĿռ�
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE

	*	@param (OUT) plusedSize			��ʹ�õĿռ� (��λ: Byte)
	*	@param (OUT) pltotalSize		�û��ռ����� (��λ: Byte)
	*	@param (OUT) plrecycled			�û��ռ�Ļ���վ�ռ�ʹ���� (��λ: Byte)(��һ������ȷ��ֵ)
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_GetSpace(
		XLIVE_HANDLE xHandle,
		LONGLONG* plusedSize,
		LONGLONG* pltotalSize,
		LONGLONG* plrecycled);


	/**
	*	@brief 	�鿴�����ļ����ļ�����Ϣ
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrFileId			��־�ļ���Ψһid
	*
	*	@param (OUT) phFiles			�ļ����Ͼ�� 
	*
	*	@return	�ο�����״̬����ֵ    
	*/
	STDMETHODIMP XLIVE_Metadata(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		XLIVE_HFile* phFiles,
		BOOL bList);

	
	/**
	*	@brief ��������ɾ���ļ������ļ���
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrPath			��ɾ���ļ�·��
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Delete(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath
		);
	

	/**
	*	@brief �ƶ��ļ����ļ���
	*
	*	@param (IN)	xHandle				XLIVE_HANDLE
	*	@param (IN) bstrFileId			�ƶ�������ļ�Id
	*	@param (IN) bstrNewParentId		�ƶ�����Ŀ���ļ��е�Id
	*	@param (IN) bstrNewName			�ƶ�������ļ��������Դ�"",�Ͳ��������
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Move(
		XLIVE_HANDLE xHandle,
		BSTR bstrFromPath,
		BSTR bstrToPath);

	/**
	*	@brief ���������½��ļ���
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrParentID			��Ŀ¼ID,0Ϊ��Ŀ¼
	*	@param (IN)		bstrName				�ļ��е�����(utf8���룬���ܳ���255���ַ�,�����ھ���·������Ҳ���ܳ���255)
	*
	*	@param (OUT)	pbstrFileId				�½��ļ��е�ID
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_CreateFolder(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		BSTR* pbstrFileId);


	/**
	*	@brief �����ļ����ļ���
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				Ҫ���Ƶ��ļ���id
	*	@param (IN)		bstrParentID			Ŀ��Ŀ¼id��0Ϊ��Ŀ¼
	*	@param (IN)		bstrNewName				���ƺ�����ļ���(��NULL�������������ļ�,ʹ��ԭ�ļ���)
	*
	*	@param (OUT)	pbstrNewFileId			���ƺ�����ļ�ID
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Copy(
		XLIVE_HANDLE xHandle,
		BSTR bstrFromPath,
		BSTR bstrToPath,
		BSTR* pbstrFileId);


	/**
	*	@brief 	��ҳ������վ���ļ�����ʱû���⿪��
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		iPage					����0��Ĭ��ʹ�õ�1ҳ
	*	@param (IN)		iPageSize				ÿҳ�Ĵ�С��Ĭ��ʹ��20�����512
	*
	*	@param (OUT)	phFiles					���ص��ļ����ϵľ��
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Recycle(
		XLIVE_HANDLE xHandle,
		UINT iPage ,
		UINT iPageSize,
		XLIVE_HFiles* phFiles);


	/**
	*	@brief 	�����ض�Ŀ¼�µ�һ����Ŀ¼���ļ��б�����100000����֧�ַ�ҳ
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				Ŀ¼��id��0Ϊ��Ŀ¼	
	*	@param (IN)		iFilterType				Ĭ��0��0Ϊ��ʾȫ������,1Ϊֻ��ʾ�ļ���2Ϊֻ��ʾĿ¼
	*	@param (IN)		iPage					Ĭ��0��Ϊ0��ʱ����ʾȫ�����ݣ���ҳ����page_sizeһ��ʹ�ã���ʾ��pageҳ������
	*	@param (IN)		iPageSize				Ĭ��0�����512��ÿҳ������������
	*
	*	@param (OUT)	phFiles					���ص��ļ����ϵľ��
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_EnumFiles(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileId,
		UINT iFilterType,
		INT iPage,
		INT iPageSize,
		XLIVE_HFiles* phFiles);


	/**
	*	@brief �ָ�����վָ���ļ���ָ���ļ��У��������Զ����(n)��1<=n<=20
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				�ļ�id
	*	@param (IN)		bstrParentId			ָ���ļ���Id��0Ϊ��Ŀ¼	
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Recover(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileId,
		BSTR bstrParentId);

	
	/**
	*	@brief ��ջ���վ���ļ�
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileIds				�ļ�id��0�����ȫ������վ�ļ�
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_CleanRecycle(
		XLIVE_HANDLE xHandle,
		BSTR bstrFileIds);

	/**
	*	@brief ��������ȡһ���ļ��ĵķ������ӡ������������ļ��������ˡ�
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				�ļ�id
	*	@param (IN)		bstrName				����������
	*	@param (IN)		iExpired				����������0Ϊ������
	*
	*	@param (OUT)	pbstrOutlinkUrl			����URL��ַ
	*	@param (OUT)	pbstrStatus				����״̬��CREATE��READY��PROCESSING��WAITING(��һ����Ч����)
	*	@param (OUT)	pbstrOutlinkId			����id(��һ����Ч����)
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_Shares(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		BSTR bstrName,
		BSTR bstrAccessCode,
		BSTR* pbstrOutlinkUrl,
		BSTR* pbstrAccessCode);


	/**
	*	@brief ɾ������
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrOutlinkId			����id
	*
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_DeleteShares(
		XLIVE_HANDLE xHandle,
		BSTR bstrOutlinkId);


	/**
	*	@brief �鿴�ļ�����ʷ�汾
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				Ҫ��ѯ���ļ�id�������޸Ĺ����ļ�������ʷ�汾
	*
	*	@param (OUT)	phFiles					���ص��ļ��������ʷ�汾ֻ���������ԣ��ļ�id���޸�ʱ����ļ��汾�ţ�
	*	@return	�ο�����״̬����ֵ  
	*/
	STDMETHODIMP XLIVE_History(
		XLIVE_HANDLE xHandle,
		BSTR bstrPath,
		XLIVE_HFiles* phFiles);

	//---------------------------------------------------------

	/**
	*	@brief : �ϴ��ļ�(ע�⣺ȷ���ļ���·�����ļ��Ǵ��ڵ�)
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN):	bstrParentId				��Ŀ¼Id
	*	@param (IN):	bstrName					�ļ���	(�� "test.txt")
	*	@param (IN):	bstrFilePath				�ļ�·�� (�� "D:\\testData\\uploadTest.txt")
	*	@param (IN):	bstrTempFolderPath			�ļ��ϴ���ʱ�ļ���·�� ("D:\\testData\\Temp")
	*	@param (IN):	hProgress					�ϴ����Ⱦ��
	*	
	*	@param (IN):	upCallBackFunc				�ϴ��ص�����,���ޣ�����ΪNULL.�ݶ��ӿ���void (*funcName)(void)
	*
	*	@param (OUT):	pbstrFileId					�ϴ����ļ���FileId
	*	@param (OUT):	pbstrFileVer				���ص��ļ��İ汾��
	*
	*	@return	�ο�����״̬����ֵ  
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
	*	@brief : �����첽�ϴ��ļ�(ע�⣺ȷ���ļ���·�����ļ��Ǵ��ڵ�)
	*	
	*	param (IN) :	copy�����̵߳ľ��
	*			
	*		�������߳����ϴ��ļ�
	*		���̴߳����ɹ����̷���XLIVE_OK����������ɹ��ϴ�
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
	*	@brief �ļ�����
	*
	*	@param (IN)		xHandle					XLIVE_HANDLE
	*	@param (IN)		bstrFileId				�����ص��ļ�Id
	*	@param (IN)		bstrLocalPath			�����ļ��ı���Ŀ¼(�� L"E:\\TestData\\downloadData.txt")
	*	@param (IN)		bstrTempFolderPath		��ʱĿ¼(�� L"D:\\testData\\Temp")
	*	@param (IN)		bstrFileVer				��ʷ�汾��,����("")��ʾ���ص�ǰ�汾
	*	@param (IN)		hProgress				���Ⱦ��
	*
	*	@return	�ο�����״̬����ֵ  
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
	*	@brief	: �����첽�����ļ�
	*
	*	�������߳��������ļ�
	*	���̴߳����ɹ����̷���XLIVE_OK�������������سɹ�
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
	*	@brif �����첽����
	**/
	unsigned int STDMETHODCALLTYPE threadAsyncPerform(PVOID pM);



	/**
	*	@brief ���鿴�ϴ������صĽ���
	*
	*	@param : hProgress	���Ⱦ��
	*	@param : pdTotal	�ϴ������ص��ܽ���
	*	@param ��pdNow		Ŀǰ�Ľ���
	*	@param : pdSpeed	�ϴ������صĽ���
	*
	*	@return
	*		@ �ɹ� S_OK
	*/
	STDMETHODIMP XLIVE_QueryProgress(XLIVE_HANDLE xHandle, double* pdTotal, double* pdNow, double* pdSpeed);


	/*
	*	@brief :	�첽��ѯ����
	*
	*	@param : filePath   ��ѯ�������ϴ�(����)�Ŀ����ļ�·��
	*	
	*	@return��
	*		@XLIVE_OK				: ��ѯ�ɹ�
	*		@XLIVE_INVALID_PARAM	: ����·�����󣬻����ϴ�(����)�����Ѿ����
	*/
	STDMETHODIMP XLIVE_QueryProgressByPath(BSTR filePath, double* pdTotal, double* pdNow, double* pdSpeed);


	/**
	*	@brief : ȡ���ϴ�����������
	*
	*	@param : ���Ⱦ��
	*
	*	@return
	*		@ �ɹ� S_OK
	*/
	STDMETHODIMP XLIVE_CancelTransport(XLIVE_HANDLE xHandle);


	/*
	*	@brief		: �����ļ�·��ȡ���ϴ�����������
	*	
	*	@param(IN)  : �ļ�·�����Կ���·��Ϊ׼
	*	
	*	@return		: 
			@XLIVE_OK			 : �ɹ� 	
			@XLIVE_INVALID_PARAM : ������ļ�·����������ϴ������أ������Ѿ����
	*/
	STDMETHODIMP XLIVE_CancelTransportByPath(BSTR filePath);

	/**
	*	@brief �����ļ����Ͼ��
	*
	*	@param (IN) hFiles	�ļ����Ͼ��
	*
	*/
	STDMETHODIMP_(void) XLIVE_DestoryFiles(XLIVE_HFiles hFiles);
	
	/**
	*	@brief ��ȡ�ļ��������ļ�������(�����ļ���)
	*
	*	@param (IN):	hFiles			�ļ����
	*
	*	@param (OUT):	fileNum			�ļ�(�����ļ���)����
	*
	*	@return	
	*		@ �����ļ����ϵ�����
	*/
	STDMETHODIMP_(void) XLIVE_GetFilesNum(XLIVE_HFiles hFiles, UINT* fileNum);

	STDMETHODIMP_(void) XLIVE_GetFolderPath(XLIVE_HFiles hFiles, BSTR* pbstrPath);

	STDMETHODIMP_(void) XLIVE_GetFolderHash(XLIVE_HFiles hFiles, BSTR* pbstrHash);

	/**
	*	@brief ��ȡ�ļ�����
	*
	*	@param (IN)		hFiles �ļ����Ͼ��, �����������
	*	@param (IN)		index ����ֵ����ʾ�ڼ����ļ������ܳ����ļ��������ֵ����Ŀ¼���ļ���ʱ��-1��ʾȡ�ļ��еĵ����ԣ� 
	
	*	@param (OUT):	fileType	�ļ�����(1��ʾ�ļ� 0��ʾ�ļ���)
	*	@return	
	*	@ �ļ����� 1��ʾ�ļ� 0��ʾ�ļ���
	*/
	STDMETHODIMP_(void) XLIVE_GetFileType(XLIVE_HFiles hFiles, UINT index, UINT* fileType);

	/*
	*	@param (IN)		index ����ֵ����ʾ�ڼ����ļ������ܳ����ļ��������ֵ����Ŀ¼���ļ���ʱ��-1��ʾȡ�ļ��еĵ����ԣ� 
	*/
	STDMETHODIMP_(void) XLIVE_GetFileCreateTime(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);
	STDMETHODIMP_(void) XLIVE_GetFileModifyTime(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);

	STDMETHODIMP_(void) XLIVE_GetFileName(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrHash);
	STDMETHODIMP_(void) XLIVE_GetFileRev(XLIVE_HFiles hFiles, UINT index, BSTR* pbstrRev);
	STDMETHODIMP_(void) XLIVE_GetFileIsDeleted(XLIVE_HFiles hFiles, UINT index, BOOL* pbIsDeleted);

	STDMETHODIMP_(void) XLIVE_GetFileId(XLIVE_HFiles hFiles, UINT index, BSTR* pbIsDeleted);

	STDMETHODIMP_(void) XLIVE_GetFileSize(XLIVE_HFiles hFiles, UINT index, ULONG* plSzie);

	//�����ṩʹ��
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

	//�����ṩʹ��
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
	// ��ģ�嶨�ƽӿ�
	STDMETHODIMP XLIVE_RegisterAppPrevileges(BSTR strToken, BSTR strAppNo, BSTR strUserName, BSTR strKey);
	STDMETHODIMP XLIVE_GetAllContact(BSTR strToken, BSTR* pstrResult);
	STDMETHODIMP XLIVE_SendFile2Users(BSTR strToken, BSTR strFileId, BSTR strUserNames, BSTR strDestPath, BSTR* bstrResult);

#ifdef __cplusplus
}
#endif

#endif