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

#include "kconectionbox.h"
#include "ui_kconectionbox.h"
#include "DataBase/kdatabase.h"
#include <QMessageBox>

KConectionBox::KConectionBox(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::KConectionBox)
{
	ui->setupUi(this);
	this->ui->comboBox->addItems(KDataBase::suportedSQLDrivers());
}

KConectionBox::~KConectionBox()
{
	delete ui;
}

void KConectionBox::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}
void KConectionBox::show(){
	KConectionBox * box= new KConectionBox();
	box->exec();
	delete box;
}

void KConectionBox::on_buttonBox_accepted()
{
	QString _ms = KDataBase::conectar(this->ui->leServer->text(),this->ui->leDataBase->text(),this->ui->leUser->text(),this->ui->lePassword->text(),
						this->ui->comboBox->currentText());
	if(!_ms.isEmpty())
		QMessageBox::warning(this,"",_ms);
	else
		accept();
}
