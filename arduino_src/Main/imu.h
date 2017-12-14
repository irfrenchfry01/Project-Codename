/*
 * File name:   imu.h
 * Author:      Garrett Clay
 * Description: IMU (inertial measurement unit) header file.
 *              Includes accelerometer, gyro and magnetometer control.
 */
/*
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
 */
#ifndef IMU_H
#define IMU_H

class Imu{
  public:
   void displaySensorDetails(void);
   void InitImu(void);
   void ReadAndPrintImuData(void);
   double GetAx(void);
   double GetAy(void);
   double GetAz(void);
   
   double GetGx(void);
   double GetGy(void);
   double GetGz(void);

   double GetMx(void);
   double GetMy(void);
   double GetMz(void);
};

#endif
