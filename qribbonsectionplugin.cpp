#include "qribbonsectionplugin.h"

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

#include "qribbonsection.h"
#include "qribbonsectionplugin.h"
#include "qribbonsectionextensionfactory.h"

#include <QtPlugin>


QRibbonSectionPlugin::QRibbonSectionPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}


void QRibbonSectionPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new QRibbonSectionExtensionFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}

bool QRibbonSectionPlugin::isInitialized() const
{
    return initialized;
}

QWidget *QRibbonSectionPlugin::createWidget(QWidget *parent)
{
    QWidget *widget = new QRibbonSection(parent);
    connect(widget, SIGNAL(textChanged(int, const QString &)), this, SLOT(textChanged(int, const QString &)));
    return widget;
}

QString QRibbonSectionPlugin::name() const
{
    return "QRibbonSection";
}

QString QRibbonSectionPlugin::group() const
{
    return "Buttons";
}

QIcon QRibbonSectionPlugin::icon() const
{
    return QIcon();
}

QString QRibbonSectionPlugin::toolTip() const
{
    return "The Ribbon toolbar section";
}

QString QRibbonSectionPlugin::whatsThis() const
{
    return "The QRibbon Plugin contains a Ribbon Toolbar a la Microsoft Offce 2013.";
}

bool QRibbonSectionPlugin::isContainer() const
{
    return true;
}

QString QRibbonSectionPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QRibbonSection\" name=\"section\">\n"
           "   <property name=\"toolTip\" >\n"
           "      <string>Ribbon section</string>\n"
           "   </property>\n"
           " </widget>\n"
           " <customwidgets>\n"
           "   <customwidget>\n"
           "      <class>QRibbonSection</class>\n"
           "      <extends>QWidget</extends>\n"
           "   </customwidget>\n"
           " </customwidgets>\n"
           "</ui>\n";
}


QString QRibbonSectionPlugin::includeFile() const
{
    return "qribbon.h";
}


void QRibbonSectionPlugin::titleChanged(const QString &title)
{
    Q_UNUSED(title);
    QRibbonSection *widget = qobject_cast<QRibbonSection*>(sender());
    if (widget) {
        widget->setTitle(title);
        QDesignerFormWindowInterface *form;
        form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form) {
            /*QDesignerFormEditorInterface *editor = form->core();
            QExtensionManager *manager = editor->extensionManager();
            QDesignerPropertySheetExtension *sheet;
            sheet = qt_extension<QDesignerPropertySheetExtension*>(manager, page);
            const int propertyIndex = sheet->indexOf(QLatin1String("sectionTitle"));
            sheet->setChanged(propertyIndex, true);*/
        }
    }
}
