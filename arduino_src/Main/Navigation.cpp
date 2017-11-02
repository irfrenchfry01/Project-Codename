/*
 * File name:   Navigation.cpp
 * Author:      Brandon Fry
 * Description: Navigation controller
 */

 //Include files
 #include "Navigation.h"
 #include "Gps.h"

 Gps gps;

 DD_COORDINATE flightPath[MAXCOORDINATES];
 int writeCount = 0;
 
 void Navigation::NavInitialize()
 {
    gps.GpsInit();
 }

 bool Navigation::AddCoordinate(String latitude, String longitude)
 {
    DD_COORDINATE coordinate;
    if(writeCount < MAXCOORDINATES)
    {
      //Parse the latitude value into the coordinate struct
      for(int i = 0; i < latitude.length(); i++)
      {
        if(latitude.charAt(i) == '.')
        {
          coordinate.latDegrees = latitude.substring(0, i).toInt();
          coordinate.latDecimal = latitude.substring(i, latitude.length()).toFloat();
        }
      }
      
      //Parse the longitude value into the coordinate struct
      for(int i = 0; i < longitude.length(); i++)
      {
        if(longitude.charAt(i) == '.')
        {
          coordinate.longDegrees = longitude.substring(0, i).toInt();
          coordinate.longDecimal = longitude.substring(i, longitude.length()).toFloat();
        }
      }

      //Add the coordinate to the flight plan
      flightPath[writeCount] = coordinate;
      writeCount++;

      Serial.println(flightPath[0].latDegrees);
      Serial.println(flightPath[0].latDecimal, 6);
      Serial.println(flightPath[0].longDegrees);
      Serial.println(flightPath[0].longDecimal, 6);
      
      return true;
    }
    else 
    {
      Serial.println("Maximum coordinates reached");
      return false;
    }
    return false;
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

