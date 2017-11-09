/*
 * File name:   Gps.cpp
 * Author:      Brandon Fry
 * Description: Interrupt based GPS module
 */

#include "Gps.h"

  //Used for storing incoming data from GPS
  //String inputString = "";

  //Enables verbose output from the parseNMEA function
  bool verboseOutput = true;

void Gps::GpsInit()
{
  InitializeStruct();
  
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

void Gps::InitializeStruct()
{
  timeData = 0.0;
  latitude = 0.0;
  latitudeQuad = "N";
  longitude = 0.0;
  longitudeQuad = "W";
  fixQuality = 0;
  numSats = 0;
  horDilution = 0.0;
  altInMeters = 0.0;
  dataLocked = false;
  dataValid = false;
}

//This function parses the NMEA packet and stores the values in the public variables to be used by the main program
void Gps::ParseNMEAPacket(String nmeaPacket, bool verboseOutput)
{
  //Algorithm variables
  uint startIndex = 0;
  uint curIndex = 1;
  int checkSum = 0;
  int loopStep = 0;
  bool firstCommaDetected = false;

  //Temporary GPS data
  float _timeData = 0.0;
  float _latitude = 0.0;
  String _latitudeQuad = "N";
  float _longitude = 0.0;
  String _longitudeQuad = "W";
  int _fixQuality = 0;
  int _numSats = 0;
  float _horDilution = 0.0;
  float _altInMeters = 0.0;
  int _checkSum = 0;

  if(verboseOutput) Serial.println(nmeaPacket);
  
  for(curIndex = 1; curIndex < nmeaPacket.length(); curIndex++)
  {
    char curChar = nmeaPacket.charAt(curIndex);
    //Add to the checksum value

    if(curChar != '*')
    {
      checkSum ^= curChar;
    }
    
    if(curChar == ',' || curChar == '*')
    {
      if(firstCommaDetected == false)
      {
        firstCommaDetected = true;
      }
      else
      {
        switch(loopStep)
        {
          //Time data
          case 0: if(verboseOutput) Serial.println("Time Data: " + nmeaPacket.substring(startIndex, curIndex));
                  _timeData = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Latitude
          case 1: if(verboseOutput) Serial.println("Latitude: " + nmeaPacket.substring(startIndex, curIndex));
                  _latitude = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Latitude Quadrant
          case 2: if(verboseOutput) Serial.println("Latitude Quadrant: " + nmeaPacket.substring(startIndex, curIndex));
                  _latitudeQuad = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Longitude
          case 3: if(verboseOutput) Serial.println("Longitude: " + nmeaPacket.substring(startIndex, curIndex));
                  _longitude = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Longitude Quadrant
          case 4: if(verboseOutput) Serial.println("Longitude Quadrant: " + nmeaPacket.substring(startIndex, curIndex));
                  _longitudeQuad = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Fix Quality
          case 5: if(verboseOutput) Serial.println("Fix Quality: " + nmeaPacket.substring(startIndex, curIndex));
                  _fixQuality = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Number of Satellites
          case 6: if(verboseOutput) Serial.println("Number of Satellites: " + nmeaPacket.substring(startIndex, curIndex));
                  _numSats = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Horizontal Dilution
          case 7: if(verboseOutput) Serial.println("Horizontal Dilution " + nmeaPacket.substring(startIndex, curIndex));
                  _horDilution = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Altitude
          case 8: if(verboseOutput) Serial.println("Altitude in Meters: " + nmeaPacket.substring(startIndex, curIndex));
                  _altInMeters = nmeaPacket.substring(startIndex, curIndex).toFloat();
                  break;
          //Altitude Units
          case 9: if(verboseOutput) Serial.println("Altitude Units: " + nmeaPacket.substring(startIndex, curIndex));
                  break;
          //Height of Geoid
          case 10: if(verboseOutput) Serial.println("Height of GEOID " + nmeaPacket.substring(startIndex, curIndex));
                   break;
          //Height of Geoid Units
          case 11: if(verboseOutput) Serial.println("Height of GEOID Units " + nmeaPacket.substring(startIndex, curIndex));
                   break;
          //Empty Field
          case 12: if(verboseOutput) Serial.println("Time since last DGPS Update: " + nmeaPacket.substring(startIndex, curIndex));
                   break;
          //Empty Field
          case 13: if(verboseOutput) Serial.println("DGPS Station Number " + nmeaPacket.substring(startIndex, curIndex));
                  break;
        }
        loopStep++;
      }
      startIndex = curIndex + 1;
      if(curChar == '*') 
      {
        break;
      }
    } 
  }
  //Check sum
  if(verboseOutput) Serial.println("CheckSum: " + nmeaPacket.substring(startIndex));
  //_checkSum = std::strtol(&nmeaPacket.substring(startIndex)[0], nullptr, 16);
  
  if(verboseOutput) Serial.print("Calculated Checksum = ");
  if(verboseOutput) Serial.println(checkSum, HEX);

  if(_checkSum == checkSum)
  {
    timeData = _timeData;
    latitude = _latitude;
    latitudeQuad = _latitudeQuad;
    longitude = _longitude;
    longitudeQuad = _longitudeQuad;
    fixQuality = _fixQuality;
    numSats = _numSats;
    horDilution = _horDilution;
    altInMeters = _altInMeters;
    dataValid = true;
  }
}

void Gps::ReadISR()
{
  while(GPSSerial.available())
  {
    char inChar = (char)GPSSerial.read();
    inputString += inChar;

    if(inChar == '\n')
    {
      if(inputString.startsWith("$GPGGA"))
      {
        if(!dataLocked)
        {
          dataLocked = true;
          Gps::ParseNMEAPacket(inputString, verboseOutput);
          dataLocked = false;
        }
      }
      inputString = "";
    }
  }
}

void Gps::SendCommand(String cmd)
{
  GPSSerial.println(cmd);
}


