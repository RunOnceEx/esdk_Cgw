//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��notifyStruct_t.h
//	��  ��	��w00206574
//	������ڣ�2014-04-08
//	˵  ��	��ʵ��eLTE�ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================
#include "StdAfx.h"
#include <string>

/**
   ����Ⱥ����ʾ���ݽṹ
**/
typedef enum {
    PTT_IND_STATUS_UNKNOWN=1000,
    PTT_IND_STATUS_RECEIVED,
    PTT_IND_STATUS_REQUEST,
    PTT_IND_STATUS_ACCEPT,
    PTT_IND_STATUS_WAITING,
    PTT_IND_STATUS_REJECT,
    PTT_IND_STATUS_SNATCH,
    PTT_IND_STATUS_HANGUP_OK,
    PTT_IND_STATUS_CLOSE_OK,
    PTT_IND_STATUS_CANCEL_OK,
    PTT_IND_STATUS_PREMPTED,
    /*--------ý����仯��֪ͨ-------------*/
    PTT_IND_STATUS_TX_BEGIN,        //�����Ȩ�仯
    PTT_IND_STATUS_TX_IDLE,         //�����Ȩ����
    PTT_IND_STATUS_MEDIAPLANE_ERROR,
    PTT_IND_STATUS_EMERGENCY_BEGIN,
    PTT_IND_STATUS_EMERGENCY_UPDATE,
    PTT_IND_STATUS_LICENSE_LIMIT,
    PTT_IND_STATUS_SIGNAL_ERROR
} Speaker_Status_t;

typedef  struct  strGrpDspInfo
{
	int _grpId;
	Speaker_Status_t _sp_status;
	int _speaker;
	int theLocalPort;
	int theRemotePort;
	unsigned long theRemoteIP;
};
typedef void (*notifyGroupStatus_t)(strGrpDspInfo *pGrpInfo);

typedef enum
{
	/*-------------------������ϢԪ�����ڵ����������Ƶ�������p2pcallstatus_indicator.cpp-----------*/
	CALLSTATUS =0, //���״̬
	CALLERINFO =1, //������
	CALLEEINFO =2, //������

	/*--------------------������ϢԪ�������������grpcallstatus_indicator.cpp----------------*/
	GRPCALLSTATUS =3, //���״̬
	GRPCALLSPERKER =4, //���������
	FLOORSTATUS =5,    //��Ȩ״ָ̬ʾ

	/*--------------------������ϢԪ�����ڽ������У� ��emergency_indicator.cpp----------------*/
	EMERGENCYCALL =6,  //��������ָʾ
	EMERGENCYCALLER =7,  //����������

	/*--------------------������ϢԪ��������Դ״̬����,��resourcestatus_indicator.cpp----------------*/
	RESORCEID =8,              //��ԴID
	DEVICEID =9,               //��Ƶ����ʱ�Ĵ��ں�
	RESSELECTSTATUS =10,        //��Դѡ��״ָ̬ʾ�� ���ڶ�GUI����
	RESASSIGNSTATUS =11,        //��Դָ��״ָ̬ʾ�� ������̨�Ƿ�������Դ��
	RESTXSTATUS =12,            //��Դռ��״ָ̬ʾ
	RESLOGGINGSTATUS =13,       //��Դ¼��״ָ̬ʾ
	RESDLSTATUS =14,            //��Դ����״ָ̬ʾ
	RESREGSTATUS_PROXY =15,     //��Դע��״ָ̬ʾ, ����ע��(���������û����ն˼�Ⱥע��)
	RESREGSTATUS_DIRECT =16,    //��Դע��״ָ̬ʾ, ֱ��ע��(�ն�ҵ��ע�ᣬ����Ƶ)
	ATTACHINGGROUP =17,         //��Դ��������

	/*--------------------������ϢԪ�������û�״̬����;��userstatus_indicator.cpp----------------*/
	USERSTATUS =18,		//�û�״ָ̬ʾ�� һ����BCC֪ͨ
	USERGPSSTATUS =19,       //�û�GPS״ָ̬ʾ
	USERDLSTATUS =20,            //�û���¼״ָ̬ʾ
	USERDGNASTATUS =21,      //�û���̬����״̬
	VIDEODISPATCHSTATUS =22,     //��Ƶ�ַ�״̬
	MUTESTATUS =23,          //����״̬
	GRPPATCHSTATUS =24  //�ɽӲ���״̬
}BundleKey;

