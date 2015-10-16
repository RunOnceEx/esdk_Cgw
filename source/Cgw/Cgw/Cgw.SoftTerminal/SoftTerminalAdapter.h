//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��SoftTerminalAdapter.h
//	��  ��	��������
//	��  ��	��V100R002C03
//	������ڣ�2013-03-22
//	˵  ��	��ʵ�����ն˽ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================
#if !defined(AFX_SOFTTERMINALADAPTER_20130321)
#define AFX_SOFTTERMINALADAPTER_20130321

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "include/soft_terminal_interface.h"
#include <msclr/marshal.h>        // .NET string to C-style string
#include <msclr/marshal_cppstd.h> // .NET string to STL string

using namespace System;
using namespace msclr::interop;
using namespace System::Runtime::InteropServices;
using namespace Cgw::Common;
using namespace Cgw::SmcError;

SOT_UINT32 WriteLog(SOT_LOG_LEVEL_E eLevel,SOT_INT8 * pcLog,SOT_UINT32 lLen);   // ���ն�д��־
SOT_UINT32 MakeIFrame(IN SOT_INT8 * pcSotNum);        // I֡�ش�


/** �������պ����Ƿ�ɹ���֪ͨ�ص�������ע����ֻ���ڽ��պ��гɹ��ŵ��øûص������� */
SOT_VOID ReceiveCallCallback(SOT_INT8 * pcSotNum,SOT_RECV_CALL_STAT_E eRecStat);

/** ����session�Ƿ�ɹ���֪ͨ�ص�������ע����ֻ���ڴ���session�ɹ��ŵ��øûص������� */
//ucMediaType:0:audio ,1:video
SOT_VOID CreateSessionCallback(SOT_INT8 * pcSotNum,SOT_CREATE_SESSION_STAT_E eCreSessionStat,SOT_UINT8 ucMediaType, SOT_UINT8 ucPayloadType,SOT_UINT16 usReceivePort);

//�Ҷϻص�
SOT_VOID   CallHandupCallback(SOT_INT8 * pcSotNum);

//�����ϱ�
SOT_VOID   ErrorReportCallback(SOT_INT8 * pcSotNum, SOT_ERROR_CODE_E eErrorCode);

typedef  SOT_BOOL (__stdcall *PSoftTerminalInit)(const SOT_SYSCFG_S * pstParamSet,const SOT_APP_REG_FN_S *pstCallBackSet);
typedef  SOT_BOOL (__stdcall *PSoftTerminalAddCallChannel)(SOT_CHANNEL_INFO_S* channelInfo);
typedef  SOT_BOOL (__stdcall *PSoftTerminalDeleteCallChannel)(SOT_INT8 *pszSotChannelLabel,SOT_UINT32 channelLabelLen);
typedef  SOT_BOOL (__stdcall *PSoftTerminalSendVideoData)(SOT_INT8 *pszSotChannelLabel,SOT_H264_DATA_TYPE_E dataType,unsigned char * pszData,int len);
typedef  SOT_BOOL (__stdcall *PSoftTerminalSendG711AudioData)(SOT_INT8 *pszSotChannelLabel,SOT_AUDIO_DATA_TYPE_E dataType,unsigned char * pszData,int len);

public ref class SoftTerminalAdapter
{
public:
	// ���캯��
	SoftTerminalAdapter();
	//��������
	~SoftTerminalAdapter();

public:
	// ��ʼ�����ն�
	SmcErr^ Init(InitSotParam^ param);

	// ע��ص�����
	bool RegistSotCallback(SoftTerminalCallback^ callback);

	// ������ն˺���ͨ��
	bool AddChannel(String^ channelLabel, String^ confLabel);

	// ɾ�����ն˺���ͨ��
	bool RemoveChannel(String^ channelLabel);

	// ��������
	bool SendMediaData(String^ channelLabel, MediaData^ data);

	std::string SoftTerminalAdapter::GetCurPath(void);

private:
	// ���й�byte����ת����unsigned char*
	unsigned char* AllocateNativeMemory(IN array<Byte> ^ManagedArray);

	//ģ����
	HMODULE  m_hDllInst;

	//��ʼ������
	PSoftTerminalInit pSoftTerminalInit;

	//��Ӻ���ͨ��
	PSoftTerminalAddCallChannel pSoftTerminalAddCallChannel;

	//ɾ������ͨ��
	PSoftTerminalDeleteCallChannel pSoftTerminalDeleteCallChannel;

	//�������ݣ���2�����ݣ�1��rtp����2��һ֡���������
	PSoftTerminalSendVideoData pSoftTerminalSendVideoData;

	//������Ƶ����(G.711a����G.711u) 
	PSoftTerminalSendG711AudioData pSoftTerminalSendG711AudioData;

public:
	// NLog��־���
	static NLogCallback^ NLogHandler;

	// I֡�ش����
	static IFrameCallback^ IFrameHandler;

	// ����ص����
	static SotErrorReport^ errReportHandler;
};

#endif // !defined(AFX_SOFTTERMINALADAPTER_20130321)