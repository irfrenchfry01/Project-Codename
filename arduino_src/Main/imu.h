/*
 * File name:   imu.h
 * Author:      Garrett Clay
 * Description: IMU (inertial measurement unit) header file.
 */
/*
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>
 */
#ifndef imu_h
#define imu_h

class Imu{
  public:
   void displaySensorDetails(void);
   void InitImu(void);
   void ReadAndPrintImuData(void);
};

#endif
