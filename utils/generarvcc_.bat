@echo off
echo "Compiling libs"
mkdir Core
cd Core
qmake.exe ../../Core/Core.pro -t vclib CONFIG+=release
cd ..

mkdir GUI
cd GUI
qmake.exe ../../GUI/GUI.pro -t vclib CONFIG+=release
cd ..

echo "Compiling plugins"
mkdir plugins
cd plugins 

qmake.exe ../../plugins/plugins.pro -t vclib CONFIG+=release
cd C:\Qt\APUSistems\utils
pause