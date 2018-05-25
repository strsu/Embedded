/*
 * Module.c
 *
 *  Created on: 2018. 4. 23.
 *      Author: 502
 */

#include "Module.h"


int WhatNote(int note) {

	switch (note) {
	case C1: return 0;
	case D1: return 1;
	case E1: return 2;
	case F1: return 3;
	case G1: return 4;
	case A1: return 5;
	case B1: return 6;
	case C2: return 7;
	}

	return 0;
}

void Siren() {
	int cnt = 5000;
	int pro = 5;

	while (1) {
		GPIO_WRITE(GPIO_PORTB, 0x04, 0x04);
		delay(cnt);

		GPIO_WRITE(GPIO_PORTB, 0x04, ~0x04);
		delay(cnt);
		cnt += pro;

		if (cnt > 8000 || cnt < 5000) {
			pro *= -1;
		}
	}
}

void FND_CLOCK(int push_data) {
	int cnt, hour, min, sec;

	if (push_data & 0x01) { 	// PUSH1 - 1110
		hour = 11;
		min = 59;
		sec = 55;
		cnt = 0;
		while (~(GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & 0x01) {
			WRITE_FND(1, (hour - (hour % 10)) / 10);
			WRITE_FND_DOT(2, hour % 10);
			WRITE_FND(3, (min - (min % 10)) / 10);
			WRITE_FND_DOT(4, min % 10);
			WRITE_FND(5, (sec - (sec % 10)) / 10);
			WRITE_FND(6, sec % 10);
			if (sec == 59) {
				sec = 0;
				if (min == 59) {
					min = 0;
					if (hour == 23) {
						hour = 0;
					}
					else {
						hour++;
					}
				}
				else {
					min++;
				}
			}
			else {
				if (cnt > 150) {
					sec++;
					cnt = 0;
				}
				cnt++;
			}
		}
		FND_clear();
	}
	else if (push_data & 0x02) {	// PUSH2 - 1101
		WRITE_FND(1, 1);
	}
	else if (push_data & 0x04) {	// PUSH3 - 1011
		cnt = 0;
	}
	else if (push_data & 0x08) {	// PUSH4 - 0111
		cnt = 0;
	}
}

int isHit(uint8_t code, int *y) {
	int i;
	for (i = 0; i < 7; i++) {
		if (y[i] >= 220 && code == 'a' + i) {
			return 1;
		}
	}
	return 0;
}

void Buzzer_play(int *cnt, int *doing) {
	int i;
	int note[8] = { C1,D1,E1,F1,G1,A1,B1,C2 };
	int schoolBell_Code[24] = { G1,G1,A1,A1,G1,G1,E1,G1,G1,E1,E1,D1,G1,G1,A1,A1,G1,G1,E1,G1,G1,D1,E1,C1 };
	int schoolBell_Delay[24] = { DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_8,DLY_4,DLY_8,
						DLY_8,DLY_8,DLY_8,20,DLY_8,DLY_8,DLY_8,DLY_8,
						DLY_8,DLY_8,DLY_4,DLY_8,DLY_8,DLY_8,DLY_8,20 };
	if (*doing == 1) {
		BUZZER_clear();
	}
	if (*doing <= 0) {
		//Play(schoolBell_Code[*cnt]);
		GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & WhatNote(schoolBell_Code[*cnt]));
		//DelayForPlay(school2[*cnt]);

		if (*cnt > 23) {
			*cnt = 0;
		}
		if (schoolBell_Delay[(*cnt)] == DLY_8) {
			*doing = 10;
		}
		else if (schoolBell_Delay[(*cnt)] == DLY_4) {
			*doing = 15;
		}
		else {
			*doing = 10;
		}
		*cnt += 1;
		if (*cnt > 23) {
			*cnt = 0;
		}
	}

	//delay(90000);
}


