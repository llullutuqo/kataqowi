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
# Project created by QtCreator 2010-08-16T09:00:51
# -------------------------------------------------
QT += gui \
	sql
TARGET = KqPrint
TEMPLATE = lib
DEFINES += PRINT_LIBRARY
SOURCES += \
    kdocument.cpp
HEADERS += print_global.h \
    kdocument.h
include ('../baseconfig.pri')
# INSTALACIÓN DE CABECERAS
include.path = "../include/Print"
include.files = $$HEADERS
INSTALLS += include
