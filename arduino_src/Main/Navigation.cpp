/*
 * File name:   Navigation.cpp
 * Author:      Brandon Fry
 * Description: Navigation controller
 */

 //Include files
 #include "Navigation.h"
 #include "Gps.h"

 //Global parameters
 //Adafruit_GPS Gps(&GPSSerial);
 //uint32_t timer = millis();
 Gps gps;
 
 void Navigation::NavInitialize()
 {
    gps.Initialize();
 }
 
 void Navigation::GetCurrentLocation()
 {
  /*
    //while(true)
    //{
    char c = Gps.read();
    if (Gps.newNMEAreceived()) 
    {
      //Serial.println(Gps.lastNMEA());
      if(!Gps.parse(Gps.lastNMEA()))
      {
        Serial.print("Unable to parse NMEA packet");
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
        
    if(Gps.fix)
    { 
      Serial.print(Gps.latitude, 4);
      Serial.print(Gps.longitude, 4);
    }
    else
    {
      Serial.print("No fix acheived\n");
    }
    //}
    */
 }

