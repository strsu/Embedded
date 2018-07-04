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
	sts->SCENEM.sceneID = 0;
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
		sts->SCENEM.go.AlphaLocation[i] = 280 + ALPHAWIDTH * i;
	}
	char Alpha[ALPHACNT];


}

void LoadingScene() {
	int i,k;
	for (k = 0; k < 2; k++) {
		for (i = 0; i < 10; i++) {
			DrawImage(buffer, 0, 0, 480, 272, LOADING + 0x40000*i);
			delay(100000);
		}
	}
	DrawImage(buffer, 0, 0, 480, 272, GAMELOGO);
	while(1) {
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   0, 0,
						   480, 272 )) {
			sts->SCENEM.sceneID = 1;
			break;
		}
		delay(500000);
	}
}

void MenuScene() {
	DrawImage(buffer, 0, 0, 480, 272, GAMEMENU);
	if (checkTouchDown(sts->touchX,	// play 버튼
					   sts->touchY,
					   150, 180,
					   180, 50 )) {
		sts->SCENEM.sceneID = 2;
	} else
	if (checkTouchDown(sts->touchX,	// option 버튼
			   	   	   sts->touchY,
					   150, 110,
					   180, 50 )) {
		sts->SCENEM.sceneID = 3;
	} else
	if (checkTouchDown(sts->touchX,	// about 버튼
					   sts->touchY,
					   150, 30,
					   180, 50 )) {
		sts->SCENEM.sceneID = 4;
	}
}

void OptionScene() {
	DrawImage(buffer, 0, 0, 480, 272, GAMEOPTION);



	while(1) {

		// 키보드, push 체크박스 /////////////////////////////////////
		if (sts->IM.keyboard == false &&
			checkTouchDown(sts->touchX,
							   sts->touchY,
							   210, 190,		// button_left_down
							   30, 30 )) {		// width, height
			bool temp = sts->IM.keyboard;

			sts->IM.keyboard 	= !temp;
			sts->IM.push 		= temp;

			DrawImage(buffer, 0, 0, 480, 272, GAMEOPTION);
		}

		if (sts->IM.push == false &&
			checkTouchDown(sts->touchX,
						   sts->touchY,
						   340, 190,		// button_left_down
						   30, 30 )) {		// width, height
				bool temp = sts->IM.push;

				sts->IM.keyboard 	= temp;
				sts->IM.push 		= !temp;

				DrawImage(buffer, 0, 0, 480, 272, GAMEOPTION);
		}
		////////////////////////////////////////////////////////

		// 배경음, 노래소리 체크박스 //////////////////////////////////
		if (checkTouchDown(sts->touchX,
									   sts->touchY,
									   210, 130,		// button_left_down
									   30, 30 )) {		// width, height

					sts->MM.BGM = !sts->MM.BGM;
					BUZZER_clear();

					DrawImage(buffer, 0, 0, 480, 272, GAMEOPTION);
				}

				if (checkTouchDown(sts->touchX,
								   sts->touchY,
								   340, 130,		// button_left_down
								   30, 30 )) {		// width, height

					sts->MM.EFM = !sts->MM.EFM;

					DrawImage(buffer, 0, 0, 480, 272, GAMEOPTION);
			}
		///////////////////////////////////////////////////////

				if (sts->IM.keyboard) 	{ DrawRect(220, 198, 235, 208, 0xF800); }
				else 					{ DrawRect(337, 198, 353, 208, 0xF800); }
				if (sts->MM.BGM)		{ DrawRect(220, 140, 235, 150, 0xF800); }
				if (sts->MM.EFM)		{ DrawRect(337, 140, 353, 150, 0xF800); }

		// back 버튼 ////////////////////////////////////////////
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   150, 0,		// button_left_down
						   120, 40 )) {		// width, height
			sts->SCENEM.sceneID = 1;
			break;
		}
		///////////////////////////////////////////////////////
	}
}

void AboutScene() {

	DrawImage(buffer, 0, 0, 480, 272, GAMEABOUT);
	while(1) {
		// back 버튼 ////////////////////////////////////////////
				if (checkTouchDown(sts->touchX,
								   sts->touchY,
								   170, 10,		// button_left_down
								   130, 40 )) {		// width, height
					sts->SCENEM.sceneID = 1;
					break;
				}
				///////////////////////////////////////////////////////
	}
}

void PlayScene() {
	DrawImage(buffer, 0, 0, 480, 272, GAMESELECT);
	while(1) {
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   110, 190,		// button_left_down
						   260, 50 )) {		// width, height
			sts->SCENEM.sceneID = 5;
			break;
		}
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   110, 100,		// button_left_down
						   260, 50 )) {		// width, height
			sts->SCENEM.sceneID = 6;
			break;
		}
		// back 버튼 ////////////////////////////////////////////
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   170, 30,		// button_left_down
						   120, 30 )) {		// width, height
			sts->SCENEM.sceneID = 1;
			break;
		}
		///////////////////////////////////////////////////////
	}
}

