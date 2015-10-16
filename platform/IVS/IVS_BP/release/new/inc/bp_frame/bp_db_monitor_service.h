/********************************************************************
filename    :    bp_db_monitor_service.h
author      :    x00196467
created     :    2014/07/29
description :    db���ӵļ���߳�
copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
history     :    2014/07/29 ��ʼ�汾
*********************************************************************/

#ifndef BP_DB_MONITOR_SERVICE_H
#define BP_DB_MONITOR_SERVICE_H

#include "IService.h"

class EXPORT_DLL CDBMonitorService : public BP::IService
{
public:
    CDBMonitorService ();
    virtual ~CDBMonitorService(void);

public:
    /**************************************************************************
    * name       : HandleCmd
    * description: ���������������ʵ������Ҫ��������
    * input      : pCmd ����ָ��
    * output     : NA
    * return     : IVS_SUCCEED - �ɹ���IVS_FAIL - ʧ��
    * remark     : NA
    **************************************************************************/
    virtual int HandleCmd(BP::CCmd* pCmd);

    /**************************************************************************
    * name       : Routing
    * description: ���ڼ�飬��������ʵ���ദ���ڼ������
				   ע�⣺һ��Ҫͳ�Ʊ���routing��ɵ��¼������̵߳���ѯ�����ڴ�ͳ�ƣ�����
    * input      : NA
    * output     : NA
    * return     : ���ر���rouint��ɵ��¼��������ں���ͳ��
    * remark     : NA
    **************************************************************************/
    virtual uint32_t Routing(void);

private:

    time_t m_tLastCheckTime;
};

#endif