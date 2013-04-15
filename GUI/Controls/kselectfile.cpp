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

#include "kselectfile.h"
#include "ui_kselectfile.h"
#include <QFileDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include <QBuffer>
const qint64 SIZE_LIMIT =1677721;
class KSelectFile::KSelectFilePrivate{
public:
KSelectFilePrivate(){}
	QImage _img;
	QPrinter _p;
	QByteArray _m;
};
KSelectFile::KSelectFile(QWidget *parent) :
    QWidget(parent),
	ui(new Ui::KSelectFile),
	d(new KSelectFilePrivate)
{
    ui->setupUi(this);
	ui->__le->setText("Seleccione una imagen.");
	connect(ui->__Push,SIGNAL(clicked()),this,SLOT(push_clicked()));
	connect(ui->___pbuton,SIGNAL(clicked()),this,SLOT(pbuton_clicked()));
}

KSelectFile::~KSelectFile()
{
	delete d;
	delete ui;
}

void KSelectFile::push_clicked()
{
	QFileDialog c;
	c.setNameFilter("Image files (*.png *.xpm *.jpg)");
	if(c.exec()==QDialog::Accepted){
        QFileInfo imageInfo(c.selectedFiles().at(0));
        if(imageInfo.size()> SIZE_LIMIT){
            QString text =QString::fromUtf8("La imagen seleccionada (%1 bytes) no ha podido ser cargada, el tamaño máximoes de %2 bytes.");
            QMessageBox::information(this,"Error al cargar imagen",text.arg(QString::number(imageInfo.size())).arg(QString::number(SIZE_LIMIT)));
            return;
        }
		ui->__le->setText(c.selectedFiles().at(0));
		if(!d->_img.load(c.selectedFiles().at(0))){
			QMessageBox::information(this,"Error al cargar imagen","La imagen no ha podido ser cargada");
			return;
		}
		QBuffer ba(&d->_m);
		ba.open(QIODevice::WriteOnly);
		d->_img.save(&ba,"PNG");
		d->_m=d->_m.toBase64();
		emit valueChanged(d->_m);
	}
}

const QByteArray
KSelectFile::value(){	
	return d->_m;
}

void
KSelectFile::setValue(const QByteArray &b){
	d->_img = QImage::fromData(QByteArray::fromBase64(b));
	if(d->_img.isNull())
		ui->__le->setText("Seleccione una imagen.");
	else
		ui->__le->setText("Imagen cargada.");
}

void
KSelectFile::printPreview(QPrinter* printer){
	QPainter painter(printer);
	QRect rect = painter.viewport();
	QSize size = d->_img.size();
	size.scale(rect.size(), Qt::KeepAspectRatio);
	painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
	painter.setWindow(d->_img.rect());
	painter.drawImage(0, 0, d->_img);
}

void
KSelectFile::pbuton_clicked()
{
	if(d->_img.isNull())
		return;
	QPrintPreviewDialog *dialog = new QPrintPreviewDialog(&d->_p, this);
	connect(dialog,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
	dialog->setWindowState(dialog->windowState()|Qt::WindowMaximized);
	dialog->setWindowIcon(QIcon::fromTheme("document-preview"));
	dialog->exec();
}
