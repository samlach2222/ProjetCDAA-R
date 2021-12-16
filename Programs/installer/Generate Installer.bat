@ECHO OFF
cd "%~dp0"

::win32 win32 win32 win32 win32 win32 win32 win32
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
echo.

::UWP UWP UWP UWP UWP UWP UWP UWP UWP UWP UWP UWP
::Generate the msix
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\makeappx.exe" pack /o /d "..\..\build-CDAA-R-Qt_5_12_12_for_UWP_32bit_MSVC_2017-Release\release" /p "packages\com.groupe_R.CDAA_R_uwp\data\CDAA-R_UWP.msix"
echo.
::Sign the msix
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\signtool.exe" sign /debug /fd sha256 /f "Groupe R without password.pfx" /t http://timestamp.digicert.com/ "packages\com.groupe_R.CDAA_R_uwp\data\CDAA-R_UWP.msix"
echo.

::APK APK APK APK APK APK APK APK APK APK APK APK
::Copy the latest release build
if %username% == SYSTEM (
	xcopy /y "..\..\build-CDAA-R-Android_Qt_5_12_11_Clang_armeabi_v7a-Release\android-build\build\outputs\apk\debug\CDAA-R v1.0.3.apk" "packages\com.groupe_R.CDAA_R_apk\data\"
) else (
	xcopy /y "..\..\build-CDAA-R-Android_Qt_5_12_12_Clang_armeabi_v7a-Release\android-build\build\outputs\apk\debug\CDAA-R v1.0.3.apk" "packages\com.groupe_R.CDAA_R_apk\data\"
)
echo.

::Installateur Installateur Installateur Installateur
::--ac = compression level, -v = verbose, -f = offline installer
if %username% == SYSTEM ("D:\LOGICIELS\QT\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur 2.1.1.exe") else ("C:\Qt\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur 2.1.1.exe")
echo.
echo L'installateur se trouve dans Programs\installer
TIMEOUT 3
