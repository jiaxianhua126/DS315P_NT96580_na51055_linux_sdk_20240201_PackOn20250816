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
#include "UIApp/Network/EthCamAppSocket.h"
#include "UIApp/Network/EthCamAppCmd.h"
#include <unistd.h>


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

AlgoEventData rcw_eventData;
AlgoHandle rcwHandle;

extern AlgoEventData adas_eventData_app;

extern AlgoEventData rcw_eventData_app;

extern FLOAT g_CurSpeed;


BOOL ADAS_OpenState = FALSE;
UINT8 ActiveFiles_flag = 0;
pthread_mutex_t g_data_mutex_front = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_data_mutex_rear = PTHREAD_MUTEX_INITIALIZER;
BOOL ADAS_Auth_Test = FALSE;
extern BOOL SysInit_getintoadas_mode_getstd(void);

static void MovieAlgFunc_ADASSetSentivity(void)
{
	AlgoAttr AlgoAttr_set={0};
	UINT8 adasSensitivity = 0;
	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_LDW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	switch(SysGetFlag(FL_MOVIE_LDWS))
	{
		case ADAS_LDWS_LOW:
			adasSensitivity = SEN_LOW;
			break;
		case ADAS_LDWS_MID:
			adasSensitivity = SEN_MIDDLE;
			break;
		case ADAS_LDWS_HIGH:
			adasSensitivity = SEN_HIGH;
			break;
		case ADAS_LDWS_OFF:
		default:
			adasSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_LDW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_FCW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	switch(SysGetFlag(FL_MOVIE_FCW))
	{
		case ADAS_FCW_LOW:
			adasSensitivity = SEN_LOW;
			break;
		case ADAS_FCW_MID:
			adasSensitivity = SEN_MIDDLE;
			break;
		case ADAS_FCW_HIGH:
			adasSensitivity = SEN_HIGH;
			break;
		case ADAS_FCW_OFF:
		default:
			adasSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_FCW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_PED_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	switch(SysGetFlag(FL_PCW))
	{
		case ADAS_PCW_LOW:
			adasSensitivity = SEN_LOW;
			break;
		case ADAS_PCW_MID:
			adasSensitivity = SEN_MIDDLE;
			break;
		case ADAS_PCW_HIGH:
			adasSensitivity = SEN_HIGH;
			break;
		case ADAS_PCW_OFF:
		default:
			adasSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_PED_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_STGO_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	switch(SysGetFlag(FL_SNG))
	{
		case ADAS_SNG_LOW:
			adasSensitivity = SEN_LOW;
			break;
		case ADAS_SNG_MID:
			adasSensitivity = SEN_MIDDLE;
			break;
		case ADAS_SNG_HIGH:
			adasSensitivity = SEN_HIGH;
			break;
		case ADAS_SNG_OFF:
		default:
			adasSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_STGO_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_VIRBUMPER_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
	switch(SysGetFlag(FL_ADAS_VIRTUAL_BUMPER))
	{
		case ADAS_VIRTUAL_BUMPER_LOW:
			adasSensitivity = SEN_LOW;
			break;
		case ADAS_VIRTUAL_BUMPER_MID:
			adasSensitivity = SEN_MIDDLE;
			break;
		case ADAS_VIRTUAL_BUMPER_HIGH:
			adasSensitivity = SEN_HIGH;
			break;
		case ADAS_VIRTUAL_BUMPER_OFF:
		default:
			adasSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.adasAttr.senType = adasSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_VIRBUMPER_SENSITIVITY,&AlgoAttr_set);
}

static void MovieAlgFunc_SetLdwSpeed(int speed)
{
	AlgoAttr AlgoAttr_set={0};
	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_LDW_WARN_SPEED,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.speedThreshold);
	AlgoAttr_set.adasAttr.speedThreshold = speed;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_ADAS_LDW_WARN_SPEED,&AlgoAttr_set);
}

static void MovieAlgFunc_RCWSetSpeed(int speed)
{
	AlgoAttr AlgoAttr_set={0};
	ALGO_MANAGER_GetAttr(ALGO_ATTR_RCW_SPEED_THRESHOLD,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.rcwAttr.speedThreshold);
	AlgoAttr_set.rcwAttr.speedThreshold = speed;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_RCW_SPEED_THRESHOLD,&AlgoAttr_set);
}

static void MovieAlgFunc_RCWSetSentivity(void)
{
	AlgoAttr AlgoAttr_set={0};
	UINT8 rcwSensitivity = 0;
	ALGO_MANAGER_GetAttr(ALGO_ATTR_RCW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.rcwAttr.sen);
	switch(SysGetFlag(FL_RCW))
	{
		case ADAS_RCW_LOW:
			rcwSensitivity = SEN_LOW;
			break;
		case ADAS_RCW_MID:
			rcwSensitivity = SEN_MIDDLE;
			break;
		case ADAS_RCW_HIGH:
			rcwSensitivity = SEN_HIGH;
			break;
		case ADAS_RCW_OFF:
		default:
			rcwSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.rcwAttr.sen = rcwSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_RCW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_RCW_LCA_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.rcwAttr.sen);
	switch(SysGetFlag(FL_ADAS_LCAWS))
	{
		case ADAS_LCAWS_LOW:
			rcwSensitivity = SEN_LOW;
			break;
		case ADAS_LCAWS_MID:
			rcwSensitivity = SEN_MIDDLE;
			break;
		case ADAS_LCAWS_HIGH:
			rcwSensitivity = SEN_HIGH;
			break;
		case ADAS_LCAWS_OFF:
		default:
			rcwSensitivity = SEN_LOW;
			break;
	}
	AlgoAttr_set.rcwAttr.sen = rcwSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_RCW_LCA_SENSITIVITY,&AlgoAttr_set);
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
	AlgoAttr attr_debug_lvl ={0};
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_1, _CFG_ALG_PATH3);
	printf("=========%s====img_path:%d=====\n",__func__,img_path);
	is_movie_alg_adas_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&adas_handle,ADAS_ALGO_NAME);
	MovieAlgFunc_ADASSetSentivity();
	MovieAlgFunc_SetLdwSpeed(60);
	
	attr_debug_lvl.logLevel = ALGO_LEVEL_WARN;
	hd_ret = ALGO_MANAGER_SetAttr(ALGO_ATTR_LOGLEVEL,&attr_debug_lvl);
	if(hd_ret != 0)
	{
		printf("algo setattr failed %x \n",hd_ret);
	}

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
		if (SysInit_getintoadas_mode_getstd()) {
			para.speed = 60;//60
		}else{
			para.speed = g_CurSpeed;//60
		}
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

			if(adas_eventData.result.type == ALGO_TYPE_ADAS && adas_eventData.result.algoResult.adasResult.calib.calib_history == 0)
			{				
				//if(adas_eventData.result.algoResult.adasResult.calib.calib_process < 100)
					//printf("calib_process:%d==ADAS===\n",adas_eventData.result.algoResult.adasResult.calib.calib_process);
				
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
					#if  1
					if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
						//printf("LOCK success===1.\r\n");
						memcpy(&adas_eventData_app,&adas_eventData,sizeof(adas_eventData));
						pthread_mutex_unlock(&g_data_mutex_front);
					}
					#endif
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//ǰ����ײ
				        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
						if(SysGetFlag(FL_MOVIE_FCW) != ADAS_FCW_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//ǰ����ײԤ����
				        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
						if(SysGetFlag(FL_PCW) != ADAS_PCW_OFF|| SysInit_getintoadas_mode_getstd())
					        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FPW);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////����ƫ�� ��ƫ��
				        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
						if(SysGetFlag(FL_MOVIE_LDWS) != ADAS_LDWS_OFF|| SysInit_getintoadas_mode_getstd())
				       		Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//����ƫ�� ��ƫ��
				        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
						if(SysGetFlag(FL_MOVIE_LDWS) != ADAS_LDWS_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//ǰ���𲽱���
				        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
						if(SysGetFlag(FL_SNG) != ADAS_SNG_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)){//������ײ
				        printf("=====ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS====\r\n");
						if(SysGetFlag(FL_ADAS_VIRTUAL_BUMPER) != ADAS_VIRTUAL_BUMPER_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_VIRTUAL_BUMPERS);
				    }
					before_algoWarnType = adas_eventData.result.algoWarnType;
				}
			}
			else if(adas_eventData.result.type == ALGO_TYPE_ADAS && 
					adas_eventData.result.algoResult.adasResult.calib.calib_history == 1)
			{	
				#if 1
				if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
					//printf("LOCK success.\r\n");
					memcpy(&adas_eventData_app,&adas_eventData,sizeof(adas_eventData));
					pthread_mutex_unlock(&g_data_mutex_front);
				}
				#endif
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//ǰ����ײ
			        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
					if(SysGetFlag(FL_MOVIE_FCW) != ADAS_FCW_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//ǰ����ײԤ����
			        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
					if(SysGetFlag(FL_PCW) != ADAS_PCW_OFF|| SysInit_getintoadas_mode_getstd())
				        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FPW);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////����ƫ�� ��ƫ��
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
					if(SysGetFlag(FL_MOVIE_LDWS) != ADAS_LDWS_OFF|| SysInit_getintoadas_mode_getstd())
			       		Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//����ƫ�� ��ƫ��
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
					if(SysGetFlag(FL_MOVIE_LDWS) != ADAS_LDWS_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//ǰ���𲽱���
			        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
					if(SysGetFlag(FL_SNG) != ADAS_SNG_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)){//������ײ
			        printf("=====ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS====\r\n");
					if(SysGetFlag(FL_ADAS_VIRTUAL_BUMPER) != ADAS_VIRTUAL_BUMPER_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_VIRTUAL_BUMPERS);
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

#if 1
static THREAD_RETTYPE MovieAlgFunc_RCW_Tsk(void)
{	
	HD_PATH_ID img_path;
	HD_VIDEO_FRAME video_frame = {0};
	HD_RESULT hd_ret;

	AlgoHandle rcw_handle;
	AlgoImages rcw_input_image = {0};
	AlgoImage rcw_Image[2];
	AlgoImage *imagePack[2];
	AlgoCmdPara para;
	int size = 345600;
	static UINT32 before_algoWarnType = 0;	
	AlgoAttr attr_debug_lvl ={0};
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_2, _CFG_ALG_PATH3);
	//img_path = _CFG_ETHCAM_ID_1;
	printf("=========%s====img_path:%d=====\n",__func__,img_path);
	is_movie_alg_rcw_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&rcw_handle,RCW_ALGO_NAME);
	MovieAlgFunc_RCWSetSentivity();
	MovieAlgFunc_RCWSetSpeed(10);

	attr_debug_lvl.logLevel = ALGO_LEVEL_WARN;
	hd_ret = ALGO_MANAGER_SetAttr(ALGO_ATTR_LOGLEVEL,&attr_debug_lvl);
	if(hd_ret != 0)
	{
		printf("algo setattr failed %x \n",hd_ret);
	}

	memset(&rcw_input_image,0, sizeof(AlgoImages));
	memset(&rcw_eventData,0, sizeof(AlgoEventData));

	for(int i=0;i<2;i++)
	{
		imagePack[i] = &rcw_Image[i];
	}
	rcw_input_image.imageNum =1;
	rcw_input_image.image = imagePack;
	
	movie_alg_rcw_tsk_run = true;
   
	while (movie_alg_rcw_tsk_run) {
		if (SysInit_getintoadas_mode_getstd()) {
			para.speed = 60;
		}else{
			para.speed = g_CurSpeed;//60
		}
		hd_ret = ALGO_MANAGER_Invoke(ALGO_RCW_INVOKE_CMD_SPEED,&para);
		if ((hd_ret = hd_videoproc_pull_out_buf(img_path, &video_frame, -1)) == HD_OK)
		//if ((hd_ret = ImageApp_MovieMulti_DispPullOut(img_path, &video_frame, -1)) == HD_OK)
		{
			//printf("##### video frame w %d h %d, count %lld\n",video_frame.dim.w,video_frame.dim.h,video_frame.count);
			void * video_viraddr = hd_common_mem_mmap(HD_COMMON_MEM_MEM_TYPE_NONCACHE, video_frame.phy_addr[0], size);
			rcw_Image[0].phyAddr = video_frame.phy_addr[0];
			rcw_Image[0].virAddr = video_viraddr;
			rcw_Image[0].phyAddr_uv = rcw_Image[0].phyAddr + 640*360;
			rcw_Image[0].u32Stride = 640;
			rcw_Image[0].u32Width = 640;
			rcw_Image[0].u32Height = 360;
			rcw_Image[0].size = size;
			
			ALGO_MANAGER_ProcessImage(rcw_handle,ALGO_PROCESS_CMD_RCW_BASE_ID,&rcw_input_image,&rcw_eventData);

			if(rcw_eventData.result.type == ALGO_TYPE_RCW && rcw_eventData.result.algoResult.rcwResult.calib.calib_history == 0)
			{
				//if(rcw_eventData.result.algoResult.rcwResult.calib.calib_process < 100)
					//printf("calib_process:%d===RCW==\n",rcw_eventData.result.algoResult.rcwResult.calib.calib_process);
				
				if(rcw_eventData.result.type == ALGO_TYPE_RCW &&rcw_eventData.result.algoResult.rcwResult.calib.calib_process>=1
					&&rcw_eventData.result.algoResult.rcwResult.calib.calib_process>=100)
				{
					/*printf("warn %x, fcw objsize %d ldw %d ped %d, calib_his %d calib_process %d\n",adas_eventData.result.algoWarnType,
							adas_eventData.result.algoResult.adasResult.fcw.objsize,
							adas_eventData.result.algoResult.adasResult.ldw.lineNum,
							adas_eventData.result.algoResult.adasResult.ped.objsize,
							adas_eventData.result.algoResult.adasResult.calib.calib_history,
							adas_eventData.result.algoResult.adasResult.calib.calib_process
					);*/
					//
					#if 1
					if (pthread_mutex_trylock(&g_data_mutex_rear) == 0) {
						memcpy(&rcw_eventData_app,&rcw_eventData,sizeof(rcw_eventData));
						pthread_mutex_unlock(&g_data_mutex_rear);
					}
					#endif
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)){//����ײ
				        printf("=====ALGO_RCW_WARN_TYPE_RCW_REAR====\r\n");
						if(SysGetFlag(FL_RCW) != ADAS_RCW_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_RCW_REAR);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)){//����г�
				        printf("=====ALGO_RCW_WARN_TYPE_LCA_LEFT====\r\n");
						if(SysGetFlag(FL_ADAS_LCAWS) != ADAS_LCAWS_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_LEFT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)){//�Ҳ��г�
				        printf("=====ALGO_RCW_WARN_TYPE_LCA_RIGHT====\r\n");
						if(SysGetFlag(FL_ADAS_LCAWS) != ADAS_LCAWS_OFF|| SysInit_getintoadas_mode_getstd())
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_RIGHT);
				    }
					before_algoWarnType = rcw_eventData.result.algoWarnType;
				}
			}
			else if(rcw_eventData.result.type == ALGO_TYPE_RCW && rcw_eventData.result.algoResult.rcwResult.calib.calib_history == 1)
			{
				#if  1	
				if (pthread_mutex_trylock(&g_data_mutex_rear) == 0) {
					memcpy(&rcw_eventData_app,&rcw_eventData,sizeof(rcw_eventData));
					pthread_mutex_unlock(&g_data_mutex_rear);
				}
				#endif
				if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)){//ǰ����ײ
			        printf("=====ALGO_RCW_WARN_TYPE_RCW_REAR====\r\n");
					if(SysGetFlag(FL_RCW) != ADAS_RCW_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_RCW_REAR);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)){//�������
			        printf("=====ALGO_RCW_WARN_TYPE_LCA_LEFT====\r\n");
					if(SysGetFlag(FL_ADAS_LCAWS) != ADAS_LCAWS_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)){//ǰ����ײԤ����
			        printf("=====ALGO_RCW_WARN_TYPE_LCA_RIGHT====\r\n");
					if(SysGetFlag(FL_ADAS_LCAWS) != ADAS_LCAWS_OFF|| SysInit_getintoadas_mode_getstd())
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_RIGHT);
			    }
				before_algoWarnType = rcw_eventData.result.algoWarnType;
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
#else
static THREAD_RETTYPE MovieAlgFunc_RCW_Ethcam_Tsk(void)
{	
	printf("=========%s=========\n",__func__);
	//HD_PATH_ID img_path;
	HD_VIDEO_FRAME video_frame = {0};
	HD_RESULT hd_ret;

	AlgoHandle rcw_handle;
	AlgoImages rcw_input_image = {0};
	AlgoImage rcw_Image[2];
	AlgoImage *imagePack[2];
	AlgoCmdPara para;
	int size = 345600;
	static UINT32 before_algoWarnType = 0;
	
	UINT32 ethcam_index = 0; // 假设只有一个后路以太网摄像�?	UINT32 ethcam_id;
	HD_RESULT ret = E_OK; // 添加错误�?	
	THREAD_ENTRY();
	
	// 以太网后路摄像头索引
	ethcam_id = _CFG_ETHCAM_ID_1 + ethcam_index;

	is_movie_alg_rcw_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&rcw_handle,RCW_ALGO_NAME);
	MovieAlgFunc_SetSentivity(g_AdasSensitivity);


	memset(&rcw_input_image,0, sizeof(AlgoImages));
	memset(&rcw_eventData,0, sizeof(AlgoEventData));

	for(int i=0;i<2;i++)
	{
		imagePack[i] = &rcw_Image[i];
	}
	rcw_input_image.imageNum =1;
	rcw_input_image.image = imagePack;
	
	movie_alg_rcw_tsk_run = true;
   
	while (movie_alg_rcw_tsk_run) {
		//para.speed = g_CurSpeed;//60
		para.speed = 60;
		//printf("=========%s====speed�?d=====\n",__func__,g_CurSpeed);
		hd_ret = ALGO_MANAGER_Invoke(ALGO_RCW_INVOKE_CMD_SPEED,&para);

		// 检查以太网摄像头是否连接并获取数据
        if (ImageApp_MovieMulti_EthCamLinkForDispStatus(ethcam_id)) {
			// 根据系统标志选择不同的数据源
            #if (ETH_REARCAM_CLONE_FOR_DISPLAY == ENABLE)
            if (socketCliEthData2_IsRecv(ethcam_index)) 
            #else
            if (socketCliEthData1_IsRecv(ethcam_index)) 
            #endif
			{
				if ((ret = ImageApp_MovieMulti_DispPullOut(ethcam_id, &video_frame, 150)) != HD_OK) {
					 // 错误处理
                    DBG_ERR("ethcam pull_out yuv error[%d]=%d\r\n", ethcam_index, ret);
                    if(ret == HD_ERR_BAD_DATA){
                        DBG_ERR("Dec err!, path_id=%d\r\n", ethcam_index);
                        if(ImageApp_MovieMulti_IsStreamRunning(ethcam_id)){
                            Ux_PostEvent(NVTEVT_CB_MOVIE_SLOW, 0);
                        }
                        // 尝试重置以太网连�?                        EthCamCmd_GetFrameTimerEn(0);
                        EthCam_SendXMLCmd(ethcam_index, ETHCAM_PORT_DATA1, ETHCAM_CMD_TX_RESET_I, 0);
                        #if(ETH_REARCAM_CLONE_FOR_DISPLAY == ENABLE)
                        EthCam_SendXMLCmd(ethcam_index, ETHCAM_PORT_DATA2, ETHCAM_CMD_TX_RESET_I, 0);
                        #endif
                        EthCamCmd_GetFrameTimerEn(1);
                        vos_util_delay_ms(100); // 等待重置完成
                    }
                    continue;
				}else{
						//printf("##### video frame w %d h %d, count %lld\n",video_frame.dim.w,video_frame.dim.h,video_frame.count);
						void * video_viraddr = hd_common_mem_mmap(HD_COMMON_MEM_MEM_TYPE_NONCACHE, video_frame.phy_addr[0], size);
						rcw_Image[0].phyAddr = video_frame.phy_addr[0];
						rcw_Image[0].virAddr = video_viraddr;
						rcw_Image[0].phyAddr_uv = rcw_Image[0].phyAddr + 640*360;
						rcw_Image[0].u32Stride = 640;
						rcw_Image[0].u32Width = 640;
						rcw_Image[0].u32Height = 360;
						rcw_Image[0].size = size;

						hd_ret = ALGO_MANAGER_ProcessImage(rcw_handle,ALGO_PROCESS_CMD_RCW_BASE_ID,&rcw_input_image,&rcw_eventData);

						if(rcw_eventData.result.algoResult.rcwResult.calib.calib_process < 100)
							printf("calib_process�?d===RCW==hd_ret:%d \n",rcw_eventData.result.algoResult.rcwResult.calib.calib_process,hd_ret);
						
						if(rcw_eventData.result.type == ALGO_TYPE_RCW
							&&rcw_eventData.result.algoResult.rcwResult.calib.calib_process>=1
							&&rcw_eventData.result.algoResult.rcwResult.calib.calib_process>=100)
						{
							/*printf("warn %x, fcw objsize %d ldw %d ped %d, calib_his %d calib_process %d\n",adas_eventData.result.algoWarnType,
									adas_eventData.result.algoResult.adasResult.fcw.objsize,
									adas_eventData.result.algoResult.adasResult.ldw.lineNum,
									adas_eventData.result.algoResult.adasResult.ped.objsize,
									adas_eventData.result.algoResult.adasResult.calib.calib_history,
									adas_eventData.result.algoResult.adasResult.calib.calib_process
							);*/
							//
							if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)){//ǰ����ײ
						        printf("=====ALGO_RCW_WARN_TYPE_RCW_REAR====\r\n");
						        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_RCW_REAR);
						    }
							if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)){//�������
						        printf("=====ALGO_RCW_WARN_TYPE_LCA_LEFT====\r\n");
						        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_LEFT);
						    }
							if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)){//ǰ����ײԤ����
						        printf("=====ALGO_RCW_WARN_TYPE_LCA_RIGHT====\r\n");
						        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_RIGHT);
						    }
							before_algoWarnType = rcw_eventData.result.algoWarnType;
						}

						if ((hd_ret = hd_common_mem_munmap((void*)video_viraddr, size)) != HD_OK) {
							DBG_ERR("hd_common_mem_munmap fail(%d)\n", hd_ret);
						}
						if( (hd_ret = ImageApp_MovieMulti_DispReleaseOut(ethcam_id,&video_frame)) != HD_OK){
							DBG_ERR("hd_videoproc_release_out_buf fail(%d)\n",hd_ret);
						}
				}
        	}else {
                DBG_WRN("No data from ethernet camera %d\n", ethcam_index);
                vos_util_delay_ms(50); // 等待数据
        	}
		}else {
            DBG_WRN("Ethernet camera %d not linked for display\n", ethcam_index);
            vos_util_delay_ms(100); // 等待连接
        }
			//printf(" *** MovieAlgFunc_RCW_Tsk \r\n");
	}
	is_movie_alg_rcw_tsk_running = FALSE;
	THREAD_RETURN(0);
}
#endif

