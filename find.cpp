#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <algorithm>

// Requirements: Input iterator
// == !=
// deref: rvalue
// ++ pre / post 

template <typename T>
void Display(T Iterator, T End) {
  while (Iterator != End) {
    std::cout << *Iterator << std::endl;
    ++Iterator;
  }
}

// Requirements: Output iterator
// U 
// deref : lvalue
// ++ Increment post / pre

template <typename T, typename U>
void Copy(T First, T Last, U DstFirst) {
  while (First != Last) {
    *DstFirst = *First;
    ++First;
    ++DstFirst;
  }
}

template <typename T>
struct M {
  T operator() (T value) { return value * 2; }
};

// Forward iterator = Input iterator + Output iterator
// Requirements:
// == != 
// deref: lvalue / rvalue
// ++ pre / post

template <typename T, typename Transform>
void Replace(T Iter, T End, Transform Trans) {
  while (Iter != End) {
    auto Value = *Iter;
    *Iter = Trans(Value);
    ++Iter;
  }
}

template <typename T>
struct multiply {
  T operator () (T first, T second) { return first * second; } 
};

template <typename iterator, typename T, typename Operation>
T accumulate(iterator iter, iterator last, T init, Operation Op) {
  T acc = init;

  while (iter != last) {
    acc = Op(acc, *iter);
    ++iter;
  }

  return acc;
}

template <typename T>
void swap(T &First, T &Second) {
  T Value = First;
  First = Second;
  Second = Value;
}

// Bidirectional iterator:  forward iterator
// Requirements:
// != ==
// * rvalue / lvalue
// ++ pre / post
// -- pre / post

template <typename T>
void Reverse(T First, T Last) {
  while ((First != Last) && (First != (--Last))) {
    auto Value = *First;
    *First = *Last;
    *Last = Value;

    ++First;
  }
}

// Random Access iterator: Bidirectional iterator
// Requirements:
// !=  ==
// * rvalue / lvalue
// ++ pre / post 
// --  pre / post
// + - (iterator + 3) (iterator - 3)
// += -= (iterator += 3) (iterator -= 3)
// iter1 iter2 (iter1 - iter2)

template <typename T, size_t N>
T* Begin(T (&Array)[N]) {
  return &Array[0];
}

Begin(Container &C ) {
  return C.begin();
}

template <typename T, size_t N>
T* End(T (&Array)[N]) {
  return &Array[N];
}

int main () {
  int array[] ={ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int second[10];

  std::vector<int> Vector{1, 2, 3, 4, 5, 6, 7, 8, 9}; // uniform initialization

  std::list<int> List{100, 200, 300, 400, 500};

  std::forward_list<int> FwList{800, 900, 700, 1000};

  Copy(std::begin(array), std::end(array), std::begin(second));

  for (int V: second) {
    std::cout << "[SECOND] " << V << "\n";
  }

  std::cout << *(Begin(array)) << *(End(array));

#if 0
  multiply<int> m;

  Begin(array);

  std::cout << accumulate(std::begin(array), std::end(array),  1, m) << '\n';
  std::cout << accumulate(std::begin(Vector), std::end(Vector), 1, m) << '\n';
#endif

  std::cout << "Array:\n ";
  Display(std::begin(array), std::end(array));

  std::cout << "Vector:\n";
  Display(std::begin(Vector), std::end(Vector));

  std::cout << "List:\n";
  Display(std::begin(List), std::end(List));

  std::cout << "FwList:\n";
  Display(std::begin(FwList), std::end(FwList));


  Replace(std::begin(List), std::end(List), M<int>{});
  std::cout << "After transform: \n";
  Display(std::begin(List), std::end(List));

//  Reverse(std::begin(FwList), std::end(FwList));
  for (int V: FwList) {
    std::cout << "[REVERSE] " << V << std::endl;
  }


  auto iter = std::begin(Vector);

 /* iter = iter + 4;

  iter =  iter - 3;
*/
  auto end = std::end(Vector);
  std::cout << (end - iter);

 return 0;
}


// input iterators
// output iterators
// forward iterators 
// bidirectional iterators
// random access iterators 
// contiguous iterators
