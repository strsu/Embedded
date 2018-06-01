#ifndef _BAR_H_
#define _BAR_H_
#pragma once
#include "cortex_m4.h"

#define BAR_LMAX 4
#define BAR_BLUE		0x1B0000
#define BAR_RED			0x1F0000

typedef struct {
	int  x, y;
	int  width, height;
	bool active;
	int  image;
}Bar;

typedef struct {

	Bar bar[BAR_LMAX];
}BarManager;

#include "SingleTon.h"

void BarInit();
void BarUpdate();		/* Bar를 다시그리는 함수 */
void TouchBar(Bar C);	/* Bar를 터치했을때 처리 함수 */
void BarDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);

#endif /*_BAR_H_*/
