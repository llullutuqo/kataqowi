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

#ifndef KSINGLETON_H
#define KSINGLETON_H

template <typename T>
class KSingleton
{
public:
	static T *instance() {
		static T *_instance = NULL;
		if (_instance == NULL)
			_instance = new T();
		return _instance;
	}
protected:
	KSingleton() {}
};

#endif // KSINGLETON_H
