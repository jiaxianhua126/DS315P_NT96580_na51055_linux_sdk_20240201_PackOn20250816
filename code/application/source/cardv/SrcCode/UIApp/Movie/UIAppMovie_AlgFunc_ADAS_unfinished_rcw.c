#include "PrjInc.h"
#include "hdal.h"
#include "ImageApp/ImageApp_MovieMulti.h"
#include "sw_md.h"
#include <kwrap/debug.h>
#include <kwrap/error_no.h>
#include <kwrap/task.h>
#include <kwrap/type.h>
#include <kwrap/util.h>
#include "algo_manager.h"

#define PRI_MOVIEALG_ADAS                20//10
#define STKSIZE_MOVIEALG_ADAS            4096


//adas
static THREAD_HANDLE movie_alg_adas_tsk_id;
static UINT32 movie_alg_adas_tsk_run, is_movie_alg_adas_tsk_running;
static UINT32 movie_alg_adas_result = FALSE;

#define ADAS_ALGO_NAME "AdasAlgo"

#define PRI_MOVIEALG_RCW                20//10
#define STKSIZE_MOVIEALG_RCW            4096

//rcw
static THREAD_HANDLE movie_alg_rcw_tsk_id;
static UINT32 movie_alg_rcw_tsk_run, is_movie_alg_rcw_tsk_running;
static UINT32 movie_alg_rcw_result = FALSE;

#define RCW_ALGO_NAME "RcwAlgo"

AlgoEventData adas_eventData;
AlgoHandle adasHandle;
AlgoHandle rcwHandle;
extern UINT8 g_AdasSensitivity;
extern FLOAT g_CurSpeed;

