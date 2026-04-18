#include "UIFlowLVGL/UIFlowMenuSetupVersion/UIFlowMenuSetupVersion.h"
#include "UIFlowLVGL/UIFlowLVGL.h"

#include "Resource/Plugin/lvgl_plugin.h"
/**********************
 *       WIDGETS
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
lv_obj_t* container_1_scr_uiflowmenusetupversion;
lv_obj_t* label_version_scr_uiflowmenusetupversion;
lv_obj_t* label_version_1_scr_uiflowmenusetupversion;
lv_obj_t* label_version_2_scr_uiflowmenusetupversion;
lv_obj_t* label_version_3_scr_uiflowmenusetupversion;

lv_obj_t* UIFlowMenuSetupVersion_create(){
	lv_obj_t *parent = lv_plugin_scr_create();
	lv_obj_set_event_cb(parent, UIFlowMenuSetupVersionEventCallback);

	lv_color_t color = {0};
	STYLE_COLOR_PROP(0x00, 0x55, 0x1f, 0x57);
	_lv_obj_set_style_local_color(parent,0,LV_STYLE_BG_COLOR, color);

	if(color.full== LV_COLOR_TRANSP.full){
		_lv_obj_set_style_local_opa(parent,0,LV_STYLE_BG_OPA,0);
	}


	static lv_style_t container_1_s0;
	lv_style_init(&container_1_s0);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_bg_color(&container_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&container_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x05, 0x00, 0xff, 0xff) ; lv_style_set_border_color(&container_1_s0, LV_STATE_DISABLED, color);
	lv_obj_t *container_1 = lv_cont_create(parent, NULL);
	lv_obj_set_hidden(container_1, false);
	lv_obj_set_click(container_1, true);
	lv_obj_set_drag(container_1, false);
	lv_obj_set_pos(container_1, 50, 50);
	lv_obj_set_size(container_1, 520, 150);
	lv_obj_add_style(container_1, 0, &container_1_s0);

	container_1_scr_uiflowmenusetupversion = container_1;


	static lv_style_t label_version_s0;
	lv_style_init(&label_version_s0);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_DEFAULT, color);
	lv_style_set_text_font(&label_version_s0,LV_STATE_DEFAULT,&lv_font_montserrat_16);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_s0, LV_STATE_DISABLED, color);
	lv_obj_t *label_version = lv_label_create(container_1, NULL);
	lv_obj_set_hidden(label_version, false);
	lv_obj_set_click(label_version, false);
	lv_obj_set_drag(label_version, false);
	lv_plugin_label_allocate_ext_attr(label_version);
	lv_label_set_text(label_version,"Version");
	lv_plugin_label_allocate_ext_attr(label_version);
	lv_plugin_label_set_font_type(label_version, LV_PLUGIN_LANGUAGE_FONT_TYPE_0);
	lv_label_set_align(label_version, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(label_version, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(label_version, 16, 16);
	lv_obj_set_size(label_version, 480, 18);
	lv_obj_add_style(label_version, 0, &label_version_s0);

	label_version_scr_uiflowmenusetupversion = label_version;


	static lv_style_t label_version_1_s0;
	lv_style_init(&label_version_1_s0);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	lv_style_set_text_font(&label_version_1_s0,LV_STATE_DEFAULT,&lv_font_montserrat_16);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_1_s0, LV_STATE_DISABLED, color);
	lv_obj_t *label_version_1 = lv_label_create(container_1, NULL);
	lv_obj_set_hidden(label_version_1, false);
	lv_obj_set_click(label_version_1, false);
	lv_obj_set_drag(label_version_1, false);
	lv_plugin_label_allocate_ext_attr(label_version_1);
	lv_plugin_label_allocate_ext_attr(label_version_1);
	lv_plugin_label_set_font_type(label_version_1, LV_PLUGIN_LANGUAGE_FONT_TYPE_0);
	lv_label_set_align(label_version_1, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(label_version_1, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(label_version_1, 20, 52);
	lv_obj_set_size(label_version_1, 480, 18);
	lv_obj_add_style(label_version_1, 0, &label_version_1_s0);

	label_version_1_scr_uiflowmenusetupversion = label_version_1;


	static lv_style_t label_version_2_s0;
	lv_style_init(&label_version_2_s0);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	lv_style_set_text_font(&label_version_2_s0,LV_STATE_DEFAULT,&lv_font_montserrat_16);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_2_s0, LV_STATE_DISABLED, color);
	lv_obj_t *label_version_2 = lv_label_create(container_1, NULL);
	lv_obj_set_hidden(label_version_2, false);
	lv_obj_set_click(label_version_2, false);
	lv_obj_set_drag(label_version_2, false);
	lv_plugin_label_allocate_ext_attr(label_version_2);
	lv_plugin_label_allocate_ext_attr(label_version_2);
	lv_plugin_label_set_font_type(label_version_2, LV_PLUGIN_LANGUAGE_FONT_TYPE_0);
	lv_label_set_align(label_version_2, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(label_version_2, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(label_version_2, 19, 85);
	lv_obj_set_size(label_version_2, 480, 18);
	lv_obj_add_style(label_version_2, 0, &label_version_2_s0);

	label_version_2_scr_uiflowmenusetupversion = label_version_2;


	static lv_style_t label_version_3_s0;
	lv_style_init(&label_version_3_s0);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	lv_style_set_text_font(&label_version_3_s0,LV_STATE_DEFAULT,&lv_font_montserrat_16);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_DEFAULT, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_CHECKED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_FOCUSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_EDITED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_HOVERED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_PRESSED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_bg_grad_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x01, 0x00, 0x00, 0x00) ; lv_style_set_border_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x02, 0xff, 0xff, 0xff) ; lv_style_set_text_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0xd3, 0x3c, 0x3c, 0x3c) ; lv_style_set_text_sel_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	STYLE_COLOR_PROP(0x3a, 0x00, 0xb4, 0x95) ; lv_style_set_text_sel_bg_color(&label_version_3_s0, LV_STATE_DISABLED, color);
	lv_obj_t *label_version_3 = lv_label_create(container_1, NULL);
	lv_obj_set_hidden(label_version_3, false);
	lv_obj_set_click(label_version_3, false);
	lv_obj_set_drag(label_version_3, false);
	lv_plugin_label_allocate_ext_attr(label_version_3);
	lv_plugin_label_allocate_ext_attr(label_version_3);
	lv_plugin_label_set_font_type(label_version_3, LV_PLUGIN_LANGUAGE_FONT_TYPE_0);
	lv_label_set_align(label_version_3, LV_LABEL_ALIGN_CENTER);
	lv_label_set_long_mode(label_version_3, LV_LABEL_LONG_CROP);
	lv_obj_set_pos(label_version_3, 21, 118);
	lv_obj_set_size(label_version_3, 480, 18);
	lv_obj_add_style(label_version_3, 0, &label_version_3_s0);

	label_version_3_scr_uiflowmenusetupversion = label_version_3;


	return parent;
}
