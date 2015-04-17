/****************************************************************************
**
**
****************************************************************************/

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include "qribbon.h"
#include "qribbonplugin.h"
#include "qribbonextensionfactory.h"

#include <QtPlugin>


QRibbonPlugin::QRibbonPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;

}


void QRibbonPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new QRibbonExtensionFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}

bool QRibbonPlugin::isInitialized() const
{
    return initialized;
}

QWidget *QRibbonPlugin::createWidget(QWidget *parent)
{
    QWidget *widget = new QRibbon(parent);
    connect(widget, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
    connect(widget, SIGNAL(tabTextChanged(int, const QString &)), this, SLOT(tabTextChanged(int, const QString &)));
    return widget;
}

QString QRibbonPlugin::name() const
{
    return "QRibbon";
}

QString QRibbonPlugin::group() const
{
    return "Buttons";
}

QIcon QRibbonPlugin::icon() const
{
    return QIcon();
}

QString QRibbonPlugin::toolTip() const
{
    return "The Ribbon toolbar";
}

QString QRibbonPlugin::whatsThis() const
{
    return "The QRibbon Plugin contains a Ribbon Toolbar a la Microsoft Offce 2013.";
}

bool QRibbonPlugin::isContainer() const
{
    return true;
}

QString QRibbonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QRibbon\" name=\"ribbon\">\n"
           "   <property name=\"toolTip\" >\n"
           "      <string>Ribbon toolbar container</string>\n"
           "   </property>\n"
           " </widget>\n"
           " <customwidgets>\n"
           "   <customwidget>\n"
           "      <class>QRibbon</class>\n"
           "      <extends>QTabWidget</extends>\n"
           "      <addpagemethod>addTab</addpagemethod>\n"
           "   </customwidget>\n"
           " </customwidgets>\n"
           "</ui>\n";
}

/*
 *            "   <widget class=\"QWidget\" name=\"start\" >\n"
           "     <widget class=\"QWidget\" name=\"buttons\" />\n"
           "   </widget>\n"
*/

QString QRibbonPlugin::includeFile() const
{
    return "qribbon.h";
}

void QRibbonPlugin::currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QRibbon *widget = qobject_cast<QRibbon*>(sender());
    if (widget) {
        QDesignerFormWindowInterface *form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form)
            form->emitSelectionChanged();
    }
}

void QRibbonPlugin::tabTextChanged(int index, const QString &title)
{
    Q_UNUSED(title);
    QRibbon *widget = qobject_cast<QRibbon*>(sender());
    if (widget) {
        QWidget *page = widget->widget(index);
        QDesignerFormWindowInterface *form;
        form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form) {
            QDesignerFormEditorInterface *editor = form->core();
            QExtensionManager *manager = editor->extensionManager();
            QDesignerPropertySheetExtension *sheet;
            sheet = qt_extension<QDesignerPropertySheetExtension*>(manager, page);
            const int propertyIndex = sheet->indexOf(QLatin1String("windowTitle"));
            sheet->setChanged(propertyIndex, true);
        }
    }
}
