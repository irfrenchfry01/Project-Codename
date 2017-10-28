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
String inputString;

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

}

void parseCommand(String inputCommand)
{
  //$ and first 8 characters are the command type
  String commandType;
  //Can hold up to 10 parameters
  String parameters[10];

  uint parameterIndex = 0;
  uint curIndex = 0;
  uint startIndex = 0;
  bool firstCommaDetected = false;

  //Performs the parsing of the different data values
  for(curIndex = 1; curIndex < inputCommand.length(); curIndex++)
  {
    char curChar = inputCommand.charAt(curIndex);
    
    if(curChar == ',')
    {
      if(firstCommaDetected == false)
      {
        firstCommaDetected = true;
        commandType = inputCommand.substring(1, curIndex);
      }
      else
      {
        parameters[parameterIndex] = inputCommand.substring(startIndex, curIndex);
        parameterIndex++;
      }
      startIndex = curIndex + 1;
    }
  }

  if(commandType.equals("ADDCOORD"))
  {
    Serial.println("Adding Coordinate");
    Nav.AddCoordinate(parameters[0].toFloat(), parameters[1].toFloat());
  }
  else if(commandType.equals("BEGNPLAN"))
  {
    
  }
  
}

void serialEvent()
{
  while(Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;

    if(inChar == '\n')
    {
      parseCommand(inputString);
      inputString = "";
    }
  }
}
void setup() {
  //GarrettSetup();
  BrandonSetup();
}

void loop() {
  //GarrettLoop(); 
  BrandonLoop(); 
}

