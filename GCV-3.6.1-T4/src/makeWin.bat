rem May 30, 2014
rem LETARTARE

rem  3.6.1-Tx

rem for release

qmake -config release -spec win32-g++ GCV.pro
mingw32-make -fmakefile.release

rem for debug

rem qmake -config debug -spec win32-g++ GCV.pro
rem mingw32-make -fmakefile.debug

cd ..
