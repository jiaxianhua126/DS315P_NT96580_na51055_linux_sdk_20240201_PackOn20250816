#ifndef UIFLOWMENUCOMMONOPTION_H
#define UIFLOWMENUCOMMONOPTION_H

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
void UIFlowMenuCommonOptionEventCallback(lv_obj_t* obj, lv_event_t event);


extern lv_obj_t* container_main_menu_scr_uiflowmenucommonoption;
extern lv_obj_t* container_1_scr_uiflowmenucommonoption;
extern lv_obj_t* button_1_scr_uiflowmenucommonoption;
extern lv_obj_t* label_1_scr_uiflowmenucommonoption;
extern lv_obj_t* image_select0_scr_uiflowmenucommonoption;
extern lv_obj_t* button_2_scr_uiflowmenucommonoption;
extern lv_obj_t* label_2_scr_uiflowmenucommonoption;
extern lv_obj_t* image_select1_scr_uiflowmenucommonoption;
extern lv_obj_t* button_3_scr_uiflowmenucommonoption;
extern lv_obj_t* label_3_scr_uiflowmenucommonoption;
extern lv_obj_t* image_select2_scr_uiflowmenucommonoption;
extern lv_obj_t* button_4_scr_uiflowmenucommonoption;
extern lv_obj_t* label_4_scr_uiflowmenucommonoption;
extern lv_obj_t* image_select3_scr_uiflowmenucommonoption;
extern lv_obj_t* image_title_bar_scr_uiflowmenucommonoption;
extern lv_obj_t* label_menu_title_scr_uiflowmenucommonoption;
extern lv_obj_t* label_menu_page_num_scr_uiflowmenucommonoption;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t* UIFlowMenuCommonOption_create(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*UIFLOWMENUCOMMONOPTION_H*/