#include "UIFlowLVGL/UIFlowLVGL.h"

#include "Resource/Plugin/lvgl_plugin.h"

#include <stdlib.h>


lv_obj_t *UIFlowMovie;
lv_obj_t *UIFlowPhoto;
lv_obj_t *UIFlowWrnMsg;
lv_obj_t *UIFlowPlay;
lv_obj_t *UIFlowMenuCommonItem;
lv_obj_t *UIFlowMenuCommonOption;
lv_obj_t *UIFlowMenuCommonConfirm;
lv_obj_t *UIFlowWaitMoment;
lv_obj_t *UIFlowSetupDateTime;
lv_obj_t *UIFlowSetupGPS;
lv_obj_t *UIFlowPlayThumb;
lv_obj_t *UIFlowUSB;
lv_obj_t *UIFlowUSBMenu;
lv_obj_t *UIFlowWifiLink;
lv_obj_t *UIFlowWifiLinkOK;
lv_obj_t *UIFlowWifiWait;
lv_obj_t *UIFlowMovieWiFi;
lv_obj_t *UIFlowMenuSetupVersion;


extern lv_plugin_string_t lv_plugin_EN_string_table[];
extern lv_plugin_string_t lv_plugin_FR_string_table[];
extern lv_plugin_string_t lv_plugin_DE_string_table[];
extern lv_plugin_string_t lv_plugin_ES_string_table[];
extern lv_plugin_string_t lv_plugin_IT_string_table[];
extern lv_plugin_string_t lv_plugin_PO_string_table[];
extern lv_plugin_string_t lv_plugin_SC_string_table[];
extern lv_plugin_string_t lv_plugin_JP_string_table[];
extern lv_plugin_string_t lv_plugin_TC_string_table[];
extern lv_plugin_string_t lv_plugin_RU_string_table[];


