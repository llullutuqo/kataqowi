#include "kdatabuttons.h"
#include "kdatabuttonsplugin.h"

#include <QtCore/QtPlugin>

KDataButtonsPlugin::KDataButtonsPlugin(QObject *parent)
	: QObject(parent)
{
	m_initialized = false;
}

void KDataButtonsPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

bool KDataButtonsPlugin::isInitialized() const
{
	return m_initialized;
}

QWidget *KDataButtonsPlugin::createWidget(QWidget *parent)
{
	return new KDataButtons(parent);
}

QString KDataButtonsPlugin::name() const
{
	return QLatin1String("KDataButtons");
}

QString KDataButtonsPlugin::group() const
{
	return QLatin1String("JPRMS Solutions");
}

QIcon KDataButtonsPlugin::icon() const
{
	return QIcon(QLatin1String(":/ico.png"));
}

QString KDataButtonsPlugin::toolTip() const
{
	return QLatin1String("");
}

QString KDataButtonsPlugin::whatsThis() const
{
	return QLatin1String("");
}

bool KDataButtonsPlugin::isContainer() const
{
	return false;
}

QString KDataButtonsPlugin::domXml() const
{
	return QLatin1String("<widget class=\"KDataButtons\" name=\"kDataButtons\">\n</widget>\n");
}

QString KDataButtonsPlugin::includeFile() const
{
	return QLatin1String("kdatabuttons.h");
}

