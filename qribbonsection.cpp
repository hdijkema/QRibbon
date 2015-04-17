#include "qribbonbutton.h"
#include "qribbonsection.h"

#include <QVBoxLayout>
#include <QGridLayout>

QRibbonSection::QRibbonSection(QWidget *parent, const QString &_title, const QString &_name) : QWidget(parent)
{
    action = NULL;
    col = 0;
    row = 0;
    colBase = 0;
    _index = -1;

    if (&_name) { this->setObjectName(_name); }

    QHBoxLayout *slayout = new QHBoxLayout();
    slayout->setContentsMargins(2,0,2,0);
    slayout->setSpacing(2);
    this->setLayout(slayout);

    //QLabel *lab_line = new QLabel("X", this);
    QFrame *line = new QFrame(this);
    line->setFrameStyle(QFrame::VLine | QFrame::Plain);
    line->setFixedWidth(3);
    line->setContentsMargins(0,3,0,5);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString sheet = line->styleSheet();
    sheet.append("QFrame { color: #c0c0c0; }");
    line->setStyleSheet(sheet);

    QWidget *wvbox = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    wvbox->setLayout(layout);

    buttons = new QWidget(wvbox);
    QGridLayout *blayout = new QGridLayout();
    blayout->setContentsMargins(0,0,0,0);
    blayout->setSpacing(2);
    buttons->setLayout(blayout);

    QHBoxLayout *lfooter = new QHBoxLayout();
    lfooter->setContentsMargins(0,0,0,0);
    QWidget *footer = new QWidget(wvbox);
    footer->setLayout(lfooter);

    if (&title == 0) {
        title = new QLabel("", footer);
    } else {
        title = new QLabel(_title, footer);
    }
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(titleFont.pointSize()*0.98f);
    title->setFont(titleFont);

    {
        QIcon *dtl = new QIcon(":/icons/QRibbonDetails.svg");
        details = new QRibbonButton(*dtl, "", footer);
        delete dtl;
    }
    details->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QFont f;
    QFontMetrics metrics(f);
    QSize is = QSize(metrics.boundingRect("^").width(), metrics.boundingRect("X").height());
    is = QSize(is.width()*2, is.height());
    details->setIconSize(is);
    details->setMaximumSize(is);
    details->setVisible(false);
    QObject::connect(details, SIGNAL(clicked()), this, SLOT(activateDetails()));


    lfooter->addWidget(title, 1);
    lfooter->addWidget(details);

    layout->addWidget(buttons, 1);
    layout->addWidget(footer);

    slayout->addWidget(wvbox, 1);
    slayout->addWidget(line, 1);
}

QRibbonSection::~QRibbonSection()
{
}

void QRibbonSection::setDetailsAction(QAction *_action)
{
    action = _action;
    details->setVisible(action != NULL);
}

void QRibbonSection::activateDetails()
{
    if (action) {
        action->trigger();
    }
}

void QRibbonSection::activateAction()
{
    QAction *a;
    QRibbonButton *b = (QRibbonButton *) sender();
    if (b) {
        a = b->getAction();
        if (a) {
            a->trigger();
        }
    }
}

QWidget *QRibbonSection::widget(int index) {
    return _widgets[index];
}

int QRibbonSection::count() {
    return _widgets.size();
}

int QRibbonSection::currentIndex() {
    return _index;
}

void QRibbonSection::setCurrentIndex(int i) {
    _index = i;
}

void QRibbonSection::addAction(QAction * a, const QString &name)
{
    QGridLayout *l = (QGridLayout *) buttons->layout();
    QRibbonButton *btn = new QRibbonButton(a->icon(), a->text(), buttons);
    btn->setAction(a);
    connect(btn, SIGNAL(clicked()), this, SLOT(activateAction()));
    if (&name != 0) { btn->setObjectName(name); } else { btn->setObjectName(a->objectName()); }
    l->addWidget(btn, row, col, 1, 1);
    col += 1;
    _widgets.append(btn);
}

void QRibbonSection::addLargeAction(QAction * a, const QString &name)
{
    QGridLayout *l = (QGridLayout *) buttons->layout();
    QRibbonButton *btn = new QRibbonButton(a->icon(), a->text(), buttons);
    btn->setAction(a);
    connect(btn, SIGNAL(clicked()), this, SLOT(activateAction()));
    if (&name != 0) { btn->setObjectName(name); } else { btn->setObjectName(a->objectName()); }
    nextColumn();
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setIconSize(QSize(btn->iconSize().width() * 2, btn->iconSize().height() * 2));
    l->addWidget(btn, row, col, 2, 2);
    col += 2;
    _widgets.append(btn);
}

void QRibbonSection::addWidget(QWidget *w, const QString &name, int colspan)
{
    QGridLayout *l = (QGridLayout *) buttons->layout();
    if (&name != 0) { w->setObjectName(name); }
    l->addWidget(w, row, col, 1, colspan);
    col += colspan;
    _widgets.append(w);
}

void QRibbonSection::addLargeWidget(QWidget *w, const QString &name)
{
    QGridLayout *l = (QGridLayout *) buttons->layout();
    if (&name != 0) { w->setObjectName(name); }
    nextColumn();
    l->addWidget(w, row, col, 2, 2);
    col += 2;
    _widgets.append(w);
}

void QRibbonSection::nextColumn() {
    QGridLayout *l = (QGridLayout *) buttons->layout();
    colBase = l->columnCount();
    col = colBase;
    row = 0;
}

void QRibbonSection::nextRow() {
    row += 1;
    col = colBase;
}

void QRibbonSection::setTitle(const QString &_title)
{
    title->setText(_title);
}

