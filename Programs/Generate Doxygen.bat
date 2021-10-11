@ECHO OFF
cd "%~dp0"
"C:\Program Files\doxygen\bin\doxygen" Doxyfile
echo.
python doxygen2qtcreator_modified.py ..\Doxygen\html
echo.
if %username% == samlach22 ("D:\LOGICIELS\QT\5.12.11\mingw73_64\bin\qhelpgenerator.exe" ..\Doxygen\html\index.qhp -o ..\Doxygen\CDAA-R.qch) else ("C:\Qt\5.12.11\mingw73_64\bin\qhelpgenerator.exe" ..\Doxygen\html\index.qhp -o ..\Doxygen\CDAA-R.qch ; chcp 65001)
echo.
echo.
echo Nécessaire qu'une seule fois : Ajoutez la documentation CDAA-R.qch (se trouvant dans le dossier Doxygen) dans Qt Creator depuis Outils-^>Options...-^>Aide-^>Documentation
echo Déplacer le curseur de la souris sur une fonction affiche un tooltip, la documentation complète s'affiche avec F1
TIMEOUT 8
