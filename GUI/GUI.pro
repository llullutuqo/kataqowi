###############################################################################
## This file is part of Kata Qowi
##
## Copyright (C) 2010 - 2013 Jean Pierre Ruedi Mazuelos Saavedra(LlulluTuqo)
##
## All rights reserved.
## Contact: (mail@jeanmazuelos.com)
## Personal Web Site: http://jeanmazuelos.com
##
## GNU Lesser General Public License Usage
##
## This file may be used under the terms of the GNU Lesser General Public
## License version 2.1 as published by the Free Software Foundation and
## appearing in the file LICENSE.LGPL included in the packaging of this file.
## Please review the following information to ensure the GNU Lesser General
## Public License version 2.1 requirements will be met:
## http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
###############################################################################
# -------------------------------------------------
# Project created by QtCreator 2010-06-07T15:38:36
# -------------------------------------------------
QT += gui \
    xml \
    xmlpatterns \
    sql
CONFIG += help
TARGET = KqGui
TEMPLATE = lib
DEFINES += GUI_LIBRARY
HEADERS += \
    gui_global.h \
    Central/kbasepanel.h \
    Central/kdatapanel.h \
    Central/khelperbrowser.h \
    Central/khelpviewer.h \
    Central/kmainwindow.h \
    Controls/kcombomodel.h \
    Controls/ksearchdata.h \
    utils/kaccess.h \
    Widgets/kconectionbox.h \
    Widgets/kdatabuttons.h \
    Widgets/kdatapaneldialog.h \
    kapplicationgui.h \
    Controls/kselectfile.h
SOURCES += \
    Central/kbasepanel.cpp \
    Central/kdatapanel.cpp \
    Central/khelperbrowser.cpp \
    Central/khelpviewer.cpp \
    Central/kmainwindow.cpp \
    Controls/kcombomodel.cpp \
    Controls/ksearchdata.cpp \
    utils/kaccess.cpp \
    Widgets/kconectionbox.cpp \
    Widgets/kdatabuttons.cpp \
    Widgets/kdatapaneldialog.cpp \
    kapplicationgui.cpp \
    Controls/kselectfile.cpp
FORMS += \
    Controls/ksearchdata.ui \
    Widgets/kconectionbox.ui \
    Controls/kselectfile.ui
unix:DESTDIR = ../bin/
win32:LIBS +=-L../lib/
unix:LIBS += -L../bin/
build_pass:CONFIG(debug, debug|release):LIBS += -lKqCored
else:LIBS += -lKqCore
INCLUDEPATH += "../Core/"
include ('../baseconfig.pri')

# INSTALACIÓN DE CABECERAS
include.path = "../include/GUI"
include.files = $$HEADERS
win32:INCLUDEPATH += ./
INSTALLS += include

RESOURCES += \
    icons.qrc
