#include "DxEdog_Sound.h"
#include "hd_common.h"
#include "Edog/EDogGlobal.h"
#include "PrjInc.h"
#include "DxInput.h"


#define __MODULE__          DxSoundEdogTask
#define __DBGLVL__          2 // 0=FATAL, 1=ERR, 2=WRN, 3=UNIT, 4=FUNC, 5=IND, 6=MSG, 7=VALUE, 8=USER
#define __DBGFLT__          "*" //*=All, [mark]=CustomClass
#include <kwrap/debug.h>

static THREAD_HANDLE  edogSound_pid;
#define PRI_DX_EDOGSOUND                15
#define STKSIZE_DX_EDOGSOUND            4096
pthread_mutex_t lockSound = PTHREAD_MUTEX_INITIALIZER;
static BOOL     g_bDxEdogSoundTskOpened = FALSE;
static BOOL     g_bDxEdogSoundTskClosing = FALSE;
ID FLG_ID_EDOGSOUND = 0;

extern void DogSoundCycPlay(void);



void *  EdogSound_CreateTask(void *pvParameters)
{
	FLGPTN	FlgPtn;
	printf("...............EDOGSoundTsk.................!!!!\r\n");
	THREAD_ENTRY();

	while(1)
	{
		vos_flag_set(FLG_ID_EDOGSOUND, FLGEDOGSOUND_IDLE);
		PROFILE_TASK_IDLE();
		vos_flag_wait(&FlgPtn, FLG_ID_EDOGSOUND, FLGEDOGSOUND_UPDATE, TWF_ORW | TWF_CLR);
		PROFILE_TASK_BUSY();
		vos_flag_clr(FLG_ID_EDOGSOUND, FLGEDOGSOUND_IDLE);
		//printf("11111\r\n");
		DogSoundCycPlay();

	}
	return NULL;

}

void EdogSound_Handle_Init(void)
{
	if (g_bDxEdogSoundTskOpened) {
		return ;
	}
	vos_flag_create(&FLG_ID_EDOGSOUND, NULL, "FLG_ID_EDOGSOUND");
	vos_flag_clr(FLG_ID_EDOGSOUND, FLGEDOGSOUND_ALL);
	g_bDxEdogSoundTskOpened = TRUE;
	g_bDxEdogSoundTskClosing = FALSE;

	if ((edogSound_pid = vos_task_create(EdogSound_CreateTask, 0, "DxEdogSoundTsk", PRI_DX_EDOGSOUND, STKSIZE_DX_EDOGSOUND)) == 0) {
		printf("DxEdogSound Tsk create failed.\r\n");
	} else {
	    vos_task_resume(edogSound_pid);
	}
}

void EdogSoundTsk_TrigUpdate(void)
{
	if(g_bDxEdogSoundTskOpened&&!g_bDxEdogSoundTskClosing){
		set_flg(FLG_ID_EDOGSOUND, FLGEDOGSOUND_UPDATE);
	}
}

ER EdogSoundTsk_Close(void)
{
	FLGPTN  FlgPtn;

	if (!g_bDxEdogSoundTskOpened) {
		return E_SYS;
	}

	g_bDxEdogSoundTskClosing = TRUE;
	vos_flag_wait(&FlgPtn, FLG_ID_EDOGSOUND, FLGEDOGSOUND_IDLE, TWF_ORW);
	vos_task_destroy(edogSound_pid);
	vos_flag_destroy(FLG_ID_EDOGSOUND);
	g_bDxEdogSoundTskOpened = FALSE;

	return E_OK;
}

