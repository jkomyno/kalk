#pragma once
#include <algorithm> // std::transform
#include <numeric> // std::accumulate
#include "abstract_square_matrix.h"
#include "i_diagonal_matrix.h"
#include "exceptions/bad_cast.h"
#include "dense_vector.h"

namespace linear_algebra {
    template <typename T, typename Iterator, typename ConstIterator>
    class abstract_diagonal_matrix : virtual public i_diagonal_matrix<T>,
                                     virtual public abstract_square_matrix<T, Iterator, ConstIterator> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using const_pointer = typename i_container<T>::const_pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using iterator = typename abstract_container<T, Iterator, ConstIterator>::iterator;
        using const_iterator = typename abstract_container<T, Iterator, ConstIterator>::const_iterator;
        using diagonal_iterator = typename abstract_square_matrix<T, Iterator, ConstIterator>::diagonal_iterator;
        using const_diagonal_iterator = typename abstract_square_matrix<T, Iterator, ConstIterator>::
        const_diagonal_iterator;

        explicit abstract_diagonal_matrix(size_type dimensions)
            : abstract_matrix<value_type, iterator, const_iterator>(dimensions, dimensions),
              abstract_square_matrix<value_type, iterator, const_iterator>(dimensions) {}

        abstract_diagonal_matrix(const abstract_diagonal_matrix<T, Iterator, ConstIterator>& other) = default;
        abstract_diagonal_matrix(abstract_diagonal_matrix<T, Iterator, ConstIterator>&& other) noexcept = default;
        abstract_diagonal_matrix& operator=(const abstract_diagonal_matrix<T, Iterator, ConstIterator>& other) = default
        ;

        virtual ~abstract_diagonal_matrix() = default;

        void to_identity() override;
        bool is_identity() const override;
        i_vector<T>* diagonal() const override;
        value_type norm_infinity() const override;

        /* A diagonal matrix cannot have values different than 0 outside its main diagonal */
        void random(const_reference min, const_reference max, abstract_random_function<value_type>* random_functor)
        override { this->apply_diagonal(this->random_op(min, max, random_functor)); }

        void fill(const_reference scalar) override { this->apply_diagonal(this->fill_op(scalar)); }
        void scale(const_reference scalar) override { this->apply_diagonal(this->scale_op(scalar)); }
        void increment(const_reference scalar) override { this->apply_diagonal(this->increment_op(scalar)); }
        void negate() override { this->apply_diagonal(this->negate_op()); }
        value_type determinant() const override;

    private:
        template <typename F>
        void apply_diagonal(F&& mutate_operator);

        void check_is_diagonal() const;
    };

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_diagonal_matrix<T, Iterator, ConstIterator>::to_identity() { this->fill_diagonal(T(1)); }

    template <typename T, typename Iterator, typename ConstIterator>
    bool abstract_diagonal_matrix<T, Iterator, ConstIterator>::is_identity() const {
        bool result = true;
        auto one = T(1);
        for (auto cit = this->begin_diagonal(); cit != this->end_diagonal() && result; ++cit) {
            result = result && (*cit == one);
        }
        return result;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    i_vector<T>* abstract_diagonal_matrix<T, Iterator, ConstIterator>::diagonal() const {
        const_diagonal_iterator start = this->begin_diagonal();
        const_diagonal_iterator end = this->end_diagonal();
        auto raw_data = std::vector<value_type>(start, end);
        return new dense_vector<value_type>(raw_data);
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_diagonal_matrix<T, Iterator, ConstIterator>::value_type abstract_diagonal_matrix<T, Iterator,
                                                                                                       ConstIterator>::
    norm_infinity() const {
        // this is due to the fact that for each row, at most only a value is different than T(0)
        return this->max_abs();
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_diagonal_matrix<T, Iterator, ConstIterator>::value_type abstract_diagonal_matrix<T, Iterator,
                                                                                                       ConstIterator>::
    determinant() const {
        const_diagonal_iterator start = this->begin_diagonal();
        const_diagonal_iterator end = this->end_diagonal();
        return std::accumulate(start, end, T(1), std::multiplies<T>());
    }

    template <typename T, typename Iterator, typename ConstIterator>
    template <typename F>
    void abstract_diagonal_matrix<T, Iterator, ConstIterator>::apply_diagonal(F&& mutate_operator) {
        diagonal_iterator start = this->begin_diagonal();
        diagonal_iterator end = this->end_diagonal();
        std::transform(start, end, start, mutate_operator);
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_diagonal_matrix<T, Iterator, ConstIterator>::check_is_diagonal() const {
        auto dim = this->dimension();
        for (size_type row = 1; row <= dim; ++row) {
            for (size_type column = 1; column <= dim; ++column) {
                if (row != column && this->get_at(row, column) != T(0)) {
                    throw exceptions::bad_diagonal_matrix_cast();
                }
            }
        }
    }
}