static void MovieAlgFunc_SetSentivity(UINT8 adasSensitivity)
{
	AlgoAttr AlgoAttr_set={0};
	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_LDW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_LDW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_FCW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_FCW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_PED_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_PED_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_STGO_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_STGO_SENSITIVITY,&AlgoAttr_set);
}
static THREAD_RETTYPE MovieAlgFunc_ADAS_Tsk(void)
{
	HD_PATH_ID img_path;
	HD_VIDEO_FRAME video_frame = {0};
	HD_RESULT hd_ret;

	AlgoHandle adas_handle;
	AlgoImages adas_input_image = {0};
	AlgoImage adas_Image[2];
	AlgoImage *imagePack[2];
	AlgoCmdPara para;
	int size = 345600;
	static UINT32 before_algoWarnType = 0;
	//UINT32 err_cnt = 0;
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_1, _CFG_ALG_PATH3);
	is_movie_alg_adas_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&adas_handle,ADAS_ALGO_NAME);
	MovieAlgFunc_SetSentivity(g_AdasSensitivity);


	memset(&adas_input_image,0, sizeof(AlgoImages));
	memset(&adas_eventData,0, sizeof(AlgoEventData));

	for(int i=0;i<2;i++)
	{
		imagePack[i] = &adas_Image[i];
	}
	adas_input_image.imageNum =1;
	adas_input_image.image = imagePack;
	
	movie_alg_adas_tsk_run = true;
   
	while (movie_alg_adas_tsk_run) {
		para.speed = g_CurSpeed;//60
		para.speed = 50;
		hd_ret = ALGO_MANAGER_Invoke(ALGO_ADAS_INVOKE_CMD_SPEED,&para);
		if ((hd_ret = hd_videoproc_pull_out_buf(img_path, &video_frame, -1)) == HD_OK)
		{
			//printf("##### video frame w %d h %d, count %lld\n",video_frame.dim.w,video_frame.dim.h,video_frame.count);
			void * video_viraddr = hd_common_mem_mmap(HD_COMMON_MEM_MEM_TYPE_NONCACHE, video_frame.phy_addr[0], size);
			adas_Image[0].phyAddr = video_frame.phy_addr[0];
			adas_Image[0].virAddr = video_viraddr;
			adas_Image[0].phyAddr_uv = adas_Image[0].phyAddr + 640*360;
			adas_Image[0].u32Stride = 640;
			adas_Image[0].u32Width = 640;
			adas_Image[0].u32Height = 360;
			adas_Image[0].size = size;

			ALGO_MANAGER_ProcessImage(adas_handle,ALGO_PROCESS_CMD_ADAS_BASE_ID,&adas_input_image,&adas_eventData);
			if(adas_eventData.result.type == ALGO_TYPE_ADAS
				&&adas_eventData.result.algoResult.adasResult.calib.calib_process>=1
				&&adas_eventData.result.algoResult.adasResult.calib.calib_process>=100)
			{
				/*printf("warn %x, fcw objsize %d ldw %d ped %d, calib_his %d calib_process %d\n",adas_eventData.result.algoWarnType,
						adas_eventData.result.algoResult.adasResult.fcw.objsize,
						adas_eventData.result.algoResult.adasResult.ldw.lineNum,
						adas_eventData.result.algoResult.adasResult.ped.objsize,
						adas_eventData.result.algoResult.adasResult.calib.calib_history,
						adas_eventData.result.algoResult.adasResult.calib.calib_process
				);*/
				//
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//前车碰撞
			        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FDW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FDW)){//车距过近
			        printf("=====ALGO_ADAS_WARN_TYPE_FDW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPRE)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPRE)){//前车碰撞预报警
			        printf("=====ALGO_ADAS_WARN_TYPE_FPRE====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////车道偏离 左偏离
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
			       Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//车道偏离 右偏离
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//前车起步报警
			        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//行人碰撞
			        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_PD);
			    }
				before_algoWarnType = adas_eventData.result.algoWarnType;
			}

			if ((hd_ret = hd_common_mem_munmap((void*)video_viraddr, size)) != HD_OK) {
				DBG_ERR("hd_common_mem_munmap fail(%d)\n", hd_ret);
			}
			if( (hd_ret = hd_videoproc_release_out_buf(img_path,&video_frame)) != HD_OK){
				DBG_ERR("hd_videoproc_release_out_buf fail(%d)\n",hd_ret);
			}
		}
		//printf(" *** MovieAlgFunc_ADAS_Tsk \r\n");
	}

	is_movie_alg_adas_tsk_running = FALSE;

	THREAD_RETURN(0);
}
static THREAD_RETTYPE MovieAlgFunc_RCW_Tsk(void)
{
	HD_PATH_ID img_path;
	HD_VIDEO_FRAME video_frame = {0};
	HD_RESULT hd_ret;

	AlgoHandle adas_handle;
	AlgoImages adas_input_image = {0};
	AlgoImage adas_Image[2];
	AlgoImage *imagePack[2];
	AlgoCmdPara para;
	int size = 345600;
	static UINT32 before_algoWarnType = 0;
	//UINT32 err_cnt = 0;
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_1, _CFG_ALG_PATH3);
	is_movie_alg_rcw_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&adas_handle,RCW_ALGO_NAME);
	MovieAlgFunc_SetSentivity(g_AdasSensitivity);


	memset(&adas_input_image,0, sizeof(AlgoImages));
	memset(&adas_eventData,0, sizeof(AlgoEventData));

	for(int i=0;i<2;i++)
	{
		imagePack[i] = &adas_Image[i];
	}
	adas_input_image.imageNum =1;
	adas_input_image.image = imagePack;
	
	movie_alg_rcw_tsk_run = true;
   
	while (movie_alg_rcw_tsk_run) {
		//para.speed = g_CurSpeed;//60
		para.speed = 50;
		hd_ret = ALGO_MANAGER_Invoke(ALGO_ADAS_INVOKE_CMD_SPEED,&para);
		if ((hd_ret = hd_videoproc_pull_out_buf(img_path, &video_frame, -1)) == HD_OK)
		{
			//printf("##### video frame w %d h %d, count %lld\n",video_frame.dim.w,video_frame.dim.h,video_frame.count);
			void * video_viraddr = hd_common_mem_mmap(HD_COMMON_MEM_MEM_TYPE_NONCACHE, video_frame.phy_addr[0], size);
			adas_Image[0].phyAddr = video_frame.phy_addr[0];
			adas_Image[0].virAddr = video_viraddr;
			adas_Image[0].phyAddr_uv = adas_Image[0].phyAddr + 640*360;
			adas_Image[0].u32Stride = 640;
			adas_Image[0].u32Width = 640;
			adas_Image[0].u32Height = 360;
			adas_Image[0].size = size;

			ALGO_MANAGER_ProcessImage(adas_handle,ALGO_PROCESS_CMD_ADAS_BASE_ID,&adas_input_image,&adas_eventData);
			if(adas_eventData.result.type == ALGO_TYPE_ADAS
				&&adas_eventData.result.algoResult.adasResult.calib.calib_process>=1
				&&adas_eventData.result.algoResult.adasResult.calib.calib_process>=100)
			{
				/*printf("warn %x, fcw objsize %d ldw %d ped %d, calib_his %d calib_process %d\n",adas_eventData.result.algoWarnType,
						adas_eventData.result.algoResult.adasResult.fcw.objsize,
						adas_eventData.result.algoResult.adasResult.ldw.lineNum,
						adas_eventData.result.algoResult.adasResult.ped.objsize,
						adas_eventData.result.algoResult.adasResult.calib.calib_history,
						adas_eventData.result.algoResult.adasResult.calib.calib_process
				);*/
				//
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//前车碰撞
			        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FDW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FDW)){//车距过近
			        printf("=====ALGO_ADAS_WARN_TYPE_FDW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPRE)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPRE)){//前车碰撞预报警
			        printf("=====ALGO_ADAS_WARN_TYPE_FPRE====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////车道偏离 左偏离
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
			       Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//车道偏离 右偏离
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//前车起步报警
			        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//行人碰撞
			        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
			        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_PD);
			    }
				before_algoWarnType = adas_eventData.result.algoWarnType;
			}

			if ((hd_ret = hd_common_mem_munmap((void*)video_viraddr, size)) != HD_OK) {
				DBG_ERR("hd_common_mem_munmap fail(%d)\n", hd_ret);
			}
			if( (hd_ret = hd_videoproc_release_out_buf(img_path,&video_frame)) != HD_OK){
				DBG_ERR("hd_videoproc_release_out_buf fail(%d)\n",hd_ret);
			}
		}
		//printf(" *** MovieAlgFunc_RCW_Tsk \r\n");
	}

	is_movie_alg_rcw_tsk_running = FALSE;

	THREAD_RETURN(0);
}

