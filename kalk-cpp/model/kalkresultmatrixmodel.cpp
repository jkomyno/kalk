#include "lib/linearalgebra/linear_algebra.h"
#include "model/kalkmatrixmodel.h"
#include "kalkresultmatrixmodel.h"

KalkResultMatrixModel::KalkResultMatrixModel(QObject* parent) :
    QAbstractTableModel(parent) {}

int KalkResultMatrixModel::rowCount(const QModelIndex& /*parent*/) const
{
    return matrix_ == nullptr ? 0 : static_cast<int>(matrix_->rows());
}

int KalkResultMatrixModel::columnCount(const QModelIndex& /*parent*/) const
{
    return matrix_ == nullptr ? 0 : static_cast<int>(matrix_->columns());
}

QVariant KalkResultMatrixModel::data(const QModelIndex& index, int role) const
{
    int row = index.row() + 1;
    int col = index.column() + 1;
    if (role == Qt::DisplayRole && matrix_ != nullptr) {
        auto value = matrix_->get_at(row, col);
        return QString::number(value);
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
}

Qt::ItemFlags KalkResultMatrixModel::flags(const QModelIndex& index) const
{
    return QAbstractItemModel::flags(index);
}

KalkResultMatrixModel::~KalkResultMatrixModel()
{
    delete matrix_;
}

void KalkResultMatrixModel::add(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB)
{
    beginResetModel();
    matrix_ = matrixModelA.matrix().add(&matrixModelB.matrix());
    endResetModel();
}

void KalkResultMatrixModel::subtract(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB)
{
    beginResetModel();
    matrix_ = matrixModelA.matrix().subtract(&matrixModelB.matrix());
    endResetModel();
}

void KalkResultMatrixModel::multiply(KalkMatrixModel& matrixModelA, KalkMatrixModel& matrixModelB)
{
    beginResetModel();
    matrix_ = matrixModelA.matrix().multiply(&matrixModelB.matrix());
    endResetModel();
}
