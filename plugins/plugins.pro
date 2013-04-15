CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(apusistemplugin)
TEMPLATE    = lib

HEADERS     = \
    kcombomodelplugin.h \
    kdatabuttonsplugin.h \
    kdatapanelplugin.h \
    ksearchdataplugin.h \
    kataqowi.h
SOURCES     = \
    kcombomodelplugin.cpp \
    kdatabuttonsplugin.cpp \
    kdatapanelplugin.cpp \
    ksearchdataplugin.cpp \
    kataqowi.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

DESTDIR = plugins
INCLUDEPATH +=..\\include\\GUI
LIBS +=	-L ../lib
build_pass:CONFIG(debug, debug|release) {
	LIBS += -lKqGuid
}
else{
	LIBS += -lKqGui
}
build_pass:CONFIG(debug, debug|release) {
	TARGET = $$join(TARGET,,,d)
}
