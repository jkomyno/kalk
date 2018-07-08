#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include "../model/matrixinfoenumerator.h"
#include "../model/kalkmatrixmodel.h"
#include "../model/kalkresultmatrixmodel.h"
#include "../model/resultdestination.h"
#include "transformwidget.h"
#include "kalkoperandboard.h"
#include "commonoperationswidget.h"
#include "operandinfodialog.h"
#include "kalkboardwidget.h"
#include "resultswidget.h"
#include "lib/linearalgebra/linear_algebra.h"

KalkBoardWidget::KalkBoardWidget(QWidget *parent) :
    QWidget(parent),
    outerLayout(new QVBoxLayout),
    boardsLayout(new QHBoxLayout),
    commonOperationsWidget(new CommonOperationsWidget),
    transformWidgetA(new TransformWidget),
    transformWidgetB(new TransformWidget),
    matrixInfoEnumerator(new MatrixInfoEnumerator),
    kalkResultMatrixModel(new KalkResultMatrixModel),
    resultsWidget(new ResultsWidget(*kalkResultMatrixModel)){}

void KalkBoardWidget::init(linear_algebra::i_matrix_t* boardAMatrix,
                           linear_algebra::i_matrix_t* boardBMatrix,
                           int minMatrixDimension,
                           int maxMatrixDimension,
                           int minRandomValue,
                           int maxRandomValue,
                           int minTransformValue,
                           int maxTransformValue)
{
    kalkOperandBoardA = new KalkOperandBoard(tr("Board A"),
                                             *boardAMatrix,
                                             minMatrixDimension,
                                             maxMatrixDimension,
                                             minRandomValue,
                                             maxRandomValue);
    kalkOperandBoardB = new KalkOperandBoard(tr("Board B"),
                                             *boardBMatrix,
                                             minMatrixDimension,
                                             maxMatrixDimension,
                                             minRandomValue,
                                             maxRandomValue);

    transformWidgetA->setMinTransformValue(minTransformValue);
    transformWidgetA->setMaxTransformValue(maxTransformValue);
    transformWidgetB->setMinTransformValue(minTransformValue);
    transformWidgetB->setMaxTransformValue(maxTransformValue);

    setupBoardA(kalkOperandBoardA);
    setupCommonOperations();
    setupBoardB(kalkOperandBoardB);
    outerLayout->addLayout(boardsLayout);
    setLayout(outerLayout);
    wire();
    emit onInit();
}

void KalkBoardWidget::reinit(linear_algebra::i_matrix_t* boardAMatrix, linear_algebra::i_matrix_t* boardBMatrix)
{
    kalkOperandBoardA->setMatrix(*boardAMatrix);
    kalkOperandBoardB->setMatrix(*boardBMatrix);
    kalkOperandBoardA->setDimensions(boardAMatrix->rows(), boardAMatrix->columns());
    kalkOperandBoardB->setDimensions(boardBMatrix->rows(), boardBMatrix->columns());
}

KalkMatrixModel& KalkBoardWidget::matrixModelA() const
{
    return kalkOperandBoardA->matrixModel();
}

KalkMatrixModel& KalkBoardWidget::matrixModelB() const
{
    return kalkOperandBoardB->matrixModel();
}

KalkResultMatrixModel& KalkBoardWidget::matrixModelResult() const
{
    return *kalkResultMatrixModel;
}

void KalkBoardWidget::toggleResultWindow(bool toggle)
{
    if (toggle) {
        resultsWidget->show();
    } else {
        resultsWidget->hide();
    }
}

RESULT_DESTINATION KalkBoardWidget::resultDestination() const
{
    return commonOperationsWidget->resultDestination();
}

void KalkBoardWidget::setupBoardA(KalkOperandBoard* kalkOperandBoardA)
{
    kalkOperandBoardA->addWidgetToBoardLayout(transformWidgetA);
    boardsLayout->addWidget(kalkOperandBoardA);
}

void KalkBoardWidget::setupBoardB(KalkOperandBoard* kalkOperandBoardB)
{
    kalkOperandBoardB->addWidgetToBoardLayout(transformWidgetB);
    boardsLayout->addWidget(kalkOperandBoardB);
}

void KalkBoardWidget::setupCommonOperations()
{
    boardsLayout->addWidget(commonOperationsWidget);
}

void KalkBoardWidget::wire()
{
    wireBoardA();
    wireCommonOperations();
    wireBoardB();
}

void KalkBoardWidget::wireBoardA()
{
    wireBoardAHeader();
    wireBoardATransform();
}

