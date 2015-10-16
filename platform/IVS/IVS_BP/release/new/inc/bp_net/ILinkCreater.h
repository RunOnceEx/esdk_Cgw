/********************************************************************
filename    :    LinkCreater.h
author      :    j00213308
created     :    2012/04/06
description :    LinkCreater�ӿ�ͷ�ļ�
copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
history     :    2012/04/06 ��ʼ�汾
*********************************************************************/
#ifndef LINK_CREATER_H
#define LINK_CREATER_H

#include "bp_def.h"
#include "bp_namespace.h"

#include <string>
#include <list>
#include <map>

NAMESPACE_BP_BEGIN		// IVS NAMESPACE

// ǰ������
class ILink;
class IMsgHandle;
class IProtocol;
class ILinkCreater;

// LinkCreater�ӿ�
class EXPORT_DLL ILinkCreater
{
public:
	ILinkCreater(void);
	virtual ~ILinkCreater(void);

    /**************************************************************************
    * name       : CreateLink
    * description: ����ILink����
    * input      : NA
    * output     : NA
    * return     : ��NULL - �ɹ���NULL - ʧ��
    * remark     : ����ILink�������󣬰�����Э��ջ����
    **************************************************************************/
	ILink* CreateLink(void);

    /**************************************************************************
    * name       : SetLinkProperty
    * description: ����LinkCreater������
    * input      : iLinkType    : �������ͣ�  0 - UDP
	*										  1 - TCP
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	void SetLinkProperty(int iLinkType);
	
	/**************************************************************************
	* name       : SetTimeout
	* description: ���ó�ʱʱ��
	* input      : uiTimeout����ʱʱ��
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
	void SetTimeout(unsigned int uiTimeout);

	/**************************************************************************
	* name       : SetHeartBeat
	* description: �����������
	* input      : uiHeartBeat���������
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
	void SetHeartBeat(unsigned int uiHeartBeat);

	/**************************************************************************
	* name       : SetSecuritySocket
	* description: �����Ƿ��贴����ȫ�׽���
	* input      : bSecuritySocket���Ƿ��贴����ȫ�׽���
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
	void SetSecuritySocket(bool bSecuritySocket);

	/**************************************************************************
	* name       : GetSecuritySocket
	* description: ��֪�Ƿ��贴����ȫ�׽���
	* input      : NA
	* output     : NA
	* return     : bool���Ƿ��贴����ȫ�׽���
	* remark     : NA
	**************************************************************************/
	bool GetSecuritySocket(void) const;

	/**************************************************************************
	* name       : SetPriPemFileKey
	* description: ����SSL����˵�˽Կ�ļ���key(���ܹ���)
	* input      : strPriPemFileKey��SSL����˵�˽Կ�ļ���key(���ܹ���)
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
	void SetPriPemFileKey(const std::string & strPriPemFileKey);

	/**************************************************************************
	* name       : GetPriPemFileKey
	* description: ��֪SSL����˵�˽Կ�ļ���key(���ܹ���)
	* input      : NA
	* output     : NA
	* return     : const std::string &��SSL����˵�˽Կ�ļ���key(���ܹ���)
	* remark     : NA
	**************************************************************************/
	const std::string & GetPriPemFileKey(void) const;

    /**************************************************************************
	* name       : SetAuthType
	* description: ���ü�Ȩ����
	* input      : NA
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    void SetAuthType(ProtocolAuthType enAuthType);

    /**************************************************************************
	* name       : GetAuthType
	* description: ��ȡ��Ȩ����
	* input      : NA
	* output     : NA
	* return     : ProtocolAuthType
	* remark     : NA
	**************************************************************************/
    ProtocolAuthType GetAuthType() const;

    /**************************************************************************
	* name       : SetAuthMessageList
	* description: ���ü�Ȩ��Ϣ�б�
	* input      : NA
	* output     : NA
	* return     : ProtocolAuthType
	* remark     : NA
	**************************************************************************/
    void SetAuthMessageList(const std::list<uint32_t>& authMessageList);

    /**************************************************************************
	* name       : GetAuthMessageList
	* description: ��ȡ��Ȩ��Ϣ�б�
	* input      : NA
	* output     : NA
	* return     : const std::list<uint32_t>& ��Ȩ��Ϣ�б�
	* remark     : NA
	**************************************************************************/
    const std::list<uint32_t>& GetAuthMessageList();

    /**************************************************************************
	* name       : SetAuthKey
	* description: �����key
	* input      : const std::string& strAuthKey
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    void SetAuthKey(const std::string& strAuthKey);

    /**************************************************************************
	* name       : GetAuthKey
	* description: �����key
	* input      : NA
	* output     : NA
	* return     : const std::string& 
	* remark     : NA
	**************************************************************************/
    const std::string& GetAuthKey() const;
protected:
    /**************************************************************************
    * name       : BuildMsgHandle
    * description: ������Ϣ������
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : �ض�link creater����ʵ��,��ȡ��Ӧ����Ϣ������
    **************************************************************************/
	virtual IMsgHandle* BuildMsgHandle(void) = 0;

    /**************************************************************************
    * name       : BuildProtocol
    * description: ����Э��ջ
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	virtual IProtocol* BuildProtocol(void) = 0;


private:
    /**************************************************************************
    * name       : BuildLink
    * description: ������������,��������
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : NA
    **************************************************************************/
	ILink* BuildLink(void);

protected:
    int          m_iLinkType;         // ��������

    unsigned int m_uiTimeout;         // ��ʱʱ��
    unsigned int m_uiHeartBeat;       // �������

    bool         m_bSecuritySocket;   // �Ƿ���Ҫʹ��SSLЭ�鴫������(ֻ֧��TCP)
    std::string  m_strPriPemFileKey;  // SSL����˵�˽Կ�ļ���key(���ܹ���)

    ProtocolAuthType m_enAuthType;
    std::string  m_strAuthKey;
    std::list<uint32_t> m_authMessageList;
};

NAMESPACE_BP_END

#endif // LINK_CREATER_H
