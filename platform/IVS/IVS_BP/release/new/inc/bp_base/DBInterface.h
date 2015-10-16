/********************************************************************
filename    :    DBInterface.h
author       :     z00193167
created      :    2012/04/13
description :    ���ݿ�ӿ���
copyright   :    Copyright (c) 2012-2016 Huawei Tech.Co.,Ltd
history       :     2012/04/13 ��ʼ�汾
*********************************************************************/
#ifndef DB_INTERFACE_H
#define DB_INTERFACE_H

#include "bp_mutex.h"
#include "ace_header.h"
#include "db_connect.h"
#include "bp_db_config.h"
#include <string>
#include <queue>
#include <map>
#include "bp_errno.h"

#ifdef WIN32
    #define DATBASE_CONFIG_FILE_NAME ("\\db.xml")
#else
    #define DATBASE_CONFIG_FILE_NAME ("/db.xml")
#endif

#ifdef ARM_HIS3531
#define BP_ERROR                  (-1)
#define BP_CON_DATE_LEN_USUAL               (51)
#define BP_STRING_START_MINSYSTEM_FILE                ("/mnt/minsystem")
#define BP_CON_READ_DATE_LESS_THAN_DEF                 (1)
#define BP_STRING_START_MINSYSTEM_SIGN                ("-minsystem")


int BPReadFile(char *dev,char *pcBuf,int iLen);
int BpReadMinSystem(void);

#endif

#define BP_CONNPOOL_EMPTY 0
#define BP_CONNPOOL_SIZE  1 
#define BP_CONNPOOL_MAX_SIZE 10
#define LOCAL_DB  0
#define CENTER_DB 1
#define LOCAL_DB_INDEX  0
#define CENTER_DB_INDEX 1
#define LOCAL_DB_POOL_NUM 1
#define CLUSTER_DB_POOL_NUM 2
#define MAX_DB_POOL_NUM 2
typedef DLLEXPORT DB_CONNECT_TYPE BP_DBTYPE;

typedef bool (*DBExceptionCallBack)(int, const char *, const char *);

const unsigned int DB_EXCEPTION_USER_LENGTH   = 32;
const unsigned int DB_EXCEPTION_SERVER_LENGTH = 256;

typedef struct DBAlarmInfo
{
    uint32_t      uiErrorCode;                          // ������
    char          szUser[DB_EXCEPTION_USER_LENGTH];     // �û���
    char          szServer[DB_EXCEPTION_SERVER_LENGTH]; // ������URL
} DB_ALARM_INFO;

typedef IDBConnect* (*CreateDBHandle)();
typedef void (*InitDBContextHandle)(DBExceptionCallBack);

enum
{
    DB_ALARM_FOR_CONNECT_FAIL = 600,   // ���ݿ�����ʧ��
    DB_ALARM_FOR_ACCESS_FAIL,          // ���ݿ����ʧ��
    DB_ALARM_FOR_CONNECT_RESUME,       // ���ݿ����ӻָ�
    DB_ALARM_FOR_ACCESS_RESUME         // ���ݿ���ʻָ�
};

/**
 * @class ���ݿ������ࡣ
 * @brief ��ȡ���ݿ����Ӳ������������ݿ����ӡ�
 * ���ݿ����ӳ��ṩ2�ַ�����(ֻ��2ѡ1������ͬʱʹ��)
 * 1. �������ݿ����ӳأ�
 *    1����������ʱ������һ�����ݿ����ӳأ������ӳذ���N�����ݿ����ӡ�
 *    2).��ĳ���߳�Ҫ�������ݿ�ʱ���Ӹ����ӳ����������һ�����ݿ����ӣ�ʹ����֮���ٹ黹�����ӳء�
 *    �ӿ��У�Init(), GetConnection(), PutConnToPool()
 * 2. �߳�ר�����ݿ�����
 *    1).ͨ�����ã�һ���߳�һ�����ݿ�����, һ�����ݿ�����ֻ�ܱ�ָ�����̣߳�һ���߳�Ҳֻ��ʹ��ָ�������ݿ����ӡ�
 *       �߳�����ʱ����ȡ�����ļ��е����ݿ����ӱ�־��ȷ���Ƿ�Ҫ�������ݿ⡣
 *    2).һ�������У������̲߳����Է������ݿ⡣
 *    �ӿ��У� Init(), GetThreadDBConnection()
 */
