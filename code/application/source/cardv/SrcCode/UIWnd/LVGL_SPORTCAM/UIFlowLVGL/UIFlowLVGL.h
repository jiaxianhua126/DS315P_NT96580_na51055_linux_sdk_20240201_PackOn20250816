#ifndef UIFLOWLVGL_H
#define UIFLOWLVGL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "Resource/Plugin/lvgl_plugin.h"

void UIFlowLVGL(void);

#include "UIFlowLVGL/UIFlowMovie/UIFlowMovie.h"
#include "UIFlowLVGL/UIFlowPhoto/UIFlowPhoto.h"
#include "UIFlowLVGL/UIFlowWrnMsg/UIFlowWrnMsg.h"
#include "UIFlowLVGL/UIFlowPlay/UIFlowPlay.h"
#include "UIFlowLVGL/UIFlowMenuCommonItem/UIFlowMenuCommonItem.h"
#include "UIFlowLVGL/UIFlowMenuCommonOption/UIFlowMenuCommonOption.h"
#include "UIFlowLVGL/UIFlowMenuCommonConfirm/UIFlowMenuCommonConfirm.h"
#include "UIFlowLVGL/UIFlowWaitMoment/UIFlowWaitMoment.h"
#include "UIFlowLVGL/UIFlowSetupDateTime/UIFlowSetupDateTime.h"
#include "UIFlowLVGL/UIFlowSetupGPS/UIFlowSetupGPS.h"
#include "UIFlowLVGL/UIFlowPlayThumb/UIFlowPlayThumb.h"
#include "UIFlowLVGL/UIFlowUSB/UIFlowUSB.h"
#include "UIFlowLVGL/UIFlowUSBMenu/UIFlowUSBMenu.h"
#include "UIFlowLVGL/UIFlowWifiLink/UIFlowWifiLink.h"
#include "UIFlowLVGL/UIFlowWifiLinkOK/UIFlowWifiLinkOK.h"
#include "UIFlowLVGL/UIFlowWifiWait/UIFlowWifiWait.h"
#include "UIFlowLVGL/UIFlowMovieWiFi/UIFlowMovieWiFi.h"
#include "UIFlowLVGL/UIFlowMenuSetupVersion/UIFlowMenuSetupVersion.h"


#if LV_COLOR_DEPTH == 8
	#define COLOR_PICK(INDEX, COLOR)	(COLOR.full = INDEX)
#else
	#define COLOR_PICK(INDEX, COLOR)
#endif

#define STYLE_COLOR_PROP(INDEX, R, G, B) color = LV_COLOR_MAKE(R, G, B); COLOR_PICK(INDEX, color);

extern lv_obj_t *UIFlowMovie;
extern lv_obj_t *UIFlowPhoto;
extern lv_obj_t *UIFlowWrnMsg;
extern lv_obj_t *UIFlowPlay;
extern lv_obj_t *UIFlowMenuCommonItem;
extern lv_obj_t *UIFlowMenuCommonOption;
extern lv_obj_t *UIFlowMenuCommonConfirm;
extern lv_obj_t *UIFlowWaitMoment;
extern lv_obj_t *UIFlowSetupDateTime;
extern lv_obj_t *UIFlowSetupGPS;
extern lv_obj_t *UIFlowPlayThumb;
extern lv_obj_t *UIFlowUSB;
extern lv_obj_t *UIFlowUSBMenu;
extern lv_obj_t *UIFlowWifiLink;
extern lv_obj_t *UIFlowWifiLinkOK;
extern lv_obj_t *UIFlowWifiWait;
extern lv_obj_t *UIFlowMovieWiFi;
extern lv_obj_t *UIFlowMenuSetupVersion;

LV_FONT_DECLARE(notosans_black_32_1bpp);
LV_FONT_DECLARE(notosans_black_48_1bpp);
LV_FONT_DECLARE(notosans_black_64_1bpp);
LV_FONT_DECLARE(notosans_black_128_1bpp);

void message_box_wrnmsg_event_callback(lv_obj_t* obj, lv_event_t event);
void button_del_event_callback(lv_obj_t* obj, lv_event_t event);
void button_prev_event_callback(lv_obj_t* obj, lv_event_t event);
void button_sel_event_callback(lv_obj_t* obj, lv_event_t event);
void button_next_event_callback(lv_obj_t* obj, lv_event_t event);
void button_home_event_callback(lv_obj_t* obj, lv_event_t event);
void message_box_confirm_msg_event_callback(lv_obj_t* obj, lv_event_t event);
void btn_msdc_event_callback(lv_obj_t* obj, lv_event_t event);
void btn_pcc_event_callback(lv_obj_t* obj, lv_event_t event);
void btn_ref_event_callback(lv_obj_t* obj, lv_event_t event);
void btn_wifioff_event_callback(lv_obj_t* obj, lv_event_t event);
void btn_sel_event_callback(lv_obj_t* obj, lv_event_t event);

