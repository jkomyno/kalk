#ifndef OPERANDINFODIALOG_H
#define OPERANDINFODIALOG_H

#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class MatrixInfoEnumerator;
class OperandInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OperandInfoDialog(MatrixInfoEnumerator& matrixInfoEnumerator, QWidget *parent = nullptr);

private:
    QVBoxLayout* outerLayout;
    QGridLayout* infoListLayout;

    MatrixInfoEnumerator& _matrixInfoEnumerator;

    void setup();
};

#endif // OPERANDINFODIALOG_H
