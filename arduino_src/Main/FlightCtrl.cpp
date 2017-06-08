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

/**
 * @brief adjusts drone pitch 
 * 
 * @param[in] Pitch       angle between FL/FR and horizontal (degrees)
 */
void PitchCtrl(double Pitch)
{
  // if drone is tilted backwards
  if(Pitch > (ZERO + PITCH_TOLERANCE))
  {
    //decrease FL/FR motor speeds
    //increase BL/BR motor speeds
  }
  else if(Pitch < (ZERO - PITCH_TOLERANCE))
  {
    //increase FL/FR motor speeds
    //decrease BL/BR motor speeds
  }
  else
  {
    //don't. change. anything. 
  }


}

/**
 * @brief calculate angualr velocity from kalman filtered pitch
 * 
 * must be called at least twice
 * 
 * @param[in]   Pitch       current pitch angle in degrees
 * @param[in]   DeltaTime   change in time between pitch measurements (seconds)
 * 
 * @retval      AngVel  angular velocity in deg/sec
 */
double CalcAngularVelFromPitch(double Pitch, double DeltaTime)
{
  static double PrevPitch = 0;
  static bool InitVal = true;
  double AngVel = 0;

  if(true == InitVal)
  {
    PrevPitch = Pitch;
    InitVal = false;
  }
  else
  {
    //store new value
    PrevPitch = PrevPitch - Pitch;
  
    //calculate angular velocity
    AngVel = PrevPitch / DeltaTime;
  }

  return AngVel;
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

