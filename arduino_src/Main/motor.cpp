/*
 * File name:   motor.c
 * Author:      Garrett Clay
 * Description: motor controller
 */
#include "motor.h"
#include <Arduino.h>

/*
 *  @brief setup PWM pins for output
 */
void motor::InitMotorPins(void)
{
  pinMode(FL, OUTPUT);
  pinMode(FR, OUTPUT);
  pinMode(BL, OUTPUT);
  pinMode(BR, OUTPUT);
}

/*
 *  @brief set PWM duty cycle for motor speed control
 *  
 *  note: motor speed input is in percent but get scaled between
 *  0 and 255
 *  
 *  param[in] Motor         type MotorId_t for which motor affect
 *  param[in] SpeedPercent  0-100% of motor speed
 */
void motor::SetMotorSpeed(MotorId_t Motor, uint8_t SpeedPercent)
{
  uint8_t Speed = 0;
  if(SpeedPercent <= 100)
  {
    Speed = SpeedPercent * 2.55;
    analogWrite(Motor, Speed); 
  }
}

