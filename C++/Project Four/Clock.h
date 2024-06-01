#ifndef CLOCK_H
#define CLOCK_H

class Clock {
  private:
  unsigned short int minutes, seconds, military_hours; // military_hours stores the hour mark in 0 to 23 format
  bool military_time; // false = 12 hour format 6:41:19PM, true = 24 hour format 18:41:19
  public:
  Clock();
  Clock(unsigned short int clock_military_hours, unsigned short int clock_minutes, unsigned short int clock_seconds, bool military_time);
  ~Clock();
  void toggleFormat();
  void show();
  void tick();
};
#endif