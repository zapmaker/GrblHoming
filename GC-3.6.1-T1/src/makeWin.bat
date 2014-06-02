rem May 30, 2014
rem LETARTARE

rem  3.6.1-Tx

set QMAKESPEC= %PATH_QT%\mkspecs\win32-g++
set PATH=%PATH%; %PATH_QT%\bin;%PATH_MINW32%\bin

rem for release

qmake -config release -spec win32-g++ GcodeSenderGUIthreads.pro
mingw32-make -fmakefile.release
rem release\GrblController.exe

rem for debug

rem qmake -config debug -spec win32-g++ GcodeSenderGUIthreads.pro
rem mingw32-make -fmakefile.debug
rem debug\GrblController.exe

cd ..