lv_plugin_img_t lv_plugin_UIFlowLVGL_img_table[] =
{
	{ NULL },
	{ &bye_en },
	{ &bye_jp },
	{ &bye_sc },
	{ &bye_tc },
	{ &icon_0b },
	{ &icon_0r },
	{ &icon_1b },
	{ &icon_1r },
	{ &icon_2b },
	{ &icon_2r },
	{ &icon_3b },
	{ &icon_3r },
	{ &icon_4b },
	{ &icon_4r },
	{ &icon_5b },
	{ &icon_5r },
	{ &icon_6b },
	{ &icon_6r },
	{ &icon_7b },
	{ &icon_7r },
	{ &icon_8b },
	{ &icon_8r },
	{ &icon_9b },
	{ &icon_9r },
	{ &icon_act_push_btn },
	{ &icon_act_release_btn },
	{ &icon_adas_00 },
	{ &icon_adas_01 },
	{ &icon_adas_02 },
	{ &icon_adas_03 },
	{ &icon_adas_04 },
	{ &icon_adas_05 },
	{ &icon_adas_06 },
	{ &icon_adas_07 },
	{ &icon_adas_08 },
	{ &icon_adas_09 },
	{ &icon_adas_animation_01 },
	{ &icon_adas_animation_02 },
	{ &icon_adas_animation_03 },
	{ &icon_adas_animation_04 },
	{ &icon_adas_animation_05 },
	{ &icon_adas_animation_06 },
	{ &icon_adas_animation_07 },
	{ &icon_adas_animation_08 },
	{ &icon_adas_animation_09 },
	{ &icon_adas_animation_10 },
	{ &icon_adas_animation_11 },
	{ &icon_adas_animation_12 },
	{ &icon_adas_animation_13 },
	{ &icon_adas_animation_14 },
	{ &icon_adas_animation_bg },
	{ &icon_adas_cal },
	{ &icon_adas_cal_m },
	{ &icon_adas_car_blue },
	{ &icon_adas_car_red },
	{ &icon_adas_car_white },
	{ &icon_adas_change_lane_left },
	{ &icon_adas_change_lane_right },
	{ &icon_adas_dis_alert },
	{ &icon_adas_dis_seperate },
	{ &icon_adas_front_alert },
	{ &icon_adas_front_car_dis_bg },
	{ &icon_adas_ft },
	{ &icon_adas_go_alert },
	{ &icon_adas_lane_left },
	{ &icon_adas_lane_right },
	{ &icon_adas_off },
	{ &icon_adas_off_m },
	{ &icon_adas_on },
	{ &icon_adas_on_m },
	{ &icon_adas_people_alert },
	{ &icon_adas_rear_alert },
	{ &icon_adas_road },
	{ &icon_adas_road_01 },
	{ &icon_adas_road_02 },
	{ &icon_adas_road_03 },
	{ &icon_adas_road_04 },
	{ &icon_adas_road_05 },
	{ &icon_adas_road_06 },
	{ &icon_adas_virtual_bumper },
	{ &icon_adas_warn_bg },
	{ &icon_ap_machine_off },
	{ &icon_ap_machine_on },
	{ &icon_autoshutdown },
	{ &icon_autoshutdown_10min },
	{ &icon_autoshutdown_3min },
	{ &icon_autoshutdown_5min },
	{ &icon_autoshutdown_m },
	{ &icon_autoshutdown_off },
	{ &icon_auto_1fps },
	{ &icon_auto_1fps1 },
	{ &icon_back },
	{ &icon_backlight },
	{ &icon_backlight_high },
	{ &icon_backlight_low },
	{ &icon_backlight_m },
	{ &icon_backlight_mid },
	{ &icon_backlight_off },
	{ &icon_battery_charge },
	{ &icon_battery_empty },
	{ &icon_battery_full },
	{ &icon_battery_low },
	{ &icon_battery_med },
	{ &icon_battery_type },
	{ &icon_battery_zero },
	{ &icon_bsd_off },
	{ &icon_bsd_off_m },
	{ &icon_bsd_on },
	{ &icon_bsd_on_m },
	{ &icon_btn_emboss },
	{ &icon_bust },
	{ &icon_bust_3shot },
	{ &icon_bust_continue },
	{ &icon_bust_m },
	{ &icon_bust_off },
	{ &icon_camera_mode },
	{ &icon_cam_ptz_off },
	{ &icon_cam_ptz_on },
	{ &icon_cam_ptz_on_m },
	{ &icon_cancel },
	{ &icon_cancel_m },
	{ &icon_car_camera },
	{ &icon_car_no },
	{ &icon_close },
	{ &icon_close_wifi },
	{ &icon_cloud_connected },
	{ &icon_cloud_connected_m },
	{ &icon_cloud_connecting },
	{ &icon_cloud_connecting_m },
	{ &icon_cloud_download1 },
	{ &icon_cloud_download2 },
	{ &icon_cloud_fail },
	{ &icon_cloud_off },
	{ &icon_cloud_off_m },
	{ &icon_cloud_on },
	{ &icon_cloud_on_m },
	{ &icon_cloud_upload1 },
	{ &icon_cloud_upload2 },
	{ &icon_codec_h265 },
	{ &icon_coln },
	{ &icon_color },
	{ &icon_copy_from_card },
	{ &icon_correct },
	{ &icon_cyclic_rec },
	{ &icon_cyclic_rec_10min },
	{ &icon_cyclic_rec_15min },
	{ &icon_cyclic_rec_1min },
	{ &icon_cyclic_rec_2min },
	{ &icon_cyclic_rec_3min },
	{ &icon_cyclic_rec_5min },
	{ &icon_cyclic_rec_m },
	{ &icon_datetime_setup },
	{ &icon_datetime_setup_m },
	{ &icon_date_print },
	{ &icon_date_print_m },
	{ &icon_date_stamping },
	{ &icon_date_time },
	{ &icon_ddd_off },
	{ &icon_ddd_off_m },
	{ &icon_ddd_on },
	{ &icon_ddd_on_m },
	{ &icon_default },
	{ &icon_default_m },
	{ &icon_delete },
	{ &icon_delete_all },
	{ &icon_delete_current },
	{ &icon_delete_m },
	{ &icon_dir_d },
	{ &icon_dir_down },
	{ &icon_dir_l },
	{ &icon_dir_left },
	{ &icon_dir_r },
	{ &icon_dir_right },
	{ &icon_dir_u },
	{ &icon_dir_up },
	{ &icon_dpof },
	{ &icon_dualcam_behind },
	{ &icon_dualcam_both },
	{ &icon_dualcam_both_m },
	{ &icon_dualcam_front },
	{ &icon_edog_00km },
	{ &icon_edog_100km },
	{ &icon_edog_110km },
	{ &icon_edog_120km },
	{ &icon_edog_20km },
	{ &icon_edog_30km },
	{ &icon_edog_40km },
	{ &icon_edog_50km },
	{ &icon_edog_60km },
	{ &icon_edog_70km },
	{ &icon_edog_80km },
	{ &icon_edog_90km },
	{ &icon_edog_average_speed },
	{ &icon_edog_bg },
	{ &icon_edog_captur },
	{ &icon_edog_dis },
	{ &icon_edog_distance },
	{ &icon_edog_km },
	{ &icon_edog_kmh_big },
	{ &icon_edog_kmh_red },
	{ &icon_edog_kmh_small },
	{ &icon_edog_km_small },
	{ &icon_edog_m },
	{ &icon_edog_min_small },
	{ &icon_edog_m_small },
	{ &icon_edog_num_red_0 },
	{ &icon_edog_num_red_1 },
	{ &icon_edog_num_red_2 },
	{ &icon_edog_num_red_3 },
	{ &icon_edog_num_red_4 },
	{ &icon_edog_num_red_5 },
	{ &icon_edog_num_red_6 },
	{ &icon_edog_num_red_7 },
	{ &icon_edog_num_red_8 },
	{ &icon_edog_num_red_9 },
	{ &icon_edog_num_red_small_0 },
	{ &icon_edog_num_red_small_1 },
	{ &icon_edog_num_red_small_2 },
	{ &icon_edog_num_red_small_3 },
	{ &icon_edog_num_red_small_4 },
	{ &icon_edog_num_red_small_5 },
	{ &icon_edog_num_red_small_6 },
	{ &icon_edog_num_red_small_7 },
	{ &icon_edog_num_red_small_8 },
	{ &icon_edog_num_red_small_9 },
	{ &icon_edog_num_yellow_0 },
	{ &icon_edog_num_yellow_1 },
	{ &icon_edog_num_yellow_2 },
	{ &icon_edog_num_yellow_3 },
	{ &icon_edog_num_yellow_4 },
	{ &icon_edog_num_yellow_5 },
	{ &icon_edog_num_yellow_6 },
	{ &icon_edog_num_yellow_7 },
	{ &icon_edog_num_yellow_8 },
	{ &icon_edog_num_yellow_9 },
	{ &icon_edog_num_yellow_small_0 },
	{ &icon_edog_num_yellow_small_1 },
	{ &icon_edog_num_yellow_small_2 },
	{ &icon_edog_num_yellow_small_3 },
	{ &icon_edog_num_yellow_small_4 },
	{ &icon_edog_num_yellow_small_5 },
	{ &icon_edog_num_yellow_small_6 },
	{ &icon_edog_num_yellow_small_7 },
	{ &icon_edog_num_yellow_small_8 },
	{ &icon_edog_num_yellow_small_9 },
	{ &icon_edog_redgreen },
	{ &icon_edog_sec_small },
	{ &icon_edog_time },
	{ &icon_edog_type_accident },
	{ &icon_edog_type_bus },
	{ &icon_edog_type_dawandao },
	{ &icon_edog_type_down_hill },
	{ &icon_edog_type_entry },
	{ &icon_edog_type_exit },
	{ &icon_edog_type_jiaoliudao },
	{ &icon_edog_type_monitor },
	{ &icon_edog_type_no_drinking },
	{ &icon_edog_type_no_left_turn },
	{ &icon_edog_type_no_parking },
	{ &icon_edog_type_oil_station },
	{ &icon_edog_type_police },
	{ &icon_edog_type_school },
	{ &icon_edog_type_service_center },
	{ &icon_edog_type_straight_line },
	{ &icon_edog_type_train_way },
	{ &icon_edog_type_tunnel },
	{ &icon_edog_warn_bg },
	{ &icon_edog_warn_bg_single },
	{ &icon_ev },
	{ &icon_ev_m },
	{ &icon_ev_m0p3 },
	{ &icon_ev_m0p6 },
	{ &icon_ev_m1p0 },
	{ &icon_ev_m1p3 },
	{ &icon_ev_m1p6 },
	{ &icon_ev_m2p0 },
	{ &icon_ev_p0p0 },
	{ &icon_ev_p0p3 },
	{ &icon_ev_p0p6 },
	{ &icon_ev_p1p0 },
	{ &icon_ev_p1p3 },
	{ &icon_ev_p1p6 },
	{ &icon_ev_p2p0 },
	{ &icon_face_off },
	{ &icon_face_on },
	{ &icon_face_on_m },
	{ &icon_fatigue_driving },
	{ &icon_fatigue_driving_alert },
	{ &icon_fb_left },
	{ &icon_fb_left_ori },
	{ &icon_fcw_far_alert },
	{ &icon_fcw_near_alert },
	{ &icon_fcw_off },
	{ &icon_fcw_off_m },
	{ &icon_fcw_on },
	{ &icon_fcw_on_m },
	{ &icon_ff_right },
	{ &icon_ff_right_ori },
	{ &icon_file_lock },
	{ &icon_file_video },
	{ &icon_firmware_update },
	{ &icon_firmware_update_m },
	{ &icon_flash_auto },
	{ &icon_flash_off },
	{ &icon_flash_on },
	{ &icon_flash_on_m },
	{ &icon_flash_rec },
	{ &icon_flash_rec_m },
	{ &icon_flash_red_eye },
	{ &icon_flick_50hz },
	{ &icon_flick_60hz },
	{ &icon_format },
	{ &icon_format_m },
	{ &icon_golf_rec },
	{ &icon_golf_rec_m },
	{ &icon_gps },
	{ &icon_gps_off },
	{ &icon_gps_on },
	{ &icon_gps_on_m },
	{ &icon_gsensor },
	{ &icon_g_sensor },
	{ &icon_g_sensor_high },
	{ &icon_g_sensor_low },
	{ &icon_g_sensor_m },
	{ &icon_g_sensor_mid },
	{ &icon_g_sensor_off },
	{ &icon_hdr },
	{ &icon_hdr_m },
	{ &icon_hdr_off },
	{ &icon_help },
	{ &icon_help_m },
	{ &icon_hint_bar },
	{ &icon_hz },
	{ &icon_hz_50 },
	{ &icon_hz_60 },
	{ &icon_hz_m },
	{ &icon_info },
	{ &icon_info_m },
	{ &icon_internal_flash },
	{ &icon_ircut_auto },
	{ &icon_ircut_off },
	{ &icon_ircut_on_m },
	{ &icon_iso },
	{ &icon_iso_100 },
	{ &icon_iso_1600 },
	{ &icon_iso_200 },
	{ &icon_iso_400 },
	{ &icon_iso_800 },
	{ &icon_iso_auto },
	{ &icon_iso_m },
	{ &icon_landscape },
	{ &icon_language },
	{ &icon_language_m },
	{ &icon_ldws_left_alert },
	{ &icon_ldws_off },
	{ &icon_ldws_off_m },
	{ &icon_ldws_on },
	{ &icon_ldws_on_m },
	{ &icon_ldws_right_alert },
	{ &icon_led_det },
	{ &icon_local_station__off },
	{ &icon_local_station__on },
	{ &icon_lock },
	{ &icon_lock_all },
	{ &icon_lock_all_m },
	{ &icon_lock_current },
	{ &icon_lock_current_m },
	{ &icon_lock_m },
	{ &icon_lock_unlock },
	{ &icon_lock_unlock_m },
	{ &icon_lock_unlokc_all },
	{ &icon_lock_unlokc_all_m },
	{ &icon_lpr_off },
	{ &icon_lpr_off_m },
	{ &icon_lpr_on },
	{ &icon_lpr_on_m },
	{ &icon_menu_flash_rec },
	{ &icon_menu_hdr },
	{ &icon_menu_modechang },
	{ &icon_menu_modechang_m },
	{ &icon_menu_playback_off },
	{ &icon_menu_playback_on },
	{ &icon_menu_print_off },
	{ &icon_menu_return },
	{ &icon_menu_return_m },
	{ &icon_menu_setup_off },
	{ &icon_menu_setup_on },
	{ &icon_menu_setup_on_m },
	{ &icon_menu_still_off },
	{ &icon_menu_still_on },
	{ &icon_menu_underbar },
	{ &icon_menu_video_off },
	{ &icon_menu_video_on },
	{ &icon_menu_wdr },
	{ &icon_menu_wdr_m },
	{ &icon_menu_wdr_off },
	{ &icon_metering },
	{ &icon_metering_m },
	{ &icon_mode_capture },
	{ &icon_mode_capture_m },
	{ &icon_mode_playback },
	{ &icon_mode_playback_m },
	{ &icon_mode_video },
	{ &icon_mode_video_m },
	{ &icon_motion_det_off },
	{ &icon_motion_det_on },
	{ &icon_motion_det_on_m },
	{ &icon_movie_menu_waring },
	{ &icon_no },
	{ &icon_no_m },
	{ &icon_ok },
	{ &icon_ok2 },
	{ &icon_ok_m },
	{ &icon_ok_m_2 },
	{ &icon_ok_pause },
	{ &icon_ok_play },
	{ &icon_ok_s },
	{ &icon_parkingmode_gsensor },
	{ &icon_parkingmode_lb },
	{ &icon_parkingmode_md },
	{ &icon_parkingmode_tl },
	{ &icon_pause },
	{ &icon_pd_off },
	{ &icon_pd_off_m },
	{ &icon_pd_on },
	{ &icon_pd_on_m },
	{ &icon_pictbridge_s },
	{ &icon_pim_off },
	{ &icon_pim_off_m },
	{ &icon_pim_on },
	{ &icon_pim_on_m },
	{ &icon_play },
	{ &icon_play_backward },
	{ &icon_play_ff_b },
	{ &icon_play_ff_f },
	{ &icon_play_forward },
	{ &icon_play_pause },
	{ &icon_play_play },
	{ &icon_play_step },
	{ &icon_play_stop },
	{ &icon_power_off },
	{ &icon_power_off_m },
	{ &icon_print },
	{ &icon_protect },
	{ &icon_protect_m },
	{ &icon_quality },
	{ &icon_quality_basic },
	{ &icon_quality_fine },
	{ &icon_quality_m },
	{ &icon_quality_normal },
	{ &icon_quick_review },
	{ &icon_quick_review_m },
	{ &icon_rec_elippse },
	{ &icon_rec_ellipse },
	{ &icon_rec_recovery },
	{ &icon_rec_transpaent },
	{ &icon_remind_light },
	{ &icon_remind_light_alert },
	{ &icon_resolution },
	{ &icon_resolution_m },
	{ &icon_rotate },
	{ &icon_rsc_off },
	{ &icon_rsc_on },
	{ &icon_rsc_on_m },
	{ &icon_scene_mode },
	{ &icon_scene_mode_auto },
	{ &icon_scene_mode_landscpe },
	{ &icon_scene_mode_m },
	{ &icon_scene_mode_portrial },
	{ &icon_screensaver },
	{ &icon_screensaver_10min },
	{ &icon_screensaver_3min },
	{ &icon_screensaver_5min },
	{ &icon_screensaver_m },
	{ &icon_screensaver_off },
	{ &icon_screen_saver },
	{ &icon_sd_card },
	{ &icon_sd_lock },
	{ &icon_selftimer },
	{ &icon_selftimer_10sec },
	{ &icon_selftimer_2sec },
	{ &icon_selftimer_5sec },
	{ &icon_selftimer_m },
	{ &icon_selftimer_off },
	{ &icon_sel_bar },
	{ &icon_sel_bar_begin },
	{ &icon_sel_bar_carno },
	{ &icon_sel_bar_date },
	{ &icon_sel_bar_end },
	{ &icon_sel_bar_item },
	{ &icon_sel_bar_med },
	{ &icon_sel_bar_year },
	{ &icon_sel_focus },
	{ &icon_sequence_no },
	{ &icon_set },
	{ &icon_set_lock },
	{ &icon_shake_off },
	{ &icon_shake_on },
	{ &icon_shake_on_m },
	{ &icon_sharpness },
	{ &icon_sharpness_high },
	{ &icon_sharpness_low },
	{ &icon_sharpness_m },
	{ &icon_sharpness_med },
	{ &icon_signal_0step },
	{ &icon_signal_0step_m },
	{ &icon_signal_1step },
	{ &icon_signal_1step_m },
	{ &icon_signal_2step },
	{ &icon_signal_2step_m },
	{ &icon_slideshow },
	{ &icon_slideshow_2sec },
	{ &icon_slideshow_5sec },
	{ &icon_slideshow_8sec },
	{ &icon_slideshow_m },
	{ &icon_slideshow_off },
	{ &icon_slide_show },
	{ &icon_smile },
	{ &icon_smile_m },
	{ &icon_sng },
	{ &icon_sng_alert },
	{ &icon_sng_alert_ori },
	{ &icon_sng_off },
	{ &icon_sng_off_m },
	{ &icon_sng_on },
	{ &icon_sng_on_m },
	{ &icon_sound_rec_off },
	{ &icon_sound_rec_on },
	{ &icon_sound_rec_on_m },
	{ &icon_speaker },
	{ &icon_ssid },
	{ &icon_sys_cal },
	{ &icon_sys_cal_m },
	{ &icon_time_lapse_off },
	{ &icon_time_lapse_on },
	{ &icon_time_lapse_on_m },
	{ &icon_title_bar },
	{ &icon_tsr },
	{ &icon_tsr_off },
	{ &icon_tsr_off_m },
	{ &icon_tsr_on },
	{ &icon_tsr_on_m },
	{ &icon_tv_mode },
	{ &icon_tv_mode_m },
	{ &icon_tv_ntsc },
	{ &icon_tv_pal },
	{ &icon_urgent_protect_auto },
	{ &icon_urgent_protect_auto_m },
	{ &icon_urgent_protect_manual },
	{ &icon_urgent_protect_manual_m },
	{ &icon_usb },
	{ &icon_usb_msdc },
	{ &icon_usb_off },
	{ &icon_usb_on },
	{ &icon_usb_on_m },
	{ &icon_usb_uvc },
	{ &icon_u_stop_ori },
	{ &icon_version },
	{ &icon_version_m },
	{ &icon_video_flip_off },
	{ &icon_video_flip_on },
	{ &icon_video_flip_on_m },
	{ &icon_voice },
	{ &icon_voice_m },
	{ &icon_voice_off },
	{ &icon_voice_on },
	{ &icon_vol_0 },
	{ &icon_vol_1 },
	{ &icon_vol_2 },
	{ &icon_waring },
	{ &icon_waring_big },
	{ &icon_warn_movie_capture },
	{ &icon_wb },
	{ &icon_wb_auto },
	{ &icon_wb_cloudy },
	{ &icon_wb_daylight },
	{ &icon_wb_fluorescent },
	{ &icon_wb_m },
	{ &icon_wb_tungsten },
	{ &icon_wdr },
	{ &icon_wifi },
	{ &icon_wifi_android },
	{ &icon_wifi_app_connected },
	{ &icon_wifi_connect },
	{ &icon_wifi_connected },
	{ &icon_wifi_connected_small },
	{ &icon_wifi_connecting1 },
	{ &icon_wifi_connecting2 },
	{ &icon_wifi_connecting3 },
	{ &icon_wifi_disconnected },
	{ &icon_wifi_dot_connecting_off },
	{ &icon_wifi_dot_connecting_on },
	{ &icon_wifi_fail },
	{ &icon_wifi_ios },
	{ &icon_wifi_off },
	{ &icon_wifi_off_m },
	{ &icon_wifi_on },
	{ &icon_wifi_on_m },
	{ &icon_yes },
	{ &icon_yes_m },
	{ &icon__empty },
	{ &icon_gps_err },
	{ &icon_gps_ok },
	{ &open_aukey },
	{ &open_en },
	{ &open_jp },
	{ &open_papago },
	{ &open_sc },
	{ &open_tc },
	{ &_100 },
	{ &_110 },
	{ &_120 },
	{ &_30 },
	{ &_40 },
	{ &_50 },
	{ &_60 },
	{ &_70 },
	{ &_80 },
	{ &_90 },
	{ &off_1 },
	{ &off_10 },
	{ &off_10_en },
	{ &off_10_sc },
	{ &off_1_en },
	{ &off_1_sc },
	{ &off_2 },
	{ &off_2_en },
	{ &off_2_sc },
	{ &off_3 },
	{ &off_3_en },
	{ &off_3_sc },
	{ &off_4 },
	{ &off_4_en },
	{ &off_4_sc },
	{ &off_5 },
	{ &off_5_en },
	{ &off_5_sc },
	{ &off_6 },
	{ &off_6_en },
	{ &off_6_sc },
	{ &off_7 },
	{ &off_7_en },
	{ &off_7_sc },
	{ &off_8 },
	{ &off_8_en },
	{ &off_8_sc },
	{ &off_9 },
	{ &off_9_en },
	{ &off_9_sc },
};

