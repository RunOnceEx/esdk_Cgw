//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��IvsSdkClient.h
//	��  ��	��lkf70422
//	��  ��	��V100R002C03
//	������ڣ�2013-04-7
//	˵  ��	��IVS SDK �ͻ��˽ӿ�ʵ�֣�����SDK�ӿڣ�ʵ�ֿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================
#include "hwsdk.h"
#include "IvsSdkClient.h"
#include "ivs_error.h"
#include <string>
#include "securec.h"

using namespace std;

namespace CgwMonitorManage
{

	namespace Ivs
	{
		//===================================================================
		//	�������ƣ�	
		//	����������	ʵ��string�����TCHAR���뻥ת
		//	�����嵥��
		//	�����嵥��
		//	���������	str	--	[in] TCHAR
		//	���������  
		//	  ����ֵ��  wstring  -- [out]  TCHAR�����ַ���
		//	����˵����
		//===================================================================
		string TCHAR2STRING(TCHAR* szStr)
		{
			int iLen = WideCharToMultiByte(CP_ACP, 
				0,
				szStr, 
				-1,
				NULL, 
				0, 
				NULL, 
				NULL); 
			char* chRtn =new char[iLen*sizeof(char)]; 
			WideCharToMultiByte(CP_ACP, 
				0, 
				szStr,
				-1,
				chRtn, 
				iLen, 
				NULL, 
				NULL); 

			std::string str(chRtn);
			delete[] chRtn;
			chRtn =NULL;
			return str;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	ʵ��TCHAR�����char���뻥ת
		//	�����嵥��
		//	�����嵥��
		//	���������	const char *	--	[in] utf_8
		//	���������  
		//	  ����ֵ��  TCHAR  -- [out]  TCHAR�����ַ���
		//	����˵����
		//===================================================================
		TCHAR* CHAR2WCHAR(const char *buffer)
		{
			size_t len = strlen(buffer);
			size_t wlen = MultiByteToWideChar(CP_ACP, 
				0, 
				(const char*)buffer, 
				int(len), 
				NULL, 
				0);
			TCHAR* wBuf = new TCHAR[wlen + 1];

			memset_s(wBuf,wlen+1,0,(wlen+1)*sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 
				0, 
				(const char*)buffer, 
				int(len), 
				wBuf, 
				int(wlen));
			return wBuf;
		} 

		//===================================================================
		//	�������ƣ�IvsSdkClient
		//	�������������캯��
		//	�����嵥��NA
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ��NA
		//	����˵����
		//===================================================================
		IvsSdkClient::IvsSdkClient()
		{
			sessionId = -1;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	��managed stringת����native ansi string
		//	�����嵥��
		//	�����嵥��
		//	���������	nSrcString	--	[in]	 Managed String
		//	���������  mDestString  -- [out]   Native char�����ַ���
		//	  ����ֵ��
		//	����˵���������Ŀ���ַ�����������Խ��
		//===================================================================
		bool operator << (OUT IVS_CHAR* nDestString, IN String^ mSrcString)
		{
			if (NULL == nDestString || nullptr == mSrcString)
			{
				return false;
			}
			IntPtr ip = Marshal::StringToHGlobalAnsi(mSrcString);
			IVS_CHAR* tempBuf = static_cast<IVS_CHAR *>(ip.ToPointer());

			//����ʹ�÷��㣬nDestString�����ɵ����߱�֤�����ﴫ�ĳ��ȱ�֤����������Դ�ַ�����
			strcpy_s(nDestString,strlen(tempBuf)+1,tempBuf);

			Marshal::FreeHGlobal(ip);
			return true;
		}

		//ȫ�ֱ��������ƽ̨ID��Ĭ��ֵcgw
		//CString* localId=new CString("cgw");
		IVS_CHAR*  localId = new IVS_CHAR[IVS_DEV_CODE_LEN];
		void IvsSdkClient::SetId(String^ id)
		{
			memset_s(localId,sizeof(localId),0,IVS_DEV_CODE_LEN);
			localId<<id;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	��native ansi stringת����managed string
		//	�����嵥��
		//	�����嵥��
		//	���������	nSrcString	--	[in]	Native Char�����ַ���
		//	���������  mDestString  -- [out]   Managed String
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		bool operator << (OUT String^% mDestString, IN char* nSrcString)
		{			
			if (NULL == nSrcString)
			{
				return false;
			}
			mDestString = Marshal::PtrToStringAnsi(static_cast<IntPtr>(nSrcString));
			return true;
		}

		//===================================================================
		//	�������ƣ�CharToString
		//	������������IVS_CHAR������C#�ַ�������ԭָ������0����ֹ��ԭ���ݲ���0�������������ݴ���
		//	�����嵥��
		//	�����嵥��
		//	���������NA
		//	���������NA
		//	  ����ֵ�����ƺ���ַ���
		//	����˵����
		//===================================================================
		String^ CharToString(IVS_CHAR* nSrcString,int lenght)
		{			
			IVS_CHAR* charTemp=(IVS_CHAR*) malloc(lenght+1);

			memset_s(charTemp,lenght+1,0,lenght+1);

			memcpy_s(charTemp,lenght+1,nSrcString,lenght);
			String^ destString =  String(charTemp).ToString();

			delete charTemp;
			charTemp = NULL;

			return destString;
		}

		//===================================================================
		//	�������ƣ�SetLogPath
		//	����������������־��Ŀ¼
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::SetLogPath(String^ strLogPath)
		{
			IVS_CHAR psLogPath[IVS_FILE_NAME_LEN+1] = {0};

			psLogPath<<strLogPath;
			int result = IVS_SDK_SetLogPath(psLogPath);
			return result;
		}

		//===================================================================
		//	�������ƣ�Init
		//	������������ʼ��SDK
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::Init()
		{
			//int result = IVS_SDK_Cleanup();
			//��ȡ����·��
			wchar_t szCurrentDir[MAX_PATH] = {0};
			GetCurrentDirectory(MAX_PATH, szCurrentDir);
			TCHAR szModuleFilePath[MAX_PATH];    
			GetModuleFileName(NULL, szModuleFilePath, MAX_PATH );

			string  strModuleFilePath = TCHAR2STRING(szModuleFilePath);
			strModuleFilePath = strModuleFilePath.substr(0,strModuleFilePath.find_last_of("\\"));

			TCHAR* szBasePath =CHAR2WCHAR(strModuleFilePath.c_str());

			TCHAR szSDKPath[MAX_PATH] = L"\\IVSSDK\\";    
			TCHAR szAllPath[MAX_PATH];    
			_stprintf(szAllPath,_T("%s%s"),szBasePath, szSDKPath); 

			//����DLL·��
			SetCurrentDirectory(szAllPath);
			SetCurrentDirectory(szCurrentDir);

			delete[] szBasePath;
			szBasePath=NULL;

			int result = IVS_SDK_Init();	
			return result;
		}

		//===================================================================
		//	�������ƣ�Cleanup
		//	�����������ͷ�SDK��Դ
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::Cleanup()
		{
			int result = IVS_SDK_Cleanup();	
			return result;
		}

		//===================================================================
		//	�������ƣ�EventCallBack
		//	�����������¼��ص�����(�¼�֪ͨ���쳣�ص���)
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������iEventType			 �¼�����		  
		//	���������pEventBuf			pEventBuf
		//	���������uiBufSize			buf����
		//	���������pUserData			�û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
		//	  ����ֵ��
		//	����˵����
		//===================================================================
		IVS_VOID __SDK_CALL  EventCallBackFun(IVS_INT32  iEventType,IVS_VOID*  pEventBuf, IVS_UINT32  uiBufSize, IVS_VOID*   pUserData)
		{
			if (IVS_EVENT_USER_OFFLINE == iEventType||IVS_EVENT_LOGIN_FAILED ==iEventType)//�û�����֪ͨ������ʧ��
			{
				IVS_CHAR*   sdkId = (IVS_CHAR*  )pUserData;
				IvsUserOfflineOff^ ivsUserOfflineOff = gcnew IvsUserOfflineOff();

				IvsSdkClient::cgwEventCallBackFunc(iEventType,ivsUserOfflineOff,uiBufSize, String(sdkId).ToString());
			}
		}

		//===================================================================
		//	�������ƣ�Login
		//	������������½������
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������ip		ip��ַ
		//			  port		�˿�
		//			  user		�û�
		//			  password	����
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::Login(String^ ip, int port, String^ user, String^ password)
		{
			IVS_LOGIN_INFO* loginInfo = new IVS_LOGIN_INFO();

			loginInfo->stIP.cIP<<ip;
			loginInfo->stIP.uiIPType = IP_V4;
			loginInfo->uiPort=port;

			loginInfo->cUserName<<user;
			loginInfo->pPWD<<password;
			loginInfo->cMachineName<<System::Environment::MachineName;

			loginInfo->uiClientType = CLIENT_PC;
			loginInfo->uiLoginType = LOGIN_BASIC;
			IVS_INT32 sessionIdTemp;

			int result = IVS_SDK_Login(loginInfo, &sessionIdTemp);
			this->sessionId=sessionIdTemp;

			//���û����뱣�������������´�����
			this->ip=ip;
			this->password=password;
			this->port=port;
			this->user=user;

			delete loginInfo;
			loginInfo = NULL;

			EventCallBack fEventCallBack = &EventCallBackFun;
			IVS_SDK_SetEventCallBack(sessionIdTemp, fEventCallBack, NULL);

			return result;
		}

		//===================================================================
		//	�������ƣ�ReLogin
		//	���������������ϴε���Login�ӿ�ʹ�õĵ�¼��Ϣ�����µ�¼������
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::ReLogin()
		{
			int result = Login(this->ip,this->port,this->user,this->password);
			return result;
		}

		//===================================================================
		//	�������ƣ�Logout
		//	����������ע����½
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::Logout()
		{
			int result = IVS_SDK_Logout(sessionId);	
			return result;
		}

		//===================================================================
		//	�������ƣ�GetDeviceList
		//	��������������������ȡ�豸�б���ȡfromIndex��toIndex֮��ļ�¼
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������fromIndex			��ʼ����
		//			  toIndex			��������
		//	���������totalCameraCount  ��¼����
		//			  cameraList		����ͷ�б�
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::GetDeviceList(int fromIndex,int toIndex,[Out]int% totalCameraCount,[Out]List<IvsCamera^>^% cameraList)
		{
			cameraList = gcnew List<IvsCamera^>();

			//�����ڴ�ռ�
			IVS_UINT32 uiReqNum = (toIndex - fromIndex) + 1; 
			IVS_UINT32 uiRspBufferSize = 0;
			uiRspBufferSize = sizeof(IVS_CAMERA_BRIEF_INFO_LIST) + (uiReqNum-1)*sizeof(IVS_CAMERA_BRIEF_INFO);
			IVS_VOID *pRspBuffer = new IVS_CHAR[uiRspBufferSize]; 
			
			memset_s(pRspBuffer,uiRspBufferSize,0,uiRspBufferSize);

			IVS_INDEX_RANGE stRange;
			stRange.uiToIndex = toIndex;
			stRange.uiFromIndex = fromIndex;

			int result = IVS_SDK_GetDeviceList(sessionId,DEVICE_TYPE_CAMERA,&stRange,pRspBuffer,uiRspBufferSize);
			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();				
				
				memset_s(pRspBuffer,uiRspBufferSize,0,uiRspBufferSize);
				result = IVS_SDK_GetDeviceList(sessionId,DEVICE_TYPE_CAMERA,&stRange,pRspBuffer,uiRspBufferSize);
			}

			if (result != IVS_SUCCEED)
			{
				delete[] pRspBuffer;
				pRspBuffer = NULL;
				return result;
			}
			IVS_CAMERA_BRIEF_INFO_LIST *pRspDeviceList = (IVS_CAMERA_BRIEF_INFO_LIST*)pRspBuffer; 
			IVS_UINT32 iNum = (pRspDeviceList->stIndexRange.uiToIndex - pRspDeviceList->stIndexRange.uiFromIndex) + 1;
			if (0 == pRspDeviceList->uiTotal)
			{
				iNum = 0;
			}
			//ʵ�ʼ�¼��С�ڷ�ҳ������ѯ�ļ�¼����ʱ��ֻ����ʵ�ʵļ�¼��
			else if((pRspDeviceList->uiTotal - pRspDeviceList->stIndexRange.uiFromIndex + 1)<iNum ) 
			{				
				iNum = (pRspDeviceList->uiTotal - pRspDeviceList->stIndexRange.uiFromIndex) + 1;
			}
			totalCameraCount=pRspDeviceList->uiTotal;


			IVS_UINT32 i = 0;

			while (i < iNum)
			{
				IVS_CAMERA_BRIEF_INFO &devInfo = pRspDeviceList->stCameraBriefInfo[i];

				//C#���ݽṹ����C++�����ݽṹת��C#�����ݽṹ
				IvsCamera^ ivsCamera = gcnew IvsCamera();

				ivsCamera->Name = CharToString(devInfo.cName,IVS_CAMERA_NAME_LEN);
				ivsCamera->No = CharToString(devInfo.cCode,IVS_DEV_CODE_LEN);
				int typeTemp = devInfo.uiType;
				ivsCamera->Type = (IvsCameraType)typeTemp;
				ivsCamera->GroupNo = CharToString(devInfo.cDevGroupCode,IVS_DEVICE_GROUP_LEN);
				ivsCamera->ParentNo =  CharToString(devInfo.cParentCode,IVS_DEV_CODE_LEN);
				ivsCamera->DomainCode =CharToString(devInfo.cDomainCode,IVS_DOMAIN_CODE_LEN);
				if (DEV_STATUS_ONLINE == devInfo.uiStatus)
				{
					ivsCamera->Status = CameraStatus::Online;
				}else
				{
					ivsCamera->Status = CameraStatus::Offline;
				}

				cameraList->Add(ivsCamera);
				i++;
			}

			delete[] pRspBuffer;
			pRspBuffer = NULL;

			return result;
		}

		//===================================================================
		//	�������ƣ�GetDomainRoute
		//	������������ȡ���б�
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������NA
		//	���������domainRouteList	���б�
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::GetDomainRoute([Out]List<IvsDomainRoute^>^% domainRouteList)
		{
			domainRouteList = gcnew List<IvsDomainRoute^>();

			//Ŀǰ���֧��128��
			IVS_UINT32 uiReqNum = IVS_MAX_DOMAIN_ROUTE_NUM; 
			IVS_UINT32 uiBufferSize = sizeof(IVS_DOMAIN_ROUTE_LIST) + (uiReqNum-1)*sizeof(IVS_DOMAIN_ROUTE);
			IVS_DOMAIN_ROUTE_LIST *routeList =  (IVS_DOMAIN_ROUTE_LIST*)malloc(uiBufferSize);
			
			memset_s(routeList,uiBufferSize,0,uiBufferSize);

			int result = IVS_SDK_GetDomainRoute(sessionId,routeList,uiBufferSize);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				
				memset_s(routeList,uiBufferSize,0,uiBufferSize);
				result = IVS_SDK_GetDomainRoute(sessionId,routeList,uiBufferSize);
			}

			if (result!= IVS_SUCCEED)
			{
				//delete routeList;
				free(routeList);
				routeList = NULL;
				return result;
			}

			IVS_UINT32 i = 0;			
			while (i < routeList->uiTotal)
			{
				IVS_DOMAIN_ROUTE &domainRoute = routeList->stDomainRoute[i];

				IvsDomainRoute^ ivsDomainRoute = gcnew IvsDomainRoute();
				ivsDomainRoute->Ip = CharToString(domainRoute.stIP.cIP,IVS_IP_LEN);
				ivsDomainRoute->Port = domainRoute.uiPort;
				ivsDomainRoute->ParentDomain = CharToString(domainRoute.cSuperDomain,IVS_DOMAIN_CODE_LEN);
				ivsDomainRoute->DomainCode = CharToString(domainRoute.cDomainCode,IVS_DOMAIN_CODE_LEN);
				ivsDomainRoute->DomainName = CharToString(domainRoute.cDomainName,IVS_NAME_LEN);

				domainRouteList->Add(ivsDomainRoute);
				i++;
			}

			delete routeList;
			routeList = NULL;

			return result;
		}

		//===================================================================
		//	�������ƣ�GetDeviceGroupList
		//	������������ȡָ����ָ���ڵ��µ��������豸���б���Ϣ
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������domainCode			�����
		//			  rootGroupNo			���ڵ㣨��ĸ��ڵ�Ϊ0�������ѯ���µ����з��飬����0���ɣ�
		//	���������cameraGroupDic		�����б�Dictionary���ͣ�keyΪ���ţ�valueΪ������Ϣ����
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::GetDeviceGroupList(String^ domainCode,String^ rootGroupNo,[Out]Dictionary<String^,IvsCameraGroup^>^% cameraGroupDic)
		{
			cameraGroupDic = gcnew Dictionary<String^,IvsCameraGroup^>();
			IVS_UINT32 uiReqNum = IVS_MAX_DEV_GROUP_NUM; 
			IVS_UINT32 uiBufferSize = 0;
			uiBufferSize = sizeof(IVS_DEVICE_GROUP_LIST) + (uiReqNum-1)*sizeof(IVS_DEVICE_GROUP);
			IVS_DEVICE_GROUP_LIST *groupList = (IVS_DEVICE_GROUP_LIST*)malloc(uiBufferSize);
			
			memset_s(groupList,uiBufferSize,0,uiBufferSize);

			//IVS���ص�domainCode����Ϊ32λ�����һλ��Ϊ0����˵���ʱ������+1
			IVS_CHAR domain[IVS_DOMAIN_CODE_LEN+1];
			
			memset_s(domain,IVS_DOMAIN_CODE_LEN+1,0,IVS_DOMAIN_CODE_LEN+1);
			domain<<domainCode;

			IVS_CHAR rootGroupCode[IVS_DEVICE_GROUP_LEN+1];
			
			memset_s(rootGroupCode,IVS_DEVICE_GROUP_LEN+1,0,IVS_DEVICE_GROUP_LEN+1);
			rootGroupCode<<rootGroupNo;

			int result = IVS_SDK_GetDeviceGroup(sessionId,domain,rootGroupCode,groupList,uiBufferSize);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				//memset(groupList,0,uiBufferSize);
				memset_s(groupList,uiBufferSize,0,uiBufferSize);
				result = IVS_SDK_GetDeviceGroup(sessionId,domain,rootGroupCode,groupList,uiBufferSize);
			}

			if (result!= IVS_SUCCEED)
			{
				delete groupList;
				groupList = NULL;
				return result;
			}

			IVS_UINT32 i = 0;
			while (i < groupList->uiTotal)
			{
				IVS_DEVICE_GROUP &group = groupList->stDeviceGroup[i];
				IvsCameraGroup^ ivsCameraGroup = gcnew IvsCameraGroup();
				ivsCameraGroup->GroupNo = CharToString(group.cGroupCode,IVS_DEVICE_GROUP_LEN);
				ivsCameraGroup->GroupName = CharToString(group.cGroupName,IVS_NAME_LEN);
				ivsCameraGroup->DomainCode = domainCode;
				ivsCameraGroup->ParentGroupNo = CharToString(group.cParentGroupCode,IVS_DEVICE_GROUP_LEN);
				//������ⵥDTS2013080201001�������IVS��������������ͷ�ظ���bug�����ں������쳣������
				if (!cameraGroupDic->ContainsKey(ivsCameraGroup->GroupNo))
				{
					cameraGroupDic->Add(ivsCameraGroup->GroupNo,ivsCameraGroup);
				}
				i++;
			}

			delete groupList;
			groupList = NULL;

			return result;
		}