void FND_Calcurator(int push_data, int dip_data) {
	int sum, arr[2], tmp;
	if (push_data & 0x01) { 	// PUSH1 - 1110
		tmp = (dip_data >> 4);
		if (tmp < 10) {
			WRITE_FND(2, 0x0F & (dip_data >> 4));
		}
		else {
			arr[1] = tmp % 10;	// 일의자리
			arr[0] = (tmp - arr[1]) / 10;
			while (~(GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & 0x01) {
				WRITE_FND(1, 0xF & arr[0]);
				WRITE_FND(2, 0xF & arr[1]);
			}
			FND_clear();
		}
		//WRITE_FND(1,0x0F & (dip_data>>4));
		//WRITE_FND_DOT(6,6);

	}
	else if (push_data & 0x02) {	// PUSH2 - 1101
		tmp = (0xf & dip_data);
		if (tmp < 10) {
			WRITE_FND(2, 0x0F & (dip_data));
		}
		else {
			arr[1] = tmp % 10;	// 일의자리
			arr[0] = (tmp - arr[1]) / 10;
			while (~(GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & 0x02) {
				WRITE_FND(1, 0xF & arr[0]);
				WRITE_FND(2, 0xF & arr[1]);
			}
			FND_clear();
		}
	}
	else if (push_data & 0x04) {	// PUSH3 - 1011
		arr[0] = 0x0F & (dip_data >> 4);
		arr[1] = 0x0F & dip_data;
		sum = arr[0] + arr[1];
		if (sum > 9) {
			arr[1] = sum % 10;
			arr[0] = (sum - arr[1]) / 10;
			while (~(GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & 0x04) {
				WRITE_FND(5, 0xF & arr[0]);
				WRITE_FND(6, 0xF & arr[1]);
			}
		}
		else {
			while (~(GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & 0x04) {
				WRITE_FND(6, 0xF & sum);
			}
		}
		FND_clear();
	}
	else if (push_data & 0x08) {	// PUSH4 - 0111
		arr[0] = 0x0F & (dip_data >> 4); // 십의 자리
		arr[1] = 0x0F & dip_data;
		sum = arr[0] - arr[1];
		if (sum >= 0) {
			if (sum > 9) {
				arr[1] = sum % 10;
				arr[0] = (sum - arr[1]) / 10;
				while (~(GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4) & 0x08) {
					WRITE_FND(5, 0xF & arr[0]);
					WRITE_FND(6, 0xF & arr[1]);
				}
			}
			else {
				while (~(GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4) & 0x08) {
					WRITE_FND(6, 0xF & sum);
				}
			}
		}
		else {
			sum *= -1;
			if (sum > 9) {
				arr[1] = sum % 10;
				arr[0] = (sum - arr[1]) / 10;
				while (~(GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4) & 0x08) {
					FND_Minor(4);
					WRITE_FND(5, 0xF & arr[0]);
					WRITE_FND(6, 0xF & arr[1]);
				}
			}
			else {
				while (~(GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4) & 0x08) {
					FND_Minor(5);
					WRITE_FND(6, 0xF & sum);
				}
			}
		}

		FND_clear();
	}

	delay(900000);
}

int LED_swap(int dip) {
	int val = 0;
	val = val | ((dip & 0x01) << 7);
	val = val | ((dip & 0x02) << 5);
	val = val | ((dip & 0x04) << 3);
	val = val | ((dip & 0x08) << 1);
	val = val | ((dip & 0x10) >> 1);
	val = val | ((dip & 0x20) >> 3);
	val = val | ((dip & 0x40) >> 5);
	val = val | ((dip & 0x80) >> 7);
	return val;
}

void Chattering_NoFlag(int push_data, int *cnt) {
	if (push_data & 0x01) { 	// PUSH1 - 1110
		(*cnt) += 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, *cnt);
	}
	else if (push_data & 0x02) {	// PUSH2 - 1101
		(*cnt) -= 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, *cnt);
	}
	else if (push_data & 0x04) {	// PUSH3 - 1011
		GPIO_WRITE(GPIO_PORTL, 0xf, 0x0);
	}
	else if (push_data & 0x08) {	// PUSH4 - 0111
		GPIO_WRITE(GPIO_PORTL, 0xf, 0xf);
	}

	if (*cnt > 15) {
		*cnt = 0;
	}
	else if (*cnt < 0) {
		*cnt = 16;
	}
	delay(300000);
}

void Chattering_Flag(int push_data, int *cnt, int *flag) {
	if ((push_data & 0x01) && *flag == 0) { 	// PUSH1 - 1110
		*flag = 1;
		(*cnt) += 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, *cnt);
	}
	else if ((push_data & 0x02) && *flag == 0) {	// PUSH2 - 1101
		*flag = 1;
		(*cnt) -= 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, *cnt);
	}
	else if ((push_data & 0x04) && *flag == 0) {	// PUSH3 - 1011
		*flag = 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, 0x0);
	}
	else if ((push_data & 0x08) && *flag == 0) {	// PUSH4 - 0111
		*flag = 1;
		GPIO_WRITE(GPIO_PORTL, 0xf, 0xf);
	}
	else if ((push_data & 0xf) && *flag == 1) {	// 1111
		*flag = 0;
	}

	if (*cnt > 15) {
		*cnt = 0;
	}
	else if (*cnt < 0) {
		*cnt = 16;
	}
	delay(9000);
}