void BuzzerScene() {
	DrawImage(buffer, 0, 0, 480, 272, MUSICTITLE);

	strcpy(sts->SCENEM.musiclist, "school bell");
	AlphaDraw(40, 223);
	strcpy(sts->SCENEM.musiclist, "stay with me");
	AlphaDraw(40, 143);
	strcpy(sts->SCENEM.musiclist, "travel11111111111111111");
	AlphaDraw(40, 58);
	while(1) {
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 45,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			strcpy(sts->SCENEM.musiclist, "travel11111111111111111");
			AlphaDraw(40, 48);
			sts->UI.MusicID = 1;
			break;
		}
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 130,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			strcpy(sts->SCENEM.musiclist, "stay with me");
			sts->UI.MusicID = 2;
			break;
		}
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 210,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			strcpy(sts->SCENEM.musiclist, "school bell");
			sts->UI.MusicID = 3;
			break;
		}
		// back 버튼 ////////////////////////////////////////////
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   190, 5,		// button_left_down
						   95, 25 )) {		// width, height
			sts->SCENEM.sceneID = 2;
			break;
		}
		///////////////////////////////////////////////////////
	}
}

void MP3Scene() {
	DrawImage(buffer, 0, 0, 480, 272, MUSICTITLE);
	while(1) {
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 45,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			sts->UI.MusicID = 11;
			break;
		}
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 130,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			sts->UI.MusicID = 12;
			break;
		}
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   20, 210,		// button_left_down
						   440, 40 )) {		// width, height
			sts->UI.active = true;
			sts->UI.MusicID = 13;
			break;
		}
		// back 버튼 ////////////////////////////////////////////
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   190, 5,		// button_left_down
						   95, 25 )) {		// width, height
			sts->SCENEM.sceneID = 2;
			break;
		}
		///////////////////////////////////////////////////////
	}
}

void GameOverScene() {
	DrawImage(buffer, 0, 0, 480, 272, GAMEOVER);
	ScoreDraw();
	ComboDraw();
	GradeDraw();
	while (1) {
		delay(500000);
		if (checkTouchDown(sts->touchX,
						   sts->touchY,
						   0, 0,		// button_left_down
						   480, 272 )) {		// width, height
			if(sts->UI.MusicID < 10) {
				sts->SCENEM.sceneID = 5;
			} else {
				sts->SCENEM.sceneID = 6;
			}
			sts->SCOREM.score = 0;
			sts->SCOREM.combo = 0;
			sts->SCOREM.maxCombo = 0;
			GameOverInit();
			break;
		}
	}
	
}

void ScoreDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	int val = sts->SCOREM.score;
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

		x1 = sts->SCENEM.go.ScoreLocation[j]; //280 + NUMWIDTH*j;
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

	int val = sts->SCOREM.maxCombo;
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
		if (sts->SCOREM.score > 5000) {
			image = GRADE_S;
		} else
		if (sts->SCOREM.score > 4000) {
			image = GRADE_A;
		} else
		if (sts->SCOREM.score > 3000) {
			image = GRADE_B;
		} else
		if (sts->SCOREM.score > 2000) {
			image = GRADE_C;
		} else
		if (sts->SCOREM.score > 1000) {
			image = GRADE_D;
		}
		else {
			image = GRADE_F;
		}
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

void AlphaDraw(int Lx, int Ly) {
	int i, j, x1, x2, y1, y2, image, ascii;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = Ly;
	y2 = y1 + ALPHAHEIGHT;
	for(j=0;j<50;j++) {
		x1 = Lx + ALPHAWIDTH * j;
		x2 = x1 + ALPHAWIDTH;
		ascii = (int) sts->SCENEM.musiclist[j] - 97;
		//UART_printf("Ascii 0 d : %d, c : %c \n\r", ascii, ascii);
		if( ascii < 0 || ascii > 26 ) {
			continue;
		}
		image = ALPHA_a + 0x40000 * ascii;	// 이미지
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
	}

	SetFullFrame();

}

void PlayAlphaDraw(int Lx, int Ly) {
	int i, j, x1, x2, y1, y2, image, ascii;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = Ly;
	y2 = y1 + ALPHAHEIGHT;
	for (j = 0; j<5; j++) {
		x1 = Lx + ALPHAWIDTH * j;
		x2 = x1 + ALPHAWIDTH;
		ascii = (int)sts->SCENEM.musiclist[j] - 97;
		if (ascii < 0 || ascii > 26) {
			continue;
		}
		image = ALPHA_a + 0x40000 * ascii;	// 이미지
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
	}

	SetFullFrame();

}

void PlayScoreDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	int val = sts->SCOREM.score;
	int lo = NUMCNT - 1;
	while (val != 0) {
		sts->SCENEM.go.finalScore[lo] = val % 10;
		val = val / 10;
		lo--;
	}

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 210;
	y2 = y1 + NUMHEIGHT;

	for (j = 0; j < NUMCNT; j++) {

		/* Note 이미지를 그려주는 코드 start */

		if (sts->SCENEM.go.finalScore[j] == -1) {
			continue;
		}

		x1 = 40 + sts->SCENEM.go.ScoreLocation[j]; //280 + NUMWIDTH*j;
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

void PlayComboDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	int val = sts->SCOREM.combo;
	int lo = NUMCNT - 1;
	while (val != 0) {
		sts->SCENEM.go.finalCombo[lo] = val % 10;
		val = val / 10;
		lo--;
	}

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 190;
	y2 = y1 + NUMHEIGHT;

	for (j = 0; j < NUMCNT; j++) {

		/* Note 이미지를 그려주는 코드 start */

		if (sts->SCENEM.go.finalCombo[j] == -1) {
			continue;
		}

		x1 = 40 + sts->SCENEM.go.ScoreLocation[j];
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
