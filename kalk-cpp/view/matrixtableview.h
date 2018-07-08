#ifndef MATRIXTABLEVIEW_H
#define MATRIXTABLEVIEW_H

#include <QTableView>

class QAbstractTableModel;

class MatrixTableView : public QTableView
{
    Q_OBJECT
public:
    MatrixTableView(QAbstractTableModel* model, bool hideHeaders = false, QWidget* parent = nullptr);

private:
    void setup();
};

#endif // MATRIXTABLEVIEW_H
