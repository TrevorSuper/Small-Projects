/*       bytes       Minumum Value                             Maximum Values
uint64_t   8    |         0                             | 18,446,744,073,709,551,615 (or 2^64 − 1)
int64_t    8    | -9,223,372,036,854,775,808 (or -2^63) | 9,223,372,036,854,775,807 (or 2^63 − 1)
uint32_t   4    |         0                             | 4,294,967,295 (or 2^32 − 1)
int32_t    4    | -2,147,483,648 (or -2^31)             | 2,147,483,647 (or 2^31 − 1)
uint16_t   2    |         0                             | 65,535 (or 2^16 − 1)
int16_t    2    | -32,768 (or -2^15)                    | 32,767 (or 2^15 − 1)
uint8_t    1    |         0                             | 255 (or 2^8 − 1)
int8_t     1    | -128 (or -2^7)                        | 127 (or 2^7 − 1)

The actual size of a size_t object is architecture-dependent, as it is required to
be large enough to express the maximum size of any possible object on a given system.
*/
#include <iostream>

int main(){
  int32_t a = 2147483645;
  int32_t b = -2147483646;
  uint16_t c = 65533;
  for (uint8_t i = 0; i < 4; i++){
    std::cout << "a " << a << "\n" << "b " << b << "\n" << "c " << c << "\n";
    a = a + 1;
    b = b - 1;
    c = c + 1;
  }

  struct StudentA {
    std::string name;
    double eecs_281_score;
    int64_t enrollment_timestamp;
    char letter_grade;
    bool has_passed;
    bool has_applied_for_ia;
  };

  struct StudentB {
    bool has_passed;
    double eecs_281_score;
    char letter_grade;
    std::string name;
    bool has_applied_for_ia;
    int64_t enrollment_timestamp;
  };

  std::cout << "sizeof(StudentA) " << sizeof(StudentA) << "\n" << "sizeof(StudentB) " << sizeof(StudentB) << "\n";
  /*
  you can ensure that your object minimizes its memory footprint by following this
  simple rule: when defining a custom object, you should list member variables in order
  of increasing or decreasing size
  */
  return 0;
}