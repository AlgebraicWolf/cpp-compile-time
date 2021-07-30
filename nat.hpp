#ifndef NAT_HPP_
#define NAT_HPP_

#include <type_traits>
#include <iostream>
#include "print.hpp"

// Defining type for natural numbers
struct NatBase {};

template<typename T>
concept Nat = std::is_base_of<NatBase, T>::value;

// Natural numbers constructors 
struct Z : NatBase {};

template <Nat N>
struct Succ : NatBase {};

// Conversion to unsigned int

template <Nat N>
struct ToUnsignedInt {};

template<>
struct ToUnsignedInt<Z> {
  static constexpr unsigned int value = 0;
};

template <Nat N>
struct ToUnsignedInt<Succ<N>> {
  static constexpr unsigned int value = ToUnsignedInt<N>::value + 1;
};

// Addition for natural numbers
template <Nat A, Nat B>
struct Add {};

template <Nat B>
struct Add<Z, B> {
  using result = B;
};

template<Nat A, Nat B>
struct Add<Succ<A>, B> {
  using result = Add<A, Succ<B>>::result;
};

// Equality

template <Nat A, Nat B>
struct Eq {
  static constexpr bool value = false;
};

template<>
struct Eq<Z, Z> {
  static constexpr bool value = true;
};

template<Nat A, Nat B>
struct Eq<Succ<A>, Succ<B>> {
  static constexpr bool value = Eq<A, B>::value;
};

// Inequalities

template<Nat A, Nat B>
struct LE {};

template<Nat B>
struct LE<Z, B> {
  static constexpr bool value = true;
};

template<Nat A>
struct LE<Succ<A>, Z> {
  static constexpr bool value = false;
};

template <Nat A, Nat B>
struct LE<Succ<A>, Succ<B>> {
  static constexpr bool value = LE<A, B>::value;
};

template <Nat A, Nat B>
struct LT {
  static constexpr bool value = LE<A, B>::value && !Eq<A, B>::value;
};

// Printing helper

template<Nat N>
void print() {
  std::cout << ToUnsignedInt<N>::value;
}

#endif