		//===================================================================
		//	�������ƣ�SetRealPlayCBRawCallBackFunc
		//	�������������������ص�����
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������callbackFunc			�����ص�����IvsRealPlayCallBackRawFunc		  
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		void IvsSdkClient::SetRealPlayCBRawCallBackFunc(IvsRealPlayCallBackRawFunc^ callbackFunc)
		{			
			cgwCallbackFunc=callbackFunc;
		}

		array<Byte>^ NativeArr2ManagedArrByte(BYTE* nByArr, unsigned int nArrLen)
		{
			array<Byte>^ mByArr = gcnew array<Byte>(nArrLen);
			if(NULL == nByArr)
			{
				return mByArr;
			}
			for(unsigned int i = 0; i < nArrLen; i++)
			{
				mByArr[i] = nByArr[i];
			}
			return mByArr;
		}

		//===================================================================
		//	�������ƣ�IvsRealPlayCallBackRaw
		//	���������������ص�����������SDK������
		//	�����嵥��IvsVideoMonitor.cs
		//	�����嵥��IVS_SDK
		//	���������callbackFunc			�����ص�����RealPlayCallBackRaw		  
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		IVS_VOID __SDK_CALL IvsRealPlayCallBackRaw(IVS_ULONG ulHandle, IVS_RAW_FRAME_INFO* pRawFrameInfo, IVS_VOID* pBuf, IVS_UINT32 uiBufSize, IVS_VOID* pUserData)
		{			
			IVS_CHAR*   sdkId = (IVS_CHAR*  )pUserData;
			if (0 != strcmp(localId,sdkId))
			{
				//���Ǹ�ƽ̨�Ļص�������
				return;
			}

			IVS_CHAR*  dataBuffer = (IVS_CHAR* )pBuf;
			array<Byte>^ buf = NativeArr2ManagedArrByte((BYTE*)dataBuffer,uiBufSize);

			IvsRawFrameInfo^ ivsRawFrameInfo = gcnew IvsRawFrameInfo();

			ivsRawFrameInfo->StreamType = pRawFrameInfo->uiStreamType;
			ivsRawFrameInfo->FrameType = pRawFrameInfo->uiFrameType;
			ivsRawFrameInfo->GopSequence = pRawFrameInfo->uiGopSequence;
			ivsRawFrameInfo->Height = pRawFrameInfo->uiHeight;
			ivsRawFrameInfo->TimeStamp = pRawFrameInfo->uiTimeStamp;
			ivsRawFrameInfo->WaterMarkValue = pRawFrameInfo->uiWaterMarkValue;
			ivsRawFrameInfo->Width = pRawFrameInfo->uiWidth;
			ivsRawFrameInfo->TimeTick = pRawFrameInfo->ullTimeTick;

			IvsSdkClient::cgwCallbackFunc(ulHandle,ivsRawFrameInfo,buf,uiBufSize, String(sdkId).ToString());

		}

