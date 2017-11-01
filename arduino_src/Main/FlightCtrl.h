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


class FlightCtrl
{
  public:
    double CalcRoll(double ax, double ay, double az);
    double CalcPitch(double ax, double ay, double az);
    double GetRoll(void);
    double GetPitch(void);

    double GetGx(double GxRaw);
    
    void PitchCtrl(double Pitch);

    double CalcAngularVelFromPitch(double Pitch, double DeltaTime);

  private:
    double pitch = 0.00;  //rotation around y axis
    double roll = 0.00;   //rotation around x axis
    double yaw = 0.00;    //rotoation around z axis
};



#endif
