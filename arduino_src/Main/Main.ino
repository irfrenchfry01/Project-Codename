#include "Gps.h"
#include "main.h"
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "motor.h"

Imu Imu;
motor motor;

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

void setup() {
  //Serial.begin(38400);

  LedInit();
  motor.InitMotorPins();

  Imu.InitImu();
  
  delay(1000);
  Imu.displaySensorDetails();
}

  static uint8_t IncSpeed = 20;  

void loop() {
  //test code for motor control
  IncSpeed += 20;  
  if(IncSpeed > 100) { IncSpeed = 20; }
  motor.SetMotorSpeed(FL, IncSpeed);
  //end test code for motor control
  
  delay(1000);
  ToggleLed();
  Imu.ReadAndPrintImuData();
  
}
