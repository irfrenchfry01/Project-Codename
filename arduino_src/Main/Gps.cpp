/*
 * File name:   Gps.cpp
 * Author:      Brandon Fry
 * Description: Interrupt based GPS module
 */

#include "Gps.h"

String inputString = "";
  
void Gps::Initialize()
{
  //Initialize the GPS unit to a 9600 baud rate
  GPSSerial.begin(9600);
  
  //Turn on RMC (recommended minimum) and GGA (fix data) including altitude
  SendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  //Set the update rate
  SendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  SendCommand(PGCMD_ANTENNA);

  //Allocate the space for input string
  inputString.reserve(200);

  Serial.println("GPS Initialize Complete");
}

//This function parses the NMEA packet and stores the values in the public variables to be used by the main program
void parseNMEAPacket(String nmeaPacket)
{
  
}

void serialEvent1()
{
  //Serial.println("ENTERING SERIAL EVENT");
  while(GPSSerial.available())
  {
    char inChar = (char)GPSSerial.read();
    inputString += inChar;

    if(inChar == '\n')
    {
      if(inputString.startsWith("$GPGGA"))
      {
        Serial.println(inputString);
      }
      inputString = "";
      //SendCommand(PMTK_ACK);
    }
  }
  //Serial.println("ENDING SERIAL EVENT");
}

void Gps::SendCommand(String cmd)
{
  GPSSerial.println(cmd);
}


