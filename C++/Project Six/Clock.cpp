#include "CityClock.h"
#include <cstring>
#include <iostream>
#include <algorithm>
CityClock::CityClock(){ // default constructor
  std::cout << "Default constructor\n";
  military_hours = 0, minutes = 0, seconds = 0;
  military_time = true;
  city_name = new char[ strlen( "Rochester, Michigan" ) + 1 ];
  strcpy( city_name, "Rochester, Michigan" );
}
CityClock::CityClock( unsigned short int clock_military_hours, unsigned short int clock_minutes, unsigned short int clock_seconds, bool clock_format, const char *name ){ // paramaterized constructor
  if ( ( clock_military_hours >= 0 && clock_military_hours <= 23 ) && ( clock_minutes >= 0 && clock_minutes <= 59 ) && ( clock_seconds >= 0 && clock_seconds <= 59 ) == true ){
    std::cout << "Paramaterized Constructor\n";
    military_hours = clock_military_hours;
    minutes = clock_minutes;
    seconds = clock_seconds;
    military_time = clock_format;
    //std::cout << *name;
    city_name = new char[ strlen( name ) + 1 ];
    strcpy(city_name, name);
    //std::cout << "city_name: " << city_name << "\n";
  } else {
    std::cerr << "Invalid time input.\n";
  }
}
CityClock::~CityClock(){ // destructor
  std::cout << "Destructor\n";
  delete[] city_name;
}
CityClock::CityClock( CityClock &obj ){ // copy constructor
  std::cout << "copy constructor\n";
  minutes = obj.minutes;
  seconds = obj.seconds;
  military_hours = obj.military_hours;
  military_time = obj.military_time;
  city_name = new char[ strlen( obj.city_name ) + 1 ];
  strcpy( city_name, obj.city_name );
}
CityClock::CityClock( CityClock && temp ){ // move constructor
  std::cout << "move constructor\n";
  city_name = temp.city_name;
  temp.city_name = nullptr;
  seconds = temp.seconds;
  minutes = temp.minutes;
  military_hours = temp.military_hours;
  military_time = temp.military_time;
}
CityClock & CityClock::operator=( const CityClock &right ){ // copy assignment operator
  std::cout << "copy assignment operator\n";
  if ( this != &right ){
    city_name = new char[ strlen( right.city_name ) + 1 ];
    strcpy( city_name, right.city_name );
    seconds = right.seconds;
    minutes = right.minutes;
    military_hours = right.military_hours;
    military_time = right.military_time;
  }
  return *this;
}
CityClock & CityClock::operator=( CityClock && right ){ // move assignment operator
  std::cout << "move assignment operator\n";
  if ( this != &right ){
    std::swap( city_name, right.city_name );
    std::swap( seconds, right.seconds );
    std::swap( minutes, right.minutes );
    std::swap( military_hours, right.military_hours );
    std::swap( military_time, right.military_time );
  }
  return *this;
}
void CityClock::TypeConversion(){ // converting dynamic c-string to c++ string object
  std::string cppString( city_name );
  std::cout << "c++ string object from type conversion: " << cppString << "\n";
}
CityClock CityClock::operator+( int secondsToAdd ){ // overloaded addition operator
  std::cout << "overloaded addition operator\n";
  CityClock result(*this); // create a copy of the current object
  int totalSeconds = result.seconds + secondsToAdd;
  result.seconds = totalSeconds % 60; // update seconds, handle overflow
  int minutesToAdd = totalSeconds / 60;
  totalSeconds = result.minutes + minutesToAdd;
  result.minutes = totalSeconds % 60; // update minutes, handle overflow
  int hoursToAdd = totalSeconds / 60;
  result.military_hours = (result.military_hours + hoursToAdd) % 24; // update hours, handle overflow
  return result;
}
std::ostream& operator<<(std::ostream& os, const CityClock& clock) {
  std::cout << "overloaded ostream insertion operator\n";
  os << clock.city_name << " - ";
  if (clock.military_time) {
    if (clock.military_hours < 10) { os << '0'; }
    os << clock.military_hours << ":";
    if (clock.minutes < 10) { os << '0'; }
    os << clock.minutes << ":";
    if (clock.seconds < 10) { os << '0'; }
    os << clock.seconds;
  } else {
    int display_hours = clock.military_hours;
    const char* meridiem = " AM";
    if (display_hours >= 12) {
      meridiem = " PM";
      if (display_hours > 12) { display_hours -= 12; }
    }
    if (display_hours == 0) { display_hours = 12; }
    if (display_hours < 10) { os << '0'; }
    os << display_hours << ":";
    if (clock.minutes < 10) { os << '0'; }
    os << clock.minutes << ":";
    if (clock.seconds < 10) { os << '0'; }
    os << clock.seconds << meridiem;
  }
  return os;
}
void CityClock::toggleFormat(){ // toggles between standard time and military time
  //std::cout << "\n before toggle " << military_time;
  if ( military_time == true ){ military_time = false; }
  else { military_time = true; }
  //std::cout << "\n after toggle " << military_time << "\n";
}
void CityClock::show(){ // there are 86400 seconds in one day
  std::cout << city_name << " - ";
  if ( military_time == true ){
    if ( military_hours == 0 ){
      std::cout << "00:";
    }
    else if ( military_hours !=0 ){
      std::cout << military_hours << ":";
    }
    if ( minutes <= 9 ){
      std::cout << "0" << minutes << ":";
    }
    else if ( minutes >= 10 ){ 
      std::cout << minutes << ":";
    }
    if ( seconds <= 9 ){
      std::cout << "0" << seconds << "\n";
    }
    else if ( seconds >= 10 ){ 
      std::cout << seconds << "\n";
    }
  }
  if ( military_time == false ){ 
    if ( military_hours == 0 || military_hours == 12 ){
      std::cout << "12:";
    }
    else if ( military_hours >= 1 && military_hours <= 11 ){
      std::cout << military_hours << ":";
    }
    else if ( military_hours >= 13 && military_hours <= 23 ){
      std::cout << military_hours - 12 << ":";
    }
    if ( minutes <= 9 ){
      std::cout << "0" << minutes << ":";
    }
    else if ( minutes >= 10 ){ 
      std::cout << minutes << ":";
    }
    if ( seconds <= 9 ){
      std::cout << "0" << seconds;
    }
    else if ( seconds >= 10 ){ 
      std::cout << seconds;
    }
    if ( military_hours >= 0 && military_hours <= 11 ){
      std::cout << " AM\n";
    }
    else if ( military_hours >= 12 && military_hours <= 23 ){
      std::cout << " PM\n";
    }
  }
  //std::cout << "city_name " << city_name << "\n";
}
void CityClock::tick(){
  if ( seconds != 59 ){ 
    seconds = seconds + 1;
  }
  else if ( seconds == 59 && minutes != 59 ){
    seconds = 0;
    minutes = minutes + 1;
  }
  else if ( seconds == 59 && minutes == 59 && military_hours != 23 ){
    seconds = 0;
    minutes = 0;
    military_hours = military_hours + 1;
  }
  else if ( seconds == 59 && minutes == 59 && military_hours == 23){
    seconds = 0, minutes = 0, military_hours = 0;
  }
}
int main(){
  CityClock c1; // default constructor
  for ( int i = 0; i < 4; i++ ){
    c1.show();
    c1.tick();
  }
  c1.toggleFormat();
  c1.TypeConversion();
  for ( int i = 0; i < 4; i++ ){
    c1.show();
    c1.tick();
  }
  CityClock c2( 23, 00, 00, true, "New York"); // paramaterized constructor
  for ( int i = 0; i < 4; i++ ){
    c2.show();
    c2.tick();
  }
  c2.toggleFormat();
  c2.TypeConversion();
  for ( int i = 0; i < 4; i++ ){
    c2.show();
    c2.tick();
  }
  CityClock c3( c2 );
    for ( int i = 0; i < 4; i++ ){
    c3.show();
    c3.tick();
  }
  c3.toggleFormat();
  c3.TypeConversion();
  for ( int i = 0; i < 4; i++ ){
    c3.show();
    c3.tick();
  }
  CityClock c4 = c3; // copy constructor call
  for ( int i = 0; i < 4; i++ ){
    c4.show();
    c4.tick();
  }
  CityClock c5( 11, 51, 00, false, "Black Hills, South Dakota" );
  for ( int i = 0; i < 4; i++ ){
    c5.tick();
    c5.show();
  }
  CityClock c6;
  c6.show();
  c6 = c5; // calling copy assignment operator
  for ( int i = 0; i < 4; i++ ){
    c6.tick();
    c6.show();
  }
  c6.TypeConversion(); // another call of TypeConversion
  std::cout << "showing clock 5 again: ";
  c5.show();
  CityClock c7( 11, 23, 00, false, "Dry River, Arizona" );
  c7.toggleFormat();
  c7.show();
  CityClock c8 = c7 + 5; // overloaded addition operator call
  c8.show();
  c8.TypeConversion();
  CityClock c9 = c7 + 86400;
  c9.show();
  CityClock c10 = c7 + 7777;
  c10.show();
  CityClock c11( 12, 30, 45, false, "New York" );
  std::cout << c11 << std::endl; // overloaded insertion ostream operator call
  CityClock c12( 18, 52, 51, true, "Selfridge Air National Guard Base" );
  c12.show();
  CityClock c14( 12, 30, 45, true, "Ellesmere Island" );
  c14.show();
  CityClock c15;
  c15.show();
  c15 = std::move( c14 ); // move assignment operator call
  //std::cout << "break\n";
  CityClock c13( std::move( c12 ) ); // move constructor call
  //c12.show(); // do not call an object after it has been moved
  //std::cout << " work\n";
  c13.show(); // print 
  c15.show();
  return 0;
}