/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "qribbon.h"
#include "qribbonbutton.h"
#include "qribbonsection.h"

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTabBar>
#include <QStyle>
#include <QStyleOptionToolButton>
#include <QApplication>
#include <QMessageBox>

QRibbon::QRibbon(QWidget *parent) : QTabWidget(parent)
{
    hidden = false;
    popup = false;
    connect(this, SIGNAL(tabBarClicked(int)), this, SLOT(showRibbon(int)));

    QSizePolicy p = this->sizePolicy();
    p.setVerticalPolicy(QSizePolicy::Minimum);
    super::setSizePolicy(p);

    up = new QIcon(":/icons/RibbonUp.svg");
    point = new QIcon(":/icons/RibbonPoint.svg");

    {
        QString sheet = this->styleSheet();
        QWidget w;
        QColor c = w.palette().color(QPalette::Window);

        sheet.append("QTabWidget::pane { border: 1px solid #c0c0c0;top: -1px;background: "+c.name()+"; }");
        sheet.append("QTabBar::tab:!selected { border: 0px;margin: 0px;padding: 8px;background: none; }");
        sheet.append("QTabBar::tab:selected { background: " + c.name() + ";padding: 8px; }");
        sheet.append("QTabBar::tab { background: "+c.name()+"; border: 1px solid #c0c0c0; margin: 0px; padding: 8px; margin-bottom: -2px; border-bottom: 0px; }");
        sheet.append("QTabWidget::tab-bar { left: 3pt; }");
        QMessageBox box;
        box.setText(sheet);
        box.exec();
        this->setStyleSheet(sheet);
    }
}

QRibbon::~QRibbon()
{
    delete up;
    delete point;
}

QWidget *QRibbon::makeTab(QWidget *widget, int index)
{
    QWidget *tab = new QWidget();
    QPalette pal(tab->palette());
    pal.setColor(QPalette::Background, tab->palette().color(QPalette::Window));
    tab->setPalette(pal);
    tab->setAutoFillBackground(true);
    //tab->setStyleSheet("border: 1px solid black");

    // Our widget is layed out as a grid
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    tab->setLayout(layout);

    // It will contain a hide button
    QPushButton *hide = new QRibbonButton(*up, "", widget);
    hide->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QFont f;
    QFontMetrics metrics(f);
    QSize is = QSize(metrics.boundingRect("^").width()*2, metrics.boundingRect("^").height()*2);
    hide->setIconSize(is);
    is = QSize(is.width()*2, is.height());
    hide->setMaximumSize(is);
    //hide->setFlat(true);

    //QGridLayout *layout = (QGridLayout *) widget->layout();
    layout->addWidget(widget,0,0,1,1);
    layout->setAlignment(widget, Qt::AlignVertical_Mask | Qt::AlignLeft); //Qt::AlignHorizontal_Mask);
    layout->addWidget(hide,0,1,1,1);
    layout->setAlignment(hide, Qt::AlignRight | Qt::AlignBottom);

    if (index < 0) {
        pins.append(hide);
        widgets.append(widget);
    } else {
        pins.insert(index, hide);
        widgets.insert(index, widget);
    }

    QObject::connect(hide, SIGNAL(clicked()), this, SLOT(hideShow()));

    return tab;
}

int QRibbon::addTab(QWidget *widget, const QIcon &icon, const QString &label, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::addTab(makeTab(widget), icon, label);
}

int QRibbon::addTab(QWidget *widget, const QString &label, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::addTab(makeTab(widget), label);
}

int QRibbon::addTab(QWidget *widget, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::addTab(makeTab(widget), widget->objectName());
}

int QRibbon::addDesignerTab(QWidget *widget)
{
    return super::addTab(widget,widget->objectName());
}


int QRibbon::insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::insertTab(index, makeTab(widget), icon, label);
}

int QRibbon::insertTab(int index, QWidget *widget, const QString &label, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::insertTab(index, makeTab(widget), label);
}

int QRibbon::insertTab(int index, QWidget *widget, const QString &name)
{
    if (&name != 0) { widget->setObjectName(name); }
    return super::insertTab(index, makeTab(widget), widget->objectName());
}

int QRibbon::insertDesignerTab(int index, QWidget *widget)
{
    return super::insertTab(index, widget, widget->objectName());
}


