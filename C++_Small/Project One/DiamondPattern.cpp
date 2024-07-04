#include <iostream>
int main(){
  int n;
  do{
    if ( std::cin.fail() ){
      std::cin.clear();
      std::cin.ignore(256,'\n');
    }
    std::cout << "Enter an integer greater than zero: ";
    std::cin >> n;
  } while ( n <= 0 );
  std::cout << "Input Accepted, Printing Diamond.\n";
  for ( int i = 0; i <= n; ++i ){
    for ( int j = 0; j < n-i; ++j ){
      std::cout << " ";
    }
    for ( int j=0; j < 2*i+1; ++j ){
      std::cout << "*";
    }
    std::cout << "\n";
  }
  for ( int i = n-1; i >= 0; --i ){
    for ( int j = 0; j < n-i; ++j ){
      std::cout << " ";
    }
    for (int j = 0; j < 2*i+1; ++j ){
      std::cout << "*";
    }
    std::cout << "\n";
  }
  return 0;
}