/**
   ������Դ״ָ̬ʾ���ݽṹ
**/
typedef  BundleKey resource_status_t;

typedef enum {
    RESOURCE_STATUS_UNKNOWN = 4000,
    STATUS_SELECTED = 4001,    //��Դѡ��״̬
    STATUS_UNSELECTED = 4002,  //��Դȥѡ��״̬

    STATUS_ASSIGNED = 4003,    //��Դָ��״̬-
    STATUS_DEASSIGNED = 4004,  //��Դȥָ��״̬-

    STATUS_LISTENING = 4005,   //��Դ������״̬
    STATUS_LISTENEND = 4006,   //��Դ��������״̬

    STATUS_LOGGING = 4007,      //��Դ¼����״̬
    STATUS_NOLOGGING = 4008,    //��Դδ����¼��

    STATUS_INPATCH = 4009,      //��Դ���ɽ�
    STATUS_OUTPATCH = 4010,     //��Դ����ɽ�

    STATUS_REGOK = 4011,        //��Դע��
    STATUS_REGFAIL = 4012,      //��Դȥע��
    STATUS_FORBIDEN = 4013,     //��Դδ��Ȩ 500
    STATUS_NOT_FOUND = 4014,    //��Դ������ 404
    STATUS_TEMP_UNAVAILABLE = 4015, //��Դ��ʱ������ 480
    STATUS_RES_CONFILCT = 4016, //��Դ��ͻ 450
    STATUS_UNAUTHORIZED = 4017, //δ��Ȩ 401
    STATUS_LICENSE_LIMIT = 4018, //License���� 503
    STATUS_PASSWORD_WRONG = 4019, //������� 403

    //�����ĸ�״̬��˳�����Ҫ�� ��Ϊ isValidTransition������Ҫ�ο�˳��
    STATUS_INVITING = 4020,    //the resource is initializing a call
    STATUS_RINGING = 4021,      //the resource is ringing
    STATUS_TXMTING = 4022,     //the resource is talking/transimitting in a call
    STATUS_TXMTIDLE = 4023,    //the resource is idle

    STATUS_DGNAOK = 4024,       //dynamic regrouping OK
    STATUS_DGNAFAIL = 4025,      //dynamic regrouping fail
    STATUS_DGNA_UEFAIL = 4026,   //dynamic regrouping one UE fail
    STATUS_GROUP_ACTIVATED = 4027,
    STATUS_GROUP_DEACTIVATED = 4028,
    STATUS_MUTE = 4029,        //sound mute
    STATUS_UNMUTE = 4030,       //sound unmute
    STATUS_GRPPATCH_CREATEOK = 4031,  //�ɽ��鴴��OK
    STATUS_GRPPATCH_CREATEFAIL = 4032, //�ɽ��鴴��ʧ��
    STATUS_GRPPATCH_CANCELOK = 4033, //�ɽ���ȡ��OK
    STATUS_GRPPATCH_CANCELFAIL = 4034, //�ɽ���ȡ��ʧ��
    STATUS_GRPPATCH_ADDOK = 4035, //�ɽ�����ӳ�ԱOK
    STATUS_GRPPATCH_ADDFAIL = 4036, //�ɽ�����ӳ�ԱFAIL
    STATUS_GRPPATCH_DELOK = 4037, //�ɽ���ɾ����ԱOK
    STATUS_GRPPATCH_DELFAIL = 4038,  //�ɽ���ɾ����ԱFAIL

    STATUS_ACCOUNT_LOCKED = 4060 // �˺ű�����

} res_status_value_t;

typedef  struct  strResourceStatusIndicator
{
	int ResId;
	resource_status_t status_type;      //status type
	res_status_value_t status_value;    //status value for this type
	int attaching_grp;
};
typedef void (*notifyResourceStatus_t)(strResourceStatusIndicator *resStaIndi);
typedef void (*notifyUserStatus_t)(strResourceStatusIndicator *resStaIndi);

