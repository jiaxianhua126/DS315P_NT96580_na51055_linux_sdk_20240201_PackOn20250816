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
#include "UIFlowLVGL/UIFlowPlayThumb/UIFlowPlayThumb.h"
#include "UIFlowLVGL/UIFlowUSB/UIFlowUSB.h"
#include "UIFlowLVGL/UIFlowUSBMenu/UIFlowUSBMenu.h"
#include "UIFlowLVGL/UIFlowWifiLink/UIFlowWifiLink.h"
#include "UIFlowLVGL/UIFlowWifiLinkOK/UIFlowWifiLinkOK.h"
#include "UIFlowLVGL/UIFlowWifiWait/UIFlowWifiWait.h"
#include "UIFlowLVGL/UIFlowMovieWiFi/UIFlowMovieWiFi.h"


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
extern lv_obj_t *UIFlowPlayThumb;
extern lv_obj_t *UIFlowUSB;
extern lv_obj_t *UIFlowUSBMenu;
extern lv_obj_t *UIFlowWifiLink;
extern lv_obj_t *UIFlowWifiLinkOK;
extern lv_obj_t *UIFlowWifiWait;
extern lv_obj_t *UIFlowMovieWiFi;

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
#define LV_PLUGIN_STRING_ID_STRID_1080P60_D1P30 38
#define LV_PLUGIN_STRING_ID_STRID_D1WXH 39
#define LV_PLUGIN_STRING_ID_STRID_720PWXH 40
#define LV_PLUGIN_STRING_ID_STRID_1080PWXH 41
#define LV_PLUGIN_STRING_ID_STRID_1080FHDWXH 42
#define LV_PLUGIN_STRING_ID_STRID_COMPRESSION 43
#define LV_PLUGIN_STRING_ID_STRID_QUALITY 44
#define LV_PLUGIN_STRING_ID_STRID_SUPER 45
#define LV_PLUGIN_STRING_ID_STRID_FINE 46
#define LV_PLUGIN_STRING_ID_STRID_NORMAL 47
#define LV_PLUGIN_STRING_ID_STRID_ECONOMY 48
#define LV_PLUGIN_STRING_ID_STRID_WB 49
#define LV_PLUGIN_STRING_ID_STRID_AUTO 50
#define LV_PLUGIN_STRING_ID_STRID_WB_DAY 51
#define LV_PLUGIN_STRING_ID_STRID_WB_CLOUDY 52
#define LV_PLUGIN_STRING_ID_STRID_WB_TUNGSTEN 53
#define LV_PLUGIN_STRING_ID_STRID_WB_FLUORESCENT 54
#define LV_PLUGIN_STRING_ID_STRID_EXPOSURE 55
#define LV_PLUGIN_STRING_ID_STRID_EV 56
#define LV_PLUGIN_STRING_ID_STRID_ISO 57
#define LV_PLUGIN_STRING_ID_STRID_ISO50 58
#define LV_PLUGIN_STRING_ID_STRID_ISO100 59
#define LV_PLUGIN_STRING_ID_STRID_ISO200 60
#define LV_PLUGIN_STRING_ID_STRID_ISO400 61
#define LV_PLUGIN_STRING_ID_STRID_ISO800 62
#define LV_PLUGIN_STRING_ID_STRID_ISO1600 63
#define LV_PLUGIN_STRING_ID_STRID_ISO3200 64
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
#define LV_PLUGIN_STRING_ID_STRID_VIDEO 124
#define LV_PLUGIN_STRING_ID_STRID_AUDIO 125
#define LV_PLUGIN_STRING_ID_STRID_SETUP 126
#define LV_PLUGIN_STRING_ID_STRID_FREQUENCY 127
#define LV_PLUGIN_STRING_ID_STRID_50HZ 128
#define LV_PLUGIN_STRING_ID_STRID_60HZ 129
#define LV_PLUGIN_STRING_ID_STRID_MEDIA 130
#define LV_PLUGIN_STRING_ID_STRID_STORAGE 131
#define LV_PLUGIN_STRING_ID_STRID_INT_FLASH 132
#define LV_PLUGIN_STRING_ID_STRID_EXT_CARD 133
#define LV_PLUGIN_STRING_ID_STRID_LOGO_DISPLAY 134
#define LV_PLUGIN_STRING_ID_STRID_OPENING 135
#define LV_PLUGIN_STRING_ID_STRID_FORMAT 136
#define LV_PLUGIN_STRING_ID_STRID_OK 137
#define LV_PLUGIN_STRING_ID_STRID_CANCEL 138
#define LV_PLUGIN_STRING_ID_STRID_BEEPER 139
#define LV_PLUGIN_STRING_ID_STRID_BEEP_LOUD 140
#define LV_PLUGIN_STRING_ID_STRID_BEEP_SOFT 141
#define LV_PLUGIN_STRING_ID_STRID_LANGUAGE 142
#define LV_PLUGIN_STRING_ID_STRID_LANG_EN 143
#define LV_PLUGIN_STRING_ID_STRID_LANG_FR 144
#define LV_PLUGIN_STRING_ID_STRID_LANG_ES 145
#define LV_PLUGIN_STRING_ID_STRID_LANG_DE 146
#define LV_PLUGIN_STRING_ID_STRID_LANG_IT 147
#define LV_PLUGIN_STRING_ID_STRID_LANG_TC 148
#define LV_PLUGIN_STRING_ID_STRID_LANG_SC 149
#define LV_PLUGIN_STRING_ID_STRID_LANG_JP 150
#define LV_PLUGIN_STRING_ID_STRID_LANG_PO 151
#define LV_PLUGIN_STRING_ID_STRID_LANG_RU 152
#define LV_PLUGIN_STRING_ID_STRID_USB 153
#define LV_PLUGIN_STRING_ID_STRID_PC_MODE 154
#define LV_PLUGIN_STRING_ID_STRID_MSDC 155
#define LV_PLUGIN_STRING_ID_STRID_PCC 156
#define LV_PLUGIN_STRING_ID_STRID_PICTBRIDGE 157
#define LV_PLUGIN_STRING_ID_STRID_USBCHARGE 158
#define LV_PLUGIN_STRING_ID_STRID_TV_MODE 159
#define LV_PLUGIN_STRING_ID_STRID_TV_NTSC 160
#define LV_PLUGIN_STRING_ID_STRID_TV_PAL 161
#define LV_PLUGIN_STRING_ID_STRID_BRIGHTNESS 162
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF 163
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_1MIN 164
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_2MIN 165
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_3MIN 166
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_5MIN 167
#define LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_10MIN 168
#define LV_PLUGIN_STRING_ID_STRID_1MIN 169
#define LV_PLUGIN_STRING_ID_STRID_2MIN 170
#define LV_PLUGIN_STRING_ID_STRID_3MIN 171
#define LV_PLUGIN_STRING_ID_STRID_5MIN 172
#define LV_PLUGIN_STRING_ID_STRID_10MIN 173
#define LV_PLUGIN_STRING_ID_STRID_15MIN 174
#define LV_PLUGIN_STRING_ID_STRID_20MIN 175
#define LV_PLUGIN_STRING_ID_STRID_25MIN 176
#define LV_PLUGIN_STRING_ID_STRID_30MIN 177
#define LV_PLUGIN_STRING_ID_STRID_60MIN 178
#define LV_PLUGIN_STRING_ID_STRID_SCREEN_SAVE 179
#define LV_PLUGIN_STRING_ID_STRID_CYCLIC_REC 180
#define LV_PLUGIN_STRING_ID_STRID_FLASH_REC 181
#define LV_PLUGIN_STRING_ID_STRID_GOLF_REC 182
#define LV_PLUGIN_STRING_ID_STRID_DUAL_REC 183
#define LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_REC 184
#define LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_CAP 185
#define LV_PLUGIN_STRING_ID_STRID_MAKE_MOVIE 186
#define LV_PLUGIN_STRING_ID_STRID_PROCESSING 187
#define LV_PLUGIN_STRING_ID_STRID_NONE 188
#define LV_PLUGIN_STRING_ID_STRID_RESET_NUM 189
#define LV_PLUGIN_STRING_ID_STRID_DEFAULT_SETTING 190
#define LV_PLUGIN_STRING_ID_STRID_YES 191
#define LV_PLUGIN_STRING_ID_STRID_NO 192
#define LV_PLUGIN_STRING_ID_STRID_VERSION 193
#define LV_PLUGIN_STRING_ID_STRID_PLAYBACK 194
#define LV_PLUGIN_STRING_ID_STRID_THUMBNAIL 195
#define LV_PLUGIN_STRING_ID_STRID_SET_LOGO 196
#define LV_PLUGIN_STRING_ID_STRID_ROTATE 197
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_S 198
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_90 199
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_180 200
#define LV_PLUGIN_STRING_ID_STRID_ROTATE_270 201
#define LV_PLUGIN_STRING_ID_STRID_CROP 202
#define LV_PLUGIN_STRING_ID_STRID_CROP_S 203
#define LV_PLUGIN_STRING_ID_STRID_SLIDE_SHOW 204
#define LV_PLUGIN_STRING_ID_STRID_2SEC 205
#define LV_PLUGIN_STRING_ID_STRID_3SEC 206
#define LV_PLUGIN_STRING_ID_STRID_5SEC 207
#define LV_PLUGIN_STRING_ID_STRID_8SEC 208
#define LV_PLUGIN_STRING_ID_STRID_10SEC 209
#define LV_PLUGIN_STRING_ID_STRID_PROTECT 210
#define LV_PLUGIN_STRING_ID_STRID_PROTECTONE 211
#define LV_PLUGIN_STRING_ID_STRID_PROTECTALL 212
#define LV_PLUGIN_STRING_ID_STRID_LOCK 213
#define LV_PLUGIN_STRING_ID_STRID_LOCKONE 214
#define LV_PLUGIN_STRING_ID_STRID_LOCKALL 215
#define LV_PLUGIN_STRING_ID_STRID_LOCKSELECTED 216
#define LV_PLUGIN_STRING_ID_STRID_UNLOCK 217
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKONE 218
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKALL 219
#define LV_PLUGIN_STRING_ID_STRID_UNLOCKSELECTED 220
#define LV_PLUGIN_STRING_ID_STRID_DPOF 221
#define LV_PLUGIN_STRING_ID_STRID_ONEIMAGE 222
#define LV_PLUGIN_STRING_ID_STRID_ALL_IMAGES 223
#define LV_PLUGIN_STRING_ID_STRID_THIS_IMAGE 224
#define LV_PLUGIN_STRING_ID_STRID_THIS_VIDEO 225
#define LV_PLUGIN_STRING_ID_STRID_SELECT_IMAGES 226
#define LV_PLUGIN_STRING_ID_STRID_ALL_INDEX 227
#define LV_PLUGIN_STRING_ID_STRID_ALL 228
#define LV_PLUGIN_STRING_ID_STRID_RESETALL 229
#define LV_PLUGIN_STRING_ID_STRID_COPIES 230
#define LV_PLUGIN_STRING_ID_STRID_RETURN 231
#define LV_PLUGIN_STRING_ID_STRID_RESIZE 232
#define LV_PLUGIN_STRING_ID_STRID_QUALITYCHANGE 233
#define LV_PLUGIN_STRING_ID_STRID_COPY_TO_CARD 234
#define LV_PLUGIN_STRING_ID_STRID_COPY_FROM_CARD 235
#define LV_PLUGIN_STRING_ID_STRID_COPY 236
#define LV_PLUGIN_STRING_ID_STRID_TOSD 237
#define LV_PLUGIN_STRING_ID_STRID_TOINTERNAL 238
#define LV_PLUGIN_STRING_ID_STRID_DELETE 239
#define LV_PLUGIN_STRING_ID_STRID_DELETECURRENT 240
#define LV_PLUGIN_STRING_ID_STRID_DELETEALL 241
#define LV_PLUGIN_STRING_ID_STRID_DELETESELECTED 242
#define LV_PLUGIN_STRING_ID_STRID_DATAPROCESSED 243
#define LV_PLUGIN_STRING_ID_STRID_SELECT 244
#define LV_PLUGIN_STRING_ID_STRID_PAGE 245
#define LV_PLUGIN_STRING_ID_STRID_PRINTMODESEL 246
#define LV_PLUGIN_STRING_ID_STRID_SIZE 247
#define LV_PLUGIN_STRING_ID_STRID_STANDARD 248
#define LV_PLUGIN_STRING_ID_STRID_CONTINUE 249
#define LV_PLUGIN_STRING_ID_STRID_WITHOUT 250
#define LV_PLUGIN_STRING_ID_STRID_WITH 251
#define LV_PLUGIN_STRING_ID_STRID_NAME 252
#define LV_PLUGIN_STRING_ID_STRID_NO_IMAGE 253
#define LV_PLUGIN_STRING_ID_STRID_SET 254
#define LV_PLUGIN_STRING_ID_STRID_MEMORY_FULL 255
#define LV_PLUGIN_STRING_ID_STRID_CARD_FULL 256
#define LV_PLUGIN_STRING_ID_STRID_FOLDERFULL 257
#define LV_PLUGIN_STRING_ID_STRID_CARDERROR 258
#define LV_PLUGIN_STRING_ID_STRID_MEMORYERROR 259
#define LV_PLUGIN_STRING_ID_STRID_LENSERROR 260
#define LV_PLUGIN_STRING_ID_STRID_CARD_LOCKED 261
#define LV_PLUGIN_STRING_ID_STRID_FILE_PROTECT 262
#define LV_PLUGIN_STRING_ID_STRID_PICTUREERROR 263
#define LV_PLUGIN_STRING_ID_STRID_BATTERY_LOW 264
#define LV_PLUGIN_STRING_ID_STRID_ONEMOMENT 265
#define LV_PLUGIN_STRING_ID_STRID_NOCONNECTION 266
#define LV_PLUGIN_STRING_ID_STRID_TRANSFERRING 267
#define LV_PLUGIN_STRING_ID_STRID_CONNECTEDTOPC 268
#define LV_PLUGIN_STRING_ID_STRID_REMOVEUSBCABLE 269
#define LV_PLUGIN_STRING_ID_STRID_TOTAL 270
#define LV_PLUGIN_STRING_ID_STRID_DATE_STAMPING 271
#define LV_PLUGIN_STRING_ID_STRID_FILE_NAME 272
#define LV_PLUGIN_STRING_ID_STRID_NO_OF_COPY 273
#define LV_PLUGIN_STRING_ID_STRID_DEFAULT 274
#define LV_PLUGIN_STRING_ID_STRID_MENU 275
#define LV_PLUGIN_STRING_ID_STRID_EXIT 276
#define LV_PLUGIN_STRING_ID_STRID_PLEASE_WAIT 277
#define LV_PLUGIN_STRING_ID_STRID_STARTSHUTTER 278
#define LV_PLUGIN_STRING_ID_STRID_STOPSHUTTER 279
#define LV_PLUGIN_STRING_ID_STRID_NO_FILE 280
#define LV_PLUGIN_STRING_ID_STRID_NO_CARD 281
#define LV_PLUGIN_STRING_ID_STRID_NO_PHOTO 282
#define LV_PLUGIN_STRING_ID_STRID_NOT_JPEG 283
#define LV_PLUGIN_STRING_ID_STRID_FLASHNOTREADY 284
#define LV_PLUGIN_STRING_ID_STRID_UPDATEBG 285
#define LV_PLUGIN_STRING_ID_STRID_CHECKVERSION 286
#define LV_PLUGIN_STRING_ID_STRID_PSTOREERR 287
#define LV_PLUGIN_STRING_ID_STRID_PLAY 288
#define LV_PLUGIN_STRING_ID_STRID_PAUSE 289
#define LV_PLUGIN_STRING_ID_STRID_STOP 290
#define LV_PLUGIN_STRING_ID_STRID_MOVE 291
#define LV_PLUGIN_STRING_ID_STRID_SAVE 292
#define LV_PLUGIN_STRING_ID_STRID_NEXT 293
#define LV_PLUGIN_STRING_ID_STRID_CHANGE 294
#define LV_PLUGIN_STRING_ID_STRID_VOLUME 295
#define LV_PLUGIN_STRING_ID_STRID_STILL 296
#define LV_PLUGIN_STRING_ID_STRID_BATTERY_TYPE 297
#define LV_PLUGIN_STRING_ID_STRID_ALKALINE 298
#define LV_PLUGIN_STRING_ID_STRID_NIMH 299
#define LV_PLUGIN_STRING_ID_STRID_DELETE_WARNING 300
#define LV_PLUGIN_STRING_ID_STRID_SEQUENCE_NO 301
#define LV_PLUGIN_STRING_ID_STRID_RESET_WARNING 302
#define LV_PLUGIN_STRING_ID_STRID_ERASE_THIS 303
#define LV_PLUGIN_STRING_ID_STRID_ERASE_ALL 304
#define LV_PLUGIN_STRING_ID_STRID_IMAGES 305
#define LV_PLUGIN_STRING_ID_STRID_CONNECT_TO_DEVICE 306
#define LV_PLUGIN_STRING_ID_STRID_DEVICE_IS_CONNECTED 307
#define LV_PLUGIN_STRING_ID_STRID_LINK_ERROR 308
#define LV_PLUGIN_STRING_ID_STRID_USB_ERROR 309
#define LV_PLUGIN_STRING_ID_STRID_DUMMY 310
#define LV_PLUGIN_STRING_ID_STRID_EV_M0P3 311
#define LV_PLUGIN_STRING_ID_STRID_EV_M0P6 312
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P0 313
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P3 314
#define LV_PLUGIN_STRING_ID_STRID_EV_M1P6 315
#define LV_PLUGIN_STRING_ID_STRID_EV_M2P0 316
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P0 317
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P3 318
#define LV_PLUGIN_STRING_ID_STRID_EV_P0P6 319
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P0 320
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P3 321
#define LV_PLUGIN_STRING_ID_STRID_EV_P1P6 322
#define LV_PLUGIN_STRING_ID_STRID_EV_P2P0 323
#define LV_PLUGIN_STRING_ID_STRID_PRINT_ALL 324
#define LV_PLUGIN_STRING_ID_STRID_PRINT_INDEX 325
#define LV_PLUGIN_STRING_ID_STRID_PRINT_DPOF 326
#define LV_PLUGIN_STRING_ID_STRID_PRINT_SETTING 327
#define LV_PLUGIN_STRING_ID_STRID_DPOF_RESTART 328
#define LV_PLUGIN_STRING_ID_STRID_PRINT 329
#define LV_PLUGIN_STRING_ID_STRID_START_PRINTING 330
#define LV_PLUGIN_STRING_ID_STRID_PRINTING 331
#define LV_PLUGIN_STRING_ID_STRID_PRINT_CANCELED 332
#define LV_PLUGIN_STRING_ID_STRID_PRINT_FINISHED 333
#define LV_PLUGIN_STRING_ID_STRID_OK_TO_PRINT 334
#define LV_PLUGIN_STRING_ID_STRID_PAPER_SIZE 335
#define LV_PLUGIN_STRING_ID_STRID_L 336
#define LV_PLUGIN_STRING_ID_STRID_2L 337
#define LV_PLUGIN_STRING_ID_STRID_POSTCARD 338
#define LV_PLUGIN_STRING_ID_STRID_CARD 339
#define LV_PLUGIN_STRING_ID_STRID_100X150 340
#define LV_PLUGIN_STRING_ID_STRID_4X6 341
#define LV_PLUGIN_STRING_ID_STRID_8X10 342
#define LV_PLUGIN_STRING_ID_STRID_LETTER 343
#define LV_PLUGIN_STRING_ID_STRID_11X17 344
#define LV_PLUGIN_STRING_ID_STRID_A0 345
#define LV_PLUGIN_STRING_ID_STRID_A1 346
#define LV_PLUGIN_STRING_ID_STRID_A2 347
#define LV_PLUGIN_STRING_ID_STRID_A3 348
#define LV_PLUGIN_STRING_ID_STRID_A4 349
#define LV_PLUGIN_STRING_ID_STRID_A5 350
#define LV_PLUGIN_STRING_ID_STRID_A6 351
#define LV_PLUGIN_STRING_ID_STRID_A7 352
#define LV_PLUGIN_STRING_ID_STRID_A8 353
#define LV_PLUGIN_STRING_ID_STRID_A9 354
#define LV_PLUGIN_STRING_ID_STRID_B0 355
#define LV_PLUGIN_STRING_ID_STRID_B1 356
#define LV_PLUGIN_STRING_ID_STRID_B2 357
#define LV_PLUGIN_STRING_ID_STRID_B3 358
#define LV_PLUGIN_STRING_ID_STRID_B4 359
#define LV_PLUGIN_STRING_ID_STRID_B5 360
#define LV_PLUGIN_STRING_ID_STRID_B6 361
#define LV_PLUGIN_STRING_ID_STRID_B7 362
#define LV_PLUGIN_STRING_ID_STRID_B8 363
#define LV_PLUGIN_STRING_ID_STRID_B9 364
#define LV_PLUGIN_STRING_ID_STRID_L_ROLLS 365
#define LV_PLUGIN_STRING_ID_STRID_2L_ROLLS 366
#define LV_PLUGIN_STRING_ID_STRID_4_ROLLS 367
#define LV_PLUGIN_STRING_ID_STRID_A4_ROLLS 368
#define LV_PLUGIN_STRING_ID_STRID_PAPER_TYPE 369
#define LV_PLUGIN_STRING_ID_STRID_PHOTO_PAPER 370
#define LV_PLUGIN_STRING_ID_STRID_PLAIN_PAPER 371
#define LV_PLUGIN_STRING_ID_STRID_FAST_PHOTO 372
#define LV_PLUGIN_STRING_ID_STRID_FILE_TYPE 373
#define LV_PLUGIN_STRING_ID_STRID_EXIF_JPEG 374
#define LV_PLUGIN_STRING_ID_STRID_EXIF 375
#define LV_PLUGIN_STRING_ID_STRID_JPEG 376
#define LV_PLUGIN_STRING_ID_STRID_DATE_PRINT 377
#define LV_PLUGIN_STRING_ID_STRID_FILENAME_PRINT 378
#define LV_PLUGIN_STRING_ID_STRID_IMAGE_OPTIMIZE 379
#define LV_PLUGIN_STRING_ID_STRID_LAYOUT 380
#define LV_PLUGIN_STRING_ID_STRID_1UP 381
#define LV_PLUGIN_STRING_ID_STRID_2UP 382
#define LV_PLUGIN_STRING_ID_STRID_3UP 383
#define LV_PLUGIN_STRING_ID_STRID_4UP 384
#define LV_PLUGIN_STRING_ID_STRID_5UP 385
#define LV_PLUGIN_STRING_ID_STRID_6UP 386
#define LV_PLUGIN_STRING_ID_STRID_7UP 387
#define LV_PLUGIN_STRING_ID_STRID_8UP 388
#define LV_PLUGIN_STRING_ID_STRID_9UP 389
#define LV_PLUGIN_STRING_ID_STRID_10UP 390
#define LV_PLUGIN_STRING_ID_STRID_250UP 391
#define LV_PLUGIN_STRING_ID_STRID_INDEX 392
#define LV_PLUGIN_STRING_ID_STRID_1UP_BORDERLESS 393
#define LV_PLUGIN_STRING_ID_STRID_FIXED_SIZE 394
#define LV_PLUGIN_STRING_ID_STRID_25X325 395
#define LV_PLUGIN_STRING_ID_STRID_35X5 396
#define LV_PLUGIN_STRING_ID_STRID_254X178 397
#define LV_PLUGIN_STRING_ID_STRID_110X74 398
#define LV_PLUGIN_STRING_ID_STRID_89X55 399
#define LV_PLUGIN_STRING_ID_STRID_6X8 400
#define LV_PLUGIN_STRING_ID_STRID_7X10 401
#define LV_PLUGIN_STRING_ID_STRID_9X13 402
#define LV_PLUGIN_STRING_ID_STRID_13X18 403
#define LV_PLUGIN_STRING_ID_STRID_15X21 404
#define LV_PLUGIN_STRING_ID_STRID_18X24 405
#define LV_PLUGIN_STRING_ID_STRID_CROPPING 406
#define LV_PLUGIN_STRING_ID_STRID_PRINT_ERROR 407
#define LV_PLUGIN_STRING_ID_STRID_PRINTER_DISCONNECTABLE 408
#define LV_PLUGIN_STRING_ID_STRID_PAPER_ERROR 409
#define LV_PLUGIN_STRING_ID_STRID_PAPER_OUT 410
#define LV_PLUGIN_STRING_ID_STRID_PAPER_LOAD_ERROR 411
#define LV_PLUGIN_STRING_ID_STRID_PAPER_EJECT_ERROR 412
#define LV_PLUGIN_STRING_ID_STRID_PAPER_MEDIA_ERROR 413
#define LV_PLUGIN_STRING_ID_STRID_PAPER_JAMMED 414
#define LV_PLUGIN_STRING_ID_STRID_PAPER_NEAR_EMPTY 415
#define LV_PLUGIN_STRING_ID_STRID_PAPER_NOT_SUPPORT 416
#define LV_PLUGIN_STRING_ID_STRID_INK_ERROR 417
#define LV_PLUGIN_STRING_ID_STRID_INK_EMPTY 418
#define LV_PLUGIN_STRING_ID_STRID_INK_LOW 419
#define LV_PLUGIN_STRING_ID_STRID_INK_WASTE 420
#define LV_PLUGIN_STRING_ID_STRID_HW_ERROR 421
#define LV_PLUGIN_STRING_ID_STRID_HW_FATAL 422
#define LV_PLUGIN_STRING_ID_STRID_HW_SERVICE_CALL 423
#define LV_PLUGIN_STRING_ID_STRID_HW_UNAVAILABLE 424
#define LV_PLUGIN_STRING_ID_STRID_HW_BUSY 425
#define LV_PLUGIN_STRING_ID_STRID_HW_LEVER 426
#define LV_PLUGIN_STRING_ID_STRID_HW_COVER_OPEN 427
#define LV_PLUGIN_STRING_ID_STRID_HW_NO_MARKING_AGENT 428
#define LV_PLUGIN_STRING_ID_STRID_HW_INK_COVER_OPEN 429
#define LV_PLUGIN_STRING_ID_STRID_HW_NO_INK_CARTRIDGE 430
#define LV_PLUGIN_STRING_ID_STRID_FILE_ERROR 431
#define LV_PLUGIN_STRING_ID_STRID_FILE_PRINT_INFO 432
#define LV_PLUGIN_STRING_ID_STRID_FILE_DECODE_ERROR 433
#define LV_PLUGIN_STRING_ID_STRID_UNKNOW_ERROR 434
#define LV_PLUGIN_STRING_ID_STRID_XML_SYNTAX_ERROR 435
#define LV_PLUGIN_STRING_ID_STRID_MOTION_DET 436
#define LV_PLUGIN_STRING_ID_STRID_FACE_DET 437
#define LV_PLUGIN_STRING_ID_STRID_SMILE_DET 438
#define LV_PLUGIN_STRING_ID_STRID_ANTI_SHAKING 439
#define LV_PLUGIN_STRING_ID_STRID_NO_MOVIE 440
#define LV_PLUGIN_STRING_ID_STRID_MP3PLAY 441
#define LV_PLUGIN_STRING_ID_STRID_NO_MP3FILE 442
#define LV_PLUGIN_STRING_ID_STRID_SENSOR_ROTATE 443
#define LV_PLUGIN_STRING_ID_STRID_RECORD 444
#define LV_PLUGIN_STRING_ID_STRID_RECORD_AUDIO 445
#define LV_PLUGIN_STRING_ID_STRID_LED_SETTING 446
#define LV_PLUGIN_STRING_ID_STRID_GOOD_BYE 447
#define LV_PLUGIN_STRING_ID_STRID_PLEASE_INSERT_SD 448
#define LV_PLUGIN_STRING_ID_STRID_IR_LED 449
#define LV_PLUGIN_STRING_ID_STRID_MICROPHONE 450
#define LV_PLUGIN_STRING_ID_STRID_CLUSTER_WRONG 451
#define LV_PLUGIN_STRING_ID_STRID_SD_CLASS6 452
#define LV_PLUGIN_STRING_ID_STRID_SD_CLASS4 453
#define LV_PLUGIN_STRING_ID_STRID_HDR 454
#define LV_PLUGIN_STRING_ID_STRID_TIME_LPASE 455
#define LV_PLUGIN_STRING_ID_STRID_100MS 456
#define LV_PLUGIN_STRING_ID_STRID_200MS 457
#define LV_PLUGIN_STRING_ID_STRID_500MS 458
#define LV_PLUGIN_STRING_ID_STRID_UNDERSCORE 459
#define LV_PLUGIN_STRING_ID_STRID_WIFI 460
#define LV_PLUGIN_STRING_ID_STRID_WIFI_OFF 461
#define LV_PLUGIN_STRING_ID_STRID_REFRESH 462
#define LV_PLUGIN_STRING_ID_STRID_WIFI_AP_MODE 463
#define LV_PLUGIN_STRING_ID_STRID_WIFI_CLIENT_MODE 464
#define LV_PLUGIN_STRING_ID_STRID_FILL_ASCII 465
#define LV_PLUGIN_STRING_ID_STRID_MODE_SWITCH 466
#define LV_PLUGIN_STRING_ID_STRID_2880X2160P24 467
#define LV_PLUGIN_STRING_ID_STRID_2560X1440P30 468
#define LV_PLUGIN_STRING_ID_STRID_2304X1296P30 469
#define LV_PLUGIN_STRING_ID_STRID_1080P96 470
#define LV_PLUGIN_STRING_ID_STRID_1080P60 471
#define LV_PLUGIN_STRING_ID_STRID_1080P_DUAL 472
#define LV_PLUGIN_STRING_ID_STRID_720P120WXH 473
#define LV_PLUGIN_STRING_ID_STRID_WDR 474
#define LV_PLUGIN_STRING_ID_STRID_RSC 475
#define LV_PLUGIN_STRING_ID_STRID_G_SENSOR 476
#define LV_PLUGIN_STRING_ID_STRID_1SEC 477
#define LV_PLUGIN_STRING_ID_STRID_30SEC 478
#define LV_PLUGIN_STRING_ID_STRID_1HOUR 479
#define LV_PLUGIN_STRING_ID_STRID_2HOUR 480
#define LV_PLUGIN_STRING_ID_STRID_3HOUR 481
#define LV_PLUGIN_STRING_ID_STRID_1DAY 482
#define LV_PLUGIN_STRING_ID_STRID_IRCUT 483
#define LV_PLUGIN_STRING_ID_STRID_DUAL_CAM 484
#define LV_PLUGIN_STRING_ID_STRID_FRONT 485
#define LV_PLUGIN_STRING_ID_STRID_BEHIND 486
#define LV_PLUGIN_STRING_ID_STRID_BOTH 487
#define LV_PLUGIN_STRING_ID_STRID_PTZ 488
#define LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_AUTO 489
#define LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_MANUAL 490
#define LV_PLUGIN_STRING_ID_STRID_PIM 491
#define LV_PLUGIN_STRING_ID_STRID_FCW 492
#define LV_PLUGIN_STRING_ID_STRID_LDWS 493
#define LV_PLUGIN_STRING_ID_STRID_DDD 494
#define LV_PLUGIN_STRING_ID_STRID_ADAS 495
#define LV_PLUGIN_STRING_ID_STRID_REC_RECOVERY 496
#define LV_PLUGIN_STRING_ID_STRID_SELFTIMER 497
#define LV_PLUGIN_STRING_ID_STRID_PORTRIAL 498
#define LV_PLUGIN_STRING_ID_STRID_LANDSCPE 499
#define LV_PLUGIN_STRING_ID_STRID_0 500
#define LV_PLUGIN_STRING_ID_STRID_1 501
#define LV_PLUGIN_STRING_ID_STRID_2 502
#define LV_PLUGIN_STRING_ID_STRID_3 503
#define LV_PLUGIN_STRING_ID_STRID_4 504
#define LV_PLUGIN_STRING_ID_STRID_5 505
#define LV_PLUGIN_STRING_ID_STRID_6 506
#define LV_PLUGIN_STRING_ID_STRID_7 507
#define LV_PLUGIN_STRING_ID_STRID_8 508
#define LV_PLUGIN_STRING_ID_STRID_9 509
#define LV_PLUGIN_STRING_ID_STRID_10 510
#define LV_PLUGIN_STRING_ID_STRID_CLOUD 511
#define LV_PLUGIN_STRING_ID_STRID_FW_UPDATE 512
#define LV_PLUGIN_STRING_ID_STRID_UVC 513
#define LV_PLUGIN_STRING_ID_STRID_RESUME 514
#define LV_PLUGIN_STRING_ID_STRID_MCTF 515
#define LV_PLUGIN_STRING_ID_STRID_EDGE 516
#define LV_PLUGIN_STRING_ID_STRID_NR 517
#define LV_PLUGIN_STRING_ID_STRID_WIFI_ETH 518
#define LV_PLUGIN_STRING_ID_STRID_ISO6400 519
#define LV_PLUGIN_STRING_ID_STRID_ISO12800 520
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P50 521
#define LV_PLUGIN_STRING_ID_STRID_FRONT_3840X2160P30 522
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P24 523
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2704X2032P60 524
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P80 525
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P60 526
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P30 527
#define LV_PLUGIN_STRING_ID_STRID_FRONT_2304X1296P30 528
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P120 529
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P96 530
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P60 531
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P30 532
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P240 533
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P120 534
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P60 535
#define LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P30 536
#define LV_PLUGIN_STRING_ID_STRID_FRONT_848X480P30 537
#define LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P240 538
#define LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P30 539
#define LV_PLUGIN_STRING_ID_STRID_FRONT_320X240P30 540
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1280X720P30 541
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1920X1080P30 542
#define LV_PLUGIN_STRING_ID_STRID_DUAL_2304X1296P30_1280X720P30 543
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1080P30_1080P30 544
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_1280X720P30 545
#define LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_848X480P30 546
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1920X1080P30 547
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1280X720P30 548
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2560X1440P30_848X480P30 549
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2304X1296P30_848X480P30 550
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_848X480P30 551
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_640X360P30 552
#define LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_848X480P30 553
#define LV_PLUGIN_STRING_ID_STRID_CLONE_2048X2048P30_480X480P30 554
#define LV_PLUGIN_STRING_ID_STRID_BOTH2 555
#define LV_PLUGIN_STRING_ID_STRID_CAP_SIDE 556
#define LV_PLUGIN_STRING_ID_STRID_CAP_BURST_30 557
#define LV_PLUGIN_STRING_ID_STRID_5MWXH_USR 558
#define LV_PLUGIN_STRING_ID_STRID_CODEC 559
#define LV_PLUGIN_STRING_ID_STRID_MJPG 560
#define LV_PLUGIN_STRING_ID_STRID_H264 561
#define LV_PLUGIN_STRING_ID_STRID_H265 562
#define LV_PLUGIN_STRING_ID_STRID_2880X2160P50 563
#define LV_PLUGIN_STRING_ID_STRID_3840X2160P30 564
#define LV_PLUGIN_STRING_ID_STRID_FRONT_848X480P60 565
#define LV_PLUGIN_STRING_ID_STRID_TRI_1920X1080P30 566
#define LV_PLUGIN_STRING_ID_STRID_TRI_2560X1440P30_1920X1080P30_1920X1080P30 567
#define LV_PLUGIN_STRING_ID_STRID_QUAD_1920X1080P30 568
#define LV_PLUGIN_STRING_ID_STRID_DUAL_3840X2160P30_1920X1080P30 569
#define LV_PLUGIN_STRING_ID_STRID_ETHCAM_RESTART_REC 570
#define LV_PLUGIN_STRING_ID_STRID_ETHCAM_STOP_REC 571
#define LV_PLUGIN_STRING_ID_STRID_ETHCAM_UDFW_SEND 572
#define LV_PLUGIN_STRING_ID_STRID_ETHCAM_UDFW_START 573
#define LV_PLUGIN_STRING_ID_STRID_ETHCAM_UDFW_FINISH 574
#define LV_PLUGIN_STRING_ID_STRID_40M 575
#define LV_PLUGIN_STRING_TABLE_SIZE 576

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