#include <iostream>


template <size_t I>
struct factorial {
  static constexpr size_t value = I * factorial<I - 1>::value;
};

template <>
struct factorial<1> {
  static constexpr size_t value = 1;
};

template <>
struct factorial<0> {
  static constexpr size_t value = 1;
};

template <typename T, T Value>
struct integral_constant {
  static constexpr T value = Value;
};

struct true_type 
  : integral_constant<bool, true> {};

struct false_type 
  : integral_constant<bool, false> {};

template <typename T, typename V>
struct is_same : public false_type {} ;

template <typename T>
struct is_same<T, T> : public true_type {};

template <bool Value, typename T, typename V>
struct conditional {
//if 0
//  typedef int type;
//  using type =  int;
//
//  typedef int (*f)(int, int);
//  using f = int (*)(int, int);
//#endif

  using type = V;
};

template <typename T, typename V>
struct conditional<true, T, V> {
  using type = T;
};

template <bool Value, typename T>
struct enable_if;

template <typename T>
struct enable_if<true, T> {
  using type = T;
};

// Approach 1:
// If you have i, N, i is a square root of N, iff i * i = N
// N [1,...N] Start with 1,2,3,4,... i*i == N
//
// Approach 2:
// binary search: midpoint, N/2 == mid (mid * mid == N) 
// if (mid * mid) < N [1, mid]
// if (mid * mid) > N [mid + 1, N]
/// 120 sqrt(120) = 11

#if 0
template <uint32_t I, uint32_t Value>
struct SqrtImpl {
  static constexpr uint32_t value = ((I * I) < Value) ? (SqrtImpl<I+1, Value>::value) : (I) ;
};
#endif

template <uint32_t I, uint32_t Value>
struct SqrtImpl {
  using T = typename conditional<((I * I) < Value), SqrtImpl<I + 1, Value>, integral_constant<uint32_t, I> >::type;
  static constexpr uint32_t value = T::value;
};

 template<uint32_t I>
 struct SqrtImpl<I, I> {
  static constexpr uint32_t value  = I;
 };

template <uint32_t Value>
struct Sqrt : SqrtImpl<1, Value> {};

template <uint32_t Value, uint32_t Start, uint32_t End>
struct sqrt_impl;

template <uint32_t Value, uint32_t Start, uint32_t End>
struct sqrt_impl { 
  static constexpr uint32_t mid = (Start + End) >> 1;
  
  using T = typename conditional<(mid * mid) < Value, 
                                    sqrt_impl<Value, mid, End>, 
                                    sqrt_impl<Value, Start, mid>>
                          ::type;

  static constexpr uint32_t val = T::val;
};

template <uint32_t Value, uint32_t T>
struct sqrt_impl<Value, T, T> {
  static constexpr uint32_t val = T;
};


template <uint32_t Value>
struct sqrt : sqrt_impl<Value, 1, Value> {};


int isqrt(int Value, int start, int last) {
  int mid = (start + last) / 2;
  
  if (start == last)
    return start;

  if ((mid * mid) <= Value)
    return isqrt(Value, mid, last);
  else
    return isqrt(Value, start, mid - 1);
}

// isqrt(100, 1, 100);

int main() {
  std::cout << integral_constant<int, 5>::value << std::endl;
  std::cout << true_type::value << std::endl;
  std::cout << is_same<int, float>::value << std::endl;
  std::cout << is_same<uint, uint32_t>::value << std::endl; // SFINAE: substition failure is not an error

  std::cout << is_same<typename conditional<sizeof(int) == 4, float, double>::type, float>::value << std::endl;
  std::cout << is_same<typename conditional<sizeof(int) == sizeof(long), float, double>::type, double>::value << std::endl;

  std::cout << "size_t: " << is_same<unsigned long, size_t>::value << std::endl; 

//  std::cout << is_same<typename enable_if<sizeof(int) == 4, float>::type, float>::value << std::endl;
  constexpr int N = 100;
  std::cout << sqrt<N>::val << std::endl;
//std::cout << is_same<typename enable_if<sizeof(int) == sizeof(char), bool>::type, bool>::value << std::endl;

  return 0;
}

#if 0
factorial<5> 5 * 24 = 120
  factorial<4> 4 * 6 = 24
    factorial<3> 3 * 2 = 6
      factorial<2> 2 * 1 = 2
        factorial<1>
#endif
