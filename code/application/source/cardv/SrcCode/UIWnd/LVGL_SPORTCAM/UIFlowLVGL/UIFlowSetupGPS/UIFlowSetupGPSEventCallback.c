#include "PrjInc.h"
#include "GxTime.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include <kwrap/debug.h>
#include "DxGPS.h"
static lv_task_t* 	gUpdateGPSTimerID = NULL;
static lv_group_t* gp = NULL;
static void set_indev_keypad_group(lv_obj_t* obj)
{
	if(gp == NULL){
		gp = lv_group_create();
		lv_group_add_obj(gp, obj);
	}

	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_group(indev, gp);
}
static void update_gps_icons(void)
{
	//bool locked = TRUE;
	lv_label_set_text_fmt(label_gps_title_scr_uiflowsetupgps, "GPS");
	lv_label_set_text_fmt(label_sat_01_scr_uiflowsetupgps, "01");
	lv_label_set_text_fmt(label_sat_02_scr_uiflowsetupgps, "02");
	lv_label_set_text_fmt(label_sat_03_scr_uiflowsetupgps, "03");
	lv_label_set_text_fmt(label_sat_04_scr_uiflowsetupgps, "04");
	lv_label_set_text_fmt(label_sat_05_scr_uiflowsetupgps, "05");
	lv_label_set_text_fmt(label_sat_06_scr_uiflowsetupgps, "06");
	lv_label_set_text_fmt(label_sat_07_scr_uiflowsetupgps, "07");
	lv_label_set_text_fmt(label_sat_08_scr_uiflowsetupgps, "08");
	lv_label_set_text_fmt(label_sat_09_scr_uiflowsetupgps, "09");
	lv_label_set_text_fmt(label_sat_10_scr_uiflowsetupgps, "10");
	lv_label_set_text_fmt(label_sat_11_scr_uiflowsetupgps, "11");
	lv_label_set_text_fmt(label_sat_12_scr_uiflowsetupgps, "12");
	#if 1
	DBG_DUMP("#######################\r\n");
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[0],((g_Edog_satellie_DB.satellie_DB_GSM_BD[0]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[1],((g_Edog_satellie_DB.satellie_DB_GSM_BD[1]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[2],((g_Edog_satellie_DB.satellie_DB_GSM_BD[2]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[3],((g_Edog_satellie_DB.satellie_DB_GSM_BD[3]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[4],((g_Edog_satellie_DB.satellie_DB_GSM_BD[4]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[5],((g_Edog_satellie_DB.satellie_DB_GSM_BD[5]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[6],((g_Edog_satellie_DB.satellie_DB_GSM_BD[6]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[7],((g_Edog_satellie_DB.satellie_DB_GSM_BD[7]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[8],((g_Edog_satellie_DB.satellie_DB_GSM_BD[8]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[9],((g_Edog_satellie_DB.satellie_DB_GSM_BD[9]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[10],((g_Edog_satellie_DB.satellie_DB_GSM_BD[10]/50.0)*100/2));
	DBG_DUMP("%d %f=============2\r\n",g_Edog_satellie_DB.satellie_DB_GSM_BD[11],((g_Edog_satellie_DB.satellie_DB_GSM_BD[11]/50.0)*100/2));
	#endif
	if(GetGPSSignalStatus()==GPSSignal_FINDABLE)
	{
		//hide red bar
		lv_obj_set_hidden(bar_sat_red_01_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_02_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_03_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_04_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_05_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_06_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_07_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_08_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_09_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_10_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_11_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_red_12_scr_uiflowsetupgps, true);

		lv_label_set_text_fmt(label_sat_val_01_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[0]);
		lv_label_set_text_fmt(label_sat_val_02_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[1]);
		lv_label_set_text_fmt(label_sat_val_03_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[2]);
		lv_label_set_text_fmt(label_sat_val_04_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[3]);
		lv_label_set_text_fmt(label_sat_val_05_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[4]);
		lv_label_set_text_fmt(label_sat_val_06_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[5]);
		lv_label_set_text_fmt(label_sat_val_07_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[6]);
		lv_label_set_text_fmt(label_sat_val_08_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[7]);
		lv_label_set_text_fmt(label_sat_val_09_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[8]);
		lv_label_set_text_fmt(label_sat_val_10_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[9]);
		lv_label_set_text_fmt(label_sat_val_11_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[10]);
		lv_label_set_text_fmt(label_sat_val_12_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[11]);

		lv_bar_set_value(bar_sat_green_01_scr_uiflowsetupgps, ((g_Edog_satellie_DB.satellie_DB_GSM_BD[0]/50.0)*100/2), LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_02_scr_uiflowsetupgps, ((g_Edog_satellie_DB.satellie_DB_GSM_BD[1]/50.0)*100/2), LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_03_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[2]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_04_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[3]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_05_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[4]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_06_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[5]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_07_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[6]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_08_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[7]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_09_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[8]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_10_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[9]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_11_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[10]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_green_12_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[11]/50.0)*100/2, LV_ANIM_ON);

		//show bar
		lv_obj_set_hidden(bar_sat_green_01_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_02_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_03_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_04_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_05_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_06_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_07_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_08_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_09_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_10_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_11_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_green_12_scr_uiflowsetupgps, false);
	}
	else
	{
		//hide bar
		lv_obj_set_hidden(bar_sat_green_01_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_02_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_03_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_04_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_05_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_06_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_07_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_08_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_09_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_10_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_11_scr_uiflowsetupgps, true);
		lv_obj_set_hidden(bar_sat_green_12_scr_uiflowsetupgps, true);


		lv_label_set_text_fmt(label_sat_val_01_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[0]);
		lv_label_set_text_fmt(label_sat_val_02_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[1]);
		lv_label_set_text_fmt(label_sat_val_03_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[2]);
		lv_label_set_text_fmt(label_sat_val_04_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[3]);
		lv_label_set_text_fmt(label_sat_val_05_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[4]);
		lv_label_set_text_fmt(label_sat_val_06_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[5]);
		lv_label_set_text_fmt(label_sat_val_07_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[6]);
		lv_label_set_text_fmt(label_sat_val_08_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[7]);
		lv_label_set_text_fmt(label_sat_val_09_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[8]);
		lv_label_set_text_fmt(label_sat_val_10_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[9]);
		lv_label_set_text_fmt(label_sat_val_11_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[10]);
		lv_label_set_text_fmt(label_sat_val_12_scr_uiflowsetupgps, "%02d",g_Edog_satellie_DB.satellie_DB_GSM_BD[11]);

		lv_bar_set_value(bar_sat_red_01_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[0]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_02_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[1]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_03_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[2]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_04_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[3]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_05_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[4]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_06_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[5]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_07_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[6]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_08_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[7]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_09_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[8]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_10_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[9]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_11_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[10]/50.0)*100/2, LV_ANIM_ON);
		lv_bar_set_value(bar_sat_red_12_scr_uiflowsetupgps, (g_Edog_satellie_DB.satellie_DB_GSM_BD[11]/50.0)*100/2, LV_ANIM_ON);

		//show bar
		lv_obj_set_hidden(bar_sat_red_01_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_02_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_03_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_04_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_05_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_06_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_07_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_08_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_09_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_10_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_11_scr_uiflowsetupgps, false);
		lv_obj_set_hidden(bar_sat_red_12_scr_uiflowsetupgps, false);
	}
}
static void task_updateGPS_cb(lv_task_t* task)
{
	DBG_DUMP("======task_updateGPS_cb=========\r\n");
	update_gps_icons();
}

static void UIFlowSetupGPS_ScrOpen(lv_obj_t* obj)
{
	/***********************************************************************************
	 * Add SetupGPS Screen into group and set group to keypad indev
	 ***********************************************************************************/
	set_indev_keypad_group(obj);

	if(gUpdateGPSTimerID == NULL)
	{
		gUpdateGPSTimerID = lv_task_create(task_updateGPS_cb, 1000, LV_TASK_PRIO_MID, NULL);
	}
	update_gps_icons();//update onece

}

static void UIFlowSetupGPS_ChildScrClose(lv_obj_t* obj, LV_USER_EVENT_NVTMSG_DATA* data)
{
	set_indev_keypad_group(obj);
}

static void UIFlowSetupGPS_ScrClose(lv_obj_t* obj)
{
	if(gUpdateGPSTimerID)
	{
		lv_task_del(gUpdateGPSTimerID);
		gUpdateGPSTimerID = NULL;
	}
}
static void UIFlowSetupGPS_Key(lv_obj_t* obj, uint32_t key)
{

	switch(key)
	{
	case LV_USER_KEY_SHUTTER2:
	{
		DBG_DUMP("%sLV_USER_KEY_SHUTTER2\r\n", __func__);

		break;
	}

	case LV_USER_KEY_PREV:
	{

		DBG_DUMP("%sLV_USER_KEY_PREV\r\n", __func__);
		break;
	}

	case LV_USER_KEY_NEXT:
	{
		DBG_DUMP("%sLV_USER_KEY_PREV\r\n", __func__);
		break;
	}

	//#NT#2021/09/10#Philex Lin--begin
	case LV_USER_KEY_ZOOMIN:
	{
		break;
	}

	case LV_USER_KEY_ZOOMOUT:
	{
		break;
	}

	case LV_USER_KEY_MENU:
	{
		DBG_DUMP("%sLV_USER_KEY_MENU\r\n", __func__);
		break;
	}

	case LV_USER_KEY_SELECT:
	{
		DBG_DUMP("%sLV_USER_KEY_SELECT\r\n", __func__);
		break;
	}


	case LV_USER_KEY_MODE:
	{

		DBG_DUMP("%sLV_USER_KEY_MODE\r\n", __func__);
		break;
	}

	case LV_KEY_LEFT:
	case LV_KEY_ENTER:
	{
		lv_plugin_scr_close(UIFlowSetupGPS, NULL);
		DBG_DUMP("%sLV_KEY_ENTER\r\n", __func__);
		break;
	}
	//#NT#2021/09/10#Philex Lin--end

	case LV_KEY_UP:
	{

		DBG_DUMP("%sLV_KEY_UP\r\n", __func__);
		break;
	}

	case LV_KEY_DOWN:
	{
		DBG_DUMP("%sLV_KEY_DOWN\r\n", __func__);
		//UIFlowMovie_OnExePIM(obj);
		break;
	}


	}

}

void UIFlowSetupGPSCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{

	case LV_PLUGIN_EVENT_SCR_OPEN:
		UIFlowSetupGPS_ScrOpen(obj);
		break;

	case LV_PLUGIN_EVENT_SCR_CLOSE:
		UIFlowSetupGPS_ScrClose(obj);
		break;

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
		UIFlowSetupGPS_ChildScrClose(obj, (LV_USER_EVENT_NVTMSG_DATA*)lv_event_get_data());
		break;

	/* enter key state changed(pressed -> released) */
	case LV_EVENT_CLICKED:
		break;

	/* any key(including enter key) state changed(pressed), it's recommended to handle enter key in LV_EVENT_CLICKED instead of here. */
	case LV_EVENT_KEY:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();

		/* handle key event */
		UIFlowSetupGPS_Key(obj, *key);

		/* default to block next key event until released, could be removed depend on use cases. */
		if(key && *key != LV_KEY_ENTER)
			lv_indev_wait_release(lv_indev_get_act());
		break;
	}

	case LV_EVENT_GESTURE:
	{
		lv_gesture_dir_t gesture_dir = lv_indev_get_gesture_dir(lv_indev_get_act());

		LV_UNUSED(gesture_dir); /* avoid compile error, please remove it manually */
		break;
	}

	case LV_EVENT_DRAG_BEGIN:
		break;

	case LV_EVENT_DRAG_END:
		break;

	case LV_EVENT_DRAG_THROW_BEGIN:
		break;

	default:
		break;

	}

}

