#ifndef QRIBBONTEST_H
#define QRIBBONTEST_H

#include <QMainWindow>

class QRibbonTest : public QMainWindow
{
    Q_OBJECT

public slots:
    void action();
    void indexChanged(int tab);

public:
    QRibbonTest();
    ~QRibbonTest();
};

#endif // QRIBBONTEST_H
