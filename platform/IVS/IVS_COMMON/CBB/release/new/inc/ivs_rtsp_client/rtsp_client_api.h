/******************************************************************************
   ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� �� : rtsp_client_api.h
  ��    �� : y00182336
  �������� : RTSP�ͻ���ͨѶ��
  �޸���ʷ :
    1 ���� : 2011-10-12
      ���� : y00182336
      �޸� : ����

 ******************************************************************************/
#ifndef __RTSP_CLIENT_API_H_
#define __RTSP_CLIENT_API_H_

#include "rtsp_client_datatype.h"


#ifdef __cplusplus
extern "C"
{
#endif

#ifndef WIN32
//#define __stdcall
#define __declspec(...)
#endif

namespace RTSP_SDK{

    /***************************************************************************
     �� �� �� : RTSP_CLIENT_Init
     �������� : ͨѶ���ʼ��
     ������� : ��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_Init(const char* Backuppath);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SetLog
     �������� : ͨѶ����־�̳߳�ʼ�����������ó�ʼ������־����ӡ
     ������� : unLevel       ��־�ȼ�����Ҫ��RTSP_LOG_LEVEL_Eö����ȡֵ
                bDebugflag    ��ӡDEBUG��Ϣ��־
                pszPath       ��־�ļ�·��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SetLog(const unsigned int unLevel, const int iDebugflag,
                                                         const char* pszPath);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_GetHandle
     �������� : ��ȡ���Ӿ��
     ������� : bBlocked        ͬ��/�첽��ʽ
     ������� : nHandle         �������Ӿ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport)  int RTSPAPI RTSP_CLIENT_GetHandle(const bool bBlocked,
                                                             long *nHandle);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SetExceptionCallBack
     �������� : �����쳣�ص�����
     ������� : nHandle                     ���Ӿ��
                cbExceptionCallBack         �쳣�ص�����
                pUser                       �û��������ص������з���
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SetExceptionCallBack(long nHandle, fExceptionCallBack cbExceptionCallBack,
                                                                       void* pUser);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SetDataCallBack
     �������� : ����ý�����ص�����
     ������� :  nHandle                     ���Ӿ��
                cbDataCallBack              ý�����ص�����
                pUser                       �û��������ص������з���
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SetDataCallBack(long nHandle, fDataCallBack cbDataCallBack,
                                                                  void* pUser);

    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SetUdpDataCallBack
     �������� : ����ý�����ص�����
     ������� :  nHandle                     ���Ӿ��
                pcbDataCallBack              UDP������setup��Ӧ�����ص���pcbDataCallBackָ���������ص�������ɵ�ָ�����飬ָ������Ĵ��˳���뷢��setup��˳���豣��һ��
                pUser                       �û��������ص������з���
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SetUdpDataCallBack(long nHandle, fDataCallBack* pcbDataCallBack,
                                                                  void* pUser);

    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendDescribeMsg
     �������� : ����RTSP DESCRIBE����
     ������� :  nHandle                    ���Ӿ��
                 pstLocalAddr               ���ص�ַ
                 pstServerAddr              RTSP��������ַ
                 sURL                       Describe��Ϣ��װ�е�URL
                 unTimeout                  Describe��Ϣ��ʱʱ�䣨��λ��S��
                 bTcpFlag                   ý�崫��Э��
                 sSDP                       �ỰSDP��Ϣ
                 bAuthFlag                  �Ƿ��Ȩ��ʶ
                 pstAuthentica              ��Ȩ��Ϣ
                 bNeedBackChannel           �Ƿ���Ҫ��������������SDP,���������Խ��������㲥
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
     ***************************************************************************/
    __declspec(dllexport)  int RTSPAPI RTSP_CLIENT_SendDescribeMsg(long nHandle,
                                                                   const INET_ADDR* pstLocalAddr,const INET_ADDR* pstServerAddr,
                                                                   const char *sURL, unsigned int unTimeout, bool bTcpFlag, char *sSDP,
                                                                   bool bAuthFlag, const AUTHENTICA *pstAuthentica, bool bNeedBackChannel = false);

    ///***************************************************************************
    // �� �� �� : RTSP_CLIENT_SendDescribeMsgWithAuth
    // �������� : ����RTSP DESCRIBE�����������Զ����м�Ȩ��Ŀǰֻ֧��ͬ��ģʽ
    // ������� :  nHandle                    ���Ӿ��
    // pstLocalAddr                �������ӵ�ַ��NULL��ָ��
    // pstServerAddr               RTSP��������ַ
    // sURL                        ��Ϣ��װ�е�URL
    // unTimeout                   ��Ϣ��ʱʱ�䣨��λ��S��
    // bTcpFlag                    ý�崫��ģʽTCP����UDP
    // pstAuthentica               ��֤��Ϣ��ֻ��Ҫ����û�����������Ϣ��Ϊ������֤
    // bNeedBackChannel            �Ƿ���Ҫ��������������SDP,���������Խ��������㲥
    // ������� : sSDP             SDP��Ϣ
    // �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    // ***************************************************************************/
    //__declspec(dllexport)  int RTSPAPI RTSP_CLIENT_SendDescribeMsgWithAuth(long nHandle,
    //                                                                        const INET_ADDR* pstLocalAddr,const INET_ADDR* pstServerAddr,
    //                                                                        const char *sURL, unsigned int unTimeout, bool bTcpFlag,
    //                                                                        char *sSDP, const AUTHENTICA *pstAuthentica, bool bNeedBackChannel=false);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendSetupMsg
     �������� : ����RTSP SETUP����
     ������� : nHandle                    ���Ӿ��
                pstLocalAddr               ���ص�ַ,Ϊ���Զ�ѡ��
                pstServerAddr              RTSP��������ַ
                sURL                       SETUP��Ϣ��װ�е�URL
                unTimeout                  SETUP��Ϣ��ʱʱ��(��λ:��)
                bTcpFlag                   ý�崫��Э��
                pstLocalMediaAddr          ͬ��ģʽ�£�ý�������ؽ��յ�ַ���첽ģʽ��Ϊ��
                unChannelNo                tcpģʽ��ͨ����
                bIsForwording              ý�����Ƿ���ת
     ������� : pstPeerMediaAddr           ͬ��ģʽ�£�ý�������Ͷ˵�ַ���첽ģʽ��Ϊ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport)  int RTSPAPI RTSP_CLIENT_SendSetupMsg(long nHandle,
                                                                const INET_ADDR* pstLocalAddr, const INET_ADDR* pstServerAddr,
                                                                const char *sURL, unsigned int unTimeout, bool bTcpFlag,
                                                                const MEDIA_ADDR* pstLocalMediaAddr, MEDIA_ADDR *pstPeerMediaAddr,
                                                                unsigned int unChannelNo, bool bIsForwording=true);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendPlayMsg
     �������� : ����RTSP PLAY����
     ������� :  nHandle                    ���Ӿ��
                sURL                        PLAY��Ϣ��װ�е�URL
                dScale                      �ط�/���ز�������
                sRange                      �ط�/����ʱ���
                unTimeout                   PLAY��Ϣ��ʱʱ�䣨��λ��S��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SendPlayMsg(long nHandle, const char *sURL,
                                                              double dScale, const MEDIA_RANGE_S* stRange,
                                                              unsigned int unTimeout);

    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendOptionMsg
     �������� : ����RTSP OPTIONS����
     ������� :  nHandle                    ���Ӿ��
                sURL                        OPTIONS��Ϣ��װ�е�URL
                unTimeout                   OPTIONS��Ϣ��ʱʱ�䣨��λ��S��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SendOptionMsg(long nHandle, const char *sURL, unsigned int unTimeout, char *strMsg, int &iLength);

    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendPauseMsg
     �������� : ����RTSP PAUSE����
     ������� :  nHandle                    ���Ӿ��
                sURL                        PAUSE��Ϣ��װ�е�URL
                unTimeout                   PAUSE��Ϣ��ʱʱ�䣨��λ��S��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SendPauseMsg(long nHandle, const char *sURL,
                                                               unsigned int unTimeout);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendTeardownMsg
     �������� : ����RTSP TEARDOWN����
     ������� :  nHandle                     ���Ӿ��
                sURL                        TEARDOWN��Ϣ��װ�е�URL
                unTimeout                   PAUSE��Ϣ��ʱʱ�䣨��λ��S��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SendTeardownMsg(long nHandle, const char *sURL,
                                                                  unsigned int unTimeout);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SendSetParameterMsg
     �������� : ����RTSP SetParamter����
     ������� :  nHandle                    ���Ӿ��
                sURL                        SetParamter��Ϣ��װ�е�URL
                unTimeout                   SetParamter��Ϣ��ʱʱ�䣨��λ��S��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SendSetParameterMsg(long nHandle, const char *sURL,
                                                                      unsigned int unTimeout);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_GetStatus
     �������� : ��ȡ���ӵ�ǰ״̬
     ������� : nHandle                     ���Ӿ��
     ������� : ��
     �� �� ֵ : RTSP_SESSION_STATUS -����״̬
    ***************************************************************************/
    __declspec(dllexport) RTSP_SESSION_STATUS RTSPAPI RTSP_CLIENT_GetStatus(long nHandle);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_SetSessionBusinessType
     �������� : ����sessionҵ��״̬
     ������� : nHandle                     ���Ӿ��
     ������� : ��
     �� �� ֵ :
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_SetSessionBusinessType(long nHandle, RTSP_CLIENT_BUSINESS_TYPE businessType);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_FreeHandle
     �������� : �ͷ����Ӿ��
     ������� : nHandle                     ���Ӿ��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_FreeHandle(long nHandle);


    /***************************************************************************
     �� �� �� : RTSP_CLIENT_FreeHandle
     �������� : �ͷ�ͨѶ��
     ������� : ��
     ������� : ��
     �� �� ֵ : RET_OK-�ɹ�     RET_FAIL-ʧ��
    ***************************************************************************/
    __declspec(dllexport) int RTSPAPI RTSP_CLIENT_Cleanup();

    }

#ifdef __cplusplus
}
#endif

#endif //__RTSP_CLIENT_API_H_


