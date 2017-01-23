/*
 * File name:   motor.h
 * Author:      Garrett Clay
 * Description: motor controller
 */

#ifndef motor_h
#define motor_h

#include <stdint.h>

#define MOTOR_OFF 0u

typedef enum _MotorId_t{
  FL = 2,   //front left motor
  FR = 3,   //front right motor
  BL = 4,   //back left motor
  BR = 5   //back right motor
} MotorId_t;


class motor {
  public:
    //setup PWM pins for motors
    void InitMotorPins(void);
    
    //set motor speed
    void SetMotorSpeed(MotorId_t Motor, uint8_t SpeedPercent);

    //turns all motors off and hangs program
    void EmergencyMotorOff(void);
  private:

};

 #endif
