
#ifndef LV_PLUGIN_COMMON_H
#define LV_PLUGIN_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#define LV_PLUGIN_VERSION_MAJOR 1
#define LV_PLUGIN_VERSION_MINOR 3
#define LV_PLUGIN_VERSION_PATCH 0

#define LV_PLUGIN_RES_ID_NONE 0
#define LV_PLUGIN_RES_ID_MAX (UINT16_MAX)

#define LV_PLUGIN_EVENT_FIRST _LV_EVENT_LAST

/* copy from lv_mem.c */
#ifdef LV_ARCH_64
    #define ALIGN_MASK 0x7
#else
    #define ALIGN_MASK 0x3
#endif

#ifdef LV_ARCH_64
    #define MEM_UNIT uint64_t
#else
    #define MEM_UNIT uint32_t
#endif

#define LV_PLUGIN_PADD MEM_UNIT padd;

typedef void (*lv_plugin_iterator_callback)(lv_obj_t* obj);

typedef struct {
	const char* ptr;
	const uint32_t size;
} lv_plugin_string_t;

typedef struct {
	const lv_img_dsc_t* img;
} lv_plugin_img_t;

typedef struct {
	const lv_font_t* font;
} lv_plugin_font_t;

typedef enum {
	LV_PLUG_SUCCESS = 0,
	LV_PLUG_ERR_INVALID_PARAM,
	LV_PLUG_ERR_INVALID_RES,
	LV_PLUG_ERR_INVALID_OBJ,
	LV_PLUG_ERR_INVALID_RES_ID,
	LV_PLUG_ERR_STYLE_LIST_NOT_FOUND,
	LV_PLUG_ERR_OBJ_EXT_NOT_ALLOCATED,
	LV_PLUG_ERR_MENU_OUT_OF_IDX,
	LV_PLUG_ERR_MENU_ALREADY_ALLOCATED,
	LV_PLUG_ERR_MENU_NOT_ALLOCATED,
} LV_PLUG_RET;

enum {
	LV_PLUGIN_EVENT_SCR_OPEN = LV_PLUGIN_EVENT_FIRST,
	LV_PLUGIN_EVENT_SCR_CLOSE,
	LV_PLUGIN_EVENT_CHILD_SCR_CLOSE,
	LV_PLUGIN_EVENT_MENU_ITEM_FOCUSED,
	LV_PLUGIN_EVENT_MENU_ITEM_DEFOCUSED,
	LV_PLUGIN_EVENT_MENU_ITEM_SELECTED,
	LV_PLUGIN_EVENT_MENU_NOTIFY_END_OF_ITEM,	
	_LV_PLUGIN_EVENT_LAST
};

typedef enum {
    LV_PLUGIN_LANGUAGE_FONT_TYPE_0 = 0,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_1,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_2,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_3,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_4,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_5,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_6,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_7,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_8,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_9,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_10,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_11,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_12,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_13,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_14,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_15,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_16,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_17,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_18,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_19,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_20,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_21,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_22,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_23,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_24,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_25,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_26,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_27,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_28,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_29,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_30,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_31,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_32,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_33,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_34,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_35,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_36,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_37,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_38,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_39,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_40,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_41,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_42,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_43,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_44,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_45,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_46,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_47,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_48,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_49,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_50,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_51,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_52,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_53,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_54,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_55,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_56,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_57,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_58,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_59,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_60,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_61,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_62,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_63,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_64,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_65,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_66,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_67,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_68,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_69,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_70,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_71,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_72,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_73,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_74,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_75,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_76,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_77,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_78,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_79,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_80,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_81,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_82,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_83,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_84,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_85,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_86,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_87,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_88,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_89,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_90,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_91,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_92,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_93,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_94,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_95,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_96,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_97,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_98,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_99,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_100,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_101,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_102,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_103,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_104,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_105,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_106,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_107,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_108,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_109,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_110,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_111,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_112,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_113,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_114,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_115,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_116,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_117,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_118,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_119,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_120,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_121,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_122,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_123,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_124,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_125,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_126,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_127,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_128,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_129,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_130,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_131,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_132,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_133,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_134,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_135,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_136,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_137,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_138,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_139,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_140,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_141,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_142,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_143,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_144,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_145,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_146,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_147,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_148,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_149,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_150,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_151,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_152,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_153,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_154,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_155,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_156,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_157,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_158,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_159,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_160,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_161,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_162,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_163,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_164,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_165,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_166,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_167,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_168,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_169,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_170,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_171,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_172,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_173,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_174,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_175,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_176,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_177,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_178,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_179,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_180,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_181,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_182,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_183,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_184,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_185,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_186,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_187,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_188,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_189,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_190,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_191,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_192,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_193,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_194,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_195,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_196,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_197,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_198,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_199,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_200,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_201,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_202,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_203,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_204,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_205,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_206,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_207,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_208,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_209,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_210,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_211,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_212,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_213,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_214,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_215,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_216,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_217,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_218,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_219,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_220,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_221,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_222,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_223,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_224,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_225,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_226,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_227,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_228,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_229,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_230,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_231,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_232,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_233,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_234,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_235,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_236,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_237,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_238,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_239,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_240,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_241,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_242,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_243,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_244,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_245,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_246,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_247,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_248,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_249,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_250,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_251,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_252,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_253,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_254,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_255,
    LV_PLUGIN_LANGUAGE_FONT_TYPE_NUM
} LV_PLUGIN_LANGUAGE_FONT_TYPE;

