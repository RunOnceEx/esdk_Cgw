/*****************************************************************************
  Copyright (C), 2014-2020, Huaweisymantec Tech. Co., Ltd.
  FileName: ivs_ps2es_parse.h
  Author: yWX153026
  Version : v0.1
  Date:
  Description: Header File of ivs_ps2es_parse.cpp
  Function List:
  History:
*****************************************************************************/
#ifndef IVS_PS2ES_PARSE_H
#define IVS_PS2ES_PARSE_H

#include "ivs_ps_head.h"
#include "ivs_namespace.h"

NAMESPACE_CBB_BEGIN

class EXPORT_DLL CPs2EsParse
{
public:
    CPs2EsParse();
    ~CPs2EsParse();

    /**************************************************************************
    * name       : parsePSPack
    * description: ��һ֡PS����ת��ES����
    * input      : pFrameDate PS������Ϣ
                   iFrameLength PS��������
    * output     : pVideoData �����õ���Ƶ����
                   uiVideoLength �����õ���Ƶ���ݳ���
                   pAudioData �����õ���Ƶ����
                   uiAudioLength �����õ���Ƶ���ݳ���
                   pPSHeader �������֮��PS��ͷ������
    * return     : �ɹ���IVS_SUCCESS ʧ�ܣ�IVS_FAIL
    * remark     : ����
    **************************************************************************/
    int parsePSPack(const char* pFrameDate, int iFrameLength, char*& pVideoData, 
        unsigned int& uiVideoLength, char*& pAudioData, unsigned int& uiAudioLength, LPPS_HEADER_TOTALL_S& pPSHeader);

private:
    /**************************************************************************
    * name       : parsePSHeader
    * description: ����PSͷ
    * input      : pPSHeader PS������Ϣ
                   iLeftLength ʣ����������
    * output     : iLeftLength ���������֮��ʣ����������
                   pPSHeaderInput ָ�������ǰͷ��ָ��ͷ����һ���ֽ�
    * return     : �ɹ���IVS_SUCCESS ʧ�ܣ�IVS_FAIL
    * remark     : ����
    **************************************************************************/
    int parsePSHeader(const char*& pPSHeaderInput, int& iLeftLength);

    /**************************************************************************
    * name       : parsePSSystemHeader
    * description: ����ps����ϵͳͷ
    * input      : pSystemHeader PS������Ϣ
                   iLeftLength ʣ����������
    * output     : iLeftLength ����������µ���������
                   pSystemHeaderInput �����굱ǰͷ��ָ����һ��δ������ֽ�
    * return     : �ɹ���IVS_SUCCESS ʧ�ܣ�IVS_FAIL
    * remark     : ����
    **************************************************************************/
    int parsePSSystemHeader(const char*& pSystemHeaderInput, int& iLeftLength);

    /**************************************************************************
    * name       : parsePSPESPack
    * description: ����PES��
    * input      : pPESHeader PS������Ϣ
                   iLeftLength ʣ����������
    * output     : iLeftLength ����������µ���������
                   pPESHeaderInput �����굱ǰͷ��ָ����һ��δ������ֽ�
    * return     : �ɹ���IVS_SUCCESS ʧ�ܣ�IVS_FAIL
    * remark     : ����
    **************************************************************************/
    int parsePSPESPack(const char*& pPESHeaderInput, int& iLeftLength);

    /**************************************************************************
    * name       : getPtsDtsValue
    * description: ��ȡPESͷ��PTS��DTS����
    * input      : pPESParam ָ��PTS���ݵ�ָ��
                   ucPtsDtsFlags PTS DTS��־λ
    * output     : NA
    * return     : �ɹ���IVS_SUCCESS ʧ�ܣ�IVS_FAIL
    * remark     : ����
    **************************************************************************/
    int getPtsDtsValue(char*& pPESParam, unsigned char ucPtsDtsFlags);

    /**************************************************************************
    * name       : NtoH
    * description: �������ֽ���ת�������ֽ���
    * input      : pValue ��Ҫת���Ŀ�ʼ�ֽڵ�ַ
                   ucLen ��Ҫת���ĳ���
    * output     : NA
    * return     : NA
    * remark     : ����
    **************************************************************************/
    void NtoH(char* pValue, unsigned char ucLen);

private:
    char* m_pESVideoData;           //�����õ�����Ƶ����
    char* m_pESAudioData;           //�����õ�����Ƶ����
    unsigned int m_usESVidoeLength; //�����õ�����Ƶ���ݳ���
    unsigned int m_usESAudioLength; //�����õ�����Ƶ���ݳ���
    PS_HEADER_TOTALL_S m_PSHeaderInfo;
};

NAMESPACE_CBB_END

#endif // IVS_PS2ES_PARSE_H