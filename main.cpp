//#include <vld.h>
#include <QApplication>

#include "qribbontest.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("QtProject");
    app.setApplicationName("Application Example");
    QRibbonTest mainWin;
    mainWin.show();
    return app.exec();
}
