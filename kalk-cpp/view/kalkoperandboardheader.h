#ifndef KALKOPERANDBOARDHEADER_H
#define KALKOPERANDBOARDHEADER_H

#include <QWidget>

class QHBoxLayout;
class QGroupBox;
class QPushButton;
class QSpinBox;
class KalkOperandBoardHeader : public QWidget
{
    Q_OBJECT
public:
    KalkOperandBoardHeader(int minDimension, int maxDimension, int rows, int columns, QWidget *parent = nullptr);

signals:
    void onChangeDimensionsClicked(int rows, int columns);
    void onInfoClicked();

public slots:
    void setDimensions(int rows, int columns);
    void emitChangeDimensions();

private:
    QHBoxLayout* outerLayout;
    QGroupBox* dimensionsGroupBox;
    QGroupBox* infoGroupBox;
    QSpinBox* rowsSpinBox;
    QSpinBox* columnsSpinBox;
    QPushButton* changeDimensionsBtn;
    QPushButton* showInfoBtn;

    void setup();
    void setupDimensions();
    void setupInfo();
    void wire();
};

#endif // KALKOPERANDBOARDHEADER_H
