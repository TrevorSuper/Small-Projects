#include <iostream>

int main(){
  int *ptr = new int{281}; // dynamically allocate memory, also known as manual memory management
  std::cout << *ptr << "\n";
  delete ptr; // free up the memory to prevent a leak
  ptr = nullptr; // handle the dangling pointer
  // ptr is a local variable that is allocated on the stack, and it points to a memory address on the heap
  return 0;
}