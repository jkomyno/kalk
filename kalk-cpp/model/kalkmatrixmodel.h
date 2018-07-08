#ifndef KALKMATRIXMODEL_H
#define KALKMATRIXMODEL_H

#include <QAbstractTableModel>
#include "lib/linearalgebra/linear_algebra.fwd.h"

class QString;
class KalkMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit KalkMatrixModel(linear_algebra::i_matrix_t* matrix,
                             int minRandomValue,
                             int maxRandomValue,
                             QObject* parent = nullptr);
    ~KalkMatrixModel();

    //These methods need to be reimplemented to make a editable model
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    linear_algebra::i_matrix_t& matrix();
    void resetMatrix(linear_algebra::i_matrix_t& matrix);

    void add(KalkMatrixModel& other);
    void subtract(KalkMatrixModel& other);
    void multiply(KalkMatrixModel& other, bool preserveOrder = true);

    void reshape(int rows, int columns);

    void transpose();
    void random();
    void sort();
    void negate();
    void identity();

    void increment(int increment);
    void scale(int scale);
    void fill(int fill);
    void fillDiagonal(int fillDiagonal);

    void swap(KalkMatrixModel& other);

signals:
    void updateDimensions(int rows, int columns);

private:
    linear_algebra::i_matrix_t* matrix_;
    linear_algebra::random_fun* random_;
    int minRandomValue_;
    int maxRandomValue_;

    void emitUpdateDimensions();

    static void printStats(const QString& message, const linear_algebra::i_matrix_t& mat);
};

#endif // KALKMATRIXMODEL_H
