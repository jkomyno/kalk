#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QVariant>
#include <tuple>
#include "../model/matrixinfoenumerator.h"
#include "operandinfodialog.h"

OperandInfoDialog::OperandInfoDialog(MatrixInfoEnumerator& matrixInfoEnumerator, QWidget *parent) :
    QDialog(parent),
    outerLayout(new QVBoxLayout),
    infoListLayout(new QGridLayout),
    _matrixInfoEnumerator(matrixInfoEnumerator)
{
    setLayout(outerLayout);
    setup();
}

void OperandInfoDialog::setup()
{
    QString matrixName;
    std::vector<std::tuple<QString, QString, QString>> infoVector;
    std::tie(matrixName, infoVector)= _matrixInfoEnumerator.enumerateInfos();
    setWindowTitle(QString("%1: %2").arg("Info").arg(matrixName));

    infoListLayout->setHorizontalSpacing(40);
    QString labelText;
    QString tooltip;
    QString value;
    int row = 0;
    for (auto info : infoVector) {
        std::tie(labelText, tooltip, value) = info;
        labelText.append(":");
        QLabel* propertyLabel = new QLabel(labelText);
        propertyLabel->setProperty("class", "title-label");
        propertyLabel->setToolTip(tooltip);

        QLabel* valueField = new QLabel(value);

        infoListLayout->addWidget(propertyLabel, row, 0);
        infoListLayout->addWidget(valueField, row, 1);

        QFrame* line = new QFrame();
        line->setGeometry(infoListLayout->geometry());
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        infoListLayout->addWidget(line, row + 1, 0, 1, 2);
        row += 2;
    }

    QFrame* frame = new QFrame(this);
    frame->setStyleSheet("QLabel.title-label {"
                            "font-weight: bold;"
                            "color: #222;"
                         "}");
    frame->setLayout(infoListLayout);
    outerLayout->addWidget(frame);
}
