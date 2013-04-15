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

#ifndef KSELECTFILE_H
#define KSELECTFILE_H

#include <QWidget>
#include <QByteArray>
#include "gui_global.h"

namespace Ui {
    class KSelectFile;
}

class GUISHARED_EXPORT KSelectFile : public QWidget
{
    Q_OBJECT

public:
	explicit KSelectFile(QWidget *parent = 0);
    ~KSelectFile();
	const QByteArray value();
public slots:
	void setValue(const QByteArray &);
private slots:
	void push_clicked();
	void printPreview(QPrinter*);
	void pbuton_clicked();
signals:
	void valueChanged(const QByteArray value);
private:
    Ui::KSelectFile *ui;
	class KSelectFilePrivate;
	KSelectFilePrivate * d;
};

#endif // KSELECTFILE_H
