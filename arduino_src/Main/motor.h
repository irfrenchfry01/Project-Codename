/*
 * File name:   motor.h
 * Author:      Garrett Clay
 * Description: motor controller
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define MOTOR_OFF 0u

// use motor speed coefficient to weight newer vs older motor speeds
#define MOTOR_SPEED_AVG_CNT 3u     //note, add coefs if adding more to average
//#define MOTOR_SPEED_COEF[MOTOR_SPEED_AVG_CNT] = { 0.8 1.0 1.2 } // oldest speed to newest
#define MOTOR_SPEED_COEF 1 // oldest speed to newest

typedef enum _MotorId_t{
  MOTOR_FL = 2,   //front left motor
  MOTOR_FR = 3,   //front right motor
  MOTOR_BL = 4,   //back left motor
  MOTOR_BR = 5   //back right motor
} MotorId_t;

typedef enum _MotorStatus_t{
  MOTOR_STATUS_SUCCESS            = 0,   //successful motor function execution
  MOTOR_STATUS_ERROR              = 1,
  MOTOR_STATUS_INVALID_MOTOR_ID   = 2    //invalid motor identifier
} MotorStatus_t;

class motor {
  public:
    //setup PWM pins for motors
    void InitMotorPins(void);

    uint8_t CalcMotorSpeed(MotorId_t Motor, uint8_t NewSpeed);
    
    //set motor speed
    MotorStatus_t SetMotorSpeed(MotorId_t Motor, uint8_t SpeedPercent);

    //turns all motors off and hangs program
    void EmergencyMotorOff(void);
  private:

    //variable to track set motor speeds
    //note, these are not actual values as those will be calculated based on this array

    
};

#endif
