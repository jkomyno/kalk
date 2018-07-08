#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QAbstractTableModel;
class QTableView;

class ResultsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsWidget(QAbstractTableModel& matrixModel, QWidget *parent = nullptr);

signals:

public slots:

private:
    void setup();

    QVBoxLayout* outerLayout;
    QAbstractTableModel& matrixModel_;
    QTableView* matrixTableView;
};

#endif // RESULTSWIDGET_H
