#ifndef _BAR_H_
#define _BAR_H_

#include "SingleTon.h"

#define BAR_LMAX 4

typedef struct {
	int  x, y;
	int  width, height;
	bool active;
	int  image;
}Bar;

typedef struct {
	
	Bar bar[BAR_LMAX];
}BarManager;


void BarUpdate();		/* Bar�� �ٽñ׸��� �Լ� */
void TouchBar(Bar C);	/* Bar�� ��ġ������ ó�� �Լ� */
void BarDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);

#endif _BAR_H_