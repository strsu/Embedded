#include "play.h"

void noteView() {
	NoteUpdate();
	ScollBell();
	InputUpdate();
	BarUpdate();
	CollisionUpdate();
	ScoreUpdate();
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
