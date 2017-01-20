/*
 * File name:   Gps.cpp
 * Author:      Brandon Fry
 * Description: This is the source code for the
 *              GPS module
 */

 #include <arduino.h>
 #include "Gps.h"

 #define gpsSerial Serial1

 //Gps::Gps()
 //{
 //}

 class Gps
 {
  public:
  void InitGps();
  void DefaultState();
  //void ReadCurrentLocation();
  void WritePacket(String cmd);
 };

 void Gps::InitGps()
 {
   //Initialization code for the serial interface
   gpsSerial.begin(9600);
 }

 void Gps::DefaultState()
 {
   //Code to set the GPS to a default state
 }

 //void Gps::ReadCurrentLocation()
 //{
 //}

 void Gps::WritePacket(String cmd)
 {
   gpsSerial.print(cmd);
 }

/*
 string Gps::GetPktTypeString(pktTypes pktType)
 {
   switch(pktType)
   {
     case PMTK_ACK: return
   }
 }
*/
