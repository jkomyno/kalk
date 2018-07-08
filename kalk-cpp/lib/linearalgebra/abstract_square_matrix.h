#pragma once
#include <iterator>
#include "abstract_matrix.h"
#include "i_square_matrix.h"

namespace linear_algebra {

    template <typename T, typename Iterator, typename ConstIterator>
    class abstract_square_matrix : virtual public i_square_matrix<T>,
                                   virtual public abstract_matrix<T, Iterator, ConstIterator> {
    public:
        using size_type = typename i_container<T>::size_type;

        template <typename ValueType>
        class custom_stride_iterator : public std::iterator<std::forward_iterator_tag, ValueType> {
        public:
            using iterator_t = custom_stride_iterator<ValueType>;
            using value_type = typename std::iterator<std::forward_iterator_tag, ValueType>::pointer;
            using pointer = typename std::iterator<std::forward_iterator_tag, ValueType>::pointer;
            using reference = typename std::iterator<std::forward_iterator_tag, ValueType>::reference;

            /**
            * Notes: difference_type (https://en.cppreference.com/w/cpp/types/ptrdiff_t)
            * "When working with the C++ container library, the proper type for the difference between
            * iterators is the member typedef difference_type, which is often synonymous with std::ptrdiff_t.
            * Only pointers to elements of the same array (including the pointer one past the end of the array)
            * may be subtracted from each other."
            */
            using difference_type = typename std::iterator<std::forward_iterator_tag, ValueType>::difference_type;

            explicit custom_stride_iterator(pointer p = nullptr, size_type custom_stride = 0) :
                p_(p),
                custom_stride_(custom_stride) {}

            custom_stride_iterator(const custom_stride_iterator& other) = default;
            custom_stride_iterator(custom_stride_iterator&& other) noexcept = default;
            custom_stride_iterator& operator=(const custom_stride_iterator& other) = default;
            custom_stride_iterator& operator=(custom_stride_iterator&& other) noexcept = default;

            ~custom_stride_iterator() = default;

            // prefix increment
            iterator_t& operator++() {
                p_ += custom_stride_;
                return *this;
            }

            // postfix
            iterator_t operator ++(int) {
                custom_stride_iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            iterator_t operator +(difference_type i) const { return custom_stride_iterator(p_ + (custom_stride_ * i)); }

            iterator_t& operator +=(difference_type i) {
                p_ += (custom_stride_ * i);
                return *this;
            }

            reference operator*() { return *p_; }
            reference operator*() const { return *p_; }
            pointer operator->() const { return p_; }
            value_type operator[](difference_type i) const { return *(p_ + (custom_stride_ * i)); }
            bool operator==(const iterator_t& other) const { return p_ == other.p_; }
            bool operator!=(const iterator_t& other) const { return p_ != other.p_; }

        private:
            pointer p_;
            size_type custom_stride_;
        };

        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using const_pointer = typename i_container<T>::const_pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using iterator = typename abstract_container<T, Iterator, ConstIterator>::iterator;
        using const_iterator = typename abstract_container<T, Iterator, ConstIterator>::const_iterator;
        using diagonal_iterator = custom_stride_iterator<value_type>;
        using const_diagonal_iterator = custom_stride_iterator<const value_type>;

        explicit abstract_square_matrix(size_type dimensions)
            : abstract_matrix<T, Iterator, ConstIterator>(dimensions, dimensions) {}

        abstract_square_matrix(const abstract_square_matrix<T, Iterator, ConstIterator>& other) = default;
        abstract_square_matrix(abstract_square_matrix<T, Iterator, ConstIterator>&& other) noexcept = default;
        abstract_square_matrix& operator=(const abstract_square_matrix<T, Iterator, ConstIterator>& other) = default;
        virtual ~abstract_square_matrix() = default;

        size_type dimension() const override;
        value_type trace() const override;
        value_type determinant() const override;
        void fill_diagonal(const_reference scalar) override;

        diagonal_iterator begin_diagonal();
        diagonal_iterator end_diagonal();
        const_diagonal_iterator begin_diagonal() const;
        const_diagonal_iterator end_diagonal() const;

    private:
        value_type determinant1x1() const;
        value_type determinant2x2() const;
        value_type determinant3x3() const;
        value_type determinantNxN() const;

        diagonal_iterator make_diagonal_iterator(pointer p) { return diagonal_iterator(p, this->dimension() + 1); }

        const_diagonal_iterator make_diagonal_iterator(const_pointer p) const {
            return const_diagonal_iterator(p, this->dimension() + 1);
        }

        void check_is_square() const;
    };

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::size_type
    abstract_square_matrix<T, Iterator, ConstIterator>::dimension() const {
        return this->rows(); // or this->columns(), it's indifferent since it's a square matrix
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::trace() const {
        auto result = T(0);
        for (const_diagonal_iterator cit = this->begin_diagonal(); cit != this->end_diagonal(); ++cit) {
            result += *cit;
        }
        return result;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::determinant() const {
        switch (dimension()) {
            case 1:
                return determinant1x1();
            case 2:
                return determinant2x2();
            case 3:
                return determinant3x3();
            default:
                return determinantNxN();
        }
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_square_matrix<T, Iterator, ConstIterator>::fill_diagonal(const_reference scalar) {
        for (diagonal_iterator it = this->begin_diagonal(); it != this->end_diagonal(); ++it) { *it = scalar; }
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::diagonal_iterator abstract_square_matrix<T, Iterator,
                                                                                                          ConstIterator>
    ::begin_diagonal() { return make_diagonal_iterator(this->begin_ptr()); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::diagonal_iterator abstract_square_matrix<T, Iterator,
                                                                                                          ConstIterator>
    ::end_diagonal() { return make_diagonal_iterator(this->end_ptr() + dimension()); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::const_diagonal_iterator abstract_square_matrix<T,
                                                                                                                Iterator
                                                                                                                , ConstIterator
    >::begin_diagonal() const { return make_diagonal_iterator(this->begin_ptr()); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::const_diagonal_iterator abstract_square_matrix<T,
                                                                                                                Iterator
                                                                                                                , ConstIterator
    >::end_diagonal() const { return make_diagonal_iterator(this->end_ptr() + dimension()); }

    /**
     * \brief The determinant of a scalar is the scalar itself
     */
    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::determinant1x1() const { return this->get_at(1, 1); }

    /**
     * \brief The determinant of a 2x2 square matrix is det(A) = ad - bc
     */
    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::determinant2x2() const {
        return (this->get_at(1, 1) * this->get_at(2, 2)) - (this->get_at(1, 2) * this->get_at(2, 1));
    }

    /**
     * \brief The determinant of a 3x3 square matrix is determined applying the Sarrus Rule
     */
    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::determinant3x3() const {
        const T a11 = this->get_at(1, 1);
        const T a12 = this->get_at(1, 2);
        const T a13 = this->get_at(1, 3);
        const T a21 = this->get_at(2, 1);
        const T a22 = this->get_at(2, 2);
        const T a23 = this->get_at(2, 3);
        const T a31 = this->get_at(3, 1);
        const T a32 = this->get_at(3, 2);
        const T a33 = this->get_at(3, 3);

        return ((a11 * a22 * a33) + (a12 * a23 * a31) + (a13 * a21 * a32)) -
            ((a31 * a22 * a13) + (a32 * a23 * a11) + (a33 * a21 * a12));
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_square_matrix<T, Iterator, ConstIterator>::value_type
    abstract_square_matrix<T, Iterator, ConstIterator>::determinantNxN() const {
        auto determinant = T(0);
        auto dim = this->dimension();
        for (size_type i = 1; i <= dim; ++i) {
            // It would be static_cast, if I wasn't using virtual inheritance
            auto mat = dynamic_cast<abstract_square_matrix<value_type, iterator, const_iterator>*>(this->clone());
            mat->vswap(*(mat->reshape(dim - 1, dim - 1)));
            for (size_type j = 2; j <= dim; ++j) {
                for (size_type k = 1; k <= dim; ++k) {
                    T value = this->get_at(j, k);
                    if (k < i) { mat->set_at(j - 1, k, value); } else if (k > i) { mat->set_at(j - 1, k - 1, value); }
                }
            }

            T sign = (i % 2 == 1) ? T(1) : T(-1);
            T multiplier = sign * this->get_at(1, i) * mat->determinant();
            determinant += multiplier;
        }
        return determinant;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_square_matrix<T, Iterator, ConstIterator>::check_is_square() const {
        return this->rows() == this->columns();
    }

}
