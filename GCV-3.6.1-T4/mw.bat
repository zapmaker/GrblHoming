rem mw.bat
rem by LETARTARE

rem Change with your paths

rem QT5
rem set PATH_QT=o:\DevCpp\Qt-5.3\5.2.0\mingw48_32\
rem set PATH_MINGW32=o:\DevCpp\Qt-5.3\Tools\mingw48_32\ 

rem Qt4 
set PATH_QT=u:\DONNEES\SVN_COMPILE\qt\4.7.3\
set PATH_MINGW32o:\DevCpp\MinGw32-TDM\

echo off

PATH = %PATH_QT%bin;%PATH_MINGW32%bin;%PATH%;

set path

cd src

makeWin.bat