LV_IMG_DECLARE(bye_en);
LV_IMG_DECLARE(bye_jp);
LV_IMG_DECLARE(bye_sc);
LV_IMG_DECLARE(bye_tc);
LV_IMG_DECLARE(icon_0b);
LV_IMG_DECLARE(icon_0r);
LV_IMG_DECLARE(icon_1b);
LV_IMG_DECLARE(icon_1r);
LV_IMG_DECLARE(icon_2b);
LV_IMG_DECLARE(icon_2r);
LV_IMG_DECLARE(icon_3b);
LV_IMG_DECLARE(icon_3r);
LV_IMG_DECLARE(icon_4b);
LV_IMG_DECLARE(icon_4r);
LV_IMG_DECLARE(icon_5b);
LV_IMG_DECLARE(icon_5r);
LV_IMG_DECLARE(icon_6b);
LV_IMG_DECLARE(icon_6r);
LV_IMG_DECLARE(icon_7b);
LV_IMG_DECLARE(icon_7r);
LV_IMG_DECLARE(icon_8b);
LV_IMG_DECLARE(icon_8r);
LV_IMG_DECLARE(icon_9b);
LV_IMG_DECLARE(icon_9r);
LV_IMG_DECLARE(icon_act_push_btn);
LV_IMG_DECLARE(icon_act_release_btn);
LV_IMG_DECLARE(icon_adas_00);
LV_IMG_DECLARE(icon_adas_01);
LV_IMG_DECLARE(icon_adas_02);
LV_IMG_DECLARE(icon_adas_03);
LV_IMG_DECLARE(icon_adas_04);
LV_IMG_DECLARE(icon_adas_05);
LV_IMG_DECLARE(icon_adas_06);
LV_IMG_DECLARE(icon_adas_07);
LV_IMG_DECLARE(icon_adas_08);
LV_IMG_DECLARE(icon_adas_09);
LV_IMG_DECLARE(icon_adas_animation_01);
LV_IMG_DECLARE(icon_adas_animation_02);
LV_IMG_DECLARE(icon_adas_animation_03);
LV_IMG_DECLARE(icon_adas_animation_04);
LV_IMG_DECLARE(icon_adas_animation_05);
LV_IMG_DECLARE(icon_adas_animation_06);
LV_IMG_DECLARE(icon_adas_animation_07);
LV_IMG_DECLARE(icon_adas_animation_08);
LV_IMG_DECLARE(icon_adas_animation_09);
LV_IMG_DECLARE(icon_adas_animation_10);
LV_IMG_DECLARE(icon_adas_animation_11);
LV_IMG_DECLARE(icon_adas_animation_12);
LV_IMG_DECLARE(icon_adas_animation_13);
LV_IMG_DECLARE(icon_adas_animation_14);
LV_IMG_DECLARE(icon_adas_animation_bg);
LV_IMG_DECLARE(icon_adas_cal);
LV_IMG_DECLARE(icon_adas_cal_m);
LV_IMG_DECLARE(icon_adas_car_blue);
LV_IMG_DECLARE(icon_adas_car_red);
LV_IMG_DECLARE(icon_adas_car_white);
LV_IMG_DECLARE(icon_adas_change_lane_left);
LV_IMG_DECLARE(icon_adas_change_lane_right);
LV_IMG_DECLARE(icon_adas_dis_alert);
LV_IMG_DECLARE(icon_adas_dis_seperate);
LV_IMG_DECLARE(icon_adas_front_alert);
LV_IMG_DECLARE(icon_adas_front_car_dis_bg);
LV_IMG_DECLARE(icon_adas_ft);
LV_IMG_DECLARE(icon_adas_go_alert);
LV_IMG_DECLARE(icon_adas_lane_left);
LV_IMG_DECLARE(icon_adas_lane_right);
LV_IMG_DECLARE(icon_adas_off);
LV_IMG_DECLARE(icon_adas_off_m);
LV_IMG_DECLARE(icon_adas_on);
LV_IMG_DECLARE(icon_adas_on_m);
LV_IMG_DECLARE(icon_adas_people_alert);
LV_IMG_DECLARE(icon_adas_rear_alert);
LV_IMG_DECLARE(icon_adas_road);
LV_IMG_DECLARE(icon_adas_road_01);
LV_IMG_DECLARE(icon_adas_road_02);
LV_IMG_DECLARE(icon_adas_road_03);
LV_IMG_DECLARE(icon_adas_road_04);
LV_IMG_DECLARE(icon_adas_road_05);
LV_IMG_DECLARE(icon_adas_road_06);
LV_IMG_DECLARE(icon_adas_virtual_bumper);
LV_IMG_DECLARE(icon_adas_warn_bg);
LV_IMG_DECLARE(icon_ap_machine_off);
LV_IMG_DECLARE(icon_ap_machine_on);
LV_IMG_DECLARE(icon_autoshutdown);
LV_IMG_DECLARE(icon_autoshutdown_10min);
LV_IMG_DECLARE(icon_autoshutdown_3min);
LV_IMG_DECLARE(icon_autoshutdown_5min);
LV_IMG_DECLARE(icon_autoshutdown_m);
LV_IMG_DECLARE(icon_autoshutdown_off);
LV_IMG_DECLARE(icon_auto_1fps);
LV_IMG_DECLARE(icon_auto_1fps1);
LV_IMG_DECLARE(icon_back);
LV_IMG_DECLARE(icon_backlight);
LV_IMG_DECLARE(icon_backlight_high);
LV_IMG_DECLARE(icon_backlight_low);
LV_IMG_DECLARE(icon_backlight_m);
LV_IMG_DECLARE(icon_backlight_mid);
LV_IMG_DECLARE(icon_backlight_off);
LV_IMG_DECLARE(icon_battery_charge);
LV_IMG_DECLARE(icon_battery_empty);
LV_IMG_DECLARE(icon_battery_full);
LV_IMG_DECLARE(icon_battery_low);
LV_IMG_DECLARE(icon_battery_med);
LV_IMG_DECLARE(icon_battery_type);
LV_IMG_DECLARE(icon_battery_zero);
LV_IMG_DECLARE(icon_bsd_off);
LV_IMG_DECLARE(icon_bsd_off_m);
LV_IMG_DECLARE(icon_bsd_on);
LV_IMG_DECLARE(icon_bsd_on_m);
LV_IMG_DECLARE(icon_btn_emboss);
LV_IMG_DECLARE(icon_bust);
LV_IMG_DECLARE(icon_bust_3shot);
LV_IMG_DECLARE(icon_bust_continue);
LV_IMG_DECLARE(icon_bust_m);
LV_IMG_DECLARE(icon_bust_off);
LV_IMG_DECLARE(icon_camera_mode);
LV_IMG_DECLARE(icon_cam_ptz_off);
LV_IMG_DECLARE(icon_cam_ptz_on);
LV_IMG_DECLARE(icon_cam_ptz_on_m);
LV_IMG_DECLARE(icon_cancel);
LV_IMG_DECLARE(icon_cancel_m);
LV_IMG_DECLARE(icon_car_camera);
LV_IMG_DECLARE(icon_car_no);
LV_IMG_DECLARE(icon_close);
LV_IMG_DECLARE(icon_close_wifi);
LV_IMG_DECLARE(icon_cloud_connected);
LV_IMG_DECLARE(icon_cloud_connected_m);
LV_IMG_DECLARE(icon_cloud_connecting);
LV_IMG_DECLARE(icon_cloud_connecting_m);
LV_IMG_DECLARE(icon_cloud_download1);
LV_IMG_DECLARE(icon_cloud_download2);
LV_IMG_DECLARE(icon_cloud_fail);
LV_IMG_DECLARE(icon_cloud_off);
LV_IMG_DECLARE(icon_cloud_off_m);
LV_IMG_DECLARE(icon_cloud_on);
LV_IMG_DECLARE(icon_cloud_on_m);
LV_IMG_DECLARE(icon_cloud_upload1);
LV_IMG_DECLARE(icon_cloud_upload2);
LV_IMG_DECLARE(icon_codec_h265);
LV_IMG_DECLARE(icon_coln);
LV_IMG_DECLARE(icon_color);
LV_IMG_DECLARE(icon_copy_from_card);
LV_IMG_DECLARE(icon_correct);
LV_IMG_DECLARE(icon_cyclic_rec);
LV_IMG_DECLARE(icon_cyclic_rec_10min);
LV_IMG_DECLARE(icon_cyclic_rec_15min);
LV_IMG_DECLARE(icon_cyclic_rec_1min);
LV_IMG_DECLARE(icon_cyclic_rec_2min);
LV_IMG_DECLARE(icon_cyclic_rec_3min);
LV_IMG_DECLARE(icon_cyclic_rec_5min);
LV_IMG_DECLARE(icon_cyclic_rec_m);
LV_IMG_DECLARE(icon_datetime_setup);
LV_IMG_DECLARE(icon_datetime_setup_m);
LV_IMG_DECLARE(icon_date_print);
LV_IMG_DECLARE(icon_date_print_m);
LV_IMG_DECLARE(icon_date_stamping);
LV_IMG_DECLARE(icon_date_time);
LV_IMG_DECLARE(icon_ddd_off);
LV_IMG_DECLARE(icon_ddd_off_m);
LV_IMG_DECLARE(icon_ddd_on);
LV_IMG_DECLARE(icon_ddd_on_m);
LV_IMG_DECLARE(icon_default);
LV_IMG_DECLARE(icon_default_m);
LV_IMG_DECLARE(icon_delete);
LV_IMG_DECLARE(icon_delete_all);
LV_IMG_DECLARE(icon_delete_current);
LV_IMG_DECLARE(icon_delete_m);
LV_IMG_DECLARE(icon_dir_d);
LV_IMG_DECLARE(icon_dir_down);
LV_IMG_DECLARE(icon_dir_l);
LV_IMG_DECLARE(icon_dir_left);
LV_IMG_DECLARE(icon_dir_r);
LV_IMG_DECLARE(icon_dir_right);
LV_IMG_DECLARE(icon_dir_u);
LV_IMG_DECLARE(icon_dir_up);
LV_IMG_DECLARE(icon_dpof);
LV_IMG_DECLARE(icon_dualcam_behind);
LV_IMG_DECLARE(icon_dualcam_both);
LV_IMG_DECLARE(icon_dualcam_both_m);
LV_IMG_DECLARE(icon_dualcam_front);
LV_IMG_DECLARE(icon_edog_00km);
LV_IMG_DECLARE(icon_edog_100km);
LV_IMG_DECLARE(icon_edog_110km);
LV_IMG_DECLARE(icon_edog_120km);
LV_IMG_DECLARE(icon_edog_20km);
LV_IMG_DECLARE(icon_edog_30km);
LV_IMG_DECLARE(icon_edog_40km);
LV_IMG_DECLARE(icon_edog_50km);
LV_IMG_DECLARE(icon_edog_60km);
LV_IMG_DECLARE(icon_edog_70km);
LV_IMG_DECLARE(icon_edog_80km);
LV_IMG_DECLARE(icon_edog_90km);
LV_IMG_DECLARE(icon_edog_average_speed);
LV_IMG_DECLARE(icon_edog_bg);
LV_IMG_DECLARE(icon_edog_captur);
LV_IMG_DECLARE(icon_edog_dis);
LV_IMG_DECLARE(icon_edog_distance);
LV_IMG_DECLARE(icon_edog_km);
LV_IMG_DECLARE(icon_edog_kmh_big);
LV_IMG_DECLARE(icon_edog_kmh_red);
LV_IMG_DECLARE(icon_edog_kmh_small);
LV_IMG_DECLARE(icon_edog_km_small);
LV_IMG_DECLARE(icon_edog_m);
LV_IMG_DECLARE(icon_edog_min_small);
LV_IMG_DECLARE(icon_edog_m_small);
LV_IMG_DECLARE(icon_edog_num_red_0);
LV_IMG_DECLARE(icon_edog_num_red_1);
LV_IMG_DECLARE(icon_edog_num_red_2);
LV_IMG_DECLARE(icon_edog_num_red_3);
LV_IMG_DECLARE(icon_edog_num_red_4);
LV_IMG_DECLARE(icon_edog_num_red_5);
LV_IMG_DECLARE(icon_edog_num_red_6);
LV_IMG_DECLARE(icon_edog_num_red_7);
LV_IMG_DECLARE(icon_edog_num_red_8);
LV_IMG_DECLARE(icon_edog_num_red_9);
LV_IMG_DECLARE(icon_edog_num_red_small_0);
LV_IMG_DECLARE(icon_edog_num_red_small_1);
LV_IMG_DECLARE(icon_edog_num_red_small_2);
LV_IMG_DECLARE(icon_edog_num_red_small_3);
LV_IMG_DECLARE(icon_edog_num_red_small_4);
LV_IMG_DECLARE(icon_edog_num_red_small_5);
LV_IMG_DECLARE(icon_edog_num_red_small_6);
LV_IMG_DECLARE(icon_edog_num_red_small_7);
LV_IMG_DECLARE(icon_edog_num_red_small_8);
LV_IMG_DECLARE(icon_edog_num_red_small_9);
LV_IMG_DECLARE(icon_edog_num_yellow_0);
LV_IMG_DECLARE(icon_edog_num_yellow_1);
LV_IMG_DECLARE(icon_edog_num_yellow_2);
LV_IMG_DECLARE(icon_edog_num_yellow_3);
LV_IMG_DECLARE(icon_edog_num_yellow_4);
LV_IMG_DECLARE(icon_edog_num_yellow_5);
LV_IMG_DECLARE(icon_edog_num_yellow_6);
LV_IMG_DECLARE(icon_edog_num_yellow_7);
LV_IMG_DECLARE(icon_edog_num_yellow_8);
LV_IMG_DECLARE(icon_edog_num_yellow_9);
LV_IMG_DECLARE(icon_edog_num_yellow_small_0);
LV_IMG_DECLARE(icon_edog_num_yellow_small_1);
LV_IMG_DECLARE(icon_edog_num_yellow_small_2);
LV_IMG_DECLARE(icon_edog_num_yellow_small_3);
LV_IMG_DECLARE(icon_edog_num_yellow_small_4);
LV_IMG_DECLARE(icon_edog_num_yellow_small_5);
LV_IMG_DECLARE(icon_edog_num_yellow_small_6);
LV_IMG_DECLARE(icon_edog_num_yellow_small_7);
LV_IMG_DECLARE(icon_edog_num_yellow_small_8);
LV_IMG_DECLARE(icon_edog_num_yellow_small_9);
LV_IMG_DECLARE(icon_edog_redgreen);
LV_IMG_DECLARE(icon_edog_sec_small);
LV_IMG_DECLARE(icon_edog_time);
LV_IMG_DECLARE(icon_edog_type_accident);
LV_IMG_DECLARE(icon_edog_type_bus);
LV_IMG_DECLARE(icon_edog_type_dawandao);
LV_IMG_DECLARE(icon_edog_type_down_hill);
LV_IMG_DECLARE(icon_edog_type_entry);
LV_IMG_DECLARE(icon_edog_type_exit);
LV_IMG_DECLARE(icon_edog_type_jiaoliudao);
LV_IMG_DECLARE(icon_edog_type_monitor);
LV_IMG_DECLARE(icon_edog_type_no_drinking);
LV_IMG_DECLARE(icon_edog_type_no_left_turn);
LV_IMG_DECLARE(icon_edog_type_no_parking);
LV_IMG_DECLARE(icon_edog_type_oil_station);
LV_IMG_DECLARE(icon_edog_type_police);
LV_IMG_DECLARE(icon_edog_type_school);
LV_IMG_DECLARE(icon_edog_type_service_center);
LV_IMG_DECLARE(icon_edog_type_straight_line);
LV_IMG_DECLARE(icon_edog_type_train_way);
LV_IMG_DECLARE(icon_edog_type_tunnel);
LV_IMG_DECLARE(icon_edog_warn_bg);
LV_IMG_DECLARE(icon_edog_warn_bg_single);
LV_IMG_DECLARE(icon_ev);
LV_IMG_DECLARE(icon_ev_m);
LV_IMG_DECLARE(icon_ev_m0p3);
LV_IMG_DECLARE(icon_ev_m0p6);
LV_IMG_DECLARE(icon_ev_m1p0);
LV_IMG_DECLARE(icon_ev_m1p3);
LV_IMG_DECLARE(icon_ev_m1p6);
LV_IMG_DECLARE(icon_ev_m2p0);
LV_IMG_DECLARE(icon_ev_p0p0);
LV_IMG_DECLARE(icon_ev_p0p3);
LV_IMG_DECLARE(icon_ev_p0p6);
LV_IMG_DECLARE(icon_ev_p1p0);
LV_IMG_DECLARE(icon_ev_p1p3);
LV_IMG_DECLARE(icon_ev_p1p6);
LV_IMG_DECLARE(icon_ev_p2p0);
LV_IMG_DECLARE(icon_face_off);
LV_IMG_DECLARE(icon_face_on);
LV_IMG_DECLARE(icon_face_on_m);
LV_IMG_DECLARE(icon_fatigue_driving);
LV_IMG_DECLARE(icon_fatigue_driving_alert);
LV_IMG_DECLARE(icon_fb_left);
LV_IMG_DECLARE(icon_fb_left_ori);
LV_IMG_DECLARE(icon_fcw_far_alert);
LV_IMG_DECLARE(icon_fcw_near_alert);
LV_IMG_DECLARE(icon_fcw_off);
LV_IMG_DECLARE(icon_fcw_off_m);
LV_IMG_DECLARE(icon_fcw_on);
LV_IMG_DECLARE(icon_fcw_on_m);
LV_IMG_DECLARE(icon_ff_right);
LV_IMG_DECLARE(icon_ff_right_ori);
LV_IMG_DECLARE(icon_file_lock);
LV_IMG_DECLARE(icon_file_video);
LV_IMG_DECLARE(icon_firmware_update);
LV_IMG_DECLARE(icon_firmware_update_m);
LV_IMG_DECLARE(icon_flash_auto);
LV_IMG_DECLARE(icon_flash_off);
LV_IMG_DECLARE(icon_flash_on);
LV_IMG_DECLARE(icon_flash_on_m);
LV_IMG_DECLARE(icon_flash_rec);
LV_IMG_DECLARE(icon_flash_rec_m);
LV_IMG_DECLARE(icon_flash_red_eye);
LV_IMG_DECLARE(icon_flick_50hz);
LV_IMG_DECLARE(icon_flick_60hz);
LV_IMG_DECLARE(icon_format);
LV_IMG_DECLARE(icon_format_m);
LV_IMG_DECLARE(icon_golf_rec);
LV_IMG_DECLARE(icon_golf_rec_m);
LV_IMG_DECLARE(icon_gps);
LV_IMG_DECLARE(icon_gps_off);
LV_IMG_DECLARE(icon_gps_on);
LV_IMG_DECLARE(icon_gps_on_m);
LV_IMG_DECLARE(icon_gsensor);
LV_IMG_DECLARE(icon_g_sensor);
LV_IMG_DECLARE(icon_g_sensor_high);
LV_IMG_DECLARE(icon_g_sensor_low);
LV_IMG_DECLARE(icon_g_sensor_m);
LV_IMG_DECLARE(icon_g_sensor_mid);
LV_IMG_DECLARE(icon_g_sensor_off);
LV_IMG_DECLARE(icon_hdr);
LV_IMG_DECLARE(icon_hdr_m);
LV_IMG_DECLARE(icon_hdr_off);
LV_IMG_DECLARE(icon_help);
LV_IMG_DECLARE(icon_help_m);
LV_IMG_DECLARE(icon_hint_bar);
LV_IMG_DECLARE(icon_hz);
LV_IMG_DECLARE(icon_hz_50);
LV_IMG_DECLARE(icon_hz_60);
LV_IMG_DECLARE(icon_hz_m);
LV_IMG_DECLARE(icon_info);
LV_IMG_DECLARE(icon_info_m);
LV_IMG_DECLARE(icon_internal_flash);
LV_IMG_DECLARE(icon_ircut_auto);
LV_IMG_DECLARE(icon_ircut_off);
LV_IMG_DECLARE(icon_ircut_on_m);
LV_IMG_DECLARE(icon_iso);
LV_IMG_DECLARE(icon_iso_100);
LV_IMG_DECLARE(icon_iso_1600);
LV_IMG_DECLARE(icon_iso_200);
LV_IMG_DECLARE(icon_iso_400);
LV_IMG_DECLARE(icon_iso_800);
LV_IMG_DECLARE(icon_iso_auto);
LV_IMG_DECLARE(icon_iso_m);
LV_IMG_DECLARE(icon_landscape);
LV_IMG_DECLARE(icon_language);
LV_IMG_DECLARE(icon_language_m);
LV_IMG_DECLARE(icon_ldws_left_alert);
LV_IMG_DECLARE(icon_ldws_off);
LV_IMG_DECLARE(icon_ldws_off_m);
LV_IMG_DECLARE(icon_ldws_on);
LV_IMG_DECLARE(icon_ldws_on_m);
LV_IMG_DECLARE(icon_ldws_right_alert);
LV_IMG_DECLARE(icon_led_det);
LV_IMG_DECLARE(icon_local_station__off);
LV_IMG_DECLARE(icon_local_station__on);
LV_IMG_DECLARE(icon_lock);
LV_IMG_DECLARE(icon_lock_all);
LV_IMG_DECLARE(icon_lock_all_m);
LV_IMG_DECLARE(icon_lock_current);
LV_IMG_DECLARE(icon_lock_current_m);
LV_IMG_DECLARE(icon_lock_m);
LV_IMG_DECLARE(icon_lock_unlock);
LV_IMG_DECLARE(icon_lock_unlock_m);
LV_IMG_DECLARE(icon_lock_unlokc_all);
LV_IMG_DECLARE(icon_lock_unlokc_all_m);
LV_IMG_DECLARE(icon_lpr_off);
LV_IMG_DECLARE(icon_lpr_off_m);
LV_IMG_DECLARE(icon_lpr_on);
LV_IMG_DECLARE(icon_lpr_on_m);
LV_IMG_DECLARE(icon_menu_flash_rec);
LV_IMG_DECLARE(icon_menu_hdr);
LV_IMG_DECLARE(icon_menu_modechang);
LV_IMG_DECLARE(icon_menu_modechang_m);
LV_IMG_DECLARE(icon_menu_playback_off);
LV_IMG_DECLARE(icon_menu_playback_on);
LV_IMG_DECLARE(icon_menu_print_off);
LV_IMG_DECLARE(icon_menu_return);
LV_IMG_DECLARE(icon_menu_return_m);
LV_IMG_DECLARE(icon_menu_setup_off);
LV_IMG_DECLARE(icon_menu_setup_on);
LV_IMG_DECLARE(icon_menu_setup_on_m);
LV_IMG_DECLARE(icon_menu_still_off);
LV_IMG_DECLARE(icon_menu_still_on);
LV_IMG_DECLARE(icon_menu_underbar);
LV_IMG_DECLARE(icon_menu_video_off);
LV_IMG_DECLARE(icon_menu_video_on);
LV_IMG_DECLARE(icon_menu_wdr);
LV_IMG_DECLARE(icon_menu_wdr_m);
LV_IMG_DECLARE(icon_menu_wdr_off);
LV_IMG_DECLARE(icon_metering);
LV_IMG_DECLARE(icon_metering_m);
LV_IMG_DECLARE(icon_mode_capture);
LV_IMG_DECLARE(icon_mode_capture_m);
LV_IMG_DECLARE(icon_mode_playback);
LV_IMG_DECLARE(icon_mode_playback_m);
LV_IMG_DECLARE(icon_mode_video);
LV_IMG_DECLARE(icon_mode_video_m);
LV_IMG_DECLARE(icon_motion_det_off);
LV_IMG_DECLARE(icon_motion_det_on);
LV_IMG_DECLARE(icon_motion_det_on_m);
LV_IMG_DECLARE(icon_movie_menu_waring);
LV_IMG_DECLARE(icon_no);
LV_IMG_DECLARE(icon_no_m);
LV_IMG_DECLARE(icon_ok);
LV_IMG_DECLARE(icon_ok2);
LV_IMG_DECLARE(icon_ok_m);
LV_IMG_DECLARE(icon_ok_m_2);
LV_IMG_DECLARE(icon_ok_pause);
LV_IMG_DECLARE(icon_ok_play);
LV_IMG_DECLARE(icon_ok_s);
LV_IMG_DECLARE(icon_parkingmode_gsensor);
LV_IMG_DECLARE(icon_parkingmode_lb);
LV_IMG_DECLARE(icon_parkingmode_md);
LV_IMG_DECLARE(icon_parkingmode_tl);
LV_IMG_DECLARE(icon_pause);
LV_IMG_DECLARE(icon_pd_off);
LV_IMG_DECLARE(icon_pd_off_m);
LV_IMG_DECLARE(icon_pd_on);
LV_IMG_DECLARE(icon_pd_on_m);
LV_IMG_DECLARE(icon_pictbridge_s);
LV_IMG_DECLARE(icon_pim_off);
LV_IMG_DECLARE(icon_pim_off_m);
LV_IMG_DECLARE(icon_pim_on);
LV_IMG_DECLARE(icon_pim_on_m);
LV_IMG_DECLARE(icon_play);
LV_IMG_DECLARE(icon_play_backward);
LV_IMG_DECLARE(icon_play_ff_b);
LV_IMG_DECLARE(icon_play_ff_f);
LV_IMG_DECLARE(icon_play_forward);
LV_IMG_DECLARE(icon_play_pause);
LV_IMG_DECLARE(icon_play_play);
LV_IMG_DECLARE(icon_play_step);
LV_IMG_DECLARE(icon_play_stop);
LV_IMG_DECLARE(icon_power_off);
LV_IMG_DECLARE(icon_power_off_m);
LV_IMG_DECLARE(icon_print);
LV_IMG_DECLARE(icon_protect);
LV_IMG_DECLARE(icon_protect_m);
LV_IMG_DECLARE(icon_quality);
LV_IMG_DECLARE(icon_quality_basic);
LV_IMG_DECLARE(icon_quality_fine);
LV_IMG_DECLARE(icon_quality_m);
LV_IMG_DECLARE(icon_quality_normal);
LV_IMG_DECLARE(icon_quick_review);
LV_IMG_DECLARE(icon_quick_review_m);
LV_IMG_DECLARE(icon_rec_elippse);
LV_IMG_DECLARE(icon_rec_ellipse);
LV_IMG_DECLARE(icon_rec_recovery);
LV_IMG_DECLARE(icon_rec_transpaent);
LV_IMG_DECLARE(icon_remind_light);
LV_IMG_DECLARE(icon_remind_light_alert);
LV_IMG_DECLARE(icon_resolution);
LV_IMG_DECLARE(icon_resolution_m);
LV_IMG_DECLARE(icon_rotate);
LV_IMG_DECLARE(icon_rsc_off);
LV_IMG_DECLARE(icon_rsc_on);
LV_IMG_DECLARE(icon_rsc_on_m);
LV_IMG_DECLARE(icon_scene_mode);
LV_IMG_DECLARE(icon_scene_mode_auto);
LV_IMG_DECLARE(icon_scene_mode_landscpe);
LV_IMG_DECLARE(icon_scene_mode_m);
LV_IMG_DECLARE(icon_scene_mode_portrial);
LV_IMG_DECLARE(icon_screensaver);
LV_IMG_DECLARE(icon_screensaver_10min);
LV_IMG_DECLARE(icon_screensaver_3min);
LV_IMG_DECLARE(icon_screensaver_5min);
LV_IMG_DECLARE(icon_screensaver_m);
LV_IMG_DECLARE(icon_screensaver_off);
LV_IMG_DECLARE(icon_screen_saver);
LV_IMG_DECLARE(icon_sd_card);
LV_IMG_DECLARE(icon_sd_lock);
LV_IMG_DECLARE(icon_selftimer);
LV_IMG_DECLARE(icon_selftimer_10sec);
LV_IMG_DECLARE(icon_selftimer_2sec);
LV_IMG_DECLARE(icon_selftimer_5sec);
LV_IMG_DECLARE(icon_selftimer_m);
LV_IMG_DECLARE(icon_selftimer_off);
LV_IMG_DECLARE(icon_sel_bar);
LV_IMG_DECLARE(icon_sel_bar_begin);
LV_IMG_DECLARE(icon_sel_bar_carno);
LV_IMG_DECLARE(icon_sel_bar_date);
LV_IMG_DECLARE(icon_sel_bar_end);
LV_IMG_DECLARE(icon_sel_bar_item);
LV_IMG_DECLARE(icon_sel_bar_med);
LV_IMG_DECLARE(icon_sel_bar_year);
LV_IMG_DECLARE(icon_sel_focus);
LV_IMG_DECLARE(icon_sequence_no);
LV_IMG_DECLARE(icon_set);
LV_IMG_DECLARE(icon_set_lock);
LV_IMG_DECLARE(icon_shake_off);
LV_IMG_DECLARE(icon_shake_on);
LV_IMG_DECLARE(icon_shake_on_m);
LV_IMG_DECLARE(icon_sharpness);
LV_IMG_DECLARE(icon_sharpness_high);
LV_IMG_DECLARE(icon_sharpness_low);
LV_IMG_DECLARE(icon_sharpness_m);
LV_IMG_DECLARE(icon_sharpness_med);
LV_IMG_DECLARE(icon_signal_0step);
LV_IMG_DECLARE(icon_signal_0step_m);
LV_IMG_DECLARE(icon_signal_1step);
LV_IMG_DECLARE(icon_signal_1step_m);
LV_IMG_DECLARE(icon_signal_2step);
LV_IMG_DECLARE(icon_signal_2step_m);
LV_IMG_DECLARE(icon_slideshow);
LV_IMG_DECLARE(icon_slideshow_2sec);
LV_IMG_DECLARE(icon_slideshow_5sec);
LV_IMG_DECLARE(icon_slideshow_8sec);
LV_IMG_DECLARE(icon_slideshow_m);
LV_IMG_DECLARE(icon_slideshow_off);
LV_IMG_DECLARE(icon_slide_show);
LV_IMG_DECLARE(icon_smile);
LV_IMG_DECLARE(icon_smile_m);
LV_IMG_DECLARE(icon_sng);
LV_IMG_DECLARE(icon_sng_alert);
LV_IMG_DECLARE(icon_sng_alert_ori);
LV_IMG_DECLARE(icon_sng_off);
LV_IMG_DECLARE(icon_sng_off_m);
LV_IMG_DECLARE(icon_sng_on);
LV_IMG_DECLARE(icon_sng_on_m);
LV_IMG_DECLARE(icon_sound_rec_off);
LV_IMG_DECLARE(icon_sound_rec_on);
LV_IMG_DECLARE(icon_sound_rec_on_m);
LV_IMG_DECLARE(icon_speaker);
LV_IMG_DECLARE(icon_ssid);
LV_IMG_DECLARE(icon_sys_cal);
LV_IMG_DECLARE(icon_sys_cal_m);
LV_IMG_DECLARE(icon_time_lapse_off);
LV_IMG_DECLARE(icon_time_lapse_on);
LV_IMG_DECLARE(icon_time_lapse_on_m);
LV_IMG_DECLARE(icon_title_bar);
LV_IMG_DECLARE(icon_tsr);
LV_IMG_DECLARE(icon_tsr_off);
LV_IMG_DECLARE(icon_tsr_off_m);
LV_IMG_DECLARE(icon_tsr_on);
LV_IMG_DECLARE(icon_tsr_on_m);
LV_IMG_DECLARE(icon_tv_mode);
LV_IMG_DECLARE(icon_tv_mode_m);
LV_IMG_DECLARE(icon_tv_ntsc);
LV_IMG_DECLARE(icon_tv_pal);
LV_IMG_DECLARE(icon_urgent_protect_auto);
LV_IMG_DECLARE(icon_urgent_protect_auto_m);
LV_IMG_DECLARE(icon_urgent_protect_manual);
LV_IMG_DECLARE(icon_urgent_protect_manual_m);
LV_IMG_DECLARE(icon_usb);
LV_IMG_DECLARE(icon_usb_msdc);
LV_IMG_DECLARE(icon_usb_off);
LV_IMG_DECLARE(icon_usb_on);
LV_IMG_DECLARE(icon_usb_on_m);
LV_IMG_DECLARE(icon_usb_uvc);
LV_IMG_DECLARE(icon_u_stop_ori);
LV_IMG_DECLARE(icon_version);
LV_IMG_DECLARE(icon_version_m);
LV_IMG_DECLARE(icon_video_flip_off);
LV_IMG_DECLARE(icon_video_flip_on);
LV_IMG_DECLARE(icon_video_flip_on_m);
LV_IMG_DECLARE(icon_voice);
LV_IMG_DECLARE(icon_voice_m);
LV_IMG_DECLARE(icon_voice_off);
LV_IMG_DECLARE(icon_voice_on);
LV_IMG_DECLARE(icon_vol_0);
LV_IMG_DECLARE(icon_vol_1);
LV_IMG_DECLARE(icon_vol_2);
LV_IMG_DECLARE(icon_waring);
LV_IMG_DECLARE(icon_waring_big);
LV_IMG_DECLARE(icon_warn_movie_capture);
LV_IMG_DECLARE(icon_wb);
LV_IMG_DECLARE(icon_wb_auto);
LV_IMG_DECLARE(icon_wb_cloudy);
LV_IMG_DECLARE(icon_wb_daylight);
LV_IMG_DECLARE(icon_wb_fluorescent);
LV_IMG_DECLARE(icon_wb_m);
LV_IMG_DECLARE(icon_wb_tungsten);
LV_IMG_DECLARE(icon_wdr);
LV_IMG_DECLARE(icon_wifi);
LV_IMG_DECLARE(icon_wifi_android);
LV_IMG_DECLARE(icon_wifi_app_connected);
LV_IMG_DECLARE(icon_wifi_connect);
LV_IMG_DECLARE(icon_wifi_connected);
LV_IMG_DECLARE(icon_wifi_connected_small);
LV_IMG_DECLARE(icon_wifi_connecting1);
LV_IMG_DECLARE(icon_wifi_connecting2);
LV_IMG_DECLARE(icon_wifi_connecting3);
LV_IMG_DECLARE(icon_wifi_disconnected);
LV_IMG_DECLARE(icon_wifi_dot_connecting_off);
LV_IMG_DECLARE(icon_wifi_dot_connecting_on);
LV_IMG_DECLARE(icon_wifi_fail);
LV_IMG_DECLARE(icon_wifi_ios);
LV_IMG_DECLARE(icon_wifi_off);
LV_IMG_DECLARE(icon_wifi_off_m);
LV_IMG_DECLARE(icon_wifi_on);
LV_IMG_DECLARE(icon_wifi_on_m);
LV_IMG_DECLARE(icon_yes);
LV_IMG_DECLARE(icon_yes_m);
LV_IMG_DECLARE(icon__empty);
LV_IMG_DECLARE(icon_gps_err);
LV_IMG_DECLARE(icon_gps_ok);
LV_IMG_DECLARE(open_aukey);
LV_IMG_DECLARE(open_en);
LV_IMG_DECLARE(open_jp);
LV_IMG_DECLARE(open_papago);
LV_IMG_DECLARE(open_sc);
LV_IMG_DECLARE(open_tc);
LV_IMG_DECLARE(_100);
LV_IMG_DECLARE(_110);
LV_IMG_DECLARE(_120);
LV_IMG_DECLARE(_30);
LV_IMG_DECLARE(_40);
LV_IMG_DECLARE(_50);
LV_IMG_DECLARE(_60);
LV_IMG_DECLARE(_70);
LV_IMG_DECLARE(_80);
LV_IMG_DECLARE(_90);
LV_IMG_DECLARE(off_1);
LV_IMG_DECLARE(off_10);
LV_IMG_DECLARE(off_10_en);
LV_IMG_DECLARE(off_10_sc);
LV_IMG_DECLARE(off_1_en);
LV_IMG_DECLARE(off_1_sc);
LV_IMG_DECLARE(off_2);
LV_IMG_DECLARE(off_2_en);
LV_IMG_DECLARE(off_2_sc);
LV_IMG_DECLARE(off_3);
LV_IMG_DECLARE(off_3_en);
LV_IMG_DECLARE(off_3_sc);
LV_IMG_DECLARE(off_4);
LV_IMG_DECLARE(off_4_en);
LV_IMG_DECLARE(off_4_sc);
LV_IMG_DECLARE(off_5);
LV_IMG_DECLARE(off_5_en);
LV_IMG_DECLARE(off_5_sc);
LV_IMG_DECLARE(off_6);
LV_IMG_DECLARE(off_6_en);
LV_IMG_DECLARE(off_6_sc);
LV_IMG_DECLARE(off_7);
LV_IMG_DECLARE(off_7_en);
LV_IMG_DECLARE(off_7_sc);
LV_IMG_DECLARE(off_8);
LV_IMG_DECLARE(off_8_en);
LV_IMG_DECLARE(off_8_sc);
LV_IMG_DECLARE(off_9);
LV_IMG_DECLARE(off_9_en);
LV_IMG_DECLARE(off_9_sc);

