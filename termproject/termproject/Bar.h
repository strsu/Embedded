#ifndef _BAR_H_
#define _BAR_H_
#pragma once

#include "cortex_m4.h"

#define BAR_LMAX		4
#define BAR_BLUE		0x1B0000
#define BAR_RED			0x1F0000
#define BARWEITHD	72
#define BARHEIGHT		32

typedef struct {
	int  x;
	bool active;
}Bar;

typedef struct {

	Bar bar[BAR_LMAX];
}BarManager;

void BarInit();
void BarUpdate();			/* Bar�� �ٽñ׸��� �Լ� */
void BarAction();
void BarDraw();

#endif /*_BAR_H_*/
