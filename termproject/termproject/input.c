/*
 * input.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "input.h"
#include "SingleTon.h"
#include "cortex_m4.h"

void InputInit() {
	int i;
	st.IM.keyboard = FALSE;
	st.IM.push = TRUE;
	for (i = 0; i < KEYMAX; i++) {
		st.IM.input[i] = FALSE;
	}
}

void InputUpdate() {
	InputAction();
}

void InputAction() {
	int i, push_data;
	uint8_t code;
	for (i = 0; i < KEYMAX; i++) {
		st.IM.input[i] = FALSE;
	}
	if (st.IM.keyboard) {
		code = UART_getkey();
		if (code) {
			switch (code) {
			case 'a': st.IM.input[0] = TRUE; return;
			case 's': st.IM.input[1] = TRUE; return;
			case 'd': st.IM.input[2] = TRUE; return;
			case 'f': st.IM.input[3] = TRUE; return;
			}
		}
	}
	else if(st.IM.push) {
		push_data = (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & \
						  	(~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);
		int i;
		if (push_data & 0x1) {
			st.IM.input[0] = TRUE;
		}
		if (push_data & 0x2) {
			st.IM.input[1] = TRUE;
		}
		if (push_data & 0x4) {
			st.IM.input[2] = TRUE;
		}
		if (push_data & 0x8) {
			st.IM.input[3] = TRUE;
		}
	}
}


