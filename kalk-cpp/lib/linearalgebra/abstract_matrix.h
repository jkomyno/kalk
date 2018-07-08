#pragma once
#include <ostream> // std::ostream
#include <iomanip> // std::setw
#include "abstract_container.h"
#include "i_matrix.h"
#include "exceptions/bad_cast.h"

namespace linear_algebra {

    template <typename T, typename Iterator, typename ConstIterator>
    class abstract_matrix : virtual public i_matrix<T>, public abstract_container<T, Iterator, ConstIterator> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;
        using iterator = Iterator;
        using const_iterator = ConstIterator;

        friend std::ostream& operator<<(std::ostream& os,
                                        const abstract_matrix<value_type, iterator, const_iterator>& mat) {
            return mat.print(os);
        }

        explicit abstract_matrix(size_type rows, size_type columns)
            : rows_(rows),
              columns_(columns) { check_is_matrix(); }

        abstract_matrix(const abstract_matrix<T, Iterator, ConstIterator>& other)
            : i_container<value_type>(other),
              i_matrix<value_type>(other),
              abstract_container<value_type, iterator, const_iterator>(other),
              rows_(other.rows_),
              columns_(other.columns_) { check_is_matrix(); }

        abstract_matrix(abstract_matrix<T, Iterator, ConstIterator>&& other) noexcept
            : i_matrix<T>(std::move(other)),
              abstract_container<value_type, iterator, const_iterator>(std::move(other)),
              rows_(other.rows_),
              columns_(other.columns_) { check_is_matrix(); }

        /*
        abstract_matrix(const abstract_matrix<T, Iterator, ConstIterator>& other, size_type new_rows, size_type new_columns)
            : abstract_container<T, Iterator, ConstIterator>(other),
            rows_(new_rows),
            columns_(new_columns) { }

        abstract_matrix(abstract_matrix<T, Iterator, ConstIterator>&& other, size_type new_rows, size_type new_columns) noexcept
            : i_matrix<T>(other),
            abstract_container<T, Iterator, ConstIterator>(other),
            rows_(new_rows),
            columns_(new_columns) { }
            */
        abstract_matrix& operator=(const abstract_matrix<T, Iterator, ConstIterator>& other) = default;
        virtual ~abstract_matrix() = default;
        void swap(abstract_matrix<value_type, iterator, const_iterator>& other) noexcept;

        size_type rows() const override;
        size_type columns() const override;
        void transpose() override;
        value_type norm_infinity() const override;

    protected:
        void set_rows(size_type rows) override;
        void set_columns(size_type columns) override;

        /**
         * \brief In linear algebra, every matrix is indexed starting from 1, and
         * not from 0
         * \param row
         * \param column
         * \param columns
         * \return
         */
        static size_type get_index_from_one(size_type row, size_type column, size_type columns) {
            return (row - 1) * columns + (column - 1);
        }

        virtual std::ostream& print(std::ostream& os) const;

    private:
        size_type rows_;
        size_type columns_;

        void check_is_matrix() const;
    };

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_matrix<T, Iterator, ConstIterator>::set_rows(size_type rows) { rows_ = rows; }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_matrix<T, Iterator, ConstIterator>::swap(
        abstract_matrix<value_type, iterator, const_iterator>& other) noexcept {
        using std::swap;
        swap(this->rows_, other.rows_);
        swap(this->columns_, other.columns_);
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_matrix<T, Iterator, ConstIterator>::size_type
    abstract_matrix<T, Iterator, ConstIterator>::rows() const { return rows_; }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_matrix<T, Iterator, ConstIterator>::size_type
    abstract_matrix<T, Iterator, ConstIterator>::columns() const { return columns_; }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_matrix<T, Iterator, ConstIterator>::set_columns(size_type columns) { columns_ = columns; }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_matrix<T, Iterator, ConstIterator>::transpose() {
        auto helper = dynamic_cast<abstract_matrix<T, Iterator, ConstIterator>*>(this->clone());
        size_type tmp_columns = this->rows();
        this->set_rows(this->columns());
        this->set_columns(tmp_columns);
        for (size_type row = 1; row <= this->rows(); ++row) {
            for (size_type column = 1; column <= this->columns(); ++column) {
                this->set_at(row, column, helper->get_at(column, row));
            }
        }
    }

    template <typename T, typename Iterator, typename ConstIterator>
    typename abstract_matrix<T, Iterator, ConstIterator>::value_type abstract_matrix<T, Iterator, ConstIterator>::
    norm_infinity() const {
        auto maximum = T(-1);
        for (size_type row = 1; row <= this->rows_; ++row) {
            auto vec = this->get_row_at(row);
            T row_sum = vec->sum_abs();
            if (row_sum > maximum) { maximum = row_sum; }
            delete vec;
        }
        return maximum;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    std::ostream& abstract_matrix<T, Iterator, ConstIterator>::print(std::ostream& os) const {
        const auto width = 4;
        for (size_type row = 1; row < this->rows_; ++row) {
            for (size_type column = 1; column < this->columns_; ++column) {
                os << std::setw(width) << this->get_at(row, column) << ' ';
            }
            os << std::setw(width) << this->get_at(row, this->columns_) << std::endl;
        }
        for (size_type column = 1; column <= this->columns_; ++column) {
            os << std::setw(width) << this->get_at(this->rows_, column) << ' ';
        }
        os << std::endl;
        return os;
    }

    template <typename T, typename Iterator, typename ConstIterator>
    void abstract_matrix<T, Iterator, ConstIterator>::check_is_matrix() const {
        if (this->rows_ < 1 || this->columns_ < 1) { throw exceptions::bad_matrix_cast(); }
    }
}
