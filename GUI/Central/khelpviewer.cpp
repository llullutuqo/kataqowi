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

#include "khelpviewer.h"
#include "khelperbrowser.h"
#include <QtHelp/QHelpEngine>
#include <QDockWidget>
#include <QSplitter>
#include <QTextBrowser>
#include <QHelpEngine>
#include <QHelpSearchEngine>
#include <QLayout>
#include <QHBoxLayout>
#include <QTextCodec>
#include <QDebug>
#include <QHelpSearchQueryWidget>
#include <QHelpSearchResultWidget>
#include <QHelpContentWidget>

class KHelpViewer::KHelpViewerPrivate{
public:
	KHelpViewerPrivate(KHelpViewer *parent,QString file){
		m_help=new QHelpEngine(file,parent);
		QSplitter *helpPanel = new QSplitter(Qt::Horizontal);

		helpBrowser = new KHelperBrowser(parent);
		helpBrowser->setEngine(m_help);

		QWidget *wg = new QWidget(parent);
		wg->setLayout(new QVBoxLayout(parent));
		QTabWidget * wt = new QTabWidget(parent);
		wt->addTab(m_help->contentWidget(),"Contenido");
		wg->layout()->addWidget(m_help->searchEngine()->queryWidget());
		wg->layout()->addWidget(m_help->searchEngine()->resultWidget());
		QObject::connect(m_help->searchEngine()->queryWidget(),SIGNAL(search()),parent,SLOT(search()));
		QObject::connect(m_help->searchEngine()->resultWidget(),SIGNAL(requestShowLink(QUrl)),helpBrowser,SLOT(setSource(QUrl)));
		wt->addTab(wg,QObject::trUtf8("Búsqueda"));

		helpPanel->insertWidget(0, wt);
		helpPanel->insertWidget(1, helpBrowser);
		helpPanel->setStretchFactor(1, 1);

		parent->setLayout(new QHBoxLayout);
		parent->layout()->addWidget(helpPanel);
		parent->setWindowTitle("");
		parent->setWindowIcon(QIcon::fromTheme("help-browser"));

		connect(m_help->contentWidget(),
				SIGNAL(linkActivated(const QUrl &)),
				helpBrowser, SLOT(setSource(const QUrl &)));
				//helpBrowser,SLOT(setSource(const QUrl &)));
	}
	KHelperBrowser *helpBrowser;
	QDockWidget *helpWindow;
	QHelpEngine *m_help;
	QString path;
};


KHelpViewer::KHelpViewer(/*QWidget *parent*/) /*:
	QWidget(parent)*/
{
	d= NULL;
}
KHelpViewer::~KHelpViewer(){
	delete d;
}

bool KHelpViewer::isSetUpedDocumentation(){
	if(!d)
		return false;
	return true;
}
bool KHelpViewer::setDocumentationUrl(QString path){
	if(!d)
		d = new KHelpViewerPrivate(this,path);
	return d->m_help->setupData();
	return false;
}
QString KHelpViewer::documentationUrl(){
	return d->path;
}
void KHelpViewer::search(){
	d->m_help->searchEngine()->search( d->m_help->searchEngine()->queryWidget()->query());
}
QHelpEngine * KHelpViewer::engine(){
	return d->m_help;
}
