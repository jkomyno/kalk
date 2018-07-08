#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QAbstractButton>
#include <QString>
#include <QIntValidator>
#include "utils/layout/button.h"
#include "utils/layout/label.h"
#include "utils/layout/spinbox.h"
#include "inlineoperationrow.h"
#include "transformwidget.h"

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    outerLayout(new QVBoxLayout),
    transformGroupBox(new QGroupBox(tr("Transform"))),
    transposeBtn(utils::layout::newButtonWithText<QPushButton>(tr("Transpose"),
                                                               tr("Transposes the current matrix"))),
    randomBtn(utils::layout::newButtonWithText<QPushButton>(tr("Random"),
                                                            tr("Every element in the matrix assumes a random value"))),
    sortBtn(utils::layout::newButtonWithText<QPushButton>(tr("Sort"),
                                                          tr("Sorts the elements in the matrix in ascending order"))),
    negateBtn(utils::layout::newButtonWithText<QPushButton>(tr("Negate"),
                                                            tr("Inverts the sign of every element in the matrix"))),
    identityBtn(utils::layout::newButtonWithText<QPushButton>(tr("Identity"),
                                                              tr("Mutates the current diagonal matrix to an identity matrix, that is, a diagonal matrix with a sequence of 1 in the diagonal. It can only work with diagonal matrices"))),
    incrementBtn(utils::layout::newButtonWithText<QPushButton>(tr("Increment"),
                                                               tr("Adds the selected scalar value to every matrix element"))),
    scaleBtn(utils::layout::newButtonWithText<QPushButton>(tr("Scale"),
                                                           tr("Moltiplies every element in the matrix by the selected scalar value"))),
    fillBtn(utils::layout::newButtonWithText<QPushButton>(tr("Fill"),
                                                          tr("Every element in the container assumes the value of the selected scalar"))),
    fillDiagonalBtn(utils::layout::newButtonWithText<QPushButton>(tr("Fill diagonal"),
                                                                  tr("Every non-zero element in the current diagonal matrix assumes the value of the selected scalar. It can only work with diagonal matrices"))),
    incrementSpinBox(utils::layout::newSpinBox<QSpinBox>(0)),
    scaleSpinBox(utils::layout::newSpinBox<QSpinBox>(0)),
    fillSpinBox(utils::layout::newSpinBox<QSpinBox>(0)),
    fillDiagonalSpinBox(utils::layout::newSpinBox<QSpinBox>(0))
{
    setup();
    wire();
    setLayout(outerLayout);
}

void TransformWidget::setMinTransformValue(int minTransformValue)
{
    incrementSpinBox->setMinimum(minTransformValue);
    scaleSpinBox->setMinimum(minTransformValue);
    fillSpinBox->setMinimum(minTransformValue);
    fillDiagonalSpinBox->setMinimum(minTransformValue);
}

void TransformWidget::setMaxTransformValue(int maxTransformValue)
{
    incrementSpinBox->setMaximum(maxTransformValue);
    scaleSpinBox->setMaximum(maxTransformValue);
    fillSpinBox->setMaximum(maxTransformValue);
    fillDiagonalSpinBox->setMaximum(maxTransformValue);
}

void TransformWidget::emitIncrement()
{
    const int incrementValue = incrementSpinBox->value();
    emit onIncrementClicked(incrementValue);
}

void TransformWidget::emitScale()
{
    const int scaleValue = scaleSpinBox->value();
    emit onScaleClicked(scaleValue);
}

void TransformWidget::emitFill()
{
    const int fillValue = fillSpinBox->value();
    emit onFillClicked(fillValue);
}

void TransformWidget::emitFillDiagonal()
{
    const int fillDiagonalValue = fillDiagonalSpinBox->value();
    emit onFillDiagonalClicked(fillDiagonalValue);
}

void TransformWidget::setup()
{
    QVBoxLayout* btnsContainer = new QVBoxLayout;
    QHBoxLayout* btnRow = new QHBoxLayout;
    btnRow->addWidget(transposeBtn);
    btnRow->addWidget(randomBtn);
    btnRow->addWidget(sortBtn);
    btnRow->addWidget(negateBtn);
    btnRow->addWidget(identityBtn);

    auto incrementRow = new InlineOperationRow(tr("Increment by"), incrementSpinBox, incrementBtn);
    auto scaleRow = new InlineOperationRow(tr("Scale by"), scaleSpinBox, scaleBtn);
    auto fillRow = new InlineOperationRow(tr("Fill with"), fillSpinBox, fillBtn);
    auto fillDiagonalRow = new InlineOperationRow(tr("Fill diagonal with"), fillDiagonalSpinBox, fillDiagonalBtn);

    btnsContainer->addLayout(btnRow);
    btnsContainer->addWidget(incrementRow);
    btnsContainer->addWidget(scaleRow);
    btnsContainer->addWidget(fillRow);
    btnsContainer->addWidget(fillDiagonalRow);

    transformGroupBox->setLayout(btnsContainer);
    outerLayout->addWidget(transformGroupBox);
    outerLayout->setMargin(0);
}

void TransformWidget::wire()
{
    connect(transposeBtn, SIGNAL(clicked(bool)), this, SIGNAL(onTransposeClicked()));
    connect(randomBtn, SIGNAL(clicked(bool)), this, SIGNAL(onRandomClicked()));
    connect(sortBtn, SIGNAL(clicked(bool)), this, SIGNAL(onSortClicked()));
    connect(negateBtn, SIGNAL(clicked(bool)), this, SIGNAL(onNegateClicked()));
    connect(identityBtn, SIGNAL(clicked(bool)), this, SIGNAL(onIdentityClicked()));

    connect(incrementBtn, SIGNAL(clicked(bool)), this, SLOT(emitIncrement()));
    connect(scaleBtn, SIGNAL(clicked(bool)), this, SLOT(emitScale()));
    connect(fillBtn, SIGNAL(clicked(bool)), this, SLOT(emitFill()));
    connect(fillDiagonalBtn, SIGNAL(clicked(bool)), this, SLOT(emitFillDiagonal()));
}
