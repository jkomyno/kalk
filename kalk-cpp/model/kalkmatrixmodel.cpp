#include <QString>
#include "utils/debug.h"
#include "lib/linearalgebra/linear_algebra.h"
#include "kalkmatrixmodel.h"

KalkMatrixModel::KalkMatrixModel(linear_algebra::i_matrix_t* matrix,
                                 int minRandomValue,
                                 int maxRandomValue,
                                 QObject* parent) :
    QAbstractTableModel(parent),
    matrix_(matrix),
    random_(new linear_algebra::random_fun()),
    minRandomValue_(minRandomValue),
    maxRandomValue_(maxRandomValue) {}

KalkMatrixModel::~KalkMatrixModel()
{
    delete random_;
}

int KalkMatrixModel::rowCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(matrix_->rows());
}

int KalkMatrixModel::columnCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(matrix_->columns());
}

QVariant KalkMatrixModel::data(const QModelIndex& index, int role) const
{
    int row = index.row() + 1;
    int col = index.column() + 1;
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        auto value = matrix_->get_at(row, col);
        return QString::number(value);
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else if (role == Qt::ToolTipRole) {
        return QString("%1: (%2, %3)").arg(tr("Double click the matrix cell to edit the value at")).arg(row).arg(col);
    }

    return QVariant();
}

bool KalkMatrixModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row() + 1;
    int col = index.column() + 1;
    if (role == Qt::EditRole) {
        bool ok = true;
        auto newValue = value.toInt(&ok);
        if (ok) {
            matrix_->set_at(row, col, newValue);
        } else {
            return false;
        }
    }
    return true;
}

Qt::ItemFlags KalkMatrixModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

linear_algebra::i_matrix_t& KalkMatrixModel::matrix()
{
    return *matrix_;
}

void KalkMatrixModel::resetMatrix(linear_algebra::i_matrix_t& matrix)
{
    beginResetModel();
    delete matrix_;
    matrix_ = &matrix;
    endResetModel();
}

void KalkMatrixModel::add(KalkMatrixModel& other)
{
    beginResetModel();
    /**
     * In cases of virtual inheritance, the Swap Idiom is preferred
     * to the assignment operator.
     */
    auto& result = *(matrix_->add(&other.matrix()));
    matrix_->vswap(result);
    endResetModel();
}

void KalkMatrixModel::subtract(KalkMatrixModel& other)
{
    beginResetModel();
    /**
     * In cases of virtual inheritance, the Swap Idiom is preferred
     * to the assignment operator.
     */
    auto& result = *(matrix_->subtract(&other.matrix()));
    matrix_->vswap(result);
    endResetModel();
}

void KalkMatrixModel::multiply(KalkMatrixModel& other, bool preserveOrder)
{
    beginResetModel();
    printStats("Other", other.matrix());

    /**
     * In cases of virtual inheritance, the Swap Idiom is preferred
     * to the assignment operator.
     */
    auto& result = *(preserveOrder ?
                         matrix_->multiply(&other.matrix()) :
                         other.matrix().multiply(matrix_));
    printStats("Result", result);

    try {
        /**
         * a->vswap(b) requires that a and b have the same dynamic type,
         * otherwise std::bad_cast is implicitly thrown
         */
        matrix_->vswap(result);
    } catch (std::bad_cast&) {
        delete matrix_;
        matrix_ = &result;
    }

    printStats("matrix_", *matrix_);

    this->emitUpdateDimensions();
    endResetModel();
}

void KalkMatrixModel::reshape(int rows, int columns)
{
    // resets model only if it's necessary
    if (rows != static_cast<int>(matrix_->rows()) || columns != static_cast<int>(matrix_->columns())) {
        beginResetModel();
        auto result = matrix_->reshape(rows, columns);
        try {
            /**
             * a->vswap(b) requires that a and b have the same dynamic type,
             * otherwise std::bad_cast is implicitly thrown
             */
            matrix_->vswap(*result);
        } catch (std::bad_cast&) {
            delete matrix_;
            matrix_ = result;
        }

        matrix_->vswap(*(matrix_->reshape(rows, columns)));
        endResetModel();
    }
}

void KalkMatrixModel::transpose()
{
    beginResetModel();
    matrix_->transpose();
    if (dynamic_cast<linear_algebra::i_square_matrix_t*>(matrix_) == nullptr) {
        // if it enters here, it's not a square matrix, whose transposed matrix has the exact same
        // rows and columns
        this->emitUpdateDimensions();
    }
    endResetModel();
}

void KalkMatrixModel::random()
{
    beginResetModel();
    matrix_->random(this->minRandomValue_, this->maxRandomValue_, this->random_);
    endResetModel();
}

void KalkMatrixModel::sort()
{
    beginResetModel();
    matrix_->sort();
    endResetModel();
}

void KalkMatrixModel::negate()
{
    beginResetModel();
    matrix_->negate();
    endResetModel();
}

void KalkMatrixModel::identity()
{
    auto matrixAsDiagonal = dynamic_cast<linear_algebra::i_diagonal_matrix_t*>(matrix_);
    if (matrixAsDiagonal == nullptr) {
        throw linear_algebra::exceptions::bad_diagonal_matrix_cast();
    } else {
        beginResetModel();
        matrixAsDiagonal->to_identity();
        endResetModel();
    }
}

void KalkMatrixModel::increment(int increment)
{
    beginResetModel();
    matrix_->increment(increment);
    endResetModel();
}

void KalkMatrixModel::scale(int scale)
{
    beginResetModel();
    matrix_->scale(scale);
    endResetModel();
}

void KalkMatrixModel::fill(int fill)
{
    beginResetModel();
    matrix_->fill(fill);
    endResetModel();
}

void KalkMatrixModel::fillDiagonal(int fillDiagonal)
{
    auto matrixAsSquare = dynamic_cast<linear_algebra::i_square_matrix_t*>(matrix_);
    if (matrixAsSquare == nullptr) {
        throw linear_algebra::exceptions::bad_square_matrix_cast();
    } else {
        beginResetModel();
        matrixAsSquare->fill_diagonal(fillDiagonal);
        endResetModel();
    }
}

void KalkMatrixModel::swap(KalkMatrixModel& other)
{
    beginResetModel();
    other.beginResetModel();
    matrix_->vswap(*(other.matrix_));
    other.emitUpdateDimensions();
    other.endResetModel();
    this->emitUpdateDimensions();
    endResetModel();
}

void KalkMatrixModel::emitUpdateDimensions()
{
    emit updateDimensions(static_cast<int>(matrix_->rows()), static_cast<int>(matrix_->columns()));
}

void KalkMatrixModel::printStats(const QString& message, const linear_algebra::i_matrix_t& mat)
{
    utils::debug(QString("%1 stats:").arg(message), QString("%1 x %2, size: %3").arg(mat.rows()).arg(mat.columns()).arg(mat.size()));
}