class DLLEXPORT CDBDriverManager
{
private:
    CDBDriverManager ( void );

    CDBDriverManager ( CDBDriverManager& );

    CDBDriverManager& operator = ( CDBDriverManager& );

public:
    virtual ~CDBDriverManager ( void );

    /**********************************************************************
    * name           : Instance
    * description    : ���CDBDriverManager��ʵ��
    * input          : dbType, ���ӳع���ʵ�������ͣ�Ĭ����0
    * return         : BP_OK - �ɹ���ʼ�� BP_FAIL -��ʼ��ʧ��
    * remark         : NA   
    *********************************************************************/
    static CDBDriverManager& Instance ( int dbType = LOCAL_DB );

    /**********************************************************************
    * name           : IsNeedRefreshDBConn
    * description    : �Ƿ���Ҫ���ڸ������ݿ�����
    * input          : NA
    * return         : TRUE ��Ҫ���ڸ������ݿ����ӣ�FALSE����Ҫ
    * remark         : NA   
    *********************************************************************/
    static bool IsNeedRefreshDBConn();

    /**********************************************************************
    * name           : RefreshAllConn
    * description    : ������������
    * input          : NA
    * return         : NA
    * remark         : NA   
    *********************************************************************/
    static void RefreshAllConn();

    /**********************************************************************
    * name           : Init
    * description    : ���ݿ����ӹ�����ĳ�ʼ��
    * input          : pDBCallBackFunc ���ݿ��쳣�ص�����
    * return         : BP_OK - �ɹ���ʼ�� BP_FAIL -��ʼ��ʧ��
    * remark         : ҵ��ʼʱ����Ҫ���ã�������mainctrl��init�����е��á�
    *********************************************************************/
    int Init ( DBExceptionCallBack pDBCallBackFunc = NULL);

    /**********************************************************************
    * name           : Fini
    * description    : ���ݿ����ʱ���ã��������ݿ����ӳ�
    * input          : NA
    * return         : NA
    * remark         : ҵ�����ʱ��һ��Ҫ�ǵõ��ã�������mainctrl��uninit�����е��á�
    *********************************************************************/
    int Fini ( void );

    /**********************************************************************
    * name           : GetConnection
    * description    : ȡ��һ�����ݿ�����
    * input          : NA
    * return         : IDBConnect�����һ��ָ��
    * remark         : ���ô˺����ķ�������ӣ�����ʹ��PutConnToPool�Żسأ������ֶ��ͷš�
    *********************************************************************/
    IDBConnect* GetConnection ( void );

    /**********************************************************************
    * name           : PutConnToPool
    * description    : ��һ�����ӷŻ����ݿ����ӳ�
    * input          : ��Ӧ���͵����ݿ�����IDBConnect*
    * return         : NA
    * remark         : �����������ݿ�ľ���Żس�
    *********************************************************************/
    void PutConnToPool ( IDBConnect* );

    /**********************************************************************
    * name           : OpenConnection()
    * description    : ���̵߳�ר�����ݿ�����
    * input          : ��
    * return         : BP_OK - �򿪳ɹ� BP_FAIL - ��ʧ��
    * remark         : ����GetThreadDBConnection֮ǰ��������ô˷�����
    *********************************************************************/
    int OpenThreadDBConnection ();

    /**********************************************************************
    * name           : GetThreadDBConnect()
    * description    : ��ȡ�����̵߳��ض����ݿ�����
    * input          : ��
    * return         : �������ݿ�����
    * remark         : �˺�����������Ӳ������ֶ��ͷţ���������ʱ���Զ��ͷš�
    *********************************************************************/
    IDBConnect* GetThreadDBConnection( void );

