/*
 * Bar.c
 *
 *  Created on: 2018. 5. 31.
 *      Author: Home
 */

#include "Bar.h"
#include "SingleTon.h"
#include "myLib.h"

uint32_t g_ui32SysClock;

void BarInit() {
	int i;
	st.BM.bar[0].x = 4;
	st.BM.bar[1].x = 78;
	st.BM.bar[2].x = 152;
	st.BM.bar[3].x = 226;

	for (i = 0; i < BAR_LMAX; i++) {
		st.BM.bar[i].active = FALSE;
	}
}

void BarUpdate() {
	BarAction();
	BarDraw();
}

void BarAction() {
	int i;

	for (i = 0; i < BAR_LMAX; i++) {
		st.BM.bar[i].active = st.IM.input[i];
	}
}

void BarUrteil(Bar C) {


}

void BarDraw(){
	int i, j, x1, x2, y1, y2;
	int BarImage;
	unsigned long ulClockMS;

	ulClockMS = g_ui32SysClock / (3 * 1000);

	// �� �ڵ�� ������� ��� ��ġ�� �̹����� �ѷ����� �����ϴ� �ڵ��̴�.
	
	for (j = 0; j < BAR_LMAX; j++) {
		x1 = st.BM.bar[j].x;
		x2 = st.BM.bar[j].x + BARWEITHD;
		y1 = 0;
		y2 = BARHEIGHT;

		BarImage = st.BM.bar[j].active ? 0x1F0000 : 0x1B0000;
		if (st.BM.bar[j].active) {
			//Play(C1);
			//DelayForPlay(DLY_4);
			//BUZZER_clear();
		}
		st.BM.bar[j].active = FALSE;

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
		///// �������

		for (i = 0; i <= BARHEIGHT; ++i) {
			MX66L51235FRead(BarImage + (i*(BARWEITHD) * 2), buffer, (BARWEITHD) * 2);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[0], (void *)0x44050018, (BARWEITHD) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);

			SysCtlDelay(ulClockMS / DIV_MS);

			uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE | UDMA_ARB_8);
			uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT, UDMA_MODE_AUTO, &buffer[(72)], (void *)0x44050018, (BARWEITHD) / 2);
			uDMAChannelEnable(UDMA_CHANNEL_SW);
			uDMAChannelRequest(UDMA_CHANNEL_SW);
			SysCtlDelay(ulClockMS / DIV_MS);
		}

		SetFullFrame();
	}
}

