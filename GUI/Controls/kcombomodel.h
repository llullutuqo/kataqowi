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

#ifndef KCOMBOMODEL_H
#define KCOMBOMODEL_H

#include <QWidget>
#include "gui_global.h"
#include <QStyleOptionComboBox>
#include <QStylePainter>
#include <QCompleter>
#include <QComboBox>
#include <QLineEdit>

class QEvent;
class KDataClass;
class KSearchData;
class GUISHARED_EXPORT KComboModel : public QComboBox {
	Q_OBJECT
public:
	KComboModel(QWidget *parent = 0);
	~KComboModel();

	void setEnableDropDown(bool value);
	bool isEnableDropDown();
	void setEditableText(bool value);
	bool editableText();
	void setDataClass(KDataClass *value, bool normal =false);
	void addFilter(QString filterName,QString filter);
	virtual void showPopup(QString base);
	void showPopup();
	virtual void hidePopup();
	void setMaxLength(int length);
	void setSQL(QString sql);
	KSearchData * searchData();
public slots:
	void setText(QString text);
	void setText(int number);
private:
	KSearchData * m_search;
	KDataClass *m_data;
	bool m_enabledrop;
private slots:
	void getText(QString);
	void _clicked();
signals:
	void selectedRow(QVariant firstItem);
	void buttonSearchClicked();
	void editTextChanged(int );
};

#endif // KCOMBOMODEL_H
