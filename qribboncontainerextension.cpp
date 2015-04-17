#include "qribboncontainerextension.h"
#include "qribbon.h"

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

QRibbonContainerExtension::QRibbonContainerExtension(QRibbon *widget, QObject *parent)
    :QObject(parent)
{
    _ribbon = widget;
}

void QRibbonContainerExtension::addWidget(QWidget *widget)
{
    _ribbon->addDesignerTab(widget);
}

int QRibbonContainerExtension::count() const
{
    return _ribbon->count();
}

int QRibbonContainerExtension::currentIndex() const
{
    return _ribbon->currentIndex();
}

void QRibbonContainerExtension::insertWidget(int index, QWidget *widget)
{
    _ribbon->insertDesignerTab(index, widget);
}

void QRibbonContainerExtension::remove(int index)
{
    _ribbon->removeTab(index);
}

void QRibbonContainerExtension::setCurrentIndex(int index)
{
    _ribbon->setCurrentIndex(index);
}

QWidget* QRibbonContainerExtension::widget(int index) const
{
    return _ribbon->tab(index);
}

