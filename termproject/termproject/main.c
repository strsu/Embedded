#include "SingleTon.h"
#include "report7.h"
#include "math.h"

#define COLOR_BLUE		0x001f
#define COLOR_GREEN		0x07E0
#define COLOR_RED		0xF800
#define COLOR_WHITE		0xFFFF
#define COLOR_BLACK		0x0000

unsigned char buffer[LCD_WIDTH * LCD_HEIGHT];
extern int32_t user_X, user_Y;
uint32_t g_ui32SysClock;

//#define 	Wait_RTC_Control 	while (!(HIBCTL & 0x80000000))
volatile unsigned int variable0 = 0;

void _user_interrupt_handler_1(void);
void _user_interrupt_handler_2(void);
void _user_interrupt_handler_3(void);
void _user_interrupt_handler_4(void);
void _user_Bluetooth_Interrupt_Handler(void);
int32_t PointerMessage(uint32_t ui32Message, int32_t i32X, int32_t i32Y);

int cnt;
int move[2];
int colors2[] = {0x001f, 0x07E0, 0xF800, 0x0000};

int main(void) {
	g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
											SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
											SYSCTL_CFG_VCO_480), 120000000);
	int push_data;
	int dip_data;
	int reverse_dip;

	// UART 관련 함수
	uint8_t code;

	float BRD;
	int   BRDI;
	int   BRDF;

	//RTC
	int rtc_time0;
	int rtc_time1;

	int time_sec = 0;
	int time_flag = 0;

	//uart baud rate(p.1339)
	BRD = (float)g_ui32SysClock / (16 * 115200);
	BRDI = (int)BRD;
	BRDF = (int)(((BRD - (int)BRD) * 64) + 0.5);


	UART_init(BRD, BRDI, BRDF);
	Bluetooth_init(BRD, BRDI, BRDF);

	UART_printf("//**************************************//\n\r");
	UART_printf("//***********  Initialize  *************//\n\r");
	UART_printf("//***********      OK      *************//\n\r");
	UART_printf("//**************************************//\n\r");


	// Interupt init
	//Interrupt_init();

	// LED 관련 함수
	LED_init();
	LED_clear();

	//DIP SWITCH 관련 함수
	DIP_init();

	// PUSH 관련 함수
	PUSH_init();

	// 7-SEGMENT 관련 함수
	FND_init();
	FND_clear();

	// BUZZER 관런 함수
	BUZZER_init();
	TIMER_init();
	WDTinitISR();

	//Touch
	TouchScreenInit(g_ui32SysClock);
	TouchScreenCallbackSet(PointerMessage);

	LCD_Init(g_ui32SysClock);

	GPIO_WRITE(GPIO_PORTD, 0x10, 0x10);  // buzzer ON
	GPTMCTL = GPTMCTL | 0x41;   		 // timer enable

	BUZZER_clear();

	RTC_Init();

	//********** Set Real Clock ************//
		HIBLOCK = 0xA3359554;

		while (!(HIBCTL & 0x80000000));
		HIBCALLD0 = (12 << 16) | (34 << 8) | 56;
		// (Hour << 16) | (Min << 8) | Sec
		while (!(HIBCTL & 0x80000000));

		HIBCALLD1 = (0x0 << 24) | (16 << 16) | (5 << 8) | 31;
		// (Day of Week << 24) | (Year << 16) | (Month << 8) | Day of Month
		while (!(HIBCTL & 0x80000000));

		HIBLOCK = 0;
		while (!(HIBCTL & 0x80000000));

		rtc_time0 = HIBCAL0;	// hour, min, sec
		rtc_time1 = HIBCAL1;	// year, month, day
		//**************************************//

		time_sec = rtc_time0 & 0x3f;

		// HIBCTL = HIBCTL | 0x01;	// 타이머 활성
		// HIBCTL = HIBCTL & ~0x01;	// 타이머 비활성

	delay(1000000);

	/* initial setting finish*/

	// SingleTon init
	Init();
	DrawRect(0,0,480,272,COLOR_WHITE);
	//LoadingScene();
	//DrawImage(buffer, 0, 0, 480, 272, BACKGROUND);

	//MenuScene();
	//ScoreDraw();
	//ComboDraw();
	//GradeDraw();
	//DrawImage(buffer, 0, 0, 12, 16, NUM0);
	//DrawImage(buffer, 0, 0, 480, 272, BACKGROUND);

	while (1){
		rtc_time0 = HIBCAL0;
		rtc_time1 = HIBCAL1;

		WRITE_FND(0,((rtc_time0 >> 16) & 0x1f) / 10);
		WRITE_FND_DOT(1,((rtc_time0 >> 16) & 0x1f) % 10);
		WRITE_FND(2,((rtc_time0 >> 8) & 0x3f) / 10);
		WRITE_FND_DOT(3,((rtc_time0 >> 8) & 0x3f) % 10);
		WRITE_FND(4,((rtc_time0) & 0x3f) / 10);
		WRITE_FND_DOT(5,((rtc_time0) & 0x3f) % 10);
	}


	move[0] = 10;
	move[1] = 10;
	cnt = 0;
	while (1) {
		code = UART_getkey();
			if(code >= 'a'-97 && code <= 'z'+5) {
					Bluetooth_PutCh(code);
				}

		//noteView();
	}

	while (1) {
		//push_data = (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & \
							  (~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);

				//reverse_dip =  ( GPIO_READ(GPIO_PORTA, 0x08) << 4 ) | ( GPIO_READ(GPIO_PORTA, 0x40) << 0 ) |	\
		 						 ( GPIO_READ(GPIO_PORTA, 0x80) >> 2 ) | ( GPIO_READ(GPIO_PORTB, 0x08) << 1 ) |	\
		 					  	 ( GPIO_READ(GPIO_PORTQ, 0x40) >> 3 ) | ( GPIO_READ(GPIO_PORTQ, 0x20) >> 3 ) |	\
		 					  	 ( GPIO_READ(GPIO_PORTQ, 0x10) >> 3 ) | ( GPIO_READ(GPIO_PORTG, 0x40) >> 6 );

				//dip_data =  (GPIO_READ(GPIO_PORTA, 0x08) >> 3) | (GPIO_READ(GPIO_PORTA, 0x40) >> 5) |	\
		 					  (GPIO_READ(GPIO_PORTA, 0x80) >> 5) | (GPIO_READ(GPIO_PORTB, 0x08) >> 0) |	\
		 					  (GPIO_READ(GPIO_PORTQ, 0x40) >> 2) | (GPIO_READ(GPIO_PORTQ, 0x20) >> 0) |	\
		 					  (GPIO_READ(GPIO_PORTQ, 0x10) << 2) | (GPIO_READ(GPIO_PORTG, 0x40) << 1);
	} // end while

}

