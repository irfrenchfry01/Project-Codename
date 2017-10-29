/*
 * File name:   Navigation.cpp
 * Author:      Brandon Fry
 * Description: Navigation controller
 */

 //Include files
 #include "Navigation.h"
 #include "Gps.h"

 Gps gps;

 float flightPath[MAXCOORDINATES][2];
 int writeCount = 0;
 
 void Navigation::NavInitialize()
 {
    gps.Initialize();
 }

 bool Navigation::AddCoordinate(float latitude, float longitude)
 {
    if(writeCount < MAXCOORDINATES)
    {
      flightPath[writeCount][0] = latitude;
      flightPath[writeCount][1] = longitude;
      writeCount++;
      return true;
    }
    else 
    {
      Serial.println("Maximum coordinates reached");
      return false;
    }
 }
 
 void Navigation::GetCurrentLocation()
 {
  if(!gps.dataLocked)
  {
    gps.dataLocked = true;
    Serial.println(gps.latitude);
    Serial.println(gps.longitude);
    gps.dataLocked = false;
    Serial.println("Data Unlocked");
    Serial.println("\n");
  }
 }

 float Navigation::DDMToDDConversion(float ddmValue)
 {
  //Serial.println(ddmValue, 5);
  //Get the Degrees portion of the value
  long ddDegrees = (long)(ddmValue*10000.0);
  Serial.print("Degrees = ");Serial.println(ddDegrees);
 }
  
 void serialEvent1()
 {
    gps.ReadISR();
 }

