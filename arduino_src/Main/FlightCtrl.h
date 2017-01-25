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


  private:
    double pitch = 0.00;  //rotation around x axis
    double roll = 0.00;   //rotation around y axis
    double yaw = 0.00;    //rotoation around z axis
};








 #endif
