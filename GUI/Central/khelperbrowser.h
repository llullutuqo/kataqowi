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

#ifndef KHELPERBROWSER_H
#define KHELPERBROWSER_H

#include <QTextBrowser>
class QHelpEngine;
class KHelperBrowser : public QTextBrowser
{
Q_OBJECT
public:
	explicit KHelperBrowser(QWidget *parent = 0);
	QVariant loadResource(int type, const QUrl &url);
	void setEngine(QHelpEngine *help);
private:
	QHelpEngine *m_help;
};

#endif // KHELPERBROWSER_H
