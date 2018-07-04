#include "play.h"
#include "SingleTon.h"

void noteView() {
	//MenuScene();
	//NumScene();
	//NumDraw();
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
