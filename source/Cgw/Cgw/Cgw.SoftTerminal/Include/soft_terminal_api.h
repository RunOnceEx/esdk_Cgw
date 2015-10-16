/*****************************************************************************
*               Copyright (C) 2013, Huawei Tech. Co., Ltd.               
*                           ALL RIGHTS RESERVED                               
* FileName: soft_terminal_api.h                                                          
* Version: 1.0                                                                
* Description:  ����ģ��ĺ��д���ͷ�ļ�    
*                                                                             
* History:                                                                    
* 1. 2013-03-14,y00186060 Create this file.                                 
******************************************************************************/

#ifndef __CALL_MGNT_H__
#define __CALL_MGNT_H__

#include "soft_terminal_type.h"


#ifdef __cplusplus
extern "C"{
#endif


//��ʼ����������
/* see in soft_terminal_type.h*/

//�ⲿע��Ļص���������
/* see in soft_terminal_type.h*/

//��ʼ����
SOT_BOOL SoftTerminalInit(const SOT_SYSCFG_S * pstParamSet,const SOT_APP_REG_FN_S *pstCallBackSet);

//��Ӻ���ͨ��
SOT_BOOL SoftTerminalAddCallChannel(const SOT_CHANNEL_INFO_S * pstChannelInfo);

//ɾ������ͨ��
SOT_BOOL SoftTerminalDeleteCallChannel(SOT_INT8 * pcCallNumber,SOT_UINT32 ulCallNumberLen);

//�������ݣ���2�����ݣ�1��rtp����2��һ֡���������
SOT_BOOL SoftTerminalSendVideoData(SOT_INT8 * pcCallNumber, SOT_H264_DATA_TYPE_E edataType,SOT_UINT8 * pucData,SOT_UINT32 ulDataLen);

//������Ƶ���ݣ��ɵĽӿڣ���ɾ��  
SOT_BOOL SoftTerminalSendAudioData(SOT_INT8 * pcCallNumber,SOT_UINT8 * pucData,SOT_UINT32 ulDataLen);

//������Ƶ����(G.711a����G.711u) 
SOT_BOOL SoftTerminalSendG711AudioData(SOT_INT8 * pcCallNumber,SOT_AUDIO_DATA_TYPE_E edataType,SOT_UINT8 * pucData,SOT_UINT32 ulDataLen);

//����I֡�ش�
SOT_BOOL SoftTerminalRequestIFrame(SOT_INT8 * pcCallNumber);

//��ѯͨ��״̬
SOT_CHANNEL_STATUS_E SoftTerminalGetChannelStatus(SOT_INT8 * pcCallNumber);


#ifdef __cplusplus
}
#endif

#endif
