#pragma once

#include <cstddef>

namespace pr {

    template <typename I> 
    size_t count(I begin, I end) {

        size_t i = 0;

        for (I it = begin; it != end; ++it) {
            i++;
        }

        return i;
    }

    template <typename I, typename T> 
    size_t count_if_equal(I begin, I end, T& val) {

        size_t i = 0;

        for (I it = begin; it != end; ++it) {
            if (*it == val) i++;
        }

        return i;
    }
}
 