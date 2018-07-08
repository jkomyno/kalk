#include <QString>
#include <iterator>
#include "lib/linearalgebra/linear_algebra.h"
#include "matrixinfoenumerator.h"

void MatrixInfoEnumerator::setMatrix(linear_algebra::i_matrix_t& mat)
{
    mat_ = &mat;
}

/**
 * @brief MatrixInfoEnumerator::enumerateInfos
 * This function should list every interesting property of a given matrix.
 * Its output depends by the matrix class instance passed to the constructor.
 * The tuple consists in the text to be displayed in a label, its tooltip content, and
 * the value to be shown.
 * @return
 */
std::tuple<QString, MatrixInfoEnumerator::traits_vector> MatrixInfoEnumerator::enumerateInfos() const
{
    {
        auto mat = dynamic_cast<linear_algebra::i_diagonal_matrix_t*>(mat_);
        if (mat != nullptr) {
            return std::make_tuple(tr("Diagonal matrix"), enumerateDiagonalMatrixInfos(mat));
        }
    }
    {
        auto mat = dynamic_cast<linear_algebra::i_square_matrix_t*>(mat_);
        if (mat != nullptr) {
            return std::make_tuple(tr("Square matrix"), enumerateSquareMatrixInfos(mat));
        }
    }
    return std::make_tuple(tr("Generic matrix"), enumerateMatrixInfos(mat_));
}

MatrixInfoEnumerator::traits_vector MatrixInfoEnumerator::enumerateMatrixInfos(linear_algebra::i_matrix_t* const mat)
{
    auto dataSize = mat->size();
    auto dataSizeTuple = std::make_tuple(
        tr("Data size"),
        tr("The number of entries in the storage"),
        QString("%1").arg(dataSize)
    );

    auto max = mat->max();
    auto maxTuple = std::make_tuple(
        tr("Maximum"),
        tr("The maximum value stored in the storage"),
        QString("%1").arg(max)
    );

    auto min = mat->min();
    auto minTuple = std::make_tuple(
        tr("Minimum"),
        tr("The minimum value stored in the storage"),
        QString("%1").arg(min)
    );

    auto sum = mat->sum();
    auto sumTuple = std::make_tuple(
        tr("Sum"),
        tr("The sum of every value stored in the storage"),
        QString("%1").arg(sum)
    );

    auto maxAbs = mat->max_abs();
    auto maxAbsTuple = std::make_tuple(
        tr("Maximum Absolute"),
        tr("The maximum absolute value stored in the storage"),
        QString("%1").arg(maxAbs)
    );

    auto minAbs = mat->min_abs();
    auto minAbsTuple = std::make_tuple(
        tr("Minimum Absolute"),
        tr("The minimum absolute value stored in the storage"),
        QString("%1").arg(minAbs)
    );

    auto sumAbs = mat->sum_abs();
    auto sumAbsTuple = std::make_tuple(
        tr("Sum Absolute"),
        tr("The absolute sum of every value stored in the storage"),
        QString("%1").arg(sumAbs)
    );

    auto normInfinity = mat->norm_infinity();
    auto normInfinityTuple = std::make_tuple(
        tr("Norm infinity"),
        tr("The absolute row sum of the matrix"),
        QString("%1").arg(normInfinity)
    );

    traits_vector tuplesVector = {
        dataSizeTuple,
        maxTuple,
        minTuple,
        sumTuple,
        maxAbsTuple,
        minAbsTuple,
        sumAbsTuple,
        normInfinityTuple
    };

    return tuplesVector;
}

MatrixInfoEnumerator::traits_vector MatrixInfoEnumerator::enumerateSquareMatrixInfos(linear_algebra::i_square_matrix_t* const mat)
{
    auto trace = mat->trace();
    auto traceTuple = std::make_tuple(
        tr("Trace"),
        tr("Defined as the sum of the elements on the main diagonal of a square matrix"),
        QString("%1").arg(trace)
    );

    auto determinant = mat->determinant();
    auto determinantTuple = std::make_tuple(
        tr("Determinant"),
        tr("The determinant of a square matrix"),
        QString("%1").arg(determinant)
    );

    traits_vector tuplesVector = {
        traceTuple,
        determinantTuple
    };

    traits_vector squareMatrixTuplesVector = enumerateMatrixInfos(mat);
    squareMatrixTuplesVector.insert(
                squareMatrixTuplesVector.end(),
                std::make_move_iterator(tuplesVector.begin()),
                std::make_move_iterator(tuplesVector.end())
    );

    return squareMatrixTuplesVector;
}

MatrixInfoEnumerator::traits_vector MatrixInfoEnumerator::enumerateDiagonalMatrixInfos(linear_algebra::i_diagonal_matrix_t* const mat)
{
    auto isIdentity = mat->is_identity();
    auto identityTuple = std::make_tuple(
        tr("Identity"),
        tr("A digaonal matrix is defined as identity if all the values on its main diagonal are equal to 1"),
        isIdentity ? tr("Yes") : tr("No")
    );

    auto diagonal = mat->diagonal();
    auto diagonalNormInfinity = diagonal->norm_infinity();
    auto diagonalNormInfinityTuple = std::make_tuple(
        tr("Diagonal norm infinity"),
        tr("It's the same as the maximum absolute value of the vector"),
        QString("%1").arg(diagonalNormInfinity)
    );

    traits_vector tuplesVector = {
        identityTuple,
        diagonalNormInfinityTuple
    };

    traits_vector diagonalMatrixTuplesVector = enumerateSquareMatrixInfos(mat);
    diagonalMatrixTuplesVector.insert(
                diagonalMatrixTuplesVector.end(),
                std::make_move_iterator(tuplesVector.begin()),
                std::make_move_iterator(tuplesVector.end())
    );

    delete diagonal;
    return diagonalMatrixTuplesVector;
}
