#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <random>
#include "abstract_container.h"
#include "abstract_dense_matrix.h"
#include "abstract_diagonal_matrix.h"
#include "abstract_matrix.h"
#include "abstract_square_matrix.h"
#include "abstract_vector.h"
#include "dense_diagonal_matrix.h"
#include "dense_matrix.h"
#include "dense_square_matrix.h"
#include "dense_vector.h"
#include "i_container.h"
#include "i_diagonal_matrix.h"
#include "i_matrix.h"
#include "i_square_matrix.h"
#include "i_vector.h"
#include "exceptions/bad_cast.h"
#include "exceptions/illegal_dimensions.h"

namespace linear_algebra {
    class random_fun : public abstract_random_function<int> {
    public:
        int operator()(const int& min, const int& max) const override {
            std::random_device rd; // only used once to initialise (seed) engine
            std::mt19937 rng(rd());
            // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
            return uni(rng);
        }
    };
}

#endif // LINEAR_ALGEBRA_H
