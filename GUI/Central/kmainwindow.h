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

#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include "kdatapanel.h"
#include "gui_global.h"

class PrivateKMainWindow;
class GUISHARED_EXPORT KMainWindow : public QMainWindow {
	Q_OBJECT
public:
	KMainWindow(QWidget *parent = 0);
	~KMainWindow();
	bool setUpHelp(QString documentationFile);
protected:
	void changeEvent(QEvent *e);
	enum Acceso{
		Todo,
		Normal
	};
	QDockWidget *centralDockWidget();
	void addTab(KDataPanel *panel ,QString tittle="");
	void addWidgetTab(QWidget *panel ,QString tittle);
	void closeEvent(QCloseEvent *event);
	virtual void exit();
	KDataPanel * m_basePanel;
	QToolBar *mainToolBar();
	void setUpMainWindow(QToolBar * toolbar,QMenu *helpMenu=0);
	void setUpActions(QMenu * menu);
public slots:
	void showHelp();
	void showQuickHelp();
private slots:
	void cerrarPanel(int index);
	void currentTabChanged(int);
	void nuevo();
	void limpiar();
	void guardar();
	void modificar();
	void eliminar();
	void buscar();
protected:
	PrivateKMainWindow *d;
};

#endif // KMAINWINDOW_H
