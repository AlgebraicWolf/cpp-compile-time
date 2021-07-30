#ifndef PRINT_HPP_
#define PRINT_HPP_
#include <type_traits>

template<typename T>
concept Printable = requires(T a) {
  print<T>();
};

#endif
