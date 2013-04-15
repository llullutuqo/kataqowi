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

#include "kdataclass.h"
#include <QMap>
#include <QString>
#include <QMapIterator>
#include <QHash>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>
#include <QDate>

class KDataClass::KDataClassPrivate{
public:
	KDataClassPrivate(KDataClass * parent){
		base = parent;
	}
	bool isPossibleErase(){
		if(m_estado!=Loaded){
			base->sendMessage("Debe cargar antes de eliminar");
			return false;
		}
		return true;
	}
	bool isPossibleSave(){
		bool salida = true;
		QMapIterator<int, QString> i(cantBeNull);
		 while (i.hasNext()) {
			 i.next();
			 QVariant d =valueslist.at(i.key());
			 if(d.isNull()){
				 base->sendMessage(i.value());
				 salida = false;
				 break;
			 }
		 }
		return salida;
	}
	void _addCantBeNullColumn(int id,QString message){
		cantBeNull.insert(id,message);
	}
	void limpiarData(){
		for(int i =0;i<base->m_numeroColumnas;i++)
			valueslist.replace(i,QVariant());
	}
	KDataClass * base;
	DataState m_estado;
	QVariantList valueslist;
	QMap<int,QString> cantBeNull;
};

KDataClass::KDataClass(QObject *parent) :
	QObject(parent),d(new KDataClassPrivate(this))
{
	m_loadDependences=true;
}
KDataClass::~KDataClass()
{
	delete d;
}

const char *KDataClass::table(){
	return "";
}
bool KDataClass::loadFromPrimaryKey(QVariant value){
	return loadFromPrimaryKey(QList<QVariant>()<<value);
}
bool KDataClass::isLoaded(){
	if(d->m_estado==Loaded)
		return true;
	return false;
}
QVariant KDataClass::getVariantValue(int index){
	return d->valueslist.at(index);
}

void KDataClass::setVariantValue(int i, const QVariant &value){
	d->valueslist.replace(i,value);
}

bool KDataClass::loadFromPrimaryKey(QList<QVariant> value){
	QHash<KDataClass::Columns,QStringList> datos = getColumns();
	if(datos[KDataClass::PrimaryKey].count()!=value.count()){
		qDebug()<<"Error : el numero de columnas primarias y las cadenas pasadas como argumento no coinciden.";
		return false;
	}

	return loadFromColumns(datos[KDataClass::PrimaryKey],value);
}
bool KDataClass::loadFromColumns(QStringList columnas,QList<QVariant> value){
	if(value.isEmpty())
		return false;
	QStringList values;
	for(int i =0;i< value.size();i++){
		switch(value.at(i).type()){
		case QVariant::Int:
		case QVariant::UInt:
		case QVariant::Bool:
		case QVariant::Double:
			values<<value.at(i).toString();
			break;
		default:
			values<<value.at(i).toString();
			break;
		}
	}
	return loadFromColumns(columnas,values);
}
bool KDataClass::isAutoincrement(){
	return m_isAutoincrement;
}
void KDataClass::setAutoIncrement(bool value){
	if(value!=m_isAutoincrement){
		m_isAutoincrement= value;
	}
}

bool KDataClass::loadFromColumns(QStringList columnas,QStringList data){
	QString cadena;
	int cn =columnas.count();
	if(cn<1){
		return false;
	}
	cadena = columnas.at(0) + "= \"" + data.at(0) + "\"";
	for(int i =1;i<cn;i++){
		cadena += " and " + columnas.at(i) + "= \"" + data.at(i) + "\"";
	}
	qDebug()<<"Filter:"<<cadena;
	m_model->setFilter(cadena);
	if(!m_model->select()){
		qDebug()<<"Error al cargar: "<<m_model->lastError().text();
		detectState();
		return false;
	}
	if(m_model->rowCount()!=1){
		qDebug()<<"Hay más de un registro: "<<m_model->rowCount();
		detectState();
		return false;
	}
	setClassState(Loaded);
	loadValueList();
	emit classLoaded(description());
	if(m_loadDependences)
		loadDependences();
	else
		setPrimaryKeyToDependences();
	this->emitSignals();
	emit dataLoaded();
	return true;
}

bool KDataClass::isLoadingDependences(){
	return m_loadDependences;
}

void KDataClass::setLoadingDependences(bool value){
	if(value!=m_loadDependences)
		m_loadDependences=true;
}

void KDataClass::loadDependences(){
}
void KDataClass::setPrimaryKeyToDependences(){
}

void KDataClass::beforeSave(){
}
QString KDataClass::getNextCode(){
	if(m_isAutoincrement)
		return "";
	return returnNextCode();
}
QString KDataClass::returnNextCode(){
	return "";
}

bool KDataClass::save(){
	qDebug()<<"GUardado:";
	beforeSave();
	if(!d->isPossibleSave())
		return false;
	for(int i =0;i<m_numeroColumnas;i++){
		m_model->setData(m_model->index(m_row,i),d->valueslist.at(i));
	}
	bool sald= m_model->submitAll();
	if(!sald){
		sendMessage(m_model->lastError().text());
#ifdef QT_DEBUG
		qDebug()<<"----SAVE ERROR";
		qDebug()<<m_model->lastError().text();
		for(int i =0;i<m_numeroColumnas;i++){
			qDebug()<<"value for:"<<i<<m_model->data(m_model->index(m_row,i));
		}
		qDebug()<<"--------------";
#endif
	}
	afterSave();
	return sald;
}

void KDataClass::afterSave(){
}

void KDataClass::beforeErase(){
}
bool KDataClass::erase(){
	qDebug()<<"Borrado:";
	if(!d->isPossibleErase())
		return false;
	beforeErase();
	m_model->removeRows(m_row,1);
	bool sald= m_model->submitAll();
	if(!sald){
		sendMessage(m_model->lastError().text());
		qDebug()<<m_model->lastError().text();
	}
	else{
		setAsNew();
		clear();
	}
	return sald;
}
void  KDataClass::setClassState(DataState value){
	if(d->m_estado!=value){
		d->m_estado = value;
		detectState();
		if(value==New)
			d->limpiarData();
		emit classStateChanged(value);
	}
}
KDataClass::DataState KDataClass::classState(){
	return d->m_estado;
}
void KDataClass::detectState(){
	m_model->revertAll();
	switch(d->m_estado){
	case Null:
	case Loaded:
		break;
	case New:
		m_model->insertRows(m_row,1);
		break;
	}
}
void KDataClass::clear(){
		detectState();
	if(this->classState()==New){
		d->limpiarData();
		setPredValue();
	}
	else if(this->classState()==Loaded){
		loadValueList();
	}
	this->emitSignals();
}

void KDataClass::loadClass(){
	m_row=0;
	m_model= new QSqlTableModel(this);
	m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_model->setTable(tableName());
	if(m_model->lastError().isValid())
		qDebug()<<"Error:"<< m_model->lastError().text();
	for(int i =0;i<m_numeroColumnas;i++)
		d->valueslist.append(QVariant());
	setClassState(New);
}
void KDataClass::loadValueList(){
	for(int i =0;i<m_numeroColumnas;i++)
		d->valueslist.replace(i,m_model->data(m_model->index(m_row,i)));
}

void KDataClass::setPredValue(){}
void KDataClass::setAsNew(){
	this->setClassState(New);
	emit classLoaded(description());
}
void KDataClass::sendMessage(QString Message){
	QMessageBox::warning(NULL,tableName(),Message);
}
void KDataClass::addCantBeNullColumn(int id,QString message){
	d->_addCantBeNullColumn(id,message);
}
