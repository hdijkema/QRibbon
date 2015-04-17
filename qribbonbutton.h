#ifndef QRIBBONBUTTON_H
#define QRIBBONBUTTON_H

#include <QPushButton>


class QRibbonButton : public QPushButton
{
public:
    QRibbonButton(QWidget *parent);
    QRibbonButton(const QString & text, QWidget * parent = 0);
    QRibbonButton(const QIcon & icon, const QString & text, QWidget * parent = 0);

public:
    void setAction(QAction *a);
    QAction *getAction();

protected:
    bool event(QEvent *e);

private:
    QAction *_action;
};

#endif // QRIBBONBUTTON_H
