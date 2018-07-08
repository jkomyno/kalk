#pragma once
#include "abstract_dense_matrix.h"

namespace linear_algebra {
    template <typename T>
    class dense_matrix : public abstract_dense_matrix<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using import_data = typename abstract_dense_matrix<T>::import_data;
        using iterator = typename abstract_dense_matrix<T>::iterator;
        using const_iterator = typename abstract_dense_matrix<T>::const_iterator;

        dense_matrix(size_type rows, size_type columns)
            : abstract_matrix<T, iterator, const_iterator>(rows, columns),
              // https://isocpp.org/wiki/faq/multiple-inheritance#virtual-inheritance-abcs
              abstract_dense_matrix<T>(rows, columns) { }

        dense_matrix(size_type rows, size_type columns, const import_data& data)
            : abstract_dense_matrix<T>(rows, columns, data) { }

        dense_matrix(const dense_matrix<T>& other) = default;
        dense_matrix(dense_matrix<T>&& other) noexcept = default;
        dense_matrix& operator=(const dense_matrix<T>& other) = default;
        virtual ~dense_matrix() = default;

        dense_matrix<T>* clone() const override;
        i_matrix<T>* factory(size_type new_rows, size_type new_columns) const override;
        void vswap(i_container<value_type>& other) override;
    };

    template <typename T>
    dense_matrix<T>* dense_matrix<T>::clone() const { return new dense_matrix<T>(*this); }

    template <typename T>
    i_matrix<T>* dense_matrix<T>::factory(size_type new_rows, size_type new_columns) const {
        return new dense_matrix<T>(new_rows, new_columns);
    }

    template <typename T>
    void dense_matrix<T>::vswap(i_container<value_type>& other) {
        this->swap(dynamic_cast<dense_matrix<value_type>&>(other));
    }

}
