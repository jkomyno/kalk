#ifndef KALKBOARDWIDGET_H
#define KALKBOARDWIDGET_H

#include <QWidget>
#include "lib/linearalgebra/linear_algebra.fwd.h"

class QVBoxLayout;
class QHBoxLayout;
class KalkOperandBoard;
class CommonOperationsWidget;
class TransformWidget;
class OperandInfoDialog;
class MatrixInfoEnumerator;
class KalkMatrixModel;
class KalkResultMatrixModel;
class ResultsWidget;
class QString;
enum class RESULT_DESTINATION;

class KalkBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KalkBoardWidget(QWidget *parent = nullptr);
    void init(linear_algebra::i_matrix_t* boardAMatrix,
              linear_algebra::i_matrix_t* boardBMatrix,
              int minMatrixDimension,
              int maxMatrixDimension,
              int minRandomValue,
              int maxRandomValue,
              int minTransformValue,
              int maxTransformValue);
    void reinit(linear_algebra::i_matrix_t* boardAMatrix, linear_algebra::i_matrix_t* boardBMatrix);

    KalkMatrixModel& matrixModelA() const;
    KalkMatrixModel& matrixModelB() const;
    KalkResultMatrixModel& matrixModelResult() const;

    void toggleResultWindow(bool toggle);
    RESULT_DESTINATION resultDestination() const;

signals:
    void onInit();

    /* Board A header signals */
    void onChangeDimensionsBoardAClicked(int rows, int columns);
    void onInfoBoardAClicked();

    /* Board A transform signals */
    void onTransposeBoardAClicked();
    void onRandomBoardAClicked();
    void onSortBoardAClicked();
    void onNegateBoardAClicked();
    void onIdentityBoardAClicked();

    void onIncrementBoardAClicked(int increment);
    void onScaleBoardAClicked(int scale);
    void onFillBoardAClicked(int fill);
    void onFillDiagonalBoardAClicked(int fillDiagonal);

    /* Board B header signals */
    void onChangeDimensionsBoardBClicked(int rows, int columns);
    void onInfoBoardBClicked();

    /* Board B transform signals */
    void onTransposeBoardBClicked();
    void onRandomBoardBClicked();
    void onSortBoardBClicked();
    void onNegateBoardBClicked();
    void onIdentityBoardBClicked();

    void onIncrementBoardBClicked(int increment);
    void onScaleBoardBClicked(int scale);
    void onFillBoardBClicked(int fill);
    void onFillDiagonalBoardBClicked(int fillDiagonal);

    /* Common operations signals */
    void onAddOperationClicked();
    void onSubtractOperationClicked();
    void onMultiplyOperationClicked();
    void onSwapOperationClicked();

public slots:
    void openDialogA();
    void openDialogB();
    void showErrorDialog(const QString& title, const QString& error);

private:
    QVBoxLayout* outerLayout;
    QHBoxLayout* boardsLayout;
    CommonOperationsWidget* commonOperationsWidget;
    TransformWidget* transformWidgetA;
    TransformWidget* transformWidgetB;
    MatrixInfoEnumerator* matrixInfoEnumerator;
    KalkOperandBoard* kalkOperandBoardA = nullptr;
    KalkOperandBoard* kalkOperandBoardB = nullptr;
    KalkResultMatrixModel* kalkResultMatrixModel;
    ResultsWidget* resultsWidget;

    void setupBoardA(KalkOperandBoard* kalkOperandBoardA);
    void setupBoardB(KalkOperandBoard* kalkOperandBoardB);
    void setupCommonOperations();
    void wire();
    void wireBoardA();
    void wireBoardAHeader();
    void wireBoardATransform();
    void wireBoardB();
    void wireBoardBHeader();
    void wireBoardBTransform();
    void wireCommonOperations();
};

#endif // KALKBOARDWIDGET_H
