#include <QWidget>
#include <QStringListModel>
#include <QMessageBox>
#include "tabwidget.h"

TabWidget::TabWidget(QWidget* parent) :
    QTabWidget(parent),
    typeChoiceQuestionWidget(new TypeChoiceQuestionWidget),
    kalkBoardWidget(new KalkBoardWidget)
{}

TabWidget::~TabWidget()
{
    delete kalkBoardWidget;
    delete typeChoiceQuestionWidget;
}

TypeChoiceQuestionWidget* TabWidget::getTypeChoiceQuestionWidget() const
{
    return typeChoiceQuestionWidget;
}

KalkBoardWidget* TabWidget::getKalkBoardWidget() const
{
    return kalkBoardWidget;
}

void TabWidget::initKalkBoardWidget()
{
    addTab(kalkBoardWidget, tr("Kalk board"));
    setCurrentIndex(static_cast<int>(TAB_INDEXES::KALK_BOARD));
}

void TabWidget::onSettingsSuccess()
{
    setup();
}

void TabWidget::onSettingsError(const QString& message)
{
    QMessageBox::critical(this, tr("Settigs Error"), message);
}

void TabWidget::setup()
{
    addTab(typeChoiceQuestionWidget, tr("Type choice"));
    setCurrentIndex(static_cast<int>(TAB_INDEXES::TYPE_CHOICE));
}
