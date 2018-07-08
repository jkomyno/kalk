#pragma once

namespace linear_algebra {

    template <typename T>
    class abstract_random_function {
    public:
        abstract_random_function() = default;
        abstract_random_function(const abstract_random_function& other) = delete;
        abstract_random_function(abstract_random_function&& other) noexcept = delete;
        abstract_random_function& operator=(const abstract_random_function& other) = delete;
        abstract_random_function& operator=(abstract_random_function&& other) noexcept = delete;
        virtual ~abstract_random_function() = default;
        virtual T operator()(const T& min, const T& max) const = 0;
    };

    template <typename T>
    class i_container {
    public:
        using size_type = std::size_t;
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        i_container() = default;
        i_container(const i_container& other) = default;
        i_container(i_container&& other) noexcept = default;
        i_container& operator=(const i_container& other) = default;
        virtual ~i_container() = default;

        virtual i_container* clone() const = 0;

        /**
         * \brief Swaps object polymorphically. It requires the dynamic type to be the same, otherwise
         * it throws the std::bad_cast exception.
         * Inspired by https://stackoverflow.com/questions/12314820/what-is-the-proper-approach-to-swap-and-copy-idiom-in-virtual-inheritance
         * \param other 
         */
        virtual void vswap(i_container<value_type>& other) = 0;

        /**
         * \brief Returns the number of entries in the storage
         */
        virtual size_type size() const = 0;

        /**
         * \brief Sets value of the current container at a specific index
         * \param index 
         * \param value 
         */
        virtual void set_at(size_type index, const_reference value) = 0;

        /**
         * \brief Returns the value of the current container at a specific index
         * \param index
         */
        virtual value_type get_at(size_type index) const = 0;

        /**
         * \brief Returns a reference of the current container at a specific index
         * \param index
         */
        virtual reference get_at(size_type index) = 0;

        /**
         * \brief Returns a pointer to the underlying container serving as element storage
         */
        virtual pointer data() = 0;

        /**
        * \brief Returns a pointer to the underlying container serving as element storage
        */
        virtual const_pointer data() const = 0;

        /**
         * \brief Moltiplies every element in the container by a scalar value
         * \param scalar 
         */
        virtual void scale(const_reference scalar) = 0;

        /**
         * \brief Adds the values of scalar to every element in the container
         * \param scalar 
         */
        virtual void increment(const_reference scalar) = 0;

        /**
         * \brief Every element in the container assumes the value of scalar
         * \param scalar 
         */
        virtual void fill(const_reference scalar) = 0;

        /**
         * \brief Zero-fills every element in the container
         */
        virtual void zero() = 0;

        /**
         * \brief Inverts the sign of every element in the container
         */
        virtual void negate() = 0;

        /**
         * \brief Sorts the elements in ascending order
         */
        virtual void sort() = 0;

        /**
         * \brief very element in the container assumes a random value between min and max
         * \param min 
         * \param max 
         * \param random_functor 
         */
        virtual void random(const_reference min, const_reference max,
                            abstract_random_function<value_type>* random_functor) = 0;

        /**
        * \brief Computes the ||A||_infinity norm.
        * If it's applied to a matrix, it's the maximum absolute row sum of the matrix.
        * If it's applied to a vector, it's the maximum absolute value of that vector.
        */
        virtual value_type norm_infinity() const = 0;

        /**
         * \brief Returns the maximum value stored in the storage
         */
        virtual value_type max() const = 0;

        /**
         * \brief Returns the minimum value stored in the storage
         */
        virtual value_type min() const = 0;

        /**
         * \brief Returns the sum of every value stored in the storage 
         */
        virtual value_type sum() const = 0;

        /**
         * \brief Returns the maximum absolute value stored in the storage
         */
        virtual value_type max_abs() const = 0;

        /**
         * \brief Returns the minimum absolute value stored in the storage
         */
        virtual value_type min_abs() const = 0;

        /**
         * \brief Returns the absolute sum of every value stored in the storage
         */
        virtual value_type sum_abs() const = 0;
    };

}
