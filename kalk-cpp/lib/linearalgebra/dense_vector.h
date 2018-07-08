#pragma once
#include "abstract_dense_vector.h"

namespace linear_algebra {
    template <typename T>
    class dense_vector : public abstract_dense_vector<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using const_pointer = typename i_container<T>::const_pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using storage = std::vector<T>;
        using dense_iterator = typename abstract_dense_vector<T>::iterator;
        using dense_const_iterator = typename abstract_dense_vector<T>::const_iterator;
        using iterator = typename abstract_dense_vector<T>::iterator;
        using const_iterator = typename abstract_dense_vector<T>::const_iterator;
        using import_data = storage;

        explicit dense_vector(size_type length)
            : abstract_dense_vector<T>(length) {}

        explicit dense_vector(const import_data& data)
            : abstract_dense_vector<T>(data) {}

        explicit dense_vector(import_data&& data)
            : abstract_dense_vector<T>(data) {}

        explicit dense_vector(const abstract_dense_vector<T>& other)
            : abstract_dense_vector<T>(other) {}

        explicit dense_vector(abstract_dense_vector<T>&& other)
            : abstract_dense_vector<T>(other) {}

        dense_vector<T>* clone() const override;
        void vswap(i_container<value_type>& other) override;
    };

    template <typename T>
    dense_vector<T>* dense_vector<T>::clone() const { return new dense_vector<T>(*this); }

    template <typename T>
    void dense_vector<T>::vswap(i_container<value_type>& other) {
        this->swap(dynamic_cast<abstract_dense_vector<value_type>&>(other));
    }
}
