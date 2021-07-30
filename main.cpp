#include <iostream>

#include "nat.hpp"
#include "list.hpp"
#include "merge_sort.hpp"

int main() {
  using zero = Z;
  using one = Succ<zero>;
  using two = Succ<one>;
  using three = Succ<two>;
  using four = Succ<three>;

  using l = Cons<three,
            Cons<four,
            Cons<one, 
            Cons<one,
            Cons<two,
            Cons<zero,
            Nil>>>>>>;

  print<MergeSort<l>::result>();
}