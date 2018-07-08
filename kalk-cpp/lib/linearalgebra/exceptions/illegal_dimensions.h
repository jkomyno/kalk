#pragma once
#include <string>
#include <stdexcept>

namespace linear_algebra {
	namespace exceptions {
		// https://isocpp.org/wiki/faq/exceptions#throwing-polymorphically
		class illegal_dimensions : public std::runtime_error {
		public:
			explicit illegal_dimensions(const std::string& message)
				: runtime_error("Illegal dimensions! " + message) {}

			illegal_dimensions(const illegal_dimensions& other) = default;
			illegal_dimensions(illegal_dimensions&& other) noexcept = default;
			illegal_dimensions& operator=(const illegal_dimensions& other) = default;
			illegal_dimensions& operator=(illegal_dimensions&& other) noexcept = default;

			virtual ~illegal_dimensions() = default;

            virtual void raise() { throw *this; }
		};

		class illegal_square_matrix_dimensions : public illegal_dimensions {
		public:
			explicit illegal_square_matrix_dimensions()
				: illegal_dimensions("A square matrix must have the same amount of rows and columns.") {}

            void raise() override { throw *this; }
		};

		class operator_dimensions : public illegal_dimensions {
		public:
			explicit operator_dimensions(const std::string& operation, const std::string& message)
                : illegal_dimensions("In order to perform 'c = " + operation + "', " + message) {}

			operator_dimensions(const operator_dimensions& other) = default;
			operator_dimensions(operator_dimensions&& other) noexcept = default;
			operator_dimensions& operator=(const operator_dimensions& other) = default;
			operator_dimensions& operator=(operator_dimensions&& other) noexcept = default;

			virtual ~operator_dimensions() = 0; // in order to make operator_dimensions abstract
		};

		inline operator_dimensions::~operator_dimensions() = default;

		class multiplication_dimensions : public operator_dimensions {
		public:
			explicit multiplication_dimensions()
                : operator_dimensions("a * b", "'a' must have as many columns as 'b''s rows.") {}

            void raise() override { throw *this; }
		};

		class algebric_sum_dimensions : public operator_dimensions {
		public:
			explicit algebric_sum_dimensions()
                : operator_dimensions("a + b", "'a' and 'b' must have the same amount of rows and columns.") {}

            void raise() override { throw *this; }
		};
	}
}
