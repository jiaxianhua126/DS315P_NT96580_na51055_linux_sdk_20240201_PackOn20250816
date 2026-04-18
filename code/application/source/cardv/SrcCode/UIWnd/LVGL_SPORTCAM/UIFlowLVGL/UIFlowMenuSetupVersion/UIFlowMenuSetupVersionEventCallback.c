#include "UIFlowLVGL/UIFlowLVGL.h"
#include "PrjInc.h"
#include "GxTime.h"
#include <kwrap/debug.h>

/******************* */

static lv_group_t* gp = NULL;

/***************** */


static void set_indev_keypad_group(lv_obj_t* obj)
{
	if(gp == NULL){
		gp = lv_group_create();
		lv_group_add_obj(gp, obj);
	}

	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_group(indev, gp);
}
#if 0
static void UIFlowMenuSetupVersion_ScrClose(lv_obj_t* obj)
{
	DBG_DUMP("%s\r\n", __func__);
}
#endif
static void UIFlowMenuSetupVersion_ChildScrClose(lv_obj_t* obj)
{
	DBG_DUMP("%s\r\n", __func__);

	set_indev_keypad_group(obj);

}

static void UIFlowMenuSetupVersion_ScrOpen(lv_obj_t* obj, const void *data)
{
	CHAR FwVersion[32] = {0};
	CHAR EdogVer[32] = {0};
	DBG_DUMP("%s\r\n", __func__);
	set_indev_keypad_group(obj);
	snprintf((char*)FwVersion,sizeof(FwVersion),"%s",Prj_GetVersionString());	
	snprintf((char*)EdogVer,sizeof(EdogVer),"%s",GPSRec_GetEdogVersion());
	lv_label_set_text_fmt(label_version_scr_uiflowmenusetupversion, "%s",FwVersion);
	lv_label_set_text_fmt(label_version_1_scr_uiflowmenusetupversion, "%s",EdogVer);
	lv_obj_set_hidden(label_version_scr_uiflowmenusetupversion, FALSE);
	lv_obj_set_hidden(label_version_1_scr_uiflowmenusetupversion, FALSE);
	lv_obj_set_hidden(label_version_2_scr_uiflowmenusetupversion, TRUE);
	lv_obj_set_hidden(label_version_3_scr_uiflowmenusetupversion, TRUE);
	
}
static void UIFlowMenuSetupVersion_Key(lv_obj_t* obj, uint32_t key)
{
	DBG_DUMP("%s\r\n", __func__);

	switch(key)
	{
		case LV_KEY_ENTER:
		case LV_KEY_LEFT:
		{
			lv_plugin_scr_close(UIFlowMenuSetupVersion, NULL);
			break;
		}
		default:
			break;
	}

}

void UIFlowMenuSetupVersionEventCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{

	case LV_PLUGIN_EVENT_SCR_OPEN:
		UIFlowMenuSetupVersion_ScrOpen(obj,lv_event_get_data());
		break;

	case LV_PLUGIN_EVENT_SCR_CLOSE:
		break;

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
		UIFlowMenuSetupVersion_ChildScrClose(obj);
		break;

	/* enter key state changed(pressed -> released) */
	case LV_EVENT_CLICKED:
		break;

	/* any key(including enter key) state changed(pressed), it's recommended to handle enter key in LV_EVENT_CLICKED instead of here. */
	case LV_EVENT_KEY:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();

		UIFlowMenuSetupVersion_Key(obj,*key);
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

