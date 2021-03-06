/*
 * File: 	main.h	
 * Author: 	Branett Fray
 * Desc.: 	Header file for main.ino.
 */

/*
 *    Pin Configuration (as enumerated on teensy 3.6 card)
 *    
 *    Pin       External device         Desc.
 *    2         front left motor        PWM output
 *    3         front right motor       PWM output
 *    4         back left motor         PWM output
 *    5         back right motor        PWM output
 *    6         nc
 *    7         nc
 *    8         nc
 *    9         nc
 *    10        nc
 *    11        nc
 *    12        nc
 *    13        nc
 *    14        nc
 *    15        nc
 *    16        nc
 *    17        nc
 *    18        IMU data                SDA0
 *    19        IMU clock               SCL0
 *    20        nc
 */


#ifndef MAIN_H
#define MAIN_H

#define TEENSY_LED  (1u<<5u)

void LedInit(void)
{
  PORTC_PCR5 = PORT_PCR_MUX(0x1); //digital GPIO mode?
  GPIOC_PDDR = TEENSY_LED;
  GPIOC_PSOR = TEENSY_LED;
}




#endif
