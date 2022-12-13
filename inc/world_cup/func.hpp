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
#include "world_cup/rng.hpp"

namespace all_star::world_cup::func {

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

// Similar functionality to R's `order` function that sorts a vector of indices 
// based on a passed in vector. Returns a vector of indices corresponding to the 
// position of the ith element in a sorted vector
// 
// This version of order assumes that X is semi ordered (< and > exist) 
//
// example:
//
// order([14, 4, 7, 8]) -> [3, 0, 1, 2]
// order([14, 4, 7, 8], true) -> [0, 3, 2, 1]
template <class X>
auto order(const std::vector<X> &vec, bool descending = false) -> std::vector<int> {

    std::vector<int> indices (vec.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::function<bool(int, int)> pred;

    if (descending) { 
        pred = [&] (int i_plus_1, int i) { return vec[i_plus_1] > vec[i]; }; // we want this expression to be false
    } else {
        pred = [&] (int i_plus_1, int i) { return vec[i_plus_1] < vec[i]; };
    }

    std::stable_sort(indices.begin(), indices.end(), pred);

    return indices;
}

// Similar to R's replicate function, this function calls the _Expr n times
template <class _Expr>
inline void replicate(int n, _Expr expr) {
    for (int i = 0; i < n; i++) {
        expr();
    }
}


} // namespace all_star::world_cup::func