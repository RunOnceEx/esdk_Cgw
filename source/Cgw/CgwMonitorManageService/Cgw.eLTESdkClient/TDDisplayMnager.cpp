//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��TDDisplayMnager.cpp
//	��  ��	��w00206574
//	������ڣ�2014-04-08
//	˵  ��	��ʵ��eLTE�ӿ�C++ ��C#֮��ת��,�¼�֪ͨ�ӿڣ�SDKͨ���ص��ýӿڷ������м��û�״̬�¼����ϲ�Ӧ��
//	��  ��	��
//	��ʷ��¼��
//===================================================================
#include "StdAfx.h"
#include "TDDisplayMnager.h"
#include "process_xml.h"
#include <Winsock2.h>

using namespace std;

#pragma comment(linker, "/EXPORT:SetGrpStaCallBack=_SetGrpStaCallBack@4")
#pragma comment(linker, "/EXPORT:SetModStaCallBack=_SetModStaCallBack@4")
#pragma comment(linker, "/EXPORT:SetP2pStaCallBack=_SetP2pStaCallBack@4")
#pragma comment(linker, "/EXPORT:SetResStaCallBack=_SetResStaCallBack@4")
//#pragma comment(linker, "/EXPORT:SetSMSCallBack2=_SetSMSCallBack2@4")
#pragma comment(linker, "/EXPORT:SetUserStaCallBack=_SetUserStaCallBack@4")
#pragma comment(linker, "/EXPORT:SetP2pVideoCallStaCallBack=_SetP2pVideoCallStaCallBack@4")
#pragma comment(linker, "/EXPORT:SetProvisionAllResyncCallBack=_SetProvisionAllResyncCallBack@4")

//�ص��������ϲ㴫����Ϣ
static notifyGroupStatus_t callbackGrpFunc=NULL;
static notifyResourceStatus_t callbackResStaFunc=NULL;
static notifyP2pcallStatus_t callbackP2pStaFunc=NULL;
static notifyUserStatus_t callbackUserStaFunc=NULL;
static notifySMS2_t callbackSMSFunc2=NULL;
static notifyModuleStatus_t callbackModuleFunc=NULL;
static notifyP2pvideocallStatus_t callbackP2pvideocallStaFunc=NULL;

static notifyProvisionAllResync_t callbackProvisionAllResync=NULL;

#define STATUS_REGSUCCESS 4011

TDDisplayMnager::TDDisplayMnager(void)
{
	m_EventLogin = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}


TDDisplayMnager::~TDDisplayMnager(void)
{
	if(m_EventLogin)
	{
		CloseHandle(m_EventLogin); 
		m_EventLogin = NULL;
	}
}

TDDisplayMnager& TDDisplayMnager::Instance()
{ 
	static TDDisplayMnager _instance;
	return _instance; 
}

//��ȡ�����Ϣ
void TDDisplayMnager::notifyGroupStatus(const string& strEventBuf) const
{
	if (!callbackGrpFunc)
	{
		return;
	}
	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("GroupID"))
		{
			return;
		}
		int iGroupID = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("GroupCallStatus"))
		{
			return;
		}
		int iGroupCallStatus = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Speaker"))
		{
			return;
		}
		int iSpeaker = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("LocalPort"))
		{
			return;
		}
		int iLocalPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemotePort"))
		{
			return;
		}
		int iRemotePort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemoteIp"))
		{
			return;
		}
		string strRemoteIp = rspXml.GetElemValue();
		strGrpDspInfo* pGrpInfo = new strGrpDspInfo;
		pGrpInfo->_grpId = iGroupID;
		pGrpInfo->_sp_status = (Speaker_Status_t)iGroupCallStatus;
		pGrpInfo->_speaker = iSpeaker;
		pGrpInfo->theLocalPort = iLocalPort;
		pGrpInfo->theRemotePort = iRemotePort;
		pGrpInfo->theRemoteIP = inet_addr(strRemoteIp.c_str());
		//�⺯���_��Ĳ���������ָ�����͵Ĳ���
		(*callbackGrpFunc)(pGrpInfo);

		delete pGrpInfo;
		pGrpInfo =NULL;
		return;
	}
}