/**
   ����Ⱥ����ʾ���ݽṹ
**/
typedef enum {
    P2P_IND_STATUS_UNKNOWN = 2000,
    /*--------������״̬--------*/
    P2P_IND_STATUS_INITIATED = 2001,
    P2P_IND_STATUS_RECEIVED = 2002,
    P2P_IND_STATUS_ANSWERED = 2003,
    P2P_IND_STATUS_EMERGENCY = 2004,
    P2P_IND_STATUS_PROCEEDING = 2005,
    P2P_IND_STATUS_RINGING = 2006,
    P2P_IND_STATUS_ACKED = 2007,
    P2P_IND_STATUS_RELEASED = 2008,
    P2P_IND_STATUS_HANGUPED = 2009,
    P2P_IND_STATUS_HANGUPED_ACTIVE = 2010,
    P2P_IND_STATUS_CANCELLED = 2011,
    P2P_IND_STATUS_PREMPTED = 2012,
    P2P_IND_STATUS_RELEASED_BUSY = 2013,
    P2P_IND_STATUS_BREAKIN_FAIL = 2014,
    P2P_IND_STATUS_BREAKIN_SUCCESS = 2015,
    P2P_IND_STATUS_PROHIBITED = 2016,
    P2P_IND_STATUS_REMOTE_NOANSWER = 2017,
    P2P_IND_STATUS_REMOTE_NOTFOUND = 2018,
    P2P_IND_STATUS_LICENSE_LIMIT = 2019,
    /*--------ý����״̬--------*/
    P2P_IND_STATUS_MEDIAPLANE_ERROR = 2020,
    P2P_IND_STATUS_MEDIAPLANE_MUTE = 2021,
    P2P_IND_STATUS_MEDIAPLANE_UNMUTE = 2022,
    P2P_IND_STATUS_REMOTE_NOTSUPPORTED = 2023,
    P2P_IND_STATUS_REMOTE_NOTCONNECTED = 2024,
    P2P_IND_STATUS_TRANSFER_SUCCESS = 2025,
    P2P_IND_STATUS_TRANSFER_FAIL = 2026,
    P2P_IND_STATUS_TRANSFER = 2027,
    P2P_IND_STATUS_SIGNAL_ERROR = 2028,
    P2P_IND_STATUS_EMERGENCY_BEGIN = 2029,
    P2P_IND_STATUS_RING_START_180 = 2030,         //introduced from TTR3.0
    P2P_IND_STATUS_RING_START_183 = 2031,         //introduced from TTR3.0
    P2P_IND_STATUS_RING_STOP = 2032               //introduced from TTR3.0
} P2pcall_Status_t;

typedef  struct  strP2pcallStatusIndicator
{
	P2pcall_Status_t theStatus;
	int theCaller;
	int  theCallee;
	int  theInserter;//��Ȩ��
	int  theTargeter;//��Ȩ��Ӧ����

	int theLocalPort;
	int theRemotePort;
	unsigned long theRemoteIP;
};
typedef void (*notifyP2pcallStatus_t)(strP2pcallStatusIndicator *p2pStaIndi);

//����Ϣ�ĺ�������
typedef void (*notifySMS2_t)(char *content,char *from,int getSdsContent);

typedef enum {
	SDS_MODULE = 1,   //����ҵ��ģ��
	SMS_MODULE,       //����ҵ��ģ��
	AUDIO_MODULE,    //����ҵ��ģ��
	VIDEO_MODULE,  //��Ƶҵ��ģ��
	GIS_MODULE,  //GISҵ��ģ��
	SIP_MODULE,  //����ͨ��ģ��
	RTP_MODULE,   //ý��ͨ��ģ��
	RING_MODULE,   //���� add by lwj
	SVC_MODULE, //���Ȼ�����
	UNKOWN_MODULE = 999
} dc_module_t;

typedef enum {
	RESOURCE_STATUS_NORMAL = 0, //״̬����
	SDS_OVERFLOW,    //������
	SDS_DISCONNECT,  //DC�Ͷ��ŷ���������
	SDS_CONNECT,     //DC�Ͷ��ŷ���������
	SDS_SEND_SUCCESS, //���ŷ��ͳɹ�
	SDS_SEND_FAIL, //���ŷ���ʧ��
	FOLDER_IS_EMPTY,  //�����ļ���Ϊ��
	GIS_LICESNCE_UPDATE,  //GIS License���
	GIS_LICENSCE_EXPIREDAY, //license �����������ѣ�ֻʣ7��ʱ֪ͨ������Ϊ��ʣn�죬����Ϊ�Ѿ�����n��
	SIP_DISCONNECT,       //DC��BCC����
	SIP_RECONNECT,       //DC��BCC�ָ�
	SIP_KEEPALIVE_REJECT, //BCC�ܾ�DC����������
	ATTACH_UPLOAD_FAIL,   //�����ϴ�ʧ��
	ATTACH_DOWNLOAD_FAIL,  //��������ʧ��
	SIP_START_RUNNING,     //BCC ����
	KICK_OFF,      //BCC �߳�����̨֪ͨ,��Ϊ����ͬ�˺ŵ�¼
	ASYN_CALLBACK_RETURN,   //�첽���÷���ֵ
	PASSWORD_CHANGE,    //����Ա�����޸�
	MODULE_DISCONNECT,
	MODULE_RECONNECT,
	SIP_KA_FAILONCE,       //DC��BCC����һ��
	SIP_KA_OKONCE,       //DC��BCC�ָ�һ��
	USER_DELETE,
	UNKOWN_STATUS = 999
} module_status_t;

