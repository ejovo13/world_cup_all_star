/**========================================================================
 * ?                          func.hpp
 * @brief   : Functional routines like map, filter, take etc that allow 
 *            us to write clear and expressive code instead of bogging down
 *            source code with for loops
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-10
 *========================================================================**/
#pragma once

#include <functional>
#include <vector>
#include "rng.hpp"

namespace world_cup::func {

/**========================================================================
 *!                  Functional approach to bracket handling
 *========================================================================**/
// map vector<X> to vector<Y> using a function f: X -> Y
template<class X, class Y>
auto map_vec(std::vector<X> vec, std::function<Y(X)> fn) -> std::vector<Y> {
    std::vector<Y> y(vec.size());

    int i = 0;
    for (auto &x : vec) {
        y[i] = fn(x);
        i++;
    }

    return y;
}

//todo test functional operations!!!
// operates on vectors!!
// takes the first n elements of a vector, returning a new copy
template<class X>
auto take(std::vector<X> vec, int n) {
    int i = 0;
    std::vector<X> out;

    for (const auto &v : vec) {
        if (i >= n) break;
        out.push_back(v);
        i++;
    }

    return out;
}

} // namespace world_cup::func