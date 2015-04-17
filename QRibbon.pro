
CONFIG(app) {
    warning(App config)

    TEMPLATE = app
    QT += widgets designer

    CONFIG      += plugin

    HEADERS       = qribbon.h \
                    qribbontest.h \
                    qribbonsection.h \
                    qribbonbutton.h

    SOURCES       = main.cpp \
                    qribbon.cpp \
                    qribbonsection.cpp \
                    qribbonbutton.cpp \
                    qribbontest.cpp

    TARGET = qribbontest

} else {
    warning(Lib config)

    QT          += widgets designer

    QTDIR_build {
        # This is only for the Qt build. Do not use externally. We mean it.
        PLUGIN_TYPE = designer
        PLUGIN_CLASS_NAME = QRibbonPlugin
        load(qt_plugin)
    } else {
        # Library build
        warning(Library build)

        CONFIG      += plugin
        TEMPLATE    = lib

        TARGET = $$qtLibraryTarget($$TARGET)

        target.path = $$[QT_INSTALL_PLUGINS]/designer
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
    }

    HEADERS     = \
        qribbon.h \
        qribbontest.h
    SOURCES     = \
        qribbon.cpp \
        qribbontest.cpp \
        main.cpp

    HEADERS += \
        qribbonsection.h

    SOURCES += \
        qribbonsection.cpp

    HEADERS += \
        qribbonbutton.h

    SOURCES += \
        qribbonbutton.cpp

    DISTFILES +=
        OTHER_FILES +=

    header_files.files = $$HEADERS
    header_files.path = ../include
    INSTALLS += header_files

    warning($$INSTALLS)



}

RESOURCES += \
    qribbon.qrc



