#include <iostream>
#include <vector>
#include <list>
#include <iterator>

// function overloading
// iterator_traits

template <typename iter>
iter advance_impl(iter I, size_t N, std::input_iterator_tag) {
  // ++
  std::cout << "From input iterator" << std::endl;
  while (N--) {
    ++ I;
  }
  return I;
}  

template <typename iter>
iter advance_impl(iter I, size_t N, std::random_access_iterator_tag) {
  // +
  std::cout << "From random access iterator" << std::endl;
  return I + N;
}

template <typename iter>
iter advance(iter I, size_t N) {
  return advance_impl(I, N, 
      typename std::iterator_traits<iter>::iterator_category());
}

int main() {
  std::vector<int> V { 10, 20, 30, 40, 50, 60 }; // random_access_iterator_tag
                                                 // i: i + N
    
  std::vector<int>::iterator it = std::begin(V);
  auto X =  *(advance(it, 3));

  std::cout << *X;

  std::list<int> L { 1, 2, 3, 4, 5, 6, 7, 8 }; // bidirectional_iterator_tag
                                               // i: loop ++i, (N-1) times
                                               //
  typename std::list<int>::iterator it_1 = std::begin(L);
  std::cout << *(advance(it_1, 3));
}

// advance(x, 2)
