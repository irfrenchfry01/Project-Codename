#include "Gps.h"
#include "main.h"
#include <Wire.h>
#include "imu.h"
#include "kalman.h"
#include "motor.h"
#include "FlightCtrl.h"

#define TEENSY_LED  (1u<<5u)  

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

  static uint8_t count = 0;

void loop() {

  
  delay(1000);
  ToggleLed();
  Imu.ReadAndPrintImuData();

  motor.SetMotorSpeed(FL, 50);
  motor.SetMotorSpeed(FR, 50);
  motor.SetMotorSpeed(BL, 50);
  motor.SetMotorSpeed(BR, 50);  
  
  count++;
  
}
