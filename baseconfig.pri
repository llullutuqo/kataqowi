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

CONFIG += debug_and_release build_all
unix:DESTDIR = ../bin/
win32{
DESTDIR = ../lib/
DLLDESTDIR = ../bin/
}
debug{
	OBJECTS_DIR = trash/obj/debug
	MOC_DIR = trash/moc/debug
	UI_DIR = trash/ui/debug
}
else{
	OBJECTS_DIR = trash/obj/release
	MOC_DIR = trash/moc/release
	UI_DIR = trash/ui/release
}
build_pass:CONFIG(debug, debug|release) {
	TARGET = $$join(TARGET,,,d)
}
