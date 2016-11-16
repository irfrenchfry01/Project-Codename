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
  //Definitions
  #define preamble "$"
  #define talkerID "PMTK"
  #define dataEnd  "*"
  #define pktEnd   "\r\n"

  private enum pktTypes {
    PMTK_ACK,
    PMTK_SYS_MSG
  };
  
  public:
    Gps();
    void Initialize();
    void Default();
    void ReadCurrentLocation();
    void WritePacket(String cmd);
};

#endif
