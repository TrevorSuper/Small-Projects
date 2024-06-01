#ifndef CITYCLOCK_H
#define CITYCLOCK_H
#include <ostream>
class CityClock {
  private:
  unsigned short int minutes, seconds, military_hours; // military_hours stores the hour mark in 0 to 23 format
  bool military_time; // false = 12 hour format 6:41:19PM, true = 24 hour format 18:41:19
  char *city_name;
  public:
  CityClock(); // default constructor
  CityClock(unsigned short int clock_military_hours, unsigned short int clock_minutes, unsigned short int clock_seconds, bool military_time, const char *name); // paramaterized constructor
  ~CityClock(); // destructor
  CityClock( CityClock &obj ); // Copy constructor
  CityClock( CityClock &&temp ); // move constructor
  CityClock & operator=( const CityClock &right ); // copy assignment operator
  CityClock & operator=( CityClock && right ); // move assignment operator
  CityClock operator+( int seconds ); // overloaded addition operator
  friend std::ostream& operator<< ( std::ostream& os, const CityClock& clock ); // overloaded ostream insertion operator
  void TypeConversion();
  void toggleFormat();
  void show();
  void tick();
};
#endif