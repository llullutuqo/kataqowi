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

#include "ksearchdata.h"
#include "ui_ksearchdata.h"
#include <QDebug>
#include <QMap>
#include <QSqlError>
#include <QSqlQueryModel>
class KSearchData::KSearchDataPrivate{
public:
	KSearchDataPrivate(KSearchData *parent){
		m_table= new QSqlQueryModel(parent);
		limit= " LIMIT 10";
	}
	void setSQL(QString sqla){
		if(sqla.toLower().contains("where"))
			sep = " and ";
		else
			sep = " where ";
		sql = sqla;
	}
	const QString getSQL(){
		return sql;// + limit;
	}
	QString getSQLFilter(QString filter){
		return sql  + sep + filter;//+ limit;
	}
	QMap<QString, QString> filters;
	QString Filter;
	QSqlQueryModel *m_table;
	QString m_filter;
	QString limit;
	QString table;
	int m_filterCounts;
private:
		QString sql;
		QString sep;
};

KSearchData::KSearchData(QWidget *parent,Qt::WindowType tipe) :
	QWidget(parent),
	d(new KSearchDataPrivate(this)),
	ui(new Ui::KSearchData)
{
	ui->setupUi(this);
	ui->comboBox->setAutoCompletion(true);
	//ui->comboBox->addItem(tr("All"));
	setShowAllFilter(true);
	ui->toolButton->setVisible(false);
	connect(this->ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(_doubleClicked(QModelIndex)));
	connect(ui->leFilter,SIGNAL(textEdited(QString)),this,SLOT(lEditTextChanged(QString)));
	connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(_clicked()));
	this->setWindowFlags(tipe);
	#if  QT_VERSION >= 0x040603
	this->ui->tableView->setModel(d->m_table);
	#endif
}

KSearchData::~KSearchData()
{
	delete ui;
	delete d;
}

/** Agrega un filtro al combo box
*/
void KSearchData::addFilter(QString filterName,QString filter){
	d->filters.insert(filterName,filter);
	ui->comboBox->addItem(filterName);
	if(ui->comboBox->findText("All")>0)
		on_comboBox_currentIndexChanged("All");
	//ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
}

void KSearchData::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
void KSearchData::_doubleClicked(QModelIndex index)
{
	if(index.isValid()){
		this->hide();
		emit doubleClick(this->ui->tableView->model()->data(this->ui->tableView->model()->index(index.row(),0)));
	}
}


/** Ejecuta la sentencia SQL establecida.
*/
void KSearchData::select()
{
	d->m_table->setQuery(d->getSQL());
}

/** Proiedad sobreescrita
*/
void KSearchData::show()
{
	QWidget::show();
	select();
	ui->leFilter->setFocus();
}

/** Establece el nombre de una tabla a ser utilizada para poblar el datagrid
  se debe llamar a la funcion select() o show para poblar la tabla
*/
void KSearchData::setTableName(QString value){
	d->setSQL("SELECT * FROM " + value);
	d->table = value;
	//#if QT_VERSION < 0x040603
//TODO REVISAR EN POSTERIORES VERSIONES
#ifdef Q_WS_X11
	ui->tableView->setModel(NULL);
	ui->tableView->setModel(d->m_table);
#endif
}

/** Establece la sentencia SQL utilizada para poblar la tabla
  se debe llamar a la funcion select() o show para poblar la tabla
*/
void KSearchData::setSQL(QString sql){
	d->setSQL(sql);
	//#if QT_VERSION < 0x040603
//TODO REVISAR EN POSTERIORES VERSIONES
#ifdef Q_WS_X11
	ui->tableView->setModel(NULL);
	ui->tableView->setModel(d->m_table);
#endif
}

const QString KSearchData::sql()
{
	return d->getSQL();
}

QString KSearchData::tableName(){
	return d->table;
}

//void KSearchData::setFilter(QString value){
//	setFilter(QStringList()<<value);
//}
//
//void KSearchData::setFilter(QStringList value){
//	if(value.count()<1)
//		return;
//	d->m_filter = value.at(0) + " LIKE '%1'";
//	for(int i =1;i<value.count();i++){
//		d->m_filter += " or " + value.at(i) +" LIKE '%"+QString::number(i+1)+"'";
//	}
//	d->m_filterCounts=value.count();
//	qDebug()<<"setFilter:"+d->m_filter;
//}

void KSearchData::lEditTextChanged(QString value)
{
//	//if(value.length()<3)
//	//	return;
//	QString filter=d->m_filter;
//	qDebug()<<"Filtro previo:"<<d->m_filter;
//	for(int i=0;i < d->m_filterCounts;i++){
//		filter=filter.arg("%" + value + "%");
//	}
//	qDebug()<<"Filtro generado:"<<filter;
//	d->m_table->setFilter(filter);
	if(d->Filter.isNull())
		return;
	qDebug()<<"filtro:"<<d->Filter.arg(value);
	//d->m_table->setFilter(d->Filter.arg(value));
	d->m_table->setQuery(d->getSQLFilter(d->Filter.arg(value)));
	if(d->m_table->lastError().isValid()){
		qDebug()<<d->m_table->lastError().text();
	}
}

void KSearchData::on_comboBox_currentIndexChanged(QString value)
{
	if(value ==tr("All")){
		//POner todos los filtros
		QMapIterator<QString, QString> i(d->filters);
		if(i.hasNext()){
			i.next();
			d->Filter = i.value();
			while (i.hasNext()) {
				i.next();
				d->Filter += " OR " + i.value();
			}
		}
	}
	else{
		d->Filter = d->filters.value(value,"");
	}
	ui->leFilter->setFocus();
}
void KSearchData::setButtonVisible(bool value){
	ui->toolButton->setVisible(value);
}

bool KSearchData::isButtonVisible(){
	return ui->toolButton->isVisible();
}
void KSearchData::_clicked(){
	emit buttonClicked();
}

void KSearchData::setTextFilter(QString string)
{
	ui->leFilter->setText(string);
}

void KSearchData::setShowAllFilter(bool value)
{
	if(!value)
	{
		ui->comboBox->removeItem(ui->comboBox->findText("All"));
	}
	else
		ui->comboBox->addItem("All");
}

QTableView *KSearchData::tableView()
{
	return ui->tableView;
}
