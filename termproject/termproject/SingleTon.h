#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

#include "screen.h"
#include "Bar.h"
#include "input.h"
#include "Note.h"
#include "play.h"
#include "collision.h"
#include "score.h"
#include "scene.h"
#include "music.h"
#include "ui.h"
#include "buzzer.h"
#include "sound.h"

#define LCD_HEIGHT	272
#define LCD_WIDTH	480

extern unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];

typedef struct {
	int number[10][12][16];
} Number;

typedef struct {

	ScreenManager				SM;
	InputManager				IM;
	NoteManager					NM;
	BarManager  				BM;
	CollisionManager			COLM;
	ScoreManager				SCOREM;
	SceneManager				SCENEM;
	MusicManager				MM;
	BuzzerManager				BUZZERM;
	UIgameoption				UI;
	SoundManager				SOUNDM;

	int touchX, touchY;

	int 						random;

}SingleTon;

static SingleTon st;

void Init();
void GameOverInit();
void GamePlayScene();
void SceneUpdate();
bool checkTouchDown(int Tx, int Ty, int Bx, int By, int w, int h);
SingleTon* getSingleTon();

#endif /* _SINGLETON_H_ */
