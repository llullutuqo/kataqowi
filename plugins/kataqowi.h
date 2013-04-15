#ifndef KATAQOWI_H
#define KATAQOWI_H

#include <QtDesigner/QtDesigner>
#include <QtPlugin>

class KataQowi : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
	explicit KataQowi(QObject *parent = 0);
	virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;
private:
	QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif // KATAQOWI_H
