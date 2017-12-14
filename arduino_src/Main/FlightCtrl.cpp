/*
 * File name:   FlightCtrl.c
 * Author:      Garrett Clay
 * Description: flight controller
 */

#include "FlightCtrl.h"
#include <math.h>
#include <Wire.h>
#include "imu.h"

motor mtr;
Imu Imu;

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
double FlightCtrl::CalcRoll(void)
{
  double ax = Imu.GetAx();
  double ay = Imu.GetAy();
  double az = Imu.GetAz();
  
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
double FlightCtrl::CalcPitch(void)
{
  double ax = Imu.GetAx();
  double ay = Imu.GetAy();
  double az = Imu.GetAz();
  
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
double FlightCtrl::GetGx(void)
{
  double GxDeg = 0;
  double GxRaw = 0;
   
  GxRaw = Imu.GetGx();  //accelerometer data in x-axis in rad/s

  GxDeg = ((GxRaw * 180)/M_PI);
  
  return GxDeg;
}

/**
* @brief convert gyro y-axis data to deg/s
*
* retval    GxDeg  gyro y-axis data in deg/s
*/
double FlightCtrl::GetGy(void)
{
  double GyDeg = 0;
  double GyRaw = 0;
   
  GyRaw = Imu.GetGy();  //accelerometer data in y-axis in rad/s

  GyDeg = ((GyRaw * 180)/M_PI);
  
  return GyDeg;
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
double FlightCtrl::CalcAngularVelFromPitch(double Pitch, double DeltaTime)
{
  /*  compile issue
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
  */
  return 0;
}


// things to experiment with
// 1. base value
// 2. coeff scale
/**
 * @brief calculate motor speeds based on roll, pitch (and yaw, eventually?)
 * 
 * @param[in] Motor   motor (front left, front right, etc.) to set speed of
 * @param[in] kRoll   Kalman filtered roll in degrees
 * @param[in] kPitch  Kalman filtered pitch in degrees
 * 
 */
void FlightCtrl::CalcMSpeed(MotorId_t Motor, int32_t kRoll, int32_t kPitch)
{
  uint8_t CurMotorSpeed = 0;
  uint8_t BaseSpeed = 0;
  int8_t PitchCoef = 0;
  int8_t RollCoef = 0;

  BaseSpeed = MTR_BASE;

  if(MOTOR_FL == Motor)
  {
    PitchCoef = MTR_FL_PITCH_COEF;
    RollCoef = MTR_FL_ROLL_COEF;
  }
  else if(MOTOR_FR == Motor)
  {
    PitchCoef = MTR_FR_PITCH_COEF;
    RollCoef = MTR_FR_ROLL_COEF;
  }
  else if(MOTOR_BL == Motor)
  {
    PitchCoef = MTR_BL_PITCH_COEF;
    RollCoef = MTR_BL_ROLL_COEF;
  }
  else if(MOTOR_BR == Motor)
  {
    PitchCoef = MTR_BR_PITCH_COEF;
    RollCoef = MTR_BR_ROLL_COEF;
  }

  CurMotorSpeed = BaseSpeed + (kRoll * RollCoef) + (kPitch * PitchCoef);
  
  mtr.SetMotorSpeed(Motor, CurMotorSpeed);
  //Serial.print(CurMotorSpeed);
}

//*******************************************
// below, deprecated code - depends on needs
//*******************************************
/* compile issue
double FlightCtrl::GetRoll(void)
{
  return this->roll;
}

double FlightCtrl::GetPitch(void)
{
  return this->pitch;
}
*/

