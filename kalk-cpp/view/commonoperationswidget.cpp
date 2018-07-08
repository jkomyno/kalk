#include <QButtonGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include "model/resultdestination.h"
#include "utils/layout/button.h"
#include "commonoperationswidget.h"

CommonOperationsWidget::CommonOperationsWidget(QWidget *parent) :
    QWidget(parent),
    outerLayout(new QVBoxLayout),
    commonOperationsGroupBox(new QGroupBox(tr("Common operations"))),
    exclusiveRadioButtonsGroup(new QButtonGroup(this))
{
    setup();
    wire();
    setLayout(outerLayout);
}

RESULT_DESTINATION CommonOperationsWidget::resultDestination() const
{
    auto result = static_cast<RESULT_DESTINATION>(exclusiveRadioButtonsGroup->checkedId());
    return result;
}

void CommonOperationsWidget::setup()
{
    QVBoxLayout* commonOperationsLayout = new QVBoxLayout();

    addBtn = utils::layout::newButtonWithText<QPushButton>("A + B", tr("Performs A + B, A and B must have the same dimensions"));
    subtractBtn = utils::layout::newButtonWithText<QPushButton>("A - B", tr("Performs A - B, A and B must have the same dimensions"));
    multiplyBtn = utils::layout::newButtonWithText<QPushButton>("A * B", tr("Performs A * B, A's columns number must be the same as B's rows'"));
    swapBtn = utils::layout::newButtonWithText<QPushButton>("A <-> B", tr("Swaps the matrix A with the matrix B"));

    addBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    subtractBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    multiplyBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    swapBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    commonOperationsLayout->addWidget(addBtn);
    commonOperationsLayout->addWidget(subtractBtn);
    commonOperationsLayout->addWidget(multiplyBtn);
    commonOperationsLayout->addWidget(swapBtn);

    auto resultToARadioButton = utils::layout::newButtonWithText<QRadioButton>(tr("Redirect to A"),
                                                                               tr("Assigns the result of every next common operation to the matrix in the A Board"));
    auto resultToBRadioButton = utils::layout::newButtonWithText<QRadioButton>(tr("Redirect to B"),
                                                                               tr("Assigns the result of every next common operation to the matrix in the B Board"));
    auto resultToWindowRadioButton = utils::layout::newButtonWithText<QRadioButton>(tr("Redirect to new window"),
                                                                                    tr("Displays the result of every next common operation in a new window"));
    resultToWindowRadioButton->setChecked(true);

    exclusiveRadioButtonsGroup->addButton(resultToARadioButton, static_cast<int>(RESULT_DESTINATION::TO_A));
    exclusiveRadioButtonsGroup->addButton(resultToBRadioButton, static_cast<int>(RESULT_DESTINATION::TO_B));
    exclusiveRadioButtonsGroup->addButton(resultToWindowRadioButton, static_cast<int>(RESULT_DESTINATION::TO_WINDOW));

    QVBoxLayout* exclusiveRadioButtonsLayout = new QVBoxLayout;
    exclusiveRadioButtonsLayout->addWidget(resultToARadioButton);
    exclusiveRadioButtonsLayout->addWidget(resultToBRadioButton);
    exclusiveRadioButtonsLayout->addWidget(resultToWindowRadioButton);

    commonOperationsLayout->addLayout(exclusiveRadioButtonsLayout);
    commonOperationsLayout->setAlignment(exclusiveRadioButtonsLayout, Qt::AlignHCenter);
    commonOperationsGroupBox->setLayout(commonOperationsLayout);

    outerLayout->addWidget(commonOperationsGroupBox);
}

void CommonOperationsWidget::wire()
{
    connect(addBtn, SIGNAL(clicked(bool)), this, SIGNAL(onAddOperationClicked()));
    connect(subtractBtn, SIGNAL(clicked(bool)), this, SIGNAL(onSubtractOperationClicked()));
    connect(multiplyBtn, SIGNAL(clicked(bool)), this, SIGNAL(onMultiplyOperationClicked()));
    connect(swapBtn, SIGNAL(clicked(bool)), this, SIGNAL(onSwapOperationClicked()));
}
