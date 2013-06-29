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

#include "kdatabase.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QObject>
#include <QFile>
KDataBase::KDataBase()
{
}
QString KDataBase::conectar(QString fichero, QString qtDriver){
	return conectar("",fichero,"","",qtDriver);
}
QString KDataBase::conectar(QString servidor, QString baseDatos,QString usuario, QString contrasenia, QString qtDriver){
	if(!QSqlDatabase::isDriverAvailable(qtDriver)){
		//emit onMessage();
		return QObject::trUtf8("El driver %1 no está disponible.").arg(qtDriver);
	}
	bool isFileADataBase = usuario.isEmpty();
	QSqlDatabase basedatos = QSqlDatabase::addDatabase(qtDriver);
	if(!isFileADataBase){
		basedatos.setUserName(usuario);
		basedatos.setPassword(contrasenia);
		basedatos.setHostName(servidor);
	}
	else{
		if(!QFile::exists(baseDatos))
			return QObject::trUtf8("La base de datos no existe.");
	}
	/*if(port!=0)
		basedatos.setPort(port);
	if(!isFileADataBase() && generarBaseDatos){
		if (!basedatos.open()){
			emit onMessage(basedatos.lastError().databaseText());
			return;
		}
		if(!this->ejecutarQuery(this->generarBaseDatos(baseDatos)))
			return;
		basedatos.close();
	}*/
	basedatos.setDatabaseName(baseDatos);
	if (!basedatos.open()){
		return QObject::trUtf8("Error al intentar conectar: ")+basedatos.lastError().databaseText();
	}
	qDebug()<<"Transacciones:"<<suportTransaction();
	return "";
}
QString KDataBase::reconectar(QString fichero, QString qtDriver){
	return conectar(fichero,qtDriver);
}
QString KDataBase::desconectar(){
	QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
	return "";
}
QStringList KDataBase::suportedSQLDrivers(){
	return QSqlDatabase::drivers();
}

bool KDataBase::suportTransaction(){
	return QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions);
}