QWidget *QRibbon::addRibbonTab(const QString & label, const QString & name)
{
    QWidget * widget = new QWidget();
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0,0,0,0);
    hbox->setSpacing(2);
    widget->setLayout(hbox);
    if (&name != 0) { widget->setObjectName(name); }
    this->addTab(widget, label, widget->objectName());
    return widget;
}

void QRibbon::setCurrentIndex(int index)
{
    super::setCurrentIndex(index);
    emit currentIndexChanged(index);
}

void QRibbon::setRibbonVisible(bool visible) {
    hidden = !visible;
    emit ribbonVisibilityChanged(visible);
}

QSize QRibbon::minimumSizeHint() const
{
    return (hidden) ? currentSize : super::minimumSizeHint();
}

QSize QRibbon::sizeHint() const
{
    return (hidden) ? currentSize : super::sizeHint();
}

void QRibbon::hideShow()
{
    if (!hidden) {
        prevSize = this->size();
        int i;
        for(i = 0; i < this->count(); i++) {
            QWidget *page = this->widget(i);
            page->setVisible(false);
            pins[i]->setIcon(*point);
        }
        QSize newSize(prevSize.width(), this->tabBar()->size().height());
        currentSize = newSize;
        this->updateGeometry();
        setRibbonVisible(false);
        popup = true;
    } else {
        int i;
        for(i = 0; i < this->count(); i++) {
            QWidget *page = this->widget(i);
            page->setVisible(true);
            pins[i]->setIcon(*up);
        }
        currentSize = prevSize;
        this->updateGeometry();
        setRibbonVisible(true);
        popup = false;
    }

}

void QRibbon::showRibbon(int page)
{
    if (hidden) {
        if (page == this->currentIndex() && popup) {
            popup = false;
            currentSize = prevSize;
            this->updateGeometry();
            int i;
            for(i = 0; i < this->count(); i++) {
                QWidget *page = this->widget(i);
                page->setVisible(true);
            }
        } else {
            int i;
            for(i = 0; i < this->count(); i++) {
                QWidget *page = this->widget(i);
                page->setVisible(false);
            }
            QSize newSize(prevSize.width(), this->tabBar()->size().height());
            currentSize = newSize;
            this->updateGeometry();
            popup = true;
        }
    }
    if (page != this->currentIndex()) {
        emit currentIndexChanged(page);
    }
}

QWidget *QRibbon::tab(int index) const
{
    return super::widget(index);
    //return widgets[index];
}

QRibbonSection *QRibbon::section(const QString & name) const
{
    int i;
    for(i = 0; i < widgets.size(); i++) {
        QWidget *widget = widgets[i];
        QObjectList list = widget->children();
        int j;
        for(j = 0; j < list.size(); j++) {
            QObject *w = list[j];
            if (_stricmp(w->metaObject()->className(),"QRibbonSection") == 0) {
                if (w->objectName() == name) {
                    return (QRibbonSection *) w;
                }
            }
        }
    }
    return NULL;
}

void QRibbon::addSection(const QString &tabName, QRibbonSection *section)
{
    int i;
    for(i = 0; i < widgets.size(); i++) {
        QWidget *w = widgets[i];
        if (w->objectName() == tabName) {
            QLayout *l = w->layout();
            if (!l) {
                QHBoxLayout *hb = new QHBoxLayout();
                hb->setContentsMargins(0,0,0,0);
                hb->setSpacing(2);
                w->setLayout(hb);
                l = w->layout();
            }
            l->addWidget(section);
            i = widgets.size() - 1;
        }
    }
}

QRibbonSection *QRibbon::section(int tabIndex, int sectionIndex) const
{
    QWidget *widget = (tabIndex >= 0 && tabIndex <widgets.size()) ? widgets[tabIndex] : NULL;
    if (widget) {
        QObjectList list = widget->children();
        QObject *w = (sectionIndex >= 0 && sectionIndex < list.size()) ? list[sectionIndex] : NULL;
        if (_stricmp(w->metaObject()->className(),"QRibbonSection") == 0) {
            return (QRibbonSection *) w;
        }
    }

    return NULL;
}

void QRibbon::setTabText(int index, const QString & txt) {
    super::setTabText(index, txt);
    emit tabTextChanged(index, txt);
}


