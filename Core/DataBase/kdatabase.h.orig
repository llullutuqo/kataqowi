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

#ifndef KDATABASE_H
#define KDATABASE_H
#include <QString>
#include "core_global.h"

class  CORESHARED_EXPORT KDataBase
{
public:
	KDataBase();
	static QString conectar(QString servidor,QString baseDatos, QString usuario,QString contrasenia,QString qtDriver);
	static QString conectar(QString fichero,QString qtDriver);
	static QString reconectar(QString fichero, QString qtDriver);
	static QString desconectar();
	static bool suportTransaction();
	static QStringList suportedSQLDrivers();
};

#endif // KDATABASE_H
