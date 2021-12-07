@ECHO OFF
cd "%~dp0"
::Copy the latest release build
if %username% == SYSTEM (
	xcopy /y "..\..\build-CDAA-R-Desktop_Qt_5_12_11_MinGW_64_bit-Release\release\CDAA-R.exe" "packages\com.groupe_R.CDAA_R_win32\data\"
) else (
	chcp 65001
	xcopy /y "..\..\build-CDAA-R-Desktop_Qt_5_12_12_MinGW_64_bit-Release\release\CDAA-R.exe" "packages\com.groupe_R.CDAA_R_win32\data\"
)
echo.
::Check if the .exe file exists, ask to deploy it
if NOT exist packages\com.groupe_R.CDAA_R_win32\data\Qt5Core.dll (
	echo Déployez CDAA-R avec la commande "<RépertoireDeQt>\<VersionDeQt>\mingw73_64\bin\windeployqt.exe packages\com.groupe_R.CDAA_R_win32\data\CDAA-R.exe" ^(oublie certains dll^)
	echo puis utilisez un outil tel que https://github.com/lucasg/Dependencies pour connaitre les dépendances
	echo Les dll à ajouter se trouve dans "<RépertoireDeQt>\<VersionDeQt>\mingw73_64\bin" et doivent être placer au même endroit que CDAA-R.exe
	pause
	exit /b 1
)
::--ac = compression level, -v = verbose, -f = offline installer
if %username% == SYSTEM ("D:\LOGICIELS\QT\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur 1.1.0.exe") else ("C:\Qt\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur 1.1.0.exe")
echo.
echo L'installateur "CDAA-R installateur.exe" se trouve dans Programs\installer
TIMEOUT 3
