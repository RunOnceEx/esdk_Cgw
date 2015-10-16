//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��OperationProxy.cpp
//	��  ��	��w00206574
//	������ڣ�2014-04-08
//	˵  ��	��ʵ��eLTE�ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================
#include "StdAfx.h"
#include <tchar.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>

#include "eLTESdkClient.h"
#include "eLTE_SDK.h"
#include "process_xml.h"
#include "securec.h"

#define STR_LENGTH_SIZE  20
#define INT_FORMAT_D	 10
#define WAIT_OBJECT_TIME 5000 

using namespace std;

namespace CgwMonitorManage
{
	namespace eLTE
	{	
		//������IP
		char cServerIP[50] = {0};
		//�û���
		char cUserName[50] = {0};
		//sip�˿�
		char cSipPort[50] = {0};
		//����IP 
		char cLocalIP[50] = {0};
		//�û�����
		char cPassWord[50] = {0};

		//===================================================================
		//	�������ƣ�	
		//	����������	ʵ��wchar_t��std::string��ת
		//	�����嵥��
		//	�����嵥��
		//	���������wchar_t str	--	[in] wchar_t
		//	���������  
		//	  ����ֵ�� std::string   -- [out]  std::string�ַ���
		//	����˵����
		//===================================================================
		string WSToString(const std::wstring& ws)
		{
			std::string curLocale = setlocale(LC_ALL, NULL);
			setlocale(LC_ALL, "chs");
			const wchar_t* _Source = ws.c_str();
			size_t _Dsize = 2 * ws.size() + 1;
			char *_Dest = new char[_Dsize];
			memset_s(_Dest,_Dsize,0,_Dsize);
			wcstombs(_Dest,_Source,_Dsize);
			string result = _Dest;
			delete []_Dest;
			setlocale(LC_ALL, curLocale.c_str());
			return result;
		}

		// int ת��Ϊ std::string
		std::string Int2String(int iVar)
		{
			char buf[STR_LENGTH_SIZE] = {0};
			(void)_itoa_s(iVar, buf, INT_FORMAT_D);
			return std::string(buf);
		}

		string ANSIToUnicode(const std::string& str)
		{
			string strResult("");

			int textlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
			if (0 >= textlen)
			{
				// MultiByteToWideChar failed.
				return strResult;
			}

			size_t bufsize = (size_t)(textlen+1);
			wchar_t* pBuf = new wchar_t[bufsize];

			memset_s(pBuf,sizeof(wchar_t)*bufsize,0,sizeof(wchar_t)*bufsize);
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pBuf, textlen);//lint !e713

			wstring  rt = pBuf;
			//ʵ��wchar_t��std::string��ת
			strResult= WSToString(rt);
			delete[] pBuf;

			return strResult;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	ʵ��UTF-8�����Unicode���뻥ת
		//	�����嵥��
		//	�����嵥��
		//	���������	str	--	[in] utf_8
		//	���������  
		//	  ����ֵ��  wstring  -- [out]  Unicode�����ַ���
		//	����˵����
		//===================================================================
		string UTF8ToUnicode(string str)
		{
			int  ilen = str.length();
			int  iUnicodeLen = ::MultiByteToWideChar( CP_UTF8,
				0,
				str.c_str(),
				-1,
				NULL,
				0 ); 
			wchar_t*  pUnicode = new  wchar_t[iUnicodeLen+1];

			memset_s(pUnicode,(iUnicodeLen+1)*sizeof(wchar_t),0,(iUnicodeLen+1)*sizeof(wchar_t));
			MultiByteToWideChar( CP_UTF8,
				0,
				str.c_str(),
				-1,
				(LPWSTR)pUnicode,
				iUnicodeLen ); 

			wstring  rt = ( wchar_t* )pUnicode;
		   //ʵ��wchar_t��std::string��ת
			string strRet= WSToString(rt);

			if(pUnicode)
			{
				delete[] pUnicode;
				pUnicode=NULL;
			}
			
			return  strRet; 
		}

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
 
			memset_s(wBuf,(wlen+1)*sizeof(wchar_t),0,(wlen+1)*sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 
				0, 
				(const char*)buffer, 
				int(len), 
				wBuf, 
				int(wlen));
			return wBuf;
		} 

