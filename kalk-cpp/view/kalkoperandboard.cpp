#include <QVBoxLayout>
#include <QGroupBox>
#include <QString>
#include "model/kalkmatrixmodel.h"
#include "kalkoperandboardheader.h"
#include "kalkoperandboard.h"
#include "lib/linearalgebra/linear_algebra.h"
#include "view/matrixtableview.h"

KalkOperandBoard::KalkOperandBoard(const QString& boardName,
                                   linear_algebra::i_matrix_t& matrix,
                                   int minDimension,
                                   int maxDimension,
                                   int minRandomValue,
                                   int maxRandomValue,
                                   QWidget* parent) :
    QWidget(parent),
    outerLayout(new QVBoxLayout),
    boardLayout(new QVBoxLayout),
    boardGroupBox(new QGroupBox(boardName)),
    matrixGroupBox(new QGroupBox(tr("Matrix"))),
    matrixModel_(new KalkMatrixModel(&matrix, minRandomValue, maxRandomValue)),
    matrixTableView(new MatrixTableView(matrixModel_)),
    kalkOperandBoardHeader(new KalkOperandBoardHeader(minDimension, maxDimension, static_cast<int>(matrix.rows()), static_cast<int>(matrix.columns())))
{
    setup();
    wire();
    setLayout(outerLayout);
}

KalkMatrixModel& KalkOperandBoard::matrixModel()
{
    return *matrixModel_;
}

void KalkOperandBoard::setMatrix(linear_algebra::i_matrix_t& matrix)
{
    matrixModel_->resetMatrix(matrix);
}

/**
 * @brief KalkOperandBoard::addWidgetToBoardLayout Calling this method will cause
 * widget's parent to be overridden by boardLayout, thus causing the widget's
 * destructor to be called boardALayout's lifecycle ends, due to it calling
 * deleteChildren(). But I'm ok with it, since KalkOperandBoard gets delete only when
 * the app gets closed. Otherwise, I'd have used a smart pointer like std::shared_ptr.
 * @param widget
 */
void KalkOperandBoard::addWidgetToBoardLayout(QWidget* widget)
{
    boardLayout->addWidget(widget);
}

void KalkOperandBoard::setDimensions(std::size_t rows, std::size_t cols)
{
    kalkOperandBoardHeader->setDimensions(static_cast<int>(rows), static_cast<int>(cols));
}

void KalkOperandBoard::setup()
{
    QVBoxLayout* matrixLayout = new QVBoxLayout;
    matrixLayout->addWidget(matrixTableView);
    matrixGroupBox->setLayout(matrixLayout);

    boardLayout->addWidget(kalkOperandBoardHeader);
    boardLayout->addWidget(matrixGroupBox);
    boardGroupBox->setLayout(boardLayout);
    outerLayout->addWidget(boardGroupBox);
}

void KalkOperandBoard::wire()
{
    connect(kalkOperandBoardHeader, SIGNAL(onChangeDimensionsClicked(int,int)), this, SIGNAL(onChangeDimensionsClicked(int,int)));
    connect(kalkOperandBoardHeader, SIGNAL(onInfoClicked()), this, SIGNAL(onInfoClicked()));
    connect(matrixModel_, SIGNAL(updateDimensions(int,int)), kalkOperandBoardHeader, SLOT(setDimensions(int,int)));
}
