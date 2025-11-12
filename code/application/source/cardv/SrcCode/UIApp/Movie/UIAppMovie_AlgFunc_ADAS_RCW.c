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
#include "PStore.h"
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

void Init_ActiveFile_Pstore(void);
void ADAS_main_File(void);
void Restore_AllActiveFiles(void);
void Delete_ActiveFile_Pstore(void);
UINT8 CheckActiveFiles(void);
void CreateTestFile(void);
ER Init_PStore(void);

BOOL ADAS_OpenState = FALSE;
UINT8 ActiveFiles_flag = 0;
pthread_mutex_t g_data_mutex_front = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_data_mutex_rear = PTHREAD_MUTEX_INITIALIZER;

static void MovieAlgFunc_ADASSetSentivity(UINT8 adasSensitivity)
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

	ALGO_MANAGER_GetAttr(ALGO_ATTR_ADAS_VIRBUMPER_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.adasAttr.senType);
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

static void MovieAlgFunc_RCWSetSentivity(UINT8 rcwSensitivity)
{
	AlgoAttr AlgoAttr_set={0};
	ALGO_MANAGER_GetAttr(ALGO_ATTR_RCW_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.rcwAttr.sen);
	AlgoAttr_set.rcwAttr.sen = rcwSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_RCW_SENSITIVITY,&AlgoAttr_set);

	ALGO_MANAGER_GetAttr(ALGO_ATTR_RCW_LCA_SENSITIVITY,&AlgoAttr_set);
	printf("senType %d\n",AlgoAttr_set.rcwAttr.sen);
	AlgoAttr_set.rcwAttr.sen = rcwSensitivity;
	ALGO_MANAGER_SetAttr(ALGO_ATTR_RCW_LCA_SENSITIVITY,&AlgoAttr_set);
}

static THREAD_RETTYPE MovieAlgFunc_ADAS_Tsk(void)
{
	printf("=========%s=========\n",__func__);
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
	UINT32 speed_cnt = 0;
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_1, _CFG_ALG_PATH3);
	printf("=========%s====img_path:%d=====\n",__func__,img_path);
	is_movie_alg_adas_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&adas_handle,ADAS_ALGO_NAME);
	MovieAlgFunc_ADASSetSentivity(SEN_HIGH);
	MovieAlgFunc_SetLdwSpeed(30);

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
		//para.speed = g_CurSpeed;//60
		para.speed = 60;
		speed_cnt++;
		if(speed_cnt == 1000){
			//printf("=========%s====speed:%d=====\n",__func__,g_CurSpeed);
			speed_cnt = 0;
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
					printf("warn %x, fcw objsize %d ldw %d ped %d, calib_his %d calib_process %d\n",adas_eventData.result.algoWarnType,
							adas_eventData.result.algoResult.adasResult.fcw.objsize,
							adas_eventData.result.algoResult.adasResult.ldw.lineNum,
							adas_eventData.result.algoResult.adasResult.ped.objsize,
							adas_eventData.result.algoResult.adasResult.calib.calib_history,
							adas_eventData.result.algoResult.adasResult.calib.calib_process
					);
					
					//
					#if  1
					if (pthread_mutex_trylock(&g_data_mutex_front) == 0) {
						printf("LOCK success===1.\r\n");
						memcpy(&adas_eventData_app,&adas_eventData,sizeof(adas_eventData));
						pthread_mutex_unlock(&g_data_mutex_front);
					}else{
						printf("LOCK fail======111.\r\n");
					}
					#endif
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//ǰ����ײ
				        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
						//if(SysGetFlag(FL_MOVIE_FCW) == MOVIE_FCW_ON)
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//ǰ����ײԤ����
				        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
						//if(SysGetFlag(FL_MOVIE_FPW) == MOVIE_FPW_ON)
					        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FPW);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////����ƫ�� ��ƫ��
				        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
						//if(SysGetFlag(FL_MOVIE_LDWS) == MOVIE_LDWS_ON)
				       		Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//����ƫ�� ��ƫ��
				        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
						//if(SysGetFlag(FL_MOVIE_LDWS) == MOVIE_LDWS_ON)
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//ǰ���𲽱���
				        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
						//if(SysGetFlag(FL_SNG) == MOVIE_STOP_GO_ON)
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)){//������ײ
				        printf("=====ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS====\r\n");
						//if(SysGetFlag(FL_MOVIE_VIRTUAL_BUMPERS) == MOVIE_VIRTUAL_BUMPERS_ON)
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
					printf("LOCK success.\r\n");
					memcpy(&adas_eventData_app,&adas_eventData,sizeof(adas_eventData));
					pthread_mutex_unlock(&g_data_mutex_front);
				}else{
					printf("LOCK fail.\r\n");
				}
				#endif
				//printf("=========%s=====222====\n",__func__);
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FCW)){//ǰ����ײ
			        printf("=====ALGO_ADAS_WARN_TYPE_FCW====\r\n");
					//if(SysGetFlag(FL_MOVIE_FCW_MENU) == MOVIE_FCW_ON)
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FC);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_FPW)){//ǰ����ײԤ����
			        printf("=====ALGO_ADAS_WARN_TYPE_FPW====\r\n");
					//if(SysGetFlag(FL_MOVIE_FPW) == MOVIE_FPW_ON)
				        Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_FPW);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_L)){////����ƫ�� ��ƫ��
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_L====\r\n");
					//if(SysGetFlag(FL_MOVIE_LDWS_MENU) == MOVIE_LDWS_ON)
			       		Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_LDW_R)){//����ƫ�� ��ƫ��
			        printf("=====ALGO_ADAS_WARN_TYPE_LDW_R====\r\n");
					//if(SysGetFlag(FL_MOVIE_LDWS_MENU) == MOVIE_LDWS_ON)
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LD_RIGHT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_STOP_GO)){//ǰ���𲽱���
			        printf("=====ALGO_ADAS_WARN_TYPE_STOP_GO====\r\n");
					//if(SysGetFlag(FL_SNG) == MOVIE_STOP_GO_ON)
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_GO);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(adas_eventData.result.algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS)){//������ײ
			        printf("=====ALGO_ADAS_WARN_TYPE_VIRTUAL_BUMPERS====\r\n");
					//if(SysGetFlag(FL_MOVIE_VIRTUAL_BUMPERS) == MOVIE_VIRTUAL_BUMPERS_ON)
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
	//printf("=========%s=========\n",__func__);
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
	UINT32 speed_cnt = 0;
	THREAD_ENTRY();
	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_2, _CFG_ALG_PATH3);
	//img_path = _CFG_ETHCAM_ID_1;
	printf("=========%s====img_path:%d=====\n",__func__,img_path);
	is_movie_alg_rcw_tsk_running = TRUE;

	//add by keytech
	hd_ret = ALGO_MANAGER_GetHandleByName(&rcw_handle,RCW_ALGO_NAME);
	MovieAlgFunc_RCWSetSentivity(SEN_HIGH);

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
		speed_cnt++;
		if(speed_cnt == 1000){
			//printf("=========%s====speed:%d=====\n",__func__,g_CurSpeed);
			speed_cnt = 0;
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
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_RCW_REAR)){//ǰ����ײ
				        printf("=====ALGO_RCW_WARN_TYPE_RCW_REAR====\r\n");
						//if(SysGetFlag(FL_MOVIE_RCW) == MOVIE_RCW_ON)
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_RCW_REAR);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)){//�������
				        printf("=====ALGO_RCW_WARN_TYPE_LCA_LEFT====\r\n");
						//if(SysGetFlag(FL_MOVIE_LCAS) == MOVIE_LCAS_ON)
				        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_LEFT);
				    }
					if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)){//ǰ����ײԤ����
				        printf("=====ALGO_RCW_WARN_TYPE_LCA_RIGHT====\r\n");
						//if(SysGetFlag(FL_MOVIE_LCAS) == MOVIE_LCAS_ON)
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
					//if(SysGetFlag(FL_MOVIE_RCW) == MOVIE_RCW_ON)
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_RCW_REAR);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_LEFT)){//�������
			        printf("=====ALGO_RCW_WARN_TYPE_LCA_LEFT====\r\n");
					//if(SysGetFlag(FL_MOVIE_LCAS) == MOVIE_LCAS_ON)
			        	Ux_PostEvent(NVTEVT_CB_ADAS_SHOWALARM, 1, ADAS_ALARM_LCA_LEFT);
			    }
				if(ALGO_WARN_TYPE_CHECK_SET(rcw_eventData.result.algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)&&!ALGO_WARN_TYPE_CHECK_SET(before_algoWarnType,ALGO_RCW_WARN_TYPE_LCA_RIGHT)){//ǰ����ײԤ����
			        printf("=====ALGO_RCW_WARN_TYPE_LCA_RIGHT====\r\n");
					//if(SysGetFlag(FL_MOVIE_LCAS) == MOVIE_LCAS_ON)
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
}