void MovieAlgFunc_ADAS_Init(void)
{
	printf("@@@ %s \n",__func__);

	// add by keytech, init algo, using debug mode
	
	AlgoInitPara initPara;
	initPara.activePath = NULL;
	initPara.serialPath = NULL;
	initPara.logPath = NULL;
	initPara.debug_enable = 1;
	int ret = ALGO_MANAGER_Init(&initPara);
	printf("@@@ ALGO_MANAGER_Init ret %d\n",ret);

	// init Adas ,add by keytech
	
	//char name[32] = "AlgoAdas";
	AlgoCreatePara creatPara;
	memset(&creatPara,0,sizeof(AlgoCreatePara));
	memcpy(creatPara.algoName,ADAS_ALGO_NAME,strlen(ADAS_ALGO_NAME));

	creatPara.algoPara.modelPath =  "/data/adas/model_file";
	creatPara.type = ALGO_TYPE_ADAS;
	creatPara.algoPara.freeCallback =NULL;
	creatPara.algoPara.eventCallback =NULL;
	creatPara.algoPara.configPath = "/data/adas/model_file";
	creatPara.algoPara.imageWidth = 1920;
	creatPara.algoPara.imageHeight = 1080;
	creatPara.algoPara.fps = 10;
	creatPara.algoPara.sync_enable = 1;


	ALGO_MANAGER_Create(&adasHandle,&creatPara);
	printf("@@@@ ALGO_MANAGER_Create Adas success\n");

	// init Rcw, add by keytech
	//char rcw_name[32] = "AlgoRcw";
	AlgoCreatePara rcw_creatPara;
	memset(&rcw_creatPara,0,sizeof(AlgoCreatePara));
	memcpy(rcw_creatPara.algoName,RCW_ALGO_NAME,strlen(RCW_ALGO_NAME));

	rcw_creatPara.algoPara.modelPath =  "/data/adas/model_file";
	rcw_creatPara.type = ALGO_TYPE_RCW;
	rcw_creatPara.algoPara.freeCallback =NULL;
	rcw_creatPara.algoPara.eventCallback =NULL;
	rcw_creatPara.algoPara.configPath = "/data/adas/model_file";
	rcw_creatPara.algoPara.imageWidth = 1920;
	rcw_creatPara.algoPara.imageHeight = 1080;
	rcw_creatPara.algoPara.fps = 8;
	rcw_creatPara.algoPara.sync_enable = 1;

	ALGO_MANAGER_Create(&rcwHandle,&rcw_creatPara);
	printf("@@@@ ALGO_MANAGER_Create Rcw success\n");
}

