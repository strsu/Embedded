/*
 * report7.h
 *
 *  Created on: 2018. 6. 8.
 *      Author: Home
 */

#ifndef REPORT7_H_
#define REPORT7_H_

#include "mylib.h"

int colors[] = {0x001f, 0x07E0, 0xF800, 0x0000};
int i = 0;
int loX = 200, loY = 100;
int flag  = 1;

void prob_1(int x, int y) {
	if(x >= loX - 50 && x < loX + 50 && y >= loY - 50 && y < loY + 50){
		if(i>4) {
			i=0;
		} else {
			i++;
		}
		DrawCircle(loX, loY, 50, colors[i]);
	} else {
		DrawCircle(loX, loY, 50, 0xFFFF);
		loX = x; loY = y;
		DrawCircle(loX, loY, 50, colors[i]);
	}
}

void prob_2(int x, int y) {
	if(x >= loX - 50 && x < loX + 50 && y >= loY - 50 && y < loY + 50){
		if(i>4) {
			i=0;
		} else {
			i++;
		}
		DrawTriangle(loX, loY, 50, colors[i]);
	} else {
		DrawTriangle(loX, loY, 50, 0xFFFF);
		loX = x; loY = y;
		DrawTriangle(loX, loY, 50, colors[i]);
	}
}

void prob_3(int x, int y) {
	if(flag) {
		DrawRect(140,61,340,210,0x001f);	// 200x150 파란색 사각형
		flag = 0;
	}
	if(x-10 >= 140 && x+10 < 340 && y-10 >= 61 && y+10 < 210){
		DrawRect(loX-10, loY-10, loX+10, loY+10, 0x001f);
		loX = x; loY = y;
		DrawRect(loX-10, loY-10, loX+10, loY+10, 0xFFFF);
	}
}




#endif /* REPORT7_H_ */
