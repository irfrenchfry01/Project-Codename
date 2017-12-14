/*
 * File name:   FlightCtrl.h
 * Author:      Garrett Clay
 * Description: flight controller
 */

#ifndef FLIGHTCTRL_H
#define FLIGHTCTRL_H

#define PITCH_TOLERANCE   0.01    //in degrees
#define ZERO              0.0

#include <stdint.h>
#include "motor.h"

class FlightCtrl
{
  public:
    double CalcRoll(void);
    double CalcPitch(void);
    double GetRoll(void);
    double GetPitch(void);

    double GetGx(void);
    double GetGy(void);
    
    double CalcAngularVelFromPitch(double Pitch, double DeltaTime);

    void CalcMSpeed(MotorId_t Motor, int32_t kRoll, int32_t kPitch);

  private:
    double pitch = 0.00;  //rotation around y axis
    double roll = 0.00;   //rotation around x axis
    double yaw = 0.00;    //rotoation around z axis
};



#endif
