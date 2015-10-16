/********************************************************************
filename		: 	eLTE_SDK.h
author			:	zWX229156
created		    :	2015/1/5
description		:	���� DLL Ӧ�ó���ĵ�������
copyright		:	Copyright (C) 2015-2017
history			:	2015/1/5 ��ʼ�汾
*********************************************************************/

#ifndef __ELTE_SDK_H__
#define __ELTE_SDK_H__

#include "eLTE_Types.h"

// �����ṩDLL�����ӿ�
#ifdef WIN32
#ifdef  ELTE_SDK_EXPORTS
#define ELTE_SDK_API __declspec(dllexport)
#else
#define ELTE_SDK_API __declspec(dllimport)
#endif
#else
#define ELTE_SDK_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/**************************************************************************
	* name			: ELTE_SDK_SetLogPath
	* description   : ������־·������ʹ�þ���·������鿴��־�ļ�
	* input			: pLogFilePath ��־����·��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetLogPath(const ELTE_CHAR* pLogFilePath);

	/**************************************************************************
	* name			: ELTE_SDK_SetLogLevel	
	* description   : ������־����
	* input			: iLogLevel ��־����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetLogLevel(ELTE_UINT32 iLogLevel);

	/**************************************************************************
	* name			: ELTE_SDK_ReleaseBuffer
	* description   : �ͷ�SDK�ڲ�������ڴ�
	* input			: pBuffer �ڴ�ָ��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL  ELTE_SDK_ReleaseBuffer(ELTE_CHAR* pBuffer);

	/**************************************************************************
	* name			: ELTE_SDK_GetVersion
	* description   : ��ȡSDK�汾��
	* input			: pVersion ��ȡSDK�汾��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetVersion(ELTE_CHAR** pVersion);

	/**************************************************************************
	* name			: ELTE_SDK_Init
	* description   : ��ʼ��SDK
	* input			: N/A
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Init();

	/**************************************************************************
	* name			: ELTE_SDK_Cleanup
	* description   : �ͷ�SDK
	* input			: N/A
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Cleanup();

	/**************************************************************************
	* name			: ELTE_SDK_SetEventCallBack
	* description   : ������Ϣ�ص�����
	* input			: fEventCallBack �û����õ��¼��ص�������Ϊ�ձ�ʾȡ�����õĻص�����
	                  pUserData      �û�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetEventCallBack(EventCallBack fEventCallBack, ELTE_VOID* pUserData);

	/**************************************************************************
	* name			: ELTE_SDK_Login
	* description   : ��¼
	* input			: pUserID         ����Ա�˺�
					  pPWD            ����Ա����
					  pServerIP       ���Ȼ�IP��ַ
	                  pLocalIP        ��������IP��ַ
					  uiServerSIPPort ���Ȼ�SIP����˿�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Login(const ELTE_CHAR* pUserID, const ELTE_CHAR* pPWD, const ELTE_CHAR* pServerIP, const ELTE_CHAR* pLocalIP, ELTE_UINT32 uiServerSIPPort);

	/**************************************************************************
	* name			: ELTE_SDK_Logout
	* description   : ע��
	* input			: pUserID ����Ա�˺�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Logout(const ELTE_CHAR* pUserID);

	/**************************************************************************
	* name			: ELTE_SDK_TriggerStatusReport
	* description   : ����״̬�ϱ�
	* input			: iEnableStatusReport �Ƿ���״̬�ϱ�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_TriggerStatusReport(ELTE_INT32 iEnableStatusReport);

	/**************************************************************************
	* name			: ELTE_SDK_ProvisionManagerInit
	* description   : ���ù����ʼ��
	* input			: pServerIP ���Ȼ�IP��ַ
	                : pUserID   ����Ա�˺�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_ProvisionManagerInit(const ELTE_CHAR* pServerIP,const ELTE_CHAR* pUserID);

	/**************************************************************************
	* name			: ELTE_SDK_ProvisionManagerExit
	* description   : �˳����ù���
	* input			: N/A
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_ProvisionManagerExit();

	/**************************************************************************
	* name			: ELTE_SDK_GetDcGroups
	* description   : ��ȡ����̨Ⱥ���б�
	* input			: pUserID ����̨���û���
	* output		: pDcGroups �õ���̨����������Ⱥ���б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcGroups(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcGroups);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcUsers
	* description   : ��ȡ����̨�û��б�
	* input			: pUserID ����̨���û���
	* output		: pDcUsers �õ���̨������������û��б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcUsers(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcUsers);

	/**************************************************************************
	* name			: ELTE_SDK_GetGroupUsers
	* description   : ��ȡһ��Ⱥ���Ա�б�
	* input			: pGroupID Ⱥ���
	* output		: pGroupUsers ��Ⱥ������г�Ա�б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGroupUsers(const ELTE_CHAR* pGroupID, ELTE_CHAR** pGroupUsers);

	/**************************************************************************
	* name			: ELTE_SDK_GetGroupInfo
	* description   : ��ȡһ��Ⱥ����ϸ��Ϣ
	* input			: pGroupID Ⱥ���
	* output		: pGroupInfo ��Ⱥ�����ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGroupInfo(const ELTE_CHAR* pGroupID, ELTE_CHAR** pGroupInfo);

	/**************************************************************************
	* name			: ELTE_SDK_GetUserInfo
	* description   : ��ȡһ���û���ϸ��Ϣ
	* input			: pUserID ����Ա�˺�
	* output		: pUserInfo ���û�����ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetUserInfo(const ELTE_CHAR* pUserID, ELTE_CHAR** pUserInfo);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcInfo
	* description   : ��ȡһ���û���ϸ��Ϣ
	* input			: pUserID ����̨���û���
	* output		: pDcInfo �õ���̨��ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcInfo(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcInfo);

	/**************************************************************************
	* name			: ELTE_SDK_SubscribeGroup
	* description   : ����Ⱥ��
	* input			: pGroupID              Ⱥ���
	                  iEnableSubscribeGroup �Ƿ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SubscribeGroup(const ELTE_CHAR* pGroupID, ELTE_INT32 iEnableSubscribeGroup);

	/**************************************************************************
	* name			: ELTE_SDK_CreateDynamicGroup
	* description   : ������̬Ⱥ��
	* input			: pDGNAParam ��̬�������Ϣ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CreateDynamicGroup(const ELTE_CHAR* pDGNAParam);

	/**************************************************************************
	* name			: ELTE_SDK_CancelDynamicGroup
	* description   : ɾ����̬Ⱥ��
	* input			: pResourceID ��̬�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CancelDynamicGroup(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_GetTempGroupID
	* description   : ��ȡ��ʱ���
	* input			: N/A
	* output		: iGroupID ��ʱ�����
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetTempGroupID(ELTE_INT32* iGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_CreateTempGroup
	* description   : ������ʱ��
	* input			: pTEMPGParam ��ʱ�������Ϣ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CreateTempGroup(const ELTE_CHAR* pTEMPGParam);

	/**************************************************************************
	* name			: ELTE_SDK_GetUserRECFileInfoList
	* description   : ��ȡ¼���ļ��б�
	* input			: pQueryXml ��ѯ¼������Xml
	* output		: pRspXml   ��ѯ¼���ļ�����б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetUserRECFileInfoList(const ELTE_CHAR* pQueryXml, ELTE_CHAR** pRspXml);

	/**************************************************************************
	* name			: ELTE_SDK_StartRealPlay
	* description   : ��ʼ����ʵʱ��Ƶ
	* input			: pResourceID ��ԴID
	                  pVideoParam ý�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StartRealPlay(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoParam);

	/**************************************************************************
	* name			: ELTE_SDK_PTZControl
	* description   : ��ʼ��̨����
	* input			: pResourceID      ����̨���������ԴID
	                  iPTZControlCode  ��̨��������
					  iPTZControlValue ��̨���������Ӧ�Ĳ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTZControl(const ELTE_CHAR* pResourceID, ELTE_UINT32 iPTZControlCode, ELTE_UINT32 iPTZControlValue);

	/**************************************************************************
	* name			: ELTE_SDK_StopRealPlay
	* description   : ֹͣ����ʵʱ��Ƶ
	* input			: pResourceID      ����̨���������ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StopRealPlay(const ELTE_CHAR* pResourceID);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif
