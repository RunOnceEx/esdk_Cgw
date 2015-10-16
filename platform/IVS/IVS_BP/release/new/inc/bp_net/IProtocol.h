/********************************************************************
filename    :    IProtocol.h
author      :    j00213308
created     :    2012/04/06
description :    Э��ջ�ӿ�
copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
history     :    2012/04/06 ��ʼ�汾
*********************************************************************/
#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include "bp_def.h"
#include "Cmd.h"
#include "IMsgHandle.h"
#include "ILink.h"

NAMESPACE_BP_BEGIN        // IVS NAMESPACE

// Э��ӿ�
class IProtocol
{
public:
    IProtocol(void)
        : m_pILink(NULL)
        , m_pMsgHandle(NULL)
        , m_bAuthed(true)
        , m_tConnectTime(0)
        , m_enAuthType(AUTH_NONE)
    {}
    virtual ~IProtocol(void) { HW_DELETE(m_pMsgHandle); }
private:
    IProtocol(const IProtocol&src)
    {
    }

    IProtocol& operator=(const IProtocol&)
    {
        return *this;
    }

public:

    /**************************************************************************
    * name       : HandleCmd
    * description: ����������Ϣ
    * input      : pCmd : �账���������Ϣ
    * output     : NA
    * return     : NA
    * remark     : �����ڴ�ͨ��Э��ջ������Ϣ��
    **************************************************************************/
    virtual void HandleCmd(CCmd* pCmd) = 0;
    
    /**************************************************************************
    * name       : Routing
    * description: �г̴���
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : ����Э��ջ������
    **************************************************************************/
    virtual void Routing(void) = 0;

    /**************************************************************************
    * name       : NotifyOpen
    * description: ֪ͨЭ��ջ���ӽ���
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : ���ӽ���ʱ�����ص���֪ͨЭ��ջ
    **************************************************************************/
    virtual void NotifyOpen(void) = 0;

    /**************************************************************************
    * name       : NotifyClose
    * description: ֪ͨЭ��ջ���ӶϿ�
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : ���ӶϿ�ʱ�����ص���֪ͨЭ��ջ
    **************************************************************************/
    virtual void NotifyClose(void) = 0;

    /**************************************************************************
    * name       : NotifyTimeout
    * description: ֪ͨЭ��ջ���ӳ�ʱ
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : ���ӳ�ʱʱ�����ص���֪ͨЭ��ջ
    **************************************************************************/
    virtual void NotifyTimeout(void) = 0;
    
    /**************************************************************************
    * name       : NotifyRecv
    * description: ֪ͨЭ��ջ�����ݵ���
    * input      : NA
    * output     : NA
    * return     : NA
    * remark     : �����������ݵ���ʱ�����ص���֪ͨЭ��ջ��
    *              ��ʱ��Э��ջӦ�������Ӷ���Ľ������ݺ���
    **************************************************************************/
    virtual int NotifyRecv(void) = 0;

	/**************************************************************************
	* name       : SetLink
	* description: �������Ӷ���
	* input      : pILink�����Ӷ���
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    inline void SetLink(ILink* pILink) { m_pILink = pILink; }
    
	/**************************************************************************
	* name       : SetMsgHandle
	* description: ������Ϣ�������
	* input      : pMsgHandle����Ϣ�������
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    inline void SetMsgHandle(IMsgHandle* pMsgHandle) { m_pMsgHandle = pMsgHandle; }

	/**************************************************************************
	* name       : LinkStatusReport
	* description: ����״̬�ϱ�
	* input      : linkState�� ����״̬�������д򿪣���ɣ���ʱ����
	*              pszTransID������ID
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    virtual void LinkStatusReport(enum enLinkState linkState, const char* pszTransID) = 0;

    /**************************************************************************
	* name       : SetAuthFalg
	* description: ���ü�Ȩ��ʶ
	* input      : bool bAuthFlag
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    void SetAuthFlag(bool bAuthFlag) { m_bAuthed = bAuthFlag; }

    /**************************************************************************
	* name       : IsAuthed
	* description: ͨ���Ƿ��Ѿ���Ȩ
	* input      : NA
	* output     : NA
	* return     : bool �Ƿ��Ѿ���Ȩ
	* remark     : NA
	**************************************************************************/
    inline bool IsAuthed(void) { return m_bAuthed; }

    /**************************************************************************
	* name       : SetAuthType
	* description: ���ü�Ȩ����
	* input      : NA
	* output     : NA
	* return     : NA
	* remark     : NA
	**************************************************************************/
    inline void SetAuthType(ProtocolAuthType enAuthType) { m_enAuthType = enAuthType; }

    /**************************************************************************
	* name       : GetAuthType
	* description: ��ȡ��Ȩ����
	* input      : NA
	* output     : NA
	* return     : ProtocolAuthType
	* remark     : NA
	**************************************************************************/
    ProtocolAuthType GetAuthType() const{ return m_enAuthType; }

    /**************************************************************************
	* name       : SetAuthMessageList
	* description: ���ü�Ȩ��Ϣ�б�
	* input      : NA
	* output     : NA
	* return     : ProtocolAuthType
	* remark     : NA
	**************************************************************************/
    void SetAuthMessageList(const std::list<uint32_t>& authMessageList) { m_authMessageList = authMessageList; }

    /**************************************************************************
	* name       : IsAuthMessage
	* description: �鿴��Ϣ�����Ƿ��Ǽ�Ȩ��Ϣ
	* input      : NA
	* output     : NA
	* return     : const std::list<uint32_t>& ��Ȩ��Ϣ�б�
	* remark     : NA
	**************************************************************************/
    bool IsAuthMessage(uint32_t uiMessageType) { return  ( m_authMessageList.end() != std::find(m_authMessageList.begin(), m_authMessageList.end(), uiMessageType) ); }

    /**************************************************************************
	* name       : SetAuthKey
	* description: ����Э�������Կ�����ģ�
	* input      : NA
	* output     : NA
	* return     : strAuthKey
	* remark     : NA
	**************************************************************************/
    void SetAuthKey(const std::string& strAuthKey) { m_strAuthKey = strAuthKey; }

    /**************************************************************************
	* name       : GetAuthKey
	* description: �����key
	* input      : NA
	* output     : NA
	* return     : const std::string& 
	* remark     : NA
	**************************************************************************/
    const std::string& GetAuthKey() const { return(m_strAuthKey); }

    time_t GetConnectTime(void) const { return m_tConnectTime; }

    void SetConnectTime(time_t tConnectTime)  { m_tConnectTime = tConnectTime; }
    
protected:
    ILink*        m_pILink;      // ���Ӷ���ָ��
    IMsgHandle*   m_pMsgHandle;  // ��Ϣ������ָ��
    bool          m_bAuthed;     // ͨ���Ƿ��Ѿ���Ȩ
    time_t        m_tConnectTime; // ���Ӵ�ʱ��
    ProtocolAuthType m_enAuthType;
    std::string  m_strAuthKey;
    std::list<uint32_t> m_authMessageList;
};

NAMESPACE_BP_END

#endif    // IPROTOCOL_H
