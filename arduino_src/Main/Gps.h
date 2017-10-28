/*
 * File name:   Gps.h
 * Author:      Brandon Fry
 * Description: This is the header file for the GPS
 *              module.
 */

#ifndef Gps_h
#define Gps_h

#include "arduino.h"

  //Definitions

  //GPS Serial Interface=
  #define GPSSerial Serial1
  
  // different commands to set the update rate from once a second (1 Hz) to 10 times a second (10Hz)
  // Note that these only control the rate at which the position is echoed, to actually speed up the
  // position fix you must also send one of the position fix rate commands below too.
  #define PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ  "$PMTK220,10000*2F" // Once every 10 seconds, 100 millihertz.
  #define PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ  "$PMTK220,5000*1B"  // Once every 5 seconds, 200 millihertz.
  #define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
  #define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
  #define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"
  // Position fix update rate commands.
  #define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ  "$PMTK300,10000,0,0,0,0*2C" // Once every 10 seconds, 100 millihertz.
  #define PMTK_API_SET_FIX_CTL_200_MILLIHERTZ  "$PMTK300,5000,0,0,0,0*18"  // Once every 5 seconds, 200 millihertz.
  #define PMTK_API_SET_FIX_CTL_1HZ  "$PMTK300,1000,0,0,0,0*1C"
  #define PMTK_API_SET_FIX_CTL_5HZ  "$PMTK300,200,0,0,0,0*2F"
  // Can't fix position faster than 5 times a second!

  #define PMTK_SET_BAUD_57600 "$PMTK251,57600*2C"
  #define PMTK_SET_BAUD_9600 "$PMTK251,9600*17"

  // turn on only the second sentence (GPRMC)
  #define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
  // turn on GPRMC and GGA
  #define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
  // turn on ALL THE DATA
  #define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
  // turn off output
  #define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

  #define PMTK_ENABLE_SBAS "$PMTK313,1*2E"
  #define PMTK_ENABLE_WAAS "$PMTK301,2*2E"

  // standby command & boot successful message
  #define PMTK_STANDBY "$PMTK161,0*28"
  #define PMTK_STANDBY_SUCCESS "$PMTK001,161,3*36"  // Not needed currently
  #define PMTK_AWAKE "$PMTK010,002*2D"

  // ask for the release and version
  #define PMTK_Q_RELEASE "$PMTK605*31"

  // request for updates on antenna status 
  #define PGCMD_ANTENNA "$PGCMD,33,1*6C" 
  #define PGCMD_NOANTENNA "$PGCMD,33,0*6D" 

  //Acknowldgement
  #define PMTK_ACK "$PMTK001,"
    
class Gps
{
  public:
   //Parameters   
   float timeData;
   float latitude;
   String latitudeQuad;
   float longitude;
   String longitudeQuad;
   int fixQuality;
   int numSats;
   float horDilution;
   float altInMeters;
   //This acts as a semaphore for the data, so that data isn't modified during the interrupt if the main thread is using it.
   bool dataLocked;
   //This gets set true when new data is stored, and then set false when the data is used by the main thread.
   bool dataValid;
   
   //Public Functions
   void Initialize();
   bool IsDataLocked();
   bool IsDataValid();
   void ParseNMEAPacket(String nmeaPacket, bool verboseOutput);
   void ReadISR();
    
  private:
    void InitializeStruct();
    void SendCommand(String cmd);
};

#endif
