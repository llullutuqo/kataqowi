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

#ifndef KDATAPANELDIALOG_H
#define KDATAPANELDIALOG_H

#include <QDialog>
#include "gui_global.h"
namespace Ui {
	class KDataPanelDialog;
}
class KDataPanel;
class GUISHARED_EXPORT KDataPanelDialog : public QDialog {
	Q_OBJECT
public:
	KDataPanelDialog(QWidget *parent = 0);
	~KDataPanelDialog();
	void setDataPanel(KDataPanel * panel);
protected:
	void changeEvent(QEvent *e);
public slots:
	void newObject();
	void clean();
	void save();
	void modify();
	void deleteObject();
	void search();
private:
	class KDataPanelDialogPrivate;
	KDataPanelDialogPrivate *d;
};

#endif // KDATAPANELDIALOG_H
