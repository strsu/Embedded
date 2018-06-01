#ifndef _MYLIB_H_
#define _MYLIB_H_
#pragma once
#include "cortex_m4.h"
#include "play.h"

/*  C1 : 도 , D1 : 레 , E1 : 미 ...
    DLY_4 : 4분음표 , DLY_8 : 8분음표 , DLY_16 : 16분음표     */
#define DLY_4 	16
#define DLY_8	8
#define DLY_16	4
#define C1 		61068
#define C1S 	57624
#define D1 		54421
#define D1S 	51366
#define E1 		48484
#define F1 		45844
#define F1S 	43270
#define G1 		40815
#define G1S 	38524
#define A1 		36363
#define A1S 	34322
#define B1 		32388
#define C2 		30592

static unsigned char fnd_num[17] = {
//	0		1		2		3		4		5		6		7
	0x3f,	0x06,	0x5b,	0x4f,	0x66,	0x6d,	0x7d,	0x27,
//	8		9		a		b		c		d		e		f
	0x7f,	0x67,	0x5f,	0x7c,	0x39,	0x5e,	0x79,	0x71,
//	off
	0x00
};

static unsigned char fnd_pos[6] = {
//	D1		D2		D3		D4		D5		D6
	0x01,	0x02,	0x04,	0x08,	0x10,	0x20
};

#define HDP_S 	479
#define	VDP_S	271
#define SCROLL	10
#define LCD_HEIGHT	272
#define LCD_WIDTH	480
#define DIV_MS	17

#define LCD_ENTRY_MODE_REG        0x36
#define LCD_RAM_DATA_REG          0x2C
#define LCD_X_RAM_ADDR_REG        0x2A
#define LCD_Y_RAM_ADDR_REG        0x2B

void Interrupt_init(void);
void Interrupt_init_dip(void);

inline uint16_t ReadData(void);
inline void WriteData(uint16_t ui16Data);
inline void WriteCommand(uint16_t ui8Data);

void LCD_Init(unsigned long g_ui32SysClock);

void RestoreBackground(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);
void CharacterDraw(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);

void PutPixel(int x, int y, int color);
void DrawLine(int x1, int y1, int x2, int y2, int color);

void DrawImage(unsigned char *buffer, int x1, int y1, int x2, int y2, int image);

void Scroll_left(unsigned char *buffer, int x1, int y1, int x2, int y2, int scroll);
void Scroll_right(unsigned char *buffer, int x1, int y1, int x2, int y2, int scroll);
void Scroll_down(unsigned char *buffer, int x1, int y1, int x2, int y2, int scroll);
void Scroll_up(unsigned char *buffer, int x1, int y1, int x2, int y2, int scroll);
void SetFullFrame();

void DrawRect(int x1, int y1, int x2, int y2, int color);
void DrawCircle(int nCenterX,int nCenterY, int nRadius,int color);
void MoveCircle(int nCenterX,int nCenterY, int nRadius,int color);

void BUZZER_init();
void TIMER_init();

void delay(int count);
void BUZZER_clear();
void Play(int freq);
void DelayForPlay(int DLY);
void WDTinitISR(void);

void FND_clear();
void FND_init();
void FND_Minor(int digit);
void WRITE_FND(int digit, int seg_out);
void WRITE_FND_DOT(int digit, int seg_out);
void LED_clear();
void LED_init();
void PUSH_init();
void DIP_init();

void UART_init(float BRD, int BRDI, int BRDF);

char UART_getch(void);

char UART_getkey(void);
void UART_putch(uint8_t data);
void UART_putstr(char* pt);
void UART_printf(char *fmt, ...);

#endif /* _MYLIB_H_ */
