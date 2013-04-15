@echo off
echo Setting up environment for Qt usage...
set QTDIR=C:\QtSDK\Desktop\Qt\4.7.3\mingw
set PATH=C:\QtSDK\mingw\bin;%PATH%
set PATH=%QTDIR%\bin;%PATH%
set PATH=%PATH%;%SystemRoot%\System32
set PATH=%PATH%;C:\Qt\KataQowi\bin
set QMAKESPEC=win32-g++
cd ..
echo "Limpiando entorno:"
rmdir  /S /Q include
rmdir  /S /Q bin
rmdir  /S /Q lib
rmdir  /S /Q Core\trash
rmdir  /S /Q Gui\trash
rmdir  /S /Q Print\trash
qmake.exe KataQowi.pro -r -spec win32-g++
mingw32-make.exe -w
mingw32-make.exe install -w
echo "Eliminando rastros de travesura :)"

del Makefile.Release Makefile.Debug object_script.sistem.Release object_script.sistem.Debug Makefile
echo "Creando instalador :"
cd instaladores
"C:\Archivos de programa\Inno Setup 5\iscc.exe" windows.iss

pause