#ifndef CLOCK_H
#define CLOCK_H
class Clock { // base class
  protected:
  unsigned short int minutes, seconds, military_hours; // military_hours stores the hour mark in 0 to 23 format
  bool military_time; // false = 12 hour format 6:41:19PM, true = 24 hour format 18:41:19
  char *city_name;
};
#endif