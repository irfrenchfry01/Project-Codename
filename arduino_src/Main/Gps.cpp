/*
 * File name:   Gps.cpp
 * Author:      Brandon Fry
 * Description: This is the source code for the
 *              GPS module
 */

 #include <arduino.h>
 #include "Gps.h"

 #define gpsSerial Serial1

 Gps::Gps()
 {
 }

 void Gps::Initialize()
 {
   //Initialization code for the serial interface
   gpsSerial.begin(9600);
 }

 void Gps::Default()
 {
   //Code to set the GPS to a default state
 }

 void Gps::ReadCurrentLocation()
 {
 }

 void Gps::WritePacket()
 {
   gpsSerial.print(cmd);
 }

 string Gps::GetPktTypeString(pktTypes pktType)
 {
   switch(pktType)
   {
     case PMTK_ACK: return
   }
 }

