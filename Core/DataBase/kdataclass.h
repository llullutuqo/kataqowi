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

#ifndef KDATACLASS_H
#define KDATACLASS_H

#include <QObject>
#include <QStringList>
#include <QVariant>
#include <QDate>
#include "core_global.h"

class QSqlTableModel;
/**
* @brief EXample
*pa joder eres bueno
* @class DataClass dataclass.h "dataclass.h"
*/
class CORESHARED_EXPORT KDataClass : public QObject
{
Q_OBJECT
public:
	enum Columns{PrimaryKey=0,Normal=1};
	enum DataState{Null=0,New=1,Loaded=2};
	explicit KDataClass(QObject *parent = 0);
	~KDataClass();

	bool isLoadingDependences();
	void setLoadingDependences(bool value);

	//EStablece los data values en blanco
	virtual void clear();
	virtual DataState classState();

	void detectState();
	bool save();
	bool erase();
	//TODO: reeplantear la función en caso de que consumiera mucha memoria.
	static const QHash<KDataClass::Columns,QStringList> columns();
	virtual const QHash<KDataClass::Columns,QStringList> getColumns()=0;
	static const char * table();
	virtual const char * tableName()=0;
	void setAsNew();
	QString getNextCode();
	virtual QString returnNextCode();
	virtual QString description()=0;
	bool isAutoincrement();
	bool isLoaded();
	QVariant getVariantValue(int indice);
	bool loadFromColumns(QStringList columnas,QStringList data);
	bool loadFromColumns(QStringList columnas,QList<QVariant> data);
public slots:
	bool loadFromPrimaryKey(QList<QVariant> value);
	bool loadFromPrimaryKey(QVariant value);
signals:
	void classStateChanged(DataState value);
	//TODO: cambiar el nombre a esta señal
	//Debido a que classLoaded se usa como para new así como modificados
	void classLoaded(QString description);
	void dataLoaded();
protected:
	void setAutoIncrement(bool value);
	virtual void beforeErase();
	virtual void beforeSave();
	virtual void afterSave();
	virtual void loadDependences();
	virtual void setPrimaryKeyToDependences();
	//ESTABLECE valores predeterminados para la clase
	virtual void emitSignals()=0;	
	virtual void setPredValue();
	//virtual const char * tabla()
	QSqlTableModel *m_model;
	bool m_loadDependences;
	int m_row;
	virtual void  setClassState(DataState value);
	void loadClass();
	void loadValueList();
	int m_numeroColumnas;
	bool m_isAutoincrement;
	void sendMessage(QString Message);
	void setVariantValue(int i, const QVariant &value);
	void addCantBeNullColumn(int id,QString message);
private:
	class KDataClassPrivate;
	KDataClassPrivate *d;
};

#endif // DATACLASS_H
