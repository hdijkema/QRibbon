#ifndef QRIBBONCONTAINEREXTENSION
#define QRIBBONCONTAINEREXTENSION

#include <QtDesigner/QDesignerContainerExtension>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE
class QRibbon;

class QRibbonContainerExtension: public QObject,
                                 public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    QRibbonContainerExtension(QRibbon *widget, QObject *parent);

    void addWidget(QWidget *widget);
    int count() const;
    int currentIndex() const;
    void insertWidget(int index, QWidget *widget);
    void remove(int index);
    void setCurrentIndex(int index);
    QWidget *widget(int index) const;

private:
    QRibbon *_ribbon;
};


#endif // QRIBBONCONTAINEREXTENSION

