#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <algorithm>

template <typename T>
struct ReturnType;

// sequence of int: -> long
// sequnece of char -> int 
// sequence of float -> double

template <>
struct ReturnType<int> {
  using RT = long;
  static constexpr RT val = 100L;
};

template <>
struct ReturnType<char> {
  using RT = int;
  static constexpr RT val = 128;
};

template <>
struct ReturnType<float> {
  using RT = double;
  static constexpr RT val = 300.0f;
};

#if 0
template <typename T>
typename ReturnType<T>::RT Accumulate(T *first, T *last) {
  typename ReturnType<T>::RT accumulator {};

  // RTTI : Runtime Type Identification
  std::cout << typeid(typename ReturnType<T>::RT).name() << std::endl;

  while (first != last) {
    accumulator += (*first);

    ++ first;
  }

  return accumulator;
} 
#endif

#if 0
template <typename T, typename _RT = typename ReturnType<T>::RT>
_RT Accumulate(T *first, T *last) {
  _RT accumulator{};

  std::cout << typeid(_RT).name() << std::endl;

  while (first != last) {
    accumulator += (*first);

    ++ first;
  }

  return accumulator;
}
#endif

#if 0
// Ignore this example
template <typename T, typename RetTy = ReturnType<T>, typename _RT = typename RetTy::RT>
_RT Accumulate(T *first, T *last) {
  _RT accumulator = RetTy::val;

  std::cout << typeid(_RT).name() << std::endl;

  while (first != last) {
    accumulator += (*first);

    ++ first;
  }

  return accumulator;
}
#endif

#if 0
template <typename T, typename Reduce>
typename ReturnType<T>::RT Accumulate(T *first, T *last, Reduce Op) {
  typename ReturnType<T>::RT accumulator {};

  // RTTI : Runtime Type Identification
  // std::cout << typeid(typename ReturnType<T>::RT).name() << std::endl;

  while (first != last) {
    // accumulator += (*first);

    accumulator = Op(*first, accumulator);
    ++ first;
  }

  return accumulator;
} 
#endif 

template <typename T>
struct MaxPolicy {
  static T op(T val1, T val2) { return std::max(val1, val2); }
};

template <typename T>
struct AddPolicy {
  static T op(T val1, T val2) { return val1 + val2; }
};


template <typename T, typename ReducePolicy>
typename ReturnType<T>::RT Accumulate(T *first, T *last) {
  typename ReturnType<T>::RT accumulator {};

  // RTTI : Runtime Type Identification
  // std::cout << typeid(typename ReturnType<T>::RT).name() << std::endl;

  while (first != last) {
    // accumulator += (*first);

    accumulator = ReducePolicy::op(*first, accumulator);
    ++ first;
  }

  return accumulator;
} 


int main() {
  int array[] = {1, 2, 3, 4, 6, 9, 7, 8};
  char array_char[] = {'a', 'b', 'c', 'd', 'e'};
  float array_float[] = {100.6f, 345.5f, 89, 345.6f};

  // std::cout << Accumulate(array, array + sizeof(array) / sizeof(int)) << std::endl;
  // std::cout << Accumulate(array_char, array_char + sizeof(array_char) / sizeof(char)) << std::endl;
  // std::cout << Accumulate(array_float, array_float + sizeof(array_float) / sizeof(float)) << std::endl;

  // std::cout << Accumulate(array, array + (sizeof(array) / sizeof(int)), 
  //             [](long x, long y) -> long { return std::max(x, y); }) << std::endl;

  // std::cout << Accumulate(array_float, array_float + (sizeof(array_float) / sizeof(float)),
  //             [](float x, float y) { return x + y; }) << std::endl;


  std::cout << Accumulate<int, MaxPolicy<int>>(array, array + sizeof(array) / sizeof(int)) << std::endl;
  std::cout << Accumulate<float, AddPolicy<float>>(array_float, array_float + sizeof(array_float) / sizeof(float)) << std::endl;



  // std::cout << Accumulate(array_char, array_char + 5) << std::endl;
  // std::cout << Accumulate(array_float, array_float + 4) << std::endl;
  // std::cout << std::is_same<double, 
  //                           decltype(Accumulate(array_float, array_float + 4))>::value
  //           << std::endl;

  return 0;
}
