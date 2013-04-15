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

#ifndef KCONECTIONBOX_H
#define KCONECTIONBOX_H

#include <QDialog>
#include "gui_global.h"
namespace Ui {
	class KConectionBox;
}

class GUISHARED_EXPORT KConectionBox : public QDialog {
	Q_OBJECT
public:
	KConectionBox(QWidget *parent = 0);
	~KConectionBox();
	static void show();
	void connect();
protected:
	void changeEvent(QEvent *e);

private:
	Ui::KConectionBox *ui;

private slots:
	void on_buttonBox_accepted();
};

#endif // KCONECTIONBOX_H
