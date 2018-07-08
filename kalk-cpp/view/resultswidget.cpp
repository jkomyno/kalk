#include <QVBoxLayout>
#include <QAbstractTableModel>
#include "resultswidget.h"
#include "matrixtableview.h"

ResultsWidget::ResultsWidget(QAbstractTableModel& matrixModel, QWidget *parent) :
    QWidget(parent),
    outerLayout(new QVBoxLayout),
    matrixModel_(matrixModel),
    matrixTableView(new MatrixTableView(&matrixModel_, true)) {
    setup();
    setLayout(outerLayout);
}

void ResultsWidget::setup()
{
    setWindowTitle("Result");
    resize(800, 600);
    setWindowFlags(Qt::Window);

    outerLayout->addWidget(matrixTableView);
}

