#include "qribboncollection.h"
#include "qribbonplugin.h"
#include "qribbonsectionplugin.h"

QRibbonCollection::QRibbonCollection(QObject *parent) : QObject(parent)
{
    widgets.append(new QRibbonPlugin(this));
    widgets.append(new QRibbonSectionPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QRibbonCollection::customWidgets() const
{
    return widgets;
}
