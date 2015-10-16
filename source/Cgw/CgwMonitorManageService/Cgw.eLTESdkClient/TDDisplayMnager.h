//===================================================================
//	Copyright(C)2013-2020, Huawei Tech. Co., Ltd.
//
//	�ļ���	��TDDisplayMnager.h
//	��  ��	��w00206574
//	������ڣ�2014-04-08
//	˵  ��	��ʵ��eLTE�ӿ�C++ ��C#֮��ת��
//	��  ��	��
//	��ʷ��¼��
//===================================================================

#include <list>
#include <string>
#include "notifyStruct_t.h"

using namespace std;

class TDDisplayMnager
{
private:
	TDDisplayMnager(void);
public:
	~TDDisplayMnager(void);

	//��ȡTDDisplayMnager��̬ʵ��
	static TDDisplayMnager& Instance();

	//֪ͨ�����״̬�����Ϣ
	void notifyGroupStatus(const string& strEventBuf) const;

	//֪ͨ�û���Ⱥ����Դ��״̬�����Ϣ
	void notifyResourceStatus(const string& strEventBuf);

	//֪ͨ��Ե���е�״̬�����Ϣ
	void notifyP2pcallStatus(const string& strEventBuf) const;

	//֪ͨ��Ƶ���е�״̬�����Ϣ��������Ƶ�ش�������ҪYCʵ��
	void notifyP2pvideocallStatus(const string& strEventBuf) const;

	void notifyUserStatus(const string& strEventBuf) const;

	void notifyUserSdsStatus(const string& strEventBuf) const;
	void notifyModuleStatus(const string& strEventBuf) const;

	//��������Ϣ�ϱ���GUI
	void notifySMS(const string& strEventBuf) const;

	//֪ͨ���ö���ı����Ϣ�� ����Ϊһ����ָ̬�룬 ʹ������Ҫdowncast Ϊ��Ӧ�ı������
	void notifyProvisionChange(const string& strEventBuf) const {;};

	//֪ͨ���ö����ȫͬ���� ����Ϊһ����ָ̬�룬 ʹ������Ҫdowncast Ϊ��Ӧ�ı������
	void notifyProvisionAllResync();

	//֪ͨ״̬�����ȫͬ���� ����Ϊһ����ָ̬�룬 ʹ������Ҫdowncast Ϊ��Ӧ�ı������
	void notifyStatusAllResync(const string& strEventBuf) const;

	//��ȡ��¼�¼�����
	void* GetLoginEventHandle() {return m_EventLogin;};

	//���õ�ǰ��¼���û�id
	void SetResID(const std::string& strResID){m_strResID = strResID;};

protected:

private:
	void*       m_EventLogin;
	std::string  m_strResID;
};

#ifdef ESDK_EXPORTS
#define ESDK_API __declspec(dllexport)
#else
#define ESDK_API __declspec(dllimport)
#endif

#ifdef WIN32
#define _SDK_CALL __stdcall
#else
#define _SDK_CALL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

 ESDK_API void _SDK_CALL SetGrpStaCallBack(notifyGroupStatus_t notiGrpSta);

 ESDK_API void _SDK_CALL SetResStaCallBack(notifyResourceStatus_t notiResSta);

 ESDK_API void _SDK_CALL SetP2pStaCallBack(notifyP2pcallStatus_t notiP2pSta);

 ESDK_API void _SDK_CALL SetUserStaCallBack(notifyUserStatus_t notiUserSta);

 //ESDK_API void _SDK_CALL SetSMSCallBack2(notifySMS2_t notiSMS);

 ESDK_API void _SDK_CALL SetModStaCallBack(notifyModuleStatus_t notifyModSta);

 ESDK_API void _SDK_CALL SetP2pVideoCallStaCallBack(notifyP2pvideocallStatus_t notifyP2pvideocallSta);

 ESDK_API void _SDK_CALL SetProvisionAllResyncCallBack(notifyProvisionAllResync_t notifyProSta);
#ifdef __cplusplus
}
#endif 


