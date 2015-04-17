#ifndef QRIBBONSECTION_H
#define QRIBBONSECTION_H

#include "qribbon_global.h"

#include <QAction>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class QRIBBON_EXPORT  QRibbonSection : public QWidget
{
    Q_OBJECT

public:
    QRibbonSection(QWidget *parent = 0, const QString &title = 0, const QString &name = 0);
    ~QRibbonSection();

private:
    QWidget *buttons;
    QLabel  *title;
    QPushButton *details;
    QAction *action;

    int row;
    int col;
    int colBase;

    QVector<QWidget *> _widgets;
    int _index;

public:
    void setDetailsAction(QAction * action);

public slots:
    void activateDetails();
    void activateAction();

public:
    void addAction(QAction * btn, const QString & name = 0);
    void addLargeAction(QAction * btn, const QString & name = 0);

    void addLargeWidget(QWidget *w, const QString &name);
    void addWidget(QWidget *w, const QString & name = 0, int colspan = 1);

    void nextRow();
    void nextColumn();

public:
    QWidget *widget(int index);
    int count();
    void setCurrentIndex(int index);
    int currentIndex();

public:
    void setTitle(const QString & title);
};

#endif // QRIBBONSECTION_H