#define LV_PLUGIN_IMG_ID_BYE_EN 1
#define LV_PLUGIN_IMG_ID_BYE_JP 2
#define LV_PLUGIN_IMG_ID_BYE_SC 3
#define LV_PLUGIN_IMG_ID_BYE_TC 4
#define LV_PLUGIN_IMG_ID_ICON_0B 5
#define LV_PLUGIN_IMG_ID_ICON_0R 6
#define LV_PLUGIN_IMG_ID_ICON_1B 7
#define LV_PLUGIN_IMG_ID_ICON_1R 8
#define LV_PLUGIN_IMG_ID_ICON_2B 9
#define LV_PLUGIN_IMG_ID_ICON_2R 10
#define LV_PLUGIN_IMG_ID_ICON_3B 11
#define LV_PLUGIN_IMG_ID_ICON_3R 12
#define LV_PLUGIN_IMG_ID_ICON_4B 13
#define LV_PLUGIN_IMG_ID_ICON_4R 14
#define LV_PLUGIN_IMG_ID_ICON_5B 15
#define LV_PLUGIN_IMG_ID_ICON_5R 16
#define LV_PLUGIN_IMG_ID_ICON_6B 17
#define LV_PLUGIN_IMG_ID_ICON_6R 18
#define LV_PLUGIN_IMG_ID_ICON_7B 19
#define LV_PLUGIN_IMG_ID_ICON_7R 20
#define LV_PLUGIN_IMG_ID_ICON_8B 21
#define LV_PLUGIN_IMG_ID_ICON_8R 22
#define LV_PLUGIN_IMG_ID_ICON_9B 23
#define LV_PLUGIN_IMG_ID_ICON_9R 24
#define LV_PLUGIN_IMG_ID_ICON_ACT_PUSH_BTN 25
#define LV_PLUGIN_IMG_ID_ICON_ACT_RELEASE_BTN 26
#define LV_PLUGIN_IMG_ID_ICON_ADAS_00 27
#define LV_PLUGIN_IMG_ID_ICON_ADAS_01 28
#define LV_PLUGIN_IMG_ID_ICON_ADAS_02 29
#define LV_PLUGIN_IMG_ID_ICON_ADAS_03 30
#define LV_PLUGIN_IMG_ID_ICON_ADAS_04 31
#define LV_PLUGIN_IMG_ID_ICON_ADAS_05 32
#define LV_PLUGIN_IMG_ID_ICON_ADAS_06 33
#define LV_PLUGIN_IMG_ID_ICON_ADAS_07 34
#define LV_PLUGIN_IMG_ID_ICON_ADAS_08 35
#define LV_PLUGIN_IMG_ID_ICON_ADAS_09 36
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_01 37
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_02 38
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_03 39
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_04 40
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_05 41
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_06 42
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_07 43
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_08 44
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_09 45
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_10 46
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_11 47
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_12 48
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_13 49
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_14 50
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ANIMATION_BG 51
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CAL 52
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CAL_M 53
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CAR_BLUE 54
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CAR_RED 55
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CAR_WHITE 56
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CHANGE_LANE_LEFT 57
#define LV_PLUGIN_IMG_ID_ICON_ADAS_CHANGE_LANE_RIGHT 58
#define LV_PLUGIN_IMG_ID_ICON_ADAS_DIS_ALERT 59
#define LV_PLUGIN_IMG_ID_ICON_ADAS_DIS_SEPERATE 60
#define LV_PLUGIN_IMG_ID_ICON_ADAS_FRONT_ALERT 61
#define LV_PLUGIN_IMG_ID_ICON_ADAS_FRONT_CAR_DIS_BG 62
#define LV_PLUGIN_IMG_ID_ICON_ADAS_FT 63
#define LV_PLUGIN_IMG_ID_ICON_ADAS_GO_ALERT 64
#define LV_PLUGIN_IMG_ID_ICON_ADAS_LANE_LEFT 65
#define LV_PLUGIN_IMG_ID_ICON_ADAS_LANE_RIGHT 66
#define LV_PLUGIN_IMG_ID_ICON_ADAS_OFF 67
#define LV_PLUGIN_IMG_ID_ICON_ADAS_OFF_M 68
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ON 69
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ON_M 70
#define LV_PLUGIN_IMG_ID_ICON_ADAS_PEOPLE_ALERT 71
#define LV_PLUGIN_IMG_ID_ICON_ADAS_REAR_ALERT 72
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD 73
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_01 74
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_02 75
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_03 76
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_04 77
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_05 78
#define LV_PLUGIN_IMG_ID_ICON_ADAS_ROAD_06 79
#define LV_PLUGIN_IMG_ID_ICON_ADAS_VIRTUAL_BUMPER 80
#define LV_PLUGIN_IMG_ID_ICON_ADAS_WARN_BG 81
#define LV_PLUGIN_IMG_ID_ICON_AP_MACHINE_OFF 82
#define LV_PLUGIN_IMG_ID_ICON_AP_MACHINE_ON 83
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN 84
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN_10MIN 85
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN_3MIN 86
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN_5MIN 87
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN_M 88
#define LV_PLUGIN_IMG_ID_ICON_AUTOSHUTDOWN_OFF 89
#define LV_PLUGIN_IMG_ID_ICON_AUTO_1FPS 90
#define LV_PLUGIN_IMG_ID_ICON_AUTO_1FPS1 91
#define LV_PLUGIN_IMG_ID_ICON_BACK 92
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT 93
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT_HIGH 94
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT_LOW 95
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT_M 96
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT_MID 97
#define LV_PLUGIN_IMG_ID_ICON_BACKLIGHT_OFF 98
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_CHARGE 99
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_EMPTY 100
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_FULL 101
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_LOW 102
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_MED 103
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_TYPE 104
#define LV_PLUGIN_IMG_ID_ICON_BATTERY_ZERO 105
#define LV_PLUGIN_IMG_ID_ICON_BSD_OFF 106
#define LV_PLUGIN_IMG_ID_ICON_BSD_OFF_M 107
#define LV_PLUGIN_IMG_ID_ICON_BSD_ON 108
#define LV_PLUGIN_IMG_ID_ICON_BSD_ON_M 109
#define LV_PLUGIN_IMG_ID_ICON_BTN_EMBOSS 110
#define LV_PLUGIN_IMG_ID_ICON_BUST 111
#define LV_PLUGIN_IMG_ID_ICON_BUST_3SHOT 112
#define LV_PLUGIN_IMG_ID_ICON_BUST_CONTINUE 113
#define LV_PLUGIN_IMG_ID_ICON_BUST_M 114
#define LV_PLUGIN_IMG_ID_ICON_BUST_OFF 115
#define LV_PLUGIN_IMG_ID_ICON_CAMERA_MODE 116
#define LV_PLUGIN_IMG_ID_ICON_CAM_PTZ_OFF 117
#define LV_PLUGIN_IMG_ID_ICON_CAM_PTZ_ON 118
#define LV_PLUGIN_IMG_ID_ICON_CAM_PTZ_ON_M 119
#define LV_PLUGIN_IMG_ID_ICON_CANCEL 120
#define LV_PLUGIN_IMG_ID_ICON_CANCEL_M 121
#define LV_PLUGIN_IMG_ID_ICON_CAR_CAMERA 122
#define LV_PLUGIN_IMG_ID_ICON_CAR_NO 123
#define LV_PLUGIN_IMG_ID_ICON_CLOSE 124
#define LV_PLUGIN_IMG_ID_ICON_CLOSE_WIFI 125
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_CONNECTED 126
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_CONNECTED_M 127
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_CONNECTING 128
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_CONNECTING_M 129
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_DOWNLOAD1 130
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_DOWNLOAD2 131
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_FAIL 132
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_OFF 133
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_OFF_M 134
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_ON 135
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_ON_M 136
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_UPLOAD1 137
#define LV_PLUGIN_IMG_ID_ICON_CLOUD_UPLOAD2 138
#define LV_PLUGIN_IMG_ID_ICON_CODEC_H265 139
#define LV_PLUGIN_IMG_ID_ICON_COLN 140
#define LV_PLUGIN_IMG_ID_ICON_COLOR 141
#define LV_PLUGIN_IMG_ID_ICON_COPY_FROM_CARD 142
#define LV_PLUGIN_IMG_ID_ICON_CORRECT 143
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC 144
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_10MIN 145
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_15MIN 146
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_1MIN 147
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_2MIN 148
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_3MIN 149
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_5MIN 150
#define LV_PLUGIN_IMG_ID_ICON_CYCLIC_REC_M 151
#define LV_PLUGIN_IMG_ID_ICON_DATETIME_SETUP 152
#define LV_PLUGIN_IMG_ID_ICON_DATETIME_SETUP_M 153
#define LV_PLUGIN_IMG_ID_ICON_DATE_PRINT 154
#define LV_PLUGIN_IMG_ID_ICON_DATE_PRINT_M 155
#define LV_PLUGIN_IMG_ID_ICON_DATE_STAMPING 156
#define LV_PLUGIN_IMG_ID_ICON_DATE_TIME 157
#define LV_PLUGIN_IMG_ID_ICON_DDD_OFF 158
#define LV_PLUGIN_IMG_ID_ICON_DDD_OFF_M 159
#define LV_PLUGIN_IMG_ID_ICON_DDD_ON 160
#define LV_PLUGIN_IMG_ID_ICON_DDD_ON_M 161
#define LV_PLUGIN_IMG_ID_ICON_DEFAULT 162
#define LV_PLUGIN_IMG_ID_ICON_DEFAULT_M 163
#define LV_PLUGIN_IMG_ID_ICON_DELETE 164
#define LV_PLUGIN_IMG_ID_ICON_DELETE_ALL 165
#define LV_PLUGIN_IMG_ID_ICON_DELETE_CURRENT 166
#define LV_PLUGIN_IMG_ID_ICON_DELETE_M 167
#define LV_PLUGIN_IMG_ID_ICON_DIR_D 168
#define LV_PLUGIN_IMG_ID_ICON_DIR_DOWN 169
#define LV_PLUGIN_IMG_ID_ICON_DIR_L 170
#define LV_PLUGIN_IMG_ID_ICON_DIR_LEFT 171
#define LV_PLUGIN_IMG_ID_ICON_DIR_R 172
#define LV_PLUGIN_IMG_ID_ICON_DIR_RIGHT 173
#define LV_PLUGIN_IMG_ID_ICON_DIR_U 174
#define LV_PLUGIN_IMG_ID_ICON_DIR_UP 175
#define LV_PLUGIN_IMG_ID_ICON_DPOF 176
#define LV_PLUGIN_IMG_ID_ICON_DUALCAM_BEHIND 177
#define LV_PLUGIN_IMG_ID_ICON_DUALCAM_BOTH 178
#define LV_PLUGIN_IMG_ID_ICON_DUALCAM_BOTH_M 179
#define LV_PLUGIN_IMG_ID_ICON_DUALCAM_FRONT 180
#define LV_PLUGIN_IMG_ID_ICON_EDOG_00KM 181
#define LV_PLUGIN_IMG_ID_ICON_EDOG_100KM 182
#define LV_PLUGIN_IMG_ID_ICON_EDOG_110KM 183
#define LV_PLUGIN_IMG_ID_ICON_EDOG_120KM 184
#define LV_PLUGIN_IMG_ID_ICON_EDOG_20KM 185
#define LV_PLUGIN_IMG_ID_ICON_EDOG_30KM 186
#define LV_PLUGIN_IMG_ID_ICON_EDOG_40KM 187
#define LV_PLUGIN_IMG_ID_ICON_EDOG_50KM 188
#define LV_PLUGIN_IMG_ID_ICON_EDOG_60KM 189
#define LV_PLUGIN_IMG_ID_ICON_EDOG_70KM 190
#define LV_PLUGIN_IMG_ID_ICON_EDOG_80KM 191
#define LV_PLUGIN_IMG_ID_ICON_EDOG_90KM 192
#define LV_PLUGIN_IMG_ID_ICON_EDOG_AVERAGE_SPEED 193
#define LV_PLUGIN_IMG_ID_ICON_EDOG_BG 194
#define LV_PLUGIN_IMG_ID_ICON_EDOG_CAPTUR 195
#define LV_PLUGIN_IMG_ID_ICON_EDOG_DIS 196
#define LV_PLUGIN_IMG_ID_ICON_EDOG_DISTANCE 197
#define LV_PLUGIN_IMG_ID_ICON_EDOG_KM 198
#define LV_PLUGIN_IMG_ID_ICON_EDOG_KMH_BIG 199
#define LV_PLUGIN_IMG_ID_ICON_EDOG_KMH_RED 200
#define LV_PLUGIN_IMG_ID_ICON_EDOG_KMH_SMALL 201
#define LV_PLUGIN_IMG_ID_ICON_EDOG_KM_SMALL 202
#define LV_PLUGIN_IMG_ID_ICON_EDOG_M 203
#define LV_PLUGIN_IMG_ID_ICON_EDOG_MIN_SMALL 204
#define LV_PLUGIN_IMG_ID_ICON_EDOG_M_SMALL 205
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_0 206
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_1 207
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_2 208
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_3 209
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_4 210
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_5 211
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_6 212
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_7 213
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_8 214
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_9 215
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_0 216
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_1 217
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_2 218
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_3 219
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_4 220
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_5 221
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_6 222
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_7 223
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_8 224
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_RED_SMALL_9 225
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_0 226
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_1 227
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_2 228
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_3 229
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_4 230
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_5 231
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_6 232
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_7 233
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_8 234
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_9 235
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_0 236
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_1 237
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_2 238
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_3 239
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_4 240
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_5 241
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_6 242
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_7 243
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_8 244
#define LV_PLUGIN_IMG_ID_ICON_EDOG_NUM_YELLOW_SMALL_9 245
#define LV_PLUGIN_IMG_ID_ICON_EDOG_REDGREEN 246
#define LV_PLUGIN_IMG_ID_ICON_EDOG_SEC_SMALL 247
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TIME 248
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_ACCIDENT 249
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_BUS 250
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_DAWANDAO 251
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_DOWN_HILL 252
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_ENTRY 253
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_EXIT 254
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_JIAOLIUDAO 255
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_MONITOR 256
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_NO_DRINKING 257
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_NO_LEFT_TURN 258
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_NO_PARKING 259
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_OIL_STATION 260
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_POLICE 261
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_SCHOOL 262
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_SERVICE_CENTER 263
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_STRAIGHT_LINE 264
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_TRAIN_WAY 265
#define LV_PLUGIN_IMG_ID_ICON_EDOG_TYPE_TUNNEL 266
#define LV_PLUGIN_IMG_ID_ICON_EDOG_WARN_BG 267
#define LV_PLUGIN_IMG_ID_ICON_EDOG_WARN_BG_SINGLE 268
#define LV_PLUGIN_IMG_ID_ICON_EV 269
#define LV_PLUGIN_IMG_ID_ICON_EV_M 270
#define LV_PLUGIN_IMG_ID_ICON_EV_M0P3 271
#define LV_PLUGIN_IMG_ID_ICON_EV_M0P6 272
#define LV_PLUGIN_IMG_ID_ICON_EV_M1P0 273
#define LV_PLUGIN_IMG_ID_ICON_EV_M1P3 274
#define LV_PLUGIN_IMG_ID_ICON_EV_M1P6 275
#define LV_PLUGIN_IMG_ID_ICON_EV_M2P0 276
#define LV_PLUGIN_IMG_ID_ICON_EV_P0P0 277
#define LV_PLUGIN_IMG_ID_ICON_EV_P0P3 278
#define LV_PLUGIN_IMG_ID_ICON_EV_P0P6 279
#define LV_PLUGIN_IMG_ID_ICON_EV_P1P0 280
#define LV_PLUGIN_IMG_ID_ICON_EV_P1P3 281
#define LV_PLUGIN_IMG_ID_ICON_EV_P1P6 282
#define LV_PLUGIN_IMG_ID_ICON_EV_P2P0 283
#define LV_PLUGIN_IMG_ID_ICON_FACE_OFF 284
#define LV_PLUGIN_IMG_ID_ICON_FACE_ON 285
#define LV_PLUGIN_IMG_ID_ICON_FACE_ON_M 286
#define LV_PLUGIN_IMG_ID_ICON_FATIGUE_DRIVING 287
#define LV_PLUGIN_IMG_ID_ICON_FATIGUE_DRIVING_ALERT 288
#define LV_PLUGIN_IMG_ID_ICON_FB_LEFT 289
#define LV_PLUGIN_IMG_ID_ICON_FB_LEFT_ORI 290
#define LV_PLUGIN_IMG_ID_ICON_FCW_FAR_ALERT 291
#define LV_PLUGIN_IMG_ID_ICON_FCW_NEAR_ALERT 292
#define LV_PLUGIN_IMG_ID_ICON_FCW_OFF 293
#define LV_PLUGIN_IMG_ID_ICON_FCW_OFF_M 294
#define LV_PLUGIN_IMG_ID_ICON_FCW_ON 295
#define LV_PLUGIN_IMG_ID_ICON_FCW_ON_M 296
#define LV_PLUGIN_IMG_ID_ICON_FF_RIGHT 297
#define LV_PLUGIN_IMG_ID_ICON_FF_RIGHT_ORI 298
#define LV_PLUGIN_IMG_ID_ICON_FILE_LOCK 299
#define LV_PLUGIN_IMG_ID_ICON_FILE_VIDEO 300
#define LV_PLUGIN_IMG_ID_ICON_FIRMWARE_UPDATE 301
#define LV_PLUGIN_IMG_ID_ICON_FIRMWARE_UPDATE_M 302
#define LV_PLUGIN_IMG_ID_ICON_FLASH_AUTO 303
#define LV_PLUGIN_IMG_ID_ICON_FLASH_OFF 304
#define LV_PLUGIN_IMG_ID_ICON_FLASH_ON 305
#define LV_PLUGIN_IMG_ID_ICON_FLASH_ON_M 306
#define LV_PLUGIN_IMG_ID_ICON_FLASH_REC 307
#define LV_PLUGIN_IMG_ID_ICON_FLASH_REC_M 308
#define LV_PLUGIN_IMG_ID_ICON_FLASH_RED_EYE 309
#define LV_PLUGIN_IMG_ID_ICON_FLICK_50HZ 310
#define LV_PLUGIN_IMG_ID_ICON_FLICK_60HZ 311
#define LV_PLUGIN_IMG_ID_ICON_FORMAT 312
#define LV_PLUGIN_IMG_ID_ICON_FORMAT_M 313
#define LV_PLUGIN_IMG_ID_ICON_GOLF_REC 314
#define LV_PLUGIN_IMG_ID_ICON_GOLF_REC_M 315
#define LV_PLUGIN_IMG_ID_ICON_GPS 316
#define LV_PLUGIN_IMG_ID_ICON_GPS_OFF 317
#define LV_PLUGIN_IMG_ID_ICON_GPS_ON 318
#define LV_PLUGIN_IMG_ID_ICON_GPS_ON_M 319
#define LV_PLUGIN_IMG_ID_ICON_GSENSOR 320
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR 321
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR_HIGH 322
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR_LOW 323
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR_M 324
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR_MID 325
#define LV_PLUGIN_IMG_ID_ICON_G_SENSOR_OFF 326
#define LV_PLUGIN_IMG_ID_ICON_HDR 327
#define LV_PLUGIN_IMG_ID_ICON_HDR_M 328
#define LV_PLUGIN_IMG_ID_ICON_HDR_OFF 329
#define LV_PLUGIN_IMG_ID_ICON_HELP 330
#define LV_PLUGIN_IMG_ID_ICON_HELP_M 331
#define LV_PLUGIN_IMG_ID_ICON_HINT_BAR 332
#define LV_PLUGIN_IMG_ID_ICON_HZ 333
#define LV_PLUGIN_IMG_ID_ICON_HZ_50 334
#define LV_PLUGIN_IMG_ID_ICON_HZ_60 335
#define LV_PLUGIN_IMG_ID_ICON_HZ_M 336
#define LV_PLUGIN_IMG_ID_ICON_INFO 337
#define LV_PLUGIN_IMG_ID_ICON_INFO_M 338
#define LV_PLUGIN_IMG_ID_ICON_INTERNAL_FLASH 339
#define LV_PLUGIN_IMG_ID_ICON_IRCUT_AUTO 340
#define LV_PLUGIN_IMG_ID_ICON_IRCUT_OFF 341
#define LV_PLUGIN_IMG_ID_ICON_IRCUT_ON_M 342
#define LV_PLUGIN_IMG_ID_ICON_ISO 343
#define LV_PLUGIN_IMG_ID_ICON_ISO_100 344
#define LV_PLUGIN_IMG_ID_ICON_ISO_1600 345
#define LV_PLUGIN_IMG_ID_ICON_ISO_200 346
#define LV_PLUGIN_IMG_ID_ICON_ISO_400 347
#define LV_PLUGIN_IMG_ID_ICON_ISO_800 348
#define LV_PLUGIN_IMG_ID_ICON_ISO_AUTO 349
#define LV_PLUGIN_IMG_ID_ICON_ISO_M 350
#define LV_PLUGIN_IMG_ID_ICON_LANDSCAPE 351
#define LV_PLUGIN_IMG_ID_ICON_LANGUAGE 352
#define LV_PLUGIN_IMG_ID_ICON_LANGUAGE_M 353
#define LV_PLUGIN_IMG_ID_ICON_LDWS_LEFT_ALERT 354
#define LV_PLUGIN_IMG_ID_ICON_LDWS_OFF 355
#define LV_PLUGIN_IMG_ID_ICON_LDWS_OFF_M 356
#define LV_PLUGIN_IMG_ID_ICON_LDWS_ON 357
#define LV_PLUGIN_IMG_ID_ICON_LDWS_ON_M 358
#define LV_PLUGIN_IMG_ID_ICON_LDWS_RIGHT_ALERT 359
#define LV_PLUGIN_IMG_ID_ICON_LED_DET 360
#define LV_PLUGIN_IMG_ID_ICON_LOCAL_STATION__OFF 361
#define LV_PLUGIN_IMG_ID_ICON_LOCAL_STATION__ON 362
#define LV_PLUGIN_IMG_ID_ICON_LOCK 363
#define LV_PLUGIN_IMG_ID_ICON_LOCK_ALL 364
#define LV_PLUGIN_IMG_ID_ICON_LOCK_ALL_M 365
#define LV_PLUGIN_IMG_ID_ICON_LOCK_CURRENT 366
#define LV_PLUGIN_IMG_ID_ICON_LOCK_CURRENT_M 367
#define LV_PLUGIN_IMG_ID_ICON_LOCK_M 368
#define LV_PLUGIN_IMG_ID_ICON_LOCK_UNLOCK 369
#define LV_PLUGIN_IMG_ID_ICON_LOCK_UNLOCK_M 370
#define LV_PLUGIN_IMG_ID_ICON_LOCK_UNLOKC_ALL 371
#define LV_PLUGIN_IMG_ID_ICON_LOCK_UNLOKC_ALL_M 372
#define LV_PLUGIN_IMG_ID_ICON_LPR_OFF 373
#define LV_PLUGIN_IMG_ID_ICON_LPR_OFF_M 374
#define LV_PLUGIN_IMG_ID_ICON_LPR_ON 375
#define LV_PLUGIN_IMG_ID_ICON_LPR_ON_M 376
#define LV_PLUGIN_IMG_ID_ICON_MENU_FLASH_REC 377
#define LV_PLUGIN_IMG_ID_ICON_MENU_HDR 378
#define LV_PLUGIN_IMG_ID_ICON_MENU_MODECHANG 379
#define LV_PLUGIN_IMG_ID_ICON_MENU_MODECHANG_M 380
#define LV_PLUGIN_IMG_ID_ICON_MENU_PLAYBACK_OFF 381
#define LV_PLUGIN_IMG_ID_ICON_MENU_PLAYBACK_ON 382
#define LV_PLUGIN_IMG_ID_ICON_MENU_PRINT_OFF 383
#define LV_PLUGIN_IMG_ID_ICON_MENU_RETURN 384
#define LV_PLUGIN_IMG_ID_ICON_MENU_RETURN_M 385
#define LV_PLUGIN_IMG_ID_ICON_MENU_SETUP_OFF 386
#define LV_PLUGIN_IMG_ID_ICON_MENU_SETUP_ON 387
#define LV_PLUGIN_IMG_ID_ICON_MENU_SETUP_ON_M 388
#define LV_PLUGIN_IMG_ID_ICON_MENU_STILL_OFF 389
#define LV_PLUGIN_IMG_ID_ICON_MENU_STILL_ON 390
#define LV_PLUGIN_IMG_ID_ICON_MENU_UNDERBAR 391
#define LV_PLUGIN_IMG_ID_ICON_MENU_VIDEO_OFF 392
#define LV_PLUGIN_IMG_ID_ICON_MENU_VIDEO_ON 393
#define LV_PLUGIN_IMG_ID_ICON_MENU_WDR 394
#define LV_PLUGIN_IMG_ID_ICON_MENU_WDR_M 395
#define LV_PLUGIN_IMG_ID_ICON_MENU_WDR_OFF 396
#define LV_PLUGIN_IMG_ID_ICON_METERING 397
#define LV_PLUGIN_IMG_ID_ICON_METERING_M 398
#define LV_PLUGIN_IMG_ID_ICON_MODE_CAPTURE 399
#define LV_PLUGIN_IMG_ID_ICON_MODE_CAPTURE_M 400
#define LV_PLUGIN_IMG_ID_ICON_MODE_PLAYBACK 401
#define LV_PLUGIN_IMG_ID_ICON_MODE_PLAYBACK_M 402
#define LV_PLUGIN_IMG_ID_ICON_MODE_VIDEO 403
#define LV_PLUGIN_IMG_ID_ICON_MODE_VIDEO_M 404
#define LV_PLUGIN_IMG_ID_ICON_MOTION_DET_OFF 405
#define LV_PLUGIN_IMG_ID_ICON_MOTION_DET_ON 406
#define LV_PLUGIN_IMG_ID_ICON_MOTION_DET_ON_M 407
#define LV_PLUGIN_IMG_ID_ICON_MOVIE_MENU_WARING 408
#define LV_PLUGIN_IMG_ID_ICON_NO 409
#define LV_PLUGIN_IMG_ID_ICON_NO_M 410
#define LV_PLUGIN_IMG_ID_ICON_OK 411
#define LV_PLUGIN_IMG_ID_ICON_OK2 412
#define LV_PLUGIN_IMG_ID_ICON_OK_M 413
#define LV_PLUGIN_IMG_ID_ICON_OK_M_2 414
#define LV_PLUGIN_IMG_ID_ICON_OK_PAUSE 415
#define LV_PLUGIN_IMG_ID_ICON_OK_PLAY 416
#define LV_PLUGIN_IMG_ID_ICON_OK_S 417
#define LV_PLUGIN_IMG_ID_ICON_PARKINGMODE_GSENSOR 418
#define LV_PLUGIN_IMG_ID_ICON_PARKINGMODE_LB 419
#define LV_PLUGIN_IMG_ID_ICON_PARKINGMODE_MD 420
#define LV_PLUGIN_IMG_ID_ICON_PARKINGMODE_TL 421
#define LV_PLUGIN_IMG_ID_ICON_PAUSE 422
#define LV_PLUGIN_IMG_ID_ICON_PD_OFF 423
#define LV_PLUGIN_IMG_ID_ICON_PD_OFF_M 424
#define LV_PLUGIN_IMG_ID_ICON_PD_ON 425
#define LV_PLUGIN_IMG_ID_ICON_PD_ON_M 426
#define LV_PLUGIN_IMG_ID_ICON_PICTBRIDGE_S 427
#define LV_PLUGIN_IMG_ID_ICON_PIM_OFF 428
#define LV_PLUGIN_IMG_ID_ICON_PIM_OFF_M 429
#define LV_PLUGIN_IMG_ID_ICON_PIM_ON 430
#define LV_PLUGIN_IMG_ID_ICON_PIM_ON_M 431
#define LV_PLUGIN_IMG_ID_ICON_PLAY 432
#define LV_PLUGIN_IMG_ID_ICON_PLAY_BACKWARD 433
#define LV_PLUGIN_IMG_ID_ICON_PLAY_FF_B 434
#define LV_PLUGIN_IMG_ID_ICON_PLAY_FF_F 435
#define LV_PLUGIN_IMG_ID_ICON_PLAY_FORWARD 436
#define LV_PLUGIN_IMG_ID_ICON_PLAY_PAUSE 437
#define LV_PLUGIN_IMG_ID_ICON_PLAY_PLAY 438
#define LV_PLUGIN_IMG_ID_ICON_PLAY_STEP 439
#define LV_PLUGIN_IMG_ID_ICON_PLAY_STOP 440
#define LV_PLUGIN_IMG_ID_ICON_POWER_OFF 441
#define LV_PLUGIN_IMG_ID_ICON_POWER_OFF_M 442
#define LV_PLUGIN_IMG_ID_ICON_PRINT 443
#define LV_PLUGIN_IMG_ID_ICON_PROTECT 444
#define LV_PLUGIN_IMG_ID_ICON_PROTECT_M 445
#define LV_PLUGIN_IMG_ID_ICON_QUALITY 446
#define LV_PLUGIN_IMG_ID_ICON_QUALITY_BASIC 447
#define LV_PLUGIN_IMG_ID_ICON_QUALITY_FINE 448
#define LV_PLUGIN_IMG_ID_ICON_QUALITY_M 449
#define LV_PLUGIN_IMG_ID_ICON_QUALITY_NORMAL 450
#define LV_PLUGIN_IMG_ID_ICON_QUICK_REVIEW 451
#define LV_PLUGIN_IMG_ID_ICON_QUICK_REVIEW_M 452
#define LV_PLUGIN_IMG_ID_ICON_REC_ELIPPSE 453
#define LV_PLUGIN_IMG_ID_ICON_REC_ELLIPSE 454
#define LV_PLUGIN_IMG_ID_ICON_REC_RECOVERY 455
#define LV_PLUGIN_IMG_ID_ICON_REC_TRANSPAENT 456
#define LV_PLUGIN_IMG_ID_ICON_REMIND_LIGHT 457
#define LV_PLUGIN_IMG_ID_ICON_REMIND_LIGHT_ALERT 458
#define LV_PLUGIN_IMG_ID_ICON_RESOLUTION 459
#define LV_PLUGIN_IMG_ID_ICON_RESOLUTION_M 460
#define LV_PLUGIN_IMG_ID_ICON_ROTATE 461
#define LV_PLUGIN_IMG_ID_ICON_RSC_OFF 462
#define LV_PLUGIN_IMG_ID_ICON_RSC_ON 463
#define LV_PLUGIN_IMG_ID_ICON_RSC_ON_M 464
#define LV_PLUGIN_IMG_ID_ICON_SCENE_MODE 465
#define LV_PLUGIN_IMG_ID_ICON_SCENE_MODE_AUTO 466
#define LV_PLUGIN_IMG_ID_ICON_SCENE_MODE_LANDSCPE 467
#define LV_PLUGIN_IMG_ID_ICON_SCENE_MODE_M 468
#define LV_PLUGIN_IMG_ID_ICON_SCENE_MODE_PORTRIAL 469
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER 470
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER_10MIN 471
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER_3MIN 472
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER_5MIN 473
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER_M 474
#define LV_PLUGIN_IMG_ID_ICON_SCREENSAVER_OFF 475
#define LV_PLUGIN_IMG_ID_ICON_SCREEN_SAVER 476
#define LV_PLUGIN_IMG_ID_ICON_SD_CARD 477
#define LV_PLUGIN_IMG_ID_ICON_SD_LOCK 478
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER 479
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER_10SEC 480
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER_2SEC 481
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER_5SEC 482
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER_M 483
#define LV_PLUGIN_IMG_ID_ICON_SELFTIMER_OFF 484
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR 485
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_BEGIN 486
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_CARNO 487
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_DATE 488
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_END 489
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_ITEM 490
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_MED 491
#define LV_PLUGIN_IMG_ID_ICON_SEL_BAR_YEAR 492
#define LV_PLUGIN_IMG_ID_ICON_SEL_FOCUS 493
#define LV_PLUGIN_IMG_ID_ICON_SEQUENCE_NO 494
#define LV_PLUGIN_IMG_ID_ICON_SET 495
#define LV_PLUGIN_IMG_ID_ICON_SET_LOCK 496
#define LV_PLUGIN_IMG_ID_ICON_SHAKE_OFF 497
#define LV_PLUGIN_IMG_ID_ICON_SHAKE_ON 498
#define LV_PLUGIN_IMG_ID_ICON_SHAKE_ON_M 499
#define LV_PLUGIN_IMG_ID_ICON_SHARPNESS 500
#define LV_PLUGIN_IMG_ID_ICON_SHARPNESS_HIGH 501
#define LV_PLUGIN_IMG_ID_ICON_SHARPNESS_LOW 502
#define LV_PLUGIN_IMG_ID_ICON_SHARPNESS_M 503
#define LV_PLUGIN_IMG_ID_ICON_SHARPNESS_MED 504
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_0STEP 505
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_0STEP_M 506
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_1STEP 507
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_1STEP_M 508
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_2STEP 509
#define LV_PLUGIN_IMG_ID_ICON_SIGNAL_2STEP_M 510
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW 511
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW_2SEC 512
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW_5SEC 513
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW_8SEC 514
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW_M 515
#define LV_PLUGIN_IMG_ID_ICON_SLIDESHOW_OFF 516
#define LV_PLUGIN_IMG_ID_ICON_SLIDE_SHOW 517
#define LV_PLUGIN_IMG_ID_ICON_SMILE 518
#define LV_PLUGIN_IMG_ID_ICON_SMILE_M 519
#define LV_PLUGIN_IMG_ID_ICON_SNG 520
#define LV_PLUGIN_IMG_ID_ICON_SNG_ALERT 521
#define LV_PLUGIN_IMG_ID_ICON_SNG_ALERT_ORI 522
#define LV_PLUGIN_IMG_ID_ICON_SNG_OFF 523
#define LV_PLUGIN_IMG_ID_ICON_SNG_OFF_M 524
#define LV_PLUGIN_IMG_ID_ICON_SNG_ON 525
#define LV_PLUGIN_IMG_ID_ICON_SNG_ON_M 526
#define LV_PLUGIN_IMG_ID_ICON_SOUND_REC_OFF 527
#define LV_PLUGIN_IMG_ID_ICON_SOUND_REC_ON 528
#define LV_PLUGIN_IMG_ID_ICON_SOUND_REC_ON_M 529
#define LV_PLUGIN_IMG_ID_ICON_SPEAKER 530
#define LV_PLUGIN_IMG_ID_ICON_SSID 531
#define LV_PLUGIN_IMG_ID_ICON_SYS_CAL 532
#define LV_PLUGIN_IMG_ID_ICON_SYS_CAL_M 533
#define LV_PLUGIN_IMG_ID_ICON_TIME_LAPSE_OFF 534
#define LV_PLUGIN_IMG_ID_ICON_TIME_LAPSE_ON 535
#define LV_PLUGIN_IMG_ID_ICON_TIME_LAPSE_ON_M 536
#define LV_PLUGIN_IMG_ID_ICON_TITLE_BAR 537
#define LV_PLUGIN_IMG_ID_ICON_TSR 538
#define LV_PLUGIN_IMG_ID_ICON_TSR_OFF 539
#define LV_PLUGIN_IMG_ID_ICON_TSR_OFF_M 540
#define LV_PLUGIN_IMG_ID_ICON_TSR_ON 541
#define LV_PLUGIN_IMG_ID_ICON_TSR_ON_M 542
#define LV_PLUGIN_IMG_ID_ICON_TV_MODE 543
#define LV_PLUGIN_IMG_ID_ICON_TV_MODE_M 544
#define LV_PLUGIN_IMG_ID_ICON_TV_NTSC 545
#define LV_PLUGIN_IMG_ID_ICON_TV_PAL 546
#define LV_PLUGIN_IMG_ID_ICON_URGENT_PROTECT_AUTO 547
#define LV_PLUGIN_IMG_ID_ICON_URGENT_PROTECT_AUTO_M 548
#define LV_PLUGIN_IMG_ID_ICON_URGENT_PROTECT_MANUAL 549
#define LV_PLUGIN_IMG_ID_ICON_URGENT_PROTECT_MANUAL_M 550
#define LV_PLUGIN_IMG_ID_ICON_USB 551
#define LV_PLUGIN_IMG_ID_ICON_USB_MSDC 552
#define LV_PLUGIN_IMG_ID_ICON_USB_OFF 553
#define LV_PLUGIN_IMG_ID_ICON_USB_ON 554
#define LV_PLUGIN_IMG_ID_ICON_USB_ON_M 555
#define LV_PLUGIN_IMG_ID_ICON_USB_UVC 556
#define LV_PLUGIN_IMG_ID_ICON_U_STOP_ORI 557
#define LV_PLUGIN_IMG_ID_ICON_VERSION 558
#define LV_PLUGIN_IMG_ID_ICON_VERSION_M 559
#define LV_PLUGIN_IMG_ID_ICON_VIDEO_FLIP_OFF 560
#define LV_PLUGIN_IMG_ID_ICON_VIDEO_FLIP_ON 561
#define LV_PLUGIN_IMG_ID_ICON_VIDEO_FLIP_ON_M 562
#define LV_PLUGIN_IMG_ID_ICON_VOICE 563
#define LV_PLUGIN_IMG_ID_ICON_VOICE_M 564
#define LV_PLUGIN_IMG_ID_ICON_VOICE_OFF 565
#define LV_PLUGIN_IMG_ID_ICON_VOICE_ON 566
#define LV_PLUGIN_IMG_ID_ICON_VOL_0 567
#define LV_PLUGIN_IMG_ID_ICON_VOL_1 568
#define LV_PLUGIN_IMG_ID_ICON_VOL_2 569
#define LV_PLUGIN_IMG_ID_ICON_WARING 570
#define LV_PLUGIN_IMG_ID_ICON_WARING_BIG 571
#define LV_PLUGIN_IMG_ID_ICON_WARN_MOVIE_CAPTURE 572
#define LV_PLUGIN_IMG_ID_ICON_WB 573
#define LV_PLUGIN_IMG_ID_ICON_WB_AUTO 574
#define LV_PLUGIN_IMG_ID_ICON_WB_CLOUDY 575
#define LV_PLUGIN_IMG_ID_ICON_WB_DAYLIGHT 576
#define LV_PLUGIN_IMG_ID_ICON_WB_FLUORESCENT 577
#define LV_PLUGIN_IMG_ID_ICON_WB_M 578
#define LV_PLUGIN_IMG_ID_ICON_WB_TUNGSTEN 579
#define LV_PLUGIN_IMG_ID_ICON_WDR 580
#define LV_PLUGIN_IMG_ID_ICON_WIFI 581
#define LV_PLUGIN_IMG_ID_ICON_WIFI_ANDROID 582
#define LV_PLUGIN_IMG_ID_ICON_WIFI_APP_CONNECTED 583
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECT 584
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTED 585
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTED_SMALL 586
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTING1 587
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTING2 588
#define LV_PLUGIN_IMG_ID_ICON_WIFI_CONNECTING3 589
#define LV_PLUGIN_IMG_ID_ICON_WIFI_DISCONNECTED 590
#define LV_PLUGIN_IMG_ID_ICON_WIFI_DOT_CONNECTING_OFF 591
#define LV_PLUGIN_IMG_ID_ICON_WIFI_DOT_CONNECTING_ON 592
#define LV_PLUGIN_IMG_ID_ICON_WIFI_FAIL 593
#define LV_PLUGIN_IMG_ID_ICON_WIFI_IOS 594
#define LV_PLUGIN_IMG_ID_ICON_WIFI_OFF 595
#define LV_PLUGIN_IMG_ID_ICON_WIFI_OFF_M 596
#define LV_PLUGIN_IMG_ID_ICON_WIFI_ON 597
#define LV_PLUGIN_IMG_ID_ICON_WIFI_ON_M 598
#define LV_PLUGIN_IMG_ID_ICON_YES 599
#define LV_PLUGIN_IMG_ID_ICON_YES_M 600
#define LV_PLUGIN_IMG_ID_ICON__EMPTY 601
#define LV_PLUGIN_IMG_ID_ICON_GPS_ERR 602
#define LV_PLUGIN_IMG_ID_ICON_GPS_OK 603
#define LV_PLUGIN_IMG_ID_OPEN_AUKEY 604
#define LV_PLUGIN_IMG_ID_OPEN_EN 605
#define LV_PLUGIN_IMG_ID_OPEN_JP 606
#define LV_PLUGIN_IMG_ID_OPEN_PAPAGO 607
#define LV_PLUGIN_IMG_ID_OPEN_SC 608
#define LV_PLUGIN_IMG_ID_OPEN_TC 609
#define LV_PLUGIN_IMG_ID__100 610
#define LV_PLUGIN_IMG_ID__110 611
#define LV_PLUGIN_IMG_ID__120 612
#define LV_PLUGIN_IMG_ID__30 613
#define LV_PLUGIN_IMG_ID__40 614
#define LV_PLUGIN_IMG_ID__50 615
#define LV_PLUGIN_IMG_ID__60 616
#define LV_PLUGIN_IMG_ID__70 617
#define LV_PLUGIN_IMG_ID__80 618
#define LV_PLUGIN_IMG_ID__90 619
#define LV_PLUGIN_IMG_ID_OFF_1 620
#define LV_PLUGIN_IMG_ID_OFF_10 621
#define LV_PLUGIN_IMG_ID_OFF_10_EN 622
#define LV_PLUGIN_IMG_ID_OFF_10_SC 623
#define LV_PLUGIN_IMG_ID_OFF_1_EN 624
#define LV_PLUGIN_IMG_ID_OFF_1_SC 625
#define LV_PLUGIN_IMG_ID_OFF_2 626
#define LV_PLUGIN_IMG_ID_OFF_2_EN 627
#define LV_PLUGIN_IMG_ID_OFF_2_SC 628
#define LV_PLUGIN_IMG_ID_OFF_3 629
#define LV_PLUGIN_IMG_ID_OFF_3_EN 630
#define LV_PLUGIN_IMG_ID_OFF_3_SC 631
#define LV_PLUGIN_IMG_ID_OFF_4 632
#define LV_PLUGIN_IMG_ID_OFF_4_EN 633
#define LV_PLUGIN_IMG_ID_OFF_4_SC 634
#define LV_PLUGIN_IMG_ID_OFF_5 635
#define LV_PLUGIN_IMG_ID_OFF_5_EN 636
#define LV_PLUGIN_IMG_ID_OFF_5_SC 637
#define LV_PLUGIN_IMG_ID_OFF_6 638
#define LV_PLUGIN_IMG_ID_OFF_6_EN 639
#define LV_PLUGIN_IMG_ID_OFF_6_SC 640
#define LV_PLUGIN_IMG_ID_OFF_7 641
#define LV_PLUGIN_IMG_ID_OFF_7_EN 642
#define LV_PLUGIN_IMG_ID_OFF_7_SC 643
#define LV_PLUGIN_IMG_ID_OFF_8 644
#define LV_PLUGIN_IMG_ID_OFF_8_EN 645
#define LV_PLUGIN_IMG_ID_OFF_8_SC 646
#define LV_PLUGIN_IMG_ID_OFF_9 647
#define LV_PLUGIN_IMG_ID_OFF_9_EN 648
#define LV_PLUGIN_IMG_ID_OFF_9_SC 649
#define LV_PLUGIN_IMG_TABLE_SIZE 650

