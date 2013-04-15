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

#include "kdatabuttons.h"
#include <QVBoxLayout>
#include <QPushButton>

class KDataButtons::KDataButtonsPrivate{
public:
	KDataButtonsPrivate(KDataButtons *parent){
		verticalLayout = new QVBoxLayout(parent);
		verticalLayout->setSpacing(0);
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
		tbNew = new QPushButton(parent);
		tbNew->setObjectName(QString::fromUtf8("tbNew"));
		tbNew->setEnabled(false);
		tbNew->setIconSize(QSize(22, 22));
		tbNew->setCheckable(true);
		tbNew->setFlat(true);

		verticalLayout->addWidget(tbNew);

		tbModify = new QPushButton(parent);
		tbModify->setObjectName(QString::fromUtf8("tbModify"));
		tbModify->setEnabled(false);
		tbModify->setIconSize(QSize(22, 22));
		tbModify->setCheckable(true);
		tbModify->setFlat(true);

		verticalLayout->addWidget(tbModify);

		btnSearch = new QPushButton(parent);
		btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
		btnSearch->setEnabled(false);
		btnSearch->setIconSize(QSize(22, 22));
		btnSearch->setFlat(true);

		verticalLayout->addWidget(btnSearch);

		btnClean = new QPushButton(parent);
		btnClean->setObjectName(QString::fromUtf8("btnClean"));
		btnClean->setEnabled(false);
		btnClean->setIconSize(QSize(22, 22));
		btnClean->setFlat(true);

		verticalLayout->addWidget(btnClean);

		btnSave = new QPushButton(parent);
		btnSave->setObjectName(QString::fromUtf8("btnSave"));
		btnSave->setEnabled(false);
		btnSave->setIconSize(QSize(22, 22));
		btnSave->setFlat(true);

		verticalLayout->addWidget(btnSave);

		btnDelete = new QPushButton(parent);
		btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
		btnDelete->setEnabled(false);
		btnDelete->setIconSize(QSize(22, 22));
		btnDelete->setFlat(true);

		verticalLayout->addWidget(btnDelete);
		verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

		verticalLayout->addItem(verticalSpacer);
		tbNew->setIcon(QIcon::fromTheme("document-new",QIcon(":/icons/22x/document-new.png")));
		tbModify->setIcon(QIcon::fromTheme("document-edit",QIcon(":/icons/22x/document-edit.png")));
		btnClean->setIcon(QIcon::fromTheme("edit-clear",QIcon(":/icons/22x/edit-clear.png")));
		btnDelete->setIcon(QIcon::fromTheme("edit-delete",QIcon(":/icons/22x/edit-delete.png")));
		btnSave->setIcon(QIcon::fromTheme("document-save",QIcon(":/icons/22x/document-save.png")));
		btnSearch->setIcon(QIcon::fromTheme("edit-find",QIcon(":/icons/22x/edit-find.png")));
		QObject::connect(btnClean,SIGNAL(clicked()),parent,SLOT(cleanCLick()));
		QObject::connect(btnDelete,SIGNAL(clicked()),parent,SLOT(deleteCLick()));
		QObject::connect(tbModify,SIGNAL(clicked()),parent,SLOT(modifyCLick()));
		QObject::connect(tbNew,SIGNAL(clicked()),parent,SLOT(newClick()));
		QObject::connect(btnSave,SIGNAL(clicked()),parent,SLOT(saveCLick()));
		QObject::connect(btnSearch,SIGNAL(clicked()),parent,SLOT(searchCLick()));
		translateUI();
	}
	void translateUI(){
		tbNew->setToolTip(QObject::trUtf8("Nuevo registro"));
		tbModify->setToolTip(QObject::trUtf8("Modificar registro"));
		btnSearch->setToolTip(QObject::trUtf8("Buscar registro"));
		btnClean->setToolTip(QObject::trUtf8("Limpiar interfaz"));
		btnSave->setToolTip(QObject::trUtf8("Guardar cambios"));
		btnDelete->setToolTip(QObject::trUtf8("Eliminar registro"));
	}

	QSpacerItem *verticalSpacer;
	QVBoxLayout *verticalLayout;
	QPushButton *tbNew;
	QPushButton *tbModify;
	QPushButton *btnSearch;
	QPushButton *btnClean;
	QPushButton *btnSave;
	QPushButton *btnDelete;
};

KDataButtons::KDataButtons(QWidget *parent) :
	QWidget(parent),d(new KDataButtonsPrivate(this))
{
}
void KDataButtons::setButtonsState(int value){
	switch(value){
	case 1:
		d->tbNew->setEnabled(true);
		d->tbModify->setEnabled(true);
		d->tbNew->setChecked(true);
		d->tbModify->setChecked(false);
		d->btnClean->setEnabled(true);
		d->btnSearch->setEnabled(false);
		d->btnDelete->setEnabled(false);
		d->btnSave->setEnabled(true);
		break;
	case 2:
		d->tbNew->setEnabled(true);
		d->tbModify->setEnabled(true);
		d->tbNew->setChecked(false);
		d->tbModify->setChecked(true);
		d->btnClean->setEnabled(true);
		d->btnSearch->setEnabled(true);
		d->btnDelete->setEnabled(true);
		d->btnSave->setEnabled(true);
		break;
	case 0:
		d->tbNew->setEnabled(false);
		d->tbModify->setEnabled(false);
		d->tbNew->setChecked(false);
		d->tbModify->setChecked(false);
		d->btnClean->setEnabled(false);
		d->btnSearch->setEnabled(false);
		d->btnDelete->setEnabled(false);
		d->btnSave->setEnabled(false);
		break;
	}
}
void KDataButtons::newClick(){
	emit newClicked();
}

void KDataButtons::modifyCLick(){
	emit modifyClicked();
}

void KDataButtons::searchCLick(){
	emit searchClicked();
}

void KDataButtons::cleanCLick(){
	emit cleanClicked();
}

void KDataButtons::saveCLick(){
	emit saveClicked();
}

void KDataButtons::deleteCLick(){
	emit deleteClicked();
}
void KDataButtons::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		d->translateUI();
		break;
	default:
		break;
	}
}
