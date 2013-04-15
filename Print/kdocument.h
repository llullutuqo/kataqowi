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

#ifndef KDOCUMENT_H
#define KDOCUMENT_H

#include <QString>
#include <QObject>
#include <QTextDocument>
#include <QStringList>
#include "print_global.h"
#include <QPrinter>

class PRINTSHARED_EXPORT KDocument : public QObject
{
	Q_OBJECT
public:
	KDocument(QObject *parent = 0);
	~KDocument();
	void addArguments(QString arg);
	void setArgument(QString key, QString arg);
	void addArguments(QStringList args);
	void showPreview(bool modal = true);
	void loadHeaderFromFile(QString filename,double heigth);
	void loadBodyFromFile(QString filename);
	void print(const QTextDocument *document,const QString &caption=QString());
	void paintPage(QPainter *painter,QTextDocument *document,int pagenum,int pagecount);
	double leftMargin() const;
	void setLeftMargin(double margin);
	double rightMargin() const;
	void setRightMargin(double margin);
	double topMargin() const;
	void setTopMargin(double margin);
	double bottomMargin() const;
	void setBottomMargin(double margin);
	double spacing() const;
	void setHeaderHeight(double spacing);
	double headerHeight() const;
	void setSpacing(double spacing);
	void setOrientation(QPrinter::Orientation orientation);
	void replaceInHeader(QString regex,QString replace);
	void setPageSize(qreal width, qreal height);
	void setMargins(qreal uniformMargin);
	void render();
	void revertChanges();
	QPrinter * printer();
public slots:
	void print(QPrinter *printer);
private:
	QString loadDocument(QString file);
	//QString m_file;
	QString m_con;
	QString m_conBase;
	//QTextDocument doc;
	QTextDocument *tempdoc_;
	QString m_header;
	QRectF paperRect(QPaintDevice *device);
	QRectF contentRect(QPaintDevice *device);
	QRectF headerRect(QPaintDevice *device);
	double leftmargin_;
	double rightmargin_;
	double topmargin_;
	double bottommargin_;
	double spacing_;
	double headersize_;
	QPrinter::Unit m_unit;
protected:
	QPrinter * m_printer;
//public slots:
//	void printPreview(QPrinter* print);
};

#endif // KDOCUMENT_H
