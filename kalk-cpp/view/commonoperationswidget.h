#ifndef COMMONOPERATIONSWIDGET_H
#define COMMONOPERATIONSWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QGroupBox;
class QPushButton;
class QButtonGroup;
enum class RESULT_DESTINATION;

class CommonOperationsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommonOperationsWidget(QWidget *parent = nullptr);

    RESULT_DESTINATION resultDestination() const;

signals:
    void onAddOperationClicked();
    void onSubtractOperationClicked();
    void onMultiplyOperationClicked();
    void onSwapOperationClicked();

private:
    QVBoxLayout* outerLayout;
    QGroupBox* commonOperationsGroupBox;
    QPushButton* addBtn;
    QPushButton* subtractBtn;
    QPushButton* multiplyBtn;
    QPushButton* swapBtn;
    QButtonGroup* exclusiveRadioButtonsGroup;

    void setup();
    void wire();
};

#endif // COMMONOPERATIONSWIDGET_H
