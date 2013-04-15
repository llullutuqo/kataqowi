set /P ub= Ingrese la ubicacion de MySQL :
cd %ub%\lib\o
reimp -d libmysql.lib
dlltool -k -d libmysql.def -l libmysql.a
cd %QTDIR%\src\plugins\sqldrivers\mysql
qmake "INCLUDEPATH+=%ub%\include" "LIBS+=%ub%\lib\libmysql.lib" mysql.pro
mingw32-make
copy %ub%\lib\opt\libmysql.dll %QTDIR%\bin

qmake "CONFIG+=release" "INCLUDEPATH+=c:/mysql/include" "LIBS+=c:/mysql/lib/mysqlclient.lib Advapi32.lib Secur32.lib /NODEFAULTLIB:MSVCRTD /NODEFAULTLIB:LIBCMT" mysql.pro