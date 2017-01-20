
/* File: Skeeter.ino
 * Author: Garrett Clay & Brandon Fry
 * Date: 11.13.2016
 * Description: Code for the Skeeter Eater
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

//#include <9dof.h>

#define TEENSY_LED  (1u<<5u)

/* Assign a unique ID to the sensors */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void LedInit(void)
{
  PORTC_PCR5 = PORT_PCR_MUX(0x1); //digital GPIO mode?
  GPIOC_PDDR = TEENSY_LED;
}

void ToggleLed(void)
{
  uint32_t PortC = GPIOC_PSOR;
  PortC = PortC | TEENSY_LED;
  GPIOC_PTOR = PortC;
  delay(1000);    // TODO: remove delay and make interrupt driven
}

void setup() {
  LedInit();
}

void loop() {
  ToggleLed();
}
