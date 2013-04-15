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

#ifndef KDATABUTTONS_H
#define KDATABUTTONS_H

#include <QWidget>
#include <QPaintEvent>
#include "gui_global.h"
class GUISHARED_EXPORT  KDataButtons : public QWidget
{
Q_OBJECT
public:
	explicit KDataButtons(QWidget *parent = 0);
	//También se puede usar las numeraciones de KDataPanel::EstadoPanel
	void setButtonsState(int value);
protected:
	void changeEvent(QEvent *e);
signals:
	void newClicked();
	void modifyClicked();
	void searchClicked();
	void cleanClicked();
	void saveClicked();
	void deleteClicked();
private slots:
	void newClick();
	void modifyCLick();
	void searchCLick();
	void cleanCLick();
	void saveCLick();
	void deleteCLick();

private :
	class KDataButtonsPrivate;
	KDataButtonsPrivate *d;
};

#endif // KDATABUTTONS_H
