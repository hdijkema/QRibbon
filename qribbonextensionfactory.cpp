#include "qribbonextensionfactory.h"
#include "qribboncontainerextension.h"
#include "qribbon.h"

QRibbonExtensionFactory::QRibbonExtensionFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *QRibbonExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    QRibbon *widget = qobject_cast<QRibbon*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension))) {
        return new QRibbonContainerExtension(widget, parent);
    } else {
        return 0;
    }
}
