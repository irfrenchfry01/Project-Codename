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

int main(void) {

	/* Write your code here */
	//uint32_t PORTC_PCR13 = 0x4004B034;
	uint32_t test_var = 0;

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

	//GPIO_SET_PDDR(PORTC_PCR13, PC13.value);
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
