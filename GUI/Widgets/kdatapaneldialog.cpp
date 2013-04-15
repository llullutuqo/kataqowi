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

#include "kdatapaneldialog.h"
#include "Central/kdatapanel.h"
#include "Widgets/kdatabuttons.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QDialogButtonBox>

class KDataPanelDialog::KDataPanelDialogPrivate{
public:
	KDataPanelDialogPrivate(KDataPanelDialog *parent){
		data=NULL;
		parent->setMinimumWidth(450);
		verticalLayout = new QVBoxLayout(parent);
		verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
		horizontalLayout = new QHBoxLayout();
		horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
//		groupBox = new QGroupBox(parent);
//		groupBox->setObjectName(QString::fromUtf8("groupBox"));
//		groupBox->setMaximumSize(QSize(55, 16777215));
//		verticalLayout_2 = new QVBoxLayout(groupBox);
//		verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

//		horizontalLayout->addWidget(groupBox);


		verticalLayout->addLayout(horizontalLayout);

		buttonBox = new QDialogButtonBox(parent);
		buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
		buttonBox->setStandardButtons(QDialogButtonBox::Close);

		verticalLayout->addWidget(buttonBox);
		buttons = new KDataButtons(parent);
		horizontalLayout->addWidget(buttons);
//		verticalLayout_2->addWidget(buttons);

		QObject::connect(buttonBox, SIGNAL(rejected()), parent, SLOT(reject()));
		QObject::connect(buttons,SIGNAL(cleanClicked()),parent,SLOT(clean()));
		QObject::connect(buttons,SIGNAL(deleteClicked()),parent,SLOT(deleteObject()));
		QObject::connect(buttons,SIGNAL(modifyClicked()),parent,SLOT(modify()));
		QObject::connect(buttons,SIGNAL(newClicked()),parent,SLOT(newObject()));
		QObject::connect(buttons,SIGNAL(saveClicked()),parent,SLOT(save()));
		QObject::connect(buttons,SIGNAL(searchClicked()),parent,SLOT(search()));
	}
	KDataPanel *data;
	KDataButtons *buttons;
	QVBoxLayout *verticalLayout;
	QHBoxLayout *horizontalLayout;
//	QGroupBox *groupBox;
//	QVBoxLayout *verticalLayout_2;
	QDialogButtonBox *buttonBox;
};

KDataPanelDialog::KDataPanelDialog(QWidget *parent) :
	QDialog(parent),
	d(new KDataPanelDialogPrivate(this))
{
//	ui->setupUi(this);
}

KDataPanelDialog::~KDataPanelDialog()
{
	delete d;
}

void KDataPanelDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
//	switch (e->type()) {
//	case QEvent::LanguageChange:
//		//ui->retranslateUi(this);
//		break;
//	default:
//		break;
//	}
}
void KDataPanelDialog::setDataPanel(KDataPanel * panel){
	setWindowTitle(panel->windowTitle());
	//ui->horizontalLayout->addWidget(panel);
	if(d->data){
		d->horizontalLayout->removeWidget(d->data);
		d->data->setVisible(false);
//		delete d->data;
	}
	d->horizontalLayout->addWidget(panel);
	panel->setVisible(true);
	d->data =panel;
//	d->buttons->setButtonsState(KDataPanel::Nuevo);

	newObject();
}
void KDataPanelDialog::newObject(){
	if(!d->data)
		return;
	d->data->setEstadoPanel(KDataPanel::Nuevo);
	d->buttons->setButtonsState(d->data->estadoPanel());
}

void KDataPanelDialog::clean(){
	if(!d->data)
		return;
	d->data->limpiar();
}

void KDataPanelDialog::save(){
	if(!d->data)
		return;
	if(d->data->guardar())
		d->data->limpiar();
	d->buttons->setButtonsState(d->data->estadoPanel());
}

void KDataPanelDialog::modify(){
	if(!d->data)
		return;
	d->data->setEstadoPanel(KDataPanel::Modificado);
	d->buttons->setButtonsState(d->data->estadoPanel());
}

void KDataPanelDialog::deleteObject(){
	if(!d->data)
		return;
	d->data->eliminar();
	d->buttons->setButtonsState(d->data->estadoPanel());
}

void KDataPanelDialog::search(){
	if(!d->data)
		return;
	d->data->buscar();
}
