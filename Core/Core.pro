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

QT += xml \
    xmlpatterns \
	sql
TARGET = KqCore
TEMPLATE = lib

# CONFIG += staticlib
DEFINES += CORE_LIBRARY
HEADERS += core_global.h \
    Core/ksingleton.h \
    DataBase/kdatabase.h \
    DataBase/kdataclass.h \
    DataBase/kblobvalue.h
SOURCES += \
    DataBase/kdatabase.cpp \
    DataBase/kdataclass.cpp \
    DataBase/kblobvalue.cpp
include ('../baseconfig.pri')
# INSTALACIÓN DE CABECERAS
include.path = "../include/Core"
include.files = $$HEADERS
INSTALLS += include
win32:INCLUDEPATH += ./
