#include "ksearchdata.h"
#include "ksearchdataplugin.h"

#include <QtCore/QtPlugin>

KSearchDataPlugin::KSearchDataPlugin(QObject *parent)
	: QObject(parent)
{
	m_initialized = false;
}

void KSearchDataPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

bool KSearchDataPlugin::isInitialized() const
{
	return m_initialized;
}

QWidget *KSearchDataPlugin::createWidget(QWidget *parent)
{
	return new KSearchData(parent);
}

QString KSearchDataPlugin::name() const
{
	return QLatin1String("KSearchData");
}

QString KSearchDataPlugin::group() const
{
	return QLatin1String("JPRMS Solutions");
}

QIcon KSearchDataPlugin::icon() const
{
	return QIcon(QLatin1String(":/ico.png"));
}

QString KSearchDataPlugin::toolTip() const
{
	return QLatin1String("");
}

QString KSearchDataPlugin::whatsThis() const
{
	return QLatin1String("");
}

bool KSearchDataPlugin::isContainer() const
{
	return false;
}

QString KSearchDataPlugin::domXml() const
{
	return QLatin1String("<widget class=\"KSearchData\" name=\"kSearchData\">\n</widget>\n");
}

QString KSearchDataPlugin::includeFile() const
{
	return QLatin1String("ksearchdata.h");
}

