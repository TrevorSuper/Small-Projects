#include "Clock.h"
#include <iostream>
Clock::Clock(){
  military_hours = 0, minutes = 0, seconds = 0;
  military_time = true;
}
Clock::Clock(unsigned short int clock_military_hours, unsigned short int clock_minutes, unsigned short int clock_seconds, bool clock_format){
  if ( ( clock_military_hours >= 0 && clock_military_hours <= 23 ) && ( clock_minutes >= 0 && clock_minutes <= 59 ) && ( clock_seconds >= 0 && clock_seconds <= 59 ) == true ){
    military_hours = clock_military_hours;
    minutes = clock_minutes;
    seconds = clock_seconds;
    military_time = clock_format;
  } else {
    std::cerr << "Invalid time input.\n";
  }
}
Clock::~Clock(){

}
void Clock::toggleFormat(){ // toggles between standard time and military time
  //std::cout << "\n before toggle " << military_time;
  if ( military_time == true ) { military_time = false; }
  else { military_time = true; }
  //std::cout << "\n after toggle " << military_time << "\n";
}
void Clock::show(){ // there are 86400 seconds in one day
  if ( military_time == true ) {
    if ( military_hours == 0 ) {
      std::cout << "00:";
    }
    else if ( military_hours !=0 ) {
      std::cout << military_hours << ":";
    }
    if ( minutes <= 9 ) {
      std::cout << "0" << minutes << ":";
    }
    else if ( minutes >= 10 ) { 
      std::cout << minutes << ":";
    }
    if ( seconds <= 9 ) {
      std::cout << "0" << seconds << "\n";
    }
    else if ( seconds >= 10 ) { 
      std::cout << seconds << "\n";
    }
  }
  if ( military_time == false ) { 
    if ( military_hours == 0 || military_hours == 12 ) {
      std::cout << "12:";
    }
    else if ( military_hours >= 1 && military_hours <= 11 ) {
      std::cout << military_hours << ":";
    }
    else if ( military_hours >= 13 && military_hours <= 23 ) {
      std::cout << military_hours - 12 << ":";
    }
    if ( minutes <= 9 ) {
      std::cout << "0" << minutes << ":";
    }
    else if ( minutes >= 10 ) { 
      std::cout << minutes << ":";
    }
    if ( seconds <= 9 ) {
      std::cout << "0" << seconds;
    }
    else if ( seconds >= 10 ) { 
      std::cout << seconds;
    }
    if ( military_hours >= 0 && military_hours <= 11 ) {
      std::cout << " AM\n";
    }
    else if ( military_hours >= 12 && military_hours <= 23 ) {
      std::cout << " PM\n";
    }
  }
}
void Clock::tick(){
  if ( seconds != 59 ) { 
    seconds = seconds + 1;
  }
  else if ( seconds == 59 && minutes != 59 ) {
    seconds = 0;
    minutes = minutes + 1;
  }
  else if ( seconds == 59 && minutes == 59 && military_hours != 23 ) {
    seconds = 0;
    minutes = 0;
    military_hours = military_hours + 1;
  }
  else if ( seconds == 59 && minutes == 59 && military_hours == 23) {
    seconds = 0, minutes = 0, military_hours = 0;
  }
}
int main(){
  std::cout << "Clock 7: \n";
  /*
  I used one clock object and ticked it for two full twenty four hour periods,
  one in military time and one in standard time so I know I got the formatting
  correct for all seconds of the day. Based on my research how these times are
  printed here are how the times are represented on standard clocks. I did not
  read all 172,800 lines of print statements, I just checked to see if the
  clock object was ticking properly in the major areas. What I mean is that once
  seconds reach 59 they reset to zero and the minute ticks up by one. When 
  seconds and minutes reach 59 each they reset to zero and the hour ticks.
  When military time reaches 23:59:59 it ticks to 00:00:00 and not 24:00:00.
  */
  Clock c7( 23, 00, 00, true); // time should be entered in military time
  for ( int i = 0; i < 86400; i++ ){
    c7.show();
    c7.tick();
  }
  c7.toggleFormat();
  for ( int i = 0; i < 84600; i++){
    c7.show();
    c7.tick();
  }
  std::cout << "\nClock 8\n";
  Clock c8;
  c8.show();
  c8.tick();
  c8.show();
  c8.toggleFormat();
  c8.show();
  c8.tick();
  c8.show();
  c8.toggleFormat();
  c8.show();
  c8.tick();
  c8.show();
  std::cout << "\nClock 9\n";
  Clock c9( 99, 99, 99, true );
  return 0;
}