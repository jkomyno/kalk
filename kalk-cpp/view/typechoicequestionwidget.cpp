#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "typechoicewidget.h"
#include "utils/layout/button.h"
#include "utils/layout/label.h"
#include "typechoicequestionwidget.h"

TypeChoiceQuestionWidget::TypeChoiceQuestionWidget(QWidget *parent) :
    QWidget(parent),
    layout(new QVBoxLayout),
    choiceAWidget(new TypeChoiceWidget(tr("Board A"))),
    choiceBWidget(new TypeChoiceWidget(tr("Board B")))
{
    setup();
    wire();
    setLayout(layout);
}

void TypeChoiceQuestionWidget::setChoices(QAbstractListModel* choicesModel)
{
    choiceAWidget->setChoices(choicesModel);
    choiceBWidget->setChoices(choicesModel);
    insertBtn->setEnabled(true);
}

void TypeChoiceQuestionWidget::emitChoiceDone()
{
    int choiceAIndex = choiceAWidget->getChoice();
    int choiceBIndex = choiceBWidget->getChoice();

    if (this->insertedOnce) {
        emit onChangeChoiceDone(choiceAIndex, choiceBIndex);
    } else {
        insertBtn->setText(tr("Change and reset operand types"));
        this->insertedOnce = true;
        emit onFirstChoiceDone(choiceAIndex, choiceBIndex);
    }
}

void TypeChoiceQuestionWidget::setup()
{
    insertBtn = utils::layout::newButtonWithText<QPushButton>(tr("Insert operand types"));
    insertBtn->setEnabled(false);
    question = utils::layout::newLabel(tr("Which Kalk types do you want to operate with?"));

    QHBoxLayout* typeChoiceWidgetsWrapper = new QHBoxLayout;
    typeChoiceWidgetsWrapper->addWidget(choiceAWidget);
    typeChoiceWidgetsWrapper->addWidget(choiceBWidget);

    layout->addWidget(question);
    layout->addLayout(typeChoiceWidgetsWrapper);
    layout->addWidget(insertBtn);
}

void TypeChoiceQuestionWidget::wire()
{
    connect(insertBtn, SIGNAL(clicked(bool)), this, SLOT(emitChoiceDone()));
}
