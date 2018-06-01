/*
 * input.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "input.h"

void InputUpdate() {
	int i;
	for (i = 0; i < ENUM_MAX; i++) st.IM.input[i] = false;

	if (st.IM.keyboard) {

	} else
	if (st.IM.push) {

	}
}


