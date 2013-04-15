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

#ifndef KDATAPANEL_H
#define KDATAPANEL_H
#include "kbasepanel.h"
#include "gui_global.h"

class QToolBar;
class GUISHARED_EXPORT KDataPanel : public KBasePanel
{
Q_OBJECT
public:
	explicit KDataPanel(QWidget *parent = 0);
	enum EstadoPanel{Nulo=0,Nuevo=1,Modificado=2};
	enum Accion{Guardar=3,Eliminar =4,Cancelar=5,Limpiar=6};
	virtual void limpiar();
	virtual bool guardar();
	virtual bool eliminar();
	virtual void cancelar();
	virtual void cerrar();
	virtual bool buscar();
	EstadoPanel estadoPanel();
	void setEstadoPanel(EstadoPanel value);
	void addActionsTo(QToolBar *);
	void setVisibleActions(bool value);
	bool visibleActions();
protected:
	virtual void nuevo();
	virtual void modificar();
	virtual void anular();
private:
	EstadoPanel m_estadoPanel;
	bool m_mantenerFluidez;
	bool m_vsible;
};

#endif // KDATAPANEL_H
