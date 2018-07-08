#ifndef KALKRESULTMATRIXMODEL_H
#define KALKRESULTMATRIXMODEL_H

#include <QAbstractTableModel>
#include "lib/linearalgebra/linear_algebra.fwd.h"

class KalkMatrixModel;

class KalkResultMatrixModel : public QAbstractTableModel
{
public:
    explicit KalkResultMatrixModel(QObject* parent = nullptr);

    //These methods need to be reimplemented to make a editable model
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    ~KalkResultMatrixModel();

    void add(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB);
    void subtract(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB);
    void multiply(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB);

private:
    linear_algebra::i_matrix_t* matrix_ = nullptr;
};

#endif // KALKRESULTMATRIXMODEL_H