typedef uint16_t lv_plugin_res_id;

typedef struct {

	lv_plugin_img_t* 				img_table;
	lv_plugin_font_t*				font_table;
	lv_plugin_string_t** 			language_table;
    lv_plugin_res_id**				language_font_map;      /* language - font map, one language coulde associates multiple fonts */
	lv_plugin_res_id*				fixed_language_string_id_table;

    uint16_t						img_table_size;         /* how many images */
    uint16_t						font_table_size;        /* how many fonts */
    uint16_t						language_table_size;    /* how many languages */
    uint16_t						string_table_size;      /* how many string ids */
    uint8_t                         language_font_type_size;      /* how many fonts associated with per language */

} lv_plugin_res_t;


typedef struct {
	lv_label_ext_t base_ext;
	lv_plugin_res_id string_id;
    LV_PLUGIN_LANGUAGE_FONT_TYPE font_type;
	LV_PLUGIN_PADD
} lv_plugin_label_ext_t;

typedef struct {
	lv_img_ext_t base_ext;
	lv_plugin_res_id img_id;
	LV_PLUGIN_PADD
} lv_plugin_img_ext_t;


typedef struct {
	lv_msgbox_ext_t base_ext;
	lv_plugin_res_id string_id;
    LV_PLUGIN_LANGUAGE_FONT_TYPE font_type_bg;
    LV_PLUGIN_LANGUAGE_FONT_TYPE font_type_btn;
    LV_PLUGIN_LANGUAGE_FONT_TYPE font_type_btn_bg;
	LV_PLUGIN_PADD
} lv_plugin_msgbox_ext_t;

void						lv_plugin_init(void);

LV_PLUG_RET 				lv_plugin_install_resource(lv_plugin_res_t* res);

const lv_plugin_img_t* 		lv_plugin_get_img(lv_plugin_res_id id);
const lv_plugin_font_t* 	lv_plugin_get_font(lv_plugin_res_id id);


/**
 * Set object font, this API simplify style configuration.
 * @param obj
 * @param id font resource id
 * @param part please refer to lvgl document or just set -1.
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET					lv_plugin_obj_set_font(lv_obj_t* obj, lv_plugin_res_id font_id, int16_t part);


LV_PLUG_RET					lv_plugin_label_update_font(lv_obj_t* label, int16_t part);
LV_PLUG_RET					lv_plugin_msgbox_update_font(lv_obj_t* msgbox, int16_t part);

LV_PLUG_RET					lv_plugin_set_active_language(lv_plugin_res_id language_id);
lv_plugin_res_id			lv_plugin_get_active_language(void);
const lv_plugin_string_t*	lv_plugin_get_string(lv_plugin_res_id string_id);

LV_PLUG_RET					lv_plugin_obj_update_font(lv_obj_t* obj, lv_plugin_res_id string_id, int16_t part);
LV_PLUG_RET                 lv_plugin_obj_update_font_ex(lv_obj_t* obj, lv_plugin_res_id string_id, int16_t part, LV_PLUGIN_LANGUAGE_FONT_TYPE type);


/**
 * Internal API, check object plug-in extended attributes is allocated, the base_size should be ext size of obj.
 * @param obj
 * @param base_size generic widget ext size
 * @return bool
 */
bool 						_lv_plugin_obj_is_ext_attr_allocated(lv_obj_t* obj, uint32_t base_size);


/**
 * Internal API, allocate object plug-in extended attributes, ext_size is plug-in ext size and should be larger than generic ext size.
 * @param obj
 * @param base_size generic widget ext size
 * @return void*
 */
