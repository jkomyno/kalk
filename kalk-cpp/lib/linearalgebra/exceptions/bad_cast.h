#pragma once
#include <string>
#include <stdexcept>

namespace linear_algebra {
	namespace exceptions {
		class bad_cast : public std::runtime_error {
		public:
			explicit bad_cast(const std::string& message)
				: runtime_error("Bad cast! " + message) {}

			bad_cast(const bad_cast& other) = default;
			bad_cast(bad_cast&& other) noexcept = default;
			bad_cast& operator=(const bad_cast& other) = default;
			bad_cast& operator=(bad_cast&& other) noexcept = default;

			virtual ~bad_cast() = default;
		};

		class bad_matrix_cast : public bad_cast {
		public:
			explicit bad_matrix_cast()
				: bad_cast("Cannot cast to matrix: rows and columns must be strictly bigger than 0") {}
		};

		class bad_square_matrix_cast : public bad_cast {
		public:
			explicit bad_square_matrix_cast()
				: bad_cast("Cannot cast to square matrix: rows != columns") {}
		};

		class bad_diagonal_matrix_cast : public bad_cast {
		public:
			explicit bad_diagonal_matrix_cast()
				: bad_cast("Cannot cast to diagonal matrix: elements outside the main diagonal are != 0") {}
		};
	}
}
