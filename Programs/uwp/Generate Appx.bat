@ECHO OFF
cd "%~dp0"
if NOT %username% == SYSTEM (chcp 65001)
echo Création de l'installateur .msix
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\makeappx.exe" pack /o /d "..\..\build-CDAA-R-Qt_5_12_12_for_UWP_32bit_MSVC_2017-Release\release" /p CDAA-R_UWP.msix
echo.
echo Signe le .msix
"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\signtool.exe" sign /debug /fd sha256 /f "Groupe R.pfx" /p raclette /t http://timestamp.digicert.com/ CDAA-R_UWP.msix
echo.
echo L'installateur CDAA-R_UWP.msix se trouve dans Programs
TIMEOUT 3