void* 						_lv_plugin_obj_allocate_ext_attr(lv_obj_t* obj, uint32_t ext_size);

/**
 * Set label font type.
 * @param label
 * @param font_type
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET					lv_plugin_label_set_font_type(lv_obj_t* label,  LV_PLUGIN_LANGUAGE_FONT_TYPE font_type);
LV_PLUG_RET					lv_plugin_msgbox_set_font_type(lv_obj_t* msgbox,  LV_PLUGIN_LANGUAGE_FONT_TYPE font_type, int8_t part);


/**
 * Set label text by string id of the active language.
 * @param label
 * @param string_id
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET					lv_plugin_label_set_text(lv_obj_t* label,  lv_plugin_res_id string_id);
LV_PLUG_RET					lv_plugin_msgbox_set_text(lv_obj_t* msgbox,  lv_plugin_res_id string_id);

/**
 * Update label text by string id of the active language.
 * @param label
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET					lv_plugin_label_update_text(lv_obj_t* label);
LV_PLUG_RET					lv_plugin_msgbox_update_text(lv_obj_t* msgbox);


/**
 * Check label object plug-in extended attributes is allocated.
 * @param label
 * @return bool
 */
bool 						lv_plugin_label_is_ext_attr_allocated(lv_obj_t* label);
bool 						lv_plugin_msgbox_is_ext_attr_allocated(lv_obj_t* label);

/**
 * Allocate label object plug-in extended attributes.
 * @param label
 */
void* 						lv_plugin_label_allocate_ext_attr(lv_obj_t* label);
void* 						lv_plugin_msgbox_allocate_ext_attr(lv_obj_t* msgbox);


LV_PLUG_RET					lv_plugin_img_set_src(lv_obj_t* obj,  lv_plugin_res_id img_id);



bool 						lv_plugin_scr_is_ready_to_be_closed(lv_obj_t* scr);


/**
 * Open a screen object and send LV_PLUGIN_EVENT_SCR_OPEN events.
 * @param scr
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET 				lv_plugin_scr_open(lv_obj_t* scr, const void * data);


/**
 * Close a screen object and send LV_PLUGIN_EVENT_SCR_CLOSE events.
 * @param scr
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET 				lv_plugin_scr_close(lv_obj_t* scr, const void * data);

/**
 * Internal API, attach a screen object to root screen from tmp screen.
 * @param scr
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET 				_lv_plugin_scr_attach(lv_obj_t* scr);


/**
 * Internal API, detach a screen object from root screen to tmp screen.
 * @param scr
 * @return LV_PLUG_RET return code
 */
LV_PLUG_RET 				_lv_plugin_scr_detach(lv_obj_t* scr);


/**
 * Create a plug-in screen.
 * @return lv_obj_t* plug-in screen
 */
lv_obj_t* 					lv_plugin_scr_create(void);


void lv_plugin_obj_iterator(lv_obj_t* parent, lv_plugin_iterator_callback cb, bool recursive);

typedef lv_obj_t * (*lv_plugin_obj_create_cb_t)(lv_obj_t * par, const lv_obj_t * copy);

const char* lv_plugin_label_type_name(void);
const char* lv_plugin_img_type_name(void);
const char* lv_plugin_btn_type_name(void);
const char* lv_plugin_cont_type_name(void);
const char* lv_plugin_imgbtn_type_name(void);
const char* lv_plugin_msgbox_type_name(void);

bool lv_plugin_obj_is_label(lv_obj_t* obj);
bool lv_plugin_obj_is_img(lv_obj_t* obj);
bool lv_plugin_obj_is_imgbtn(lv_obj_t* obj);
bool lv_plugin_obj_is_cont(lv_obj_t* obj);
bool lv_plugin_obj_is_btn(lv_obj_t* obj);
bool lv_plugin_obj_is_msgbox(lv_obj_t* obj);

lv_obj_t* 	lv_plugin_find_child_by_type(lv_obj_t* obj, lv_obj_t* start_child, const char* type);
lv_indev_t* lv_plugin_find_indev_by_type(lv_indev_type_t type);

lv_obj_t* lv_plugin_scr_act(void);

/**
 * Get screen handle by index.
 * @param index start from bottom(0) to top(count-1)
 * @return lv_obj_t* plug-in screen
 */
lv_obj_t* lv_plugin_scr_by_index(uint16_t index);

/**
 * Get number of opened screen.
 * @return uint16_t number of opened screen
 */
uint16_t lv_plugin_scr_count(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_PLUGIN_H*/
