#ifndef QRIBBONPLUGIN_H
#define QRIBBONPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QRibbonPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface" FILE "QRibbon.json")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QRibbonPlugin(QObject *parent = 0);

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

private slots:
    void currentIndexChanged(int index);
    void tabTextChanged(int index, const QString &title);

private:
    bool initialized;
};

#endif
