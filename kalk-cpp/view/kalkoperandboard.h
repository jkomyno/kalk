#ifndef KALKOPERANDBOARD_H
#define KALKOPERANDBOARD_H

#include <QWidget>
#include "lib/linearalgebra/linear_algebra.fwd.h"

class QVBoxLayout;
class QGroupBox;
class QTableView;
class QString;
class KalkOperandBoardHeader;
class KalkMatrixModel;
class KalkOperandBoard : public QWidget
{
    Q_OBJECT
public:
    explicit KalkOperandBoard(const QString& boardName,
                              linear_algebra::i_matrix_t& matrix,
                              int minDimension,
                              int maxDimension,
                              int minRandomValue,
                              int maxRandomValue,
                              QWidget *parent = nullptr);
    KalkMatrixModel& matrixModel();

    void setMatrix(linear_algebra::i_matrix_t& matrix);
    void addWidgetToBoardLayout(QWidget* widget);

signals:
    void onChangeDimensionsClicked(int rows, int columns);
    void onInfoClicked();

public slots:
    void setDimensions(std::size_t rows, std::size_t cols);

private:
    QVBoxLayout* outerLayout;
    QVBoxLayout* boardLayout;
    QGroupBox* boardGroupBox;
    QGroupBox* matrixGroupBox;
    KalkMatrixModel* matrixModel_;
    QTableView* matrixTableView;
    KalkOperandBoardHeader* kalkOperandBoardHeader;

    void setup();
    void wire();
};

#endif // KALKOPERANDBOARD_H