    BP_DBTYPE GetDbType();

    /**********************************************************************
    * name           : GetServiceIp()
    * description    : ��ȡ��ǰ���ӵ����ݿ��ip
    * input          : ��
    * return         : �������ݿ�ip
    * remark         : ��������ݿ�ip��ʵ���Ǵ�db.xml�ж�ȡ������ip
    *********************************************************************/
	std::string GetServiceIp();
    void SetServiceIp(const std::string& strIp);

    void RefreshConn();
protected:
    /**********************************************************************
    * name           : NewConnection()
    * description    : �������ݿ�����(������)
    * input          : DB_ORACLE ����ORACLE���ݿ� DB_PGSQL ����Postgre SQL���ݿ�
    * return         : ��Ӧ���͵����ݿ�����IDBConnect*
    * remark         : NA   
    *********************************************************************/
    IDBConnect* NewConnection(BP_DBTYPE);

    //ȥ��
    /**********************************************************************
    * name           : GetConnection
    * description    : �������ݿ�����(������)
    * input          : ��������ַ���û���������
    * return         : ��Ӧ���͵����ݿ�����IDBConnect*
    * remark         : ORACLE��ʽ IP:port/db PGSQL��ʽ ODBC�е�����Դ����
    *********************************************************************/
    IDBConnect* GetConnection(BP_DBTYPE, const char*, const char*, const char*,const char*);

    /**********************************************************************
    * name           : CreateConnPool
    * description    : �������ݿ����ӳ�(������)
    * input          : ���ͣ���������ַ���û��������룬����������ѡ��
    * return         : ���ڵ����ݿ�������
    * remark         : �ش�С��Ĭ��ֵ���ɸ���ҵ�����е���
    *********************************************************************/
    int CreateConnPool(BP_DBTYPE, const char*, const char*, const char*,const char*,
                       int size = BP_CONNPOOL_SIZE);

    /**********************************************************************
    * name           : GetConnFromPool
    * description    : �����ݿ����ӳ���ȡһ������
    * input          : NA
    * return         : ��Ӧ���͵����ݿ�����IDBConnect*
    * remark         : �ӳ��л�ȡ���������ݿ�ľ��
    *********************************************************************/
    IDBConnect* GetConnFromPool ( void );


private:
    /**********************************************************************
    * name           : GetDBFcn
    * description    : �����Ӧ�Ķ�̬�⣬�������ݿ�
    * input          : DB_ORACLE ����ORACLE���ݿ� DB_PGSQL ����Postgre SQL���ݿ�
    * output         : NA
    * return         : �������ݿ���
    * remark         : NA   
    *********************************************************************/
    CreateDBHandle  GetDBFcn(const char*);

private:
#ifdef WIN32
    HINSTANCE       m_dbhandle;
#else
    void*             m_dbhandle;
#endif
    static CDBDriverManager m_Mgr[MAX_DB_POOL_NUM];                       //���ؿ������Ŀ��һ��ʵ��

    BP::CDatabaseConnectionConfig m_DatabaseConnectionConfig;             //���ݿ������ļ�

    CreateDBHandle m_CreateDBHnd;

    std::queue<IDBConnect*> m_pool;                                       //���ӳ�

    bool m_bInit;                                                         //��ʼ����־

    DBExceptionCallBack m_pDBCallBackFunc;                                //���ݿ��쳣�ص�����

    int m_iPoolSize;                                                      //���ӳ�������С

    ACE_Semaphore *m_Semaphore;                                           //��ȡ�����ź���

    BP_Recursive_Thread_Mutex m_mapConnMutex;                             //���ӡ�����ӳ���

    std::map<ACE_thread_t, IDBConnect* > m_mapConn;                       //���ӡ�����ӳ���

    int m_iDbType;                                                        //��ǰʵ�������ݿ����ͣ�0���ؿ⣬1���Ŀ�

    int m_iPoolVersion;                                                   //���ӳذ汾�ţ�����Ŵ�����
    
    static int m_iRefreshTime;
};

#endif // DB_INTERFACE_H

