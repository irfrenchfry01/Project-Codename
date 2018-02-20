#include "main.h"
#include "Gps.h"
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "motor.h"
#include "FlightCtrl.h"
#include "Navigation.h"

#define SENSOR_POLL_INTERVAL  0.0001  //unit: seconds
#define MICROSEC_IN_SEC       1000000 //unit: microseconds

IntervalTimer SwTimer1;
IntervalTimer SwTimer2;

Imu ImuMain;
motor motor;
Navigation Nav;
FlightCtrl Fc;
kalman k;
String inputString;


void ToggleLed(void)
{
  uint32_t PortC = GPIOC_PSOR;
  PortC = PortC | (1<<5);
  GPIOC_PTOR = PortC;
}

double gRollDeg, gPitchDeg = 0;         //in degrees
double gGxDegPerSec, gGyDegPerSec = 0;  //in deg/s
float gkRoll = 0;


/**
 * @brief Update kalman calculations on set timer interval
 */
void CalcKalmanData(void)
{
  /* Calc roll with Kalman filter */
  // angle in degrees, rate in degrees per second, delta in seconds
  //float kalman::GetAngle(float NewAngle, float NewRate, float Dt)
  gkRoll = k.GetRollAngle(gRollDeg, gGxDegPerSec, SENSOR_POLL_INTERVAL);
  
}

/**
 * @brief Initialization and setup before loop begins
 */
void GarrettSetup()
{ 
  Serial.begin(115200);

  LedInit();
  motor.InitMotorPins();

  ImuMain.InitImu();

  k.kalmanInit();
  
  delay(1000);
  //Imu.displaySensorDetails();

  //setup software timer 1 to blink LED
  SwTimer1.begin(ToggleLed, 1000000);  
  SwTimer1.priority(200);   //value 0-255, lower value = higher priority

  //setup software tiemr 2 to collect sensor data
  SwTimer2.begin(CalcKalmanData, (SENSOR_POLL_INTERVAL * MICROSEC_IN_SEC));
  SwTimer2.priority(25);
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

  /* Get roll and pitch from accelerometer */
  RollDeg = Fc.CalcRoll();
  PitchDeg = Fc.CalcPitch();
  Serial.print(RollDeg); Serial.print(" ");

  /* Get gyro data in x and y */
  GxDegPerSec = Fc.GetGx();
  GyDegPerSec = Fc.GetGy();
  Serial.print(GxDegPerSec); Serial.print(" ");

  /* Calc roll using Kalman filter */
  //kRoll = k.GetRollAngle(RollDeg, GxDegPerSec, SENSOR_POLL_INTERVAL);
  noInterrupts(); //disable interrupts while updating globals
  /* Update globals for use in kalman timer call */
  gRollDeg = RollDeg;
  gGxDegPerSec = GxDegPerSec;
  
  kRoll = gkRoll;
  interrupts();   //enable interrupts 

  //COMMENTED OUT COMP IN ROLL
  //kRoll = kRoll - 3;
  Serial.print(kRoll); Serial.print(" ");

  //bounds for the plotter
  //Serial.print(-10); Serial.print(" ");
  Serial.println(0);

  /* Calc pitch using Kalman filter */
  kPitch = k.GetPitchAngle(PitchDeg, GyDegPerSec, SENSOR_POLL_INTERVAL);
  //Serial.print("kPitch: "); Serial.print(kPitch); Serial.println(" "); Serial.println(" ");

  if(stopped == false)
  {
    //uncomment code below to spin motors
    //motor, kRoll, kPitch
    Fc.CalcMSpeed(MOTOR_FL, kRoll, 0);
    Fc.CalcMSpeed(MOTOR_FR, kRoll, 0);
    Fc.CalcMSpeed(MOTOR_BL, kRoll, 0);
    Fc.CalcMSpeed(MOTOR_BR, kRoll, 0);
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
  else if(commandType.equals("STOP"))
  {
    Serial.print("STOPMOTR requested");
    motor.EmergencyMotorOff();
    stopped = true;
  }
  else if(commandType.equals("k"))
  {
    Serial.println("Increase speed");
    Fc.IncOrDecUserSpeed(true);
  }  
  else if(commandType.equals("j"))
  {
    Serial.println("Decrease speed");
    Fc.IncOrDecUserSpeed(false);
  }
  else if(commandType.equals("ka"))
  {
      k.SetQAngleRoll(parameters[0].toFloat());
  }
  else if(commandType.equals("kb"))
  {
      k.SetQBiasRoll(parameters[0].toFloat());   
  }
  else if(commandType.equals("km"))
  {
      k.SetRMeasureRoll(parameters[0].toFloat());
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

