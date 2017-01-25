/*
 * File name:   Navigation.cpp
 * Author:      Brandon Fry
 * Description: Navigation controller
 */

 //Include files
 #include "Navigation.h"
 #include <Adafruit_GPS.h>

 //Definitions
 #define GPSSerial Serial1

 //Global parameters
 Adafruit_GPS Gps(&GPSSerial);
 uint32_t timer = millis();
 
 void Navigation::NavInitialize()
 {
  //Initialize the GPS unit to a 9600 baud rate
  Gps.begin(9600);
  
  //Turn on RMC (recommended minimum) and GGA (fix data) including altitude
  Gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  //Set the update rate
  Gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  Gps.sendCommand(PGCMD_ANTENNA);

  delay(1000);
  
  //Get the gps firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
 }
 
 void Navigation::GetCurrentLocation()
 {
    while(true)
    {
    char c = Gps.read();
    if (Gps.newNMEAreceived()) 
    {
      Serial.println(Gps.lastNMEA());
      if(!Gps.parse(Gps.lastNMEA()))
      {
        //Serial.print("Unable to parse NMEA packet");
        return;
      }
    }

    if (timer > millis()) timer = millis();
     
    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000) {
    
      Serial.println(Gps.hour, DEC);
      Serial.print("Fix: "); Serial.print((int)Gps.fix);
      if(Gps.fix)
      { 
        Serial.print(Gps.latitude, 4);
        Serial.print(Gps.longitude, 4);
      }
      else
      {
        Serial.print("No fix acheived\n");
      }
    }
    }
    
 }

