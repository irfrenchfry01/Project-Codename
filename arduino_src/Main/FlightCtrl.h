/*
 * File name:   FlightCtrl.h
 * Author:      Garrett Clay
 * Description: flight controller
 */

 #ifndef FLIGHTCTRL_H
 #define FLIGHTCTRL_H

#include <stdint.h>


class FlightCtrl
{
  public:
    double CalcRoll(double ax, double ay, double az);
    double CalcPitch(double ax, double ay, double az);
    double GetRoll(void);
    double GetPitch(void);

    double GetGx(double GxRaw);
    

  private:
    double pitch = 0.00;  //rotation around y axis
    double roll = 0.00;   //rotation around x axis
    double yaw = 0.00;    //rotoation around z axis
};








 #endif