void _user_interrupt_handler_1(void) {
	GPIO_PORTP_IM = GPIO_PORTP_IM & (~(0x01 << 1));

	// ******* Your Code ******* //
	cnt = 0;

	// *********  FIN ********** //

	GPIO_PORTP_IM = GPIO_PORTP_IM | (0x01 << 1);
	//interrupt set pending/clear pending(p.168~169)
	INTUNPEND2 = INTPEND2;
}

void _user_interrupt_handler_2(void) {
	GPIO_PORTN_IM = GPIO_PORTN_IM & (~(0x01 << 3));

	// ******* Your Code ******* //



	// *********  FIN ********** //

	GPIO_PORTN_IM = GPIO_PORTN_IM | (0x01 << 3);
	//interrupt set pending/clear pending(p.168~169)
	INTUNPEND2 = INTPEND2;
}

void _user_interrupt_handler_3(void) {
	GPIO_PORTE_IM = GPIO_PORTE_IM & (~(0x01 << 5));

	// ******* Your Code ******* //



	// *********  FIN ********** //

	GPIO_PORTE_IM = GPIO_PORTE_IM | (0x01 << 5);
	//interrupt set pending/clear pending(p.168~169)
	INTUNPEND2 = INTPEND2;
}

void _user_interrupt_handler_4(void) {
	GPIO_PORTK_IM = GPIO_PORTK_IM & (~(0x01 << 7));

	// ******* Your Code ******* //
	int push_data = (~GPIO_READ(GPIO_PORTP, (0x01 << 1)) >> 1) & (~GPIO_READ(GPIO_PORTN, (0x01 << 3)) >> 2) & \
		(~GPIO_READ(GPIO_PORTE, (0x01 << 5)) >> 3) & (~GPIO_READ(GPIO_PORTK, (0x01 << 7)) >> 4);

	int dip_data = (GPIO_READ(GPIO_PORTA, 0x08) << 4) | (GPIO_READ(GPIO_PORTA, 0x40) << 0) |
		(GPIO_READ(GPIO_PORTA, 0x80) >> 2) | (GPIO_READ(GPIO_PORTB, 0x08) << 1) |
		(GPIO_READ(GPIO_PORTQ, 0x40) >> 3) | (GPIO_READ(GPIO_PORTQ, 0x20) >> 3) |
		(GPIO_READ(GPIO_PORTQ, 0x10) >> 3) | (GPIO_READ(GPIO_PORTG, 0x40) >> 6);

	GPIO_WRITE(GPIO_PORTL, 0x0f, push_data);
	delay(50000000);
	GPIO_WRITE(GPIO_PORTL, 0x0f, 0);
	GPIO_WRITE(GPIO_PORTL, 0x0f, dip_data);
	delay(50000000);
	GPIO_WRITE(GPIO_PORTL, 0x0f, 0);

	// *********  FIN ********** //

	GPIO_PORTK_IM = GPIO_PORTK_IM | (0x01 << 7);
	//interrupt set pending/clear pending(p.168~169)
	INTUNPEND2 = INTPEND2;
}

int32_t PointerMessage(uint32_t ui32Message, int32_t i32X, int32_t i32Y){
    if(user_X >= 0 && user_X < 480 && user_Y >= 0 && user_Y < 272){
    	//prob_1((int)user_X, (int)user_Y);
    	//prob_2((int)user_X, (int)user_Y);
    	prob_3((int)user_X, (int)user_Y);
    }
    delay(1000000);
	return 0;
}

void _user_Bluetooth_Interrupt_Handler(void) {
	char Bluetooth_Data;

	int loX = 100;
	int loY = 100;

	UART3IM = UART3IM & ~(0x1 << 4);

	Bluetooth_Data = Bluetooth_GetKey();	// 외부 장치로부터 받은 데이터를 저장
	UART_putch(Bluetooth_Data);				// 터미널에 해당 데이터 출력
	DrawRect(loX+move[0],loY+move[1],loX+20+move[0],loY+20+move[1],COLOR_WHITE);
	switch(Bluetooth_Data) {
	case 'w' : move[1]+=10; break;
	case 's' : move[1]-=10; break;
	case 'a' : move[0]-=10; break;
	case 'd' : move[0]+=10; break;
	case '1' : cnt = 0; break;
	case '2' : cnt = 1; break;
	case '3' : cnt = 2; break;
	}
	DrawRect(loX+move[0],loY+move[1],loX+20+move[0],loY+20+move[1],colors2[cnt]);

	UART3IM = UART3IM | (0x1 << 4);
	UART3ICR = UART3ICR | (0x1 << 4);
	INTUNPEND1 = INTPEND1;
}