//֪ͨ�û���Ⱥ����Դ��״̬�����Ϣ
void TDDisplayMnager::notifyResourceStatus(const string& strEventBuf)
{
	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("ResourceID"))
		{
			return;
		}
		int iResId = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("StatusType"))
		{
			return;
		}
		int iStatusType = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("StatusValue"))
		{
			return;
		}
		int iStatusValue = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("AttachingGroup"))
		{
			return;
		}
		int iAttachingGrp = atoi(rspXml.GetElemValue());

		if(!m_strResID.empty() && iResId == atoi(m_strResID.c_str()))
		{
			if(STATUS_REGSUCCESS == iStatusValue)
			{
				::SetEvent(m_EventLogin);
			}			
		}

		strResourceStatusIndicator* resStaIndi = new strResourceStatusIndicator;
		resStaIndi->ResId = iResId;
		resStaIndi->status_type = (resource_status_t)iStatusType;
		resStaIndi->status_value = (res_status_value_t)iStatusValue;
		resStaIndi->attaching_grp = iAttachingGrp;
		if (!callbackResStaFunc)
		{
			delete resStaIndi;
			resStaIndi =NULL;
			return;
		}
		(*callbackResStaFunc)(resStaIndi);
		delete resStaIndi;
		resStaIndi =NULL;
	}	
}


//֪ͨ��Ե���е�״̬��Ϣ
void TDDisplayMnager::notifyP2pcallStatus(const string& strEventBuf) const
{
	if (!callbackP2pStaFunc)
	{
		return;
	}
	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("P2pcallStatus"))
		{
			return;
		}
		int iP2pcallStatus = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Callee"))
		{
			return;
		}
		int iCallee = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Caller"))
		{
			return;
		}
		int iCaller = atoi(rspXml.GetElemValue());

		if(!rspXml.FindElem("Inserter"))
		{
			return;
		}
		int iInserter = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Targeter"))
		{
			return;
		}
		int iTargeter = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("LocalPort"))
		{
			return;
		}
		int iLocalPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemotePort"))
		{
			return;
		}
		int iRemotePort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemoteIp"))
		{
			return;
		}
		string strRemoteIp = rspXml.GetElemValue();

		strP2pcallStatusIndicator* p2pStaIndi = new strP2pcallStatusIndicator;

		p2pStaIndi->theCallee = iCallee;
		p2pStaIndi->theCaller = iCaller;
		p2pStaIndi->theInserter = iInserter;
		p2pStaIndi->theTargeter = iTargeter;
		p2pStaIndi->theStatus = (P2pcall_Status_t)iP2pcallStatus;
		p2pStaIndi->theRemoteIP = inet_addr(strRemoteIp.c_str());
		p2pStaIndi->theLocalPort = iLocalPort;
		p2pStaIndi->theRemotePort = iRemotePort;

		(*callbackP2pStaFunc)(p2pStaIndi);
		delete p2pStaIndi;
		p2pStaIndi =NULL;
	}
}

//֪ͨ�û���Ⱥ����Դ��״̬�����Ϣ,��ҪYCʵ��
void TDDisplayMnager::notifyUserStatus(const string& strEventBuf) const
{
	if (!callbackUserStaFunc)
	{
		return;
	}
	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("UserID"))
		{
			return;
		}
		int iResId = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("StatusType"))
		{
			return;
		}
		int iStatusType = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("StatusValue"))
		{
			return;
		}
		int iStatusValue = atoi(rspXml.GetElemValue());
		strResourceStatusIndicator* resStaIndi = new strResourceStatusIndicator;

		resStaIndi->ResId = iResId;
		resStaIndi->status_type = (resource_status_t)iStatusType;
		resStaIndi->status_value = (res_status_value_t)iStatusValue;
		(*callbackUserStaFunc)(resStaIndi);

		delete resStaIndi;
		resStaIndi = NULL;
	}
}

//֪ͨ�û�״̬����Ϣ�ķ������ʵ��
void TDDisplayMnager::notifyUserSdsStatus(const string& strEventBuf) const
{
}

//֪ͨ�û���ͨ����Ϣ�ķ������ʵ��
void TDDisplayMnager::notifySMS(const string& strEventBuf) const
{	
}

void TDDisplayMnager::notifyProvisionAllResync()
{ 
	if(callbackProvisionAllResync)
	{
		(*callbackProvisionAllResync)();
	}
}

void TDDisplayMnager::notifyStatusAllResync(const string& strEventBuf) const
{
}

void TDDisplayMnager::notifyModuleStatus(const string& strEventBuf) const
{
	if (!callbackModuleFunc)
	{
		return;
	}
	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("ModuleType"))
		{
			return;
		}
		int iModuleType = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("ModuleStatus"))
		{
			return;
		}
		int iModuleStatus = atoi(rspXml.GetElemValue());
	
		strDCModuleStatusIndicator* resStaIndi = new strDCModuleStatusIndicator;

		resStaIndi->m_module_type = (dc_module_t)iModuleType;
		resStaIndi->m_status_value = (module_status_t)iModuleStatus;
	
		(*callbackModuleFunc)(resStaIndi);

		delete resStaIndi;
		resStaIndi = NULL;
	}
}