		//===================================================================
		//	�������ƣ�StartRealPlayCBRaw
		//	��������������ʵ��Ԥ������ʼ��������
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������cameraNo			����ͷ���		  
		//	���������handle			���ž��
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::StartRealPlayCBRaw(String^ cameraNo,[Out]long%  handle)
		{

			IVS_CHAR pCameraCode[IVS_DEV_CODE_LEN];
			
			memset_s(pCameraCode,IVS_DEV_CODE_LEN,0,IVS_DEV_CODE_LEN);
			pCameraCode<<cameraNo;

			////2015/3/3 ��ȡ�豸���������ò������磺TCP��UDP
			//IntPtr ip = Marshal::StringToHGlobalAnsi(cameraNo);
			//IVS_CHAR* tempBuf = static_cast<IVS_CHAR *>(ip.ToPointer());

			//IVS_CAMERA_STREAM_CFG deviceInfo={0};
			//IVS_SDK_GetDeviceConfig(sessionId,tempBuf,CONFIG_CAMERA_STREAM_CFG,&deviceInfo,sizeof(deviceInfo));

			IVS_REALPLAY_PARAM  pRealplayPara;
			pRealplayPara.bDirectFirst = MEDIA_TRANS;                           //��ת��ö��IVS_MEDIA_TRANS_MODE    
			pRealplayPara.bMultiCast = BROADCAST_UNICAST;						//������ö��IVS_BROADCAST_TYPE
			pRealplayPara.uiProtocolType = PROTOCOL_RTP_OVER_UDP;				//UDPЭ�飬ö��IVS_PROTOCOL_TYPE
			pRealplayPara.uiStreamType = STREAM_TYPE_MAIN;						//��������ö��IVS_STREAM_TYPE

			/*	for(int i=0;i< deviceInfo.uiStreamInfoNum;i++)
			{
			if(deviceInfo.stStreamInfo[i].uiStreamType==STREAM_TYPE_MAIN)
			{
			pRealplayPara.uiProtocolType=deviceInfo.stStreamInfo[i].uiTransProtocol;
			break;
			}
			}*/

			RealPlayCallBackRaw ivsCallbackFunc = &IvsRealPlayCallBackRaw;
			IVS_ULONG iPlayHandle = 0;

			int result = IVS_SDK_StartRealPlayCBRaw(sessionId, &pRealplayPara, pCameraCode,ivsCallbackFunc, localId,&iPlayHandle);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				result = IVS_SDK_StartRealPlayCBRaw(sessionId, &pRealplayPara, pCameraCode,ivsCallbackFunc, localId,&iPlayHandle);
			}

