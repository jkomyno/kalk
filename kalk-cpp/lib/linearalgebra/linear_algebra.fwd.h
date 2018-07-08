#pragma once

namespace linear_algebra {
    template <typename T>
    class i_container;

    template <typename T>
    class i_vector;

    template <typename T>
    class i_matrix;

    template <typename T>
    class i_square_matrix;

    template <typename T>
    class i_diagonal_matrix;

    template <typename T>
    class abstract_dense_matrix;

    template <typename T>
    class dense_matrix;

    template <typename T>
    class dense_square_matrix;

    template <typename T>
    class dense_diagonal_matrix;

    template <typename T>
    class dense_vector;

    namespace detail {
        using value_type = int;
    }

    class random_fun;

    using i_vector_t = i_vector<detail::value_type>;
    using i_matrix_t = i_matrix<detail::value_type>;
    using i_square_matrix_t = i_square_matrix<detail::value_type>;
    using i_diagonal_matrix_t = i_diagonal_matrix<detail::value_type>;

    using dense_vector_t = dense_vector<detail::value_type>;
    using matrix_t = abstract_dense_matrix<detail::value_type>;
    using dense_matrix_t = dense_matrix<detail::value_type>;
    using dense_square_matrix_t = dense_square_matrix<detail::value_type>;
    using dense_diagonal_matrix_t = dense_diagonal_matrix<detail::value_type>;
}
