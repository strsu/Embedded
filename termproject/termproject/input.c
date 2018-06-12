/*
 * input.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "input.h"

#include "SingleTon.h"
#include "cortex_m4.h"

SingleTon *sti;

void InputInit() {
	int i;
	sti = getSingleTon();
	sti->IM.keyboard = true;
	sti->IM.push = false;
	for (i = 0; i < KEYMAX; i++) {
		sti->IM.input[i] = false;
	}
}

void InputUpdate() {
	InputAction();
}

void InputAction() {
	int i, push_data;
	uint8_t code;
	for (i = 0; i < KEYMAX; i++) {
		sti->IM.input[i] = false;
	}
	if (sti->IM.keyboard) {
		code = UART_getkey();
		if (code) {
			switch (code) {
			case 'a': sti->IM.input[0] = true; return;
			case 's': sti->IM.input[1] = true; return;
			case 'd': sti->IM.input[2] = true; return;
			case 'f': sti->IM.input[3] = true; return;
			}
		}
	}
	else if(sti->IM.push) {
		push_data = (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & \
						  	(~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);
		if (push_data & 0x1) {
			sti->IM.input[0] = true;
		}
		if (push_data & 0x2) {
			sti->IM.input[1] = true;
		}
		if (push_data & 0x4) {
			sti->IM.input[2] = true;
		}
		if (push_data & 0x8) {
			sti->IM.input[3] = true;
		}
	}
}


