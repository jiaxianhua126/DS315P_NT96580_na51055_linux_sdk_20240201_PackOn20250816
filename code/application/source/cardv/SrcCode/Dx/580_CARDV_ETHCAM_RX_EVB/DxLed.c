
#include "DxLed.h"
#include "DxGpio.h"

BOOL Led_FlashEn = FALSE;
pthread_t led_thr;

void select_sleep(unsigned int mSectime)
{
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = mSectime*1000;
	select(0,NULL,NULL,NULL,&timeout);
}


void *Led_Flash(void *arg)
{
	//使用for循环，根据系统分配的频率
	static int Led_State = 0;
	led_cfg *c2 = (led_cfg *) arg;
    printf("led_num = %d,led_time = %d \r\n",c2->led_num,c2->led_time);
	while(1) {
		Led_State = !Led_State;
		if (Led_State) {
				select_sleep(c2->led_time);
                Control_LedTurn(REC_LED,1);
				//printf("LED ON \r\n");
		} else {
				select_sleep(c2->led_time);
                Control_LedTurn(REC_LED,0);
				//printf("LED OFF \r\n");
		}
	}

	return 0;
}

void Led_Install(unsigned int Led_Num,unsigned int Led_time)
{
	static led_cfg c1;
	if(!Led_FlashEn) {
		c1.led_num = Led_Num;
		c1.led_time = Led_time;
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
		pthread_create(&led_thr,NULL,(void *)Led_Flash,(void *)&c1);
		Led_FlashEn = TRUE;
	}
}

void Led_Uninstall(void)
{
	if(Led_FlashEn) {
		pthread_cancel(led_thr);
		Led_FlashEn = FALSE;
		 Control_LedTurn(REC_LED,1);
	}
}





