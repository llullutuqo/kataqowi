#include "kataqowi.h"
#include "kcombomodelplugin.h"
#include "ksearchdataplugin.h"
#include "kdatabuttonsplugin.h"
#include "kdatapanelplugin.h"

KataQowi::KataQowi(): QObject(parent)
{
	m_widgets.append(new AComboModelPlugin(this));
	m_widgets.append(new ASearchDataPlugin(this));
	m_widgets.append(new ADataButtonsPlugin(this));
	m_widgets.append(new ADataPanelPlugin(this));

}

QList<QDesignerCustomWidgetInterface*>
KataQowi::customWidgets() const
{
	return m_widgets;
}

Q_EXPORT_PLUGIN2(kataqowiplugin, KataQowi)
