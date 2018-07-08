#pragma once
#include <vector>
#include "utils/list_utils.h"
#include "abstract_matrix.h"
#include "dense_vector.h"

namespace linear_algebra {
    template <typename T>
    class abstract_dense_matrix : virtual public abstract_matrix<
            T, typename std::vector<T>::iterator, typename std::vector<T>::const_iterator> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using const_pointer = typename i_container<T>::const_pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using storage = std::vector<T>;
        using dense_iterator = typename std::vector<T>::iterator;
        using dense_const_iterator = typename std::vector<T>::const_iterator;
        using iterator = typename abstract_container<T, dense_iterator, dense_const_iterator>::iterator;
        using const_iterator = typename abstract_container<T, dense_iterator, dense_const_iterator>::const_iterator;
        using import_data = storage;

        explicit abstract_dense_matrix(size_type rows, size_type columns)
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(rows, columns),
              data_(utils::list_utils::init_list(rows * columns, T(0))) { }

        explicit abstract_dense_matrix(size_type rows, size_type columns, const import_data& data)
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(rows, columns),
              data_(utils::list_utils::copy_list(data)) { }

        explicit abstract_dense_matrix(size_type rows, size_type columns, import_data&& data) noexcept
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(rows, columns),
              data_(data) { }

        abstract_dense_matrix(const abstract_dense_matrix<T>& other)
            : i_container<value_type>(other),
              i_matrix<value_type>(other),
              abstract_matrix<value_type, dense_iterator, dense_const_iterator>(other),
              data_(utils::list_utils::copy_list(other.data_)) { }

        abstract_dense_matrix(abstract_dense_matrix<T>&& other) noexcept
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(std::move(other)),
              data_(std::move(other.data_)) {}

        abstract_dense_matrix(const abstract_dense_matrix<T>& other, size_type new_rows, size_type new_columns)
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(other, new_rows, new_columns),
              data_(utils::list_utils::init_list(new_rows * new_columns, T(0))) { }

        abstract_dense_matrix(abstract_dense_matrix<T>&& other, size_type new_rows, size_type new_columns) noexcept
            : abstract_matrix<T, dense_iterator, dense_const_iterator>(other, new_rows, new_columns),
              data_(utils::list_utils::init_list(new_rows * new_columns, T(0))) { }

        abstract_dense_matrix& operator=(const abstract_dense_matrix<T>& other) = default;
        virtual ~abstract_dense_matrix() = default;
        void swap(abstract_dense_matrix<value_type>& other) noexcept;

        size_type size() const override;
        void set_at(size_type index, const_reference value) override;
        value_type get_at(size_type index) const override;
        reference get_at(size_type index) override;
        iterator begin() override;
        iterator end() override;
        const_iterator begin() const override;
        const_iterator end() const override;
        void set_at(size_type row, size_type column, const_reference value) override;
        value_type get_at(size_type row, size_type column) const override;
        reference get_at(size_type row, size_type column) override;
        pointer data() override;
        const_pointer data() const override;
        i_matrix<value_type>* reshape(size_type rows, size_type columns) override;
        i_vector<value_type>* get_row_at(size_type row) const override;

    protected:
        std::vector<T> data_;

        size_type get_index(size_type row, size_type column) const {
            return this->get_index_from_one(row, column, this->columns());
        }
    };

    template <typename T>
    void abstract_dense_matrix<T>::swap(abstract_dense_matrix<value_type>& other) noexcept {
        abstract_matrix<value_type, dense_iterator, dense_const_iterator>::swap(other);
        this->data_.swap(other.data_);
    }

    template <typename T>
    typename abstract_dense_matrix<T>::size_type
    abstract_dense_matrix<T>::size() const { return data_.size(); }

    template <typename T>
    void abstract_dense_matrix<T>::set_at(size_type index, const_reference value) { data_.at(index) = value; }

    template <typename T>
    typename abstract_dense_matrix<T>::value_type
    abstract_dense_matrix<T>::get_at(size_type index) const { return data_.at(index); }

    template <typename T>
    typename abstract_dense_matrix<T>::reference
    abstract_dense_matrix<T>::get_at(size_type index) { return data_.at(index); }

    template <typename T>
    typename abstract_dense_matrix<T>::iterator abstract_dense_matrix<T>::begin() { return data_.begin(); }

    template <typename T>
    typename abstract_dense_matrix<T>::iterator abstract_dense_matrix<T>::end() { return data_.end(); }

    template <typename T>
    typename abstract_dense_matrix<T>::const_iterator abstract_dense_matrix<T>::begin() const { return data_.cbegin(); }

    template <typename T>
    typename abstract_dense_matrix<T>::const_iterator abstract_dense_matrix<T>::end() const { return data_.cend(); }

    template <typename T>
    void abstract_dense_matrix<T>::set_at(size_type row, size_type column, const_reference value) {
        const size_type linear_index = get_index(row, column);
        set_at(linear_index, value);
    }

    template <typename T>
    typename abstract_dense_matrix<T>::value_type
    abstract_dense_matrix<T>::get_at(size_type row, size_type column) const {
        const size_type linear_index = get_index(row, column);
        return get_at(linear_index);
    }

    template <typename T>
    typename abstract_dense_matrix<T>::reference abstract_dense_matrix<T>::get_at(size_type row, size_type column) {
        const size_type linear_index = get_index(row, column);
        return get_at(linear_index);
    }

    template <typename T>
    typename abstract_dense_matrix<T>::pointer abstract_dense_matrix<T>::data() { return this->data_.data(); }

    template <typename T>
    typename abstract_dense_matrix<T>::const_pointer abstract_dense_matrix<T>::data() const {
        return this->data_.data();
    }

    template <typename T>
    i_matrix<typename abstract_dense_matrix<T>::value_type>* abstract_dense_matrix<T>::reshape(size_type rows,
                                                                                               size_type columns) {
        auto dimension = rows * columns;
        auto pad_value = T(0);
        if (columns == this->columns()) {
            auto result = dynamic_cast<abstract_dense_matrix<T>*>(this->clone());
            result->set_rows(rows);
            result->data_.resize(dimension, pad_value);
            return result;
        }
        auto result = dynamic_cast<abstract_dense_matrix<value_type>*>(this->factory(rows, columns));
        T value_at;

        for (size_type i = 1; i <= rows; ++i) {
            for (size_type j = 1; j <= columns; ++j) {
                if (j > this->columns() || i > this->rows()) { value_at = pad_value; } else {
                    value_at = this->get_at(i, j);
                }
                result->set_at(i, j, value_at);
            }
        }

        return result;
    }

    template <typename T>
    i_vector<typename abstract_dense_matrix<T>::value_type>* abstract_dense_matrix<T>::get_row_at(size_type row) const {
        auto start = get_index(row, 1);
        auto end = get_index(row, this->columns());
        auto raw_data = utils::list_utils::slice(this->data_, start, end);
        return new dense_vector<value_type>(raw_data);
    }
}
