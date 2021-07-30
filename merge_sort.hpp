#ifndef MERGE_SORT_HPP_
#define MERGE_SORT_HPP_

#include "list.hpp"
#include "nat.hpp"

template <List xs, List ys>
struct Merge {};

template <List xs>
struct Merge<xs, Nil> {
    using result = xs;
};

template <List ys>
struct Merge<Nil, ys> {
    using result = ys;
};

template <>
struct Merge<Nil, Nil> {
    using result = Nil;
};

template <typename x, typename y, List xs, List ys>
struct Merge<Cons<x, xs>, Cons<y, ys>> {
    using result = std::conditional<LE<x, y>::value, Cons<x, typename Merge<xs, Cons<y, ys>>::result>, Cons<y, typename Merge<Cons<x, xs>, ys>::result>>::type;
};

template <List xs>
struct MergeSort {
   private:
    using l1 = MergeSort<typename Odds<xs>::result>::result;
    using l2 = MergeSort<typename Evens<xs>::result>::result;

   public:
    using result = Merge<l1, l2>::result;
};

template <>
struct MergeSort<Nil> {
    using result = Nil;
};

template <typename x>
struct MergeSort<Cons<x, Nil>> {
    using result = Cons<x, Nil>;
};

#endif