#include "DxEdog.h"
#include "hd_common.h"
#include "Edog/EDogGlobal.h"

pthread_t edog_pid;
//static BOOL run_control = FALSE;
void *Edog_CreateTask(void)
{
	UINT32 n_last_fd_rst_time = 0;
	//kent_tsk();

	printf("...............EDOGRecTsk.................!!!!\r\n");

	while(1)
	{
		if(hd_gettime_ms() - n_last_fd_rst_time >= 200)//200ms
		{
			n_last_fd_rst_time = hd_gettime_ms();
			//printf("==========%dms==============\r\n",n_last_fd_rst_time);
			Edog_Run();
		}
	}
}

#if 0
void Edog_EnableTask(void)
{
    run_control = TRUE;
}

void Edog_DisableTask(void)
{
    run_control = FALSE;
}
#endif
void Edog_Handle_Init(void)
{
    int ret;
    ret = pthread_create(&edog_pid,NULL,(void *)Edog_CreateTask,NULL);
    if (ret != 0) {
        printf("create edog task error\r\n");
    }else{
        printf("create edog task success\r\n");
	}
}

