#include "Dxwatchdog.h"
#include "PrjInc.h"

static int wathdog_fp;
//int Watchdog_Option = WDIOS_ENABLECARD; // WDIOS_ENABLECARD is enable watchdog
static int Watchdog_Option = WDIOS_DISABLECARD;  //WDIOS_DISABLECARD stop watch dog
static THREAD_HANDLE  watchdog_pthid;
static int watchdog_timeout;
#define PRI_DX_WATCHDOG                15
#define STKSIZE_DX_WATCHDOG            4096

//2s feed dog
static THREAD_RETTYPE  Watchdog_CreateTask(void)
{
    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    int timeout = ((watchdog_timeout/6)*1000-100)*1000;  //100毫秒前喂狗
    while(1) {
        usleep(timeout);
        if (0 > ioctl(wathdog_fp, WDIOC_KEEPALIVE, NULL)) {
            fprintf(stderr, "ioctl error: WDIOC_KEEPALIVE: %s\n", strerror(errno));
        } else {
            //printf("feed dog success!!!\r\n");
        }
        //pthread_testcancel();
    }
	THREAD_RETURN(0);
}

void Watchdog_CancelTask(void)
{
    pthread_cancel(watchdog_pthid);
}

void Watchdog_Enable(void)
{
     Watchdog_Option = WDIOS_ENABLECARD;
     ioctl(wathdog_fp,WDIOC_SETOPTIONS,&Watchdog_Option);
}

void Watchdog_Disable(void)
{
    Watchdog_Option = WDIOS_DISABLECARD;
    ioctl(wathdog_fp,WDIOC_SETOPTIONS,&Watchdog_Option);
}

void Watchdog_Init(void)
{
    struct watchdog_info dog_info;
#if 0
    int ret;
    //oepn ----let dog work  ---80s not feed will reboot
    wathdog_fp = open(DXWATCHDOG_PATH,O_RDWR);
    if (wathdog_fp < 0) {
        printf("open watchdog error!!!!\r\n");
    }
    Watchdog_Enable();
    ret = pthread_create(&watchdog_pthid,NULL,(void *)Watchdog_CreateTask,NULL);
    if (ret != 0) {
        printf("create watchdog task error\r\n");
    }
#endif
    wathdog_fp = open("/dev/watchdog0",O_WRONLY);
    if (wathdog_fp < 0) {
        printf("open /dev/watchdog0 error\r\n");
    }
    if (0 > ioctl(wathdog_fp,WDIOC_GETSUPPORT,&dog_info)) {
        fprintf(stderr,"ioctl error: WDIOC_GETSUPPORT:%s\n",strerror(errno));
    }
    printf("identity:%s\r\n",dog_info.identity);
    printf("version:%u\r\n",dog_info.firmware_version);
    if (0 == (WDIOF_KEEPALIVEPING & dog_info.options)) {
        printf("device not support watchdog\r\n");
    } else {
        printf("device support watchdog\r\n");
    }
    if(0 == (WDIOF_SETTIMEOUT & dog_info.options)) {
        printf("device not support set watchdog time\r\n");
    } else {
        printf("device support set watchdog time\r\n");
    }

    //set watchdog timeout
#if 1
    watchdog_timeout = 30;
    if (0 > ioctl(wathdog_fp,WDIOC_SETTIMEOUT, &watchdog_timeout)) {
        fprintf(stderr,"ioctl error: WDIOC_SETTIMEOUT:%s\n",strerror(errno));
    }
#endif

    //get watchdog timeout
    if (0 > ioctl(wathdog_fp,WDIOC_GETTIMEOUT,&watchdog_timeout)) {
        fprintf(stderr,"ioctl error: WDIOC_GETTIMEOUT:%s\n",strerror(errno));
    }
    printf("current timeout: %ds\n\r\n",watchdog_timeout);

    Watchdog_Enable();
	if ((watchdog_pthid = vos_task_create(Watchdog_CreateTask, 0, "DxWathchdogTsk", PRI_DX_WATCHDOG, STKSIZE_DX_WATCHDOG)) == 0) {
		printf("DxWathchdog Tsk create failed.\r\n");
	} else {
	    vos_task_resume(watchdog_pthid);
	}
}












