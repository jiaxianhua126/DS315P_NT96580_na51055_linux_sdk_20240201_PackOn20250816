#ifndef UIFLOWMOVIEWIFI_H
#define UIFLOWMOVIEWIFI_H

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
void UIFlowMovieWiFiEventCallback(lv_obj_t* obj, lv_event_t event);


extern lv_obj_t* image_storage_scr_uiflowmoviewifi;
extern lv_obj_t* image_mode_video_scr_uiflowmoviewifi;
extern lv_obj_t* image_battery_scr_uiflowmoviewifi;
extern lv_obj_t* label_date_scr_uiflowmoviewifi;
extern lv_obj_t* label_time_scr_uiflowmoviewifi;
extern lv_obj_t* image_ev_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_rec_scr_uiflowmoviewifi;
extern lv_obj_t* image_pim_scr_uiflowmoviewifi;
extern lv_obj_t* label_status_resolution_scr_uiflowmoviewifi;
extern lv_obj_t* image_cyclic_rec_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_hdr_scr_uiflowmoviewifi;
extern lv_obj_t* image_motiondetect_scr_uiflowmoviewifi;
extern lv_obj_t* label_zoom_scr_uiflowmoviewifi;
extern lv_obj_t* label_status_time_scr_uiflowmoviewifi;
extern lv_obj_t* container_bottom_bar_scr_uiflowmoviewifi;
extern lv_obj_t* divider_menu_1_scr_uiflowmoviewifi;
extern lv_obj_t* divider_menu_2_scr_uiflowmoviewifi;
extern lv_obj_t* divider_menu_3_scr_uiflowmoviewifi;
extern lv_obj_t* divider_menu_4_scr_uiflowmoviewifi;
extern lv_obj_t* image_menu_power_scr_uiflowmoviewifi;
extern lv_obj_t* image_menu_voice_scr_uiflowmoviewifi;
extern lv_obj_t* image_menu_playback_scr_uiflowmoviewifi;
extern lv_obj_t* image_menu_setting_scr_uiflowmoviewifi;
extern lv_obj_t* image_menu_closelcd_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_gps_scr_uiflowmoviewifi;
extern lv_obj_t* label_status_maxtime_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_audio_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_waring_scr_uiflowmoviewifi;
extern lv_obj_t* image_status_wifi_scr_uiflowmoviewifi;
extern lv_obj_t* image_wifi_disconnected_scr_uiflowmoviewifi;
extern lv_obj_t* container_ssid_key_scr_uiflowmoviewifi;
extern lv_obj_t* label_wifi_ssid_scr_uiflowmoviewifi;
extern lv_obj_t* label_wifi_password_scr_uiflowmoviewifi;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t* UIFlowMovieWiFi_create(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*UIFLOWMOVIEWIFI_H*/