#ifndef _BAR_H_
#define _BAR_H_
#pragma once

#define BAR_LMAX		4
#define BAR_BLUE		0x1B0000
#define BAR_RED			0x1F0000
#define BARWEITHD	72
#define BARHEIGHT		32

#define FALSE			0
#define TRUE			1

typedef struct {
	int  x;
	char active;
}Bar;

typedef struct {

	Bar bar[BAR_LMAX];
}BarManager;

void BarInit();
void BarUpdate();			/* Bar를 다시그리는 함수 */
void BarUrteil(Bar C);	/* Bar를 터치했을때 처리 함수 */
void BarAction();
void BarDraw();

#endif /*_BAR_H_*/
