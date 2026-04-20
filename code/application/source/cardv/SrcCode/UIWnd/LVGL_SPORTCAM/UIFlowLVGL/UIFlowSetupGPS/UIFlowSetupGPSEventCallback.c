#include "UIFlowLVGL/UIFlowLVGL.h"

void UIFlowSetupGPSCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{

	case LV_PLUGIN_EVENT_SCR_OPEN:
		break;

	case LV_PLUGIN_EVENT_SCR_CLOSE:
		break;

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
		break;

	/* enter key state changed(pressed -> released) */
	case LV_EVENT_CLICKED:
		break;

	/* any key(including enter key) state changed(pressed), it's recommended to handle enter key in LV_EVENT_CLICKED instead of here. */
	case LV_EVENT_KEY:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();

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

