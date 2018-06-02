/*
 * scene.h
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "cortex_m4.h"

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

typedef struct {
	int menuSel;
	int modeSel;
	bool optionSel[4];
}SceneManager;

void SceneInit();
void LoadingScene();
void MenuScene();

#endif /* SCENE_H_ */
