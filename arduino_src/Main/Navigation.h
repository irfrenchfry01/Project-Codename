/*
 * File name:   Navigation.h
 * Author:      Brandon Fry
 * Description: Navigation Controller
 */

 #ifndef NAVIGATION_H
 #define NAVIGATION_H

 #define MAXCOORDINATES 10
 
class Navigation{
  public:
    void NavInitialize();
    void GetCurrentLocation();
    bool AddCoordinate(float latitude, float longitude);
    float DDMToDDConversion(float ddmValue);
  private:
  
};

#endif
