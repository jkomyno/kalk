#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include "utils/layout/button.h"
#include "utils/layout/spinbox.h"
#include "kalkoperandboardheader.h"

KalkOperandBoardHeader::KalkOperandBoardHeader(int minDimension, int maxDimension, int rows, int columns, QWidget* parent) :
    QWidget(parent),
    outerLayout(new QHBoxLayout),
    dimensionsGroupBox(new QGroupBox(tr("Update dimensions"))),
    infoGroupBox(new QGroupBox(tr("Info"))),
    rowsSpinBox(utils::layout::newSpinBox<QSpinBox>(static_cast<int>(rows), minDimension, maxDimension,
                                          tr("Change the number of rows"))),
    columnsSpinBox(utils::layout::newSpinBox<QSpinBox>(static_cast<int>(columns), minDimension, maxDimension,
                                             tr("Change the number of columns"))),
    changeDimensionsBtn(utils::layout::newButtonWithText<QPushButton>(tr("Reshape"),
                                                                      tr("Reshapes the current matrix using the new dimensions set via the spinboxes to the left."))),
    showInfoBtn(utils::layout::newButtonWithText<QPushButton>(tr("Show details"),
                                                              tr("Displays additional infos, with an increasing amount of details based on the underlying dynamic type of the matrix")))
{
    setup();
    wire();
    setLayout(outerLayout);
}

void KalkOperandBoardHeader::setDimensions(int rows, int columns)
{
    rowsSpinBox->setValue(rows);
    columnsSpinBox->setValue(columns);
}

void KalkOperandBoardHeader::emitChangeDimensions()
{
    int rows = rowsSpinBox->value();
    int columns = columnsSpinBox->value();
    emit onChangeDimensionsClicked(rows, columns);
}

void KalkOperandBoardHeader::setup()
{
    setupDimensions();
    setupInfo();
    outerLayout->setMargin(0);
}

void KalkOperandBoardHeader::setupDimensions()
{
    QHBoxLayout* dimensionsRow = new QHBoxLayout;
    QLabel* dimensionsSeparatorLabel = new QLabel(" x ");
    dimensionsSeparatorLabel->setAlignment(Qt::AlignCenter);
    dimensionsRow->addWidget(rowsSpinBox);
    dimensionsRow->addWidget(dimensionsSeparatorLabel);
    dimensionsRow->addWidget(columnsSpinBox);
    dimensionsRow->addWidget(changeDimensionsBtn);

    dimensionsGroupBox->setLayout(dimensionsRow);
    outerLayout->addWidget(dimensionsGroupBox);
}

void KalkOperandBoardHeader::setupInfo()
{
    QHBoxLayout* infoRow = new QHBoxLayout;
    infoRow->addWidget(showInfoBtn);

    infoGroupBox->setLayout(infoRow);
    outerLayout->addWidget(infoGroupBox);
}

void KalkOperandBoardHeader::wire()
{
    connect(changeDimensionsBtn, SIGNAL(clicked(bool)), this, SLOT(emitChangeDimensions()));
    connect(showInfoBtn, SIGNAL(clicked(bool)), this, SIGNAL(onInfoClicked()));
}
