/*****************************************************************************
*               Copyright (C) 2013, Huawei Tech. Co., Ltd.               
*                           ALL RIGHTS RESERVED                               
* FileName: soft_terminal_type.h                                                          
* Version: 1.0                                                                
* Description:  ����ģ���RTP����.     
*                                                                             
* History:                                                                    
* 1. 2013-03-12,y00186060 Create this file.                                 
******************************************************************************/
#ifndef __SOT_TYPE_H__
#define __SOT_TYPE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>

#ifdef __cplusplus
	extern "C"{
#endif

#undef const
typedef void             SOT_VOID;     /**< �����������Ͷ��� */
typedef const void       SOT_CVOID;    /**< �����������Ͷ��� */
typedef char      SOT_INT8;     /**< �����������Ͷ��� */
typedef unsigned char    SOT_UINT8;    /**< �����������Ͷ��� */
typedef signed short     SOT_INT16;    /**< �����������Ͷ��� */
typedef unsigned short   SOT_UINT16;   /**< �����������Ͷ��� */
typedef signed long      SOT_INT32;    /**< �����������Ͷ��� */
typedef unsigned long    SOT_UINT32;   /**< �����������Ͷ��� */
typedef unsigned char    SOT_BOOL;     /**< �����������Ͷ��� */
typedef int              SOT_INT;      /**< �����������Ͷ��� */
typedef unsigned int     SOT_UINT;     /**< �����������Ͷ��� */
typedef float            SOT_FLOAT;    /* 32 bits float */


#define SOT_FALSE 0
#define SOT_TRUE 1

#define SOT_SUCCESS    0   /**< �ɹ� */
#define SOT_FAIL       1   /**< ʧ�� */

/** ��Чֵ���� */
#define SOT_INVALID8       0xFF        /**< 8λ��Чֵ���� */
#define SOT_INVALID16      0xFFFF      /**< 16λ��Чֵ���� */
#define SOT_INVALID32      0xFFFFFFFF  /**< 32λ��Чֵ���� */
#define SOT_INVALID_VALUE  -1          /**< λ��Чֵ���� */

/*****************�궨��*****************/
#define SOT_MAX_IPADDR_HEX_LEN 16  /**< ipv6��ַ��16���Ʊ�ʾ���ֽڳ��� */

#define SOT_PRODUCT_INFO_LEN 64 /** ��Ʒ��Ϣ����*/

//���кţ���ͨ���ŵ���󳤶�
#define  MAX_CALL_NUM_LEN  256 /** ��SIPC_MAX_NAME_LEN����һ��*/

//����ŵ���󳤶�
#define  MAX_CONF_NUM_LEN 256 /** ��SIPC_MAX_NAME_LEN����һ��*/

typedef enum tagSOT_IP_VER_E
{
	SOT_IP_V4 = 0, /**< IPЭ��ջ�汾:v4 */
	SOT_IP_V6 = 1  /**< IPЭ��ջ�汾:v6 */

}SOT_IP_VER_E;


//����֧�ֵ���Ƶ������G711a��G711u
typedef enum tagSOT_CAP_AUDIO_E
{
	SOT_CAP_AUDIO_G711_A, //G711a
	SOT_CAP_AUDIO_G711_U, //G711u
	SOT_CAP_AUDIO_END,
}SOT_CAP_AUDIO_E;


//ý�����ͣ���Ƶ����Ƶ
typedef enum 
{
	SOT_MEDIA_AUDIO,    //��Ƶ���ݲ�֧�֣����������չ
	SOT_MEDIA_VIDEO,   //��Ƶ��ֻ֧��H.264
	SOT_MEDIA_END
}SOT_MEDIA_TYPE_E;


//���͵���������
typedef enum
{
	RTP_H264_DATA,    //���ƽ̨�Ѿ����RTP��
	RAW_H264_DATA     //һ֡��������
}SOT_H264_DATA_TYPE_E;


//������Ƶ��������
typedef enum
{
	G711_A_AUDIO_DATA,    //G711a
	G711_U_AUDIO_DATA     //G711u
}SOT_AUDIO_DATA_TYPE_E;


typedef struct tagSOT_IP_ADDR_S
{
	SOT_IP_VER_E eIpVesion;          /**< ip Э��汾 */
	SOT_UINT32  ipv4;                /**< ipV4��ֵַ */
	SOT_UINT8   ipv6[SOT_MAX_IPADDR_HEX_LEN];/**< ipV6��ֵַ */

}SOT_IP_ADDR_S;


/** media chan rtp info*/
typedef struct tagSOT_MEDIA_RTP_INFO_S
{
	SOT_IP_ADDR_S  stRtpAddr;  /**< RTP �� ַ�ṹ */
	SOT_UINT16     usRtpPort;  /**< RTP �˿ں� */
	SOT_UINT16     usRtcpPort; /**< RTCP �˿ں�  */
}SOT_MEDIA_RTP_INFO_S;


//��־����
typedef enum tagSOT_LOG_LEVEL_E
{
	SOT_LOG_ERROR,      //����
	SOT_LOG_WARNING,    //����
	SOT_LOG_INFO,       //��Ϣ
	SOT_LOG_TRACE       //Trace��Ϣ
}SOT_LOG_LEVEL_E;


//ʹ�����ն�ʵ�壬vsd����cgw
typedef enum tagSOT_ENTITY_TYPE_E
{
	SOT_ENTITY_VSD,      //VSD
	SOT_ENTITY_CGW    //CGW
}SOT_ENTITY_TYPE_E;


/** ý���շ�ģʽ*/
typedef enum tagSOT_MEDIA_MODE_E
{
	SOT_MEDIA_MODE_BUTT = 0x00, 
	SOT_AUDIO_SILENCE = 0x01,  /*��Ƶ����Ĭ������Ҳ����*/
	SOT_AUDIO_RECVONLY = 0x02, /*��Ƶ��ֻ��*/
	SOT_AUDIO_SENDONLY = 0x04, /*��Ƶ��ֻ��*/
	SOT_AUDIO_SENDRECV = 0x06, /*��Ƶ���շ�*/

	SOT_VIDEO_SILENCE = 0x10,  /*��Ƶ����Ĭ������Ҳ����*/
	SOT_VIDEO_RECVONLY = 0x20, /*��Ƶ��ֻ��*/
	SOT_VIDEO_SENDONLY = 0x40, /*��Ƶ��ֻ��*/
	SOT_VIDEO_SENDRECV = 0x60, /*��Ƶ���շ�*/
}SOT_MEDIA_MODE_E;


/** ͨ��״̬*/
typedef enum tagSOT_CHANNEL_STATUS_E
{
	SOT_CHANNEL_IDLE,   /*ͨ������*/
	SOT_CHANNEL_ACTIVE, /*ͨ��ռ��*/
	SOT_CHANNEL_BUTT    /*�Ƿ���δ�����Ӧ��ͨ��*/
}SOT_CHANNEL_STATUS_E;


//���պ����Ƿ�ɹ�
typedef enum tagSOT_REC_CALL_STAT_E
{
	SOT_RECV_CALL_SUCCESS,	//���պ��гɹ�
	SOT_RECV_CALL_FAIL     //���պ���ʧ��  

}SOT_RECV_CALL_STAT_E;

//����session�Ƿ�ɹ�
typedef enum tagSOT_CREATE_SESSION_STAT_E
{
	SOT_CREATE_SESSION_FAIL,      //����sessionʧ��
	SOT_CREATE_SESSION_SUCCESS    //����session�ɹ�

}SOT_CREATE_SESSION_STAT_E;

//���󱨸�����
typedef enum tagSOT_ERROR_CODE_E
{
	SOT_INIT_STACK_ERROR,			/*��ʼ��Э��ջʧ��*/
	SOT_RTP_SESSION_CREATE_FAILED,   /*����RTP�Ựʧ��*/
}SOT_ERROR_CODE_E;

/** ϵͳ���ò���*/
typedef struct tagSOT_SYSCFG_S
{
	/*����SIP����*/
	SOT_IP_ADDR_S  stLocalAddr; /*���˵�ַ*/   
	SOT_UINT16 usLocalPort;      /*����SIP�˿ں�*/
	SOT_IP_ADDR_S stLocalAddr2;	/*���˵�ַ2*/   
	SOT_UINT16 usLocalPort2;      /*���˶˿ں�2*/

	SOT_UINT16 usLocalRtpBasePort; /*����RTP�����˿ڣ���������6000~60000֮��*/
	SOT_UINT16 usLocalRtpPortNum; /*����RTP�˿ڸ���*/

	/*�շ�ģʽ*/
	SOT_UINT16 usMediaMode; /*ý���շ�ģʽ*/

	/*������Ϣ����*/
	SOT_LOG_LEVEL_E  eLogLevel; /*�������*/

	SOT_CAP_AUDIO_E eCapAudio; //���е���Ƶ����

	SOT_ENTITY_TYPE_E eEntityType;//ʹ�����ն˵�ʵ�壬vsd����cgw

	/*��Ʒ��Ϣ����*/
	SOT_INT8 acProductInfo[SOT_PRODUCT_INFO_LEN+1];
	SOT_UINT32 ulProductInfoLen;

}SOT_SYSCFG_S;

//����ͨ��ʱ��Ҫ�Ĳ���
typedef struct tagSOT_CHANNEL_INFO_S
{
	SOT_INT8 * pcConfNumber;     //�����
	SOT_UINT32    ulConfLen;     //����ŵĳ���
	SOT_INT8 * pcCallNumber; //ͨ����
	SOT_UINT32    ulCallLen;     //ͨ���ŵĳ���
}SOT_CHANNEL_INFO_S;

typedef struct tagSOT_START_CALL_S
{
	SOT_UINT16		usSotNum; /*ͨ����*/
	SOT_UINT32     ulLocalUserNameLen;
	SOT_UINT8      aucLocalUserName[MAX_CALL_NUM_LEN + 1]; /**< ���˺��� */
	SOT_UINT32     ulRmtUserNameLen;/**< Զ�˺��볤�� */
	SOT_UINT8      aucRmtUserName[MAX_CONF_NUM_LEN + 1];  /**< Զ�˺��� */

	SOT_IP_ADDR_S  stRmtAddr;      /**< Զ��ip */
	SOT_UINT16     usRmtPort;      /**< Զ�˶˿ں� */

	SOT_UINT32		ulCallRate;     /* call bandwidth kbps*/
}SOT_START_CALL_S;

typedef struct tagSOT_END_CALL_S
{
	SOT_UINT16 usSotNum;
	SOT_UINT32 ulReason; /*�Ҷ�ԭ��*/
}SOT_END_CALL_S;


/*�ϲ�Ӧ�ô��룬��־��ػص�����*/
typedef SOT_UINT32 (* pFnSotLog)(SOT_LOG_LEVEL_E eLevel,SOT_INT8 * pcLog,SOT_UINT32 lLen);


/** ����I֡�ش�(ע�����й�����עI֡������������ʧ�����ԣ���ص������ڲ���֤) */
typedef SOT_UINT32 (* pFnSotIFrameReq)(IN SOT_INT8 * pcSotNum);


/** �������պ����Ƿ�ɹ���֪ͨ�ص�������ע����ֻ���ڽ��պ��гɹ��ŵ��øûص������� */
typedef SOT_VOID (*pFnSotReceiveCallNotify)(SOT_INT8 * pcSotNum,SOT_RECV_CALL_STAT_E eRecStat);


/** ����session�Ƿ�ɹ���֪ͨ�ص�������ע����ֻ���ڴ���session�ɹ��ŵ��øûص������� */
typedef SOT_VOID (*pFnSotCreateSessionNotify)(SOT_INT8 * pcSotNum,SOT_CREATE_SESSION_STAT_E eCreSessionStat,SOT_MEDIA_TYPE_E ucMediaType, SOT_UINT8 ucPayloadType,SOT_UINT16 usReceivePort);


/** ���йҶϵĻص����� */
typedef SOT_VOID (*pFnSotCallHangup)(SOT_INT8 * pcSotNum);

/** �����ϱ�����*/
typedef SOT_VOID (*pFnSotErrorReport)(SOT_INT8 * pcSotNum, SOT_ERROR_CODE_E eErrorCode);


/*���ϲ㴫��Ļص�����*/
typedef struct  tagSOT_APP_REG_FN_S
{
	/*��־���*/
	pFnSotLog				pfSotCallLogFunc;          /**< log����ص��ӿ� */

	/*I֡�ش�*/
	pFnSotIFrameReq			pfSotIFrameReq;     /**< ý����������ϱ� */

	/*���н���*/
	pFnSotReceiveCallNotify	pfSotReceiveCallNotify;  /**< �������պ����Ƿ�ɹ���֪ͨ�ص����� */

	/*session����*/
	pFnSotCreateSessionNotify	pfSotCreateSessionNotify;  /**< ����session�Ƿ�ɹ���֪ͨ�ص����� */

	/*���йҶ�*/
	pFnSotCallHangup		pfSotCallHangup;    /**< ���йҶϻص����� */

	pFnSotErrorReport		pfSotErrorReport; /**< ���󱨸�*/	
}SOT_APP_REG_FN_S;

#ifdef __cplusplus
	}
#endif

#endif /*__SOT_TYPE_H__*/
