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

#include "kmainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QTabWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtGui/QApplication>
#include "khelpviewer.h"
#include <QAction>
#include <QTextBrowser>
#include <QMenu>
#include "khelperbrowser.h"
#include "Widgets/kdatabuttons.h"
#include <QToolBar>
#include <QMessageBox>

class PrivateKMainWindow{
public:
	PrivateKMainWindow(){
		m_helper=NULL;
		centralWidget=NULL;
		dockWidget =NULL;
	}
	~PrivateKMainWindow(){
		delete m_helper;
	}

	void setUpWin(KMainWindow * parent,QToolBar * toolbar,QMenu *menu=0){
		mainToolBar = toolbar;
		mainToolBar->setMovable(true);
		mainToolBar->setFloatable(false);
		mainToolBar->setWindowTitle("Barra de Herramientas");
		m_helper = new KHelpViewer();
		actionNew = new QAction(parent);
		actionNew->setObjectName(QString::fromUtf8("actionNew"));
		actionNew->setEnabled(false);
		actionNew->setIcon(QIcon::fromTheme("document-new",QIcon(":/icons/16x/document-new.png")));
		actionNew->setShortcut(QKeySequence("Ctrl+N"));
		actionModify = new QAction(parent);
		actionModify->setObjectName(QString::fromUtf8("actionModify"));
		actionModify->setEnabled(false);
		actionModify->setIcon(QIcon::fromTheme("document-edit",QIcon(":/icons/16x/document-edit.png")));
		actionModify->setShortcut(QKeySequence("Ctrl+M"));
		actionSave = new QAction(parent);
		actionSave->setObjectName(QString::fromUtf8("actionSave"));
		actionSave->setEnabled(false);
		actionSave->setIcon(QIcon::fromTheme("document-save",QIcon(":/icons/16x/document-save.png")));
		actionSave->setShortcut(QKeySequence("Ctrl+S"));
		actionDelete = new QAction(parent);
		actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
		actionDelete->setEnabled(false);
		actionDelete->setIcon(QIcon::fromTheme("edit-delete",QIcon(":/icons/16x/edit-delete.png")));
		actionDelete->setShortcut(QKeySequence("Ctrl+D"));
		actionClean = new QAction(parent);
		actionClean->setObjectName(QString::fromUtf8("actionClean"));
		actionClean->setEnabled(false);
		actionClean->setIcon(QIcon::fromTheme("edit-clear",QIcon(":/icons/16x/edit-clear.png")));
		actionClean->setShortcut(QKeySequence("Ctrl+L"));
		actionSearch = new QAction(parent);
		actionSearch->setObjectName(QString::fromUtf8("actionSearch"));
		actionSearch->setEnabled(false);
		actionSearch->setIcon(QIcon::fromTheme("edit-find",QIcon(":/icons/16x/edit-find.png")));
		actionSearch->setShortcut(QKeySequence("Ctrl+F"));
		delete parent->centralWidget();
		centralWidget = new QTabWidget(parent);
		centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
		centralWidget->setElideMode(Qt::ElideNone);
		centralWidget->setUsesScrollButtons(true);
		centralWidget->setDocumentMode(true);
		centralWidget->setTabsClosable(true);
		centralWidget->setMovable(true);
		parent->setCentralWidget(centralWidget);
		dockWidget = new QDockWidget(parent);
		dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
		dockWidget->setMinimumSize(QSize(40, 252));
		dockWidget->setMaximumSize(QSize(40, 524287));
		dockWidget->setFloating(false);
		dockWidget->setWindowTitle("Acciones");
		dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
		dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
//		buttons = new KDataButtons(dockWidget);
//		dockWidget->setWidget(buttons);
		//TODO: verificar por qué no se puede personalizar el fondo sin necesidad de colocar un widget
		QWidget * ds = new QWidget(dockWidget);
		ds->setLayout(new QVBoxLayout(ds));
		buttons = new KDataButtons(dockWidget);
		ds->layout()->addWidget(buttons);
		ds->layout()->setSpacing(0);
		ds->layout()->setContentsMargins(0, 0, 0, 0);
		dockWidget->setWidget(ds);
		parent->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

		dockAyuda = new QDockWidget(parent);
		dockAyuda->setWindowTitle(QObject::trUtf8("Ayuda Rápida"));
		quickBrowser = new KHelperBrowser(dockAyuda);
		dockAyuda->setWidget(quickBrowser);
		dockAyuda->setVisible(false);
		parent->addDockWidget(Qt::RightDockWidgetArea,dockAyuda);

		QObject::connect(actionClean,SIGNAL(triggered()),parent,SLOT(limpiar()));
		QObject::connect(actionDelete,SIGNAL(triggered()),parent,SLOT(eliminar()));
		QObject::connect(actionModify,SIGNAL(triggered()),parent,SLOT(modificar()));
		QObject::connect(actionNew,SIGNAL(triggered()),parent,SLOT(nuevo()));
		QObject::connect(actionSave,SIGNAL(triggered()),parent,SLOT(guardar()));
		QObject::connect(actionSearch,SIGNAL(triggered()),parent,SLOT(buscar()));

		QObject::connect(buttons,SIGNAL(cleanClicked()),parent,SLOT(limpiar()));
		QObject::connect(buttons,SIGNAL(deleteClicked()),parent,SLOT(eliminar()));
		QObject::connect(buttons,SIGNAL(modifyClicked()),parent,SLOT(modificar()));
		QObject::connect(buttons,SIGNAL(newClicked()),parent,SLOT(nuevo()));
		QObject::connect(buttons,SIGNAL(saveClicked()),parent,SLOT(guardar()));
		QObject::connect(buttons,SIGNAL(searchClicked()),parent,SLOT(buscar()));
		actionQuickHelp=NULL;
		actionHelpBook=NULL;
		if(menu){
			actionQuickHelp = new QAction(parent);
			actionQuickHelp->setObjectName(QString::fromUtf8("actionQuickHelp"));
			actionQuickHelp->setEnabled(false);
			actionQuickHelp->setIcon(QIcon::fromTheme("help-contextual"));
			actionQuickHelp->setShortcut(QKeySequence("F1"));
			actionQuickHelp->setEnabled(true);
			actionHelpBook = new QAction(parent);
			actionHelpBook->setObjectName(QString::fromUtf8("actionHelpBook"));
			actionHelpBook->setEnabled(false);
			actionHelpBook->setIcon(QIcon::fromTheme("help-contents"));
			actionHelpBook->setShortcut(QKeySequence("CTRL+F1"));
			actionHelpBook->setEnabled(true);
			menu->addAction(actionQuickHelp);
			menu->addAction(actionHelpBook);
			QObject::connect(actionHelpBook,SIGNAL(triggered()),parent,SLOT(showHelp()));
			QObject::connect(actionQuickHelp,SIGNAL(triggered()),parent,SLOT(showQuickHelp()));
			//menu.
		}
		translateUi();
	}
	void translateUi(){
		actionNew->setText(QObject::trUtf8("Nuevo"));
		actionClean->setText(QObject::trUtf8("Limpiar"));
		actionDelete->setText(QObject::trUtf8("Eliminar"));
		actionModify->setText(QObject::trUtf8("Modificar"));
		actionSave->setText(QObject::trUtf8("Guardar"));
		actionSearch->setText(QObject::trUtf8("Buscar"));
		if(actionQuickHelp)
			actionQuickHelp->setText(QObject::trUtf8("Ayuda rápida"));
		if(actionHelpBook)
		actionHelpBook->setText(QObject::trUtf8("Contenido de ayuda"));
	}