lv_plugin_font_t lv_plugin_UIFlowLVGL_font_table[] =
{
	{ NULL },

#if LV_FONT_MONTSERRAT_16
	{ &lv_font_montserrat_16 },
#else
	{ NULL },
#endif


#if LV_FONT_DEJAVU_16_PERSIAN_HEBREW
	{ &lv_font_dejavu_persian_hebrew_16 },
#else
	{ NULL },
#endif

	{ &notosans_black_32_1bpp },
	{ &notosans_black_48_1bpp },
	{ &notosans_black_64_1bpp },
	{ &notosans_black_128_1bpp },
};

lv_plugin_string_t* lv_plugin_language_table[] = {
	NULL,
	lv_plugin_EN_string_table,
	lv_plugin_FR_string_table,
	lv_plugin_DE_string_table,
	lv_plugin_ES_string_table,
	lv_plugin_IT_string_table,
	lv_plugin_PO_string_table,
	lv_plugin_SC_string_table,
	lv_plugin_JP_string_table,
	lv_plugin_TC_string_table,
	lv_plugin_RU_string_table,
};

lv_plugin_res_id lv_plugin_language_font_table_EN[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_FR[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_DE[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_ES[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_IT[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_PO[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_SC[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_JP[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_TC[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id lv_plugin_language_font_table_RU[] = {
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
	LV_PLUGIN_FONT_ID_LV_FONT_MONTSERRAT_16,
};

lv_plugin_res_id* lv_plugin_language_fonts_table[] = {
	NULL,
	lv_plugin_language_font_table_EN,
	lv_plugin_language_font_table_FR,
	lv_plugin_language_font_table_DE,
	lv_plugin_language_font_table_ES,
	lv_plugin_language_font_table_IT,
	lv_plugin_language_font_table_PO,
	lv_plugin_language_font_table_SC,
	lv_plugin_language_font_table_JP,
	lv_plugin_language_font_table_TC,
	lv_plugin_language_font_table_RU,
};

lv_plugin_res_id lv_plugin_fixed_language_string_id_table[] = {
	LV_PLUGIN_RES_ID_NONE, /* 0*/
	LV_PLUGIN_RES_ID_NONE, /* 1*/
	LV_PLUGIN_RES_ID_NONE, /* 2*/
	LV_PLUGIN_RES_ID_NONE, /* 3*/
	LV_PLUGIN_RES_ID_NONE, /* 4*/
	LV_PLUGIN_RES_ID_NONE, /* 5*/
	LV_PLUGIN_RES_ID_NONE, /* 6*/
	LV_PLUGIN_RES_ID_NONE, /* 7*/
	LV_PLUGIN_RES_ID_NONE, /* 8*/
	LV_PLUGIN_RES_ID_NONE, /* 9*/
	LV_PLUGIN_RES_ID_NONE, /* 10*/
	LV_PLUGIN_RES_ID_NONE, /* 11*/
	LV_PLUGIN_RES_ID_NONE, /* 12*/
	LV_PLUGIN_RES_ID_NONE, /* 13*/
	LV_PLUGIN_RES_ID_NONE, /* 14*/
	LV_PLUGIN_RES_ID_NONE, /* 15*/
	LV_PLUGIN_RES_ID_NONE, /* 16*/
	LV_PLUGIN_RES_ID_NONE, /* 17*/
	LV_PLUGIN_RES_ID_NONE, /* 18*/
	LV_PLUGIN_RES_ID_NONE, /* 19*/
	LV_PLUGIN_RES_ID_NONE, /* 20*/
	LV_PLUGIN_RES_ID_NONE, /* 21*/
	LV_PLUGIN_RES_ID_NONE, /* 22*/
	LV_PLUGIN_RES_ID_NONE, /* 23*/
	LV_PLUGIN_RES_ID_NONE, /* 24*/
	LV_PLUGIN_RES_ID_NONE, /* 25*/
	LV_PLUGIN_RES_ID_NONE, /* 26*/
	LV_PLUGIN_RES_ID_NONE, /* 27*/
	LV_PLUGIN_RES_ID_NONE, /* 28*/
	LV_PLUGIN_RES_ID_NONE, /* 29*/
	LV_PLUGIN_RES_ID_NONE, /* 30*/
	LV_PLUGIN_RES_ID_NONE, /* 31*/
	LV_PLUGIN_RES_ID_NONE, /* 32*/
	LV_PLUGIN_RES_ID_NONE, /* 33*/
	LV_PLUGIN_RES_ID_NONE, /* 34*/
	LV_PLUGIN_RES_ID_NONE, /* 35*/
	LV_PLUGIN_RES_ID_NONE, /* 36*/
	LV_PLUGIN_RES_ID_NONE, /* 37*/
	LV_PLUGIN_RES_ID_NONE, /* 38*/
	LV_PLUGIN_RES_ID_NONE, /* 39*/
	LV_PLUGIN_RES_ID_NONE, /* 40*/
	LV_PLUGIN_RES_ID_NONE, /* 41*/
	LV_PLUGIN_RES_ID_NONE, /* 42*/
	LV_PLUGIN_RES_ID_NONE, /* 43*/
	LV_PLUGIN_RES_ID_NONE, /* 44*/
	LV_PLUGIN_RES_ID_NONE, /* 45*/
	LV_PLUGIN_RES_ID_NONE, /* 46*/
	LV_PLUGIN_RES_ID_NONE, /* 47*/
	LV_PLUGIN_RES_ID_NONE, /* 48*/
	LV_PLUGIN_RES_ID_NONE, /* 49*/
	LV_PLUGIN_RES_ID_NONE, /* 50*/
	LV_PLUGIN_RES_ID_NONE, /* 51*/
	LV_PLUGIN_RES_ID_NONE, /* 52*/
	LV_PLUGIN_RES_ID_NONE, /* 53*/
	LV_PLUGIN_RES_ID_NONE, /* 54*/
	LV_PLUGIN_RES_ID_NONE, /* 55*/
	LV_PLUGIN_RES_ID_NONE, /* 56*/
	LV_PLUGIN_RES_ID_NONE, /* 57*/
	LV_PLUGIN_RES_ID_NONE, /* 58*/
	LV_PLUGIN_RES_ID_NONE, /* 59*/
	LV_PLUGIN_RES_ID_NONE, /* 60*/
	LV_PLUGIN_RES_ID_NONE, /* 61*/
	LV_PLUGIN_RES_ID_NONE, /* 62*/
	LV_PLUGIN_RES_ID_NONE, /* 63*/
	LV_PLUGIN_RES_ID_NONE, /* 64*/
	LV_PLUGIN_RES_ID_NONE, /* 65*/
	LV_PLUGIN_RES_ID_NONE, /* 66*/
	LV_PLUGIN_RES_ID_NONE, /* 67*/
	LV_PLUGIN_RES_ID_NONE, /* 68*/
	LV_PLUGIN_RES_ID_NONE, /* 69*/
	LV_PLUGIN_RES_ID_NONE, /* 70*/
	LV_PLUGIN_RES_ID_NONE, /* 71*/
	LV_PLUGIN_RES_ID_NONE, /* 72*/
	LV_PLUGIN_RES_ID_NONE, /* 73*/
	LV_PLUGIN_RES_ID_NONE, /* 74*/
	LV_PLUGIN_RES_ID_NONE, /* 75*/
	LV_PLUGIN_RES_ID_NONE, /* 76*/
	LV_PLUGIN_RES_ID_NONE, /* 77*/
	LV_PLUGIN_RES_ID_NONE, /* 78*/
	LV_PLUGIN_RES_ID_NONE, /* 79*/
	LV_PLUGIN_RES_ID_NONE, /* 80*/
	LV_PLUGIN_RES_ID_NONE, /* 81*/
	LV_PLUGIN_RES_ID_NONE, /* 82*/
	LV_PLUGIN_RES_ID_NONE, /* 83*/
	LV_PLUGIN_RES_ID_NONE, /* 84*/
	LV_PLUGIN_RES_ID_NONE, /* 85*/
	LV_PLUGIN_RES_ID_NONE, /* 86*/
	LV_PLUGIN_RES_ID_NONE, /* 87*/
	LV_PLUGIN_RES_ID_NONE, /* 88*/
	LV_PLUGIN_RES_ID_NONE, /* 89*/
	LV_PLUGIN_RES_ID_NONE, /* 90*/
	LV_PLUGIN_RES_ID_NONE, /* 91*/
	LV_PLUGIN_RES_ID_NONE, /* 92*/
	LV_PLUGIN_RES_ID_NONE, /* 93*/
	LV_PLUGIN_RES_ID_NONE, /* 94*/
	LV_PLUGIN_RES_ID_NONE, /* 95*/
	LV_PLUGIN_RES_ID_NONE, /* 96*/
	LV_PLUGIN_RES_ID_NONE, /* 97*/
	LV_PLUGIN_RES_ID_NONE, /* 98*/
	LV_PLUGIN_RES_ID_NONE, /* 99*/
	LV_PLUGIN_RES_ID_NONE, /* 100*/
	LV_PLUGIN_RES_ID_NONE, /* 101*/
	LV_PLUGIN_RES_ID_NONE, /* 102*/
	LV_PLUGIN_RES_ID_NONE, /* 103*/
	LV_PLUGIN_RES_ID_NONE, /* 104*/
	LV_PLUGIN_RES_ID_NONE, /* 105*/
	LV_PLUGIN_RES_ID_NONE, /* 106*/
	LV_PLUGIN_RES_ID_NONE, /* 107*/
	LV_PLUGIN_RES_ID_NONE, /* 108*/
	LV_PLUGIN_RES_ID_NONE, /* 109*/
	LV_PLUGIN_RES_ID_NONE, /* 110*/
	LV_PLUGIN_RES_ID_NONE, /* 111*/
	LV_PLUGIN_RES_ID_NONE, /* 112*/
	LV_PLUGIN_RES_ID_NONE, /* 113*/
	LV_PLUGIN_RES_ID_NONE, /* 114*/
	LV_PLUGIN_RES_ID_NONE, /* 115*/
	LV_PLUGIN_RES_ID_NONE, /* 116*/
	LV_PLUGIN_RES_ID_NONE, /* 117*/
	LV_PLUGIN_RES_ID_NONE, /* 118*/
	LV_PLUGIN_RES_ID_NONE, /* 119*/
	LV_PLUGIN_RES_ID_NONE, /* 120*/
	LV_PLUGIN_RES_ID_NONE, /* 121*/
	LV_PLUGIN_RES_ID_NONE, /* 122*/
	LV_PLUGIN_RES_ID_NONE, /* 123*/
	LV_PLUGIN_RES_ID_NONE, /* 124*/
	LV_PLUGIN_RES_ID_NONE, /* 125*/
	LV_PLUGIN_RES_ID_NONE, /* 126*/
	LV_PLUGIN_RES_ID_NONE, /* 127*/
	LV_PLUGIN_RES_ID_NONE, /* 128*/
	LV_PLUGIN_RES_ID_NONE, /* 129*/
	LV_PLUGIN_RES_ID_NONE, /* 130*/
	LV_PLUGIN_RES_ID_NONE, /* 131*/
	LV_PLUGIN_RES_ID_NONE, /* 132*/
	LV_PLUGIN_RES_ID_NONE, /* 133*/
	LV_PLUGIN_RES_ID_NONE, /* 134*/
	LV_PLUGIN_RES_ID_NONE, /* 135*/
	LV_PLUGIN_RES_ID_NONE, /* 136*/
	LV_PLUGIN_RES_ID_NONE, /* 137*/
	LV_PLUGIN_RES_ID_NONE, /* 138*/
	LV_PLUGIN_RES_ID_NONE, /* 139*/
	LV_PLUGIN_RES_ID_NONE, /* 140*/
	LV_PLUGIN_RES_ID_NONE, /* 141*/
	LV_PLUGIN_RES_ID_NONE, /* 142*/
	LV_PLUGIN_RES_ID_NONE, /* 143*/
	LV_PLUGIN_RES_ID_NONE, /* 144*/
	LV_PLUGIN_LANGUAGE_ID_EN, /* 145*/
	LV_PLUGIN_LANGUAGE_ID_FR, /* 146*/
	LV_PLUGIN_LANGUAGE_ID_ES, /* 147*/
	LV_PLUGIN_LANGUAGE_ID_DE, /* 148*/
	LV_PLUGIN_LANGUAGE_ID_IT, /* 149*/
	LV_PLUGIN_LANGUAGE_ID_TC, /* 150*/
	LV_PLUGIN_LANGUAGE_ID_SC, /* 151*/
	LV_PLUGIN_LANGUAGE_ID_JP, /* 152*/
	LV_PLUGIN_LANGUAGE_ID_PO, /* 153*/
	LV_PLUGIN_LANGUAGE_ID_RU, /* 154*/
	LV_PLUGIN_RES_ID_NONE, /* 155*/
	LV_PLUGIN_RES_ID_NONE, /* 156*/
	LV_PLUGIN_RES_ID_NONE, /* 157*/
	LV_PLUGIN_RES_ID_NONE, /* 158*/
	LV_PLUGIN_RES_ID_NONE, /* 159*/
	LV_PLUGIN_RES_ID_NONE, /* 160*/
	LV_PLUGIN_RES_ID_NONE, /* 161*/
	LV_PLUGIN_RES_ID_NONE, /* 162*/
	LV_PLUGIN_RES_ID_NONE, /* 163*/
	LV_PLUGIN_RES_ID_NONE, /* 164*/
	LV_PLUGIN_RES_ID_NONE, /* 165*/
	LV_PLUGIN_RES_ID_NONE, /* 166*/
	LV_PLUGIN_RES_ID_NONE, /* 167*/
	LV_PLUGIN_RES_ID_NONE, /* 168*/
	LV_PLUGIN_RES_ID_NONE, /* 169*/
	LV_PLUGIN_RES_ID_NONE, /* 170*/
	LV_PLUGIN_RES_ID_NONE, /* 171*/
	LV_PLUGIN_RES_ID_NONE, /* 172*/
	LV_PLUGIN_RES_ID_NONE, /* 173*/
	LV_PLUGIN_RES_ID_NONE, /* 174*/
	LV_PLUGIN_RES_ID_NONE, /* 175*/
	LV_PLUGIN_RES_ID_NONE, /* 176*/
	LV_PLUGIN_RES_ID_NONE, /* 177*/
	LV_PLUGIN_RES_ID_NONE, /* 178*/
	LV_PLUGIN_RES_ID_NONE, /* 179*/
	LV_PLUGIN_RES_ID_NONE, /* 180*/
	LV_PLUGIN_RES_ID_NONE, /* 181*/
	LV_PLUGIN_RES_ID_NONE, /* 182*/
	LV_PLUGIN_RES_ID_NONE, /* 183*/
	LV_PLUGIN_RES_ID_NONE, /* 184*/
	LV_PLUGIN_RES_ID_NONE, /* 185*/
	LV_PLUGIN_RES_ID_NONE, /* 186*/
	LV_PLUGIN_RES_ID_NONE, /* 187*/
	LV_PLUGIN_RES_ID_NONE, /* 188*/
	LV_PLUGIN_RES_ID_NONE, /* 189*/
	LV_PLUGIN_RES_ID_NONE, /* 190*/
	LV_PLUGIN_RES_ID_NONE, /* 191*/
	LV_PLUGIN_RES_ID_NONE, /* 192*/
	LV_PLUGIN_RES_ID_NONE, /* 193*/
	LV_PLUGIN_RES_ID_NONE, /* 194*/
	LV_PLUGIN_RES_ID_NONE, /* 195*/
	LV_PLUGIN_RES_ID_NONE, /* 196*/
	LV_PLUGIN_RES_ID_NONE, /* 197*/
	LV_PLUGIN_RES_ID_NONE, /* 198*/
	LV_PLUGIN_RES_ID_NONE, /* 199*/
	LV_PLUGIN_RES_ID_NONE, /* 200*/
	LV_PLUGIN_RES_ID_NONE, /* 201*/
	LV_PLUGIN_RES_ID_NONE, /* 202*/
	LV_PLUGIN_RES_ID_NONE, /* 203*/
	LV_PLUGIN_RES_ID_NONE, /* 204*/
	LV_PLUGIN_RES_ID_NONE, /* 205*/
	LV_PLUGIN_RES_ID_NONE, /* 206*/
	LV_PLUGIN_RES_ID_NONE, /* 207*/
	LV_PLUGIN_RES_ID_NONE, /* 208*/
	LV_PLUGIN_RES_ID_NONE, /* 209*/
	LV_PLUGIN_RES_ID_NONE, /* 210*/
	LV_PLUGIN_RES_ID_NONE, /* 211*/
	LV_PLUGIN_RES_ID_NONE, /* 212*/
	LV_PLUGIN_RES_ID_NONE, /* 213*/
	LV_PLUGIN_RES_ID_NONE, /* 214*/
	LV_PLUGIN_RES_ID_NONE, /* 215*/
	LV_PLUGIN_RES_ID_NONE, /* 216*/
	LV_PLUGIN_RES_ID_NONE, /* 217*/
	LV_PLUGIN_RES_ID_NONE, /* 218*/
	LV_PLUGIN_RES_ID_NONE, /* 219*/
	LV_PLUGIN_RES_ID_NONE, /* 220*/
	LV_PLUGIN_RES_ID_NONE, /* 221*/
	LV_PLUGIN_RES_ID_NONE, /* 222*/
	LV_PLUGIN_RES_ID_NONE, /* 223*/
	LV_PLUGIN_RES_ID_NONE, /* 224*/
	LV_PLUGIN_RES_ID_NONE, /* 225*/
	LV_PLUGIN_RES_ID_NONE, /* 226*/
	LV_PLUGIN_RES_ID_NONE, /* 227*/
	LV_PLUGIN_RES_ID_NONE, /* 228*/
	LV_PLUGIN_RES_ID_NONE, /* 229*/
	LV_PLUGIN_RES_ID_NONE, /* 230*/
	LV_PLUGIN_RES_ID_NONE, /* 231*/
	LV_PLUGIN_RES_ID_NONE, /* 232*/
	LV_PLUGIN_RES_ID_NONE, /* 233*/
	LV_PLUGIN_RES_ID_NONE, /* 234*/
	LV_PLUGIN_RES_ID_NONE, /* 235*/
	LV_PLUGIN_RES_ID_NONE, /* 236*/
	LV_PLUGIN_RES_ID_NONE, /* 237*/
	LV_PLUGIN_RES_ID_NONE, /* 238*/
	LV_PLUGIN_RES_ID_NONE, /* 239*/
	LV_PLUGIN_RES_ID_NONE, /* 240*/
	LV_PLUGIN_RES_ID_NONE, /* 241*/
	LV_PLUGIN_RES_ID_NONE, /* 242*/
	LV_PLUGIN_RES_ID_NONE, /* 243*/
	LV_PLUGIN_RES_ID_NONE, /* 244*/
	LV_PLUGIN_RES_ID_NONE, /* 245*/
	LV_PLUGIN_RES_ID_NONE, /* 246*/
	LV_PLUGIN_RES_ID_NONE, /* 247*/
	LV_PLUGIN_RES_ID_NONE, /* 248*/
	LV_PLUGIN_RES_ID_NONE, /* 249*/
	LV_PLUGIN_RES_ID_NONE, /* 250*/
	LV_PLUGIN_RES_ID_NONE, /* 251*/
	LV_PLUGIN_RES_ID_NONE, /* 252*/
	LV_PLUGIN_RES_ID_NONE, /* 253*/
	LV_PLUGIN_RES_ID_NONE, /* 254*/
	LV_PLUGIN_RES_ID_NONE, /* 255*/
	LV_PLUGIN_RES_ID_NONE, /* 256*/
	LV_PLUGIN_RES_ID_NONE, /* 257*/
	LV_PLUGIN_RES_ID_NONE, /* 258*/
	LV_PLUGIN_RES_ID_NONE, /* 259*/
	LV_PLUGIN_RES_ID_NONE, /* 260*/
	LV_PLUGIN_RES_ID_NONE, /* 261*/
	LV_PLUGIN_RES_ID_NONE, /* 262*/
	LV_PLUGIN_RES_ID_NONE, /* 263*/
	LV_PLUGIN_RES_ID_NONE, /* 264*/
	LV_PLUGIN_RES_ID_NONE, /* 265*/
	LV_PLUGIN_RES_ID_NONE, /* 266*/
	LV_PLUGIN_RES_ID_NONE, /* 267*/
	LV_PLUGIN_RES_ID_NONE, /* 268*/
	LV_PLUGIN_RES_ID_NONE, /* 269*/
	LV_PLUGIN_RES_ID_NONE, /* 270*/
	LV_PLUGIN_RES_ID_NONE, /* 271*/
	LV_PLUGIN_RES_ID_NONE, /* 272*/
	LV_PLUGIN_RES_ID_NONE, /* 273*/
	LV_PLUGIN_RES_ID_NONE, /* 274*/
	LV_PLUGIN_RES_ID_NONE, /* 275*/
	LV_PLUGIN_RES_ID_NONE, /* 276*/
	LV_PLUGIN_RES_ID_NONE, /* 277*/
	LV_PLUGIN_RES_ID_NONE, /* 278*/
	LV_PLUGIN_RES_ID_NONE, /* 279*/
	LV_PLUGIN_RES_ID_NONE, /* 280*/
	LV_PLUGIN_RES_ID_NONE, /* 281*/
	LV_PLUGIN_RES_ID_NONE, /* 282*/
	LV_PLUGIN_RES_ID_NONE, /* 283*/
	LV_PLUGIN_RES_ID_NONE, /* 284*/
	LV_PLUGIN_RES_ID_NONE, /* 285*/
	LV_PLUGIN_RES_ID_NONE, /* 286*/
	LV_PLUGIN_RES_ID_NONE, /* 287*/
	LV_PLUGIN_RES_ID_NONE, /* 288*/
	LV_PLUGIN_RES_ID_NONE, /* 289*/
	LV_PLUGIN_RES_ID_NONE, /* 290*/
	LV_PLUGIN_RES_ID_NONE, /* 291*/
	LV_PLUGIN_RES_ID_NONE, /* 292*/
	LV_PLUGIN_RES_ID_NONE, /* 293*/
	LV_PLUGIN_RES_ID_NONE, /* 294*/
	LV_PLUGIN_RES_ID_NONE, /* 295*/
	LV_PLUGIN_RES_ID_NONE, /* 296*/
	LV_PLUGIN_RES_ID_NONE, /* 297*/
	LV_PLUGIN_RES_ID_NONE, /* 298*/
	LV_PLUGIN_RES_ID_NONE, /* 299*/
	LV_PLUGIN_RES_ID_NONE, /* 300*/
	LV_PLUGIN_RES_ID_NONE, /* 301*/
	LV_PLUGIN_RES_ID_NONE, /* 302*/
	LV_PLUGIN_RES_ID_NONE, /* 303*/
	LV_PLUGIN_RES_ID_NONE, /* 304*/
	LV_PLUGIN_RES_ID_NONE, /* 305*/
	LV_PLUGIN_RES_ID_NONE, /* 306*/
	LV_PLUGIN_RES_ID_NONE, /* 307*/
	LV_PLUGIN_RES_ID_NONE, /* 308*/
	LV_PLUGIN_RES_ID_NONE, /* 309*/
	LV_PLUGIN_RES_ID_NONE, /* 310*/
	LV_PLUGIN_RES_ID_NONE, /* 311*/
	LV_PLUGIN_RES_ID_NONE, /* 312*/
	LV_PLUGIN_RES_ID_NONE, /* 313*/
	LV_PLUGIN_RES_ID_NONE, /* 314*/
	LV_PLUGIN_RES_ID_NONE, /* 315*/
	LV_PLUGIN_RES_ID_NONE, /* 316*/
	LV_PLUGIN_RES_ID_NONE, /* 317*/
	LV_PLUGIN_RES_ID_NONE, /* 318*/
	LV_PLUGIN_RES_ID_NONE, /* 319*/
	LV_PLUGIN_RES_ID_NONE, /* 320*/
	LV_PLUGIN_RES_ID_NONE, /* 321*/
	LV_PLUGIN_RES_ID_NONE, /* 322*/
	LV_PLUGIN_RES_ID_NONE, /* 323*/
	LV_PLUGIN_RES_ID_NONE, /* 324*/
	LV_PLUGIN_RES_ID_NONE, /* 325*/
	LV_PLUGIN_RES_ID_NONE, /* 326*/
	LV_PLUGIN_RES_ID_NONE, /* 327*/
	LV_PLUGIN_RES_ID_NONE, /* 328*/
	LV_PLUGIN_RES_ID_NONE, /* 329*/
	LV_PLUGIN_RES_ID_NONE, /* 330*/
	LV_PLUGIN_RES_ID_NONE, /* 331*/
	LV_PLUGIN_RES_ID_NONE, /* 332*/
	LV_PLUGIN_RES_ID_NONE, /* 333*/
	LV_PLUGIN_RES_ID_NONE, /* 334*/
	LV_PLUGIN_RES_ID_NONE, /* 335*/
	LV_PLUGIN_RES_ID_NONE, /* 336*/
	LV_PLUGIN_RES_ID_NONE, /* 337*/
	LV_PLUGIN_RES_ID_NONE, /* 338*/
	LV_PLUGIN_RES_ID_NONE, /* 339*/
	LV_PLUGIN_RES_ID_NONE, /* 340*/
	LV_PLUGIN_RES_ID_NONE, /* 341*/
	LV_PLUGIN_RES_ID_NONE, /* 342*/
	LV_PLUGIN_RES_ID_NONE, /* 343*/
	LV_PLUGIN_RES_ID_NONE, /* 344*/
	LV_PLUGIN_RES_ID_NONE, /* 345*/
	LV_PLUGIN_RES_ID_NONE, /* 346*/
	LV_PLUGIN_RES_ID_NONE, /* 347*/
	LV_PLUGIN_RES_ID_NONE, /* 348*/
	LV_PLUGIN_RES_ID_NONE, /* 349*/
	LV_PLUGIN_RES_ID_NONE, /* 350*/
	LV_PLUGIN_RES_ID_NONE, /* 351*/
	LV_PLUGIN_RES_ID_NONE, /* 352*/
	LV_PLUGIN_RES_ID_NONE, /* 353*/
	LV_PLUGIN_RES_ID_NONE, /* 354*/
	LV_PLUGIN_RES_ID_NONE, /* 355*/
	LV_PLUGIN_RES_ID_NONE, /* 356*/
	LV_PLUGIN_RES_ID_NONE, /* 357*/
	LV_PLUGIN_RES_ID_NONE, /* 358*/
	LV_PLUGIN_RES_ID_NONE, /* 359*/
	LV_PLUGIN_RES_ID_NONE, /* 360*/
	LV_PLUGIN_RES_ID_NONE, /* 361*/
	LV_PLUGIN_RES_ID_NONE, /* 362*/
	LV_PLUGIN_RES_ID_NONE, /* 363*/
	LV_PLUGIN_RES_ID_NONE, /* 364*/
	LV_PLUGIN_RES_ID_NONE, /* 365*/
	LV_PLUGIN_RES_ID_NONE, /* 366*/
	LV_PLUGIN_RES_ID_NONE, /* 367*/
	LV_PLUGIN_RES_ID_NONE, /* 368*/
	LV_PLUGIN_RES_ID_NONE, /* 369*/
	LV_PLUGIN_RES_ID_NONE, /* 370*/
	LV_PLUGIN_RES_ID_NONE, /* 371*/
	LV_PLUGIN_RES_ID_NONE, /* 372*/
	LV_PLUGIN_RES_ID_NONE, /* 373*/
	LV_PLUGIN_RES_ID_NONE, /* 374*/
	LV_PLUGIN_RES_ID_NONE, /* 375*/
	LV_PLUGIN_RES_ID_NONE, /* 376*/
	LV_PLUGIN_RES_ID_NONE, /* 377*/
	LV_PLUGIN_RES_ID_NONE, /* 378*/
	LV_PLUGIN_RES_ID_NONE, /* 379*/
	LV_PLUGIN_RES_ID_NONE, /* 380*/
	LV_PLUGIN_RES_ID_NONE, /* 381*/
	LV_PLUGIN_RES_ID_NONE, /* 382*/
	LV_PLUGIN_RES_ID_NONE, /* 383*/
	LV_PLUGIN_RES_ID_NONE, /* 384*/
	LV_PLUGIN_RES_ID_NONE, /* 385*/
	LV_PLUGIN_RES_ID_NONE, /* 386*/
	LV_PLUGIN_RES_ID_NONE, /* 387*/
	LV_PLUGIN_RES_ID_NONE, /* 388*/
	LV_PLUGIN_RES_ID_NONE, /* 389*/
	LV_PLUGIN_RES_ID_NONE, /* 390*/
	LV_PLUGIN_RES_ID_NONE, /* 391*/
	LV_PLUGIN_RES_ID_NONE, /* 392*/
	LV_PLUGIN_RES_ID_NONE, /* 393*/
	LV_PLUGIN_RES_ID_NONE, /* 394*/
	LV_PLUGIN_RES_ID_NONE, /* 395*/
	LV_PLUGIN_RES_ID_NONE, /* 396*/
	LV_PLUGIN_RES_ID_NONE, /* 397*/
	LV_PLUGIN_RES_ID_NONE, /* 398*/
	LV_PLUGIN_RES_ID_NONE, /* 399*/
	LV_PLUGIN_RES_ID_NONE, /* 400*/
	LV_PLUGIN_RES_ID_NONE, /* 401*/
	LV_PLUGIN_RES_ID_NONE, /* 402*/
	LV_PLUGIN_RES_ID_NONE, /* 403*/
	LV_PLUGIN_RES_ID_NONE, /* 404*/
	LV_PLUGIN_RES_ID_NONE, /* 405*/
	LV_PLUGIN_RES_ID_NONE, /* 406*/
	LV_PLUGIN_RES_ID_NONE, /* 407*/
	LV_PLUGIN_RES_ID_NONE, /* 408*/
	LV_PLUGIN_RES_ID_NONE, /* 409*/
	LV_PLUGIN_RES_ID_NONE, /* 410*/
	LV_PLUGIN_RES_ID_NONE, /* 411*/
	LV_PLUGIN_RES_ID_NONE, /* 412*/
	LV_PLUGIN_RES_ID_NONE, /* 413*/
	LV_PLUGIN_RES_ID_NONE, /* 414*/
	LV_PLUGIN_RES_ID_NONE, /* 415*/
	LV_PLUGIN_RES_ID_NONE, /* 416*/
	LV_PLUGIN_RES_ID_NONE, /* 417*/
	LV_PLUGIN_RES_ID_NONE, /* 418*/
	LV_PLUGIN_RES_ID_NONE, /* 419*/
	LV_PLUGIN_RES_ID_NONE, /* 420*/
	LV_PLUGIN_RES_ID_NONE, /* 421*/
	LV_PLUGIN_RES_ID_NONE, /* 422*/
	LV_PLUGIN_RES_ID_NONE, /* 423*/
	LV_PLUGIN_RES_ID_NONE, /* 424*/
	LV_PLUGIN_RES_ID_NONE, /* 425*/
	LV_PLUGIN_RES_ID_NONE, /* 426*/
	LV_PLUGIN_RES_ID_NONE, /* 427*/
	LV_PLUGIN_RES_ID_NONE, /* 428*/
	LV_PLUGIN_RES_ID_NONE, /* 429*/
	LV_PLUGIN_RES_ID_NONE, /* 430*/
	LV_PLUGIN_RES_ID_NONE, /* 431*/
	LV_PLUGIN_RES_ID_NONE, /* 432*/
	LV_PLUGIN_RES_ID_NONE, /* 433*/
	LV_PLUGIN_RES_ID_NONE, /* 434*/
	LV_PLUGIN_RES_ID_NONE, /* 435*/
	LV_PLUGIN_RES_ID_NONE, /* 436*/
	LV_PLUGIN_RES_ID_NONE, /* 437*/
	LV_PLUGIN_RES_ID_NONE, /* 438*/
	LV_PLUGIN_RES_ID_NONE, /* 439*/
	LV_PLUGIN_RES_ID_NONE, /* 440*/
	LV_PLUGIN_RES_ID_NONE, /* 441*/
	LV_PLUGIN_RES_ID_NONE, /* 442*/
	LV_PLUGIN_RES_ID_NONE, /* 443*/
	LV_PLUGIN_RES_ID_NONE, /* 444*/
	LV_PLUGIN_RES_ID_NONE, /* 445*/
	LV_PLUGIN_RES_ID_NONE, /* 446*/
	LV_PLUGIN_RES_ID_NONE, /* 447*/
	LV_PLUGIN_RES_ID_NONE, /* 448*/
	LV_PLUGIN_RES_ID_NONE, /* 449*/
	LV_PLUGIN_RES_ID_NONE, /* 450*/
	LV_PLUGIN_RES_ID_NONE, /* 451*/
	LV_PLUGIN_RES_ID_NONE, /* 452*/
	LV_PLUGIN_RES_ID_NONE, /* 453*/
	LV_PLUGIN_RES_ID_NONE, /* 454*/
	LV_PLUGIN_RES_ID_NONE, /* 455*/
	LV_PLUGIN_RES_ID_NONE, /* 456*/
	LV_PLUGIN_RES_ID_NONE, /* 457*/
	LV_PLUGIN_RES_ID_NONE, /* 458*/
	LV_PLUGIN_RES_ID_NONE, /* 459*/
	LV_PLUGIN_RES_ID_NONE, /* 460*/
	LV_PLUGIN_RES_ID_NONE, /* 461*/
	LV_PLUGIN_RES_ID_NONE, /* 462*/
	LV_PLUGIN_RES_ID_NONE, /* 463*/
	LV_PLUGIN_RES_ID_NONE, /* 464*/
	LV_PLUGIN_RES_ID_NONE, /* 465*/
	LV_PLUGIN_RES_ID_NONE, /* 466*/
	LV_PLUGIN_RES_ID_NONE, /* 467*/
	LV_PLUGIN_RES_ID_NONE, /* 468*/
	LV_PLUGIN_RES_ID_NONE, /* 469*/
	LV_PLUGIN_RES_ID_NONE, /* 470*/
	LV_PLUGIN_RES_ID_NONE, /* 471*/
	LV_PLUGIN_RES_ID_NONE, /* 472*/
	LV_PLUGIN_RES_ID_NONE, /* 473*/
	LV_PLUGIN_RES_ID_NONE, /* 474*/
	LV_PLUGIN_RES_ID_NONE, /* 475*/
	LV_PLUGIN_RES_ID_NONE, /* 476*/
	LV_PLUGIN_RES_ID_NONE, /* 477*/
	LV_PLUGIN_RES_ID_NONE, /* 478*/
	LV_PLUGIN_RES_ID_NONE, /* 479*/
	LV_PLUGIN_RES_ID_NONE, /* 480*/
	LV_PLUGIN_RES_ID_NONE, /* 481*/
	LV_PLUGIN_RES_ID_NONE, /* 482*/
	LV_PLUGIN_RES_ID_NONE, /* 483*/
	LV_PLUGIN_RES_ID_NONE, /* 484*/
	LV_PLUGIN_RES_ID_NONE, /* 485*/
	LV_PLUGIN_RES_ID_NONE, /* 486*/
	LV_PLUGIN_RES_ID_NONE, /* 487*/
	LV_PLUGIN_RES_ID_NONE, /* 488*/
	LV_PLUGIN_RES_ID_NONE, /* 489*/
	LV_PLUGIN_RES_ID_NONE, /* 490*/
	LV_PLUGIN_RES_ID_NONE, /* 491*/
	LV_PLUGIN_RES_ID_NONE, /* 492*/
	LV_PLUGIN_RES_ID_NONE, /* 493*/
	LV_PLUGIN_RES_ID_NONE, /* 494*/
	LV_PLUGIN_RES_ID_NONE, /* 495*/
	LV_PLUGIN_RES_ID_NONE, /* 496*/
	LV_PLUGIN_RES_ID_NONE, /* 497*/
	LV_PLUGIN_RES_ID_NONE, /* 498*/
	LV_PLUGIN_RES_ID_NONE, /* 499*/
	LV_PLUGIN_RES_ID_NONE, /* 500*/
	LV_PLUGIN_RES_ID_NONE, /* 501*/
	LV_PLUGIN_RES_ID_NONE, /* 502*/
	LV_PLUGIN_RES_ID_NONE, /* 503*/
	LV_PLUGIN_RES_ID_NONE, /* 504*/
	LV_PLUGIN_RES_ID_NONE, /* 505*/
	LV_PLUGIN_RES_ID_NONE, /* 506*/
	LV_PLUGIN_RES_ID_NONE, /* 507*/
	LV_PLUGIN_RES_ID_NONE, /* 508*/
	LV_PLUGIN_RES_ID_NONE, /* 509*/
	LV_PLUGIN_RES_ID_NONE, /* 510*/
	LV_PLUGIN_RES_ID_NONE, /* 511*/
	LV_PLUGIN_RES_ID_NONE, /* 512*/
	LV_PLUGIN_RES_ID_NONE, /* 513*/
	LV_PLUGIN_RES_ID_NONE, /* 514*/
	LV_PLUGIN_RES_ID_NONE, /* 515*/
	LV_PLUGIN_RES_ID_NONE, /* 516*/
	LV_PLUGIN_RES_ID_NONE, /* 517*/
	LV_PLUGIN_RES_ID_NONE, /* 518*/
	LV_PLUGIN_RES_ID_NONE, /* 519*/
	LV_PLUGIN_RES_ID_NONE, /* 520*/
	LV_PLUGIN_RES_ID_NONE, /* 521*/
	LV_PLUGIN_RES_ID_NONE, /* 522*/
	LV_PLUGIN_RES_ID_NONE, /* 523*/
	LV_PLUGIN_RES_ID_NONE, /* 524*/
	LV_PLUGIN_RES_ID_NONE, /* 525*/
	LV_PLUGIN_RES_ID_NONE, /* 526*/
	LV_PLUGIN_RES_ID_NONE, /* 527*/
	LV_PLUGIN_RES_ID_NONE, /* 528*/
	LV_PLUGIN_RES_ID_NONE, /* 529*/
	LV_PLUGIN_RES_ID_NONE, /* 530*/
	LV_PLUGIN_RES_ID_NONE, /* 531*/
	LV_PLUGIN_RES_ID_NONE, /* 532*/
	LV_PLUGIN_RES_ID_NONE, /* 533*/
	LV_PLUGIN_RES_ID_NONE, /* 534*/
	LV_PLUGIN_RES_ID_NONE, /* 535*/
	LV_PLUGIN_RES_ID_NONE, /* 536*/
	LV_PLUGIN_RES_ID_NONE, /* 537*/
	LV_PLUGIN_RES_ID_NONE, /* 538*/
	LV_PLUGIN_RES_ID_NONE, /* 539*/
	LV_PLUGIN_RES_ID_NONE, /* 540*/
	LV_PLUGIN_RES_ID_NONE, /* 541*/
	LV_PLUGIN_RES_ID_NONE, /* 542*/
	LV_PLUGIN_RES_ID_NONE, /* 543*/
	LV_PLUGIN_RES_ID_NONE, /* 544*/
	LV_PLUGIN_RES_ID_NONE, /* 545*/
	LV_PLUGIN_RES_ID_NONE, /* 546*/
	LV_PLUGIN_RES_ID_NONE, /* 547*/
	LV_PLUGIN_RES_ID_NONE, /* 548*/
	LV_PLUGIN_RES_ID_NONE, /* 549*/
	LV_PLUGIN_RES_ID_NONE, /* 550*/
	LV_PLUGIN_RES_ID_NONE, /* 551*/
	LV_PLUGIN_RES_ID_NONE, /* 552*/
	LV_PLUGIN_RES_ID_NONE, /* 553*/
	LV_PLUGIN_RES_ID_NONE, /* 554*/
	LV_PLUGIN_RES_ID_NONE, /* 555*/
	LV_PLUGIN_RES_ID_NONE, /* 556*/
	LV_PLUGIN_RES_ID_NONE, /* 557*/
	LV_PLUGIN_RES_ID_NONE, /* 558*/
	LV_PLUGIN_RES_ID_NONE, /* 559*/
	LV_PLUGIN_RES_ID_NONE, /* 560*/
	LV_PLUGIN_RES_ID_NONE, /* 561*/
	LV_PLUGIN_RES_ID_NONE, /* 562*/
	LV_PLUGIN_RES_ID_NONE, /* 563*/
	LV_PLUGIN_RES_ID_NONE, /* 564*/
	LV_PLUGIN_RES_ID_NONE, /* 565*/
	LV_PLUGIN_RES_ID_NONE, /* 566*/
	LV_PLUGIN_RES_ID_NONE, /* 567*/
	LV_PLUGIN_RES_ID_NONE, /* 568*/
	LV_PLUGIN_RES_ID_NONE, /* 569*/
	LV_PLUGIN_RES_ID_NONE, /* 570*/
	LV_PLUGIN_RES_ID_NONE, /* 571*/
	LV_PLUGIN_RES_ID_NONE, /* 572*/
	LV_PLUGIN_RES_ID_NONE, /* 573*/
	LV_PLUGIN_RES_ID_NONE, /* 574*/
	LV_PLUGIN_RES_ID_NONE, /* 575*/
	LV_PLUGIN_RES_ID_NONE, /* 576*/
	LV_PLUGIN_RES_ID_NONE, /* 577*/
	LV_PLUGIN_RES_ID_NONE, /* 578*/
	LV_PLUGIN_RES_ID_NONE, /* 579*/
	LV_PLUGIN_RES_ID_NONE, /* 580*/
	LV_PLUGIN_RES_ID_NONE, /* 581*/
	LV_PLUGIN_RES_ID_NONE, /* 582*/
	LV_PLUGIN_RES_ID_NONE, /* 583*/
	LV_PLUGIN_RES_ID_NONE, /* 584*/
	LV_PLUGIN_RES_ID_NONE, /* 585*/
	LV_PLUGIN_RES_ID_NONE, /* 586*/
	LV_PLUGIN_RES_ID_NONE, /* 587*/
	LV_PLUGIN_RES_ID_NONE, /* 588*/
	LV_PLUGIN_RES_ID_NONE, /* 589*/
	LV_PLUGIN_RES_ID_NONE, /* 590*/
	LV_PLUGIN_RES_ID_NONE, /* 591*/
	LV_PLUGIN_RES_ID_NONE, /* 592*/
	LV_PLUGIN_RES_ID_NONE, /* 593*/
	LV_PLUGIN_RES_ID_NONE, /* 594*/
	LV_PLUGIN_RES_ID_NONE, /* 595*/
	LV_PLUGIN_RES_ID_NONE, /* 596*/
	LV_PLUGIN_RES_ID_NONE, /* 597*/
	LV_PLUGIN_RES_ID_NONE, /* 598*/
	LV_PLUGIN_RES_ID_NONE, /* 599*/
	LV_PLUGIN_RES_ID_NONE, /* 600*/
	LV_PLUGIN_RES_ID_NONE, /* 601*/
	LV_PLUGIN_RES_ID_NONE, /* 602*/
	LV_PLUGIN_RES_ID_NONE, /* 603*/
	LV_PLUGIN_RES_ID_NONE, /* 604*/
	LV_PLUGIN_RES_ID_NONE, /* 605*/
	LV_PLUGIN_RES_ID_NONE, /* 606*/
	LV_PLUGIN_RES_ID_NONE, /* 607*/
	LV_PLUGIN_RES_ID_NONE, /* 608*/
	LV_PLUGIN_RES_ID_NONE, /* 609*/
	LV_PLUGIN_RES_ID_NONE, /* 610*/
	LV_PLUGIN_RES_ID_NONE, /* 611*/
	LV_PLUGIN_RES_ID_NONE, /* 612*/
	LV_PLUGIN_RES_ID_NONE, /* 613*/
	LV_PLUGIN_RES_ID_NONE, /* 614*/
	LV_PLUGIN_RES_ID_NONE, /* 615*/
	LV_PLUGIN_RES_ID_NONE, /* 616*/
	LV_PLUGIN_RES_ID_NONE, /* 617*/
	LV_PLUGIN_RES_ID_NONE, /* 618*/
	LV_PLUGIN_RES_ID_NONE, /* 619*/
	LV_PLUGIN_RES_ID_NONE, /* 620*/
	LV_PLUGIN_RES_ID_NONE, /* 621*/
	LV_PLUGIN_RES_ID_NONE, /* 622*/
	LV_PLUGIN_RES_ID_NONE, /* 623*/
	LV_PLUGIN_RES_ID_NONE, /* 624*/
	LV_PLUGIN_RES_ID_NONE, /* 625*/
	LV_PLUGIN_RES_ID_NONE, /* 626*/
	LV_PLUGIN_RES_ID_NONE, /* 627*/
	LV_PLUGIN_RES_ID_NONE, /* 628*/
	LV_PLUGIN_RES_ID_NONE, /* 629*/
	LV_PLUGIN_RES_ID_NONE, /* 630*/
	LV_PLUGIN_RES_ID_NONE, /* 631*/
	LV_PLUGIN_RES_ID_NONE, /* 632*/
	LV_PLUGIN_RES_ID_NONE, /* 633*/
	LV_PLUGIN_RES_ID_NONE, /* 634*/
	LV_PLUGIN_RES_ID_NONE, /* 635*/
	LV_PLUGIN_RES_ID_NONE, /* 636*/
	LV_PLUGIN_RES_ID_NONE, /* 637*/
	LV_PLUGIN_LANGUAGE_ID_EN, /* 638*/
	LV_PLUGIN_RES_ID_NONE, /* 639*/
	LV_PLUGIN_RES_ID_NONE, /* 640*/
	LV_PLUGIN_RES_ID_NONE, /* 641*/
	LV_PLUGIN_RES_ID_NONE, /* 642*/
	LV_PLUGIN_RES_ID_NONE, /* 643*/
	LV_PLUGIN_RES_ID_NONE, /* 644*/
	LV_PLUGIN_RES_ID_NONE, /* 645*/
	LV_PLUGIN_RES_ID_NONE, /* 646*/
	LV_PLUGIN_RES_ID_NONE, /* 647*/
	LV_PLUGIN_RES_ID_NONE, /* 648*/
	LV_PLUGIN_RES_ID_NONE, /* 649*/
	LV_PLUGIN_RES_ID_NONE, /* 650*/
	LV_PLUGIN_RES_ID_NONE, /* 651*/
	LV_PLUGIN_RES_ID_NONE, /* 652*/
	LV_PLUGIN_RES_ID_NONE, /* 653*/
	LV_PLUGIN_RES_ID_NONE, /* 654*/
	LV_PLUGIN_RES_ID_NONE, /* 655*/
	LV_PLUGIN_RES_ID_NONE, /* 656*/
	LV_PLUGIN_RES_ID_NONE, /* 657*/
	LV_PLUGIN_RES_ID_NONE, /* 658*/
	LV_PLUGIN_RES_ID_NONE, /* 659*/
	LV_PLUGIN_RES_ID_NONE, /* 660*/
	LV_PLUGIN_RES_ID_NONE, /* 661*/
	LV_PLUGIN_RES_ID_NONE, /* 662*/
	LV_PLUGIN_RES_ID_NONE, /* 663*/
	LV_PLUGIN_RES_ID_NONE, /* 664*/
	LV_PLUGIN_RES_ID_NONE, /* 665*/
	LV_PLUGIN_RES_ID_NONE, /* 666*/
	LV_PLUGIN_RES_ID_NONE, /* 667*/
	LV_PLUGIN_RES_ID_NONE, /* 668*/
	LV_PLUGIN_RES_ID_NONE, /* 669*/
	LV_PLUGIN_RES_ID_NONE, /* 670*/
	LV_PLUGIN_RES_ID_NONE, /* 671*/
	LV_PLUGIN_RES_ID_NONE, /* 672*/
	LV_PLUGIN_RES_ID_NONE, /* 673*/
	LV_PLUGIN_RES_ID_NONE, /* 674*/
	LV_PLUGIN_RES_ID_NONE, /* 675*/
	LV_PLUGIN_RES_ID_NONE, /* 676*/
	LV_PLUGIN_RES_ID_NONE, /* 677*/
	LV_PLUGIN_RES_ID_NONE, /* 678*/
	LV_PLUGIN_RES_ID_NONE, /* 679*/
	LV_PLUGIN_RES_ID_NONE, /* 680*/
	LV_PLUGIN_RES_ID_NONE, /* 681*/
	LV_PLUGIN_RES_ID_NONE, /* 682*/
	LV_PLUGIN_RES_ID_NONE, /* 683*/
	LV_PLUGIN_RES_ID_NONE, /* 684*/
	LV_PLUGIN_RES_ID_NONE, /* 685*/
	LV_PLUGIN_RES_ID_NONE, /* 686*/
	LV_PLUGIN_RES_ID_NONE, /* 687*/
	LV_PLUGIN_LANGUAGE_ID_EN, /* 688*/
	LV_PLUGIN_LANGUAGE_ID_EN, /* 689*/
	LV_PLUGIN_RES_ID_NONE, /* 690*/
	LV_PLUGIN_RES_ID_NONE, /* 691*/
	LV_PLUGIN_RES_ID_NONE, /* 692*/
	LV_PLUGIN_RES_ID_NONE, /* 693*/
	LV_PLUGIN_RES_ID_NONE, /* 694*/
	LV_PLUGIN_RES_ID_NONE, /* 695*/
	LV_PLUGIN_RES_ID_NONE, /* 696*/
	LV_PLUGIN_RES_ID_NONE, /* 697*/
	LV_PLUGIN_RES_ID_NONE, /* 698*/
	LV_PLUGIN_RES_ID_NONE, /* 699*/
	LV_PLUGIN_RES_ID_NONE, /* 700*/
	LV_PLUGIN_RES_ID_NONE, /* 701*/
	LV_PLUGIN_RES_ID_NONE, /* 702*/
	LV_PLUGIN_RES_ID_NONE, /* 703*/
	LV_PLUGIN_RES_ID_NONE, /* 704*/
	LV_PLUGIN_RES_ID_NONE, /* 705*/
	LV_PLUGIN_RES_ID_NONE, /* 706*/
	LV_PLUGIN_RES_ID_NONE, /* 707*/
	LV_PLUGIN_RES_ID_NONE, /* 708*/
	LV_PLUGIN_RES_ID_NONE, /* 709*/
	LV_PLUGIN_RES_ID_NONE, /* 710*/
	LV_PLUGIN_RES_ID_NONE, /* 711*/
	LV_PLUGIN_RES_ID_NONE, /* 712*/
	LV_PLUGIN_RES_ID_NONE, /* 713*/
	LV_PLUGIN_RES_ID_NONE, /* 714*/
	LV_PLUGIN_RES_ID_NONE, /* 715*/
	LV_PLUGIN_RES_ID_NONE, /* 716*/
	LV_PLUGIN_RES_ID_NONE, /* 717*/
	LV_PLUGIN_RES_ID_NONE, /* 718*/
	LV_PLUGIN_RES_ID_NONE, /* 719*/
	LV_PLUGIN_RES_ID_NONE, /* 720*/
	LV_PLUGIN_RES_ID_NONE, /* 721*/
	LV_PLUGIN_RES_ID_NONE, /* 722*/
	LV_PLUGIN_RES_ID_NONE, /* 723*/
	LV_PLUGIN_RES_ID_NONE, /* 724*/
	LV_PLUGIN_RES_ID_NONE, /* 725*/
	LV_PLUGIN_RES_ID_NONE, /* 726*/
	LV_PLUGIN_RES_ID_NONE, /* 727*/
	LV_PLUGIN_RES_ID_NONE, /* 728*/
	LV_PLUGIN_RES_ID_NONE, /* 729*/
	LV_PLUGIN_RES_ID_NONE, /* 730*/
	LV_PLUGIN_RES_ID_NONE, /* 731*/
	LV_PLUGIN_RES_ID_NONE, /* 732*/
	LV_PLUGIN_RES_ID_NONE, /* 733*/
	LV_PLUGIN_RES_ID_NONE, /* 734*/
	LV_PLUGIN_RES_ID_NONE, /* 735*/
	LV_PLUGIN_RES_ID_NONE, /* 736*/
	LV_PLUGIN_RES_ID_NONE, /* 737*/
	LV_PLUGIN_RES_ID_NONE, /* 738*/
	LV_PLUGIN_RES_ID_NONE, /* 739*/
	LV_PLUGIN_RES_ID_NONE, /* 740*/
	LV_PLUGIN_RES_ID_NONE, /* 741*/
	LV_PLUGIN_RES_ID_NONE, /* 742*/
	LV_PLUGIN_RES_ID_NONE, /* 743*/
	LV_PLUGIN_RES_ID_NONE, /* 744*/
	LV_PLUGIN_RES_ID_NONE, /* 745*/
	LV_PLUGIN_RES_ID_NONE, /* 746*/
	LV_PLUGIN_RES_ID_NONE, /* 747*/
	LV_PLUGIN_RES_ID_NONE, /* 748*/
	LV_PLUGIN_RES_ID_NONE, /* 749*/
	LV_PLUGIN_RES_ID_NONE, /* 750*/
	LV_PLUGIN_RES_ID_NONE, /* 751*/
	LV_PLUGIN_RES_ID_NONE, /* 752*/
	LV_PLUGIN_RES_ID_NONE, /* 753*/
	LV_PLUGIN_RES_ID_NONE, /* 754*/
	LV_PLUGIN_RES_ID_NONE, /* 755*/
	LV_PLUGIN_RES_ID_NONE, /* 756*/
	LV_PLUGIN_RES_ID_NONE, /* 757*/
	LV_PLUGIN_RES_ID_NONE, /* 758*/
	LV_PLUGIN_RES_ID_NONE, /* 759*/
	LV_PLUGIN_RES_ID_NONE, /* 760*/
	LV_PLUGIN_RES_ID_NONE, /* 761*/
	LV_PLUGIN_RES_ID_NONE, /* 762*/
	LV_PLUGIN_RES_ID_NONE, /* 763*/
	LV_PLUGIN_RES_ID_NONE, /* 764*/
	LV_PLUGIN_RES_ID_NONE, /* 765*/
	LV_PLUGIN_RES_ID_NONE, /* 766*/
	LV_PLUGIN_RES_ID_NONE, /* 767*/
	LV_PLUGIN_RES_ID_NONE, /* 768*/
	LV_PLUGIN_RES_ID_NONE, /* 769*/
	LV_PLUGIN_RES_ID_NONE, /* 770*/
	LV_PLUGIN_RES_ID_NONE, /* 771*/
	LV_PLUGIN_RES_ID_NONE, /* 772*/
	LV_PLUGIN_RES_ID_NONE, /* 773*/
	LV_PLUGIN_RES_ID_NONE, /* 774*/
	LV_PLUGIN_RES_ID_NONE, /* 775*/
	LV_PLUGIN_RES_ID_NONE, /* 776*/
	LV_PLUGIN_RES_ID_NONE, /* 777*/
	LV_PLUGIN_RES_ID_NONE, /* 778*/
	LV_PLUGIN_RES_ID_NONE, /* 779*/
	LV_PLUGIN_RES_ID_NONE, /* 780*/
	LV_PLUGIN_RES_ID_NONE, /* 781*/
	LV_PLUGIN_RES_ID_NONE, /* 782*/
	LV_PLUGIN_RES_ID_NONE, /* 783*/
	LV_PLUGIN_RES_ID_NONE, /* 784*/
	LV_PLUGIN_RES_ID_NONE, /* 785*/
	LV_PLUGIN_RES_ID_NONE, /* 786*/
	LV_PLUGIN_RES_ID_NONE, /* 787*/
	LV_PLUGIN_RES_ID_NONE, /* 788*/
	LV_PLUGIN_RES_ID_NONE, /* 789*/
	LV_PLUGIN_RES_ID_NONE, /* 790*/
	LV_PLUGIN_RES_ID_NONE, /* 791*/
	LV_PLUGIN_RES_ID_NONE, /* 792*/
	LV_PLUGIN_RES_ID_NONE, /* 793*/
	LV_PLUGIN_RES_ID_NONE, /* 794*/
	LV_PLUGIN_RES_ID_NONE, /* 795*/
	LV_PLUGIN_RES_ID_NONE, /* 796*/
	LV_PLUGIN_RES_ID_NONE, /* 797*/
	LV_PLUGIN_RES_ID_NONE, /* 798*/
	LV_PLUGIN_RES_ID_NONE, /* 799*/
	LV_PLUGIN_RES_ID_NONE, /* 800*/
	LV_PLUGIN_RES_ID_NONE, /* 801*/
	LV_PLUGIN_RES_ID_NONE, /* 802*/
	LV_PLUGIN_RES_ID_NONE, /* 803*/
	LV_PLUGIN_RES_ID_NONE, /* 804*/
	LV_PLUGIN_RES_ID_NONE, /* 805*/
	LV_PLUGIN_RES_ID_NONE, /* 806*/
	LV_PLUGIN_RES_ID_NONE, /* 807*/
	LV_PLUGIN_RES_ID_NONE, /* 808*/
	LV_PLUGIN_RES_ID_NONE, /* 809*/
	LV_PLUGIN_RES_ID_NONE, /* 810*/
	LV_PLUGIN_RES_ID_NONE, /* 811*/
	LV_PLUGIN_RES_ID_NONE, /* 812*/
	LV_PLUGIN_RES_ID_NONE, /* 813*/
	LV_PLUGIN_RES_ID_NONE, /* 814*/
	LV_PLUGIN_RES_ID_NONE, /* 815*/
	LV_PLUGIN_RES_ID_NONE, /* 816*/
	LV_PLUGIN_RES_ID_NONE, /* 817*/
	LV_PLUGIN_RES_ID_NONE, /* 818*/
	LV_PLUGIN_RES_ID_NONE, /* 819*/
	LV_PLUGIN_RES_ID_NONE, /* 820*/
	LV_PLUGIN_RES_ID_NONE, /* 821*/
	LV_PLUGIN_RES_ID_NONE, /* 822*/
	LV_PLUGIN_RES_ID_NONE, /* 823*/
	LV_PLUGIN_RES_ID_NONE, /* 824*/
	LV_PLUGIN_RES_ID_NONE, /* 825*/
	LV_PLUGIN_RES_ID_NONE, /* 826*/
	LV_PLUGIN_RES_ID_NONE, /* 827*/
	LV_PLUGIN_RES_ID_NONE, /* 828*/
	LV_PLUGIN_RES_ID_NONE, /* 829*/
	LV_PLUGIN_RES_ID_NONE, /* 830*/
	LV_PLUGIN_RES_ID_NONE, /* 831*/
	LV_PLUGIN_RES_ID_NONE, /* 832*/
	LV_PLUGIN_RES_ID_NONE, /* 833*/
	LV_PLUGIN_RES_ID_NONE, /* 834*/
	LV_PLUGIN_RES_ID_NONE, /* 835*/
	LV_PLUGIN_RES_ID_NONE, /* 836*/
	LV_PLUGIN_RES_ID_NONE, /* 837*/
	LV_PLUGIN_RES_ID_NONE, /* 838*/
	LV_PLUGIN_RES_ID_NONE, /* 839*/
	LV_PLUGIN_RES_ID_NONE, /* 840*/
	LV_PLUGIN_RES_ID_NONE, /* 841*/
	LV_PLUGIN_RES_ID_NONE, /* 842*/
	LV_PLUGIN_RES_ID_NONE, /* 843*/
	LV_PLUGIN_RES_ID_NONE, /* 844*/
	LV_PLUGIN_RES_ID_NONE, /* 845*/
	LV_PLUGIN_RES_ID_NONE, /* 846*/
	LV_PLUGIN_RES_ID_NONE, /* 847*/
	LV_PLUGIN_RES_ID_NONE, /* 848*/
	LV_PLUGIN_RES_ID_NONE, /* 849*/
	LV_PLUGIN_RES_ID_NONE, /* 850*/
	LV_PLUGIN_RES_ID_NONE, /* 851*/
	LV_PLUGIN_RES_ID_NONE, /* 852*/
	LV_PLUGIN_RES_ID_NONE, /* 853*/
	LV_PLUGIN_RES_ID_NONE, /* 854*/
	LV_PLUGIN_RES_ID_NONE, /* 855*/
	LV_PLUGIN_RES_ID_NONE, /* 856*/
	LV_PLUGIN_RES_ID_NONE, /* 857*/
	LV_PLUGIN_RES_ID_NONE, /* 858*/
	LV_PLUGIN_RES_ID_NONE, /* 859*/
	LV_PLUGIN_RES_ID_NONE, /* 860*/
	LV_PLUGIN_RES_ID_NONE, /* 861*/
	LV_PLUGIN_RES_ID_NONE, /* 862*/
	LV_PLUGIN_RES_ID_NONE, /* 863*/
	LV_PLUGIN_RES_ID_NONE, /* 864*/
	LV_PLUGIN_RES_ID_NONE, /* 865*/
	LV_PLUGIN_RES_ID_NONE, /* 866*/
	LV_PLUGIN_RES_ID_NONE, /* 867*/
	LV_PLUGIN_RES_ID_NONE, /* 868*/
	LV_PLUGIN_RES_ID_NONE, /* 869*/
	LV_PLUGIN_RES_ID_NONE, /* 870*/
	LV_PLUGIN_RES_ID_NONE, /* 871*/
	LV_PLUGIN_RES_ID_NONE, /* 872*/
	LV_PLUGIN_RES_ID_NONE, /* 873*/
	LV_PLUGIN_RES_ID_NONE, /* 874*/
	LV_PLUGIN_RES_ID_NONE, /* 875*/
	LV_PLUGIN_RES_ID_NONE, /* 876*/
	LV_PLUGIN_RES_ID_NONE, /* 877*/
	LV_PLUGIN_RES_ID_NONE, /* 878*/
	LV_PLUGIN_RES_ID_NONE, /* 879*/
	LV_PLUGIN_RES_ID_NONE, /* 880*/
	LV_PLUGIN_RES_ID_NONE, /* 881*/
	LV_PLUGIN_RES_ID_NONE, /* 882*/
	LV_PLUGIN_RES_ID_NONE, /* 883*/
	LV_PLUGIN_RES_ID_NONE, /* 884*/
	LV_PLUGIN_RES_ID_NONE, /* 885*/
	LV_PLUGIN_RES_ID_NONE, /* 886*/
	LV_PLUGIN_RES_ID_NONE, /* 887*/
	LV_PLUGIN_RES_ID_NONE, /* 888*/
	LV_PLUGIN_RES_ID_NONE, /* 889*/
	LV_PLUGIN_RES_ID_NONE, /* 890*/
	LV_PLUGIN_RES_ID_NONE, /* 891*/
	LV_PLUGIN_RES_ID_NONE, /* 892*/
	LV_PLUGIN_RES_ID_NONE, /* 893*/
	LV_PLUGIN_RES_ID_NONE, /* 894*/
	LV_PLUGIN_RES_ID_NONE, /* 895*/
	LV_PLUGIN_RES_ID_NONE, /* 896*/
	LV_PLUGIN_RES_ID_NONE, /* 897*/
	LV_PLUGIN_RES_ID_NONE, /* 898*/
	LV_PLUGIN_RES_ID_NONE, /* 899*/
	LV_PLUGIN_RES_ID_NONE, /* 900*/
	LV_PLUGIN_RES_ID_NONE, /* 901*/
};

lv_plugin_res_t lv_plugin_UIFlowLVGL_res =
{
	lv_plugin_UIFlowLVGL_img_table,
	lv_plugin_UIFlowLVGL_font_table,
	lv_plugin_language_table,
	lv_plugin_language_fonts_table,
	lv_plugin_fixed_language_string_id_table,
	LV_PLUGIN_IMG_TABLE_SIZE,
	LV_PLUGIN_FONT_TABLE_SIZE,
	LV_PLUGIN_LANGUAGE_TABLE_SIZE,
	LV_PLUGIN_STRING_TABLE_SIZE,
	LV_PLUGIN_LANGUAGE_FONT_TYPE_SIZE,
};

void UIFlowLVGL(){
#if defined(LV_USE_SJPG) && LV_USE_SJPG
	lv_split_jpeg_init();
#endif
#if defined(LV_USE_PNG) && LV_USE_PNG
	lv_png_init();
#endif

	lv_plugin_init();
	lv_plugin_install_resource(&lv_plugin_UIFlowLVGL_res);
	UIFlowMovie = UIFlowMovie_create();
	UIFlowPhoto = UIFlowPhoto_create();
	UIFlowWrnMsg = UIFlowWrnMsg_create();
	UIFlowPlay = UIFlowPlay_create();
	UIFlowMenuCommonItem = UIFlowMenuCommonItem_create();
	UIFlowMenuCommonOption = UIFlowMenuCommonOption_create();
	UIFlowMenuCommonConfirm = UIFlowMenuCommonConfirm_create();
	UIFlowWaitMoment = UIFlowWaitMoment_create();
	UIFlowSetupDateTime = UIFlowSetupDateTime_create();
	UIFlowSetupGPS = UIFlowSetupGPS_create();
	UIFlowPlayThumb = UIFlowPlayThumb_create();
	UIFlowUSB = UIFlowUSB_create();
	UIFlowUSBMenu = UIFlowUSBMenu_create();
	UIFlowWifiLink = UIFlowWifiLink_create();
	UIFlowWifiLinkOK = UIFlowWifiLinkOK_create();
	UIFlowWifiWait = UIFlowWifiWait_create();
	UIFlowMovieWiFi = UIFlowMovieWiFi_create();
	UIFlowMenuSetupVersion = UIFlowMenuSetupVersion_create();

}