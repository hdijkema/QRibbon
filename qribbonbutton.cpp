#include "qribbonbutton.h"

#include <QAction>
#include <QEvent>

QRibbonButton::QRibbonButton(QWidget *parent) : QPushButton(parent)
{
    init(NULL);
}

QRibbonButton::QRibbonButton(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    init(NULL);
}

QRibbonButton::QRibbonButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    init(NULL);
}

QRibbonButton::QRibbonButton(const QIcon &icon, const QString &text, const QString &  name, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    init(&name);
}



static int button_number = 0;

void QRibbonButton::init(const QString *_name)
{
    setFlat(true);
    _action = NULL;

    button_number += 1;
    QString name;
    if (_name == NULL) { // small error here
        name = name.sprintf("%s_%04d", "qribbonbut", button_number);
        this->setObjectName(name);
    } else {
        name = *_name;
    }
    this->setStyleSheet("#" + name + ":hover { background: #d5e1f2;border: none; }");
}

void QRibbonButton::setAction(QAction *a) {
    _action = a;
}

QAction *QRibbonButton::getAction() {
    return _action;
}

bool QRibbonButton::event(QEvent *e)
{
    /*if(e->type() == QEvent::HoverEnter) {
       // setFlat(false);
    }

    if(e->type() == QEvent::HoverLeave) {
       // setFlat(true);
    }*/

    return QPushButton::event(e);
}