void MovieAlgFunc_ADAS_RCW_Init(void)
{
	printf("=========%s=========\n",__func__);

	// add by keytech, init algo, using debug mode
	AlgoInitPara initPara;
	#if 0
	initPara.activePath = "/data/adas";
	initPara.activeMode = 2;
	initPara.activeAlgoType = ACTIVE_ALGO_ADASREAR;
	initPara.serialPath = "/dev/ttyS0";
	initPara.logPath = NULL;
	initPara.debug_enable = 1;
	#else
	initPara.activePath = "/data/usr_adas";
	//initPara.activePath = "/data/adas/active_file";
	initPara.activeMode = 3;
	initPara.activeAlgoType = ACTIVE_ALGO_ADASREAR;
	//initPara.serverIp = "192.168.1.96";
	initPara.serverIp = "192.168.1.20";
	initPara.serverPort = 13456;
	initPara.logPath = NULL;
	initPara.debug_enable = 0;
	#endif
	int ret = ALGO_MANAGER_Init(&initPara);
	if(ret == 0)
		printf("=========ALGO_MANAGER_Init success=========\n");
	else
		printf("=========ALGO_MANAGER_Init failed=========\n");

	// init Adas ,add by keytech
	
	//char name[32] = "AlgoAdas";
	AlgoCreatePara creatPara;
	memset(&creatPara,0,sizeof(AlgoCreatePara));
	memcpy(creatPara.algoName,ADAS_ALGO_NAME,strlen(ADAS_ALGO_NAME));

	creatPara.algoPara.modelPath =  "/data/adas/model_file";
	creatPara.type = ALGO_TYPE_ADAS;
	creatPara.algoPara.freeCallback =NULL;
	creatPara.algoPara.eventCallback =NULL;
	creatPara.algoPara.configPath = "/data/adas/config_file";
	creatPara.algoPara.imageWidth = 1920;
	creatPara.algoPara.imageHeight = 1080;
	creatPara.algoPara.fps = 10;
	creatPara.algoPara.sync_enable = 1;


	ALGO_MANAGER_Create(&adasHandle,&creatPara);
	if(ret == 0)
		printf("=========ALGO_MANAGER_Create Adas success=========\n");
	else
		printf("=========ALGO_MANAGER_Create Adas failed=========\n");

	// init Rcw, add by keytech
	//char rcw_name[32] = "AlgoRcw";
	AlgoCreatePara rcw_creatPara;
	memset(&rcw_creatPara,0,sizeof(AlgoCreatePara));
	memcpy(rcw_creatPara.algoName,RCW_ALGO_NAME,strlen(RCW_ALGO_NAME));

	rcw_creatPara.algoPara.modelPath =  "/data/adas/model_file";
	rcw_creatPara.type = ALGO_TYPE_RCW;
	rcw_creatPara.algoPara.freeCallback =NULL;
	rcw_creatPara.algoPara.eventCallback =NULL;
	rcw_creatPara.algoPara.configPath = "/data/adas/config_file";
	rcw_creatPara.algoPara.imageWidth = 1920;
	rcw_creatPara.algoPara.imageHeight = 1080;
	rcw_creatPara.algoPara.fps = 8;
	rcw_creatPara.algoPara.sync_enable = 1;

	ALGO_MANAGER_Create(&rcwHandle,&rcw_creatPara);
	if(ret == 0)
		printf("=========ALGO_MANAGER_Create Rcw success=========\n");
	else
		printf("=========ALGO_MANAGER_Create Rcw failed=========\n");

	#if 1 
	int auth_ret = ALGO_MANAGER_GetActiveResult();
	if ((auth_ret == 0) && SysInit_getintoadas_mode_getstd())
	{
		CHKPNT;
		ADAS_Auth_Test = TRUE;
	}
	else {
		//ADAS_Auth_Test = TRUE;
	}
	#endif
}

ER MovieAlgFunc_ADAS_RCW_InstallID(void)
{
	printf("=========%s=========\n",__func__);
	ER ret = E_OK;

	MovieAlgFunc_ADAS_RCW_Init();
	
	ADAS_OpenState = TRUE;
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

ER MovieAlgFunc_ADAS_RCW_UninstallID(void)
{
	printf("=========%s=========\n",__func__);
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
	//ADAS_OpenState = FALSE;
	
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

