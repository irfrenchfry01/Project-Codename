#include "main.h"
#include "Gps.h"
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "motor.h"
#include "FlightCtrl.h"
#include "Navigation.h"

Imu ImuMain;
motor motor;
Navigation Nav;
FlightCtrl Fc;
kalman k;
String inputString;

/*
 * inc/dec motor speed
 * pitch
 * testing harness
 * 
 */

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
  Serial.begin(115200);

  LedInit();
  motor.InitMotorPins();

  ImuMain.InitImu();

  k.kalmanInit();
  
  delay(1000);
  //Imu.displaySensorDetails();
}

uint8_t temp = 35;
bool stopped = false;

void MotorWorks() {
  motor.SetMotorSpeed(MOTOR_FL, temp);
  delay(2000);
  motor.SetMotorSpeed(MOTOR_FL, 0);
  
  motor.SetMotorSpeed(MOTOR_FR, temp);
  delay(2000);
  motor.SetMotorSpeed(MOTOR_FR, 0);
  
  motor.SetMotorSpeed(MOTOR_BL, temp);
  delay(2000);
  motor.SetMotorSpeed(MOTOR_BL, 0);
  
  motor.SetMotorSpeed(MOTOR_BR, temp);
  delay(2000);
  motor.SetMotorSpeed(MOTOR_BR, 0);  
}

void GarrettLoop() {
  double RollDeg, PitchDeg = 0;   //in degrees
  double GxDegPerSec, GyDegPerSec = 0;         //in deg/s
  float kRoll, kPitch = 0;
  
  delay(1);
  ToggleLed();

  //Imu.ReadAndPrintImuData();
 
  /*Serial.print("Ay: "); Serial.print(Ay); Serial.println(" "); */
  /*Serial.print("Az: "); Serial.print(Az); Serial.println(" "); */

  RollDeg = Fc.CalcRoll();
  PitchDeg = Fc.CalcPitch();

  //Serial.print("Raw RollDeg: "); Serial.print(RollDeg); Serial.println(" ");
  //Serial.print("Raw PitchDeg: "); Serial.print(PitchDeg); Serial.println(" ");

  GxDegPerSec = Fc.GetGx();
  GyDegPerSec = Fc.GetGy();
  //Serial.print("GxDegPerSec: "); Serial.print(GxDegPerSec); Serial.println(" ");

  // angle in degrees, rate in degrees per second, delta in seconds
  //float kalman::GetAngle(float NewAngle, float NewRate, float Dt)
  kRoll = k.GetRollAngle(RollDeg, GxDegPerSec, 0.001);

  kPitch = k.GetPitchAngle(PitchDeg, GyDegPerSec, 0.001);
  //Serial.print("kPitch: "); Serial.print(kPitch); Serial.println(" "); Serial.println(" ");



  if(stopped == false)
  {
    Fc.CalcMSpeed(MOTOR_FL, kRoll, kPitch);
    //Fc.CalcMSpeed(MOTOR_FR, 0, kPitch);
    //Fc.CalcMSpeed(MOTOR_BL, 0, kPitch);
    //Fc.CalcMSpeed(MOTOR_BR, 0, kPitch);
  }

}

void BrandonSetup()
{
  Serial.begin(115200);
  Nav.NavInitialize();
}

void BrandonLoop()
{

}

//Protocol $<COMMAND_TYPE(8Characters),[Parameter1],[Parameter2],....,[ParameterN],
void parseCommand(String inputCommand)
{
  //$ and first 8 characters are the command type
  String commandType;
  //Can hold up to 10 parameters
  String parameters[10];

  uint32_t parameterIndex = 0;
  uint32_t curIndex = 0;
  uint32_t startIndex = 0;
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

  Serial.print("Inside parse command function..."); 

  //Add Coordinate requires that the coordinates being passed in are in Degrees Decimal format
  if(commandType.equals("ADDCOORD"))
  {
    Serial.println("Adding Coordinate");
    Serial.println(parameters[0]);
    Nav.AddCoordinate(parameters[0], parameters[1]);
  }
  else if(commandType.equals("BEGNPLAN"))
  {
   
  }
  else if(commandType.equals("STOPMOTR"))
  {
    motor.EmergencyMotorOff();
    stopped = true;
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
  GarrettSetup();
  //BrandonSetup();
}

void loop() {
  GarrettLoop(); 
  //BrandonLoop(); 
}

