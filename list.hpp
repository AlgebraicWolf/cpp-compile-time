#ifndef LIST_HPP_
#define LIST_HPP_

#include <iostream>
#include <type_traits>

#include "print.hpp"
#include "nat.hpp"

// List type along with its constructors

struct ListBase {};

template <typename T>
concept List = std::is_base_of<ListBase, T>::value;

struct Nil : ListBase {};

template <typename x, List xs>
struct Cons : ListBase {};

// WARNING! Not quite a compile time thing. Used for debugging.
template <List xs>
struct PrintAux {
};

template <typename x, List xs>
struct PrintAux<Cons<x, xs>> {
    static void pr() {
        print<x>();
        std::cout << ", ";
        PrintAux<xs>::pr();
    }
};

template <>
struct PrintAux<Nil> {
    static void pr() {}
};

template <List xs>
void print() {
    std::cout << '[';
    PrintAux<xs>::pr();
    std::cout << ']';
}

// List reversal 
template<List xs, List ys>
struct ReverseOnto {};

template <typename x, List xs, List ys>
struct ReverseOnto<Cons<x, xs>, ys> {
  using result = ReverseOnto<xs, Cons<x, ys>>::result;
};

template <List ys>
struct ReverseOnto<Nil, ys> {
  using result = ys;
};

template <List xs>
struct Reverse {
  using result = ReverseOnto<xs, Nil>::result;
};

// Append on lists
template <List xs, List ys>
struct Append {};

template <List ys>
struct Append<Nil, ys> {
  using result = ys;
};

template <typename x, List xs, List ys> 
struct Append<Cons<x, xs>, ys> {
  using result = Cons<x, typename Append<xs, ys>::result>;
};

// Take N elements
template <Nat N, List xs>
struct Take {};

template <List xs>
struct Take<Z, xs> {
  using result = Nil;
};

template <Nat N, typename x, List xs>
struct Take<Succ<N>, Cons<x, xs>> {
  using result = Cons<x, typename Take<N, xs>::result>;
};

// Skip N elements
template <Nat N, List xs>
struct Skip {};

template <List xs> 
struct Skip<Z, xs> {
  using result = xs;
};

template <Nat N, typename x, List xs>
struct Skip<Succ<N>, Cons<x, xs>> {
  using result = Skip<N, xs>::result;
};

// Functions to halve list

template <List xs>
struct Odds {};

template <List xs>
struct Evens {};

template<>
struct Odds<Nil> {
  using result = Nil;
};

template<>
struct Evens<Nil> {
  using result = Nil;
};

template<typename x>
struct Odds<Cons<x, Nil>> {
  using result = Cons<x, Nil>;
};

template<typename x>
struct Evens<Cons<x, Nil>> {
  using result = Nil;
};

template<typename x1, typename x2, typename xs>
struct Odds<Cons<x1, Cons<x2, xs>>> {
  using result = Cons<x1, typename Odds<xs>::result>;
};

template<typename x1, typename x2, typename xs>
struct Evens<Cons<x1, Cons<x2, xs>>> {
  using result = Cons<x2, typename Evens<xs>::result>;
};

#endif