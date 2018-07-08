#include <QHBoxLayout>
#include <QString>
#include <QAbstractSpinBox>
#include <QAbstractButton>
#include <QLabel>
#include "inlineoperationrow.h"
#include "utils/layout/label.h"

InlineOperationRow::InlineOperationRow(const QString& labelText,
                                       QAbstractSpinBox* spinBox,
                                       QAbstractButton* btn,
                                       QWidget* parent) :
    QWidget(parent),
    rowLayout(new QHBoxLayout)
{
    setup(labelText, spinBox, btn);
    this->setLayout(rowLayout);
}

void InlineOperationRow::setup(const QString& labelText, QAbstractSpinBox* spinBox, QAbstractButton* btn)
{
    QLabel* label = utils::layout::newLabel(labelText + ":", spinBox);
    rowLayout->addWidget(label);
    rowLayout->addWidget(spinBox);
    rowLayout->addWidget(btn);
    rowLayout->setMargin(0);
}
