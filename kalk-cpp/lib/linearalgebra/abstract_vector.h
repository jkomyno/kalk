#pragma once
#include "abstract_container.h"
#include "i_vector.h"

namespace linear_algebra {
    template <typename T, typename Iterator, typename ConstIterator>
    class abstract_vector : public i_vector<T>, public abstract_container<T, Iterator, ConstIterator> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using iterator = Iterator;
        using const_iterator = ConstIterator;

        abstract_vector(size_type length) :
            length_(length) {}

        abstract_vector(const abstract_vector<T, Iterator, ConstIterator>& other)
            : i_container<T>(other),
              i_vector<T>(other),
              abstract_container<value_type, iterator, const_iterator>(other) {}

        abstract_vector(abstract_vector<T, Iterator, ConstIterator>&& other) noexcept
            : i_container<T>(other),
              i_vector<T>(other),
              abstract_container<value_type, iterator, const_iterator>(other) {}

        virtual ~abstract_vector() = default;
        void swap(abstract_vector<value_type, iterator, const_iterator>& other) noexcept;

        size_type length() const override { return length_; }

    private:
        size_type length_;
    };

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_vector<T, Iterator, ConstIterator>::swap(
        abstract_vector<value_type, iterator, const_iterator>& other) noexcept {
        using std::swap;
        swap(this->length_, other.length_);
    }
}