			handle = iPlayHandle;

			return result;
		}

		//===================================================================
		//	�������ƣ�StopRealPlay
		//	����������ֹͣʵ����ֹͣ��������
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������handle			���ž��		  
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::StopRealPlay(long handle)
		{
			int result = IVS_SDK_StopRealPlay(sessionId,handle);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				result = IVS_SDK_StopRealPlay(sessionId,handle);
			}
			return result;
		}

		//===================================================================
		//	�������ƣ�StartPtzControl
		//	������������ʼptz����
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������cameraNo			����ͷ���
		//			  controlCode		��������
		//			  param				����������ٶȡ�������
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::StartPtzControl(String^ cameraNo,int controlCode,String^ param)
		{
			IVS_CHAR pCameraCode[IVS_DEV_CODE_LEN];
			
			memset_s(pCameraCode,IVS_DEV_CODE_LEN,0,IVS_DEV_CODE_LEN);
			pCameraCode<<cameraNo;

			IVS_CHAR pControlPara2[IVS_DEV_CODE_LEN];
			
			memset_s(pControlPara2,IVS_DEV_CODE_LEN,0,IVS_DEV_CODE_LEN);
			pControlPara2<<param;

			//��̨����״̬��0-������1-����
			IVS_UINT32 pLockStatus = 0;
			//ʹ������ģʽ�����ĸ�����2��ʾ����ģʽ
			int result = IVS_SDK_PtzControl(sessionId,pCameraCode, controlCode,"2",pControlPara2, &pLockStatus);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				result = IVS_SDK_PtzControl(sessionId,pCameraCode, controlCode,"2",pControlPara2, &pLockStatus);
			}

			return result;
		}

		//===================================================================
		//	�������ƣ�StopPtzControl
		//	����������ֹͣptz����
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������cameraNo			����ͷ���
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		int IvsSdkClient::StopPtzControl(String^ cameraNo)
		{
			IVS_CHAR pCameraCode[IVS_DEV_CODE_LEN];
			
			memset_s(pCameraCode,IVS_DEV_CODE_LEN,0,IVS_DEV_CODE_LEN);
			pCameraCode<<cameraNo;

			//��̨����״̬��0-������1-����
			IVS_UINT32 pLockStatus = 0;

			//PTZ_STOP����ö��IVS_PTZ_CODE,IVS��Ҫ�󣬵���ֹͣ����PTZ_STOPʱ��pControlPara1��pControlPara2���⴫,������ΪNULL
			int result = IVS_SDK_PtzControl(sessionId,pCameraCode,PTZ_STOP,"","", &pLockStatus);

			//�������Ϊ����Ч�ĻỰID���򡰵�¼��Ϣ��ʧЧ�������µ�¼���������µ�¼���ٴ�ִ�У���������
			if (result==IVS_MU_INVALID_SESSION_ID||result==IVS_SCU_ONLINE_USER_EXPIRE||result==IVS_SMU_USER_OFF_LINE||result==IVS_SDK_RET_INVALID_SESSION_ID)
			{
				//���µ�¼
				ReLogin();
				result = IVS_SDK_PtzControl(sessionId,pCameraCode,PTZ_STOP,"","", &pLockStatus);
			}

			return result;
		}

		//===================================================================
		//	�������ƣ�SetEventCallBackFunc
		//	�������������������ص�����
		//	�����嵥��IVS_SDK
		//	�����嵥��IvsVideoMonitor.cs
		//	���������callbackFun 
		//	���������NA
		//	  ����ֵ���ɹ�����0��ʧ�ܷ��ش�����
		//	����˵����
		//===================================================================
		void IvsSdkClient::SetEventCallBackFunc(IvsEventCallBackFunc^ callbackFunc)
		{			
			cgwEventCallBackFunc=callbackFunc;
		}
	}
}