	void setState(KDataPanel::EstadoPanel value){
		buttons->setButtonsState(value);
		switch(value){
		case KDataPanel::Nuevo:
			actionNew->setEnabled(false);
			actionModify->setEnabled(true);
			actionClean->setEnabled(true);
			actionSearch->setEnabled(false);
			actionDelete->setEnabled(false);
			actionSave->setEnabled(true);
			break;
		case KDataPanel::Modificado:
			actionNew->setEnabled(true);
			actionModify->setEnabled(false);
			actionClean->setEnabled(true);
			actionSearch->setEnabled(true);
			actionDelete->setEnabled(true);
			actionSave->setEnabled(true);
			break;
		case KDataPanel::Nulo:
			actionNew->setEnabled(false);
			actionModify->setEnabled(false);
			actionClean->setEnabled(false);
			actionSearch->setEnabled(false);
			actionDelete->setEnabled(false);
			actionSave->setEnabled(false);
			break;
		}
	}
	QAction *actionQuickHelp;
	QAction *actionHelpBook;
	QDockWidget *dockWidget;
	QDockWidget *dockAyuda;
	QTabWidget *centralWidget;
	QToolBar * mainToolBar;
	QAction *actionNew;
	QAction *actionModify;
	QAction *actionSave;
	QAction *actionDelete;
	QAction *actionClean;
	QAction *actionSearch;
	KHelperBrowser *quickBrowser;
	KHelpViewer *m_helper;
	KDataButtons *buttons;
};

KMainWindow::KMainWindow(QWidget *parent) :
	QMainWindow(parent),
	d(new PrivateKMainWindow())
{
	m_basePanel=NULL;
}
KMainWindow::~KMainWindow()
{
	delete d;
}
void KMainWindow::setUpMainWindow(QToolBar *toolbar,QMenu *menu){
	d->setUpWin(this,toolbar,menu);
	connect(d->centralWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(cerrarPanel(int)));
	connect(d->centralWidget,SIGNAL(currentChanged(int)),this,SLOT(currentTabChanged(int)));
	d->buttons->setButtonsState(KDataPanel::Nulo);
}

void KMainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		d->translateUi();
		break;
	default:
		break;
	}
}
QDockWidget *KMainWindow::centralDockWidget(){
	return d->dockWidget;
}
QToolBar *KMainWindow::mainToolBar(){
	return d->mainToolBar;
}
void KMainWindow::showHelp(){
	if(!d->m_helper){
		qDebug()<<trUtf8("Debe llamar a la función setupWindow() antes de intentar carga la ayuda.");
		return;
	}
	d->dockAyuda->setVisible(false);
	addWidgetTab(d->m_helper,"Ayuda");
}
void KMainWindow::showQuickHelp(){
	if(!d->m_helper->isSetUpedDocumentation()){
		d->dockAyuda->setVisible(true);
		d->quickBrowser->setHtml(tr("<p>La ayuda no ha sido cargada</p>"));
		return;
	}
	if(!d->dockAyuda->isVisible()){
		d->dockAyuda->setVisible(true);
		if(d->centralWidget->currentIndex()>-1){
			QString url ="qthelp://com.help/help/"+d->centralWidget->currentWidget()->objectName()+".html";
			d->quickBrowser->setSource(QUrl(url));
		}
	}
	else
		d->dockAyuda->setVisible(false);
}

bool KMainWindow::setUpHelp(QString path){
	if(!d->m_helper){
		qDebug()<<trUtf8("Debe llamar a la función setupWindow() antes de intentar carga la ayuda.");
		return false;
	}
	bool sald=d->m_helper->setDocumentationUrl(path);
	if(sald){
		d->quickBrowser->setEngine(d->m_helper->engine());
	}
	return sald;
}

void  KMainWindow::addTab(KDataPanel *panel ,QString tittle){
	if(!d->centralWidget)
		return;
	addWidgetTab(panel,tittle);
	panel->addActionsTo(d->mainToolBar);
	nuevo();
}

void  KMainWindow::addWidgetTab(QWidget *panel ,QString tittle){
	if(!d->centralWidget)
		return;
	if(tittle=="")
		tittle = panel->windowTitle();
	d->centralWidget->setCurrentIndex(d->centralWidget->addTab(panel,panel->windowIcon(),tittle));
}

void KMainWindow::exit(){
	if(d->centralWidget){
		for(int i =0;i<d->centralWidget->count();i++)
			cerrarPanel(i);
	}
	qApp->exit(0);
}
void KMainWindow::closeEvent(QCloseEvent *event)
 {
	 exit();
	 event->accept();
 }

//INICIO SLOTS DE ACCIÓN
void KMainWindow::nuevo(){
	if(!m_basePanel)
		return;
	m_basePanel->setEstadoPanel(KDataPanel::Nuevo);
	d->setState(m_basePanel->estadoPanel());
}
void KMainWindow::guardar(){
	if(!m_basePanel)
		return;
	if(m_basePanel->guardar()){
		QMessageBox::information(this,tr("Grabado correctamente"),tr("El registro ha sido grabado en la base de datos correctamente."));
		m_basePanel->limpiar();
	}
	d->setState(m_basePanel->estadoPanel());
}
void KMainWindow::eliminar(){
	if(!m_basePanel)
		return;
	m_basePanel->eliminar();
	d->setState(m_basePanel->estadoPanel());
}
void KMainWindow::modificar(){
	if(!m_basePanel)
		return;
	m_basePanel->setEstadoPanel(KDataPanel::Modificado);
	d->setState(m_basePanel->estadoPanel());
}
void KMainWindow::limpiar(){
	if(!m_basePanel)
		return;
	m_basePanel->limpiar();
}
void KMainWindow::buscar(){
	if(!m_basePanel)
		return;
	m_basePanel->buscar();
}
//FIN SLOTS DE ACCIÓN
void KMainWindow::cerrarPanel(int index){
//	QWidget *v =d->centralWidget->widget(index);
//	ABasePanel * panel = qobject_cast<ABasePanel *>(d->centralWidget->widget(index));
//	if(panel && panel->deleteOncloseRequest())
//		delete panel;
//	else
	d->centralWidget->removeTab(index);
}
void KMainWindow::currentTabChanged(int index )
{
	if(m_basePanel)
		m_basePanel->setVisibleActions(false);
	if(index<0){
		d->setState(KDataPanel::Nulo);
		m_basePanel=NULL;
		return;
	}
	m_basePanel = qobject_cast<KDataPanel *>(d->centralWidget->currentWidget());
	if(m_basePanel){
		d->setState(m_basePanel->estadoPanel());
		m_basePanel->setVisibleActions(true);
	}
	else{
		d->setState(KDataPanel::Nulo);
		m_basePanel=NULL;
	}
}
void KMainWindow::setUpActions(QMenu * menu){
	menu->addAction(d->actionNew);
	menu->addAction(d->actionModify);
	menu->addAction(d->actionSearch);
	menu->addAction(d->actionClean);
	menu->addAction(d->actionSave);
	menu->addAction(d->actionDelete);
}
