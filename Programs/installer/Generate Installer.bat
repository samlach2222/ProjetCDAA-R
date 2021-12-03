@ECHO OFF
cd "%~dp0"
::-f = offline installer, --ac = compression level, -v = verbose
if %username% == SYSTEM ("D:\LOGICIELS\QT\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages -f --ac 9 -v "CDAA-R installateur.exe") else ("C:\Qt\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages -f --ac 9 -v "CDAA-R installateur.exe")
echo.
echo.
echo L'installateur "CDAA-R installateur.exe" se trouve dans Programs\installer
TIMEOUT 3
