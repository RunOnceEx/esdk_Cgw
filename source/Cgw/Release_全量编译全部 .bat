@echo off
echo ���������� ��ʼ����CGW ��������������������������������
@"%VS100COMNTOOLS%\..\IDE\devenv.com" CgwMonitorManageService\CgwMonitorManage.sln /Rebuild "Release"
@"%VS100COMNTOOLS%\..\IDE\devenv.com" Cgw\Cgw.sln /Rebuild "Release"
echo.
echo ���������� ���� CGW Release�汾�ɹ� ��������������������

echo ���������� ��ʼ���CGW ��������������������������������

::��õ�ǰʱ�䣬��Ϊ���ɰ汾��Ŀ¼��
for /F "tokens=1-4 delims=-/ " %%i in ('date /t') do (
   set Year=%%i
   set Month=%%j
   set Day=%%k
   set DayOfWeek=%%l
)
for /F "tokens=1-2 delims=: " %%i in ('time /t') do (
   set Hour=%%i
   set Minute=%%j
)

set   	DateTime=%Year%-%Month%-%Day%-%Hour%-%Minute%
set	WinRarRoot=C:\Program Files\WinRAR

@echo on
echo %DateTime%
@echo .

mkdir tempversion
xcopy /y /i /r /s "Cgw\Build\x86\Release\*"     "tempversion\"        
cd tempversion
del /s /q  *.pdb
del /s /q  *.log
del /s /q  *.lib
del /s /q  *.vshost

::ɾ����Ŀ¼���ļ���
rd /s /q conf
rd /s /q config
rd /s /q defaultConfig
rd /s /q data
rd /s /q logs
rd /s /q res
rd /s /q skin
rd /s /q include
rd /s /q i18n
rd /s /q include
rd /s /q lib

::ɾ��MonitorManageServiceĿ¼���ļ���
rd /s /q MonitorManageService\conf
rd /s /q MonitorManageService\data
rd /s /q MonitorManageService\logs
rd /s /q MonitorManageService\res
rd /s /q MonitorManageService\skin
rd /s /q MonitorManageService\lib\mediastreamer
rd /s /q MonitorManageService\lib\gtk-2.0
rd /s /q MonitorManageService\include
rd /s /q MonitorManageService\i18n
rd /s /q MonitorManageService\include
rd /s /q MonitorManageService\SipStack\logs
rd /s /q MonitorManageService\SipStack\log

rd /s /q MonitorManageService\eLTeSDK\data
rd /s /q MonitorManageService\eLTeSDK\logs
rd /s /q MonitorManageService\eLTeSDK\res
rd /s /q MonitorManageService\eLTeSDK\lib
rd /s /q MonitorManageService\eLTeSDK\include


::ɾ�����ΰҵDLL
rd /s /q MonitorManageService\TiandySdk\dll
::ɾ��LTE DLL
::rd /s /q MonitorManageService\eLTeSDK

"%WinRarRoot%\WinRAR.exe" a -r eSDK_TP_CGW_V1.5.00_%DateTime%.zip .\
move eSDK_TP_CGW_V1.5.00_%DateTime%.zip ..\
cd ..
rd /Q /S tempversion

pause