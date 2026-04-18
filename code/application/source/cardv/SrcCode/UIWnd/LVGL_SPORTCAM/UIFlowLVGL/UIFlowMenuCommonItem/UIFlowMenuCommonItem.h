#ifndef UIFLOWMENUCOMMONITEM_H
#define UIFLOWMENUCOMMONITEM_H

#ifdef __cplusplus
extern "C" {
#endif

/**********************
 *      INCLUDES
 **********************/

#include "lvgl/lvgl.h"

/**********************
 *       WIDGETS
 **********************/
void UIFlowMenuCommonItemEventCallback(lv_obj_t* obj, lv_event_t event);


extern lv_obj_t* container_main_menu_scr_uiflowmenucommonitem;
extern lv_obj_t* button_1_scr_uiflowmenucommonitem;
extern lv_obj_t* image_1_scr_uiflowmenucommonitem;
extern lv_obj_t* label_1_scr_uiflowmenucommonitem;
extern lv_obj_t* button_2_scr_uiflowmenucommonitem;
extern lv_obj_t* image_2_scr_uiflowmenucommonitem;
extern lv_obj_t* label_2_scr_uiflowmenucommonitem;
extern lv_obj_t* button_3_scr_uiflowmenucommonitem;
extern lv_obj_t* image_3_scr_uiflowmenucommonitem;
extern lv_obj_t* label_3_scr_uiflowmenucommonitem;
extern lv_obj_t* button_4_scr_uiflowmenucommonitem;
extern lv_obj_t* image_4_scr_uiflowmenucommonitem;
extern lv_obj_t* label_4_scr_uiflowmenucommonitem;
extern lv_obj_t* container_1_scr_uiflowmenucommonitem;
extern lv_obj_t* image_title_bar_scr_uiflowmenucommonitem;
extern lv_obj_t* label_menu_title_scr_uiflowmenucommonitem;
extern lv_obj_t* label_menu_page_num_scr_uiflowmenucommonitem;
extern lv_obj_t* container_bottom_bar_scr_uiflowmenucommonitem;
extern lv_obj_t* image_hint_bar_scr_uiflowmenucommonitem;
extern lv_obj_t* image_bottom_power_scr_uiflowmenucommonitem;
extern lv_obj_t* image_bottom_sos_scr_uiflowmenucommonitem;
extern lv_obj_t* image_bottom_playback_scr_uiflowmenucommonitem;
extern lv_obj_t* image_bottom_setting_scr_uiflowmenucommonitem;
extern lv_obj_t* image_bottom_closelcd_scr_uiflowmenucommonitem;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t* UIFlowMenuCommonItem_create(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*UIFLOWMENUCOMMONITEM_H*/