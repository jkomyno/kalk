#pragma once
#include <vector>
#include "utils/list_utils.h"
#include "abstract_vector.h"

namespace linear_algebra {
    template <typename T>
    class abstract_dense_vector : public abstract_vector<
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

        explicit abstract_dense_vector(size_type length)
            : abstract_vector<T, dense_iterator, dense_const_iterator>(length),
              data_(utils::list_utils::init_list(length, T(0))) { }

        explicit abstract_dense_vector(const import_data& data)
            : abstract_vector<T, dense_iterator, dense_const_iterator>(data.size()),
              data_(utils::list_utils::copy_list(data)) { }

        explicit abstract_dense_vector(import_data&& data) noexcept
            : abstract_vector<T, dense_iterator, dense_const_iterator>(data.size()),
              data_(data) { }

        abstract_dense_vector(const abstract_dense_vector<T>& other)
            : i_container<value_type>(other),
              abstract_vector<value_type, dense_iterator, dense_const_iterator>(other),
              data_(utils::list_utils::copy_list(other.data_)) { }

        abstract_dense_vector(abstract_dense_vector<T>&& other) noexcept
            : i_container<value_type>(other),
              abstract_vector<T, dense_iterator, dense_const_iterator>(std::move(other)),
              data_(std::move(other.data_)) { }

        abstract_dense_vector& operator=(const abstract_dense_vector<T>& other) = default;
        virtual ~abstract_dense_vector() = default;
        void swap(abstract_dense_vector<value_type>& other) noexcept;

        size_type size() const override;
        void set_at(size_type index, const_reference value) override;
        value_type get_at(size_type index) const override;
        reference get_at(size_type index) override;
        iterator begin() override;
        iterator end() override;
        const_iterator begin() const override;
        const_iterator end() const override;
        pointer data() override;
        const_pointer data() const override;

    protected:
        std::vector<T> data_;

        /**
         * \brief In linear algebra, every vector is indexed starting from 1, and
         * not from 0
         * \param index
         */
        static size_type get_index(size_type index) { return index + 1; }
    };

    template <typename T>
    void abstract_dense_vector<T>::swap(abstract_dense_vector<value_type>& other) noexcept {
        abstract_vector<value_type, dense_iterator, dense_const_iterator>::swap(other);
        this->data_.swap(other.data_);
    }

    template <typename T>
    typename abstract_dense_vector<T>::size_type abstract_dense_vector<T>::size() const { return data_.size(); }

    template <typename T>
    void abstract_dense_vector<T>::set_at(size_type index, const_reference value) {
        data_.at(this->get_index(index)) = value;
    }

    template <typename T>
    typename abstract_dense_vector<T>::value_type abstract_dense_vector<T>::get_at(size_type index) const {
        return data_.at(this->get_index(index));
    }

    template <typename T>
    typename abstract_dense_vector<T>::reference abstract_dense_vector<T>::get_at(size_type index) {
        return data_.at(this->get_index(index));
    }

    template <typename T>
    typename abstract_dense_vector<T>::iterator abstract_dense_vector<T>::begin() { return data_.begin(); }

    template <typename T>
    typename abstract_dense_vector<T>::iterator abstract_dense_vector<T>::end() { return data_.end(); }

    template <typename T>
    typename abstract_dense_vector<T>::const_iterator abstract_dense_vector<T>::begin() const { return data_.cbegin(); }

    template <typename T>
    typename abstract_dense_vector<T>::const_iterator abstract_dense_vector<T>::end() const { return data_.cend(); }

    template <typename T>
    typename abstract_dense_vector<T>::pointer abstract_dense_vector<T>::data() { return data_.data(); }

    template <typename T>
    typename abstract_dense_vector<T>::const_pointer abstract_dense_vector<T>::data() const { return data_.data(); }
}
