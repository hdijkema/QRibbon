#include "qribbonbutton.h"

#include <QAction>
#include <QEvent>

QRibbonButton::QRibbonButton(QWidget *parent) : QPushButton(parent)
{
    setFlat(true);
    _action = NULL;
}

QRibbonButton::QRibbonButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    setFlat(true);
    _action = NULL;
}

QRibbonButton::QRibbonButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    setFlat(true);
    _action = NULL;
}

void QRibbonButton::setAction(QAction *a) {
    _action = a;
}

QAction *QRibbonButton::getAction() {
    return _action;
}

bool QRibbonButton::event(QEvent *e)
{
    if(e->type() == QEvent::HoverEnter) {
        setFlat(false);
    }

    if(e->type() == QEvent::HoverLeave) {
        setFlat(true);
    }

    return QPushButton::event(e);
}