ER MovieAlgFunc_ADAS_RCW_InstallID(void)
{
	printf("=========%s=========\n",__func__);
	ER ret = E_OK;

	//Init_PStore();
	//ActiveFiles_flag = CheckActiveFiles();
	//Delete_ActiveFile_Pstore();
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

	//ADAS_main_File();
	
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

#define KY_SECRETKEY_NAME  "Ky_SecretKey"
#define KY_UUID_NAME 	  "Ky_Uuid"
#define KY_VERIFY_NAME 	  "ky_Verify"
#define TEST_NAME 	  "TES"

#define KY_SECRETKEY_PATH	"/data/adas/active_file/Ky_SecretKey"
#define KY_UUID_PATH		"/data/adas/active_file/Ky_Uuid"
#define KY_VERIFY_PATH		"/data/adas/active_file/Ky_Verify"
//#define TEST_PATH		"A:\\data\\adas\\active_file\\test.txt"
#define TEST_PATH		"/data/adas/active_file/test.txt"

typedef enum {
	FILE_TYPE_SECRETKEY = 0,
	FILE_TYPE_UUID,
	FILE_TYPE_VERIFY,
	FILE_TYPE_ID_MAX,
}FLIE_TYPE;

typedef struct _pstore_adas {
    UINT8 fileSize;
    char fileContent[150]; // 柔性数组，实际大小根据文件内容动态分配
} pstore_adas;

BOOL ADAS_Pstroe_Exist = FALSE;
#if 0
void StoreActiveFile(char* modelName,  char* filename) 
{
	printf("=========%s=========\n",__func__);
	FST_FILE		  filehdl=0;
    UINT32      uiBuffer = 0, uiFileSize;
    INT32 ret = FST_STA_ERROR;
	UINT32 pa;
	void   *va;
    PPSTORE_SECTION_HANDLE  AdasSection;
	
	filehdl = FileSys_OpenFile(filename,FST_OPEN_READ | FST_OPEN_EXISTING);
	if(filehdl == NULL){
		DBG_ERR("Failed to open source file: %s\n", filename);
		return;
	}
	
	uiFileSize = (UINT32)FileSys_GetFileLen(filename);//first you get the size ,then read the file 
	if (uiFileSize == 0){
		DBG_ERR("File size is 0, skip storing: %s\n", filename);
		FileSys_CloseFile(filehdl);
		return;
	}

	printf("Storing file %s, size: %u bytes\n", filename, uiFileSize);
	
	ret = hd_common_mem_alloc(modelName, &pa, (void **)&va, uiFileSize, DDR_ID0);
	if (ret != HD_OK) {
		DBG_ERR("err:alloc size 0x%x, ddr %d\r\n", (unsigned int)(uiFileSize), (int)(DDR_ID0));
		return ;
	}

	uiBuffer = (UINT32)va;

	// 4. 读取文件内容
    //UINT32 bytesRead = 0;
    ret = FileSys_ReadFile(filehdl, (UINT8 *)uiBuffer, &uiFileSize, 0, NULL);
    FileSys_CloseFile(filehdl);
    
    if(ret != FST_STA_OK){
        DBG_ERR("File read failed: %d\n", ret);
        hd_common_mem_free(pa, va);
        return;
    }

	printf("Successfully read %u bytes from %s\n", uiFileSize, filename);
	
	if ((AdasSection = PStore_OpenSection(modelName, PS_RDWR)) != E_PS_SECHDLER) {
        // 先写入文件大小（4字节）
        UINT32 storedSize = uiFileSize;
        ret = PStore_WriteSection((UINT8 *)&storedSize, 0, sizeof(storedSize), AdasSection);
        if(ret != E_PS_OK){
            DBG_ERR("Failed to write file size to pstore: %d\n", ret);
        }
        
        // 再写入文件内容
        ret = PStore_WriteSection((UINT8 *)uiBuffer, sizeof(storedSize), uiFileSize, AdasSection);
        if(ret != E_PS_OK){
            DBG_ERR("Failed to write file content to pstore: %d\n", ret);
        }
        
        PStore_CloseSection(AdasSection);
        printf("Successfully stored %s to pstore, size: %u bytes\n", modelName, uiFileSize);
    } else {
        DBG_ERR("Failed to open pstore section: %s\n", modelName);
    }

	ret = hd_common_mem_free(pa, (void *)va);
	if (ret != HD_OK) {
		printf("----err:free pa = 0x%x, va = 0x%x\r\n", pa, va);
	}
	
	DBG_DUMP("-------------------------PSstor Update ADAS data complete!!!-------------------------\r\n");

}
#elif 1
void StoreActiveFile(char* modelName, char* filename) 
{
    printf("=========%s=========\n",__func__);
    FILE* file = NULL;
    UINT32 uiFileSize;
    INT32 ret = -1;
    UINT32 pa;
    void *va;
    PPSTORE_SECTION_HANDLE AdasSection;
    
    // 使用fopen打开文件
    file = fopen(filename, "r+");
    if(file == NULL){
        DBG_ERR("Failed to open source file: %s\n", filename);
        return;
    }
    
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    uiFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (uiFileSize == 0){
        DBG_ERR("File size is 0, skip storing: %s\n", filename);
        fclose(file);
        return;
    }

    printf("Storing file %s, size: %u bytes\n", filename, uiFileSize);
    
    // 分配内存
    ret = hd_common_mem_alloc(modelName, &pa, (void **)&va, uiFileSize, DDR_ID0);
    if (ret != HD_OK) {
        DBG_ERR("err:alloc size 0x%x, ddr %d\r\n", (unsigned int)(uiFileSize), (int)(DDR_ID0));
        fclose(file);
        return;
    }

    // 读取文件内容
    size_t bytesRead = fread(va, 1, uiFileSize, file);
    fclose(file);
    
    if(bytesRead != uiFileSize){
        DBG_ERR("File read failed: expected %u, got %zu\n", uiFileSize, bytesRead);
        hd_common_mem_free(pa, va);
        return;
    }

    printf("Successfully read %zu bytes from %s\n", bytesRead, filename);
    
    // PStore操作保持不变
    if ((AdasSection = PStore_OpenSection(modelName, PS_RDWR)) != E_PS_SECHDLER) {
        // 先写文件大小前缀（4字节）
        UINT32 storedSize = uiFileSize;
        ret = PStore_WriteSection((UINT8 *)&storedSize, 0, sizeof(storedSize), AdasSection);
        if(ret != E_PS_OK){
            DBG_ERR("Failed to write file size to pstore: %d\n", ret);
			// 尝试获取更多错误信息
			printf("PStore max section: %d,A section max size:%d \n", PStore_GetInfo(PS_INFO_MAX_SEC),PStore_GetInfo(PS_INFO_MAX_SEC_SIZE));
			printf("PStore size: %d,PStore free space:%d \n", PStore_GetInfo(PS_INFO_TOT_SIZE),PStore_GetInfo(PS_INFO_FREE_SPACE));
			printf("Storage block size: %d \n", PStore_GetInfo(PS_INFO_BLK_SIZE));
			PStore_DeleteSection(modelName);
			return;
        }
        
        // 再写文件内容
        ret = PStore_WriteSection((UINT8 *)va, sizeof(storedSize), uiFileSize, AdasSection);
        if(ret != E_PS_OK){
            DBG_ERR("Failed to write file content to pstore: %d\n", ret);
			// 尝试获取更多错误信息
			printf("PStore max section: %d,A section max size:%d \n", PStore_GetInfo(PS_INFO_MAX_SEC),PStore_GetInfo(PS_INFO_MAX_SEC_SIZE));
			printf("PStore size: %d,PStore free space:%d \n", PStore_GetInfo(PS_INFO_TOT_SIZE),PStore_GetInfo(PS_INFO_FREE_SPACE));
			printf("Storage block size: %d \n", PStore_GetInfo(PS_INFO_BLK_SIZE));
			PStore_DeleteSection(modelName);
			return;
        }
        
        PStore_CloseSection(AdasSection);
		printf("PStore max section: %d,A section max size:%d \n", PStore_GetInfo(PS_INFO_MAX_SEC),PStore_GetInfo(PS_INFO_MAX_SEC_SIZE));
        printf("Successfully stored %s to pstore, size: %u bytes\n", modelName, uiFileSize);
    } else {
        DBG_ERR("Failed to open pstore section: %s\n", modelName);
    }

    ret = hd_common_mem_free(pa, va);
    if (ret != HD_OK) {
        printf("----err:free pa = 0x%x, va = 0x%p\r\n", pa, va);
    }
    
    DBG_DUMP("-------------------------PSstor Update ADAS data complete!!!-------------------------\r\n");
}
#elif 0
void StoreActiveFile(char* modelName, char* filename) 
{
    printf("=========%s=========\n",__func__);
    FILE* file = NULL;
    INT32 ret = -1;
    PPSTORE_SECTION_HANDLE AdasSection;
    
    // 固定1KB文件大小
    #define FIXED_FILE_SIZE 1024
    static UINT8 staticBuffer[FIXED_FILE_SIZE + 4];
    
    // 使用fopen打开文件
    file = fopen(filename, "rb");
    if(file == NULL){
        DBG_ERR("Failed to open source file: %s\n", filename);
        return;
    }
    
    // 获取文件大小并验证
    fseek(file, 0, SEEK_END);
    UINT32 uiFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (uiFileSize == 0){
        DBG_ERR("File size is 0, skip storing: %s\n", filename);
        fclose(file);
        return;
    }
    #if 0
    // 验证文件大小确实是1KB
    if (uiFileSize != FIXED_FILE_SIZE) {
        DBG_ERR("File size mismatch: expected %d, got %u bytes\n", FIXED_FILE_SIZE, uiFileSize);
        fclose(file);
        return;
    }
	#endif
    printf("Storing file %s, size: %u bytes\n", filename, uiFileSize);
    
    // 使用memcpy设置文件大小头，避免类型双关
    UINT32 fileSizeHeader = uiFileSize;
    memcpy(staticBuffer, &fileSizeHeader, sizeof(UINT32));
    
    // 读取文件内容到静态缓冲区（跳过前4字节的文件大小头）
    size_t bytesRead = fread(staticBuffer + 4, 1, uiFileSize, file);
    fclose(file);
    
    if(bytesRead != uiFileSize){
        DBG_ERR("File read failed: expected %u, got %zu\n", uiFileSize, bytesRead);
        return;
    }

    printf("Successfully read %zu bytes from %s\n", bytesRead, filename);
    
    // PStore操作
    AdasSection = PStore_OpenSection(modelName, PS_RDWR);
    if (AdasSection == E_PS_SECHDLER) {
        // 如果不存在，则创建新的section
        AdasSection = PStore_OpenSection(modelName, PS_RDWR | PS_CREATE);
        if (AdasSection == E_PS_SECHDLER) {
            DBG_ERR("Failed to create pstore section: %s\n", modelName);
            return;
        }
    }
    
    // 写入整个数据（4字节文件大小头 + 文件内容）
    UINT32 totalSize = 4 + uiFileSize;
    ret = PStore_WriteSection(staticBuffer, 0, totalSize, AdasSection);
    if(ret != E_PS_OK){
        DBG_ERR("Failed to write to pstore: %d\n", ret);
    } else {
        printf("Successfully stored %s to pstore, total size: %u bytes\n", modelName, totalSize);
    }
    
    PStore_CloseSection(AdasSection);
    
    DBG_DUMP("-------------------------PSstor Update ADAS data complete!!!-------------------------\r\n");
}
#elif 0
void StoreActiveFile(char* modelName, char* filename) 
{
    printf("=========%s=========\n",__func__);
    FILE* file = NULL;
    INT32 ret = -1;
    PPSTORE_SECTION_HANDLE AdasSection;
    
    // 固定1KB文件大小
    #define FIXED_FILE_SIZE 1024
    static UINT8 staticBuffer[FIXED_FILE_SIZE + 4];
    
    // 使用fopen打开文件
    //file = fopen(filename, "rb");
    file = fopen(filename, "r+");
    if(file == NULL){
        DBG_ERR("Failed to open source file: %s\n", filename);
        return;
    }
    
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    UINT32 uiFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (uiFileSize == 0){
        DBG_ERR("File size is 0, skip storing: %s\n", filename);
        fclose(file);
        return;
    }

    // 检查文件大小是否超过静态缓冲区
    if (uiFileSize > FIXED_FILE_SIZE) {
        DBG_ERR("File too large: %u bytes, max supported: %u\n", uiFileSize, FIXED_FILE_SIZE);
        fclose(file);
        return;
    }

    printf("Storing file %s, size: %u bytes\n", filename, uiFileSize);
    
    // 使用memcpy设置文件大小头
    UINT32 fileSizeHeader = uiFileSize;
    memcpy(staticBuffer, &fileSizeHeader, sizeof(UINT32));
    
    // 读取文件内容
    size_t bytesRead = fread(staticBuffer + 4, 1, uiFileSize, file);
	printf("Bytes read: %zu, file size: %u\n", bytesRead, uiFileSize);
	printf("staticBuffer: %s\n", staticBuffer);
	
	// 修改第一个循环
	for(UINT32 i = 0; i < 20 && i < (4 + uiFileSize); i++) {
	    if(i % 16 == 0) printf("[%04x] ", i);
	    printf("%02x ", staticBuffer[i]);
	    if(i % 16 == 15) printf("\n");
	}
	if((4 + uiFileSize) % 16 != 0) printf("\n");

	// 修改第二个循环  
	for(UINT32 i = 4; i < (4 + uiFileSize) && i < (4 + 20); i++) {
	    if(isprint(staticBuffer[i])) {
	        printf("%c", staticBuffer[i]);
	    } else {
	        printf("\\x%02x", staticBuffer[i]);
	    }
	}
	printf("\"\n");
	
    fclose(file);	
	
    if(bytesRead != uiFileSize){
        DBG_ERR("File read failed: expected %u, got %zu\n", uiFileSize, bytesRead);
        return;
    }

    printf("Successfully read %zu bytes from %s\n", bytesRead, filename);
	
    // 先删除已有的section（如果存在）
    //PStore_DeleteSection(modelName);
    // 创建新的section
    AdasSection = PStore_OpenSection(modelName, PS_RDWR);
    if (AdasSection == E_PS_SECHDLER) {
        DBG_ERR("Failed to create pstore section: %s\n", modelName);
        return;
    }

    // 写入数据
    UINT32 totalSize = sizeof(UINT32) + uiFileSize;
    printf("Writing %u bytes to PStore section %s\n", totalSize, modelName);
    
    ret = PStore_WriteSection(staticBuffer, 0, totalSize, AdasSection);
    if(ret != E_PS_OK){
        DBG_ERR("Failed to write to pstore: %d, section: %s, size: %u\n", ret, modelName, totalSize);
        
		// 尝试获取更多错误信息
		printf("PStore max section: %d,A section max size:%d \n", PStore_GetInfo(PS_INFO_MAX_SEC),PStore_GetInfo(PS_INFO_MAX_SEC_SIZE));
		printf("PStore size: %d,PStore free space:%d \n", PStore_GetInfo(PS_INFO_TOT_SIZE),PStore_GetInfo(PS_INFO_FREE_SPACE));
		printf("Storage block size: %d \n", PStore_GetInfo(PS_INFO_BLK_SIZE));

		PStore_DeleteSection(modelName);
		return;
    } else {
        printf("Successfully stored %s to pstore, total size: %u bytes\n", modelName, totalSize);
    }
    
    PStore_CloseSection(AdasSection);
    
    DBG_DUMP("-------------------------PSstor Update ADAS data complete!!!-------------------------\r\n");
}
#else
void StoreActiveFile(char* modelName, char* filename) 
{
    printf("=========%s=========\n",__func__);
	FILE *asr_serial_fd;
	char Asr_serialData[100] = {0};
    PPSTORE_SECTION_HANDLE  AsrSection;
	pstore_adas pADAS = {0};
	
    asr_serial_fd = fopen(TEST_PATH,"r+");
    if (asr_serial_fd == NULL) {
        printf("open asr_serial_fd fail not /data/adas/test.txt\r\n");
    } else {
    
        while (fgets(Asr_serialData,sizeof(Asr_serialData),asr_serial_fd)) {
            Asr_serialData[strlen(Asr_serialData)-1] = '\0';
            printf("call getSerialNumber Asr_serialData = %s\r\n",Asr_serialData);
		
			//将serialNumber存储在Pstore中
            if ((AsrSection = PStore_OpenSection(TEST_NAME, PS_RDWR)) != E_PS_SECHDLER) {
                pADAS.fileSize = 10;
                strcpy(pADAS.fileContent,"a");//serialData);
                PStore_WriteSection((UINT8 *)&pADAS, 0, sizeof(pADAS), AsrSection);				
				#if 0
                Asr_Result = PStore_ReadSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
                printf("call getSerialNumber Asr_Result = %d\r\n",Asr_Result);
                printf("call getSerialNumber pASN.Asr_SerialNumber_Flag = %d\r\n",pASN.Asr_SerialNumber_Flag);
                printf("call getSerialNumber pASN.SerialNumber = %s\r\n",pASN.SerialNumber);
				#endif
                PStore_CloseSection(AsrSection);
            }
            fclose(asr_serial_fd);
            break;
        }
    }
}

#endif

void Open_ActiveFile_Pstore(char *pSecName)
{
	printf("=========%s=========\n",__func__);
	PPSTORE_SECTION_HANDLE  AdasSection; 
    if (!ADAS_OpenState) {
        if ((AdasSection = PStore_OpenSection(pSecName, (PS_RDWR))) != E_PS_SECHDLER) {
            printf("call ASR_Open %s already exist\r\n",pSecName);
            ADAS_Pstroe_Exist = TRUE;
            PStore_CloseSection(AdasSection);
        } else {
            ADAS_Pstroe_Exist = FALSE;
            printf("section %s does not exist\r\n",pSecName);
        }
        if (ADAS_Pstroe_Exist == FALSE) {
            //创建ASR Pstore 并初始化
            if ((AdasSection = PStore_OpenSection(pSecName, (PS_RDWR | PS_CREATE))) != E_PS_SECHDLER) {				
                ADAS_Pstroe_Exist = TRUE;
                //PStore_WriteSection((UINT8 *)&pASN, 0, sizeof(pASN), AsrSection);
                PStore_CloseSection(AdasSection);
            } else {
                printf("call PStore_OpenSection fail\r\n");
            }            
        }
    }
}

#if 0
void Restore_ActiveFile(char* pSecName, char* filename) 
{
	printf("=========%s=========\n",__func__);
    FST_FILE filehdl = NULL;
    PPSTORE_SECTION_HANDLE AdasSection = NULL;
    UINT32 uiFileSize = 0;
    UINT32 uiBuffer = 0;
    UINT32 pa;
    void *va;
    INT32 ret = FST_STA_ERROR;

    // 1. 打开PStore的section（只读模式）
    AdasSection = PStore_OpenSection(pSecName, PS_RDONLY);
    if (AdasSection == E_PS_SECHDLER) {
        DBG_ERR("PStore_OpenSection %s failed\r\n", pSecName);
        return;
    }
	
    // 2. 读取文件大小（前4字节）
    ret = PStore_ReadSection((UINT8*)&uiFileSize, 0, sizeof(uiFileSize), AdasSection);
    if (ret != E_PS_OK) {
        DBG_ERR("PStore_ReadSection failed: %d\r\n", ret);
        PStore_CloseSection(AdasSection);
        return;
    }

	// 检查文件大小是否为0
    if (uiFileSize == 0) {
        DBG_ERR("File size is 0, skip restore for section: %s\n", pSecName);
        PStore_CloseSection(AdasSection);
        return;
    }
	
    // 3. 分配内存用于存储文件内容
    ret = hd_common_mem_alloc(pSecName, &pa, (void **)&va, uiFileSize, DDR_ID0);
    if (ret != HD_OK) {
        DBG_ERR("hd_common_mem_alloc failed: %d\r\n", ret);
        PStore_CloseSection(AdasSection);
        return;
    }
    uiBuffer = (UINT32)va;

    // 4. 读取文件内容
    ret = PStore_ReadSection((UINT8*)uiBuffer, sizeof(uiFileSize), uiFileSize, AdasSection);
    if (ret != E_PS_OK) {
        DBG_ERR("PStore_ReadSection failed: %d\r\n", ret);
        hd_common_mem_free(pa, va);
        PStore_CloseSection(AdasSection);
        return;
    }

    // 5. 关闭PStore section
    PStore_CloseSection(AdasSection);
	
	printf("=========%s======111===\n",__func__);
    // 6. 创建目标文件并写入内容
    filehdl = FileSys_OpenFile(filename, FST_CREATE_ALWAYS | FST_OPEN_WRITE);
    if (filehdl == NULL) {
        DBG_ERR("FileSys_OpenFile %s failed\r\n", filename);
        hd_common_mem_free(pa, va);
        return;
    }

    ret = FileSys_WriteFile(filehdl, (UINT8*)uiBuffer, &uiFileSize, FST_FLAG_NONE, NULL);
    if (ret != FST_STA_OK) {
        DBG_ERR("FileSys_WriteFile failed: %d\r\n", ret);
    }

    // 7. 关闭文件和释放内存
    FileSys_CloseFile(filehdl);
	printf("=========%s======222===\n",__func__);
    hd_common_mem_free(pa, va);
	printf("=========%s=====333====\n",__func__);
    DBG_DUMP("Restore %s to %s success!\r\n", pSecName, filename);
}
#else
void Restore_ActiveFile(char* pSecName, char* filename) 
{
    printf("=========%s=========\n",__func__);
    FILE* file = NULL;
    PPSTORE_SECTION_HANDLE AdasSection = NULL;
    UINT32 uiFileSize = 0;
    UINT32 uiBuffer = 0;
    UINT32 pa;
    void *va;
    INT32 ret = -1;

    // 1. 打开PStore的section（读取模式）
    AdasSection = PStore_OpenSection(pSecName, PS_RDONLY);
    if (AdasSection == E_PS_SECHDLER) {
        DBG_ERR("PStore_OpenSection %s failed\r\n", pSecName);
        return;
    }
    
    // 2. 读取文件大小前缀（前4字节）
    ret = PStore_ReadSection((UINT8*)&uiFileSize, 0, sizeof(uiFileSize), AdasSection);
    if (ret != E_PS_OK) {
        DBG_ERR("PStore_ReadSection failed: %d\r\n", ret);
        PStore_CloseSection(AdasSection);
        return;
    }

    // 检查文件大小是否有效
    if (uiFileSize == 0) {
        DBG_ERR("File size is 0, skip restore for section: %s\n", pSecName);
        PStore_CloseSection(AdasSection);
        return;
    }
    
    // 3. 分配内存来存储文件内容
    ret = hd_common_mem_alloc(pSecName, &pa, (void **)&va, uiFileSize, DDR_ID0);
    if (ret != HD_OK) {
        DBG_ERR("hd_common_mem_alloc failed: %d\r\n", ret);
        PStore_CloseSection(AdasSection);
        return;
    }
    uiBuffer = (UINT32)va;

    // 4. 读取文件内容
    ret = PStore_ReadSection((UINT8*)uiBuffer, sizeof(uiFileSize), uiFileSize, AdasSection);
    if (ret != E_PS_OK) {
        DBG_ERR("PStore_ReadSection failed: %d\r\n", ret);
        hd_common_mem_free(pa, va);
        PStore_CloseSection(AdasSection);
        return;
    }

    // 5. 关闭PStore section
    PStore_CloseSection(AdasSection);
    
    printf("=========%s======111===\n",__func__);
    
    // 6. 创建目标文件并写入内容
    file = fopen(filename, "w+");  // 二进制写入模式，文件不存在则创建
    if (file == NULL) {
        DBG_ERR("fopen %s failed\r\n", filename);
        hd_common_mem_free(pa, va);
        return;
    }

    // 写入文件内容
    size_t bytesWritten = fwrite(va, 1, uiFileSize, file);
    if (bytesWritten != uiFileSize) {
        DBG_ERR("fwrite failed: expected %u, wrote %zu\n", uiFileSize, bytesWritten);
    }

    // 7. 关闭文件和释放内存
    fclose(file);
    printf("=========%s======222===\n",__func__);
    
    hd_common_mem_free(pa, va);
    
    printf("=========%s=====333====\n",__func__);
    DBG_DUMP("Restore %s to %s success!\r\n", pSecName, filename);
}
#endif

// 添加检查函数
#if 0
BOOL CheckFilesExist(char* path1, char* path2, char* path3)
{
	printf("=========%s=========\n",__func__);
    FST_FILE file1 = FileSys_OpenFile(path1, FST_OPEN_READ);
    FST_FILE file2 = FileSys_OpenFile(path2, FST_OPEN_READ);
    FST_FILE file3 = FileSys_OpenFile(path3, FST_OPEN_READ);
    
    BOOL exist = (file1 != NULL) && (file2 != NULL) && (file3 != NULL);
    
    if (file1) FileSys_CloseFile(file1);
    if (file2) FileSys_CloseFile(file2);
    if (file3) FileSys_CloseFile(file3);
    
    return exist;
}
#else
BOOL CheckFilesExist(char* path1, char* path2, char* path3)
{
    printf("=========%s=========\n",__func__);
    
    BOOL exist1 = (access(path1, F_OK) == 0);
    BOOL exist2 = (access(path2, F_OK) == 0);
    BOOL exist3 = (access(path3, F_OK) == 0);
    
    BOOL exist = exist1 && exist2 && exist3;
    
    printf("File existence check: %s(%d), %s(%d), %s(%d) -> %s\n", 
           path1, exist1, path2, exist2, path3, exist3, 
           exist ? "ALL EXIST" : "SOME MISSING");
    
    return exist;
}
#endif
BOOL CheckPStoreSectionsExist(char* sec1, char* sec2, char* sec3)
{
	printf("=========%s=========\n",__func__);
    PPSTORE_SECTION_HANDLE secHandle1 = PStore_OpenSection(sec1, PS_RDONLY);
    PPSTORE_SECTION_HANDLE secHandle2 = PStore_OpenSection(sec2, PS_RDONLY);
    PPSTORE_SECTION_HANDLE secHandle3 = PStore_OpenSection(sec3, PS_RDONLY);
    
    BOOL exist = (secHandle1 != E_PS_SECHDLER) && 
                 (secHandle2 != E_PS_SECHDLER) && 
                 (secHandle3 != E_PS_SECHDLER);
    
    if (secHandle1 != E_PS_SECHDLER) PStore_CloseSection(secHandle1);
    if (secHandle2 != E_PS_SECHDLER) PStore_CloseSection(secHandle2);
    if (secHandle3 != E_PS_SECHDLER) PStore_CloseSection(secHandle3);
    
    return exist;
}

UINT8 CheckActiveFiles(void)
{
	printf("=========%s=========\n",__func__);
	// 检查文件存在性并执行相应逻辑
    BOOL filesExist = CheckFilesExist(KY_SECRETKEY_PATH, KY_UUID_PATH, KY_VERIFY_PATH);
    BOOL pstoreSectionsExist = CheckPStoreSectionsExist(KY_SECRETKEY_NAME, KY_UUID_NAME, KY_VERIFY_NAME);
    
	printf("=========%s====filesExist:%d,pstoreSectionsExist:%d=====\n",__func__,filesExist,pstoreSectionsExist);
    if (filesExist && !pstoreSectionsExist) {
        printf("Files exist in A drive but not in PStore, running Init and Store functions\n");
        Init_ActiveFile_Pstore();
        ADAS_main_File();
    } else if (!filesExist && pstoreSectionsExist) {
        printf("Files exist in PStore but not in A drive, running Restore function\n");
        Restore_AllActiveFiles();
	} else if (filesExist && pstoreSectionsExist) {
		printf("Files exist in PStore and in A drive \n");
		ADAS_main_File();
    } else {
        printf("Files do not exist in either A drive or PStore, need to handle this case\n");
        // 这里可以添加处理逻辑，例如从网络下载或使用默认文件
        // 暂时先初始化PStore
        Init_ActiveFile_Pstore();
        #if 0
        //CreateTestFile();
		Open_ActiveFile_Pstore(TEST_NAME);
		StoreActiveFile(TEST_NAME, TEST_PATH);
		#else
		//Restore_ActiveFile(TEST_NAME, TEST_PATH);
		#endif
		return 1;
    }

	return 0;
}

void CreateTestFile(void)
{
    FST_FILE file = FileSys_OpenFile(TEST_PATH, FST_CREATE_ALWAYS | FST_OPEN_WRITE);
    if (file) {
        // 写入一些测试数据
        UINT8 data[] = "test data";
        UINT32 written = sizeof(data);
        FileSys_WriteFile(file, data, &written, FST_FLAG_NONE, NULL);
        FileSys_CloseFile(file);
        printf("Test file created successfully.\n");
    } else {
        printf("Failed to create test file.\n");
    }
}


// 添加专门的PStore初始化函数
ER Init_PStore(void)
{
    printf("=========%s=========\n",__func__);
    
    UINT32 max_sections = PStore_GetInfo(PS_INFO_MAX_SEC);
    UINT32 max_sec_size = PStore_GetInfo(PS_INFO_MAX_SEC_SIZE);
    
    printf("PStore status - Max sections: %d, Max section size: %d\n", max_sections, max_sec_size);
    
    // 如果PStore已格式化，直接返回成功
    if (max_sections > 0 && max_sec_size > 0) {
        printf("PStore already formatted\n");
        return E_OK;
    }
    
    printf("PStore not formatted, formatting now...\n");
    
    // 创建格式化参数结构体
    PSFMT fmtStruct;
    
    // 计算合适的格式化参数
    UINT32 total_size = PStore_GetInfo(PS_INFO_TOT_SIZE);        // 总容量
    UINT32 block_size = PStore_GetInfo(PS_INFO_BLK_SIZE);        // 块大小
    UINT32 total_blocks = total_size / block_size;               // 总块数
    
    // 设置分区参数
    fmtStruct.uiMaxSec = 3;  // 创建10个分区
    fmtStruct.uiMaxBlkPerSec = total_blocks / fmtStruct.uiMaxSec;
    
    // 参数边界检查
    if (fmtStruct.uiMaxBlkPerSec < 1) {
        fmtStruct.uiMaxBlkPerSec = 1;
    }
    if (fmtStruct.uiMaxSec < PS_MIN_SEC_NUM) {
        fmtStruct.uiMaxSec = PS_MIN_SEC_NUM;
    }
    if (fmtStruct.uiMaxSec > PS_MAX_SEC_NUM) {
        fmtStruct.uiMaxSec = PS_MAX_SEC_NUM;
    }
    if (fmtStruct.uiMaxBlkPerSec < PS_MIN_BLK_NUM_PER_SEC) {
        fmtStruct.uiMaxBlkPerSec = PS_MIN_BLK_NUM_PER_SEC;
    }
    if (fmtStruct.uiMaxBlkPerSec > PS_MAX_BLK_NUM_PER_SEC) {
        fmtStruct.uiMaxBlkPerSec = PS_MAX_BLK_NUM_PER_SEC;
    }
    
    printf("Formatting PStore: %d sections, %d blocks per section (total blocks: %d)\n", 
           fmtStruct.uiMaxSec, fmtStruct.uiMaxBlkPerSec, total_blocks);
    
    // 调用格式化函数
    ER format_ret = PStore_Format(&fmtStruct);
    if (format_ret == E_PS_OK) {
        printf("PStore format successful!\n");
        
        // 验证格式化结果
        max_sections = PStore_GetInfo(PS_INFO_MAX_SEC);
        max_sec_size = PStore_GetInfo(PS_INFO_MAX_SEC_SIZE);
        printf("After format - Max sections: %d, Max section size: %d\n", max_sections, max_sec_size);
        return E_OK;
    } else {
        printf("PStore format failed with error: %d\n", format_ret);
        return format_ret;
    }
}

void Restore_AllActiveFiles(void)
{
	printf("=========%s=========\n",__func__);
    // 恢复三个文件
    Restore_ActiveFile(KY_SECRETKEY_NAME, KY_SECRETKEY_PATH);
    Restore_ActiveFile(KY_UUID_NAME, KY_UUID_PATH);
    Restore_ActiveFile(KY_VERIFY_NAME, KY_VERIFY_PATH);
}

void Init_ActiveFile_Pstore(void)
{
	Open_ActiveFile_Pstore(KY_SECRETKEY_NAME);
	Open_ActiveFile_Pstore(KY_UUID_NAME);
	Open_ActiveFile_Pstore(KY_VERIFY_NAME);
}

void ADAS_main_File(void)
{
    StoreActiveFile(KY_SECRETKEY_NAME, KY_SECRETKEY_PATH);
	//Delay_DelayMs(300);

    StoreActiveFile(KY_UUID_NAME, KY_UUID_PATH);
	//Delay_DelayMs(300);
	
    StoreActiveFile(KY_VERIFY_NAME, KY_VERIFY_PATH);
}

void Delete_ActiveFile_Pstore(void)
{
	PStore_DeleteSection(KY_SECRETKEY_NAME);
	PStore_DeleteSection(KY_UUID_NAME);
	PStore_DeleteSection(KY_VERIFY_NAME);
}
