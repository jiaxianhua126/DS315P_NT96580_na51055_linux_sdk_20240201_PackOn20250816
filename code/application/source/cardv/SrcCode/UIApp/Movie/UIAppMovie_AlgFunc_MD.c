#include "PrjInc.h"
#include "hdal.h"
#include "ImageApp/ImageApp_MovieMulti.h"
#include "sw_md.h"
#include <kwrap/debug.h>
#include <kwrap/error_no.h>
#include <kwrap/task.h>
#include <kwrap/type.h>
#include <kwrap/util.h>
#include "UIWnd/UIFlow.h"

#define PRI_MOVIEALG_MD                20
#define STKSIZE_MOVIEALG_MD            4096

static THREAD_HANDLE movie_alg_md_tsk_id;
static UINT32 movie_alg_md_tsk_run, is_movie_alg_md_tsk_running;
static UINT32 movie_alg_md_result = FALSE;

static THREAD_RETTYPE MovieAlgFunc_MD_Tsk(void)
{
	HD_PATH_ID img_path;
	HD_VIDEO_FRAME video_frame = {0};
	HD_RESULT hd_ret;
	UINT32 err_cnt = 0;
	#if (SENSOR_CAPS_COUNT == 2)
	HD_PATH_ID img2_path;
	HD_VIDEO_FRAME video2_frame = {0};
	HD_RESULT hd_ret2;
	UINT32 err2_cnt = 0;
	#endif
    BOOL md_result1 = FALSE, md_result2 = FALSE;

	THREAD_ENTRY();

	img_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_1, _CFG_ALG_PATH3);
	#if (SENSOR_CAPS_COUNT == 2)
	img2_path = ImageApp_MovieMulti_GetAlgDataPort(_CFG_REC_ID_2, _CFG_ALG_PATH3);
	#endif

	is_movie_alg_md_tsk_running = TRUE;

	while (movie_alg_md_tsk_run) {
		if (UI_GetData(FL_MOVIE_MOTION_DET)|| (UI_GetData(FL_PARKING_MODE) != PARKING_MODE_OFF)) {
			if ((hd_ret = hd_videoproc_pull_out_buf(img_path, &video_frame, -1)) == HD_OK) {
				// process data
				//movie_alg_md_result = MD_Process(0, &video_frame);
				md_result1 = MD_Process(0, &video_frame);
				// release data
				if ((hd_ret = hd_videoproc_release_out_buf(img_path, &video_frame)) != HD_OK) {
					DBG_ERR("hd_videoproc_release_out_buf fail(%d)\r\n", hd_ret);
				}
			} else {
				err_cnt ++;
				if (!(err_cnt % 30)) {
					DBG_ERR("hd_videoproc_pull_out_buf fail(%d),cnt = %d\r\n", hd_ret, err_cnt);
				}
			}

			#if (SENSOR_CAPS_COUNT == 2)
			if ((hd_ret2 = hd_videoproc_pull_out_buf(img2_path, &video2_frame, -1)) == HD_OK) {
				// process data
				//movie_alg_md_result = MD_Process(0, &video_frame);
				md_result2 = MD_Process(1, &video2_frame);
				// release data
				if ((hd_ret2 = hd_videoproc_release_out_buf(img2_path, &video2_frame)) != HD_OK) {
					DBG_ERR("hd_videoproc_release_out_buf fail(%d)\r\n", hd_ret2);
				}
			} else {
				err2_cnt ++;
				if (!(err2_cnt % 30)) {
					DBG_ERR("hd_videoproc_pull_out_buf fail(%d),cnt = %d\r\n", hd_ret2, err2_cnt);
				}
			}
			#endif
			movie_alg_md_result = (md_result1 || md_result2);
		} else {
			// the delay time should < 500 ms due to UninstallID only wait for 500 ms
			vos_util_delay_ms(100);

		}
	}
	is_movie_alg_md_tsk_running = FALSE;

	THREAD_RETURN(0);
}

void MovieAlgFunc_MD_Init(void)
{
    UINT8 md_wnd[32][32];

	//prev_proc_time = 0;
	//curr_proc_time = 0;
	//proc_period = 1000000 / 10;      /// 10 fps to reduce converge time
	MD_SetLevel(0, 12);
	memset(&md_wnd[0][0], 1, 32*32);
	MD_SetDetWin(0, &md_wnd[0][0]);
	#if (SENSOR_CAPS_COUNT == 2)
	MD_SetLevel(1, 18);
	//memset(&md_wnd[0][0], 1, 32*32);
	MD_SetDetWin(1, &md_wnd[0][0]);
	#endif
}

ER MovieAlgFunc_MD_InstallID(void)
{
	ER ret = E_OK;

	MovieAlgFunc_MD_Init();

	movie_alg_md_tsk_run = FALSE;
	is_movie_alg_md_tsk_running = FALSE;

	if ((movie_alg_md_tsk_id = vos_task_create(MovieAlgFunc_MD_Tsk, 0, "MovieAlgMDTsk", PRI_MOVIEALG_MD, STKSIZE_MOVIEALG_MD)) == 0) {
		DBG_ERR("MovieAlgMDTsk create failed.\r\n");
        ret = E_SYS;
	} else {
		DBG_DUMP("MovieAlgMDTsk create successful.\r\n");
		movie_alg_md_tsk_run = TRUE;
	    vos_task_resume(movie_alg_md_tsk_id);
	}
	return ret;
}

ER MovieAlgFunc_MD_UninstallID(void)
{
	ER ret = E_OK;
	UINT32 delay_cnt;

	delay_cnt = 50;
	movie_alg_md_tsk_run = FALSE;
	while (is_movie_alg_md_tsk_running && delay_cnt) {
		vos_util_delay_ms(10);
		delay_cnt --;
	}

	if (is_movie_alg_md_tsk_running) {
		DBG_DUMP("Destroy MovieAlgMDTsk\r\n");
		vos_task_destroy(movie_alg_md_tsk_id);
	}
	return ret;
}

UINT32 MovieAlgFunc_MD_GetResult(void)
{
	return movie_alg_md_result;
}

