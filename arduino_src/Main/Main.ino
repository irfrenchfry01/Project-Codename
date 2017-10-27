#include "Gps.h"
#include "main.h"
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "motor.h"
#include "FlightCtrl.h"
#include "Navigation.h"

#define TEENSY_LED  (1u<<5u)  
 
static uint8_t count = 0;

Imu Imu;
motor motor;
Navigation Nav;
FlightCtrl Fc;
kalman k;

void LedInit(void)
{
  PORTC_PCR5 = PORT_PCR_MUX(0x1); //digital GPIO mode?
  GPIOC_PDDR = TEENSY_LED;
  GPIOC_PSOR = TEENSY_LED;
}

void TimerInit(void)
{
  //turn on PIT
  //PIT_MCR = 0x00;

  //load value
  //LDVAL = (period/clock period) - 1
  //clock period = 20 ns
  //PIT_LDVAL3 = 0x02FAF07F;
  //PIT_TCTRL3 = (1<<1);
  //PIT_TCTRL3 |= (1<<0);

  /* --------- */
  //ignore above
  //setup for TPM1 (Timer / Pulse Width)
  uint8_t TOIE = 6;
  uint8_t CMOD = 3;
  uint8_t PS = 0;
  TPM1_SC |= (1<<TOIE) | (1<<CMOD) | (7<<PS);
  
}

void ToggleLed(void)
{
  uint32_t PortC = GPIOC_PSOR;
  PortC = PortC | (1<<5);
  GPIOC_PTOR = PortC;
}

void GarrettSetup()
{
  //Serial.begin(38400);

  LedInit();
  motor.InitMotorPins();

  Imu.InitImu();
  
  delay(1000);
  Imu.displaySensorDetails();
}

void GarrettLoop() {
  double Ax, Ay, Az = 0;    //in m/s^2
  double RollDeg, PitchDeg = 0;   //in degrees
  double GxRaw = 0;         //in rad/s
  double GxDegPerSec = 0;            //in deg/s
  float kRoll = 0;
  
  delay(1000);
  ToggleLed();
  //Imu.ReadAndPrintImuData();
  Ax = Imu.GetAx();
  Ay = Imu.GetAy();
  Az = Imu.GetAz();
  //Serial.print("Ay: "); Serial.print(Ay); Serial.println(" ");
  //Serial.print("Az: "); Serial.print(Az); Serial.println(" ");

  RollDeg = Fc.CalcRoll(Ax, Ay, Az);
  PitchDeg = Fc.CalcPitch(Ax, Ay, Az);

  Serial.print("Raw RollDeg: "); Serial.print(RollDeg); Serial.println(" ");
  //Serial.print("   Raw PitchDeg: "); Serial.print(PitchDeg); Serial.println(" ");

  GxRaw = Imu.GetGx();
  GxDegPerSec = Fc.GetGx(GxRaw);
  //Serial.print("GxDegPerSec: "); Serial.print(GxDegPerSec); Serial.println(" ");

  // angle in degrees, rate in degrees per second, delta in seconds
  //float kalman::GetAngle(float NewAngle, float NewRate, float Dt)
  kRoll = k.GetAngle(RollDeg, GxDegPerSec, 1);
  Serial.print(" kRoll: "); Serial.print(kRoll); Serial.println(" ");

  motor.SetMotorSpeed(FL, 50);
  motor.SetMotorSpeed(FR, 50);
  motor.SetMotorSpeed(BL, 50);
  motor.SetMotorSpeed(BR, 50);  
  
  count++;
}

void BrandonSetup()
{
  Serial.begin(115200);
  Nav.NavInitialize();
}

void BrandonLoop()
{
  Serial.println("I am in the normal loop");
  delay(10000);
  /*
  int incomingByte = 0;
  Serial.print("Please enter a command\n");
  while(true)
  {
    //Read the serial command
    delay(10);
    if(Serial.available() > 0)
    {
      incomingByte = Serial.read();  
      
      //114 is the ascii code for 'r'
      if(incomingByte == 114)
      {
        Serial.print("Read character detected\n");
        Nav.GetCurrentLocation();
      }
    }
  }
  */
}
void setup() {
  //GarrettSetup();
  BrandonSetup();
}

void loop() {
  //GarrettLoop(); 
  BrandonLoop(); 
}

