#ifndef QRIBBONCOLLECTION_H
#define QRIBBONCOLLECTION_H

#include <qribbonplugin.h>
#include <qribbonsectionplugin.h>

#include <QtDesigner/QtDesigner>
#include <QtCore/qplugin.h>

class QRibbonCollection: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    QRibbonCollection(QObject *parent = 0);

    virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};

#endif // QRIBBONCOLLECTION_H
