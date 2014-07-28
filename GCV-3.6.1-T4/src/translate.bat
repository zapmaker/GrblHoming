rem translate.bat

echo off

set PATH=%PATH%;u:\DONNEES\SVN_COMPILE\qt\4.7.3\bin

rem create "src\trlocale\*.ts"

lupdate.exe  GCV.pro

rem create *.qm

linguist trlocale\GrblController_fr.ts

lrelease trlocale\GrblController_fr.ts -qm trlocale\GrblController_fr.qm

xcopy /Y trlocale\GrblController_fr.qm bin\trlocale\

xcopy /Y trlocale\GrblController_fr.qm ..\cons\trlocale\

cd ..
