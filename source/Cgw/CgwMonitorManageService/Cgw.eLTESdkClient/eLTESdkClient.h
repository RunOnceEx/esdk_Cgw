//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��OperationProxy.h
//	��  ��	��w00206574
//	������ڣ�2014-04-08
//	˵  ��	��ʵ��eLTE�ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================

#ifndef _OperationProxy_H
#define _OperationProxy_H
#pragma  once

#include "TDDisplayMnager.h"
#include "eLTE_Types.h"

using namespace CgwMonitorManage::Common;
using namespace System;
using namespace System::Collections::Generic;

namespace CgwMonitorManage
{
	namespace eLTE
	{	
		//�������ؽ��
	   public enum eLTE_RESULT
		{
		     RET_FAILURE                 = -1,	//ʧ��
			 RET_SUCCESS                 = 0,	//�ɹ�
			 RET_PARSE_XML_FAILURE       = 1,   //����xmlʧ��
		};
	   [Serializable]
	   public ref class eLTESdkClient
		{
		   public:
			   eLTESdkClient();

			   ~eLTESdkClient();

			   ELTE_INT32 GetUserInfo(int userid,[System::Runtime::InteropServices::Out]eLTEUserInfo^% userInfo);

			   ELTE_INT32 GetGroupUsers(int grpid,[System::Runtime::InteropServices::Out]List<eLTEGrpUserInfo^>^% groupUserList);

			   ELTE_INT32  GetAllGroups(int proviId,[System::Runtime::InteropServices::Out]List<eLTEGroupInfo^>^% groupList);

			   ELTE_INT32 Set_Login_Info(String^ CSserverIP,String^ CSlocalIP,String^ CSuserName,String^ CSpassWord,String^ CSsipPort,int CSDCID);

			   ELTE_INT32 GetAllDcUsers(int grpid,[System::Runtime::InteropServices::Out]List<eLTEUserInfo^>^% dcUsersList);

			   ELTE_INT32 SDK_START();

			   ELTE_INT32 SDK_STOP();

			   ELTE_INT32 App_Login(bool bLogin);

			   ELTE_INT32 StartP2PVideoMonitor(int mobileid,const eLTEVideoParameter^ videoPara);

			   ELTE_INT32 StopP2PVideo(int mobileid);

			   ELTE_INT32 PTZControl(int mobileid,unsigned int ptz_control_code,unsigned int ptz_control_value);

			   ELTE_INT32 TriggerStatusReport(bool bEnableStatusReport);

			private:
				//�밴�Լ��Ľӿڷ����޸�bypassMedia
				bool bypassMedia;
				//�밴�Լ������������޸����µĶ���
				String^ serverIP;
				String^ localIP;
				String^ userName;
				String^ passWord;
				String^ sipPort;
				int DCID;
		};
	}
}

#endif