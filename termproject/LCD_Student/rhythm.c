#include "rhyrhm.h"

void imageMove(int *buffer, int *noteX, int *noteY) {
	int push_data = (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) &
		(~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);
	if (push_data & 0x1) {
		if (*noteX > 0) {
			(*noteX)--;
			NoteDraw(buffer, *noteX, *noteY, imageX + *noteX, imageY + *noteY, NOTE);
			RestoreBackground(buffer, *noteX + imageX, *noteY, *noteX + imageX + 2, *noteY + imageY, IMAGE2);
		}
	}
	else if (push_data & 0x2) {
		if (*noteX < 480 - imageX) {
			(*noteX)++;
			NoteDraw(buffer, *noteX, *noteY, imageX + *noteX, imageY + *noteY, NOTE);
			RestoreBackground(buffer, *noteX - 2, *noteY, *noteX, *noteY + imageY, IMAGE2);
		}
	}
	else if (push_data & 0x4) {
		if (*noteY < 272 - imageY) {
			(*noteY)++;
			NoteDraw(buffer, *noteX, *noteY, imageX + *noteX, imageY + *noteY, NOTE);
			RestoreBackground(buffer, *noteX, *noteY - 1, *noteX + imageX, *noteY, IMAGE2);
		}
	}
	else if (push_data & 0x8) {
		if (*noteY > 1) {
			(*noteY)--;
			NoteDraw(buffer, *noteX, *noteY, imageX + *noteX, imageY + *noteY, NOTE);
			RestoreBackground(buffer, *noteX, *noteY + imageY, *noteX + imageX, *noteY + imageY + 1, IMAGE2);
		}
	}
}

void noteView(int *buffer, int *noteX_Location, int *noteY_Location) {
	int i, j;
	int BarX_Location[4] = { 4, 78, 152, 226 };
	for (i = 0; i < 4; i++) {
		NoteDraw(buffer, noteX_Location[i], noteY_Location[i], imageX + noteX_Location[i], imageY + noteY_Location[i], NOTE);
		RestoreBackground(buffer, noteX_Location[i], noteY_Location[i] + imageY, noteX_Location[i] + imageX, noteY_Location[i] + imageY + velocty, IMAGE2);
		stay_with_me_velocity[i]--;
		if (stay_with_me_velocity[i] < 1) {
			noteY_Location[i] -= velocty;
		}
		if (noteY_Location[i] < 8) {
			BarView(buffer, BarX_Location);
			noteY_Location[i] = 260;
			stay_with_me_velocity[i] = stay_with_me_velocity[delay_cnt];
			delay_cnt++;
		}
	}
}

void BarView(int *buffer, int *BarX_Location) {
	int i;
	for (i = 0; i < 4; i++) {
		BarDraw(buffer, BarX_Location[i], 0, 72 + BarX_Location[i], 32, BAR_BLUE);
	}
}

void StayWithMe(int *doing) {
	if (*doing == 1) {
		BUZZER_clear();
	}
	if (*doing <= 0) {
		//Play(stay_with_me_code[stay_with_me_cnt]);
		//GPIO_WRITE(GPIO_PORTL, 0xf, 0xf & WhatNote(schoolBell_Code[*cnt]));
		//DelayForPlay(stay_with_me_delay[*cnt]+2);

		if (stay_with_me_delay[(stay_with_me_cnt)] == DLY_8) {
			*doing = 20;
		}
		else if (stay_with_me_delay[(stay_with_me_cnt)] == DLY_4) {
			*doing = 30;
		}
		else if (stay_with_me_delay[(stay_with_me_cnt)] == DLY_16) {
			*doing = 10;
		}
		else {
			*doing = 20;
		}
		stay_with_me_cnt += 1;
		if (stay_with_me_cnt > 106) {
			stay_with_me_cnt = 0;
			delay_cnt = 0;
		}
	}
}

void ScoreProcessing(int score) {
	if (score > 100000) {
		WRITE_FND(1, score / 100000);
		score = score / 100000;
		WRITE_FND(2, score / 10000);
		score = score / 10000;
		WRITE_FND(3, score / 1000);
		score = score / 1000;
		WRITE_FND(4, score / 100);
		score = score / 100;
		WRITE_FND(5, score / 10);
		score = score / 10;
		WRITE_FND(6, score);
	}
	else if (score > 10000) {
		WRITE_FND(2, score / 10000);
		score = score / 10000;
		WRITE_FND(3, score / 1000);
		score = score / 1000;
		WRITE_FND(4, score / 100);
		score = score / 100;
		WRITE_FND(5, score / 10);
		score = score / 10;
		WRITE_FND(6, score);
	}
	else if (score > 1000) {
		WRITE_FND(3, score / 1000);
		score = score / 1000;
		WRITE_FND(4, score / 100);
		score = score / 100;
		WRITE_FND(5, score / 10);
		score = score / 10;
		WRITE_FND(6, score);
	}
	else if (score > 100) {
		WRITE_FND(4, score / 100);
		score = score / 100;
		WRITE_FND(5, score / 10);
		score = score / 10;
		WRITE_FND(6, score);
	}
	else if (score > 10) {
		WRITE_FND(5, score / 10);
		score = score / 10;
		WRITE_FND(6, score);
	}
	else {
		WRITE_FND(6, score);
	}
}

void KeyboardProcessing(unsigned char *buffer, uint8_t code) {
	switch (code) {
	case 'a':
		DrawRect(10, 30, 50, 32, 0xF000);
		UART_printf(code);
		//RestoreBackground(buffer,10,30,50+4,32+1,0x80000);
		break;
	}
}
