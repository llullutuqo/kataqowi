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

#include "kdatapanel.h"
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QList>

KDataPanel::KDataPanel(QWidget *parent):KBasePanel(parent)
{
	this->setEnabled(false);
	m_mantenerFluidez =true;
	setEnabled(false);
	m_estadoPanel=Nulo;
	m_vsible=true;
}

bool KDataPanel::guardar(){
	if(!m_mantenerFluidez)
		setEstadoPanel(Nulo);
	return true;
}

bool KDataPanel::eliminar(){
	if(!m_mantenerFluidez)
		setEstadoPanel(Nulo);
	return true;
}
void KDataPanel::limpiar(){
	qDebug()<<"Limpiar";
}

bool KDataPanel::buscar(){
	qDebug()<<"Buscar";
	return true;
}

void KDataPanel::cancelar(){
	qDebug()<<"Cancelar";
}

void KDataPanel::cerrar(){
	qDebug()<<"Cerrar";
}

void KDataPanel::nuevo(){
	limpiar();
	this->setEnabled(true);
	qDebug()<<"Nuevo";
}
void KDataPanel::modificar(){
	limpiar();
	buscar();
	this->setEnabled(true);
	qDebug()<<"Modificar";
}
void KDataPanel::anular(){
	limpiar();
	this->setEnabled(false);
	qDebug()<<"Anular";
}
KDataPanel::EstadoPanel
KDataPanel::estadoPanel(){
	return m_estadoPanel;
}

void KDataPanel::setEstadoPanel(EstadoPanel value){
	if(value==m_estadoPanel)
		return;
	switch(value){
	case Nulo:
		this->anular();
		break;
	case Nuevo:
		this->nuevo();
		break;
	case Modificado:
		this->modificar();
		break;
	}
	m_estadoPanel = value;
}
void KDataPanel::addActionsTo(QToolBar * menu){
	menu->addActions(this->actions());
}
void KDataPanel::setVisibleActions(bool value){
	if(m_vsible!=value){
		QList<QAction *> actions = this->actions();
		for(int i =0;i<actions.size();i++)
			actions[i]->setVisible(value);
		m_vsible=value;
	}
}
bool KDataPanel::visibleActions(){
	return m_vsible;
}

//void KDataPanel::showDialog(){
//	qWarning()<<"La función showDialog() debe ser usada sólo con punteros.";
//	KDataPanelDialog  fr;
//	fr.setKDataPanel(this);
//	fr.exec();
//	//delete fr;
//}