typedef  struct  strDCModuleStatusIndicator
{
	dc_module_t m_module_type;      //ģ���������
	module_status_t m_status_value;    //״ֵ̬
};
typedef void (*notifyModuleStatus_t)(strDCModuleStatusIndicator *modSta);


/**
   ����Ⱥ����ʾ���ݽṹ
**/
typedef enum {
        P2Pvideocall_IND_STATUS_UNKNOWN = 3000,
/*------------������״̬-----------*/
    P2Pvideocall_IND_STATUS_INITIATED = 3001,
    P2Pvideocall_IND_STATUS_RECEIVED = 3002,
    P2Pvideocall_IND_STATUS_ANSWERED = 3003,
    P2Pvideocall_IND_STATUS_PROCEEDING = 3004,
    P2Pvideocall_IND_STATUS_RINGING = 3005,
    P2Pvideocall_IND_STATUS_ACKED = 3006,
    P2Pvideocall_IND_STATUS_RELEASED = 3007,
    P2Pvideocall_IND_STATUS_HANGUPED = 3008,
    P2Pvideocall_IND_STATUS_HANGUPED_ACTIVE = 3009,
    P2Pvideocall_IND_STATUS_CANCELLED = 3010,
    P2Pvideocall_IND_STATUS_MONITOR = 3011,
    P2Pvideocall_IND_STATUS_PREMPTED = 3012,
    P2Pvideocall_IND_STATUS_RELEASED_BUSY = 3013,
    P2Pvideocall_IND_STATUS_PROHIBITED = 3014,
    P2Pvideocall_IND_STATUS_REMOTE_NOANSWER = 3015,
    P2Pvideocall_IND_STATUS_REMOTE_NOTFOUND = 3016,
    P2Pvideocall_IND_STATUS_LICENSE_LIMIT = 3017,
    P2Pvideocall_IND_STATUS_EMERGENCY = 3018,
	/*------------ý����״̬-----------*/
    P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_ERROR = 3019,  //��ƵRTP������ʧ��
    P2Pvideocall_IND_STATUS_ACKED_MEDIAPLANE_NOAUDIO = 3020, //��Ƶ����������ʧ��
    P2Pvideocall_IND_STATUS_REMOTE_NOTCONNECTED = 3021,
    P2Pvideocall_IND_STATUS_REMOTE_NOTSUPPORTED = 3022,
    P2Pvideocall_IND_STATUS_SIGNAL_ERROR = 3023,            //SIP error for GW-mode
    P2Pvideocall_IND_STATUS_VIDEO_CONTROL = 3024            //PTZ control for GW-mode
} P2pvideocall_Status_t;

//��Ƶ��ʽ����
typedef enum
{
	V_CIF,
	V_QCIF,
	V_D1,
	V_720P,
	V_1080P,
	INVALID_FMT
}Fmt_type;

//��Ƶ��ʽ����
typedef enum {
	invalid_ptype = -1,
	amr_475_ptype,
	amr_1220_ptype,
	pcmu_ptype,
	pcma_ptype
} Sound_t;

typedef  struct  strP2pvideocallStatusIndicator
{
	int Caller;
	int Callee;
	int CalAudioPort;
	int LocalVideoPort;
	int RemoteAudioPort;
	int RemoteVideoPort;
	unsigned long RemoteIp;
	int SoundMute;
	int Channel;
	int Uri;
	int UserCfm;
	int Camera;
	Sound_t SoundPtype;
	Fmt_type Fmt;
	P2pvideocall_Status_t Status;
};
typedef void (*notifyP2pvideocallStatus_t)(strP2pvideocallStatusIndicator *P2pvideocallSta);

typedef void (*notifyProvisionAllResync_t)();