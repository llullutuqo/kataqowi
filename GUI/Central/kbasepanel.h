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

#ifndef KBASEPANEL_H
#define KBASEPANEL_H

#include <QWidget>
#include "gui_global.h"
/**
* @brief
*
* @class BasePanel basepanel.h "basepanel.h"
*/
class GUISHARED_EXPORT KBasePanel : public QWidget{
	Q_OBJECT
public:
	explicit KBasePanel(QWidget *parent = 0);
	bool deleteOncloseRequest();
	void setDeleteOncloseRequest(bool value);
private:
	class KBasePanelPrivate;
	KBasePanelPrivate *d;
};

#endif // KBASEPANEL_H
