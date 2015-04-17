#ifndef QRIBBONSECTIONPLUGIN_H
#define QRIBBONSECTIONPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QRibbonSectionPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "QRibbonSection.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QRibbonSectionPlugin(QObject *parent = 0);

    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

public slots:
    void titleChanged(const QString &title);

private:
    bool initialized;
};

#endif // QRIBBONSECTIONPLUGIN_H
