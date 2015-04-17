#include "qribbonsectioncontainerextension.h"
#include "qribbonsection.h"

#include <QMessageBox>

static void msg(int line, const QString & msg) {
    QMessageBox msgBox;
    QString s;
    s.append(QString::number(line));
    s.append(" ");
    s.append(msg);
    msgBox.setText(s);
    msgBox.exec();
}

static void msg(int line, const char *_msg) {
    QString s = _msg;
    msg(line, s);
}

#define SD msg(__LINE__, __FUNCTION__);

QRibbonSectionContainerExtension::QRibbonSectionContainerExtension(QRibbonSection *widget, QObject *parent)
    :QObject(parent)
{
    _section = widget;
}

void QRibbonSectionContainerExtension::addWidget(QWidget *widget)
{
    _section->addWidget(widget);
}

int QRibbonSectionContainerExtension::count() const
{
    return _section->count();
}

int QRibbonSectionContainerExtension::currentIndex() const
{
    return _section->currentIndex();
}

void QRibbonSectionContainerExtension::insertWidget(int index, QWidget *widget)
{
    //_section->addWidget(widget);
}

void QRibbonSectionContainerExtension::remove(int index)
{
    //_section->removeWidget(index);
}

void QRibbonSectionContainerExtension::setCurrentIndex(int index)
{
    //_section->setCurrentIndex(index);
}

QWidget* QRibbonSectionContainerExtension::widget(int index) const
{
    return _section->widget(index);
}



