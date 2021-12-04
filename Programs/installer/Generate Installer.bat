@ECHO OFF
cd "%~dp0"
::Check if the .exe file exists, ask to copy and deploy it
chcp 65001
if NOT exist packages\com.groupe_R.CDAA-R\data\CDAA-R.exe (
	echo Copiez un builded CDAA-R.exe, de préférence une release build, dans le dossier Programs\installer\packages\com.groupe_R.CDAA-R\data
	echo Puis déployez-le avec la commande "<RépertoireDeQt>\<VersionDeQt>\mingw73_64\bin\windeployqt.exe packages\com.groupe_R.CDAA-R\data\CDAA-R.exe" ^(oublie certains dll^)
	echo puis utilisez un outil tel que https://github.com/lucasg/Dependencies pour connaitre les dépendances
	echo Les dll à ajouter se trouve dans "<RépertoireDeQt>\<VersionDeQt>\mingw73_64\bin" et doivent être placer au même endroit que CDAA-R.exe
	pause
	exit /b 1
)
::--ac = compression level, -v = verbose, -f = offline installer
if %username% == SYSTEM ("D:\LOGICIELS\QT\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur.exe") else ("C:\Qt\Tools\QtInstallerFramework\4.2\bin\binarycreator.exe" -c config\config.xml -p packages --ac 9 -v -f "CDAA-R installateur.exe")
echo.
echo L'installateur "CDAA-R installateur.exe" se trouve dans Programs\installer
TIMEOUT 3