#define LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16 1
#define LV_PLUGIN_FONT_ID_LV_FONT_DEJAVU_PERSIAN_HEBREW_16 2
#define LV_PLUGIN_FONT_ID_NOTOSANS_BLACK_32_1BPP 3
#define LV_PLUGIN_FONT_ID_NOTOSANS_BLACK_48_1BPP 4
#define LV_PLUGIN_FONT_ID_NOTOSANS_BLACK_64_1BPP 5
#define LV_PLUGIN_FONT_ID_NOTOSANS_BLACK_128_1BPP 6
#define LV_PLUGIN_FONT_TABLE_SIZE 7

#define LV_PLUGIN_STRING_ID_STRID_NULL_ 1
#define LV_PLUGIN_STRING_ID_STRID_MODE 2
#define LV_PLUGIN_STRING_ID_STRID_IMGSIZE 3
#define LV_PLUGIN_STRING_ID_STRID_RESOLUTION 4
#define LV_PLUGIN_STRING_ID_STRID_12M 5
#define LV_PLUGIN_STRING_ID_STRID_10M 6
#define LV_PLUGIN_STRING_ID_STRID_9M 7
#define LV_PLUGIN_STRING_ID_STRID_8M 8
#define LV_PLUGIN_STRING_ID_STRID_7M 9
#define LV_PLUGIN_STRING_ID_STRID_6M 10
#define LV_PLUGIN_STRING_ID_STRID_5M 11
#define LV_PLUGIN_STRING_ID_STRID_4M 12
#define LV_PLUGIN_STRING_ID_STRID_3M 13
#define LV_PLUGIN_STRING_ID_STRID_2MHD 14
#define LV_PLUGIN_STRING_ID_STRID_2M 15
#define LV_PLUGIN_STRING_ID_STRID_1M 16
#define LV_PLUGIN_STRING_ID_STRID_VGA 17
#define LV_PLUGIN_STRING_ID_STRID_QVGA 18
#define LV_PLUGIN_STRING_ID_STRID_D1 19
#define LV_PLUGIN_STRING_ID_STRID_720P 20
#define LV_PLUGIN_STRING_ID_STRID_1080P 21
#define LV_PLUGIN_STRING_ID_STRID_1080FHD 22
#define LV_PLUGIN_STRING_ID_STRID_12MWXH 23
#define LV_PLUGIN_STRING_ID_STRID_10MWXH 24
#define LV_PLUGIN_STRING_ID_STRID_9MWXH 25
#define LV_PLUGIN_STRING_ID_STRID_8MWXH 26
#define LV_PLUGIN_STRING_ID_STRID_7MWXH 27
#define LV_PLUGIN_STRING_ID_STRID_6MWXH 28
#define LV_PLUGIN_STRING_ID_STRID_5MWXH 29
#define LV_PLUGIN_STRING_ID_STRID_4MWXH 30
#define LV_PLUGIN_STRING_ID_STRID_3MWXH 31
#define LV_PLUGIN_STRING_ID_STRID_2MHDWXH 32
#define LV_PLUGIN_STRING_ID_STRID_2MWXH 33
#define LV_PLUGIN_STRING_ID_STRID_1MWXH 34
#define LV_PLUGIN_STRING_ID_STRID_WVGAWXH 35
#define LV_PLUGIN_STRING_ID_STRID_VGAWXH 36
#define LV_PLUGIN_STRING_ID_STRID_QVGAWXH 37
#define LV_PLUGIN_STRING_ID_STRID_D1WXH 38
#define LV_PLUGIN_STRING_ID_STRID_720PWXH 39
#define LV_PLUGIN_STRING_ID_STRID_1080PWXH 40
#define LV_PLUGIN_STRING_ID_STRID_1080FHDWXH 41
#define LV_PLUGIN_STRING_ID_STRID_720P60FPSWXH 42
#define LV_PLUGIN_STRING_ID_STRID_720P30FPSWXH 43
#define LV_PLUGIN_STRING_ID_STRID_VGA30FPSWXH 44
#define LV_PLUGIN_STRING_ID_STRID_VGA120FPSWXH 45
#define LV_PLUGIN_STRING_ID_STRID_COMPRESSION 46
#define LV_PLUGIN_STRING_ID_STRID_QUALITY 47
#define LV_PLUGIN_STRING_ID_STRID_SUPER 48
#define LV_PLUGIN_STRING_ID_STRID_FINE 49
#define LV_PLUGIN_STRING_ID_STRID_NORMAL 50
#define LV_PLUGIN_STRING_ID_STRID_ECONOMY 51
#define LV_PLUGIN_STRING_ID_STRID_WB 52
#define LV_PLUGIN_STRING_ID_STRID_AUTO 53
#define LV_PLUGIN_STRING_ID_STRID_WB_DAY 54
#define LV_PLUGIN_STRING_ID_STRID_WB_CLOUDY 55
#define LV_PLUGIN_STRING_ID_STRID_WB_TUNGSTEN 56
#define LV_PLUGIN_STRING_ID_STRID_WB_FLUORESCENT 57
#define LV_PLUGIN_STRING_ID_STRID_EXPOSURE 58
#define LV_PLUGIN_STRING_ID_STRID_EV 59
#define LV_PLUGIN_STRING_ID_STRID_ISO 60
#define LV_PLUGIN_STRING_ID_STRID_ISO50 61
#define LV_PLUGIN_STRING_ID_STRID_ISO100 62
#define LV_PLUGIN_STRING_ID_STRID_ISO200 63
#define LV_PLUGIN_STRING_ID_STRID_ISO400 64
#define LV_PLUGIN_STRING_ID_STRID_METERING 65
#define LV_PLUGIN_STRING_ID_STRID_METER_CENTER 66
#define LV_PLUGIN_STRING_ID_STRID_METER_SPOT 67
#define LV_PLUGIN_STRING_ID_STRID_METER_AVG 68
#define LV_PLUGIN_STRING_ID_STRID_CAP_MODE 69
#define LV_PLUGIN_STRING_ID_STRID_CAP_SINGLE 70
#define LV_PLUGIN_STRING_ID_STRID_CAP_BURST 71
#define LV_PLUGIN_STRING_ID_STRID_CAP_BURST_3 72
#define LV_PLUGIN_STRING_ID_STRID_CAP_AUTO 73
#define LV_PLUGIN_STRING_ID_STRID_CAP_TIMER2S 74
#define LV_PLUGIN_STRING_ID_STRID_CAP_TIMER5S 75
#define LV_PLUGIN_STRING_ID_STRID_CAP_TIMER10S 76
#define LV_PLUGIN_STRING_ID_STRID_CAP_TIMER20S 77
#define LV_PLUGIN_STRING_ID_STRID_FLASHMODE 78
#define LV_PLUGIN_STRING_ID_STRID_FLASHON 79
#define LV_PLUGIN_STRING_ID_STRID_FLASHOFF 80
#define LV_PLUGIN_STRING_ID_STRID_FLASHAUTO 81
#define LV_PLUGIN_STRING_ID_STRID_REDEYE 82
#define LV_PLUGIN_STRING_ID_STRID_AV 83
#define LV_PLUGIN_STRING_ID_STRID_TV 84
#define LV_PLUGIN_STRING_ID_STRID_AVTV 85
#define LV_PLUGIN_STRING_ID_STRID_AVSETTING 86
#define LV_PLUGIN_STRING_ID_STRID_TVSETTING 87
#define LV_PLUGIN_STRING_ID_STRID_AVTVSETTING 88
#define LV_PLUGIN_STRING_ID_STRID_SCENESETTING 89
#define LV_PLUGIN_STRING_ID_STRID_SCENE 90
#define LV_PLUGIN_STRING_ID_STRID_LANDSCAPE 91
#define LV_PLUGIN_STRING_ID_STRID_NIGHTSCENE 92
#define LV_PLUGIN_STRING_ID_STRID_SPORTS 93
#define LV_PLUGIN_STRING_ID_STRID_PORTRAIT 94
#define LV_PLUGIN_STRING_ID_STRID_FLOWER 95
#define LV_PLUGIN_STRING_ID_STRID_SMART 96
#define LV_PLUGIN_STRING_ID_STRID_BACKLIGHT 97
#define LV_PLUGIN_STRING_ID_STRID_COLOR 98
#define LV_PLUGIN_STRING_ID_STRID_COLOR_FULL 99
#define LV_PLUGIN_STRING_ID_STRID_COLOR_BW 100
#define LV_PLUGIN_STRING_ID_STRID_COLOR_SEPIA 101
#define LV_PLUGIN_STRING_ID_STRID_SHARPNESS 102
#define LV_PLUGIN_STRING_ID_STRID_STRONG 103
#define LV_PLUGIN_STRING_ID_STRID_SOFT 104
#define LV_PLUGIN_STRING_ID_STRID_LOW 105
#define LV_PLUGIN_STRING_ID_STRID_MED 106
#define LV_PLUGIN_STRING_ID_STRID_HIGH 107
#define LV_PLUGIN_STRING_ID_STRID_DATE_STAMP 108
#define LV_PLUGIN_STRING_ID_STRID_DATE_TIME 109
#define LV_PLUGIN_STRING_ID_STRID_DATE 110
#define LV_PLUGIN_STRING_ID_STRID_TIME 111
#define LV_PLUGIN_STRING_ID_STRID_Y_M_D 112
#define LV_PLUGIN_STRING_ID_STRID_D_M_Y 113
#define LV_PLUGIN_STRING_ID_STRID_M_D_Y 114
#define LV_PLUGIN_STRING_ID_STRID_ON 115
#define LV_PLUGIN_STRING_ID_STRID_OFF 116
#define LV_PLUGIN_STRING_ID_STRID_DZ 117
#define LV_PLUGIN_STRING_ID_STRID_QUICK_VIEW 118
#define LV_PLUGIN_STRING_ID_STRID_SATURATION 119
#define LV_PLUGIN_STRING_ID_STRID_MOVIE 120
#define LV_PLUGIN_STRING_ID_STRID_FRAMERATE 121
#define LV_PLUGIN_STRING_ID_STRID_30FPS 122
#define LV_PLUGIN_STRING_ID_STRID_15FPS 123
#define LV_PLUGIN_STRING_ID_STRID_10FPS 124
#define LV_PLUGIN_STRING_ID_STRID_1FPS 125
#define LV_PLUGIN_STRING_ID_STRID_VIDEO 126
#define LV_PLUGIN_STRING_ID_STRID_AUDIO 127
#define LV_PLUGIN_STRING_ID_STRID_SETUP 128
#define LV_PLUGIN_STRING_ID_STRID_FREQUENCY 129
#define LV_PLUGIN_STRING_ID_STRID_50HZ 130
#define LV_PLUGIN_STRING_ID_STRID_60HZ 131
#define LV_PLUGIN_STRING_ID_STRID_MEDIA 132
#define LV_PLUGIN_STRING_ID_STRID_STORAGE 133
#define LV_PLUGIN_STRING_ID_STRID_INT_FLASH 134
#define LV_PLUGIN_STRING_ID_STRID_EXT_CARD 135
#define LV_PLUGIN_STRING_ID_STRID_LOGO_DISPLAY 136
#define LV_PLUGIN_STRING_ID_STRID_OPENING 137
#define LV_PLUGIN_STRING_ID_STRID_FORMAT 138
#define LV_PLUGIN_STRING_ID_STRID_OK 139
#define LV_PLUGIN_STRING_ID_STRID_CANCEL 140
#define LV_PLUGIN_STRING_ID_STRID_BEEPER 141
#define LV_PLUGIN_STRING_ID_STRID_BEEP_LOUD 142
#define LV_PLUGIN_STRING_ID_STRID_BEEP_SOFT 143
#define LV_PLUGIN_STRING_ID_STRID_LANGUAGE 144
#define LV_PLUGIN_STRING_ID_STRID_LANG_EN 145
#define LV_PLUGIN_STRING_ID_STRID_LANG_FR 146
#define LV_PLUGIN_STRING_ID_STRID_LANG_ES 147
#define LV_PLUGIN_STRING_ID_STRID_LANG_DE 148
#define LV_PLUGIN_STRING_ID_STRID_LANG_IT 149
#define LV_PLUGIN_STRING_ID_STRID_LANG_TC 150
#define LV_PLUGIN_STRING_ID_STRID_LANG_SC 151
#define LV_PLUGIN_STRING_ID_STRID_LANG_JP 152
#define LV_PLUGIN_STRING_ID_STRID_LANG_PO 153
#define LV_PLUGIN_STRING_ID_STRID_LANG_RU 154
#define LV_PLUGIN_STRING_ID_STRID_USB 155
#define LV_PLUGIN_STRING_ID_STRID_PC_MODE 156
#define LV_PLUGIN_STRING_ID_STRID_MSDC 157
#define LV_PLUGIN_STRING_ID_STRID_PCC 158
#define LV_PLUGIN_STRING_ID_STRID_PICTBRIDGE 159
#define LV_PLUGIN_STRING_ID_STRID_USBCHARGE 160
#define LV_PLUGIN_STRING_ID_STRID_TV_MODE 161
#define LV_PLUGIN_STRING_ID_STRID_TV_NTSC 162
#define LV_PLUGIN_STRING_ID_STRID_TV_PAL 163
#define LV_PLUGIN_STRING_ID_STRID_BRIGHTNESS 164
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF 165
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_1MIN 166
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_2MIN 167
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_3MIN 168
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_5MIN 169
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_10MIN 170
#define LV_PLUGIN_STRING_ID_STRID_1MIN 171
#define LV_PLUGIN_STRING_ID_STRID_2MIN 172
#define LV_PLUGIN_STRING_ID_STRID_3MIN 173
#define LV_PLUGIN_STRING_ID_STRID_5MIN 174
#define LV_PLUGIN_STRING_ID_STRID_10MIN 175
#define LV_PLUGIN_STRING_ID_STRID_15MIN 176
#define LV_PLUGIN_STRING_ID_STRID_20MIN 177
#define LV_PLUGIN_STRING_ID_STRID_25MIN 178
#define LV_PLUGIN_STRING_ID_STRID_30MIN 179
#define LV_PLUGIN_STRING_ID_STRID_CYCLIC_REC 180
#define LV_PLUGIN_STRING_ID_STRID_FLASH_REC 181
#define LV_PLUGIN_STRING_ID_STRID_GOLF_REC 182
#define LV_PLUGIN_STRING_ID_STRID_NONE 183
#define LV_PLUGIN_STRING_ID_STRID_RESET_NUM 184
#define LV_PLUGIN_STRING_ID_STRID_DEFAULT_SETTING 185
#define LV_PLUGIN_STRING_ID_STRID_YES 186
#define LV_PLUGIN_STRING_ID_STRID_NO 187
#define LV_PLUGIN_STRING_ID_STRID_VERSION 188
#define LV_PLUGIN_STRING_ID_STRID_PLAYBACK 189
#define LV_PLUGIN_STRING_ID_STRID_THUMBNAIL 190
#define LV_PLUGIN_STRING_ID_STRID_SET_LOGO 191
#define LV_PLUGIN_STRING_ID_STRID_ROTATE 192
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_S 193
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_90 194
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_180 195
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_270 196
#define LV_PLUGIN_STRING_ID_STRID_CROP 197
#define LV_PLUGIN_STRING_ID_STRID_CROP_S 198
#define LV_PLUGIN_STRING_ID_STRID_SLIDE_SHOW 199
#define LV_PLUGIN_STRING_ID_STRID_2SEC 200
#define LV_PLUGIN_STRING_ID_STRID_3SEC 201
#define LV_PLUGIN_STRING_ID_STRID_5SEC 202
#define LV_PLUGIN_STRING_ID_STRID_8SEC 203
#define LV_PLUGIN_STRING_ID_STRID_10SEC 204
#define LV_PLUGIN_STRING_ID_STRID_PROTECT 205
#define LV_PLUGIN_STRING_ID_STRID_PROTECTONE 206
#define LV_PLUGIN_STRING_ID_STRID_PROTECTALL 207
#define LV_PLUGIN_STRING_ID_STRID_LOCK 208
#define LV_PLUGIN_STRING_ID_STRID_LOCKONE 209
#define LV_PLUGIN_STRING_ID_STRID_LOCKALL 210
#define LV_PLUGIN_STRING_ID_STRID_LOCKSELECTED 211
#define LV_PLUGIN_STRING_ID_STRID_UNLOCK 212
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKONE 213
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKALL 214
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKSELECTED 215
#define LV_PLUGIN_STRING_ID_STRID_DPOF 216
#define LV_PLUGIN_STRING_ID_STRID_ONEIMAGE 217
#define LV_PLUGIN_STRING_ID_STRID_ALL_IMAGES 218
#define LV_PLUGIN_STRING_ID_STRID_THIS_IMAGE 219
#define LV_PLUGIN_STRING_ID_STRID_THIS_VIDEO 220
#define LV_PLUGIN_STRING_ID_STRID_SELECT_IMAGES 221
#define LV_PLUGIN_STRING_ID_STRID_ALL_INDEX 222
#define LV_PLUGIN_STRING_ID_STRID_ALL 223
#define LV_PLUGIN_STRING_ID_STRID_RESETALL 224
#define LV_PLUGIN_STRING_ID_STRID_COPIES 225
#define LV_PLUGIN_STRING_ID_STRID_RETURN 226
#define LV_PLUGIN_STRING_ID_STRID_RESIZE 227
#define LV_PLUGIN_STRING_ID_STRID_QUALITYCHANGE 228
#define LV_PLUGIN_STRING_ID_STRID_COPY_TO_CARD 229
#define LV_PLUGIN_STRING_ID_STRID_COPY_FROM_CARD 230
#define LV_PLUGIN_STRING_ID_STRID_COPY 231
#define LV_PLUGIN_STRING_ID_STRID_TOSD 232
#define LV_PLUGIN_STRING_ID_STRID_TOINTERNAL 233
#define LV_PLUGIN_STRING_ID_STRID_DELETE 234
#define LV_PLUGIN_STRING_ID_STRID_DELETECURRENT 235
#define LV_PLUGIN_STRING_ID_STRID_DELETEALL 236
#define LV_PLUGIN_STRING_ID_STRID_DELETESELECTED 237
#define LV_PLUGIN_STRING_ID_STRID_DATAPROCESSED 238
#define LV_PLUGIN_STRING_ID_STRID_SELECT 239
#define LV_PLUGIN_STRING_ID_STRID_PAGE 240
#define LV_PLUGIN_STRING_ID_STRID_PRINTMODESEL 241
#define LV_PLUGIN_STRING_ID_STRID_SIZE 242
#define LV_PLUGIN_STRING_ID_STRID_STANDARD 243
#define LV_PLUGIN_STRING_ID_STRID_CONTINUE 244
#define LV_PLUGIN_STRING_ID_STRID_WITHOUT 245
#define LV_PLUGIN_STRING_ID_STRID_WITH 246
#define LV_PLUGIN_STRING_ID_STRID_NAME 247
#define LV_PLUGIN_STRING_ID_STRID_NO_IMAGE 248
#define LV_PLUGIN_STRING_ID_STRID_SET 249
#define LV_PLUGIN_STRING_ID_STRID_MEMORY_FULL 250
#define LV_PLUGIN_STRING_ID_STRID_CARD_FULL 251
#define LV_PLUGIN_STRING_ID_STRID_FOLDERFULL 252
#define LV_PLUGIN_STRING_ID_STRID_CARDERROR 253
#define LV_PLUGIN_STRING_ID_STRID_MEMORYERROR 254
#define LV_PLUGIN_STRING_ID_STRID_LENSERROR 255
#define LV_PLUGIN_STRING_ID_STRID_CARD_LOCKED 256
#define LV_PLUGIN_STRING_ID_STRID_FILE_PROTECT 257
#define LV_PLUGIN_STRING_ID_STRID_PICTUREERROR 258
#define LV_PLUGIN_STRING_ID_STRID_BATTERY_LOW 259
#define LV_PLUGIN_STRING_ID_STRID_ONEMOMENT 260
#define LV_PLUGIN_STRING_ID_STRID_NOCONNECTION 261
#define LV_PLUGIN_STRING_ID_STRID_TRANSFERRING 262
#define LV_PLUGIN_STRING_ID_STRID_CONNECTEDTOPC 263
#define LV_PLUGIN_STRING_ID_STRID_REMOVEUSBCABLE 264
#define LV_PLUGIN_STRING_ID_STRID_TOTAL 265
#define LV_PLUGIN_STRING_ID_STRID_DATE_STAMPING 266
#define LV_PLUGIN_STRING_ID_STRID_FILE_NAME 267
#define LV_PLUGIN_STRING_ID_STRID_NO_OF_COPY 268
#define LV_PLUGIN_STRING_ID_STRID_DEFAULT 269
#define LV_PLUGIN_STRING_ID_STRID_MENU 270
#define LV_PLUGIN_STRING_ID_STRID_EXIT 271
#define LV_PLUGIN_STRING_ID_STRID_PLEASE_WAIT 272
#define LV_PLUGIN_STRING_ID_STRID_STARTSHUTTER 273
#define LV_PLUGIN_STRING_ID_STRID_STOPSHUTTER 274
#define LV_PLUGIN_STRING_ID_STRID_NO_FILE 275
#define LV_PLUGIN_STRING_ID_STRID_NO_CARD 276
#define LV_PLUGIN_STRING_ID_STRID_NO_PHOTO 277
#define LV_PLUGIN_STRING_ID_STRID_NOT_JPEG 278
#define LV_PLUGIN_STRING_ID_STRID_FLASHNOTREADY 279
#define LV_PLUGIN_STRING_ID_STRID_UPDATEBG 280
#define LV_PLUGIN_STRING_ID_STRID_CHECKVERSION 281
#define LV_PLUGIN_STRING_ID_STRID_PSTOREERR 282
#define LV_PLUGIN_STRING_ID_STRID_PLAY 283
#define LV_PLUGIN_STRING_ID_STRID_PAUSE 284
#define LV_PLUGIN_STRING_ID_STRID_STOP 285
#define LV_PLUGIN_STRING_ID_STRID_MOVE 286
#define LV_PLUGIN_STRING_ID_STRID_SAVE 287
#define LV_PLUGIN_STRING_ID_STRID_NEXT 288
#define LV_PLUGIN_STRING_ID_STRID_CHANGE 289
#define LV_PLUGIN_STRING_ID_STRID_VOLUME 290
#define LV_PLUGIN_STRING_ID_STRID_STILL 291
#define LV_PLUGIN_STRING_ID_STRID_BATTERY_TYPE 292
#define LV_PLUGIN_STRING_ID_STRID_ALKALINE 293
#define LV_PLUGIN_STRING_ID_STRID_NIMH 294
#define LV_PLUGIN_STRING_ID_STRID_DELETE_WARNING 295
#define LV_PLUGIN_STRING_ID_STRID_SEQUENCE_NO 296
#define LV_PLUGIN_STRING_ID_STRID_RESET_WARNING 297
#define LV_PLUGIN_STRING_ID_STRID_ERASE_THIS 298
#define LV_PLUGIN_STRING_ID_STRID_ERASE_ALL 299
#define LV_PLUGIN_STRING_ID_STRID_IMAGES 300
#define LV_PLUGIN_STRING_ID_STRID_CONNECT_TO_DEVICE 301
#define LV_PLUGIN_STRING_ID_STRID_DEVICE_IS_CONNECTED 302
#define LV_PLUGIN_STRING_ID_STRID_LINK_ERROR 303
#define LV_PLUGIN_STRING_ID_STRID_USB_ERROR 304
#define LV_PLUGIN_STRING_ID_STRID_DUMMY 305
#define LV_PLUGIN_STRING_ID_STRID_EV_M0P3 306
#define LV_PLUGIN_STRING_ID_STRID_EV_M0P6 307
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P0 308
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P3 309
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P6 310
#define LV_PLUGIN_STRING_ID_STRID_EV_M2P0 311
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P0 312
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P3 313
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P6 314
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P0 315
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P3 316
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P6 317
#define LV_PLUGIN_STRING_ID_STRID_EV_P2P0 318
#define LV_PLUGIN_STRING_ID_STRID_PRINT_ALL 319
#define LV_PLUGIN_STRING_ID_STRID_PRINT_INDEX 320
#define LV_PLUGIN_STRING_ID_STRID_PRINT_DPOF 321
#define LV_PLUGIN_STRING_ID_STRID_PRINT_SETTING 322
#define LV_PLUGIN_STRING_ID_STRID_DPOF_RESTART 323
#define LV_PLUGIN_STRING_ID_STRID_PRINT 324
#define LV_PLUGIN_STRING_ID_STRID_START_PRINTING 325
#define LV_PLUGIN_STRING_ID_STRID_PRINTING 326
#define LV_PLUGIN_STRING_ID_STRID_PRINT_CANCELED 327
#define LV_PLUGIN_STRING_ID_STRID_PRINT_FINISHED 328
#define LV_PLUGIN_STRING_ID_STRID_OK_TO_PRINT 329
#define LV_PLUGIN_STRING_ID_STRID_PAPER_SIZE 330
#define LV_PLUGIN_STRING_ID_STRID_L 331
#define LV_PLUGIN_STRING_ID_STRID_2L 332
#define LV_PLUGIN_STRING_ID_STRID_POSTCARD 333
#define LV_PLUGIN_STRING_ID_STRID_CARD 334
#define LV_PLUGIN_STRING_ID_STRID_100X150 335
#define LV_PLUGIN_STRING_ID_STRID_4X6 336
#define LV_PLUGIN_STRING_ID_STRID_8X10 337
#define LV_PLUGIN_STRING_ID_STRID_LETTER 338
#define LV_PLUGIN_STRING_ID_STRID_11X17 339
#define LV_PLUGIN_STRING_ID_STRID_A0 340
#define LV_PLUGIN_STRING_ID_STRID_A1 341
#define LV_PLUGIN_STRING_ID_STRID_A2 342
#define LV_PLUGIN_STRING_ID_STRID_A3 343
#define LV_PLUGIN_STRING_ID_STRID_A4 344
#define LV_PLUGIN_STRING_ID_STRID_A5 345
#define LV_PLUGIN_STRING_ID_STRID_A6 346
#define LV_PLUGIN_STRING_ID_STRID_A7 347
#define LV_PLUGIN_STRING_ID_STRID_A8 348
#define LV_PLUGIN_STRING_ID_STRID_A9 349
#define LV_PLUGIN_STRING_ID_STRID_B0 350
#define LV_PLUGIN_STRING_ID_STRID_B1 351
#define LV_PLUGIN_STRING_ID_STRID_B2 352
#define LV_PLUGIN_STRING_ID_STRID_B3 353
#define LV_PLUGIN_STRING_ID_STRID_B4 354
#define LV_PLUGIN_STRING_ID_STRID_B5 355
#define LV_PLUGIN_STRING_ID_STRID_B6 356
#define LV_PLUGIN_STRING_ID_STRID_B7 357
#define LV_PLUGIN_STRING_ID_STRID_B8 358
#define LV_PLUGIN_STRING_ID_STRID_B9 359
#define LV_PLUGIN_STRING_ID_STRID_L_ROLLS 360
#define LV_PLUGIN_STRING_ID_STRID_2L_ROLLS 361
#define LV_PLUGIN_STRING_ID_STRID_4_ROLLS 362
#define LV_PLUGIN_STRING_ID_STRID_A4_ROLLS 363
#define LV_PLUGIN_STRING_ID_STRID_PAPER_TYPE 364
#define LV_PLUGIN_STRING_ID_STRID_PHOTO_PAPER 365
#define LV_PLUGIN_STRING_ID_STRID_PLAIN_PAPER 366
#define LV_PLUGIN_STRING_ID_STRID_FAST_PHOTO 367
#define LV_PLUGIN_STRING_ID_STRID_FILE_TYPE 368
#define LV_PLUGIN_STRING_ID_STRID_EXIF_JPEG 369
#define LV_PLUGIN_STRING_ID_STRID_EXIF 370
#define LV_PLUGIN_STRING_ID_STRID_JPEG 371
#define LV_PLUGIN_STRING_ID_STRID_DATE_PRINT 372
#define LV_PLUGIN_STRING_ID_STRID_FILENAME_PRINT 373
#define LV_PLUGIN_STRING_ID_STRID_IMAGE_OPTIMIZE 374
#define LV_PLUGIN_STRING_ID_STRID_LAYOUT 375
#define LV_PLUGIN_STRING_ID_STRID_1UP 376
#define LV_PLUGIN_STRING_ID_STRID_2UP 377
#define LV_PLUGIN_STRING_ID_STRID_3UP 378
#define LV_PLUGIN_STRING_ID_STRID_4UP 379
#define LV_PLUGIN_STRING_ID_STRID_5UP 380
#define LV_PLUGIN_STRING_ID_STRID_6UP 381
#define LV_PLUGIN_STRING_ID_STRID_7UP 382
#define LV_PLUGIN_STRING_ID_STRID_8UP 383
#define LV_PLUGIN_STRING_ID_STRID_9UP 384
#define LV_PLUGIN_STRING_ID_STRID_10UP 385
#define LV_PLUGIN_STRING_ID_STRID_250UP 386
#define LV_PLUGIN_STRING_ID_STRID_INDEX 387
#define LV_PLUGIN_STRING_ID_STRID_1UP_BORDERLESS 388
#define LV_PLUGIN_STRING_ID_STRID_FIXED_SIZE 389
#define LV_PLUGIN_STRING_ID_STRID_25X325 390
#define LV_PLUGIN_STRING_ID_STRID_35X5 391
#define LV_PLUGIN_STRING_ID_STRID_254X178 392
#define LV_PLUGIN_STRING_ID_STRID_110X74 393
#define LV_PLUGIN_STRING_ID_STRID_89X55 394
#define LV_PLUGIN_STRING_ID_STRID_6X8 395
#define LV_PLUGIN_STRING_ID_STRID_7X10 396
#define LV_PLUGIN_STRING_ID_STRID_9X13 397
#define LV_PLUGIN_STRING_ID_STRID_13X18 398
#define LV_PLUGIN_STRING_ID_STRID_15X21 399
#define LV_PLUGIN_STRING_ID_STRID_18X24 400
#define LV_PLUGIN_STRING_ID_STRID_CROPPING 401
#define LV_PLUGIN_STRING_ID_STRID_PRINT_ERROR 402
#define LV_PLUGIN_STRING_ID_STRID_PRINTER_DISCONNECTABLE 403
#define LV_PLUGIN_STRING_ID_STRID_PAPER_ERROR 404
#define LV_PLUGIN_STRING_ID_STRID_PAPER_OUT 405
#define LV_PLUGIN_STRING_ID_STRID_PAPER_LOAD_ERROR 406
#define LV_PLUGIN_STRING_ID_STRID_PAPER_EJECT_ERROR 407
#define LV_PLUGIN_STRING_ID_STRID_PAPER_MEDIA_ERROR 408
#define LV_PLUGIN_STRING_ID_STRID_PAPER_JAMMED 409
#define LV_PLUGIN_STRING_ID_STRID_PAPER_NEAR_EMPTY 410
#define LV_PLUGIN_STRING_ID_STRID_PAPER_NOT_SUPPORT 411
#define LV_PLUGIN_STRING_ID_STRID_INK_ERROR 412
#define LV_PLUGIN_STRING_ID_STRID_INK_EMPTY 413
#define LV_PLUGIN_STRING_ID_STRID_INK_LOW 414
#define LV_PLUGIN_STRING_ID_STRID_INK_WASTE 415
#define LV_PLUGIN_STRING_ID_STRID_HW_ERROR 416
#define LV_PLUGIN_STRING_ID_STRID_HW_FATAL 417
#define LV_PLUGIN_STRING_ID_STRID_HW_SERVICE_CALL 418
#define LV_PLUGIN_STRING_ID_STRID_HW_UNAVAILABLE 419
#define LV_PLUGIN_STRING_ID_STRID_HW_BUSY 420
#define LV_PLUGIN_STRING_ID_STRID_HW_LEVER 421
#define LV_PLUGIN_STRING_ID_STRID_HW_COVER_OPEN 422
#define LV_PLUGIN_STRING_ID_STRID_HW_NO_MARKING_AGENT 423
#define LV_PLUGIN_STRING_ID_STRID_HW_INK_COVER_OPEN 424
#define LV_PLUGIN_STRING_ID_STRID_HW_NO_INK_CARTRIDGE 425
#define LV_PLUGIN_STRING_ID_STRID_FILE_ERROR 426
#define LV_PLUGIN_STRING_ID_STRID_FILE_PRINT_INFO 427
#define LV_PLUGIN_STRING_ID_STRID_FILE_DECODE_ERROR 428
#define LV_PLUGIN_STRING_ID_STRID_UNKNOW_ERROR 429
#define LV_PLUGIN_STRING_ID_STRID_XML_SYNTAX_ERROR 430
#define LV_PLUGIN_STRING_ID_STRID_MOTION_DET 431
#define LV_PLUGIN_STRING_ID_STRID_FACE_DET 432
#define LV_PLUGIN_STRING_ID_STRID_SMILE_DET 433
#define LV_PLUGIN_STRING_ID_STRID_ANTI_SHAKING 434
#define LV_PLUGIN_STRING_ID_STRID_NO_MOVIE 435
#define LV_PLUGIN_STRING_ID_STRID_MP3PLAY 436
#define LV_PLUGIN_STRING_ID_STRID_NO_MP3FILE 437
#define LV_PLUGIN_STRING_ID_STRID_SENSOR_ROTATE 438
#define LV_PLUGIN_STRING_ID_STRID_RECORD 439
#define LV_PLUGIN_STRING_ID_STRID_RECORD_AUDIO 440
#define LV_PLUGIN_STRING_ID_STRID_LED_SETTING 441
#define LV_PLUGIN_STRING_ID_STRID_GOOD_BYE 442
#define LV_PLUGIN_STRING_ID_STRID_PLEASE_INSERT_SD 443
#define LV_PLUGIN_STRING_ID_STRID_IR_LED 444
#define LV_PLUGIN_STRING_ID_STRID_MICROPHONE 445
#define LV_PLUGIN_STRING_ID_STRID_CLUSTER_WRONG 446
#define LV_PLUGIN_STRING_ID_STRID_SD_CLASS10 447
#define LV_PLUGIN_STRING_ID_STRID_SD_CLASS6 448
#define LV_PLUGIN_STRING_ID_STRID_SD_CLASS4 449
#define LV_PLUGIN_STRING_ID_STRID_HDR 450
#define LV_PLUGIN_STRING_ID_STRID_GPS 451
#define LV_PLUGIN_STRING_ID_STRID_GSENSOR 452
#define LV_PLUGIN_STRING_ID_STRID_SCREEN_SAVER 453
#define LV_PLUGIN_STRING_ID_STRID_LOW_SENSITIVITY 454
#define LV_PLUGIN_STRING_ID_STRID_MIDDLE_SENSITIVITY 455
#define LV_PLUGIN_STRING_ID_STRID_HIGH_SENSITIVITY 456
#define LV_PLUGIN_STRING_ID_STRID_CARNO 457
#define LV_PLUGIN_STRING_ID_STRID_CAMERA_MODE 458
#define LV_PLUGIN_STRING_ID_STRID_COLOCK_1MIN 459
#define LV_PLUGIN_STRING_ID_STRID_COLOCK_3MIN 460
#define LV_PLUGIN_STRING_ID_STRID_LCD_BACKLIGHT_OFF 461
#define LV_PLUGIN_STRING_ID_STRID_UNDERLINE 462
#define LV_PLUGIN_STRING_ID_STRID_TIMER_LAPSE 463
#define LV_PLUGIN_STRING_ID_STRID_1_HOUR 464
#define LV_PLUGIN_STRING_ID_STRID_2_HOUR 465
#define LV_PLUGIN_STRING_ID_STRID_3_HOUR 466
#define LV_PLUGIN_STRING_ID_STRID_CAMERA_MODE_OFF 467
#define LV_PLUGIN_STRING_ID_STRID_NOT_USED_CAMERA_MODE 468
#define LV_PLUGIN_STRING_ID_STRID_CHANGE_TO_NORMAL_MODE 469
#define LV_PLUGIN_STRING_ID_STRID_NOT_USED_CAMERA_MODE_IN_MOTIONDET 470
#define LV_PLUGIN_STRING_ID_STRID_PLEASE_RESETING_DATE 471
#define LV_PLUGIN_STRING_ID_STRID_GSENSOR_ADJUST 472
#define LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING 473
#define LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_15_DAY 474
#define LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_30_DAY 475
#define LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_60_DAY 476
#define LV_PLUGIN_STRING_ID_STRID_PLAY_FILE 477
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FLIE 478
#define LV_PLUGIN_STRING_ID_STRID_PHOTO_FILE 479
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FILE_LIST 480
#define LV_PLUGIN_STRING_ID_STRID_PHOTO_FILE_LIST 481
#define LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING1 482
#define LV_PLUGIN_STRING_ID_STRID_MOVIEWND_PLAYBACK 483
#define LV_PLUGIN_STRING_ID_STRID_MOVIEWND_SETTING 484
#define LV_PLUGIN_STRING_ID_STRID_MOVIEWND_CLOSELCD 485
#define LV_PLUGIN_STRING_ID_STRID_MOVIEWND_OK 486
#define LV_PLUGIN_STRING_ID_STRID_PLAYBACK_PLAY_LIST 487
#define LV_PLUGIN_STRING_ID_STRID_LOGOL_OPEN 488
#define LV_PLUGIN_STRING_ID_STRID_LOGOL_BYE 489
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_10S 490
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_9S 491
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_8S 492
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_7S 493
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_6S 494
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_5S 495
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_4S 496
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_3S 497
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_2S 498
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_1S 499
#define LV_PLUGIN_STRING_ID_STRID_POWER_OFF_0S 500
#define LV_PLUGIN_STRING_ID_STRID_PARKINGGUARD 501
#define LV_PLUGIN_STRING_ID_STRID_TIME_ZONE 502
#define LV_PLUGIN_STRING_ID_STRID_GMT_N12 503
#define LV_PLUGIN_STRING_ID_STRID_GMT_N11 504
#define LV_PLUGIN_STRING_ID_STRID_GMT_N10 505
#define LV_PLUGIN_STRING_ID_STRID_GMT_N9 506
#define LV_PLUGIN_STRING_ID_STRID_GMT_N8 507
#define LV_PLUGIN_STRING_ID_STRID_GMT_N7 508
#define LV_PLUGIN_STRING_ID_STRID_GMT_N6 509
#define LV_PLUGIN_STRING_ID_STRID_GMT_N5 510
#define LV_PLUGIN_STRING_ID_STRID_GMT_N4 511
#define LV_PLUGIN_STRING_ID_STRID_GMT_N3 512
#define LV_PLUGIN_STRING_ID_STRID_GMT_N2 513
#define LV_PLUGIN_STRING_ID_STRID_GMT_N1 514
#define LV_PLUGIN_STRING_ID_STRID_GMT_N0 515
#define LV_PLUGIN_STRING_ID_STRID_GMT_P1 516
#define LV_PLUGIN_STRING_ID_STRID_GMT_P2 517
#define LV_PLUGIN_STRING_ID_STRID_GMT_P3 518
#define LV_PLUGIN_STRING_ID_STRID_GMT_P4 519
#define LV_PLUGIN_STRING_ID_STRID_GMT_P5 520
#define LV_PLUGIN_STRING_ID_STRID_GMT_P6 521
#define LV_PLUGIN_STRING_ID_STRID_GMT_P7 522
#define LV_PLUGIN_STRING_ID_STRID_GMT_P8 523
#define LV_PLUGIN_STRING_ID_STRID_GMT_P9 524
#define LV_PLUGIN_STRING_ID_STRID_GMT_P10 525
#define LV_PLUGIN_STRING_ID_STRID_GMT_P11 526
#define LV_PLUGIN_STRING_ID_STRID_GMT_P12 527
#define LV_PLUGIN_STRING_ID_STRID_GMT_P13 528
#define LV_PLUGIN_STRING_ID_STRID_GMT_N330 529
#define LV_PLUGIN_STRING_ID_STRID_GMT_P330 530
#define LV_PLUGIN_STRING_ID_STRID_GMT_P430 531
#define LV_PLUGIN_STRING_ID_STRID_GMT_P530 532
#define LV_PLUGIN_STRING_ID_STRID_GMT_P930 533
#define LV_PLUGIN_STRING_ID_STRID_GMT_P1030 534
#define LV_PLUGIN_STRING_ID_STRID_CAR_SAFE 535
#define LV_PLUGIN_STRING_ID_STRID_TSR 536
#define LV_PLUGIN_STRING_ID_STRID_REC 537
#define LV_PLUGIN_STRING_ID_STRID_SNG 538
#define LV_PLUGIN_STRING_ID_STRID_FATIGUE_DRIVING 539
#define LV_PLUGIN_STRING_ID_STRID_REMIND_LIGHT 540
#define LV_PLUGIN_STRING_ID_STRID_FATIGUE_30MIN 541
#define LV_PLUGIN_STRING_ID_STRID_FATIGUE_1HOUR 542
#define LV_PLUGIN_STRING_ID_STRID_FATIGUE_2HOUR 543
#define LV_PLUGIN_STRING_ID_STRID_FATIGUE_4HOUR 544
#define LV_PLUGIN_STRING_ID_STRID_SPEED_UNIT 545
#define LV_PLUGIN_STRING_ID_STRID_SPEED_MPH 546
#define LV_PLUGIN_STRING_ID_STRID_SPEED_KPH 547
#define LV_PLUGIN_STRING_ID_STRID_C0 548
#define LV_PLUGIN_STRING_ID_STRID_C1 549
#define LV_PLUGIN_STRING_ID_STRID_C2 550
#define LV_PLUGIN_STRING_ID_STRID_C3 551
#define LV_PLUGIN_STRING_ID_STRID_C4 552
#define LV_PLUGIN_STRING_ID_STRID_C5 553
#define LV_PLUGIN_STRING_ID_STRID_C6 554
#define LV_PLUGIN_STRING_ID_STRID_C7 555
#define LV_PLUGIN_STRING_ID_STRID_C8 556
#define LV_PLUGIN_STRING_ID_STRID_C9 557
#define LV_PLUGIN_STRING_ID_STRID_D0 558
#define LV_PLUGIN_STRING_ID_STRID_LED_DET 559
#define LV_PLUGIN_STRING_ID_STRID_1080P30_1080P30 560
#define LV_PLUGIN_STRING_ID_STRID_ONE_CAMERA 561
#define LV_PLUGIN_STRING_ID_STRID_TWO_CAMERA 562
#define LV_PLUGIN_STRING_ID_STRID_DISPLAY_MODE 563
#define LV_PLUGIN_STRING_ID_STRID_FRONT_CAMERA 564
#define LV_PLUGIN_STRING_ID_STRID_MIDDLE_CAMERA 565
#define LV_PLUGIN_STRING_ID_STRID_BACK_CAMERA 566
#define LV_PLUGIN_STRING_ID_STRID_PICTURE_IN_PICTURE 567
#define LV_PLUGIN_STRING_ID_STRID_FILL_ASCII 568
#define LV_PLUGIN_STRING_ID_STRID_PERCENT20 569
#define LV_PLUGIN_STRING_ID_STRID_PERCENT40 570
#define LV_PLUGIN_STRING_ID_STRID_PERCENT60 571
#define LV_PLUGIN_STRING_ID_STRID_PERCENT80 572
#define LV_PLUGIN_STRING_ID_STRID_PERCENT100 573
#define LV_PLUGIN_STRING_ID_STRID_MUTE 574
#define LV_PLUGIN_STRING_ID_STRID_CAMERA1 575
#define LV_PLUGIN_STRING_ID_STRID_CAMERA2 576
#define LV_PLUGIN_STRING_ID_STRID_CAMERA_NORMAL 577
#define LV_PLUGIN_STRING_ID_STRID_CAMERA_INVERTED 578
#define LV_PLUGIN_STRING_ID_STRID_WIFI 579
#define LV_PLUGIN_STRING_ID_STRID_WIFI_OFF 580
#define LV_PLUGIN_STRING_ID_STRID_REFRESH 581
#define LV_PLUGIN_STRING_ID_STRID_WIFI_AP_MODE 582
#define LV_PLUGIN_STRING_ID_STRID_WIFI_CLIENT_MODE 583
#define LV_PLUGIN_STRING_ID_STRID_SSID 584
#define LV_PLUGIN_STRING_ID_STRID_WIFI_AUTO 585
#define LV_PLUGIN_STRING_ID_STRID_BOOT_DELAY 586
#define LV_PLUGIN_STRING_ID_STRID_15SEC 587
#define LV_PLUGIN_STRING_ID_STRID_30SEC 588
#define LV_PLUGIN_STRING_ID_STRID_GPS_STAMP 589
#define LV_PLUGIN_STRING_ID_STRID_COORDINATES 590
#define LV_PLUGIN_STRING_ID_STRID_SPEED 591
#define LV_PLUGIN_STRING_ID_STRID_COORDINATES_SPEED 592
#define LV_PLUGIN_STRING_ID_STRID_GPS_STATUS 593
#define LV_PLUGIN_STRING_ID_STRID_2160P24 594
#define LV_PLUGIN_STRING_ID_STRID_1440P30 595
#define LV_PLUGIN_STRING_ID_STRID_1296P30 596
#define LV_PLUGIN_STRING_ID_STRID_1080P60 597
#define LV_PLUGIN_STRING_ID_STRID_1080P30 598
#define LV_PLUGIN_STRING_ID_STRID_720P120 599
#define LV_PLUGIN_STRING_ID_STRID_FRONT_EV 600
#define LV_PLUGIN_STRING_ID_STRID_MIDDLE_EV 601
#define LV_PLUGIN_STRING_ID_STRID_REAR_EV 602
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT 603
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_MP4 604
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_SUPER_MP4 605
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_TS 606
#define LV_PLUGIN_STRING_ID_STRID_MIDDLE_CAMERA_MIRROR 607
#define LV_PLUGIN_STRING_ID_STRID_REAR_CAMERA_MIRROR 608
#define LV_PLUGIN_STRING_ID_STRID_TIRE_SET 609
#define LV_PLUGIN_STRING_ID_STRID_PARM_SETTING 610
#define LV_PLUGIN_STRING_ID_STRID_TIRE_STATUS 611
#define LV_PLUGIN_STRING_ID_STRID_PRESSURE_UNIT 612
#define LV_PLUGIN_STRING_ID_STRID_TEMP_UNIT 613
#define LV_PLUGIN_STRING_ID_STRID_SERIAL_PORT 614
#define LV_PLUGIN_STRING_ID_STRID_HIGH_PRESSURE 615
#define LV_PLUGIN_STRING_ID_STRID_LOW_PRESSURE 616
#define LV_PLUGIN_STRING_ID_STRID_HIGH_TEMP 617
#define LV_PLUGIN_STRING_ID_STRID_INFLATING_PROGRAMMING 618
#define LV_PLUGIN_STRING_ID_STRID_TIRE_SWAP 619
#define LV_PLUGIN_STRING_ID_STRID_TIRE_PSI 620
#define LV_PLUGIN_STRING_ID_STRID_TIRE_BAR 621
#define LV_PLUGIN_STRING_ID_STRID_TIRE_C 622
#define LV_PLUGIN_STRING_ID_STRID_TIRE_F 623
#define LV_PLUGIN_STRING_ID_STRID_TIRE_FW 624
#define LV_PLUGIN_STRING_ID_STRID_TIRE_RW 625
#define LV_PLUGIN_STRING_ID_STRID_TPMS_SIGNAL_UNNORMAL 626
#define LV_PLUGIN_STRING_ID_STRID_DISABLECONNECTING 627
#define LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING 628
#define LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING_OK 629
#define LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING_FAIL 630
#define LV_PLUGIN_STRING_ID_STRID_TPMS 631
#define LV_PLUGIN_STRING_ID_STRID_AMBIANCE_LIGHT 632
#define LV_PLUGIN_STRING_ID_STRID_BREATHING_LIGHT 633
#define LV_PLUGIN_STRING_ID_STRID_PERMANENT_LIGHT 634
#define LV_PLUGIN_STRING_ID_STRID_HORSE_RACE_LIGHT 635
#define LV_PLUGIN_STRING_ID_STRID_HOST_LIGHT 636
#define LV_PLUGIN_STRING_ID_STRID_TRUNK_LIGHT 637
#define LV_PLUGIN_STRING_ID_STRID_CODEC 638
#define LV_PLUGIN_STRING_ID_STRID_WDR 639
#define LV_PLUGIN_STRING_ID_STRID_HDR_WIFI_ON_WRN 640
#define LV_PLUGIN_STRING_ID_STRID_GPS_MODULE 641
#define LV_PLUGIN_STRING_ID_STRID_MGC_3 642
#define LV_PLUGIN_STRING_ID_STRID_MGC_2 643
#define LV_PLUGIN_STRING_ID_STRID_VIDEO_FLIE_RO 644
#define LV_PLUGIN_STRING_ID_STRID_SPEEDLIMIT_VOICE 645
#define LV_PLUGIN_STRING_ID_STRID_SPEEDLIMIT_BEEP 646
#define LV_PLUGIN_STRING_ID_STRID_HDR_ON 647
#define LV_PLUGIN_STRING_ID_STRID_HDR_OFF 648
#define LV_PLUGIN_STRING_ID_STRID_HDR_TIMER 649
#define LV_PLUGIN_STRING_ID_STRID_DISABLE_GPS_IN_PARKINGMODE 650
#define LV_PLUGIN_STRING_ID_STRID_ASR 651
#define LV_PLUGIN_STRING_ID_STRID_ASR_STANDARD 652
#define LV_PLUGIN_STRING_ID_STRID_ASR_CONTENT 653
#define LV_PLUGIN_STRING_ID_STRID_ASR_TAKEPHOTO 654
#define LV_PLUGIN_STRING_ID_STRID_ASR_VIDEOSTART 655
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNONAUDIO 656
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFAUDIO 657
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNONSCREEN 658
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFSCREEN 659
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNONHOTSPOT 660
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFHOTSPOT 661
#define LV_PLUGIN_STRING_ID_STRID_ASR_LOCKVIDEO 662
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNONWIFI 663
#define LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFWIFI 664
#define LV_PLUGIN_STRING_ID_STRID_ASR_VIDEOSTOP 665
#define LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_FRONT_CAMERA 666
#define LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_REAR_CAMERA 667
#define LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_BOTH_CAMERAS 668
#define LV_PLUGIN_STRING_ID_STRID_ASR_INSIDE_VIDEO_ON 669
#define LV_PLUGIN_STRING_ID_STRID_ASR_BACK_TO_HOMEPAGE 670
#define LV_PLUGIN_STRING_ID_STRID_90SEC 671
#define LV_PLUGIN_STRING_ID_STRID_12HOUR 672
#define LV_PLUGIN_STRING_ID_STRID_24HOUR 673
#define LV_PLUGIN_STRING_ID_STRID_48HOUR 674
#define LV_PLUGIN_STRING_ID_STRID_72HOUR 675
#define LV_PLUGIN_STRING_ID_STRID_TL_1FPS 676
#define LV_PLUGIN_STRING_ID_STRID_TL_2FPS 677
#define LV_PLUGIN_STRING_ID_STRID_TL_3FPS 678
#define LV_PLUGIN_STRING_ID_STRID_TL_4FPS 679
#define LV_PLUGIN_STRING_ID_STRID_TL_5FPS 680
#define LV_PLUGIN_STRING_ID_STRID_TL_6FPS 681
#define LV_PLUGIN_STRING_ID_STRID_TL_7FPS 682
#define LV_PLUGIN_STRING_ID_STRID_TL_8FPS 683
#define LV_PLUGIN_STRING_ID_STRID_TL_9FPS 684
#define LV_PLUGIN_STRING_ID_STRID_TL_10FPS 685
#define LV_PLUGIN_STRING_ID_STRID_PARKING_GSENSOR 686
#define LV_PLUGIN_STRING_ID_STRID_PARKING_MOTION_DET 687
#define LV_PLUGIN_STRING_ID_STRID_H264 688
#define LV_PLUGIN_STRING_ID_STRID_H265 689
#define LV_PLUGIN_STRING_ID_STRID_SHUTDOWN_TIMER 690
#define LV_PLUGIN_STRING_ID_STRID_ENTERPARKING_TIMER 691
#define LV_PLUGIN_STRING_ID_STRID_PARKING_MODE 692
#define LV_PLUGIN_STRING_ID_STRID_AUTO_EVENT_DETECTION 693
#define LV_PLUGIN_STRING_ID_STRID_LOW_BITRATE 694
#define LV_PLUGIN_STRING_ID_STRID_CAN_NOT_BE_SET 695
#define LV_PLUGIN_STRING_ID_STRID_EIS 696
#define LV_PLUGIN_STRING_ID_STRID_IN_PREPARATION 697
#define LV_PLUGIN_STRING_ID_STRID_WIFI_24G 698
#define LV_PLUGIN_STRING_ID_STRID_WIFI_5G 699
#define LV_PLUGIN_STRING_ID_STRID_WIFI_52G 700
#define LV_PLUGIN_STRING_ID_STRID_WIFI_58G 701
#define LV_PLUGIN_STRING_ID_STRID_IMAGE_MIRROR 702
#define LV_PLUGIN_STRING_ID_STRID_DISPLAY_MIRROR 703
#define LV_PLUGIN_STRING_ID_STRID_MOVIE_SETTING 704
#define LV_PLUGIN_STRING_ID_STRID_SYSTEM_SETTING 705
#define LV_PLUGIN_STRING_ID_STRID_DETECT_SETTING 706
#define LV_PLUGIN_STRING_ID_STRID_START_SOUND 707
#define LV_PLUGIN_STRING_ID_STRID_SCENE_MODE 708
#define LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_GENERAL 709
#define LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_CITY 710
#define LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_MOTOCROSS 711
#define LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_PRO 712
#define LV_PLUGIN_STRING_ID_STRID_MON 713
#define LV_PLUGIN_STRING_ID_STRID_TUE 714
#define LV_PLUGIN_STRING_ID_STRID_WED 715
#define LV_PLUGIN_STRING_ID_STRID_THU 716
#define LV_PLUGIN_STRING_ID_STRID_FRI 717
#define LV_PLUGIN_STRING_ID_STRID_SAT 718
#define LV_PLUGIN_STRING_ID_STRID_SUN 719
#define LV_PLUGIN_STRING_ID_STRID_SPEED_ALERT 720
#define LV_PLUGIN_STRING_ID_STRID_TIME_DISPLAY 721
#define LV_PLUGIN_STRING_ID_STRID_WARN_OFF_WIFI 722
#define LV_PLUGIN_STRING_ID_STRID_REAR_ERROR 723
#define LV_PLUGIN_STRING_ID_STRID_LIGHT_CTRL 724
#define LV_PLUGIN_STRING_ID_STRID_BRGITHNESS_LEVEL 725
#define LV_PLUGIN_STRING_ID_STRID_BUZZER_VOLUME 726
#define LV_PLUGIN_STRING_ID_STRID_REVERSE_ALARM_SOUND 727
#define LV_PLUGIN_STRING_ID_STRID_SPEED_ALERT_SOUND 728
#define LV_PLUGIN_STRING_ID_STRID_MACHINE_POS 729
#define LV_PLUGIN_STRING_ID_STRID_BOTTOM_HORIZONTAL 730
#define LV_PLUGIN_STRING_ID_STRID_BOTTOM_VERTICAL 731
#define LV_PLUGIN_STRING_ID_STRID_SIDE_HORIZONTAL 732
#define LV_PLUGIN_STRING_ID_STRID_SIDE_VERTICAL 733
#define LV_PLUGIN_STRING_ID_STRID_BACK_HORIZONTAL 734
#define LV_PLUGIN_STRING_ID_STRID_BACK_VERTICAL 735
#define LV_PLUGIN_STRING_ID_STRID_GSENSOR_CAL 736
#define LV_PLUGIN_STRING_ID_STRID_ACCIDENT_ALARM 737
#define LV_PLUGIN_STRING_ID_STRID_REVERSE_ALARM 738
#define LV_PLUGIN_STRING_ID_STRID_GSENSOR_CAL_WARN 739
#define LV_PLUGIN_STRING_ID_STRID_REQUIRE_ACC_HW_CABLE 740
#define LV_PLUGIN_STRING_ID_STRID_HOLD3S_TOGGLE_ALARM 741
#define LV_PLUGIN_STRING_ID_STRID_HMW 742
#define LV_PLUGIN_STRING_ID_STRID_PCW 743
#define LV_PLUGIN_STRING_ID_STRID_RCW 744
#define LV_PLUGIN_STRING_ID_STRID_BSD 745
#define LV_PLUGIN_STRING_ID_STRID_LDWS 746
#define LV_PLUGIN_STRING_ID_STRID_FCW 747
#define LV_PLUGIN_STRING_ID_STRID_VIRTUAL_BUMPER 748
#define LV_PLUGIN_STRING_ID_STRID_LCWS 749
#define LV_PLUGIN_STRING_ID_STRID_ADAS_CALIBRATION 750
#define LV_PLUGIN_STRING_ID_STRID_ADAS_CORDON 751
#define LV_PLUGIN_STRING_ID_STRID_ADAS_CORDON_LINE 752
#define LV_PLUGIN_STRING_ID_STRID_APP_CONNECTTING 753
#define LV_PLUGIN_STRING_ID_STRID_ADAS 754
#define LV_PLUGIN_STRING_ID_STRID_1080P60_D1P30 755
#define LV_PLUGIN_STRING_ID_STRID_ISO800 756
#define LV_PLUGIN_STRING_ID_STRID_ISO1600 757
#define LV_PLUGIN_STRING_ID_STRID_ISO3200 758
#define LV_PLUGIN_STRING_ID_STRID_60MIN 759
#define LV_PLUGIN_STRING_ID_STRID_SCREEN_SAVE 760
#define LV_PLUGIN_STRING_ID_STRID_DUAL_REC 761
#define LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_REC 762
#define LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_CAP 763
#define LV_PLUGIN_STRING_ID_STRID_MAKE_MOVIE 764
#define LV_PLUGIN_STRING_ID_STRID_PROCESSING 765
#define LV_PLUGIN_STRING_ID_STRID_TIME_LPASE 766
#define LV_PLUGIN_STRING_ID_STRID_100MS 767
#define LV_PLUGIN_STRING_ID_STRID_200MS 768
#define LV_PLUGIN_STRING_ID_STRID_500MS 769
#define LV_PLUGIN_STRING_ID_STRID_UNDERSCORE 770
#define LV_PLUGIN_STRING_ID_STRID_MODE_SWITCH 771
#define LV_PLUGIN_STRING_ID_STRID_2880X2160P24 772
#define LV_PLUGIN_STRING_ID_STRID_2560X1440P30 773
#define LV_PLUGIN_STRING_ID_STRID_2304X1296P30 774
#define LV_PLUGIN_STRING_ID_STRID_1080P96 775
#define LV_PLUGIN_STRING_ID_STRID_1080P_DUAL 776
#define LV_PLUGIN_STRING_ID_STRID_720P120WXH 777
#define LV_PLUGIN_STRING_ID_STRID_RSC 778
#define LV_PLUGIN_STRING_ID_STRID_G_SENSOR 779
#define LV_PLUGIN_STRING_ID_STRID_1SEC 780
#define LV_PLUGIN_STRING_ID_STRID_1HOUR 781
#define LV_PLUGIN_STRING_ID_STRID_2HOUR 782
#define LV_PLUGIN_STRING_ID_STRID_3HOUR 783
#define LV_PLUGIN_STRING_ID_STRID_1DAY 784
#define LV_PLUGIN_STRING_ID_STRID_IRCUT 785
#define LV_PLUGIN_STRING_ID_STRID_DUAL_CAM 786
#define LV_PLUGIN_STRING_ID_STRID_FRONT 787
#define LV_PLUGIN_STRING_ID_STRID_BEHIND 788
#define LV_PLUGIN_STRING_ID_STRID_BOTH 789
#define LV_PLUGIN_STRING_ID_STRID_PTZ 790
#define LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_AUTO 791
#define LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_MANUAL 792
#define LV_PLUGIN_STRING_ID_STRID_PIM 793
#define LV_PLUGIN_STRING_ID_STRID_DDD 794
#define LV_PLUGIN_STRING_ID_STRID_REC_RECOVERY 795
#define LV_PLUGIN_STRING_ID_STRID_SELFTIMER 796
#define LV_PLUGIN_STRING_ID_STRID_PORTRIAL 797
#define LV_PLUGIN_STRING_ID_STRID_LANDSCPE 798
#define LV_PLUGIN_STRING_ID_STRID_0 799
#define LV_PLUGIN_STRING_ID_STRID_1 800
#define LV_PLUGIN_STRING_ID_STRID_2 801
#define LV_PLUGIN_STRING_ID_STRID_3 802
#define LV_PLUGIN_STRING_ID_STRID_4 803
#define LV_PLUGIN_STRING_ID_STRID_5 804
#define LV_PLUGIN_STRING_ID_STRID_6 805
#define LV_PLUGIN_STRING_ID_STRID_7 806
#define LV_PLUGIN_STRING_ID_STRID_8 807
#define LV_PLUGIN_STRING_ID_STRID_9 808
#define LV_PLUGIN_STRING_ID_STRID_10 809
#define LV_PLUGIN_STRING_ID_STRID_CLOUD 810
#define LV_PLUGIN_STRING_ID_STRID_FW_UPDATE 811
#define LV_PLUGIN_STRING_ID_STRID_UVC 812
#define LV_PLUGIN_STRING_ID_STRID_RESUME 813
#define LV_PLUGIN_STRING_ID_STRID_MCTF 814
#define LV_PLUGIN_STRING_ID_STRID_EDGE 815
#define LV_PLUGIN_STRING_ID_STRID_NR 816
#define LV_PLUGIN_STRING_ID_STRID_WIFI_ETH 817
#define LV_PLUGIN_STRING_ID_STRID_ISO6400 818
#define LV_PLUGIN_STRING_ID_STRID_ISO12800 819
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P50 820
#define LV_PLUGIN_STRING_ID_STRID_FRONT_3840X2160P30 821
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P24 822
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2704X2032P60 823
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P80 824
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P60 825
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P30 826
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2304X1296P30 827
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P120 828
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P96 829
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P60 830
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P30 831
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P240 832
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P120 833
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P60 834
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P30 835
#define LV_PLUGIN_STRING_ID_STRID_FRONT_848X480P30 836
#define LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P240 837
#define LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P30 838
#define LV_PLUGIN_STRING_ID_STRID_FRONT_320X240P30 839
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1280X720P30 840
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1920X1080P30 841
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2304X1296P30_1280X720P30 842
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1080P30_1080P30 843
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_1920X1080P30 844
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_1280X720P30 845
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_848X480P30 846
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1920X1080P30 847
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1280X720P30 848
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2560X1440P30_848X480P30 849
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2304X1296P30_848X480P30 850
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_848X480P30 851
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_640X360P30 852
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_848X480P30 853
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2048X2048P30_480X480P30 854
#define LV_PLUGIN_STRING_ID_STRID_BOTH2 855
#define LV_PLUGIN_STRING_ID_STRID_CAP_SIDE 856
#define LV_PLUGIN_STRING_ID_STRID_CAP_BURST_30 857
#define LV_PLUGIN_STRING_ID_STRID_5MWXH_USR 858
#define LV_PLUGIN_STRING_ID_STRID_MJPG 859
#define LV_PLUGIN_STRING_ID_STRID_2880X2160P50 860
#define LV_PLUGIN_STRING_ID_STRID_3840X2160P30 861
#define LV_PLUGIN_STRING_ID_STRID_18HOUR 862
#define LV_PLUGIN_STRING_ID_STRID_2560X1440P60 863
#define LV_PLUGIN_STRING_ID_STRID_2560X1440P80 864
#define LV_PLUGIN_STRING_ID_STRID_2704X2032P60 865
#define LV_PLUGIN_STRING_ID_STRID_4HOUR 866
#define LV_PLUGIN_STRING_ID_STRID_6HOUR 867
#define LV_PLUGIN_STRING_ID_STRID_8HOUR 868
#define LV_PLUGIN_STRING_ID_STRID_COLOR_MONO 869
#define LV_PLUGIN_STRING_ID_STRID_CUSTOMIZE 870
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1080P60_1080P60 871
#define LV_PLUGIN_STRING_ID_STRID_DUAL_3840X2160P30_1920X1080P30 872
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2304X1296P60 873
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1080P30 874
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1080P60 875
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1600P30 876
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2592X1944P30 877
#define LV_PLUGIN_STRING_ID_STRID_GMT_N230 878
#define LV_PLUGIN_STRING_ID_STRID_GMT_P630 879
#define LV_PLUGIN_STRING_ID_STRID_IR_CAMERA_COLOR 880
#define LV_PLUGIN_STRING_ID_STRID_IR_COLOR 881
#define LV_PLUGIN_STRING_ID_STRID_LANG_AZ 882
#define LV_PLUGIN_STRING_ID_STRID_LANG_CZ 883
#define LV_PLUGIN_STRING_ID_STRID_LANG_NL 884
#define LV_PLUGIN_STRING_ID_STRID_LANG_NO 885
#define LV_PLUGIN_STRING_ID_STRID_LANG_RO 886
#define LV_PLUGIN_STRING_ID_STRID_LANG_SK 887
#define LV_PLUGIN_STRING_ID_STRID_LANG_TR 888
#define LV_PLUGIN_STRING_ID_STRID_LIVESTREAM 889
#define LV_PLUGIN_STRING_ID_STRID_MODEL_STAMP 890
#define LV_PLUGIN_STRING_ID_STRID_MOVIE_BITRATE 891
#define LV_PLUGIN_STRING_ID_STRID_PERIPHERAL 892
#define LV_PLUGIN_STRING_ID_STRID_PM_15FPS 893
#define LV_PLUGIN_STRING_ID_STRID_QUAD_1920X1080P30 894
#define LV_PLUGIN_STRING_ID_STRID_RSC_EFFECT 895
#define LV_PLUGIN_STRING_ID_STRID_SUPER_HIGH 896
#define LV_PLUGIN_STRING_ID_STRID_TPMS_PRSR_UNIT 897
#define LV_PLUGIN_STRING_ID_STRID_TPMS_TEMP_UNIT 898
#define LV_PLUGIN_STRING_ID_STRID_TRI_1920X1080P30 899
#define LV_PLUGIN_STRING_ID_STRID_TRI_2560X1440P30_1920X1080P30_1920X1080P30 900
#define LV_PLUGIN_STRING_TABLE_SIZE 901

#define LV_PLUGIN_LANGUAGE_ID_EN 1
#define LV_PLUGIN_LANGUAGE_ID_FR 2
#define LV_PLUGIN_LANGUAGE_ID_DE 3
#define LV_PLUGIN_LANGUAGE_ID_ES 4
#define LV_PLUGIN_LANGUAGE_ID_IT 5
#define LV_PLUGIN_LANGUAGE_ID_PO 6
#define LV_PLUGIN_LANGUAGE_ID_SC 7
#define LV_PLUGIN_LANGUAGE_ID_JP 8
#define LV_PLUGIN_LANGUAGE_ID_TC 9
#define LV_PLUGIN_LANGUAGE_ID_RU 10
#define LV_PLUGIN_LANGUAGE_TABLE_SIZE 11
#define LV_PLUGIN_LANGUAGE_FONT_TYPE_SIZE 5



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif