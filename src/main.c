/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"

static int i = 0;

typedef union _PORTx_PCRn_t {
	uint32_t value;
	struct {
		uint32_t PS :1;
		uint32_t PE :1;
		uint32_t SRE :1;
		uint32_t Rsvd3 :1;
		uint32_t PFE :1;
		uint32_t ODE :1;
		uint32_t DSE :1;
		uint32_t Rsvd7 :1;
		uint32_t Mux :3;
		uint32_t Rsvd11_14 :4;
		uint32_t LK :1;
		uint32_t IRQC :4;
		uint32_t Rsvd20_23 :4;
		uint32_t ISF :1;
		uint32_t Rsvd25_31 :7;
	} Bit;
} PORTx_PCRn_t;




//#define kGPIO_DigitalInput  0
//#define kGPIO_DigitalOutput 1;

/*! @brief GPIO direction definition*/
typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput = 0U,  /*!< Set current pin as digital input*/
    kGPIO_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} gpio_pin_direction_t;

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t pinDirection; /*!< gpio direction, input or output */
    /* Output configurations, please ignore if configured as a input one */
    uint8_t outputLogic; /*!< Set default output logic, no use in input */
} gpio_pin_config_t;

/*! @name GPIO Output Operations */
/*@{*/

/*!
 * @brief Sets the output level of the multiple GPIO pins to the logic 1 or 0.
 *
 * @param base    GPIO peripheral base pointer(GPIOA, GPIOB, GPIOC, and so on.)
 * @param pin     GPIO pin's number
 * @param output  GPIO pin output logic level.
 *        - 0: corresponding pin output low logic level.
 *        - 1: corresponding pin output high logic level.
 */
static inline void GPIO_WritePinOutput(GPIO_Type *base, uint32_t pin, uint8_t output)
{
    if (output == 0U)
    {
        base->PCOR = 1 << pin;
    }
    else
    {
        base->PSOR = 1 << pin;
    }
}


void GPIO_PinInit(GPIO_Type *base, uint32_t pin, const gpio_pin_config_t *config)
{
    //assert(config);

    if (config->pinDirection == kGPIO_DigitalInput)
    {
        base->PDDR &= ~(1U << pin);
    }
    else
    {
        GPIO_WritePinOutput(base, pin, config->outputLogic);
        base->PDDR |= (1U << pin);
    }
}

int main(void) {

	/* Write your code here */
	// Define a digital input pin configuration,
	gpio_pin_config_t config =
	{
	   kGPIO_DigitalInput,
	   0,
	};

	 //Define a digital output pin configuration,
	 gpio_pin_config_t config =
	{
	   kGPIO_DigitalOutput,
	   0,
	};


	gpio_pin_config_t *TmpConfig;
	TmpConfig->pinDirection = kGPIO_DigitalOutput;
	TmpConfig->outputLogic = 1;

	GPIO_PinInit(GPIOC_IDX, 13, TmpConfig);

	//uint32_t DEF_PORTC_PCR13 = 0x4004B034;
	//uint32_t test_var = 0;

	//PORTx_PCRn_t PC13;
	//PC13.value = PORTC_PCR13;
	//PC13.Bit.Mux = 0b001;
	//PORTC_PCR13 = PC13.value;

	//PORTC13 = 1;
	//dang it

	//Port Data Output Register (GPIOC_PDOR)
	//Port Set Output Register (GPIOC_PSOR)
	//Port Clear Output Register (GPIOC_PCOR)
	//Port Toggle Output Register (GPIOC_PTOR)
	//Port Data Input Register (GPIOC_PDIR)
	//Port Data Direction Register (GPIOC_PDDR)

	//GPIO_SET_PDDR(DEF_PORTC_PCR13, PC13.value);
	//GPIO_WR_PSOR(GPIOC_IDX, 1);
	//PORTC13 = 1;

	/* This for loop should be replaced. By default this loop allows a single stepping. */
	for (;;) {
		i++;
	}
	/* Never leave main */
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
