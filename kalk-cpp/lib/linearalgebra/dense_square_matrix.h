#pragma once
#include "abstract_dense_matrix.h"
#include "abstract_square_matrix.h"
#include "dense_matrix.h"

namespace linear_algebra {
    template <typename T>
    class dense_square_matrix : public abstract_dense_matrix<T>,
                                public abstract_square_matrix<
                                    T, typename abstract_dense_matrix<T>::iterator, typename abstract_dense_matrix<T>::
                                    const_iterator> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using import_data = typename abstract_dense_matrix<T>::import_data;
        using iterator = typename abstract_dense_matrix<T>::iterator;
        using const_iterator = typename abstract_dense_matrix<T>::const_iterator;
        using diagonal_iterator = typename abstract_square_matrix<T, iterator, const_iterator>::diagonal_iterator;
        using const_diagonal_iterator = typename abstract_square_matrix<T, iterator, const_iterator>::
        const_diagonal_iterator;

        explicit dense_square_matrix(size_type dimensions)
            : abstract_matrix<T, iterator, const_iterator>(dimensions, dimensions),
              abstract_dense_matrix<T>(dimensions, dimensions),
              abstract_square_matrix<T, iterator, const_iterator>(dimensions) {}

        explicit dense_square_matrix(size_type dimensions, const import_data& data)
            : abstract_dense_matrix<T>(dimensions, dimensions, data),
              abstract_square_matrix<T, iterator, const_iterator>(dimensions) {}

        explicit dense_square_matrix(size_type dimensions, import_data&& data) noexcept
            : abstract_dense_matrix<T>(dimensions, dimensions, data),
              abstract_square_matrix<T, iterator, const_iterator>(dimensions) {}

        dense_square_matrix(const dense_square_matrix<T>& other) = default;
        dense_square_matrix(dense_square_matrix<T>&& other) noexcept = default;
        dense_square_matrix& operator=(const dense_square_matrix<T>& other) = default;

        dense_square_matrix(const abstract_dense_matrix<T>& other) :
            abstract_matrix<value_type, iterator, const_iterator>(other),
            abstract_dense_matrix<T>(other),
            abstract_square_matrix<T, iterator, const_iterator>(other.rows()) {}

        dense_square_matrix(abstract_dense_matrix<T>&& other) :
            abstract_matrix<value_type, iterator, const_iterator>(other),
            abstract_dense_matrix<T>(other),
            abstract_square_matrix<T, iterator, const_iterator>(other.rows()) {}

        virtual ~dense_square_matrix() = default;

        dense_square_matrix<T>* clone() const override;
        i_matrix<T>* factory(size_type new_rows, size_type new_columns) const override;
        void vswap(i_container<value_type>& other) override;
    };

    template <typename T>
    dense_square_matrix<T>* dense_square_matrix<T>::clone() const { return new dense_square_matrix(*this); }

    template <typename T>
    i_matrix<T>* dense_square_matrix<T>::factory(size_type new_rows, size_type new_columns) const {
        if (new_rows == new_columns) { return new dense_square_matrix<T>(new_rows); }
        return new dense_matrix<T>(new_rows, new_columns);
    }

    template <typename T>
    void dense_square_matrix<T>::vswap(i_container<value_type>& other) {
        this->swap(dynamic_cast<dense_square_matrix<value_type>&>(other));
    }
}
