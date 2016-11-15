/*
 * File name:   Gps.h
 * Author:      Brandon Fry
 * Description: This is the header file for the GPS
 *              module.
 */

#ifndef Gps_h
#define Gps_h

#include "arduino.h"

class Gps
{
  public:
    Gps();
    void Initialize();
    void Default();
    void ReadCurrentLocation();
};

#endif
