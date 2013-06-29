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

#include "kdocument.h"
#include <QFile>
#include <QTextStream>
#ifdef QT_DEBUG
#include <QDebug>
#endif
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QSqlQuery>
#include <QAbstractTextDocumentLayout>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QPainter>
#include <QIcon>

static inline double mmToInches(double mm) { return mm * 0.039370147; }
KDocument::KDocument(QObject *parent):QObject(parent)
{
	m_printer = new QPrinter(QPrinter::HighResolution);
	topmargin_=11;
	leftmargin_=25;
	rightmargin_=25;
	bottommargin_=15;
	spacing_=5;
	headersize_=0;
	tempdoc_=NULL;
	m_unit =QPrinter::Millimeter;
	m_printer->setOrientation(QPrinter::Portrait);
	tempdoc_=  new QTextDocument();
    index=0;
}
KDocument::~KDocument()
{
	delete m_printer;
	if(tempdoc_)
		delete tempdoc_;
}
void KDocument::addArguments(QString arg){
    index += 1;
    //const QString def ="%"+QString::number(index);
    const QString defa ="[%"+QString::number(index) +"]";
#ifdef QT_DEBUG
    qDebug()<<"index gen:"<<index<<":"<<defa;
#endif
    m_con = m_con.replace(defa,arg);
    //m_con = m_con.replace(def,arg);
}

void
KDocument::setArgument(QString key, QString arg){
	m_con=m_con.replace(key,arg);
}
void KDocument::replaceInHeader(QString regex,QString replace){
	m_header.replace(regex,replace);
}

QPrinter *
KDocument::printer()
{
	return m_printer;
}

void KDocument::addArguments(QStringList args){
	for(int i =0;i<args.count();i++)
        addArguments(args[i]);
}
void KDocument::setOrientation(QPrinter::Orientation orientation)
{
	m_printer->setOrientation(orientation);
}

double KDocument::leftMargin() const
{
	return leftmargin_;
}

void KDocument::setLeftMargin(double margin)
{
	if ((margin > 0) && (margin < m_printer->paperRect().width() / 2)) {
		leftmargin_ = margin;
	} else {
		leftmargin_ = 0;
	}
}

double KDocument::rightMargin() const
{
	return rightmargin_;
}

void KDocument::setRightMargin(double margin)
{
	if ((margin > 0) && (margin < m_printer->paperRect().width() / 2)) {
		rightmargin_ = margin;
	} else {
		rightmargin_ = 0;
	}
}

double KDocument::topMargin() const
{
	return topmargin_;
}

void KDocument::setTopMargin(double margin)
{
	if ((margin > 0) && (margin < m_printer->paperRect().height() / 4)) {
		topmargin_ = margin;
	} else {
		topmargin_ = 0;
	}
}

double KDocument::bottomMargin() const
{
	return bottommargin_;
}

void KDocument::setBottomMargin(double margin)
{
	if ((margin > 0) && (margin < m_printer->paperRect().height() / 4)) {
		bottommargin_ = margin;
	} else {
		bottommargin_ = 0;
	}
}
double KDocument::spacing() const
{
	return spacing_;
}

void KDocument::setSpacing(double spacing)
{
	if ((spacing > 0) && (spacing <= m_printer->paperRect().height() / 8)) {
		spacing_ = spacing;
	} else {
		spacing_ = 0;
	}
}

double KDocument::headerHeight() const
{
	return headersize_;
}

void KDocument::setHeaderHeight(double size)
{
	if ((size > 0) && (size <= m_printer->paperRect().height() / 8)) {
		headersize_ = size;
	} else {
		headersize_ = 0;
	}
}
void KDocument::showPreview(bool modal){
	render();
	QPrintPreviewDialog printPreviewDialog(m_printer, 0);
	connect(&printPreviewDialog, SIGNAL(paintRequested(QPrinter*)),this, SLOT(print(QPrinter*)));
	printPreviewDialog.setWindowState(printPreviewDialog.windowState()|Qt::WindowMaximized);
	printPreviewDialog.setWindowIcon(QIcon::fromTheme("document-preview"));
	if(modal)
		printPreviewDialog.exec();
	else
		printPreviewDialog.show();
	//delete tempdoc_;
	//tempdoc_ =0;
}

void
KDocument::render(){
	tempdoc_->setHtml(m_con);
}

QString KDocument::loadDocument(QString file){
	QFile files(file);
	if (!files.open(QFile::ReadOnly | QFile::Text)) {
#ifdef QT_DEBUG
		qDebug()<<"No se puede leer el fichero";
#endif
		return "";
	}
	QTextStream in(&files);
	return in.readAll();
}

void KDocument::setPageSize(qreal width, qreal height){
	m_printer->setPaperSize(QSizeF(width,height),QPrinter::Millimeter);
}

void KDocument::setMargins(qreal uniformMargin){
	topmargin_=uniformMargin;
	leftmargin_=uniformMargin;
	rightmargin_=uniformMargin;
	bottommargin_=uniformMargin;
}

