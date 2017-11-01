/*
 * File name:   motor.c
 * Author:      Garrett Clay
 * Description: motor controller
 */
#include "motor.h"
#include <Arduino.h>
#include <Servo.h>

Servo MotorFL;   // MOTOR_FL, pin 2
Servo MotorFR;   // MOTOR_FR, pin 3
Servo MotorBL;   // MOTOR_BL, pin 4
Servo MotorBR;   // MOTOR_BR, pin 5

uint8_t FLMotorSpeed[ MOTOR_SPEED_AVG_CNT ] = { 0 };

/*
 *  @brief setup PWM pins for output
 */
void motor::InitMotorPins(void)
{
  uint8_t InitSpeed = 30;
  uint8_t Speed = 0;

  MotorFL.attach(MOTOR_FL);
  MotorFR.attach(MOTOR_FR);
  MotorBL.attach(MOTOR_BL);
  MotorBR.attach(MOTOR_BR);

  //Ramp speed sequence
  for(Speed = InitSpeed; Speed < 40; Speed++)
  {
    SetMotorSpeed(MOTOR_FL, Speed);
    SetMotorSpeed(MOTOR_FR, Speed);
    SetMotorSpeed(MOTOR_BL, Speed);
    SetMotorSpeed(MOTOR_BR, Speed);
    delay(1000);
  }

  //Set speed low, this also sets motors to off
  SetMotorSpeed(MOTOR_FL, InitSpeed);
  SetMotorSpeed(MOTOR_FR, InitSpeed);
  SetMotorSpeed(MOTOR_BL, InitSpeed);
  SetMotorSpeed(MOTOR_BR, InitSpeed);
}

/*
 *  @brief calc motor speed based on averaging scheme
 *  
 *  @param[in] Motor      select which motor to calc for
 *  @param[in] NewSpeed   new speed input to be averaged, in percent
 *  
 *  @retval   Speed       current speed to change motor to, in percent
 */
uint8_t motor::CalcMotorSpeed(MotorId_t Motor, uint8_t NewSpeed)
{
  /* //compile error issue
  uint8_t i = 0;
  double Sum = 0;
  double AvgSpeed = 0;
  
  if(MOTOR_FL == Motor)
  {
    for(i = 1; i < MOTOR_SPEED_AVG_CNT; i++)
    {
      //Sum += (FLMotorSpeed[i] * MOTOR_SPEED_COEF[i-1]);
      Sum += (FLMotorSpeed[i] * MOTOR_SPEED_COEF);
      FLMotorSpeed[i-1] = FLMotorSpeed[i];
    }
    FLMotorSpeed[MOTOR_SPEED_AVG_CNT] = NewSpeed;
    Sum += FLMotorSpeed[MOTOR_SPEED_AVG_CNT];
    AvgSpeed = Sum / MOTOR_SPEED_AVG_CNT;
  }
  */
  
  /* //commented out for motor test
  else if(MOTOR_FR == Motor)
  {
    
  }
  else if(MOTOR_BL == Motor)
  {
    
  }
  else
  {
    
  }
  */
  return 0;
}

/*
 *  @brief set PWM duty cycle for motor speed control
 *  
 *  note: motor speed input is in percent but get scaled between
 *  60 and 180
 *  
 *  param[in] Motor         type MotorId_t for which motor affect
 *  param[in] SpeedPercent  34-100% of motor speed
 */
MotorStatus_t motor::SetMotorSpeed(MotorId_t Motor, uint8_t SpeedPercent)
{
  MotorStatus_t Status = MOTOR_STATUS_ERROR;
  uint8_t Speed = 0;
  if(SpeedPercent <= 100)
  {
    Speed = SpeedPercent * 1.8;
    Serial.print("\nSpeed % = "); Serial.print(SpeedPercent); Serial.print(" Speed = "); Serial.print(Speed);
     
    if(MOTOR_FL == Motor)
    {
      MotorFL.write(Speed);
    }
    else if(MOTOR_FR == Motor)
    {
      MotorFR.write(Speed);
    }
    else if(MOTOR_BL == Motor)
    {
      MotorBL.write(Speed);
    }
    else if(MOTOR_BR == Motor)
    {
      MotorBR.write(Speed);
    }
    else
    {
      Status = MOTOR_STATUS_INVALID_MOTOR_ID;
    }
  }
  else
  {
    Status = MOTOR_STATUS_ERROR;
  }

  return Status;
}

/*
 *  @brief turns off all motors and hangs program
 *  
 *  IMPORTANT program enters while loop
 *  after motors are turned off
 */
void motor::EmergencyMotorOff(void)
{
  SetMotorSpeed(MOTOR_FL, MOTOR_OFF);
  SetMotorSpeed(MOTOR_FR, MOTOR_OFF);
  SetMotorSpeed(MOTOR_BL, MOTOR_OFF);
  SetMotorSpeed(MOTOR_BR, MOTOR_OFF);
  
  while(true);
}

