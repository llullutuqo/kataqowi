/**************************************************************************
**
** This file is part of Kata Qowi
**
** Copyright (C) 2010 - 2013 Jean Pierre Ruedi Mazuelos Saavedra(LlulluTuqo)
**
** All rights reserved.
** Contact: (mail@jeanmazuelos.com)
** Personal Web Site: http://jeanmazuelos.com
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include "kapplicationgui.h"
#ifdef Q_WS_WIN
#include <QStringList>
#include "windows.h"
#endif
KApplicationGui::KApplicationGui(int &argc, char **argv, int i):QApplication(argc,argv,i)
{
#ifdef Q_WS_WIN
	foreach(QString ls ,arguments()){
		if(ls=="--debug")
			LoadLibraryA("backtrace.dll");
	}
#endif
}
