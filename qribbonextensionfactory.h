#ifndef QRIBBONEXTENSIONFACTORY
#define QRIBBONEXTENSIONFACTORY


#include <QtDesigner/QExtensionFactory>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE

class QRibbonExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    QRibbonExtensionFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};


#endif // QRIBBONEXTENSIONFACTORY

