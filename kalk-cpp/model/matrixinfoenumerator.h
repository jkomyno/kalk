#ifndef MATRIXINFOENUMERATOR_H
#define MATRIXINFOENUMERATOR_H

#include <QObject>
#include <vector>
#include <tuple>
#include "lib/linearalgebra/linear_algebra.fwd.h"
#include "utils/debug.h"

class QString;
class MatrixInfoEnumerator : public QObject
{
    Q_OBJECT
    using traits_vector = std::vector<std::tuple<QString, QString, QString>>;
public:
    MatrixInfoEnumerator() : QObject(nullptr), mat_(nullptr) {}
    void setMatrix(linear_algebra::i_matrix_t& mat);

    // labelText, tooltip, value
    std::tuple<QString, traits_vector> enumerateInfos() const;

private:
    static traits_vector enumerateMatrixInfos(linear_algebra::i_matrix_t* const mat);
    static traits_vector enumerateSquareMatrixInfos(linear_algebra::i_square_matrix_t* const mat);
    static traits_vector enumerateDiagonalMatrixInfos(linear_algebra::i_diagonal_matrix_t* const mat);

    /*
    static std::vector<std::tuple<QString, QString, QString>> enumerateContainerInfos();
    static std::vector<std::tuple<QString, QString, QString>> enumerateMatrixInfos();
    static std::vector<std::tuple<QString, QString, QString>> enumerateSquareMatrixInfos();
    static std::vector<std::tuple<QString, QString, QString>> enumerateDiagonalMatrixInfos();
    */

    linear_algebra::i_matrix_t* mat_;
};

#endif // MATRIXINFOENUMERATOR_H
