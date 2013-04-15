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

#include "kaccess.h"
#include <QAction>
#include <QMenu>

class KAccess::KAccessPrivate{
public:
	KAccessPrivate(){

	}
	void addAction(QString key,QAction *action){
		QList<QAction *> mn;
		if(actionList.contains(key)){
			mn=actionList.value(key);
		}
		action->setVisible(false);
		mn.append(action);
		actionList.insert(key,mn);
	}
	void addWidget(QString key,QMenu *widget){
		QList<QMenu *> wg;
		if(widgetList.contains(key)){
			wg = widgetList.value(key);
		}
		widget->menuAction()->setVisible(false);
		wg.append(widget);
		widgetList.insert(key,wg);
	}
	void deactivateMenus(){
		QHashIterator<QString ,QList<QMenu *>  > i(widgetList);
		while (i.hasNext()) {
			i.next();
			foreach(QMenu *wg,i.value()){
				wg->menuAction()->setEnabled(false);
			}
		}
	}
	void deactivateActions(){
		QHashIterator<QString ,QList<QAction *>  > i(actionList);
		while (i.hasNext()) {
			i.next();
			foreach(QAction *wg,i.value()){
				wg->setEnabled(false);
			}
		}
	}
	QHash<QString ,QList<QAction *> > actionList;
	QHash<QString ,QList<QMenu *> > widgetList;
};

KAccess::KAccess(QObject *parent):QObject(parent),d(new KAccessPrivate)
{
}
KAccess::~KAccess(){
	delete d;
}
void KAccess::addItem(QString key,QAction *action){
	d->addAction(key,action);
}

void KAccess::addItem(QString key, QMenu *menu){
	d->addWidget(key,menu);
}
void KAccess::activateControls(QString permission){
	if(d->actionList.contains(permission)){
		d->deactivateActions();
		foreach(QAction *action,d->actionList.value(permission)){
			action->setVisible(true);
		}
	}
	if(d->widgetList.contains(permission)){
		d->deactivateMenus();
		foreach(QMenu * widget,d->widgetList.value(permission)){
			widget->menuAction()->setVisible(false);
		}
	}
}

void KAccess::deactivateControls(){
	d->deactivateActions();
	d->deactivateMenus();
}
