#pragma once
#include "i_square_matrix.h"
#include "i_vector.h"

namespace linear_algebra {

    template <typename T>
    class i_diagonal_matrix : virtual public i_square_matrix<T> {
    public:
        i_diagonal_matrix() = default;
        i_diagonal_matrix(const i_diagonal_matrix& other) = default;
        i_diagonal_matrix(i_diagonal_matrix&& other) noexcept = default;
        i_diagonal_matrix& operator=(const i_diagonal_matrix& other) = default;
        virtual ~i_diagonal_matrix() = default;

        /**
         * \brief Mutates the current diagonal matrix to an identity matrix, that is,
         * a diagonal matrix with a sequence of 1 in the diagonal
         */
        virtual void to_identity() = 0;

        /**
         * \brief Returns true if and only if the current diagonal matrix is an identity.
         */
        virtual bool is_identity() const = 0;

        virtual i_vector<T>* diagonal() const = 0;
    };

}
