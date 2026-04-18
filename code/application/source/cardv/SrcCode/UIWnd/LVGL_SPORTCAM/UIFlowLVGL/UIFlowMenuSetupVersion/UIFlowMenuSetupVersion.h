#ifndef UIFLOWMENUSETUPVERSION_H
#define UIFLOWMENUSETUPVERSION_H

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
void UIFlowMenuSetupVersionEventCallback(lv_obj_t* obj, lv_event_t event);


extern lv_obj_t* container_1_scr_uiflowmenusetupversion;
extern lv_obj_t* label_version_scr_uiflowmenusetupversion;
extern lv_obj_t* label_version_1_scr_uiflowmenusetupversion;
extern lv_obj_t* label_version_2_scr_uiflowmenusetupversion;
extern lv_obj_t* label_version_3_scr_uiflowmenusetupversion;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t* UIFlowMenuSetupVersion_create(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*UIFLOWMENUSETUPVERSION_H*/