		//===================================================================
		//	�������ƣ�	
		//	����������	��managed stringת����native ansi string
		//	�����嵥��
		//	�����嵥��
		//	���������	nSrcString	--	[in]	 Managed String
		//	���������  mDestString -- [out]   Native char�����ַ���
		//	  ����ֵ��
		//	����˵���������Ŀ���ַ�����������Խ��
		//===================================================================
		bool operator << (OUT char* nDestString, IN String^ mSrcString)
		{
			if (NULL == nDestString || nullptr == mSrcString)
			{
				return false;
			}
			IntPtr ip = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(mSrcString);
			char* tempBuf = static_cast<char *>(ip.ToPointer());

			//����ʹ�÷��㣬nDestString�����ɵ����߱�֤�����ﴫ�ĳ��ȱ�֤����������Դ�ַ�����
			strcpy_s(nDestString,strlen(tempBuf)+1,tempBuf);

			System::Runtime::InteropServices::Marshal::FreeHGlobal(ip);
			return true;
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
			mDestString = System::Runtime::InteropServices::Marshal::PtrToStringAnsi(static_cast<IntPtr>(nSrcString));
			return true;
		}

		ELTE_VOID __SDK_CALL EventCallBackFunc(ELTE_INT32 iEventType, ELTE_VOID* pEventBuf, ELTE_UINT32 uiBufSize, ELTE_VOID* pUserData)
		{
			if(NULL != pUserData)
			{
				TDDisplayMnager* displayMnager = (TDDisplayMnager*)pUserData;
				string strEventBuf = "";
				if (NULL != pEventBuf)
				{
					ELTE_CHAR* pBuf = NULL;
					SAFE_NEW_A(pBuf, ELTE_CHAR, uiBufSize + 1);
					
					memset_s(pBuf,uiBufSize+1,0x00,uiBufSize+1);
					
					memcpy_s(pBuf,uiBufSize+1,pEventBuf,uiBufSize);
					strEventBuf = pBuf;
					SAFE_DELETE_A(pBuf)
				}
				switch(iEventType)
				{
				case ELTE_Event_NotifyProvisionAllResync:
					{
						displayMnager->notifyProvisionAllResync();
					}
					break;	
				case ELTE_Event_NotifyResourceStatus:
					{						
						displayMnager->notifyResourceStatus(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyUserStatus:
					{						
						displayMnager->notifyUserStatus(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyProvisionChange:
					{						
						displayMnager->notifyProvisionChange(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyModuleStatus:
					{						
						displayMnager->notifyModuleStatus(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyP2pvideocallStatus:
					{						
						displayMnager->notifyP2pvideocallStatus(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyP2pcallStatus:
					{						
						displayMnager->notifyP2pcallStatus(strEventBuf);
					}
					break;
				case ELTE_Event_NotifyGroupStatus:
					{						
						displayMnager->notifyGroupStatus(strEventBuf);
					}
					break;
				default:
					{
					}
				}
			}
		}

		//===================================================================
		//	�������ƣ�eLTESdkClient
		//	�������������캯��
		//	�����嵥��NA
		//	�����嵥��OperationProxy.cpp
		//	���������NA
		//	���������NA
		//	  ����ֵ��NA
		//	����˵����
		//===================================================================
		eLTESdkClient::eLTESdkClient():bypassMedia(true)
		{
	
		}

		eLTESdkClient::~eLTESdkClient()
		{
			try
			{
				GC::Collect();
			}
			catch (...)
			{
			}	
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	��ȡһ���û�����ϸ��Ϣ�����ĺ�����������������������ֵ�Լ���ز���
		//	�����嵥��
		//	�����嵥��
		//	���������	userid	--	[in]	�û�ID
		//	���������  userInfo  -- [out]   �û���Ϣ�ṹ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: GetUserInfo(int userid,[System::Runtime::InteropServices::Out]eLTEUserInfo^% userInfo)
		{
			userInfo = gcnew eLTEUserInfo();

			//�ӿڵ���
			string strUserId = Int2String(userid);
			ELTE_CHAR* pUserInfo = NULL;
			ELTE_INT32 iRet = ELTE_SDK_GetUserInfo(strUserId.c_str(), &pUserInfo);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			//xml ����
			CXml rspXml;
			if(!rspXml.Parse(pUserInfo))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElemEx("Content/UserInfo"))
			{
				return RET_PARSE_XML_FAILURE;
			}
			if(!rspXml.FindElem("UserID"))
			{
				return RET_PARSE_XML_FAILURE;
			}
			userInfo->userid = atoi(rspXml.GetElemValue());
			if(!rspXml.FindElem("UserName"))
			{
				return RET_PARSE_XML_FAILURE;
			}
			userInfo->username = String(ANSIToUnicode(rspXml.GetElemValue()).c_str()).ToString();
			if(!rspXml.FindElem("UserCategory"))
			{
				return RET_PARSE_XML_FAILURE;
			}
			userInfo->usercategory = (eLTEUser_Category_t)(atoi(rspXml.GetElemValue()));

			//�ͷ��ڴ�
			iRet = ELTE_SDK_ReleaseBuffer(pUserInfo);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	���ĳ�����������User������ֵΪһ�ݿ�¡�����ݣ��ɵ����߸�����ݲ���������
		//	�����嵥��
		//	�����嵥��
		//	���������	grpid	--	[in]	�û�����ID
		//	���������  groupUserList  -- [out]   �û��б�
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: GetGroupUsers(int grpid,[System::Runtime::InteropServices::Out]List<eLTEGrpUserInfo^>^% groupUserList)
		{
			groupUserList = gcnew List<eLTEGrpUserInfo^>();

			//�ӿڵ���
			string strGrpId = Int2String(grpid);
			ELTE_CHAR* pGroupUsers = NULL;
			ELTE_INT32 iRet = ELTE_SDK_GetGroupUsers(strGrpId.c_str(), &pGroupUsers);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			//xml ����
			CXml rspXml;
			if(!rspXml.Parse(pGroupUsers))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElemEx("Content/GroupUserInfoList"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElem("GroupUserInfo"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			do 
			{
				if(rspXml.IntoElem())
				{
					//C#���ݽṹ����C++�����ݽṹת��C#�����ݽṹ
					eLTEGrpUserInfo^ groupUser = gcnew eLTEGrpUserInfo();
					if(!rspXml.FindElem("GroupID"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					groupUser->grpid = atoi(rspXml.GetElemValue());
					if(!rspXml.FindElem("MemberType"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					groupUser->memberType = (eLTEGroup_Member_t)(atoi(rspXml.GetElemValue()));
					if(!rspXml.FindElem("UserID"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					groupUser->userid = atoi(rspXml.GetElemValue());

					groupUserList->Add(groupUser);
					(void)rspXml.OutOfElem();
				}
			} while (rspXml.NextElem());

			//�ͷ��ڴ�
			iRet = ELTE_SDK_ReleaseBuffer(pGroupUsers);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			return RET_SUCCESS;
		}
		
		//===================================================================
		//	�������ƣ�	
		//	����������	��ñ�DC���������User(����fixeduser����)������ֵΪһ�ݿ�¡�����ݣ��ɵ����߸�����ݲ���������
		//	�����嵥��
		//	�����嵥��
		//	���������	proviId	--	[in]	����̨���û���
		//	���������  groupList  -- [out]   ��ȡ����̨��Ϊ��Ա��Ⱥ����б����ޣ��򷵻�NULL
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: GetAllGroups(int proviId,[System::Runtime::InteropServices::Out]List<eLTEGroupInfo^>^% groupList)
		{
			groupList = gcnew List<eLTEGroupInfo^>();

			//�ӿڵ���
			string strProviId = Int2String(proviId);
			ELTE_CHAR* pAllGroups = NULL;
			ELTE_INT32 iRet = ELTE_SDK_GetDcGroups(strProviId.c_str(), &pAllGroups);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			//xml ����
			CXml rspXml;
			if(!rspXml.Parse(pAllGroups))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElemEx("Content/GroupInfoList"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElem("GroupInfo"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			do 
			{
				if(rspXml.IntoElem())
				{
					//C#���ݽṹ����C++�����ݽṹת��C#�����ݽṹ
					eLTEGroupInfo^ groupInfo = gcnew eLTEGroupInfo();
					if(!rspXml.FindElem("GroupID"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					groupInfo->grpid = atoi(rspXml.GetElemValue());
					if(!rspXml.FindElem("GroupName"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					groupInfo->grpname = String(ANSIToUnicode(rspXml.GetElemValue()).c_str()).ToString();

					groupList->Add(groupInfo);
					(void)rspXml.OutOfElem();
				}
			} while (rspXml.NextElem());

			//�ͷ��ڴ�
			iRet = ELTE_SDK_ReleaseBuffer(pAllGroups);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	
		//	����������	��ñ�DC���������User (����fixeduser ����)�� ����ֵΪһ�ݿ�¡�����ݣ��ɵ����߸�����ݲ���������
		//	�����嵥��
		//	�����嵥��
		//	���������	grpid	--	[in]	������̨���û���; ��� Dcid==0���򷵻�ȫ�����е�User
		//	���������  groupUserList  -- [out]   �û��б�
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: GetAllDcUsers(int grpid,[System::Runtime::InteropServices::Out]List<eLTEUserInfo^>^% dcUsersList)
		{
			dcUsersList = gcnew List<eLTEUserInfo^>();

			//�ӿڵ���
			string strGrpId = Int2String(grpid);
			ELTE_CHAR* pAllDcUsers = NULL;
			ELTE_INT32 iRet = ELTE_SDK_GetDcUsers(strGrpId.c_str(), &pAllDcUsers);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			//xml ����
			CXml rspXml;
			if(!rspXml.Parse(pAllDcUsers))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElemEx("Content/UserInfoList"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			if(!rspXml.FindElem("UserInfo"))
			{
				return RET_PARSE_XML_FAILURE;
			}

			do 
			{
				if(rspXml.IntoElem())
				{
					//C#���ݽṹ����C++�����ݽṹת��C#�����ݽṹ
					eLTEUserInfo^ userInfo = gcnew eLTEUserInfo();
				
					if(!rspXml.FindElem("UserID"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					userInfo->userid = atoi(rspXml.GetElemValue());
					if(!rspXml.FindElem("UserName"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					userInfo->username = String(ANSIToUnicode(rspXml.GetElemValue()).c_str()).ToString();
					if(!rspXml.FindElem("UserCategory"))
					{
						return RET_PARSE_XML_FAILURE;
					}
					userInfo->usercategory = (eLTEUser_Category_t)(atoi(rspXml.GetElemValue()));

					dcUsersList->Add(userInfo);
					(void)rspXml.OutOfElem();
				}
			} while (rspXml.NextElem());

			//�ͷ��ڴ�
			iRet = ELTE_SDK_ReleaseBuffer(pAllDcUsers);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	Set_Login_Info
		//	����������	���õ�¼������IP������IP���û��������롢sip�˿ڵ���Ϣ
		//	�����嵥��
		//	�����嵥��
		//	���������	������IP������IP���û��������롢sip�˿�
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: Set_Login_Info(String^ CSserverIP,String^ CSlocalIP,String^ CSuserName,String^ CSpassWord,String^ CSsipPort,int CSDCID)
		{
			try
			{	
				this->serverIP=CSserverIP;
				this->localIP=CSlocalIP;
				this->userName=CSuserName;
				this->passWord=CSpassWord;
				this->sipPort=CSsipPort;
				this->DCID=CSDCID;

				cServerIP<<this->serverIP;
				cUserName<<this->userName;
				cPassWord<<this->passWord;
				cSipPort<<this->sipPort;
				cLocalIP<<this->localIP;
			}
			catch (...)
			{
				return RET_FAILURE;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	App_Login
		//	����������	��¼��ע��SDK 
		//	�����嵥��
		//	�����嵥��
		//	���������	bLogin��true��ʵע��
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient::App_Login(bool bLogin)
		{
			if(bLogin)
			{
				ELTE_INT32 iRet = ELTE_SDK_Login(cUserName, cPassWord, cServerIP, cLocalIP, atoi(cSipPort));
				if(RET_SUCCESS != iRet)
				{
					return iRet;
				}
				else
				{
					TDDisplayMnager::Instance().SetResID(cUserName);
					return RET_SUCCESS;
				}
			}
			else
			{
				ELTE_INT32 iRet = ELTE_SDK_Logout(cUserName);
				if(RET_SUCCESS != iRet)
				{
					return iRet;
				}
				else
				{
					return RET_SUCCESS;
				}
			}
		}

		//===================================================================
		//	�������ƣ�	SDK_START
		//	����������	��ʼ�������ģ�����SDK 
		//	�����嵥��
		//	�����嵥��
		//	���������	
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//==================================================================
		ELTE_INT32 eLTESdkClient::SDK_START ()
		{
			//��ȡ��ǰ����Ŀ¼
			wchar_t szCurrentDir[MAX_PATH] = {0};
			GetCurrentDirectory(MAX_PATH, szCurrentDir);
			//��ȡ����·��
			TCHAR szModuleFilePath[MAX_PATH];    
			GetModuleFileName(NULL, szModuleFilePath, MAX_PATH );

			string  strModuleFilePath = TCHAR2STRING(szModuleFilePath);
			strModuleFilePath = strModuleFilePath.substr(0,strModuleFilePath.find_last_of("\\"));

			TCHAR* szBasePath =CHAR2WCHAR(strModuleFilePath.c_str());

			TCHAR szSDKPath[MAX_PATH] = L"\\eLTeSDK\\";    
			TCHAR szAllPath[MAX_PATH];    
			_stprintf(szAllPath,_T("%s%s"),szBasePath, szSDKPath); 

			delete[] szBasePath;
			szBasePath=NULL;

			//����DLL·��
			SetCurrentDirectory(szAllPath);
			SetCurrentDirectory(szCurrentDir);

			
			static bool InitSucc=false;
			if(InitSucc)
			{
				ELTE_SDK_Cleanup();
				Sleep(3000);
				InitSucc=false;
			}

			ELTE_INT32 iRet = ELTE_SDK_SetLogPath("eLTeSDK\\log");
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			
			iRet = ELTE_SDK_Init();
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			InitSucc=true;
			
			iRet = ELTE_SDK_SetEventCallBack(EventCallBackFunc, &TDDisplayMnager::Instance());
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}

			// ��¼
			iRet = App_Login(true);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			::ResetEvent(TDDisplayMnager::Instance().GetLoginEventHandle());
			iRet = (ELTE_INT32)::WaitForSingleObject(TDDisplayMnager::Instance().GetLoginEventHandle(), (ELTE_INT32)WAIT_OBJECT_TIME);
			if (RET_SUCCESS != iRet)
			{
				return iRet;
			}

			/*	iRet = ELTE_SDK_ProvisionManagerInit(cServerIP, cUserName);
			if(RET_SUCCESS != iRet)
			{
			return iRet;
			}*/
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	TriggerStatusReport
		//	����������	����״̬�ϱ� 
		//	�����嵥��
		//	�����嵥��
		//	���������	True����ʼ״̬�ϱ���False���ر�״̬�ϱ�
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient::TriggerStatusReport(bool bEnableStatusReport)
		{
			ELTE_INT32 iRet = ELTE_SDK_TriggerStatusReport(bEnableStatusReport);
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	SDK_STOP
		//	����������	֪ͨSDKֹͣ����ҵ�� 
		//	�����嵥��
		//	�����嵥��
		//	���������	
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: SDK_STOP()
		{
			ELTE_INT32 iRet = ELTE_SDK_SetEventCallBack(NULL, NULL);
			if (RET_SUCCESS != iRet)
			{   
				return iRet;
			}

			iRet = ELTE_SDK_ProvisionManagerExit();
			if (RET_SUCCESS != iRet)
			{   
				return iRet;
			}

			iRet = App_Login(false);
			if (RET_SUCCESS != iRet)
			{   
				return iRet;
			}

			iRet = ELTE_SDK_Cleanup();
			if (RET_SUCCESS != iRet)
			{   
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	StartP2PVideoMonitor
		//	����������	����̨������Ƶ�ش� 
		//	�����嵥��
		//	�����嵥��  mobileid
		//	���������	
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: StartP2PVideoMonitor(int mobileid,const eLTEVideoParameter^ videoPara)
		{
			//�ӿڵ���
			string strMobileId = Int2String(mobileid);
			string strVideoParam;
			strVideoParam.append("<Content><VideoParam><VideoFormat>");
			strVideoParam.append((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(videoPara->fmtvalue));
			strVideoParam.append("</VideoFormat>");
			strVideoParam.append("<CameraType>");
			strVideoParam.append((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(videoPara->cameratype));
			strVideoParam.append("</CameraType>");
			strVideoParam.append("<UserConfirmType>");
			strVideoParam.append((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(videoPara->user_confirm_type));
			strVideoParam.append("</UserConfirmType>");
			strVideoParam.append("<MuteType>");
			strVideoParam.append((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(videoPara->mutetype));
			strVideoParam.append("</MuteType>");
			strVideoParam.append("</VideoParam></Content>");

			ELTE_INT32 iRet = ELTE_SDK_StartRealPlay(strMobileId.c_str(), strVideoParam.c_str());
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	PTZControl
		//	����������	��ʼ��̨���� 
		//	�����嵥��
		//	�����嵥��
		//	���������	�ƶ��ն˱��롢��̨����������Ʋ���
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: PTZControl(int mobileid,unsigned int ptz_control_code,unsigned int ptz_control_value)
		{
			//�ӿڵ���
			string strMobileId = Int2String(mobileid);
			ELTE_INT32 iRet = ELTE_SDK_PTZControl(strMobileId.c_str(), ptz_control_code, ptz_control_value);
			if (RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}

		//===================================================================
		//	�������ƣ�	StopP2PVideo
		//	����������	����̨�Ҷ���Ƶ�������Ƶ�ش� 
		//	�����嵥��
		//	�����嵥��
		//	���������	
		//	���������  ��
		//	  ����ֵ��
		//	����˵����	
		//===================================================================
		ELTE_INT32 eLTESdkClient:: StopP2PVideo(int mobileid)
		{
			//�ӿڵ���
			string strMobileId = Int2String(mobileid);
			ELTE_INT32 iRet =  ELTE_SDK_StopRealPlay(strMobileId.c_str());
			if(RET_SUCCESS != iRet)
			{
				return iRet;
			}
			return RET_SUCCESS;
		}
	 }
 }