//֪ͨ��Ƶ���е�״̬�����Ϣ��������Ƶ�ش�������ҪYCʵ��
void TDDisplayMnager::notifyP2pvideocallStatus(const string& strEventBuf) const
{
	if (!callbackP2pvideocallStaFunc)
	{
		return;
	}

	//xml ����
	CXml rspXml;
	if(!rspXml.Parse(strEventBuf.c_str()))
	{
		return;
	}

	if(!rspXml.FindElem("Content"))
	{
		return;
	}
	if(rspXml.IntoElem())
	{
		if(!rspXml.FindElem("CallStatus"))
		{
			return;
		}
		int iCallStatus = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("LocalAudioPort"))
		{
			return;
		}
		int iLocalAudioPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("LocalVideoPort"))
		{
			return;
		}
		int iLocalVideoPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemoteAudioPort"))
		{
			return;
		}
		int iRemoteAudioPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemoteVideoPort"))
		{
			return;
		}
		int iRemoteVideoPort = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("RemoteIp"))
		{
			return;
		}
		string strRemoteIp = rspXml.GetElemValue();
		if(!rspXml.FindElem("Uri"))
		{
			return;
		}
		int iUri = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Callee"))
		{
			return;
		}
		int iCallee = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Caller"))
		{
			return;
		}
		int iCaller = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("SoundMute"))
		{
			return;
		}
		int iSoundMute = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Channel"))
		{
			return;
		}
		int iChannel = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("UserConfirm"))
		{
			return;
		}
		int iUserConfirm = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("Camera"))
		{
			return;
		}
		int iCamera = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("SoundPtype"))
		{
			return;
		}
		int iSoundPtype = atoi(rspXml.GetElemValue());
		if(!rspXml.FindElem("VideoFormatType"))
		{
			return;
		}
		int iVideoFormatType = atoi(rspXml.GetElemValue());

		strP2pvideocallStatusIndicator* p2pVideocallIndi = new strP2pvideocallStatusIndicator;

		p2pVideocallIndi->Caller = iCaller;
		p2pVideocallIndi->Callee = iCallee;
		p2pVideocallIndi->CalAudioPort = iLocalAudioPort;
		p2pVideocallIndi->LocalVideoPort = iLocalVideoPort;
		p2pVideocallIndi->RemoteAudioPort= iRemoteAudioPort;
		p2pVideocallIndi->RemoteVideoPort = iRemoteVideoPort;
		p2pVideocallIndi->RemoteIp = inet_addr(strRemoteIp.c_str());
		p2pVideocallIndi->SoundMute = iSoundMute;
		p2pVideocallIndi->Channel = iChannel;
		p2pVideocallIndi->Uri = iUri;
		p2pVideocallIndi->UserCfm = iUserConfirm;
		p2pVideocallIndi->Camera = iCamera;
		p2pVideocallIndi->SoundPtype = (Sound_t)iSoundPtype;
		p2pVideocallIndi->Fmt = (Fmt_type)iVideoFormatType;
		p2pVideocallIndi->Status = (P2pvideocall_Status_t)iCallStatus;

		(*callbackP2pvideocallStaFunc)(p2pVideocallIndi);
		delete p2pVideocallIndi;
		p2pVideocallIndi =NULL;
	}
}

//֪ͨ��Ƶ����
void _SDK_CALL SetP2pVideoCallStaCallBack(notifyP2pvideocallStatus_t notifyP2pvideocallSta)
{
	callbackP2pvideocallStaFunc=notifyP2pvideocallSta;    
}

//֪ͨȺ����е�״̬��Ϣ
void _SDK_CALL SetGrpStaCallBack(notifyGroupStatus_t notiGrpSta)
{
	callbackGrpFunc=notiGrpSta;    
}
//֪ͨ��Դ״̬��Ϣ
 void _SDK_CALL SetResStaCallBack(notifyResourceStatus_t notiResSta)
{
	callbackResStaFunc=notiResSta;
}
 //֪ͨ��Ե���е�״̬��Ϣ
void _SDK_CALL SetP2pStaCallBack(notifyP2pcallStatus_t notiP2pSta)
{
	callbackP2pStaFunc=notiP2pSta;  
}
//֪ͨ�յ�Ԥ�õ�״̬
void _SDK_CALL SetUserStaCallBack(notifyUserStatus_t notiUserSta)
{
	//UBP_SDK_DEBUG("SetUserStaCallBack.notiUserSta = "<<notiUserSta);
	callbackUserStaFunc=notiUserSta;  
}

////֪ͨ�յ���ͨ����
//void _SDK_CALL SetSMSCallBack2(notifySMS2_t notiSMS)
//{
//	callbackSMSFunc2=notiSMS;  
//}

void _SDK_CALL SetModStaCallBack(notifyModuleStatus_t notifyModSta)
{
	callbackModuleFunc=notifyModSta;
}

void _SDK_CALL SetProvisionAllResyncCallBack(notifyProvisionAllResync_t notifyProSta)
{
	callbackProvisionAllResync=notifyProSta;
}