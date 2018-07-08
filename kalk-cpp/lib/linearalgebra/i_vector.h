#pragma once
#include "i_container.h"

namespace linear_algebra {
    template <typename T>
    class i_vector : virtual public i_container<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;

        i_vector() = default;
        i_vector(const i_vector& other) = default;
        i_vector(i_vector&& other) = default;
        i_vector& operator=(const i_vector& other) = default;

        /**
         * \brief Returns the length of the vector. This value may differ
         * from the result of size() in cases of sparse vectors
         * (which are not implemented in this project)
         */
        virtual size_type length() const = 0;

        /**
        * \brief Computes the ||A||_infinity norm.
        * If it's applied to a vector, it's the maximum absolute value of the vector.
        */
        value_type norm_infinity() const override { return this->max_abs(); }
    };
}
