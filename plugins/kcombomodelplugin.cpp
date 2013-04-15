#include "kcombomodel.h"
#include "kcombomodelplugin.h"

#include <QtCore/QtPlugin>

KComboModelPlugin::KComboModelPlugin(QObject *parent)
	: QObject(parent)
{
	m_initialized = false;
}

void KComboModelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

bool KComboModelPlugin::isInitialized() const
{
	return m_initialized;
}

QWidget *KComboModelPlugin::createWidget(QWidget *parent)
{
	return new KComboModel(parent);
}

QString KComboModelPlugin::name() const
{
	return QLatin1String("KComboModel");
}

QString KComboModelPlugin::group() const
{
	return QLatin1String("JPRMS Solutions");
}

QIcon KComboModelPlugin::icon() const
{
	return QIcon(QLatin1String(":/ico.png"));
}

QString KComboModelPlugin::toolTip() const
{
	return QLatin1String("");
}

QString KComboModelPlugin::whatsThis() const
{
	return QLatin1String("");
}

bool KComboModelPlugin::isContainer() const
{
	return false;
}

QString KComboModelPlugin::domXml() const
{
	return QLatin1String("<widget class=\"KComboModel\" name=\"kComboModel\">\n</widget>\n");
}

QString KComboModelPlugin::includeFile() const
{
	return QLatin1String("kcombomodel.h");
}

