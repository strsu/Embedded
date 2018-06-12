/*
 * scene.c
 *
 *  Created on: 2018. 6. 2.
 *      Author: Home
 */

#include "scene.h"
#include "MyLib.h"
#include "SingleTon.h"

uint32_t g_ui32SysClock;
SingleTon *sts;

void SceneInit() {
	int i;
	sts = getSingleTon();
	sts->SCENEM.menuSel = -1;
	sts->SCENEM.modeSel = -1;
	sts->SCENEM.optionSel[0] = true;	// keyboard
	sts->SCENEM.optionSel[1] = false;	// push
	sts->SCENEM.optionSel[2] = true;	// 배경음	
	sts->SCENEM.optionSel[3] = true;	// 노래소리
	for (i = 0; i < NUMCNT; i++) {
		sts->SCENEM.go.finalScore[i] = -1;
		sts->SCENEM.go.finalCombo[i] = -1;
		sts->SCENEM.go.ScoreLocation[i] = 280 + NUMWIDTH * i;
	}
	sts->SCENEM.go.finalScore[NUMCNT-1] = 0;
	sts->SCENEM.go.finalCombo[NUMCNT-1] = 0;

	sts->SCENEM.go.finalGrade[0] = 'S';
	sts->SCENEM.go.finalGrade[1] = 'A';
	sts->SCENEM.go.finalGrade[2] = 'B';
	sts->SCENEM.go.finalGrade[3] = 'C';
	sts->SCENEM.go.finalGrade[4] = 'D';
	sts->SCENEM.go.finalGrade[5] = 'F';

	for (i = 0; i < ALPHACNT; i++) {
		sts->SCENEM.go.finalScore[i] = -1;
		sts->SCENEM.go.finalCombo[i] = -1;
		sts->SCENEM.go.AlphaLocation[i] = 280 + NUMWIDTH * i;
	}
	char Alpha[ALPHACNT];
}

void LoadingScene() {
	int i,k;
	for (k = 0; k < 1; k++) {
		for (i = 0; i < 30; i++) {
			DrawImage(buffer, 0, 0, 480, 272, LOADING + 0x40000*i);
			delay(100000);
		}
	}
	DrawImage(buffer, 0, 0, 480, 272, GAMELOGO);
	delay(5000000);
}

void MenuScene() {
	DrawImage(buffer, 0, 0, 480, 272, GAMEOVER);
}

void ScoreDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	int val = 132940737; //sts->SCOREM.score;
	int lo = NUMCNT - 1;
	while (val != 0) {
		sts->SCENEM.go.finalScore[lo] = val % 10;
		val = val / 10;
		lo--;
	}

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 80;
	y2 = 80 + NUMHEIGHT;

	for (j = 0; j < NUMCNT; j++) {

		/* Note 이미지를 그려주는 코드 start */

		if (sts->SCENEM.go.finalScore[j] == -1) {
			continue;
		}

		x1 = sts->SCENEM.go.ScoreLocation[j];
		x2 = x1 + NUMWIDTH;
		image = NUM0 + 0x40000 * sts->SCENEM.go.finalScore[j];
		WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
		WriteData(x1 >> 8);
		WriteData(x1 & 0xFF);
		WriteData(x2 - 1 >> 8);
		WriteData(x2 - 1 & 0xff);

		WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
		WriteData(y1 >> 8);
		WriteData(y1 & 0xFF);
		WriteData(y2 - 1 >> 8);
		WriteData(y2 - 1 & 0xff);

		WriteCommand(LCD_RAM_DATA_REG);
		///// 여기까지

		for (i = 0; i <= NUMHEIGHT; ++i) {
			MX66L51235FRead(image + (i*(NUMWIDTH) * 2), buffer, (NUMWIDTH) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (NUMWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(NUMWIDTH)], (void *)0x44050018, (NUMWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

		/* Note 이미지를 그려주는 코드 end */
	}
}

void ComboDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	int val = 2016305028;//sts->SCOREM.maxCombo;
	int lo = NUMCNT - 1;
	while (val != 0) {
		sts->SCENEM.go.finalCombo[lo] = val % 10;
		val = val / 10;
		lo--;
	}

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 40;
	y2 = 40 + NUMHEIGHT;

	for (j = 0; j < NUMCNT; j++) {

		/* Note 이미지를 그려주는 코드 start */

		if (sts->SCENEM.go.finalCombo[j] == -1) {
			continue;
		}

		x1 = sts->SCENEM.go.ScoreLocation[j];
		x2 = x1 + NUMWIDTH;
		image = NUM0 + 0x40000 * sts->SCENEM.go.finalCombo[j];
		WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
		WriteData(x1 >> 8);
		WriteData(x1 & 0xFF);
		WriteData(x2 - 1 >> 8);
		WriteData(x2 - 1 & 0xff);

		WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
		WriteData(y1 >> 8);
		WriteData(y1 & 0xFF);
		WriteData(y2 - 1 >> 8);
		WriteData(y2 - 1 & 0xff);

		WriteCommand(LCD_RAM_DATA_REG);
		///// 여기까지

		for (i = 0; i <= NUMHEIGHT; ++i) {
			MX66L51235FRead(image + (i*(NUMWIDTH) * 2), buffer, (NUMWIDTH) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (NUMWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(NUMWIDTH)], (void *)0x44050018, (NUMWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

		/* Note 이미지를 그려주는 코드 end */
	}
}

void GradeDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 120;
	y2 = y1 + GRADEHEIGHT;

		x1 = 280;
		x2 = x1 + GRADEWIDTH;
		image = GRADE_S;	// 등급에 따른 값 할당 은 필요
		WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
		WriteData(x1 >> 8);
		WriteData(x1 & 0xFF);
		WriteData(x2 - 1 >> 8);
		WriteData(x2 - 1 & 0xff);

		WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
		WriteData(y1 >> 8);
		WriteData(y1 & 0xFF);
		WriteData(y2 - 1 >> 8);
		WriteData(y2 - 1 & 0xff);

		WriteCommand(LCD_RAM_DATA_REG);
		///// 여기까지

		for (i = 0; i <= GRADEHEIGHT; ++i) {
			MX66L51235FRead(image + (i*(GRADEWIDTH) * 2), buffer, (GRADEWIDTH) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (GRADEWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(GRADEWIDTH)], (void *)0x44050018, (GRADEWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

}

void AlphaDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 120;
	y2 = y1 + ALPHAHEIGHT;

	x1 = 280;
	x2 = x1 + ALPHAWIDTH;
	image = ALPHA_a;	// 등급에 따른 값 할당 은 필요
	WriteCommand(LCD_X_RAM_ADDR_REG);		// Set X
	WriteData(x1 >> 8);
	WriteData(x1 & 0xFF);
	WriteData(x2 - 1 >> 8);
	WriteData(x2 - 1 & 0xff);

	WriteCommand(LCD_Y_RAM_ADDR_REG);		// Set Y
	WriteData(y1 >> 8);
	WriteData(y1 & 0xFF);
	WriteData(y2 - 1 >> 8);
	WriteData(y2 - 1 & 0xff);

	WriteCommand(LCD_RAM_DATA_REG);
	///// 여기까지

	for (i = 0; i <= ALPHAHEIGHT; ++i) {
		MX66L51235FRead(image + (i*(ALPHAWIDTH) * 2), buffer, (ALPHAWIDTH) * 2);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (ALPHAWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);

		SysCtlDelay(ulClockMS / DIV_MS);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(ALPHAWIDTH)], (void *)0x44050018, (ALPHAWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);
		SysCtlDelay(ulClockMS / DIV_MS);
	}

	SetFullFrame();

}
