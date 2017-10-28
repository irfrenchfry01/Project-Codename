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
  if(!gps.dataLocked)
  {
    gps.dataLocked = true;
    Serial.println("Data Locked");
    Serial.println(gps.latitude);
    Serial.println(gps.longitude);
    gps.dataLocked = false;
    Serial.println("Data Unlocked");
    Serial.println("\n");
  }
 }
  
 void serialEvent1()
 {
    gps.ReadISR();
 }

