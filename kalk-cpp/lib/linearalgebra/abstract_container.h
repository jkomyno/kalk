#pragma once
#include <algorithm> // std::transform, std::max_element, std::min_element
#include <functional> // std::function
#include "i_container.h"

namespace linear_algebra {

    template <typename T, typename Iterator, typename ConstIterator>
    class abstract_container : virtual public i_container<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using const_pointer = typename i_container<T>::const_pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using iterator = Iterator;
        using const_iterator = ConstIterator;

        abstract_container() = default;
        abstract_container(const abstract_container<T, Iterator, ConstIterator>& other) = default;
        abstract_container(abstract_container<T, Iterator, ConstIterator>&& other) noexcept = default;
        abstract_container& operator=(const abstract_container<T, Iterator, ConstIterator>& other) = default;
        virtual ~abstract_container() = default;

        void scale(const_reference scalar) override;
        void increment(const_reference scalar) override;
        void fill(const_reference scalar) override;
        void zero() override;
        void negate() override;
        void sort() override;
        void random(const_reference min, const_reference max,
                    abstract_random_function<value_type>* random_functor) override;
        value_type max() const override;
        value_type min() const override;
        value_type sum() const override;
        value_type max_abs() const override;
        value_type min_abs() const override;
        value_type sum_abs() const override;

        virtual iterator begin() = 0;
        virtual iterator end() = 0;
        virtual const_iterator begin() const = 0;
        virtual const_iterator end() const = 0;

    protected:
        virtual pointer begin_ptr() { return this->data(); }

        virtual pointer end_ptr() { return this->begin_ptr() + std::distance(this->begin(), this->end()); }

        virtual const_pointer begin_ptr() const { return this->data(); }

        virtual const_pointer end_ptr() const { return this->begin_ptr() + std::distance(this->begin(), this->end()); }

        static decltype(auto) scale_op(const_reference scalar) {
            return [&scalar](const_reference value) -> T { return value * scalar; };
        }

        static decltype(auto) increment_op(const_reference scalar) {
            return [&scalar](const_reference value) -> T { return value + scalar; };
        }

        static decltype(auto) fill_op(const_reference scalar) {
            return [&scalar](const_reference) -> T { return scalar; };
        }

        static decltype(auto) negate_op() { return [](value_type value) -> value_type { return -value; }; }

        static decltype(auto) random_op(const_reference min, const_reference max,
                                        abstract_random_function<value_type>* random_functor) {
            return [&](value_type) -> value_type { return (*random_functor)(min, max); };
        }

    private:
        template <typename F>
        void apply(F&& mutate_operator);

        value_type max_helper(bool absolute) const;
        value_type min_helper(bool absolute) const;
        value_type sum_helper(bool absolute) const;

        template <typename U>
        static bool compare_helper(const U& a, const U& b) { return a < b; }

        template <typename U>
        static bool absolute_compare_helper(const U& a, const U& b) { return std::abs(a) < std::abs(b); }
    };

    template <typename T, typename Iterator, typename ConstIterator>
    template <typename F>
    void
    abstract_container<T, Iterator, ConstIterator>::apply(F&& mutate_operator) {
        auto start = this->begin();
        auto end = this->end();
        std::transform(start, end, start, mutate_operator);
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::scale(const_reference scalar) {
        if (scalar != T(1)) { apply(this->scale_op(scalar)); }
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::increment(const_reference scalar) {
        if (scalar != T(0)) { apply(this->increment_op(scalar)); }
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::fill(const_reference scalar) { apply(this->fill_op(scalar)); }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::zero() { fill(T(0)); }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::negate() { apply(this->negate_op()); }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::sort() {
        auto start = this->begin();
        auto end = this->end();
        std::sort(start, end);
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void
    abstract_container<T, Iterator, ConstIterator>::random(const_reference min, const_reference max,
                                                           abstract_random_function<value_type>* random_functor) {
        apply(this->random_op(min, max, random_functor));
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::max() const { return max_helper(false); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::min() const { return min_helper(false); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::sum() const { return sum_helper(false); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::max_abs() const { return max_helper(true); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::min_abs() const { return min_helper(true); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::sum_abs() const { return sum_helper(true); }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type abstract_container<T, Iterator, ConstIterator>::
    max_helper(bool absolute) const {
        if (absolute) {
            ConstIterator result = std::max_element(this->begin(), this->end(), absolute_compare_helper<T>);
            return std::abs(*result);
        }
        ConstIterator result = std::max_element(this->begin(), this->end(), compare_helper<T>);
        return *result;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::min_helper(bool absolute) const {
        if (absolute) {
            ConstIterator result = std::min_element(this->begin(), this->end(), absolute_compare_helper<T>);
            return std::abs(*result);
        }
        ConstIterator result = std::min_element(this->begin(), this->end(), compare_helper<T>);
        return *result;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_container<T, Iterator, ConstIterator>::value_type
    abstract_container<T, Iterator, ConstIterator>::sum_helper(bool absolute) const {
        auto sum = T(0);
        if (absolute) { for (auto value : *this) { sum += std::abs(value); } } else {
            for (auto value : *this) { sum += value; }
        }
        return sum;
    }

}
