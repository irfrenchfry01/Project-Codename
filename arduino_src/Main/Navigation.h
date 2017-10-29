/*
 * File name:   Navigation.h
 * Author:      Brandon Fry
 * Description: Navigation Controller
 */

 #ifndef NAVIGATION_H
 #define NAVIGATION_H

 #include "arduino.h"
 
 #define MAXCOORDINATES 10

 struct DD_COORDINATE {
  int latDegrees;
  float latDecimal;
  int longDegrees;
  float longDecimal;
 };

class Navigation{
  public:
    void NavInitialize();
    void GetCurrentLocation();
    bool AddCoordinate(String latitude, String longitude);
    float DDMToDDConversion(float ddmValue);
  private:
  
};

#endif
