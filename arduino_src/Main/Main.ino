#include "Modules\Gps.h"

Gps gps;

void LedInit(void)
{
  PORTC_PCR5 = PORT_PCR_MUX(0x1); //digital GPIO mode?
  GPIOC_PDDR = TEENSY_LED;
}

void setup() {
  // put your setup code here, to run once:
  gps.Initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("test");
  delay(1000);
}
