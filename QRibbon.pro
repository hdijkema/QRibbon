QT       += widgets

CONFIG(app) {
    warning(App config)

    QT += core gui

    TEMPLATE = app
    DEFINES += QRIBBON_TEST

    HEADERS       = qribbon.h \
                    qribbon_global.h \
                    qribbontest.h \
                    qribbonsection.h \
                    qribbonbutton.h

    SOURCES       = main.cpp \
                    qribbon.cpp \
                    qribbonsection.cpp \
                    qribbonbutton.cpp \
                    qribbontest.cpp

    INCLUDEPATH += "C:\Program Files (x86)\Visual Leak Detector\include"
    LIBS += -L"C:\Program Files (x86)\Visual Leak Detector\lib\win32" -lvld

    TARGET = qribbontest

} else {
    warning(Lib config)

    CONFIG(installd) {
        TARGET = QRibbond
    } else {
        TARGET = QRibbon
    }

    TEMPLATE    = lib
    DEFINES += QRIBBON_LIBRARY

    HEADERS = \
        qribbon.h \
        qribbon_global.h \
        qribbonsection.h \
        qribbonbutton.h \

    SOURCES     = \
        qribbon.cpp \
        qribbonsection.cpp \
        qribbonbutton.cpp

    target.path = ../lib
    INSTALLS += target

    mylib.CONFIG = no_check_exists
    mylib.files = release/QRibbonPlugin.lib release/QRibbonPlugin.dll
    mylib.path = ../lib
    INSTALLS += mylib

    warning($$INSTALLS)

    mylibd.CONFIG = no_check_exists
    mylibd.files = debug/QRibbonPlugind.lib debug/QRibbonPlugind.dll
    mylibd.path = ../lib
    INSTALLS += mylibd


    DISTFILES +=
    OTHER_FILES +=

    header_files.files = $$HEADERS
    header_files.path = ../include
    INSTALLS += header_files

    warning($$INSTALLS)
}

RESOURCES += \
    qribbon.qrc

DISTFILES += \
    memorycheck.bat \
    LICENSE \
    README.md




