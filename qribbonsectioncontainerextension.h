#ifndef QRIBBONSECTIONCONTAINEREXTENSION_H
#define QRIBBONSECTIONCONTAINEREXTENSION_H

#include "qribbonsection.h"

#include <QtDesigner/QDesignerContainerExtension>

QT_BEGIN_NAMESPACE
class QExtensionManager;
QT_END_NAMESPACE
class QRibbon;

class QRibbonSectionContainerExtension:  public QObject,
                                         public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    QRibbonSectionContainerExtension(QRibbonSection *widget, QObject *parent);

    void addWidget(QWidget *widget);
    int count() const;
    int currentIndex() const;
    void insertWidget(int index, QWidget *widget);
    void remove(int index);
    void setCurrentIndex(int index);
    QWidget *widget(int index) const;

private:
    QRibbonSection *_section;
};


#endif // QRIBBONSECTIONCONTAINEREXTENSION_H
