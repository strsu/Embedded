/*
 * button.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "button.h"

void ButtonUpdate(int _X, int _Y) {
	int i;
	st.BTM.nowID = -1;

	for (i = 0; i < ENUM_MAX; i++) {

		if (!st.BTM.button[i].active) continue;
		if (BTNCheckCollision(st.BTM.button[i], _X, _Y) != -1) {
			st.BTM.nowID = st.BTM.button[i].ID;
			break;
		}
	}

	switch (st.BTM.nowID) {

	case SELECT:
		break;

	case OPTION:
		break;

	case HELP:
		break;
	}
}

int BTNCheckCollision(Button B, int _x, int _y) {

	return ((B.x <= _x) && (B.x + B.width >= _x) &&
		(B.y <= _y) && (B.y + B.height <= _y)) ? B.ID : -1;
}
