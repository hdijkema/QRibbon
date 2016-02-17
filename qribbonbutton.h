#ifndef QRIBBONBUTTON_H
#define QRIBBONBUTTON_H

#include "qribbon_global.h"

#include <QPushButton>


class QRIBBON_EXPORT QRibbonButton : public QPushButton
{
private:
    void init(const QString *_name);

public:
    QRibbonButton(QWidget *parent);
    QRibbonButton(const QString & text, QWidget * parent = 0);
    QRibbonButton(const QIcon & icon, const QString & text, QWidget * parent = 0);
    QRibbonButton(const QIcon & icon, const QString & text, const QString & name, QWidget * parent = 0);

public:
    void setAction(QAction *a);
    QAction *getAction();

protected:
    bool event(QEvent *e);

private:
    QAction *_action;
};

#endif // QRIBBONBUTTON_H
