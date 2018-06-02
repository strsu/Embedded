/*
 * scene.c
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#include "scene.h"
#include "MyLib.h"
#include "SingleTon.h"

SingleTon *sts;

void SceneInit() {
	sts = getSingleTon();

}

void LoadingScene() {
	int i,j,k;
	for (k = 0; k < 2; k++) {
		for (i = 0; i < 16; i++) {
			DrawImage(buffer, 0, 0, 480, 272, LOADING + 0x40000*i);
			delay(1000000);
		}
	}
	DrawImage(buffer, 0, 0, 480, 272, GAMELOGO);
	delay(2000000);
}

void MenuScene() {

}