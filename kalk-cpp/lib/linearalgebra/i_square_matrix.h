#pragma once
#include "i_matrix.h"

namespace linear_algebra {

    template <typename T>
    class i_square_matrix : virtual public i_matrix<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;

        i_square_matrix() = default;
        i_square_matrix(const i_square_matrix& other) = default;
        i_square_matrix(i_square_matrix&& other) noexcept = default;
        i_square_matrix& operator=(const i_square_matrix& other) = default;
        virtual ~i_square_matrix() = default;

        /**
         * \brief Returns the dimension of the square matrix, intended as the number of
         * rows or columns, which in a square matrix are the same
         */
        virtual size_type dimension() const = 0;

        /**
         * \brief Computes and returns the trace of the square matrix, which is defined by
         * the sum of the elements on the main diagonal
         */
        virtual value_type trace() const = 0;

        /**
         * \brief Computes and returns the determinant of the square matrix
         */
        virtual value_type determinant() const = 0;

        /**
         * \brief Mutates the current matrix setting scalar as the value for every item
         * in the matrix diagonal
         * \param scalar
         */
        virtual void fill_diagonal(const_reference scalar) = 0;
    };

}
