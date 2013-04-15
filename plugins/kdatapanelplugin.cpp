#include "kdatapanel.h"
#include "kdatapanelplugin.h"

#include <QtCore/QtPlugin>

KDataPanelPlugin::KDataPanelPlugin(QObject *parent)
	: QObject(parent)
{
	m_initialized = false;
}

void KDataPanelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

bool KDataPanelPlugin::isInitialized() const
{
	return m_initialized;
}

QWidget *KDataPanelPlugin::createWidget(QWidget *parent)
{
	KDataPanel *ad = new KDataPanel(parent) ;
	ad->setEnabled(true);
	return ad;
}

QString KDataPanelPlugin::name() const
{
	return QLatin1String("KDataPanel");
}

QString KDataPanelPlugin::group() const
{
	return QLatin1String("JPRMS Solutions");
}

QIcon KDataPanelPlugin::icon() const
{
	return QIcon(QLatin1String(":/ico.png"));
}

QString KDataPanelPlugin::toolTip() const
{
	return QLatin1String("");
}

QString KDataPanelPlugin::whatsThis() const
{
	return QLatin1String("");
}

bool KDataPanelPlugin::isContainer() const
{
	return true;
}

QString KDataPanelPlugin::domXml() const
{
	return QLatin1String("<widget class=\"KDataPanel\" name=\"kDataPanel\">\n</widget>\n");
}

QString KDataPanelPlugin::includeFile() const
{
	return QLatin1String("kdatapanel.h");
}

