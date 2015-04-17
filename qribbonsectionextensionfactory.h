#ifndef QRIBBONSECTIONEXTENSIONFACTORY_H
#define QRIBBONSECTIONEXTENSIONFACTORY_H


#include <QtDesigner/QExtensionFactory>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

class QRibbonSectionExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    QRibbonSectionExtensionFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif // QRIBBONSECTIONEXTENSIONFACTORY_H
