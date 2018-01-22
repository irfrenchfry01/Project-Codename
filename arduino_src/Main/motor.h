/*
 * File name:   motor.h
 * Author:      Garrett Clay
 * Description: motor controller
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define MOTOR_OFF 0u

//motor constants
#define   MTR_BASE       40

//Front Left (FL) motor constants
#define   MTR_FL_ROLL_COEF  0.5   //positive
#define   MTR_FL_PITCH_COEF 0.5   // TODO

//Front Right (FR) motor constants
#define   MTR_FR_ROLL_COEF  -0.5  //negative
#define   MTR_FR_PITCH_COEF 0.5   // TODO

//Back Left (BL) motor constants
#define   MTR_BL_ROLL_COEF  0.5   //positive
#define   MTR_BL_PITCH_COEF -0.5   // TODO

//Back Left (BR) motor constants
#define   MTR_BR_ROLL_COEF  -0.5  //negative
#define   MTR_BR_PITCH_COEF -0.5   // TODO


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
    void InitMotorPinsTest(void);

    // test servo write function, not needed for drone flight
    void TestServoWriteFunction(uint8_t Speed);
    
    //set motor speed
    MotorStatus_t SetMotorSpeed(MotorId_t Motor, uint8_t SpeedPercent);

    //turns all motors off and hangs program
    void EmergencyMotorOff(void);
  private:

    //variable to track set motor speeds
    //note, these are not actual values as those will be calculated based on this array
};

#endif
