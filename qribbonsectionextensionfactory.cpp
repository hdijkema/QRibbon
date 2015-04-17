#include "qribbonsectionextensionfactory.h"
#include "qribbonsectioncontainerextension.h"
#include "qribbonsection.h"


QRibbonSectionExtensionFactory::QRibbonSectionExtensionFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *QRibbonSectionExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    QRibbonSection *widget = qobject_cast<QRibbonSection*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension))) {
        return new QRibbonSectionContainerExtension(widget, parent);
    } else {
        return 0;
    }
}
