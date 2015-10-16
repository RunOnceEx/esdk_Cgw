/********************************************************************
filename		: 	eLTE_Types.h
author			:	zWX229156
created		    :	2015/1/6
description		:	�������������Լ��ص��������ض���
copyright		:	Copyright (C) 2015-2017
history			:	2015/1/6 ��ʼ�汾
*********************************************************************/
#ifndef __ELTE_TYPES_H__
#define __ELTE_TYPES_H__

#ifdef WIN32
#define __SDK_CALL __stdcall
#else
#define __SDK_CALL
#endif

typedef int               ELTE_INT32;
typedef unsigned int      ELTE_UINT32;
typedef char              ELTE_CHAR;
typedef void              ELTE_VOID;
typedef unsigned long     ELTE_ULONG;
typedef unsigned short    ELTE_USHORT;

// ��Ϣ����(��Ϣ�ϱ�)
typedef enum
{
	ELTE_Event_NotifyUserStatus = 0,			// �豸״̬�仯�¼�֪ͨ
	ELTE_Event_NotifyP2pvideocallStatus,		// ��ʼʵ���¼�֪ͨ
	ELTE_Event_NotifyResourceStatus,			// Ⱥ���ϵ״̬�仯�¼�֪ͨ
	ELTE_Event_NotifyProvisionChange,			// �豸�������ñ��֪ͨ�¼�
	ELTE_Event_NotifyProvisionAllResync,		// �Զ�������������֪ͨ�¼�
	ELTE_Event_NotifyP2pcallStatus,				// ���״̬�仯�¼�
	ELTE_Event_NotifyGroupStatus,				// ���״̬�仯�¼�
	ELTE_Event_NotifyModuleStatus				// ģ�����״̬�¼�
} eLTE_SDK_EVENT_TYPE;

/**************************************************************************
* name			: EventCallBack
* description   : �¼��ص�����(�¼�֪ͨ���쳣�ص���)
* input			: N/A
* output		: iEventType		�¼�����
				  pEventBuf		    �¼�����
				  uiBufSize         Buf����
				  pUserData         �û�����
* return		: N/A
**************************************************************************/
typedef ELTE_VOID (__SDK_CALL * EventCallBack)(ELTE_INT32 iEventType, ELTE_VOID* pEventBuf, ELTE_UINT32 uiBufSize, ELTE_VOID* pUserData);

#endif //__ELTE_TYPES_H__
