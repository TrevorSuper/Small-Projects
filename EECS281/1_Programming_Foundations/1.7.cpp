#include <iostream>
namespace a{
  void print(){
    std::cout << "a\n";
  }
}

namespace b{
  void print(){
    std::cout << "b\n";
  }
}

int main(){
  {
    using namespace a;
    print();
  }

  {
    using namespace b;
    print();
  }

  a::print();
  b::print();

  {
    using a::print;
    print();
  }

  {
    using b::print;
    print();
  }
  return 0;
}