#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QSpinBox;
class QGroupBox;
class QAbstractButton;
class QString;
class TransformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformWidget(QWidget *parent = nullptr);

    void setMinTransformValue(int minTransformValue);
    void setMaxTransformValue(int maxTransformValue);

signals:
    void onTransposeClicked();
    void onRandomClicked();
    void onSortClicked();
    void onNegateClicked();
    void onIdentityClicked();

    void onIncrementClicked(int increment);
    void onScaleClicked(int scale);
    void onFillClicked(int fill);
    void onFillDiagonalClicked(int fillDiagonal);

public slots:
    void emitIncrement();
    void emitScale();
    void emitFill();
    void emitFillDiagonal();

private:
    QVBoxLayout* outerLayout;
    QGroupBox* transformGroupBox;

    QPushButton* transposeBtn;
    QPushButton* randomBtn;
    QPushButton* sortBtn;
    QPushButton* negateBtn;
    QPushButton* identityBtn;

    QPushButton* incrementBtn;
    QPushButton* scaleBtn;
    QPushButton* fillBtn;
    QPushButton* fillDiagonalBtn;

    QSpinBox* incrementSpinBox;
    QSpinBox* scaleSpinBox;
    QSpinBox* fillSpinBox;
    QSpinBox* fillDiagonalSpinBox;

    void setup();
    void wire();
};

#endif // TRANSFORMWIDGET_H
