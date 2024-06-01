#include <iostream>
#include <cstdlib>        
int* duplicate( int old_array[], unsigned int &dynam_size ){ // there is no resizing of a dynamic array allocation, must manually copy the array to a new dynamic array and delete the old dynamic array
  int *new_array = new int[2 * dynam_size];
  for( int i = 0; i < dynam_size; i++ ){
    new_array[i] = old_array[i];
    new_array[dynam_size + i] = old_array[i];
  }
  //std::cout << "old_array: "  << old_array << "\n"; // same address ( 1 / 4 )
  //std::cout << "new_array: " << new_array << "\n"; // same address ( 2 / 4 )
  //delete[] old_array;
  //old_array = nullptr;
  return new_array;
}
int* generate( unsigned int &n ){
  //std::cout << n << "\n";
  int *dynam = new int[n];
  for( int i = 0; i < n; i++ ){
    dynam[i] = rand() % n;
  }
  /*
  more debugging prints
  std::cout << "all of the dynam array" << "\n";
  for( int i = 0; i < n; i++ ){
    std::cout << dynam[i] << "\n";
  }*/
  //std::cout << "dynam: " << dynam << "\n"; // same address ( 3 / 4 )
  //std::cout << "*dynam: " << *dynam << "\n";
  return dynam;
}
void display( int dynam[], unsigned int &dynam_size ){
  std::cout << "The dyamically allocated array with 8 integers per line: \n";
  //std::cout << "dynam_size: " << dynam_size << "\n";
  for( int j = 0; j < dynam_size; j++ ){
    std::cout << dynam[j] << " "; // comment for future self part 2: no * needed to dereference from the array to print numbers instead of addresses, this is strange
    if( (j + 1) % 8 == 0 ){
      std::cout << "\n";
    }
  }
  std::cout << "\n";
}
int main(){
  int k; // start with int to allow for the prevention of a negative integer entered by the user crashing the program
  do{
    if(std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(256,'\n');
    }
    std::cout << "Enter an integer greater than zero: ";
    std::cin >> k;
  } while( k <= 0 );
  unsigned int n = k; // transfer int value to unsigned int to meet requirement
  int *ptr_dynam = generate(n);

  // debugging print statements
  //std::cout << "ptr_dynam: " << ptr_dynam << "\n"; // prints the address // same address ( 4 / 4 )
  //std::cout << "*ptr_dynam: " << *ptr_dynam << "\n"; // prints the number
  display( ptr_dynam, n ); // comment for future self: passing the address into display seems to be sufficient for then printing the numbers of the array
  int *duplicated_array = duplicate( ptr_dynam, n );
  n = 2 * n;
  display( duplicated_array, n );
  delete[] ptr_dynam;
  delete[] duplicated_array; // delete last dynamic array since program is ending
  ptr_dynam = nullptr;
  duplicated_array = nullptr; // assigning a dynamic allocation to nullptr after deleting is good practice ??
  //std::cout << ptr_dynam << "\n";
  return 0;
}