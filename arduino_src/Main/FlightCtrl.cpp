/*
 * File name:   FlightCtrl.c
 * Author:      Garrett Clay
 * Description: flight controller
 */

 #include "FlightCtrl.h"
#include <math.h>
#include <Wire.h>


//double pitch, roll;
//double ax, ay, az;  //accelerometer input

/**
* @brief calculate roll using accelerometer data
* 
* param[in] ax  accelerometer data in x-axis (units m/s^2)
* param[in] ay  accelerometer data in y-axis (units m/s^2)
* param[in] az  accelerometer data in z-axis (units m/s^2)
* 
* retval    roll  angle of roll in degrees
*/
double FlightCtrl::CalcRoll(double ax, double ay, double az)
{
  this->roll  = (atan2(ay, az)*180.0)/M_PI;
  return this->roll;
}

/**
* @brief calculate pitch using accelerometer data
* 
* param[in] ax  accelerometer data in x-axis (units m/s^2)
* param[in] ay  accelerometer data in y-axis (units m/s^2)
* param[in] az  accelerometer data in z-axis (units m/s^2)
* 
* retval    pitch angle of pitch in degrees
*/
double FlightCtrl::CalcPitch(double ax, double ay, double az)
{
  this->pitch = (atan2(ax, sqrt(ay*ay + az*az))*180.0)/M_PI;
  return pitch;
}

/**
* @brief convert gyro x-axis data to deg/s
* 
* param[in] GxRaw  accelerometer data in x-axis in rad/s
* 
* retval    GxDeg  gyro x-axis data in deg/s
*/
double FlightCtrl::GetGx(double GxRaw)
{
  double GxDeg = ((GxRaw *180)/M_PI);
  return GxDeg;
}

//*******************************************
// below, deprecated code - depends on needs
//*******************************************
double FlightCtrl::GetRoll(void)
{
  return this->roll;
}

double FlightCtrl::GetPitch(void)
{
  return this->pitch;
}

