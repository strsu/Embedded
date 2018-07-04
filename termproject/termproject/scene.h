/*
 * scene.h
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "cortex_m4.h"

#define BACKGROUND		0x80000

#define LOADING			0x230000	// 10개 이미지 넣음 ~ 0x470000 
#define GAMEMENU		0x4B0000
#define GAMEABOUT		0x4F0000
#define GAMEOPTION		0x530000
#define GAMESELECT		0x570000
#define GAMELOGO		0x5B0000
#define GAMEOVER		0x5F0000

#define NUM0			0x630000
#define NUM1			0x670000
#define NUM2			0x6B0000
#define NUM3			0x6F0000
#define NUM4			0x730000
#define NUM5			0x770000
#define NUM6			0x7B0000
#define NUM7			0x7F0000
#define NUM8			0x830000
#define NUM9			0x870000

#define NUMWIDTH		12
#define NUMHEIGHT		16
#define NUMCNT			10

#define GRADE_S			0x8B0000
#define GRADE_A			0x8F0000
#define GRADE_B			0x930000
#define GRADE_C			0x970000
#define GRADE_D			0x9B0000
#define GRADE_F			0x9F0000

#define GRADEWIDTH		80
#define GRADEHEIGHT		80
#define GRADECNT		6

#define ALPHA_a			0xA30000
#define ALPHA_b			0xA70000
#define ALPHA_c			0xAB0000
#define ALPHA_d			0xAF0000
#define ALPHA_e			0xB30000
#define ALPHA_f			0xB70000
#define ALPHA_g			0xBB0000
#define ALPHA_h			0xBF0000
#define ALPHA_i			0xC30000
#define ALPHA_j			0xC70000
#define ALPHA_k			0xCB0000
#define ALPHA_l			0xCF0000
#define ALPHA_m			0xD30000
#define ALPHA_n			0xD70000
#define ALPHA_o			0xDB0000
#define ALPHA_p			0xDF0000
#define ALPHA_q			0xE30000
#define ALPHA_r			0xE70000
#define ALPHA_s			0xEB0000
#define ALPHA_t			0xEF0000
#define ALPHA_u			0xF30000
#define ALPHA_v			0xF70000
#define ALPHA_w			0xFB0000
#define ALPHA_x			0xFF0000
#define ALPHA_y			0x1030000
#define ALPHA_z			0x1070000
#define ALPHA__			0x10B0000

#define MUSICTITLE		0x10F0000
#define MUSICOPTION		0x1130000  

#define BACK_YES		0x1170000
#define BACK_NO			0x11B0000	// 현재 마지막 이미지 주소

#define BACKOPWIDTH			100
#define BACKOPHEIGHT		40

#define MUSICOPTIONWIDTH		440
#define MUSICOPTIONHEIGHT		249

#define ALPHAWIDTH		12
#define ALPHAHEIGHT		16
#define ALPHACNT		27

typedef struct {
	int finalScore[NUMCNT];
	int finalCombo[NUMCNT];
	int ScoreLocation[NUMCNT];
	char finalGrade[GRADECNT];
	char Alpha[ALPHACNT];
	char AlphaLocation[ALPHACNT];
} GameOver;

typedef struct {
	int sceneID;
	char musiclist[50];
	GameOver go;
}SceneManager;

void SceneInit();

void LoadingScene();
void MenuScene();
void PlayScene();
void OptionScene();
void AboutScene();
void BuzzerScene();
void MP3Scene();
void GameOverScene();

void ScoreDraw();
void ComboDraw();
void GradeDraw();
void AlphaDraw(int Lx, int Ly);

void PlayAlphaDraw(int Lx, int Ly);
void PlayComboDraw();
void PlayScoreDraw();


#endif /* SCENE_H_ */
