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

#include "kcombomodel.h"
#include "DataBase/kdataclass.h"
#include <QEvent>
#include "ksearchdata.h"
#include <QApplication>
#include <QDesktopWidget>

KComboModel::KComboModel(QWidget *parent) :
	QComboBox(parent)
{
	m_data = NULL;
	m_enabledrop = true;
	m_search = new KSearchData(this,Qt::Popup);
	this->setEditable(true);
	QSizePolicy pol;
	pol.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Fixed,QSizePolicy::ComboBox));
	connect(this->lineEdit(),SIGNAL(textEdited(QString)),this,SLOT(getText(QString)));
	connect(m_search,SIGNAL(buttonClicked()),this,SLOT(_clicked()));
}

KComboModel::~KComboModel()
{
	if(m_data)
		disconnect(m_data);
	disconnect(m_search);
	delete m_search;
	//delete ui;
}
void KComboModel::addFilter(QString filterName,QString filter){
	m_search->addFilter(filterName,filter);
}
void KComboModel::getText(QString sald){
	if(m_enabledrop){
		showPopup(sald);
	}
	emit editTextChanged(sald.toInt());
}

/** Establece el valor adataclass a ser usado por el combo
  estblece el valor de setTableName si es que el valor SQL no ha sido establecido.
*/
void KComboModel::setDataClass(KDataClass *value,bool normal){
	if(m_data!=value){
		if(m_data!=NULL){
			disconnect(m_data);
			disconnect(m_search);
		}
		if(value!=NULL){
			if(m_search->sql().isEmpty())
				m_search->setTableName(value->tableName());
			lineEdit()->setText(value->description());
			connect(m_search,SIGNAL(doubleClick(QVariant)),value,SLOT(loadFromPrimaryKey(QVariant)));
			connect(value,SIGNAL(classLoaded(QString)),lineEdit(),SLOT(setText(QString)));
		}
		m_data=value;
	}
}
void KComboModel::showPopup(){
	showPopup("");
}

void KComboModel::showPopup(QString base){
	if(!m_enabledrop){
		m_search->hide();
		return;
	}
	if(m_search->isVisible()){
		hidePopup();
		return;
	}
	m_search->setTextFilter(base);
	m_search->resize(this->width(),m_search->height());
	QDesktopWidget * a =QApplication::desktop();
	qDebug("%i",a->height());
	/*Si el borde inferior del m_search que dentro del tamanio de la pantalla*/
	if(a->height() > this->mapToGlobal(this->rect().bottomLeft()).y() + m_search->height())
		m_search->move(this->mapToGlobal(this->rect().bottomLeft() ) );
	else
	{
		QPoint a = this->mapToGlobal(this->rect().topLeft());
		m_search->move(QPoint(a.x(),a.y() - m_search->height()) );
	}
	m_search->show();
}
void KComboModel::setMaxLength(int length){
	lineEdit()->setMaxLength(length);
}

void KComboModel::hidePopup(){
	m_search->hide();
}
void KComboModel::setEnableDropDown(bool value){
	m_enabledrop = value;
}

bool KComboModel::isEnableDropDown(){
	return m_enabledrop;
}
void KComboModel::setEditableText(bool value){
	lineEdit()->setEnabled(value);
}
void KComboModel::setText(QString text){
	this->lineEdit()->setText(text);
}
void KComboModel::setText(int number){
	if(number ==0)
		this->lineEdit()->setText("");
	else
		this->lineEdit()->setText(QString::number(number));
}

bool KComboModel::editableText(){
	return lineEdit()->isEnabled();
}
void KComboModel::setSQL(QString sql){
	m_search->setSQL(sql);
}
KSearchData *KComboModel::searchData(){
	return m_search;
}
void KComboModel::_clicked(){
	emit buttonSearchClicked();
}
