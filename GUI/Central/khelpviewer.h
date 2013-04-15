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

#ifndef KHELPVIEWER_H
#define KHELPVIEWER_H

#include <QWidget>
#include <QUrl>
#include "gui_global.h"
class AHelperBrowser;
class QHelpEngine;
class GUISHARED_EXPORT KHelpViewer : public QWidget
{
    Q_OBJECT
public:
	explicit KHelpViewer(/*QWidget *parent = 0*/);
	~KHelpViewer();
	QString documentationUrl();
	bool isSetUpedDocumentation();
	QHelpEngine * engine();
signals:

public slots:
	bool setDocumentationUrl(QString path);
private slots:
	void search();
private:
	class KHelpViewerPrivate;
	KHelpViewerPrivate *d;
};

#endif // KHELPVIEWER_H
