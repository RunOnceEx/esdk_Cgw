#ifndef _db_connect_h
#define _db_connect_h


#include "db_parameter.h"
#include "db_result.h"


class DLLEXPORT  IDBConnect
{
public:
    IDBConnect():m_tCreateTime(time(NULL)){}
    virtual ~IDBConnect(){}

public:
    /**********************************************************************
    * name           : Connect
    * description    : ���ݿ����Ӻ������½�һ������
    * input          : pszDBServer-���ݿ��������pszUser-�û�����pszPasswd-����
    * output         : NA
    * return         : IVS_SUCCEED -���ӳɹ�  IVS_FAIL -����ʧ��
    * remark         : oracle��pgsql�����ݿ��������һ��,�����Ҫ����������������ӣ�ʹ��ReConnect
    *********************************************************************/
    virtual int Connect(const char* pszDBServer, const char* pszUser, const char* pszPasswd) = 0;

    /**********************************************************************
    * name           : ReConnect
    * description    : ��������
    * input          : pszDBServer-���ݿ��������pszUser-�û�����pszPasswd-����
    * output         : NA
    * return         : IVS_SUCCEED -���ӳɹ�  IVS_FAIL -����ʧ��
    * remark         : oracle��pgsql�����ݿ��������һ��   
    *********************************************************************/
    virtual int ReConnect(const char* pszDBServer, const char* pszUser, const char* pszPasswd) = 0;

    /**********************************************************************
    * name           : Execute
    * description    : ִ��SQL���
    * input          : pSql-SQL��䣬pParam-��̬������iParamSize-��������
    * output         : NA
    * return         : IDBResultSet* ���ݼ�
    * remark         : NA   
    *********************************************************************/
    virtual IDBResultSet* Execute(const char *pSql, CDBParam* pParam, int iParamSize) = 0;
    
    /**********************************************************************
    * remark         : ���ݽӿڣ�����MAUʹ�á�����ģ����ʹ��Execute
    **********************************************************************/
    IDBResultSet* Insert(const char *pSql, CDBParam* pParam, int iParamSize)
                            {return Execute(pSql, pParam, iParamSize);}
    IDBResultSet* Delete(const char *pSql, CDBParam* pParam, int iParamSize)
                            {return Execute(pSql, pParam, iParamSize);}
    IDBResultSet* Update(const char *pSql, CDBParam* pParam, int iParamSize)
                            {return Execute(pSql, pParam, iParamSize);}
    IDBResultSet* Select(const char *pSql, CDBParam* pParam, int iParamSize)
                            {return Execute(pSql, pParam, iParamSize);}

    /**********************************************************************
    * name           : SEQNextVal
    * description    : ���ص�ǰ��sequenceֵ������sequence�Զ���1
    * input          : seqName-seqence����
    * output         : NA
    * return         : long
    * remark         : NA   
    *********************************************************************/
    virtual int SEQNextVal(const char *seqName) = 0;

    /**********************************************************************
    * name           : Commit
    * description    : �����ύ
    * input          : NA
    * output         : NA
    * return         : IVS_SUCCEED -�ύ�ɹ�  IVS_FAIL -�ύʧ��
    * remark         : NA   
    *********************************************************************/
    virtual int Commit(void) = 0;

    /**********************************************************************
    * name           : Rollback
    * description    : �ع�����
    * input          : NA
    * output         : NA
    * return         : IVS_SUCCEED -�ع��ɹ�  IVS_FAIL -�ع�ʧ��
    * remark         : NA   
    *********************************************************************/
    virtual int Rollback(void) = 0;

    /**********************************************************************
    * name           : DisConnect
    * description    : �Ͽ����ݿ�����
    * input          : NA
    * output         : NA
    * return         : IVS_SUCCEED -�Ͽ��ɹ�  IVS_FAIL -�Ͽ�ʧ��
    * remark         : NA   
    *********************************************************************/
    virtual int DisConnect(void) = 0;

    /**********************************************************************
    * name           : IsConnected
    * description    : �Ƿ�������״̬
    * input          : NA
    * output         : NA
    * return         : true -����  false -�Ͽ�
    * remark         : NA   
    *********************************************************************/
    virtual bool IsConnected(void) = 0;

    /**********************************************************************
    * name           : getDbType
    * description    : ��ȡ���ӵ������ݿ�����
    * input          : NA
    * output         : NA
    * return         : int, 0���ؿ�, 1���Ŀ�
    * remark         : NA   
    *********************************************************************/
	virtual int getDbType(void) = 0;

    /**********************************************************************
    * name           : setDbType
    * description    : �������ӵ������ݿ�����
    * input          : dbType, 0���ؿ�, 1���Ŀ�
    * output         : NA
    * return         : void
    * remark         : NA   
    *********************************************************************/
	virtual void setDbType(int dbType) = 0;

    /**********************************************************************
    * name           : getPoolVersion
    * description    : ��ȡ���Ӱ汾��
    * input          : NA
    * output         : NA
    * return         : int
    * remark         : NA   
    *********************************************************************/
	virtual int getPoolVersion(void) = 0;

    /**********************************************************************
    * name           : setPoolVersion
    * description    : �������Ӱ汾��
    * input          : NA
    * output         : NA
    * return         : void
    * remark         : NA   
    *********************************************************************/
	virtual void setPoolVersion(int poolVersion) = 0;

	virtual void Clear() = 0;

    time_t GetCreateTime(){return m_tCreateTime;}

protected:
    time_t m_tCreateTime;
};

#endif
