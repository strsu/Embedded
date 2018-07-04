/*
 * SingleTon.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "SingleTon.h"


void Init() {
	NoteInit();
	BarInit();
	InputInit();
	CollisionInit();
	ScoreInit();
	MusicInit();
	SceneInit();
	UIgameOptionInit();
	SoundInit();
	st.random = 0;
}

void GameOverInit() {
	int i;
	for (i = 0; i < 10; i++) {
		st.SCENEM.go.finalScore[i] = -1;
		st.SCENEM.go.finalCombo[i] = -1;
		st.SCENEM.go.finalGrade[i] = -1;
	}
	NoteInit2();
	CollisionInit2();
	ScoreInit2();
	st.MM.buzzer.delayCnt = 0;
	st.SOUNDM.delayDnt = 0;
	UIgameOptionInit2();
}

void GamePlayScene() {
	DrawImage(buffer, 0, 0, 480, 272, BACKGROUND);
	strcpy(st.SCENEM.musiclist, "score11111111111");
	AlphaDraw(310, 210);
	strcpy(st.SCENEM.musiclist, "hit1111111111111");
	AlphaDraw(310, 190);
	//WDT1CTL = 0x1;
	while(1) {
		NoteUpdate();
		InputUpdate();
		BarUpdate();
		CollisionUpdate();
		ScoreUpdate();
		PlayScoreDraw();
		PlayComboDraw();
		// pause Check/////////////////////////////////
		if (checkTouchDown(st.touchX,
						   st.touchY,
						   320, 20,		// button_left_down
						   130, 30 )) {		// width, height
			st.UI.active = true;
			BUZZER_clear();
			break;
		}
		if (st.UI.MusicID == 3 && st.SOUNDM.delayDnt >= st.BUZZERM.schoolBellCnt) {	// school bell
			st.SCENEM.sceneID = 8;
			st.SOUNDM.delayDnt = 0;
			//WDT1CTL = 0x0;
			break;
		} else 
		if (st.UI.MusicID == 2 && st.SOUNDM.delayDnt >= st.BUZZERM.stayWithMeCnt) {
			st.SCENEM.sceneID = 8;
			st.SOUNDM.delayDnt = 0;
			//WDT1CTL = 0x0;
			break;
		} else
		if (st.UI.MusicID == 1 && st.SOUNDM.delayDnt >= st.BUZZERM.travelCnt) {
			st.SCENEM.sceneID = 8;
			st.SOUNDM.delayDnt = 0;
			//WDT1CTL = 0x0;
			break;
		}
	}
}

void SceneUpdate() {
	switch(st.SCENEM.sceneID) {
		case 1: {
			MenuScene();
			break;
		}
		case 2: {
			PlayScene();
			break;
		}
		case 3: {
			OptionScene();
			break;
		}
		case 4: {
			AboutScene();
			break;
		}
		case 5: {
			if(st.UI.active) {
				UIgameOptionUpdate();
			} else {
				BuzzerScene();
			}
			break;
		}
		case 6: {
			if(st.UI.active) {
				UIgameOptionUpdate();
			} else {
				MP3Scene();
			}
			break;
		}
		case 7: {
			if(st.UI.active) {
				UIgameGiveUp();
			} else {
				GamePlayScene();
			}
			break;
		}
		case 8: {	
			GameOverScene();
			break;
		}
		default: {
			LoadingScene();
		}
	}
}

bool checkTouchDown(int Tx, int Ty, int Bx, int By, int w, int h) {
	if( (Tx >= Bx && Tx <= Bx + w) &&
		(Ty >= By && Ty <= By + h) ) {
		st.touchX = st.touchY = -1;
		return true;
	}
	return false;
}

SingleTon* getSingleTon() {
	return &st;
}
