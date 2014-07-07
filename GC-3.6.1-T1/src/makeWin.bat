rem May 30, 2014
rem LETARTARE

rem  3.6.1-Tx

rem for release

qmake -config release -spec win32-g++ GcodeSenderGUIthreads.pro
mingw32-make -fmakefile.release
rem release\GrblController.exe

rem for debug

rem qmake -config debug -spec win32-g++ GcodeSenderGUIthreads.pro
rem mingw32-make -fmakefile.debug
rem debug\GrblController.exe

cd ..
