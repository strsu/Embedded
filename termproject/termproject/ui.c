/*
 * ui.c
 *
 *  Created on: 2018. 6. 24.
 *      Author: Home
 */


#include "SingleTon.h"

uint32_t g_ui32SysClock;
SingleTon *stui;

void UIgameOptionInit() {
	stui = getSingleTon();
	stui->UI.MusicID = -1;
	stui->UI.active = false;
	stui->UI.nextSceneNumber = 7;
	stui->NM.speed = 10;
}

void UIgameOptionInit2() {
	stui->UI.MusicID = -1;
	stui->UI.active = false;
	stui->NM.speed = 10;
}

void UIgameOptionUpdate() {
	MusicOptionDraw();
	AlphaDraw(120, 180);
	DrawCircle(110 + 50*3, 130, 5, 0xF800);
	while(1) {
		int i;
		for(i=0;i<7;i++) {
			if(checkTouchDown(stui->touchX,
							  stui->touchY,
						      100 + 50*i, 130,		// button_left_down
						       30, 30 )) {
					stui->NM.speed = 4 + i * 2;

					MusicOptionDraw();
					AlphaDraw(120, 180);
					DrawCircle(115 + 48*i, 130, 5, 0xF800);
			}
		}
		if (checkTouchDown(stui->touchX,
						   stui->touchY,
						   140, 20,		// button_left_down
						   90, 25 )) {		// width, height
			stui->UI.active = false;
			stui->SCENEM.sceneID = 7;
			break;
		}
		// cancel 버튼 ////////////////////////////////////////////
		if (checkTouchDown(stui->touchX,
						   stui->touchY,
						   260, 20,		// button_left_down
						   90, 25 )) {		// width, height
			stui->UI.active = false;
			break;
		}
		///////////////////////////////////////////////////////
	}
}

void UIgameGiveUp() {
	PauseYesDraw();
	PauseNoDraw();
	BUZZER_clear();
	while (1) {
		if (checkTouchDown(stui->touchX,	// Yes
			stui->touchY,
			100, 120,		// button_left_down
			100, 40)) {		// width, height
			stui->UI.active = false;
			stui->SCENEM.sceneID = 8;
			break;
		}
		if (checkTouchDown(stui->touchX,	// No
			stui->touchY,
			260, 120,		// button_left_down
			100, 40)) {		// width, height
			stui->UI.active = false;
			break;
		}
	}
}

void MusicOptionDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 10;
	y2 = y1 + MUSICOPTIONWIDTH;

		x1 = 20;
		x2 = x1 + MUSICOPTIONWIDTH;
		image = MUSICOPTION;	// 배경
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

		for (i = 0; i <= MUSICOPTIONHEIGHT; ++i) {
			MX66L51235FRead(image + (i*(MUSICOPTIONWIDTH) * 2), buffer, (MUSICOPTIONWIDTH) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (MUSICOPTIONWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(MUSICOPTIONWIDTH)], (void *)0x44050018, (MUSICOPTIONWIDTH) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();

}

void PauseYesDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 120;
	y2 = y1 + BACKOPWIDTH;

	x1 = 100;
	x2 = x1 + BACKOPWIDTH;
	image = BACK_YES;	// 배경
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

	for (i = 0; i <= BACKOPHEIGHT; ++i) {
		MX66L51235FRead(image + (i*(BACKOPWIDTH) * 2), buffer, (BACKOPWIDTH) * 2);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (BACKOPWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);

		SysCtlDelay(ulClockMS / DIV_MS);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(BACKOPWIDTH)], (void *)0x44050018, (BACKOPWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);
		SysCtlDelay(ulClockMS / DIV_MS);
	}

	SetFullFrame();

}

void PauseNoDraw() {
	int i, j, x1, x2, y1, y2, image;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	y1 = 120;
	y2 = y1 + BACKOPWIDTH;

	x1 = 260;
	x2 = x1 + BACKOPWIDTH;
	image = BACK_NO;	// 배경
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

	for (i = 0; i <= BACKOPHEIGHT; ++i) {
		MX66L51235FRead(image + (i*(BACKOPWIDTH) * 2), buffer, (BACKOPWIDTH) * 2);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (BACKOPWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);

		SysCtlDelay(ulClockMS / DIV_MS);

		uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
		uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(BACKOPWIDTH)], (void *)0x44050018, (BACKOPWIDTH) / 2);
		uDMAChannelEnable(UDMA_CHANNEL_SW);
		uDMAChannelRequest(UDMA_CHANNEL_SW);
		SysCtlDelay(ulClockMS / DIV_MS);
	}

	SetFullFrame();

}
