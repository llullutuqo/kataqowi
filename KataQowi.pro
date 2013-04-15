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

TEMPLATE = subdirs
SRC_SUBDIRS += src_core
SRC_SUBDIRS += src_gui
SRC_SUBDIRS += src_print
src_core.subdir = Core
src_core.target = sub-core
src_gui.subdir = GUI
src_gui.target = sub-gui
src_print.subdir = Print
src_print.target = sub-print
SUBDIRS += $$SRC_SUBDIRS
