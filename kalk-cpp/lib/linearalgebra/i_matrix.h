#pragma once
#include "i_container.h"
#include "exceptions/illegal_dimensions.h"
#include "i_vector.h"

namespace linear_algebra {

    template <typename T>
    class i_matrix : virtual public i_container<T> {
    public:
        using size_type = typename i_container<T>::size_type;
        using value_type = typename i_container<T>::value_type;
        using pointer = typename i_container<T>::pointer;
        using reference = typename i_container<T>::reference;
        using const_reference = typename i_container<T>::const_reference;

        using i_container<T>::get_at;
        // tell the compiler I want both the 'get_at' method from i_container and from this class
        using i_container<T>::set_at;
        // tell the compiler I want both the 'set_at' method from i_container and from this class

        i_matrix() = default;
        i_matrix(const i_matrix& other) = default;
        i_matrix(i_matrix&& other) = default;
        i_matrix& operator=(const i_matrix& other) = default;
        virtual ~i_matrix() = default;

        /**
         * \brief Returns a new concrete matrix class with the specified dimensions
         * \param new_rows
         * \param new_columns
         * \return
         */
        virtual i_matrix<T>* factory(size_type new_rows, size_type new_columns) const = 0;

        /**
         * \brief Returns the number of rows of the matrix
         */
        virtual size_type rows() const = 0;

        /**
         * \brief Sets the number of rows of the matrix
         * \param rows
         */
        virtual void set_rows(size_type rows) = 0;

        /**
         * \brief Returns the number of columns of the matrix
         */
        virtual size_type columns() const = 0;

        /**
         * \brief Sets the number of columns of the matrix
         * \param columns
         */
        virtual void set_columns(size_type columns) = 0;

        /**
         * \brief Sets the new value of the current matrix at the specific getRow and getColumn
         * \param row
         * \param column
         * \param value
         */
        virtual void set_at(size_type row, size_type column, const_reference value) = 0;

        /**
         * \brief Returns the value of the current matrix at the specific getRow and getColumn
         * \param row
         * \param column
         */
        virtual value_type get_at(size_type row, size_type column) const = 0;

        /**
        * \brief Returns a reference current matrix at the specific getRow and getColumn
        * \param row
        * \param column
        */
        virtual reference get_at(size_type row, size_type column) = 0;

        /**
         * \brief Returns a vector class representing the row-th row of the matrix
         * \param row
         */
        virtual i_vector<value_type>* get_row_at(size_type row) const = 0;

        /**
         * \brief Transposes the current matrix mutating it
         */
        virtual void transpose() = 0;

        /**
        * Returns a reshaped version of the current matrix
        */
        virtual i_matrix<value_type>* reshape(size_type rows, size_type columns) = 0;

        virtual i_matrix<T>* add(i_matrix<T>* other) {
            if (this->rows() != other->rows() || this->columns() != other->columns()) {
                throw exceptions::algebric_sum_dimensions();
            }

            auto result = dynamic_cast<i_matrix<T>*>(this->clone());
            for (size_type i = 1; i <= this->rows(); ++i) {
                for (size_type j = 1; j <= this->columns(); ++j) { result->get_at(i, j) += other->get_at(i, j); }
            }

            return result;
        }

        virtual i_matrix<T>* subtract(i_matrix<T>* other) {
            if (this->rows() != other->rows() || this->columns() != other->columns()) {
                throw exceptions::algebric_sum_dimensions();
            }

            auto result = dynamic_cast<i_matrix<T>*>(this->clone());
            for (size_type i = 1; i <= this->rows(); ++i) {
                for (size_type j = 1; j <= this->columns(); ++j) { result->get_at(i, j) -= other->get_at(i, j); }
            }

            return result;
        }

        virtual i_matrix<T>* multiply(i_matrix<T>* other) {
            if (this->columns() != other->rows()) { throw exceptions::multiplication_dimensions(); }

            i_matrix<T>* result = this->factory(this->rows(), other->columns());
            for (size_type i = 1; i <= this->rows(); ++i) {
                for (size_type j = 1; j <= other->columns(); ++j) {
                    for (size_type k = 1; k <= other->rows(); ++k) {
                        T partial_product = this->get_at(i, j) * other->get_at(k, j);
                        result->get_at(i, j) += partial_product;
                    }
                }
            }

            return result;
        }
    };

}