void KDocument::loadBodyFromFile(QString filename){
	m_conBase = loadDocument(filename);
	revertChanges();
}

void
KDocument::revertChanges(){
	m_con = m_conBase;
}

void KDocument::loadHeaderFromFile(QString filename,double heigth){
	headersize_ =heigth;
	m_header = loadDocument(filename);
}
void KDocument::print(QPrinter *printer)
{
	if (!printer || !tempdoc_) return;
	printer->setPageMargins(leftmargin_,topmargin_,rightmargin_,bottommargin_,m_unit);
	tempdoc_->setUseDesignMetrics(true);
	tempdoc_->documentLayout()->setPaintDevice(printer);
	tempdoc_->setPageSize(contentRect(printer).size());
	int doccopies;
	int pagecopies;
	if (printer->collateCopies()) {
		doccopies = 1;
		pagecopies = printer->numCopies();
	} else {
		doccopies = printer->numCopies();
		pagecopies = 1;
	}

	// get page range
	int firstpage = printer->fromPage();
	int lastpage = printer->toPage();
	if (firstpage == 0 && lastpage == 0) { // all pages
		firstpage = 1;
		lastpage = tempdoc_->pageCount();
	}

	// print order
	bool ascending = true;
	if (printer->pageOrder() == QPrinter::LastPageFirst) {
		int tmp = firstpage;
		firstpage = lastpage;
		lastpage = tmp;
		ascending = false;
	}

	// loop through and print pages
	QPainter painter(printer);
	painter.setRenderHints(QPainter::Antialiasing |
						   QPainter::TextAntialiasing |
						   QPainter::SmoothPixmapTransform, true);
	int count = ascending ? lastpage :firstpage;
	for (int dc=0; dc<doccopies; dc++) {
		int pagenum = firstpage;
		while (true) {
			for (int pc=0; pc<pagecopies; pc++) {
				if (printer->printerState() == QPrinter::Aborted ||
					printer->printerState() == QPrinter::Error) {
					return;
				}
				// print page
				paintPage(&painter, tempdoc_, pagenum,count);
				if (pc < pagecopies-1) printer->newPage();
			}
			if (pagenum == lastpage) break;
			if (ascending) pagenum++;
			else           pagenum--;
			printer->newPage();
		}

		if (dc < doccopies-1) printer->newPage();
	}
}
void KDocument::paintPage(QPainter *painter,
							QTextDocument *document,
							int pagenum,int pagecount)
{
	QRectF rect;
#ifdef QT_DEBUG
	qDebug()<<"Num1:"<<pagenum;
#endif
	//double onepoint = painter->device()->logicalDpiY() / 72.0;
	if (!m_header.isEmpty()) {
		rect = headerRect(painter->device());
		painter->save();
		painter->translate(rect.left(), rect.top());
		QRectF clip(0, 0, rect.width(), rect.height());
		QTextDocument doc;
		QString d_header =m_header;
		doc.setUseDesignMetrics(true);
		doc.setHtml(d_header.replace("[pagenum]",QString::number(pagenum)).replace("[pagecount]",QString::number(pagecount)));
		doc.documentLayout()->setPaintDevice(painter->device());
		doc.setPageSize(rect.size());
		double newtop = clip.bottom() - doc.size().height();
		clip.setHeight(doc.size().height());
		painter->translate(0, newtop);
		doc.drawContents(painter, clip);
		painter->restore();
	}
	painter->save();

	rect = contentRect(painter->device());
	painter->translate(rect.left(), rect.top() - (pagenum-1) * rect.height());
	QRectF clip(0, (pagenum-1) * rect.height(), rect.width(), rect.height());

	document->drawContents(painter, clip);

	painter->restore();
}
QRectF KDocument::paperRect(QPaintDevice *device)
{
	QRectF rect = m_printer->paperRect();
	rect.setWidth(rect.width() *
				  device->logicalDpiX() / m_printer->logicalDpiX());
	rect.setHeight(rect.height() *
				  device->logicalDpiY() / m_printer->logicalDpiY());

	return rect;
}
QRectF KDocument::headerRect(QPaintDevice *device)
{
	QRectF rect = paperRect(device);
	rect.adjust(0,
				0,
				-(mmToInches(rightmargin_)+ mmToInches(leftmargin_))* device->logicalDpiX(), 0);
	rect.setBottom(rect.top() + mmToInches(headersize_) * device->logicalDpiY());
	return rect;
}
QRectF KDocument::contentRect(QPaintDevice *device)
{
	QRectF rect = paperRect(device);

	rect.adjust(0,
				0,
				-(mmToInches(rightmargin_)+ mmToInches(leftmargin_))* device->logicalDpiX(),
				-(mmToInches(bottommargin_)+mmToInches(topmargin_)) * device->logicalDpiY());

	if (headersize_ > 0) {
		rect.adjust(0, mmToInches(headersize_) * device->logicalDpiY(), 0, 0);
		rect.adjust(0, mmToInches(spacing_) * device->logicalDpiY(), 0, 0);
	}
	return rect;
}
