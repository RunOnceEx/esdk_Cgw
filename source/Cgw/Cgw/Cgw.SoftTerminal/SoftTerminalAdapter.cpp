//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��SoftTerminalAdapter.h
//	��  ��	��������
//	��  ��	��V100R002C03
//	������ڣ�2013-03-22
//	˵  ��	��ʵ�����ն˽ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��w00206574 2014-08-22��Ϊ��̬����SotCall.dll
//===================================================================
#include "stdafx.h"
#include <string>
#include "SoftTerminalAdapter.h"

//��ȡdll·��
std::string SoftTerminalAdapter::GetCurPath(void)
{
	char path[_MAX_DIR+1] = {0};
	GetModuleFileName(NULL, path, sizeof(path));
	std::string DllPath = path;
	unsigned int pos = DllPath.find_last_of("\\", DllPath.size());
	if(pos<DllPath.size())
	{
		DllPath.resize(pos);
	}
	return DllPath;
}
//===================================================================
//	�������ƣ�SoftTerminalAdapter
//	�������������캯��
//	�����嵥��NULL
//	�����嵥��MonitorChannelManager.cs
//	���������NULL
//	���������NULL
//	  ����ֵ��NULL
//	����˵����
//===================================================================
SoftTerminalAdapter::SoftTerminalAdapter()
{
	m_hDllInst = LoadLibraryEx((GetCurPath().append("\\SotCall.dll")).c_str(),NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
	if(m_hDllInst != NULL)
	{
		pSoftTerminalInit = (PSoftTerminalInit)GetProcAddress(m_hDllInst,"SoftTerminalInit");
		pSoftTerminalAddCallChannel = (PSoftTerminalAddCallChannel)GetProcAddress(m_hDllInst,"SoftTerminalAddCallChannel");
		pSoftTerminalDeleteCallChannel = (PSoftTerminalDeleteCallChannel)GetProcAddress(m_hDllInst,"SoftTerminalDeleteCallChannel");
		pSoftTerminalSendVideoData=(PSoftTerminalSendVideoData)GetProcAddress(m_hDllInst,"SoftTerminalSendVideoData");
		pSoftTerminalSendG711AudioData=(PSoftTerminalSendG711AudioData)GetProcAddress(m_hDllInst,"SoftTerminalSendG711AudioData");
	}
}

//===================================================================
//	�������ƣ�~SoftTerminalAdapter
//	������������������
//	�����嵥��NULL
//	�����嵥��MonitorChannelManager.cs
//	���������NULL
//	���������NULL
//	  ����ֵ��NULL
//	����˵����
//===================================================================
SoftTerminalAdapter::~SoftTerminalAdapter()
{
	try
	{
		if(m_hDllInst)
		{
			FreeLibrary(m_hDllInst);
			m_hDllInst = NULL;

			pSoftTerminalInit = NULL;
			pSoftTerminalAddCallChannel =NULL;
			pSoftTerminalDeleteCallChannel =NULL;
			pSoftTerminalSendVideoData =NULL;
			pSoftTerminalSendG711AudioData =NULL;
		}
	}
	catch (...)
	{}

}

//===================================================================
//	�������ƣ�Init
//	������������ʼ��
//	�����嵥��SoftTerminal.h
//	�����嵥��MonitorChannelManager.cs
//	���������ip �ں�����ip
//	���������NULL
//	  ����ֵ��������
//	����˵�����������ն˽ӿ�ʵ�ּ���dll�����ò�������ʼ���ȹ���
//===================================================================
SmcErr^ SoftTerminalAdapter::Init(InitSotParam^ sotParam)
{
	SmcErr^ err = gcnew CgwError();
	marshal_context^ context = gcnew marshal_context();	
	SOT_APP_REG_FN_S pstCallBackSet ;
	SOT_SYSCFG_S param;

	if (String::IsNullOrEmpty(sotParam->cgwIp))
	{
		err->SetErrorNo(CgwError::ERR_CGW_CHANNEL_SOT_INIT_FAIL);
		return err;
	}

	memset(&param,0,sizeof(SOT_SYSCFG_S));
	memset(&pstCallBackSet,0,sizeof(SOT_APP_REG_FN_S));

	const char* pszAddr = context->marshal_as<const char*>(sotParam->cgwIp);	
	unsigned long dwIP = 0;
	if(0 == strcmp(pszAddr,"127.0.0.1"))
	{
		dwIP = inet_addr("0.0.0.0");
	}
	else
	{
		dwIP = inet_addr(pszAddr);
	}

	param.stLocalAddr.ipv4 = dwIP;
	param.stLocalAddr.eIpVesion = SOT_IP_VER_E::SOT_IP_V4;
	param.usLocalPort = sotParam->channelCallPort;
	param.eLogLevel = SOT_LOG_TRACE;
	param.usLocalRtpBasePort = sotParam->rtpStartPort; /*rtp�����˿ڣ���6K-60K֮��*/
	param.usMediaMode = SOT_AUDIO_SENDONLY|SOT_VIDEO_SENDONLY; /*��ʱֻ����Ƶ����*/
	param.usLocalRtpPortNum = sotParam->rtpPortCount; //ÿ·ͨ����Ҫ8���˿ڣ���������˿ڵ�2��
	param.eEntityType = SOT_ENTITY_CGW;

	if (sotParam->audioType == StreamType::AUDIO_G711A)
	{
		param.eCapAudio = SOT_CAP_AUDIO_E::SOT_CAP_AUDIO_G711_A;
	}
	else if (sotParam->audioType == StreamType::AUDIO_G711U)
	{
		param.eCapAudio = SOT_CAP_AUDIO_E::SOT_CAP_AUDIO_G711_U;
	}
	else
	{
		err->SetErrorNo(CgwError::ERR_CGW_CHANNEL_SOT_INIT_FAIL);
		return err;
	}

	// ע��ص�
	pstCallBackSet.pfSotCallLogFunc = (pFnSotLog)&WriteLog;
	pstCallBackSet.pfSotIFrameReq = (pFnSotIFrameReq)&MakeIFrame;

	pstCallBackSet.pfSotReceiveCallNotify=(pFnSotReceiveCallNotify)&ReceiveCallCallback;
	pstCallBackSet.pfSotCreateSessionNotify=(pFnSotCreateSessionNotify)&CreateSessionCallback;
	pstCallBackSet.pfSotCallHangup=(pFnSotCallHangup)&CallHandupCallback;
	pstCallBackSet.pfSotErrorReport = (pFnSotErrorReport)&ErrorReportCallback;
	
	// ���ն˳�ʼ��
	if (!pSoftTerminalInit||!pSoftTerminalInit(&param, &pstCallBackSet))
	{
		err->SetErrorNo(CgwError::ERR_CGW_CHANNEL_SOT_INIT_FAIL);
		return err;
	}

	return err;
}


SOT_VOID ReceiveCallCallback(SOT_INT8 * pcSotNum,SOT_RECV_CALL_STAT_E eRecStat)
{


}

SOT_VOID CreateSessionCallback(SOT_INT8 * pcSotNum,SOT_CREATE_SESSION_STAT_E eCreSessionStat,SOT_UINT8 ucMediaType,SOT_UINT8 ucPayloadType,SOT_UINT16 usReceivePort)
{

}

SOT_VOID   CallHandupCallback(SOT_INT8 * pcSotNum)
{


}

SOT_VOID   ErrorReportCallback(SOT_INT8 * pcSotNum, SOT_ERROR_CODE_E eErrorCode)
{
	// ���������ж�
	if (nullptr == SoftTerminalAdapter::errReportHandler || NULL == pcSotNum)
	{
		return;
	}

	String^ code = gcnew String(pcSotNum);
	SotErrorType errType = SotErrorType::InitStackErr;

	if (eErrorCode == SOT_ERROR_CODE_E::SOT_INIT_STACK_ERROR)
	{
		errType = SotErrorType::InitStackErr;
	}
	else if (eErrorCode == SOT_ERROR_CODE_E::SOT_INIT_STACK_ERROR)
	{
		errType = SotErrorType::RtpSessionCreateErr;
	}
	else
	{
		return;
	}

	SoftTerminalAdapter::errReportHandler(code, errType);
}


//===================================================================
//	�������ƣ�RegistSotCallback
//	����������ע��ص�����
//	�����嵥��SoftTerminal.h
//	�����嵥��MonitorChannelManager.cs
//	���������callback �ص�����
//	���������NULL
//	  ����ֵ��������
//	����˵����ע��д��־��i֡�ش��Ļص�����
//===================================================================
bool SoftTerminalAdapter::RegistSotCallback(SoftTerminalCallback^ callback)
{
	SmcErr^ err = gcnew CgwError();
	
	// �ж������Ƿ�Ϊ��
	if (nullptr == callback)
	{
		return false;
	}

	// �жϻص�ί���Ƿ�Ϊ��
	if (nullptr == callback->NlogHandler || nullptr == callback->IFrameHandler || nullptr == callback->errReportHandler)
	{
		return false;
	}

	NLogHandler = callback->NlogHandler;
	IFrameHandler = callback->IFrameHandler;
	errReportHandler = callback->errReportHandler;

	return true;
}

//===================================================================
//	�������ƣ�AddChannel
//	������������Ӻ���ͨ��
//	�����嵥��SoftTerminal.h
//	�����嵥��MonitorChannelManager.cs
//	���������channelLabel ͨ����ʶ��confAccessCode �����
//	���������NULL
//	  ����ֵ���������
//	����˵����
//===================================================================
bool SoftTerminalAdapter::AddChannel(String^ channelLabel, String^ confAccessCode)
{
	marshal_context^ context = gcnew marshal_context();
	SOT_CHANNEL_INFO_S channelInfo;

	// ��������ж�
	if (String::IsNullOrEmpty(channelLabel) || String::IsNullOrEmpty(confAccessCode))
	{
		return false;
	}

	const char* pszChannelLabel = context->marshal_as<const char*>(channelLabel);
	const char* pszConfAccessCode = context->marshal_as<const char*>(confAccessCode);

	// ���
	channelInfo.pcCallNumber = _strdup(pszChannelLabel);
	channelInfo.ulCallLen = strlen(pszChannelLabel);
	channelInfo.pcConfNumber = _strdup(pszConfAccessCode);
	channelInfo.ulConfLen = strlen(pszConfAccessCode);

	// ����dll�ӿ�

	bool isSuccess = false;
	if (pSoftTerminalAddCallChannel)
	{
		isSuccess = pSoftTerminalAddCallChannel(&channelInfo);
	}	

	// �ͷ�ͨ����ʶָ��
	if (NULL != channelInfo.pcCallNumber)
	{
		free(channelInfo.pcCallNumber);
		channelInfo.pcCallNumber = NULL;
	}

	// �ͷŻ����ָ��
	if (NULL != channelInfo.pcConfNumber)
	{
		free(channelInfo.pcConfNumber);
		channelInfo.pcConfNumber = NULL;
	}
	
	delete context;

	return isSuccess;
}

//===================================================================
//	�������ƣ�RemoveChannel
//	����������ɾ������ͨ��
//	�����嵥��SoftTerminal.h
//	�����嵥��MonitorChannelManager.cs
//	���������channelLabel ͨ����ʶ
//	���������NULL
//	  ����ֵ���������
//	����˵����
//===================================================================
bool SoftTerminalAdapter::RemoveChannel(String^ channelLabel)
{
	marshal_context^ context = gcnew marshal_context();

	if (String::IsNullOrEmpty(channelLabel))
	{
		return false;
	}

	const char* pszChannelLabel = context->marshal_as<const char*>(channelLabel);
	SOT_INT8 *pszSotChannelLabel = _strdup(pszChannelLabel);
	SOT_UINT32 channelLabelLen = strlen(pszChannelLabel);

	bool isSuccess =  false;
	if (pSoftTerminalDeleteCallChannel)
	{
		isSuccess = pSoftTerminalDeleteCallChannel(pszSotChannelLabel, channelLabelLen);
	}

	// �ͷ�ͨ����ʶָ��
	if (NULL != pszSotChannelLabel)
	{
		free(pszSotChannelLabel);
		pszSotChannelLabel = NULL;
	}

	delete context;

	return isSuccess;
}

//===================================================================
//	�������ƣ�SendRtpData
//	������������������
//	�����嵥��SoftTerminal.h
//	�����嵥��MonitorChannelManager.cs
//	���������channelLabel ͨ����ʶ data ��������
//	���������NULL
//	  ����ֵ���������
//	����˵����
//===================================================================
bool SoftTerminalAdapter::SendMediaData(String^ channelLabel, MediaData^ data)
{
	marshal_context^ context = gcnew marshal_context();
	bool isSuccess = false;

	// ���������ж�
	if (String::IsNullOrEmpty(channelLabel) || nullptr == data)
	{
		return false;
	}

	const char* pszChannelLabel = context->marshal_as<const char*>(channelLabel);
	SOT_INT8 *pszSotChannelLabel = _strdup(pszChannelLabel);

	// ת����������
	SOT_H264_DATA_TYPE_E dataType = SOT_H264_DATA_TYPE_E::RTP_H264_DATA;
	switch (data->DataType)
	{
	case MediaDataType::FRAME_DATA:
		dataType = SOT_H264_DATA_TYPE_E::RAW_H264_DATA;
		break;
	case MediaDataType::RTP_DATA:
		dataType = SOT_H264_DATA_TYPE_E::RTP_H264_DATA;
		break;
	default:
		break;
	}

	// ת����������
	array<Byte>^ dataArray = data->Data;
	unsigned char * pszData = AllocateNativeMemory(dataArray);
	int len = data->Size;

	// ���ýӿ�
	switch (data->StreamType)
	{
	case StreamType::VIDEO_H264:
		if (pSoftTerminalSendVideoData)
		{
			isSuccess =  pSoftTerminalSendVideoData(pszSotChannelLabel, dataType, pszData, len);
		}		
		break;
	case StreamType::AUDIO_G711A:
		if (pSoftTerminalSendG711AudioData)
		{		
			isSuccess =  pSoftTerminalSendG711AudioData(pszSotChannelLabel, SOT_AUDIO_DATA_TYPE_E::G711_A_AUDIO_DATA, pszData, len);
		}
		break;
	case StreamType::AUDIO_G711U:
		if (pSoftTerminalSendG711AudioData)
		{
			isSuccess =  pSoftTerminalSendG711AudioData(pszSotChannelLabel, SOT_AUDIO_DATA_TYPE_E::G711_U_AUDIO_DATA, pszData, len);
		}
		break;
	default:
		break;
	}
	

	// �ͷ���������ָ��
	if (NULL != pszData)
	{
		free(pszData);
		pszData = NULL;
	}

	// �ͷ�ͨ����ʶָ��
	if (NULL != pszSotChannelLabel)
	{
		free(pszSotChannelLabel);
		pszSotChannelLabel = NULL;
	}

	delete context;

	return isSuccess;
}

//===================================================================
//	�������ƣ�AllocateNativeMemory
//	������������Byte[]ת����unsigned charָ��
//	�����嵥��NULL
//	�����嵥��MonitorChannelManager.cs
//	���������ManagedArray ����������
//	���������NULL
//	  ����ֵ���ַ���ָ��
//	����˵����
//===================================================================
unsigned char* SoftTerminalAdapter::AllocateNativeMemory(IN array<Byte> ^ManagedArray)
{
	if (ManagedArray == nullptr)
	{
		return NULL;
	}

	unsigned char * DestNativePtr	= (unsigned char*) malloc(ManagedArray->Length );
	if (NULL == DestNativePtr)
	{
		return NULL;
	}
	memset(DestNativePtr,0,ManagedArray->Length );

	IntPtr NativePtr(DestNativePtr);
	Marshal::Copy(ManagedArray,0,NativePtr,ManagedArray->Length);

	return DestNativePtr;
}

//===================================================================
//	�������ƣ�WriteLog
//	����������д��־�ص�
//	�����嵥��c#ί��
//	�����嵥�����ն�
//	���������eLevel ��־���� pcLog ��־�ַ����� lLen ��־����
//	���������NULL
//	  ����ֵ��0
//	����˵����
//===================================================================
SOT_UINT32 WriteLog(SOT_LOG_LEVEL_E eLevel,SOT_INT8 * pcLog,SOT_UINT32 lLen)
{
	NLogLevel level = NLogLevel::Info;

	if (nullptr == SoftTerminalAdapter::NLogHandler)
	{
		return 0;
	}

	switch (eLevel)
	{
	case SOT_LOG_LEVEL_E::SOT_LOG_ERROR:
		level = NLogLevel::Error;
		break;
	case SOT_LOG_LEVEL_E::SOT_LOG_WARNING:
		level = NLogLevel::Warn;
		break;
	case SOT_LOG_LEVEL_E::SOT_LOG_INFO:
		level = NLogLevel::Info;
		break;
	case SOT_LOG_LEVEL_E::SOT_LOG_TRACE:
		level = NLogLevel::Trace;
		break;
	default:
		break;
	}

	String^ log = gcnew String(pcLog);
	return SoftTerminalAdapter::NLogHandler(level, log, lLen);

}

//===================================================================
//	�������ƣ�MakeIFrame
//	����������i֡�ط��ص�
//	�����嵥��c#ί��
//	�����嵥�����ն�
//	���������pcSotNum ͨ������
//	���������NULL
//	  ����ֵ��0
//	����˵����
//===================================================================
SOT_UINT32 MakeIFrame(IN SOT_INT8 * pcSotNum)
{
	if (nullptr == SoftTerminalAdapter::IFrameHandler)
	{
		return 0;
	}

	String^ channelLabel = gcnew String(pcSotNum);
	return SoftTerminalAdapter::IFrameHandler(channelLabel);
}



