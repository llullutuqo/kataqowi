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

#ifndef KSEARCHDATA_H
#define KSEARCHDATA_H

#include <QWidget>
#include <QModelIndex>
#include "gui_global.h"

class QSqlQueryModel;
class QTableView;
namespace Ui {
	class KSearchData;
}
class GUISHARED_EXPORT KSearchData : public QWidget {
	Q_OBJECT
	Q_PROPERTY(bool ButtonVisible READ isButtonVisible WRITE setButtonVisible)
public:
	KSearchData(QWidget *parent = 0,Qt::WindowType =Qt::Widget);
	~KSearchData();
	void setTableName(QString value);
	void setSQL(QString sql);
    const QString sql();
	QString tableName();
	void addFilter(QString filterName,QString filter);
	void setButtonVisible(bool value);
	bool isButtonVisible();
    void setTextFilter(QString string);
    void setShowAllFilter(bool value);
	QTableView * tableView();
protected:
	void changeEvent(QEvent *e);
signals:
	void doubleClick(QVariant code);
	void buttonClicked();
public slots:
	void show();
    void select();
private:
	class KSearchDataPrivate;
	KSearchDataPrivate *d;
	Ui::KSearchData *ui;
private slots:
	void on_comboBox_currentIndexChanged(QString );
	void _doubleClicked(QModelIndex index);
	void lEditTextChanged(QString );
	void _clicked();
};
#endif // KSEARCHDATA_H
