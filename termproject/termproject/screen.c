/*
 * button.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "screen.h"
#include "SingleTon.h"
#include "cortex_m4.h"


void ScreenUpdate(int _X, int _Y) {
	int i;
	st.SM.nowID = -1;

	for (i = 0; i < BTYPE_MAX; i++) {

		if (!st.SM.screen[i].active) continue;
	}

	switch (st.SM.nowID) {

	case SELECT:
		break;

	case OPTION:
		break;

	case HELP:
		break;
	}
}
