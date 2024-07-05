#include <iostream>

void swap(int32_t &x, int32_t &y){
  int32_t temp;
  temp = x;
  x = y;
  y = temp;
}

int main(){
  int32_t x = 5;
  int32_t y = 4;
  swap(x, y);
  std::cout << "x " << x << " y " << y << "\n";
  std::cout << "&x " << &x << " &y " << &y << "\n";
  
  int32_t a = 6;
  int32_t &b = a; // b can not be assigned to refer to another object until b goes out of scope
  a = 7;
  std::cout << "a " << a << " b " << b << "\n" << "&a " << &a << " &b " << &b << "\n";

  int32_t c = 281;
  int32_t *ptr = &c;
  std::cout << "ptr" << ptr << "\n" << "*ptr " << *ptr << "\n";

  /*
  1. If a pointer is not explicitly initialized, it is default initialized with an undefined value. Dereferencing a default-initialized pointer results in undefined behavior!
  2. It is possible for a pointer to outlive the object it is pointing to, which could also result in undefined behavior.
  the get_address() function below returns a pointer to a local copy of x (because x is not passed by reference). This local copy goes out
  of scope after the function returns, so attempting to dereference its address results in undefined behavior.
  int* get_address(int x) {
    return &x; // returns pointer to x, but x goes out of scope after function returns
  } // get_address()
  int main() {
    int val = 280;
    int* ptr = get_address(x);
    std::cout << *ptr << std::endl; // undefined behavior
  } // main()
  In C++, there is a special object known as a null pointer that can be used to designate pointers that do not point to a valid object. Any pointer
  (regardless of type) can be assigned to a null pointer value using the nullptr keyword
  Similar to pointers that are default initialized without a value, dereferencing a nullptr also results in undefined behavior.
  */
}