ER MovieAlgFunc_ADAS_InstallID(void)
{
	ER ret = E_OK;

	MovieAlgFunc_ADAS_Init();

	movie_alg_adas_tsk_run = FALSE;
	is_movie_alg_adas_tsk_running = FALSE;

	if ((movie_alg_adas_tsk_id = vos_task_create(MovieAlgFunc_ADAS_Tsk, 0, "MovieAlgADASTsk", PRI_MOVIEALG_ADAS, STKSIZE_MOVIEALG_ADAS)) == 0) {
		DBG_ERR("MovieAlgADASTsk create failed.\r\n");
		ret = E_SYS;
	} else {
		movie_alg_adas_tsk_run = TRUE;
		vos_task_resume(movie_alg_adas_tsk_id);
	}

	movie_alg_rcw_tsk_run = FALSE;
	is_movie_alg_rcw_tsk_running = FALSE;

	if ((movie_alg_rcw_tsk_id = vos_task_create(MovieAlgFunc_RCW_Tsk, 0, "MovieAlgRCWTsk", PRI_MOVIEALG_RCW, STKSIZE_MOVIEALG_RCW)) == 0) {
		DBG_ERR("MovieAlgRCWTsk create failed.\r\n");
		ret = E_SYS;
	} else {
		movie_alg_rcw_tsk_run = TRUE;
		vos_task_resume(movie_alg_rcw_tsk_id);
	}

	
	return ret;
}

ER MovieAlgFunc_ADAS_UninstallID(void)
{
	ER ret = E_OK;
	UINT32 delay_cnt;

	delay_cnt = 50;//10
	movie_alg_adas_tsk_run = FALSE;
	movie_alg_rcw_tsk_run = FALSE;
	while ((is_movie_alg_adas_tsk_running||is_movie_alg_rcw_tsk_running) && delay_cnt) {
		vos_util_delay_ms(10);//50
		delay_cnt --;
	}

	if (is_movie_alg_adas_tsk_running) {
		DBG_DUMP("Destroy MovieAlgADASTsk\r\n");
		vos_task_destroy(movie_alg_adas_tsk_id);
	}

	if (is_movie_alg_rcw_tsk_running) {
		DBG_DUMP("Destroy MovieAlgRCWTsk\r\n");
		vos_task_destroy(movie_alg_rcw_tsk_id);
	}

	printf("algo end\n");
	ALGO_MANAGER_Destroy(adasHandle);
	printf("release adas\n");
	ALGO_MANAGER_Destroy(rcwHandle);
	printf("release rear\n");
	ALGO_MANAGER_DeInit();
	printf(" end end end\n");

	return ret;
}

UINT32 MovieAlgFunc_ADAS_GetResult(void)
{
	return movie_alg_adas_result;
}

UINT32 MovieAlgFunc_RCW_GetResult(void)
{
	return movie_alg_rcw_result;
}