void KalkBoardWidget::wireBoardAHeader()
{
    connect(kalkOperandBoardA, SIGNAL(onChangeDimensionsClicked(int,int)), this, SIGNAL(onChangeDimensionsBoardAClicked(int,int)));
    connect(kalkOperandBoardA, SIGNAL(onInfoClicked()), this, SLOT(openDialogA()));
}

void KalkBoardWidget::wireBoardATransform()
{
    connect(transformWidgetA, SIGNAL(onTransposeClicked()), this, SIGNAL(onTransposeBoardAClicked()));
    connect(transformWidgetA, SIGNAL(onRandomClicked()), this, SIGNAL(onRandomBoardAClicked()));
    connect(transformWidgetA, SIGNAL(onSortClicked()), this, SIGNAL(onSortBoardAClicked()));
    connect(transformWidgetA, SIGNAL(onNegateClicked()), this, SIGNAL(onNegateBoardAClicked()));
    connect(transformWidgetA, SIGNAL(onIdentityClicked()), this, SIGNAL(onIdentityBoardAClicked()));

    connect(transformWidgetA, SIGNAL(onIncrementClicked(int)), this, SIGNAL(onIncrementBoardAClicked(int)));
    connect(transformWidgetA, SIGNAL(onScaleClicked(int)), this, SIGNAL(onScaleBoardAClicked(int)));
    connect(transformWidgetA, SIGNAL(onFillClicked(int)), this, SIGNAL(onFillBoardAClicked(int)));
    connect(transformWidgetA, SIGNAL(onFillDiagonalClicked(int)), this, SIGNAL(onFillDiagonalBoardAClicked(int)));
}

void KalkBoardWidget::wireCommonOperations()
{
    connect(commonOperationsWidget, SIGNAL(onAddOperationClicked()), this, SIGNAL(onAddOperationClicked()));
    connect(commonOperationsWidget, SIGNAL(onSubtractOperationClicked()), this, SIGNAL(onSubtractOperationClicked()));
    connect(commonOperationsWidget, SIGNAL(onMultiplyOperationClicked()), this, SIGNAL(onMultiplyOperationClicked()));
    connect(commonOperationsWidget, SIGNAL(onSwapOperationClicked()), this, SIGNAL(onSwapOperationClicked()));
}

void KalkBoardWidget::wireBoardB()
{
    wireBoardBHeader();
    wireBoardBTransform();
}

void KalkBoardWidget::wireBoardBHeader()
{
    connect(kalkOperandBoardB, SIGNAL(onChangeDimensionsClicked(int,int)), this, SIGNAL(onChangeDimensionsBoardBClicked(int,int)));
    connect(kalkOperandBoardB, SIGNAL(onInfoClicked()), this, SLOT(openDialogB()));
}

void KalkBoardWidget::wireBoardBTransform()
{
    connect(transformWidgetB, SIGNAL(onTransposeClicked()), this, SIGNAL(onTransposeBoardBClicked()));
    connect(transformWidgetB, SIGNAL(onRandomClicked()), this, SIGNAL(onRandomBoardBClicked()));
    connect(transformWidgetB, SIGNAL(onSortClicked()), this, SIGNAL(onSortBoardBClicked()));
    connect(transformWidgetB, SIGNAL(onNegateClicked()), this, SIGNAL(onNegateBoardBClicked()));
    connect(transformWidgetB, SIGNAL(onIdentityClicked()), this, SIGNAL(onIdentityBoardBClicked()));

    connect(transformWidgetB, SIGNAL(onIncrementClicked(int)), this, SIGNAL(onIncrementBoardBClicked(int)));
    connect(transformWidgetB, SIGNAL(onScaleClicked(int)), this, SIGNAL(onScaleBoardBClicked(int)));
    connect(transformWidgetB, SIGNAL(onFillClicked(int)), this, SIGNAL(onFillBoardBClicked(int)));
    connect(transformWidgetB, SIGNAL(onFillDiagonalClicked(int)), this, SIGNAL(onFillDiagonalBoardBClicked(int)));
}

void KalkBoardWidget::openDialogA()
{
    emit onInfoBoardAClicked();
    matrixInfoEnumerator->setMatrix(this->matrixModelA().matrix());
    OperandInfoDialog operandInfoDialog(*matrixInfoEnumerator, this);
    operandInfoDialog.exec();
}

void KalkBoardWidget::openDialogB()
{
    emit onInfoBoardBClicked();
    matrixInfoEnumerator->setMatrix(this->matrixModelB().matrix());
    OperandInfoDialog operandInfoDialog(*matrixInfoEnumerator, this);
    operandInfoDialog.exec();
}

void KalkBoardWidget::showErrorDialog(const QString& title, const QString& error)
{
    QMessageBox::critical(this, title, error);
}
