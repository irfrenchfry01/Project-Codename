/*
 * File name:   Gps.cpp
 * Author:      Brandon Fry
 * Description: This is the source code for the
 *              GPS module
 */

 #include <arduino.h>
 #include "Gps.h"

 Gps::Gps()
 {
 }

 void Gps::Initialize()
 {
   //Initialization code for the GPS module
   PORTC_PCR5 = PORT_PCR_MUX(0x1);
   GPIOC_PDDR = (1<<5);
   GPIOC_PSOR = (1<<5);
 }

 void Gps::Default()
 {
   //Code to set the GPS to a default state
 }

 void Gps::ReadCurrentLocation()
 {
   uint32_t PortC = GPIOC_PSOR;
   PortC = PortC | (1<<5);
   GPIOC_PTOR = PortC;
   delay(1000);
 }
