#pragma once
#include <vector> // std::vector

namespace linear_algebra {
    namespace utils {

        class list_utils {
        public:
            list_utils() = delete;

            template <typename U>
            static std::vector<U> init_list(std::size_t size, const U& scalar) {
                return std::vector<U>(size, scalar);
            }

            template <typename U>
            static std::vector<U> copy_list(const std::vector<U>& list) {
                return std::vector<U>(list);
            }

            template <typename U>
            static std::vector<U> copy_list_and_pad(const std::vector<U>& list, std::size_t oldSize,
                                                    std::size_t newSize,
                                                    const U& padValue = U(0)) {
                if (oldSize > newSize)
                {
                    auto copied_list = copy_list(list);
                    auto second_part = copied_list(newSize - oldSize, padValue);
                    copied_list.insert(copied_list.end(), second_part.begin(), second_part.end());
                    return copied_list;
                }
                return std::vector<U>(list.begin(), list.begin() + newSize);
            }

            template <typename U>
            static std::vector<U> slice(const std::vector<U>& list, std::size_t start, std::size_t end) {
                auto start_cit = list.begin() + start;
                auto end_cit = list.begin() + end + 1;
                return std::vector<U>(start_cit, end_cit);
            }
        };

    }
}
