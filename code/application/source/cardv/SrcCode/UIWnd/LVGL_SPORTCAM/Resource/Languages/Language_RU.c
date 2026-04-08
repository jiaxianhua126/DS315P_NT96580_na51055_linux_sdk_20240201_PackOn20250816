#include "Resource/Plugin/lv_plugin_common.h"
lv_plugin_string_t lv_plugin_RU_string_table[] = {
	{ NULL, 0 },
	{ "", 0 },			/* LV_PLUGIN_STRING_ID_STRID_NULL_ */ 
	{ "режим", 10 },			/* LV_PLUGIN_STRING_ID_STRID_MODE */ 
	{ "размер изображения ", 36 },			/* LV_PLUGIN_STRING_ID_STRID_IMGSIZE */ 
	{ "разрешение", 20 },			/* LV_PLUGIN_STRING_ID_STRID_RESOLUTION */ 
	{ "12M", 3 },			/* LV_PLUGIN_STRING_ID_STRID_12M */ 
	{ "10M", 3 },			/* LV_PLUGIN_STRING_ID_STRID_10M */ 
	{ "9M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_9M */ 
	{ "8M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_8M */ 
	{ "7M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_7M */ 
	{ "6M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_6M */ 
	{ "5M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_5M */ 
	{ "4M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_4M */ 
	{ "3M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_3M */ 
	{ "2MHD", 4 },			/* LV_PLUGIN_STRING_ID_STRID_2MHD */ 
	{ "2M", 2 },			/* LV_PLUGIN_STRING_ID_STRID_2M */ 
	{ "1.3M", 4 },			/* LV_PLUGIN_STRING_ID_STRID_1M */ 
	{ "VGA", 3 },			/* LV_PLUGIN_STRING_ID_STRID_VGA */ 
	{ "QVGA", 4 },			/* LV_PLUGIN_STRING_ID_STRID_QVGA */ 
	{ "D1", 2 },			/* LV_PLUGIN_STRING_ID_STRID_D1 */ 
	{ "720P", 4 },			/* LV_PLUGIN_STRING_ID_STRID_720P */ 
	{ "1080P", 5 },			/* LV_PLUGIN_STRING_ID_STRID_1080P */ 
	{ "1080FHD", 7 },			/* LV_PLUGIN_STRING_ID_STRID_1080FHD */ 
	{ "12M 4032x3024", 13 },			/* LV_PLUGIN_STRING_ID_STRID_12MWXH */ 
	{ "10M 3648x2736", 13 },			/* LV_PLUGIN_STRING_ID_STRID_10MWXH */ 
	{ "9M 3472x2604", 12 },			/* LV_PLUGIN_STRING_ID_STRID_9MWXH */ 
	{ "8M 3264x2448", 12 },			/* LV_PLUGIN_STRING_ID_STRID_8MWXH */ 
	{ "7M 3072x2304", 12 },			/* LV_PLUGIN_STRING_ID_STRID_7MWXH */ 
	{ "6M 2816x2112", 12 },			/* LV_PLUGIN_STRING_ID_STRID_6MWXH */ 
	{ "5M 2592x1944", 12 },			/* LV_PLUGIN_STRING_ID_STRID_5MWXH */ 
	{ "4M 2272x1704", 12 },			/* LV_PLUGIN_STRING_ID_STRID_4MWXH */ 
	{ "3M 2048x1536", 12 },			/* LV_PLUGIN_STRING_ID_STRID_3MWXH */ 
	{ "2MHD 1920x1080", 14 },			/* LV_PLUGIN_STRING_ID_STRID_2MHDWXH */ 
	{ "2M 1600x1200", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2MWXH */ 
	{ "1.3M 1280x960", 13 },			/* LV_PLUGIN_STRING_ID_STRID_1MWXH */ 
	{ "WVGA 848x480", 12 },			/* LV_PLUGIN_STRING_ID_STRID_WVGAWXH */ 
	{ "VGA 640x480", 11 },			/* LV_PLUGIN_STRING_ID_STRID_VGAWXH */ 
	{ "QVGA 320x240", 12 },			/* LV_PLUGIN_STRING_ID_STRID_QVGAWXH */ 
	{ "D1 720x480", 10 },			/* LV_PLUGIN_STRING_ID_STRID_D1WXH */ 
	{ "720P 1280x720", 13 },			/* LV_PLUGIN_STRING_ID_STRID_720PWXH */ 
	{ "1080P 1440x1080", 15 },			/* LV_PLUGIN_STRING_ID_STRID_1080PWXH */ 
	{ "1080FHD 1920x1080", 17 },			/* LV_PLUGIN_STRING_ID_STRID_1080FHDWXH */ 
	{ "720P60 1280x720", 15 },			/* LV_PLUGIN_STRING_ID_STRID_720P60FPSWXH */ 
	{ "720P30 1280x720", 15 },			/* LV_PLUGIN_STRING_ID_STRID_720P30FPSWXH */ 
	{ "VGA30 640x480", 13 },			/* LV_PLUGIN_STRING_ID_STRID_VGA30FPSWXH */ 
	{ "VGA120 640x480", 14 },			/* LV_PLUGIN_STRING_ID_STRID_VGA120FPSWXH */ 
	{ "Сжатие записи", 25 },			/* LV_PLUGIN_STRING_ID_STRID_COMPRESSION */ 
	{ "качество ", 17 },			/* LV_PLUGIN_STRING_ID_STRID_QUALITY */ 
	{ "Наилучшее", 18 },			/* LV_PLUGIN_STRING_ID_STRID_SUPER */ 
	{ "Высокое", 14 },			/* LV_PLUGIN_STRING_ID_STRID_FINE */ 
	{ "Стандартное", 22 },			/* LV_PLUGIN_STRING_ID_STRID_NORMAL */ 
	{ "Экономичное", 22 },			/* LV_PLUGIN_STRING_ID_STRID_ECONOMY */ 
	{ "Баланс белого", 25 },			/* LV_PLUGIN_STRING_ID_STRID_WB */ 
	{ "Авто баланс", 21 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO */ 
	{ "Солнечно", 16 },			/* LV_PLUGIN_STRING_ID_STRID_WB_DAY */ 
	{ "пасмурно", 16 },			/* LV_PLUGIN_STRING_ID_STRID_WB_CLOUDY */ 
	{ "Вольфрам", 16 },			/* LV_PLUGIN_STRING_ID_STRID_WB_TUNGSTEN */ 
	{ "Флуоресцент", 22 },			/* LV_PLUGIN_STRING_ID_STRID_WB_FLUORESCENT */ 
	{ "Экспозиция", 20 },			/* LV_PLUGIN_STRING_ID_STRID_EXPOSURE */ 
	{ "EV", 2 },			/* LV_PLUGIN_STRING_ID_STRID_EV */ 
	{ "ISO", 3 },			/* LV_PLUGIN_STRING_ID_STRID_ISO */ 
	{ "50", 2 },			/* LV_PLUGIN_STRING_ID_STRID_ISO50 */ 
	{ "100", 3 },			/* LV_PLUGIN_STRING_ID_STRID_ISO100 */ 
	{ "200", 3 },			/* LV_PLUGIN_STRING_ID_STRID_ISO200 */ 
	{ "400", 3 },			/* LV_PLUGIN_STRING_ID_STRID_ISO400 */ 
	{ "Метеринг", 16 },			/* LV_PLUGIN_STRING_ID_STRID_METERING */ 
	{ "По центру ", 18 },			/* LV_PLUGIN_STRING_ID_STRID_METER_CENTER */ 
	{ "Пятно", 10 },			/* LV_PLUGIN_STRING_ID_STRID_METER_SPOT */ 
	{ "средний", 14 },			/* LV_PLUGIN_STRING_ID_STRID_METER_AVG */ 
	{ "Режим съемки", 23 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_MODE */ 
	{ "Одиночный", 18 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_SINGLE */ 
	{ "Серия", 10 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_BURST */ 
	{ "Серия 3 фото ", 22 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_BURST_3 */ 
	{ "Авто- экспозиция", 30 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_AUTO */ 
	{ "2 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_TIMER2S */ 
	{ "5 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_TIMER5S */ 
	{ "10 сек.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_TIMER10S */ 
	{ "20сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_TIMER20S */ 
	{ "Вспышка", 14 },			/* LV_PLUGIN_STRING_ID_STRID_FLASHMODE */ 
	{ "Включено", 16 },			/* LV_PLUGIN_STRING_ID_STRID_FLASHON */ 
	{ "Выключено", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FLASHOFF */ 
	{ "Автомат", 14 },			/* LV_PLUGIN_STRING_ID_STRID_FLASHAUTO */ 
	{ "Фильтр \"красных глаз\"", 40 },			/* LV_PLUGIN_STRING_ID_STRID_REDEYE */ 
	{ "AV", 2 },			/* LV_PLUGIN_STRING_ID_STRID_AV */ 
	{ "TV", 2 },			/* LV_PLUGIN_STRING_ID_STRID_TV */ 
	{ "AV / TV", 7 },			/* LV_PLUGIN_STRING_ID_STRID_AVTV */ 
	{ "AV настройки", 21 },			/* LV_PLUGIN_STRING_ID_STRID_AVSETTING */ 
	{ "установка Tv", 21 },			/* LV_PLUGIN_STRING_ID_STRID_TVSETTING */ 
	{ "AV / TV настройки", 26 },			/* LV_PLUGIN_STRING_ID_STRID_AVTVSETTING */ 
	{ "Режим съемки", 23 },			/* LV_PLUGIN_STRING_ID_STRID_SCENESETTING */ 
	{ "Режим", 10 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE */ 
	{ "Пейзаж", 12 },			/* LV_PLUGIN_STRING_ID_STRID_LANDSCAPE */ 
	{ "Ночь", 8 },			/* LV_PLUGIN_STRING_ID_STRID_NIGHTSCENE */ 
	{ "Спорт", 10 },			/* LV_PLUGIN_STRING_ID_STRID_SPORTS */ 
	{ "портрет", 14 },			/* LV_PLUGIN_STRING_ID_STRID_PORTRAIT */ 
	{ "Цветочная", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FLOWER */ 
	{ "Авто режим", 19 },			/* LV_PLUGIN_STRING_ID_STRID_SMART */ 
	{ "Подсветка", 18 },			/* LV_PLUGIN_STRING_ID_STRID_BACKLIGHT */ 
	{ "Цветной", 14 },			/* LV_PLUGIN_STRING_ID_STRID_COLOR */ 
	{ "Стандарт", 16 },			/* LV_PLUGIN_STRING_ID_STRID_COLOR_FULL */ 
	{ "Черно белый", 21 },			/* LV_PLUGIN_STRING_ID_STRID_COLOR_BW */ 
	{ "Коричневый", 20 },			/* LV_PLUGIN_STRING_ID_STRID_COLOR_SEPIA */ 
	{ "Резкий", 12 },			/* LV_PLUGIN_STRING_ID_STRID_SHARPNESS */ 
	{ "Сильный", 14 },			/* LV_PLUGIN_STRING_ID_STRID_STRONG */ 
	{ "Мягкий", 12 },			/* LV_PLUGIN_STRING_ID_STRID_SOFT */ 
	{ "Низкий", 12 },			/* LV_PLUGIN_STRING_ID_STRID_LOW */ 
	{ "Средний", 14 },			/* LV_PLUGIN_STRING_ID_STRID_MED */ 
	{ "Высокий", 14 },			/* LV_PLUGIN_STRING_ID_STRID_HIGH */ 
	{ "Штамп дата/время", 30 },			/* LV_PLUGIN_STRING_ID_STRID_DATE_STAMP */ 
	{ "Дата / время", 21 },			/* LV_PLUGIN_STRING_ID_STRID_DATE_TIME */ 
	{ "Дата", 8 },			/* LV_PLUGIN_STRING_ID_STRID_DATE */ 
	{ "Время", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TIME */ 
	{ "ГГ/ММ/ДД", 14 },			/* LV_PLUGIN_STRING_ID_STRID_Y_M_D */ 
	{ "ДД/ММ/ГГ", 14 },			/* LV_PLUGIN_STRING_ID_STRID_D_M_Y */ 
	{ "ММ/ДД/ГГ", 14 },			/* LV_PLUGIN_STRING_ID_STRID_M_D_Y */ 
	{ "Вкл.", 7 },			/* LV_PLUGIN_STRING_ID_STRID_ON */ 
	{ "Выкл.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_OFF */ 
	{ "Цифровой зум", 23 },			/* LV_PLUGIN_STRING_ID_STRID_DZ */ 
	{ "Быстрый просмотр", 31 },			/* LV_PLUGIN_STRING_ID_STRID_QUICK_VIEW */ 
	{ "Контрастность", 26 },			/* LV_PLUGIN_STRING_ID_STRID_SATURATION */ 
	{ "Видео", 10 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIE */ 
	{ "Частота съемки ", 28 },			/* LV_PLUGIN_STRING_ID_STRID_FRAMERATE */ 
	{ "30 к/сек", 12 },			/* LV_PLUGIN_STRING_ID_STRID_30FPS */ 
	{ "15 к/сек", 12 },			/* LV_PLUGIN_STRING_ID_STRID_15FPS */ 
	{ "10  к/сек", 13 },			/* LV_PLUGIN_STRING_ID_STRID_10FPS */ 
	{ "1  к/сек", 12 },			/* LV_PLUGIN_STRING_ID_STRID_1FPS */ 
	{ "Видео", 10 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO */ 
	{ "Аудио", 10 },			/* LV_PLUGIN_STRING_ID_STRID_AUDIO */ 
	{ "Настройки", 18 },			/* LV_PLUGIN_STRING_ID_STRID_SETUP */ 
	{ "Частота освещения", 33 },			/* LV_PLUGIN_STRING_ID_STRID_FREQUENCY */ 
	{ "50 Hz", 5 },			/* LV_PLUGIN_STRING_ID_STRID_50HZ */ 
	{ "60 Hz", 5 },			/* LV_PLUGIN_STRING_ID_STRID_60HZ */ 
	{ "Выбор памяти", 23 },			/* LV_PLUGIN_STRING_ID_STRID_MEDIA */ 
	{ "Выбор места хранения", 38 },			/* LV_PLUGIN_STRING_ID_STRID_STORAGE */ 
	{ "Внутренняя память", 33 },			/* LV_PLUGIN_STRING_ID_STRID_INT_FLASH */ 
	{ "TF карта", 13 },			/* LV_PLUGIN_STRING_ID_STRID_EXT_CARD */ 
	{ "Показывать заставку", 37 },			/* LV_PLUGIN_STRING_ID_STRID_LOGO_DISPLAY */ 
	{ "Открыть ", 15 },			/* LV_PLUGIN_STRING_ID_STRID_OPENING */ 
	{ "Формат", 12 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT */ 
	{ "ОК", 4 },			/* LV_PLUGIN_STRING_ID_STRID_OK */ 
	{ "Отмена", 12 },			/* LV_PLUGIN_STRING_ID_STRID_CANCEL */ 
	{ "Звук клавиш", 21 },			/* LV_PLUGIN_STRING_ID_STRID_BEEPER */ 
	{ "Громко", 12 },			/* LV_PLUGIN_STRING_ID_STRID_BEEP_LOUD */ 
	{ "Тихо", 8 },			/* LV_PLUGIN_STRING_ID_STRID_BEEP_SOFT */ 
	{ "Язык", 8 },			/* LV_PLUGIN_STRING_ID_STRID_LANGUAGE */ 
	{ "English", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_EN */ 
	{ "Français", 9 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_FR */ 
	{ "Español", 8 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_ES */ 
	{ "Deutsch", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_DE */ 
	{ "Italiano", 8 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_IT */ 
	{ "繁體中文", 12 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_TC */ 
	{ "简体中文", 12 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_SC */ 
	{ "日本語", 9 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_JP */ 
	{ "Português", 10 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_PO */ 
	{ "Русский", 14 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_RU */ 
	{ "USB", 3 },			/* LV_PLUGIN_STRING_ID_STRID_USB */ 
	{ "Режим РС", 15 },			/* LV_PLUGIN_STRING_ID_STRID_PC_MODE */ 
	{ "Флэш-память", 21 },			/* LV_PLUGIN_STRING_ID_STRID_MSDC */ 
	{ "PC камера", 15 },			/* LV_PLUGIN_STRING_ID_STRID_PCC */ 
	{ "Pictbridge", 10 },			/* LV_PLUGIN_STRING_ID_STRID_PICTBRIDGE */ 
	{ "Поручать силы ", 26 },			/* LV_PLUGIN_STRING_ID_STRID_USBCHARGE */ 
	{ "режим TV", 13 },			/* LV_PLUGIN_STRING_ID_STRID_TV_MODE */ 
	{ "NTSC", 4 },			/* LV_PLUGIN_STRING_ID_STRID_TV_NTSC */ 
	{ "PAL", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TV_PAL */ 
	{ "Яркость", 14 },			/* LV_PLUGIN_STRING_ID_STRID_BRIGHTNESS */ 
	{ "Авто выключение", 29 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF */ 
	{ "1 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_1MIN */ 
	{ "2 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_2MIN */ 
	{ "3 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_3MIN */ 
	{ "5 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_5MIN */ 
	{ "10 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_OFF_10MIN */ 
	{ "1 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_1MIN */ 
	{ "2 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_2MIN */ 
	{ "3 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_3MIN */ 
	{ "5 мин.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_5MIN */ 
	{ "10 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_10MIN */ 
	{ "15 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_15MIN */ 
	{ "20 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_20MIN */ 
	{ "25 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_25MIN */ 
	{ "30 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_30MIN */ 
	{ "Цикл записи (мин)", 30 },			/* LV_PLUGIN_STRING_ID_STRID_CYCLIC_REC */ 
	{ "Flash Record", 12 },			/* LV_PLUGIN_STRING_ID_STRID_FLASH_REC */ 
	{ "Golf Shot", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GOLF_REC */ 
	{ "Нет", 6 },			/* LV_PLUGIN_STRING_ID_STRID_NONE */ 
	{ "Сбросить номер", 27 },			/* LV_PLUGIN_STRING_ID_STRID_RESET_NUM */ 
	{ "Перезагрузить", 26 },			/* LV_PLUGIN_STRING_ID_STRID_DEFAULT_SETTING */ 
	{ "Да", 4 },			/* LV_PLUGIN_STRING_ID_STRID_YES */ 
	{ "Нет", 6 },			/* LV_PLUGIN_STRING_ID_STRID_NO */ 
	{ "Версия ПО", 17 },			/* LV_PLUGIN_STRING_ID_STRID_VERSION */ 
	{ "Воспроизведение", 30 },			/* LV_PLUGIN_STRING_ID_STRID_PLAYBACK */ 
	{ "Ракурс ", 13 },			/* LV_PLUGIN_STRING_ID_STRID_THUMBNAIL */ 
	{ "Установка  логотипа", 36 },			/* LV_PLUGIN_STRING_ID_STRID_SET_LOGO */ 
	{ "Повернуть", 18 },			/* LV_PLUGIN_STRING_ID_STRID_ROTATE */ 
	{ "Повернуть", 18 },			/* LV_PLUGIN_STRING_ID_STRID_ROTATE_S */ 
	{ "Повернуть 90°", 23 },			/* LV_PLUGIN_STRING_ID_STRID_ROTATE_90 */ 
	{ "Повернуть 180°", 24 },			/* LV_PLUGIN_STRING_ID_STRID_ROTATE_180 */ 
	{ "Повернуть 270°", 24 },			/* LV_PLUGIN_STRING_ID_STRID_ROTATE_270 */ 
	{ "Обрезать", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CROP */ 
	{ "Обрезать", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CROP_S */ 
	{ "Слайд-шоу", 17 },			/* LV_PLUGIN_STRING_ID_STRID_SLIDE_SHOW */ 
	{ "2 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_2SEC */ 
	{ "3 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_3SEC */ 
	{ "5 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_5SEC */ 
	{ "8 сек.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_8SEC */ 
	{ "10 сек.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_10SEC */ 
	{ "Защита", 12 },			/* LV_PLUGIN_STRING_ID_STRID_PROTECT */ 
	{ "Защитить одну", 25 },			/* LV_PLUGIN_STRING_ID_STRID_PROTECTONE */ 
	{ "Защитить все", 23 },			/* LV_PLUGIN_STRING_ID_STRID_PROTECTALL */ 
	{ "Блокировка", 20 },			/* LV_PLUGIN_STRING_ID_STRID_LOCK */ 
	{ "Заблокировать  фотографию", 48 },			/* LV_PLUGIN_STRING_ID_STRID_LOCKONE */ 
	{ "Заблок.все изображ", 34 },			/* LV_PLUGIN_STRING_ID_STRID_LOCKALL */ 
	{ "Заблокировать  ", 28 },			/* LV_PLUGIN_STRING_ID_STRID_LOCKSELECTED */ 
	{ "Разблокировка", 26 },			/* LV_PLUGIN_STRING_ID_STRID_UNLOCK */ 
	{ "Разблокировать фотографию ", 50 },			/* LV_PLUGIN_STRING_ID_STRID_UNLOCKONE */ 
	{ "Разблок. все изображ", 37 },			/* LV_PLUGIN_STRING_ID_STRID_UNLOCKALL */ 
	{ "Разблокировать выбранный", 47 },			/* LV_PLUGIN_STRING_ID_STRID_UNLOCKSELECTED */ 
	{ "DPOF", 4 },			/* LV_PLUGIN_STRING_ID_STRID_DPOF */ 
	{ "Одно изображение", 31 },			/* LV_PLUGIN_STRING_ID_STRID_ONEIMAGE */ 
	{ "Все изображения", 29 },			/* LV_PLUGIN_STRING_ID_STRID_ALL_IMAGES */ 
	{ "Данное изображение", 35 },			/* LV_PLUGIN_STRING_ID_STRID_THIS_IMAGE */ 
	{ "Данное видео", 23 },			/* LV_PLUGIN_STRING_ID_STRID_THIS_VIDEO */ 
	{ "Выбрать изображение", 37 },			/* LV_PLUGIN_STRING_ID_STRID_SELECT_IMAGES */ 
	{ "Все индексы", 21 },			/* LV_PLUGIN_STRING_ID_STRID_ALL_INDEX */ 
	{ "Все", 6 },			/* LV_PLUGIN_STRING_ID_STRID_ALL */ 
	{ "Переустановить все", 35 },			/* LV_PLUGIN_STRING_ID_STRID_RESETALL */ 
	{ "Количество", 20 },			/* LV_PLUGIN_STRING_ID_STRID_COPIES */ 
	{ "Вернуться", 18 },			/* LV_PLUGIN_STRING_ID_STRID_RETURN */ 
	{ "Изменение размера", 33 },			/* LV_PLUGIN_STRING_ID_STRID_RESIZE */ 
	{ "Изменение качества", 35 },			/* LV_PLUGIN_STRING_ID_STRID_QUALITYCHANGE */ 
	{ "Копировать на карту", 36 },			/* LV_PLUGIN_STRING_ID_STRID_COPY_TO_CARD */ 
	{ "Копировать с карты", 34 },			/* LV_PLUGIN_STRING_ID_STRID_COPY_FROM_CARD */ 
	{ "Копировать", 20 },			/* LV_PLUGIN_STRING_ID_STRID_COPY */ 
	{ "На TF карту памяти", 31 },			/* LV_PLUGIN_STRING_ID_STRID_TOSD */ 
	{ "На внутреннюю память", 38 },			/* LV_PLUGIN_STRING_ID_STRID_TOINTERNAL */ 
	{ "Удалить", 14 },			/* LV_PLUGIN_STRING_ID_STRID_DELETE */ 
	{ "Удалить зту фотографию", 42 },			/* LV_PLUGIN_STRING_ID_STRID_DELETECURRENT */ 
	{ "Удалить все", 21 },			/* LV_PLUGIN_STRING_ID_STRID_DELETEALL */ 
	{ "Удалить  выбранное", 34 },			/* LV_PLUGIN_STRING_ID_STRID_DELETESELECTED */ 
	{ "Обработка данных", 31 },			/* LV_PLUGIN_STRING_ID_STRID_DATAPROCESSED */ 
	{ "Выберите", 16 },			/* LV_PLUGIN_STRING_ID_STRID_SELECT */ 
	{ "Страница", 16 },			/* LV_PLUGIN_STRING_ID_STRID_PAGE */ 
	{ "Выбрать режим печати", 38 },			/* LV_PLUGIN_STRING_ID_STRID_PRINTMODESEL */ 
	{ "Размер  ", 14 },			/* LV_PLUGIN_STRING_ID_STRID_SIZE */ 
	{ "Стандарт", 16 },			/* LV_PLUGIN_STRING_ID_STRID_STANDARD */ 
	{ "Продолжить", 20 },			/* LV_PLUGIN_STRING_ID_STRID_CONTINUE */ 
	{ "Без ", 7 },			/* LV_PLUGIN_STRING_ID_STRID_WITHOUT */ 
	{ "С", 2 },			/* LV_PLUGIN_STRING_ID_STRID_WITH */ 
	{ "Наименование файла", 35 },			/* LV_PLUGIN_STRING_ID_STRID_NAME */ 
	{ "Нет изображения", 29 },			/* LV_PLUGIN_STRING_ID_STRID_NO_IMAGE */ 
	{ "Настройки", 18 },			/* LV_PLUGIN_STRING_ID_STRID_SET */ 
	{ "Внутренняя память полная", 46 },			/* LV_PLUGIN_STRING_ID_STRID_MEMORY_FULL */ 
	{ "Карта памяти заполнена", 42 },			/* LV_PLUGIN_STRING_ID_STRID_CARD_FULL */ 
	{ "Папка заполнена", 29 },			/* LV_PLUGIN_STRING_ID_STRID_FOLDERFULL */ 
	{ "Ошибка карты", 23 },			/* LV_PLUGIN_STRING_ID_STRID_CARDERROR */ 
	{ "Ошибка памяти", 25 },			/* LV_PLUGIN_STRING_ID_STRID_MEMORYERROR */ 
	{ "Ошибка объектива", 31 },			/* LV_PLUGIN_STRING_ID_STRID_LENSERROR */ 
	{ "Карта памяти защищена", 40 },			/* LV_PLUGIN_STRING_ID_STRID_CARD_LOCKED */ 
	{ "Защищено!", 17 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_PROTECT */ 
	{ "Ошибка изображения", 35 },			/* LV_PLUGIN_STRING_ID_STRID_PICTUREERROR */ 
	{ "Батарея разряжена", 33 },			/* LV_PLUGIN_STRING_ID_STRID_BATTERY_LOW */ 
	{ "Подождите …", 22 },			/* LV_PLUGIN_STRING_ID_STRID_ONEMOMENT */ 
	{ "Нет соединения", 27 },			/* LV_PLUGIN_STRING_ID_STRID_NOCONNECTION */ 
	{ "Идет передача …", 29 },			/* LV_PLUGIN_STRING_ID_STRID_TRANSFERRING */ 
	{ "Соединение с ПК", 28 },			/* LV_PLUGIN_STRING_ID_STRID_CONNECTEDTOPC */ 
	{ "Извлечь USB кабель", 31 },			/* LV_PLUGIN_STRING_ID_STRID_REMOVEUSBCABLE */ 
	{ "Всего", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TOTAL */ 
	{ "Штамп даты", 19 },			/* LV_PLUGIN_STRING_ID_STRID_DATE_STAMPING */ 
	{ "Имя файла", 17 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_NAME */ 
	{ "Количество копий", 31 },			/* LV_PLUGIN_STRING_ID_STRID_NO_OF_COPY */ 
	{ "По умолчанию", 23 },			/* LV_PLUGIN_STRING_ID_STRID_DEFAULT */ 
	{ "Меню", 8 },			/* LV_PLUGIN_STRING_ID_STRID_MENU */ 
	{ "Выход", 10 },			/* LV_PLUGIN_STRING_ID_STRID_EXIT */ 
	{ "Пожалуйста, подождите", 40 },			/* LV_PLUGIN_STRING_ID_STRID_PLEASE_WAIT */ 
	{ "Начать: затвор ", 27 },			/* LV_PLUGIN_STRING_ID_STRID_STARTSHUTTER */ 
	{ "Остановить : затвор", 35 },			/* LV_PLUGIN_STRING_ID_STRID_STOPSHUTTER */ 
	{ "Нет файла", 17 },			/* LV_PLUGIN_STRING_ID_STRID_NO_FILE */ 
	{ "Нет карты", 17 },			/* LV_PLUGIN_STRING_ID_STRID_NO_CARD */ 
	{ "Нет фото", 15 },			/* LV_PLUGIN_STRING_ID_STRID_NO_PHOTO */ 
	{ "Файл не JPEG формата", 33 },			/* LV_PLUGIN_STRING_ID_STRID_NOT_JPEG */ 
	{ "Вспышка не готова ", 33 },			/* LV_PLUGIN_STRING_ID_STRID_FLASHNOTREADY */ 
	{ "Обновление граф.", 30 },			/* LV_PLUGIN_STRING_ID_STRID_UPDATEBG */ 
	{ "Проверить версию", 31 },			/* LV_PLUGIN_STRING_ID_STRID_CHECKVERSION */ 
	{ "Ошибка Pcstore", 20 },			/* LV_PLUGIN_STRING_ID_STRID_PSTOREERR */ 
	{ "Воспроизвести", 26 },			/* LV_PLUGIN_STRING_ID_STRID_PLAY */ 
	{ "Пауза", 10 },			/* LV_PLUGIN_STRING_ID_STRID_PAUSE */ 
	{ "Стоп", 8 },			/* LV_PLUGIN_STRING_ID_STRID_STOP */ 
	{ "Двигать", 14 },			/* LV_PLUGIN_STRING_ID_STRID_MOVE */ 
	{ "Сохранить", 18 },			/* LV_PLUGIN_STRING_ID_STRID_SAVE */ 
	{ "Следующий", 18 },			/* LV_PLUGIN_STRING_ID_STRID_NEXT */ 
	{ "Изменить", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CHANGE */ 
	{ "Громкость", 18 },			/* LV_PLUGIN_STRING_ID_STRID_VOLUME */ 
	{ "Фотографировать", 30 },			/* LV_PLUGIN_STRING_ID_STRID_STILL */ 
	{ "Тип батареи", 21 },			/* LV_PLUGIN_STRING_ID_STRID_BATTERY_TYPE */ 
	{ "Alkaline", 8 },			/* LV_PLUGIN_STRING_ID_STRID_ALKALINE */ 
	{ "NiMH", 4 },			/* LV_PLUGIN_STRING_ID_STRID_NIMH */ 
	{ "Все данные будут удалены", 45 },			/* LV_PLUGIN_STRING_ID_STRID_DELETE_WARNING */ 
	{ "Номер серии", 21 },			/* LV_PLUGIN_STRING_ID_STRID_SEQUENCE_NO */ 
	{ "Сброс на заводские установки ", 54 },			/* LV_PLUGIN_STRING_ID_STRID_RESET_WARNING */ 
	{ "Удалить выбранный ?", 35 },			/* LV_PLUGIN_STRING_ID_STRID_ERASE_THIS */ 
	{ "Удалить все изображения ?", 46 },			/* LV_PLUGIN_STRING_ID_STRID_ERASE_ALL */ 
	{ "Изображение", 22 },			/* LV_PLUGIN_STRING_ID_STRID_IMAGES */ 
	{ "Подключите устройство", 41 },			/* LV_PLUGIN_STRING_ID_STRID_CONNECT_TO_DEVICE */ 
	{ "Подключено", 20 },			/* LV_PLUGIN_STRING_ID_STRID_DEVICE_IS_CONNECTED */ 
	{ "Ошибка соединения", 33 },			/* LV_PLUGIN_STRING_ID_STRID_LINK_ERROR */ 
	{ "Ошибка USB ", 17 },			/* LV_PLUGIN_STRING_ID_STRID_USB_ERROR */ 
	{ "a\\", 3 },			/* LV_PLUGIN_STRING_ID_STRID_DUMMY */ 
	{ "-1/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M0P3 */ 
	{ "-2/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M0P6 */ 
	{ "-1.0", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M1P0 */ 
	{ "-4/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M1P3 */ 
	{ "-5/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M1P6 */ 
	{ "-2.0", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_M2P0 */ 
	{ "+0.0", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P0P0 */ 
	{ "+1/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P0P3 */ 
	{ "+2/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P0P6 */ 
	{ "+1.0", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P1P0 */ 
	{ "+4/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P1P3 */ 
	{ "+5/3", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P1P6 */ 
	{ "2", 1 },			/* LV_PLUGIN_STRING_ID_STRID_EV_P2P0 */ 
	{ "Печатать все", 23 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_ALL */ 
	{ "Печатать индексы", 31 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_INDEX */ 
	{ "DPOF  печать", 18 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_DPOF */ 
	{ "Настройка печати", 31 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_SETTING */ 
	{ "перезапуск DPOF ", 26 },			/* LV_PLUGIN_STRING_ID_STRID_DPOF_RESTART */ 
	{ "Печать", 12 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT */ 
	{ "Начало печати", 25 },			/* LV_PLUGIN_STRING_ID_STRID_START_PRINTING */ 
	{ "Идет печать…", 24 },			/* LV_PLUGIN_STRING_ID_STRID_PRINTING */ 
	{ "Печать отменена", 29 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_CANCELED */ 
	{ "Печать закончена", 31 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_FINISHED */ 
	{ "Для печати нажмите ОК", 39 },			/* LV_PLUGIN_STRING_ID_STRID_OK_TO_PRINT */ 
	{ "Размер бумаги", 25 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_SIZE */ 
	{ "L", 1 },			/* LV_PLUGIN_STRING_ID_STRID_L */ 
	{ "2L", 2 },			/* LV_PLUGIN_STRING_ID_STRID_2L */ 
	{ "Открытка", 16 },			/* LV_PLUGIN_STRING_ID_STRID_POSTCARD */ 
	{ "Карта памяти ", 24 },			/* LV_PLUGIN_STRING_ID_STRID_CARD */ 
	{ "100x150", 7 },			/* LV_PLUGIN_STRING_ID_STRID_100X150 */ 
	{ "4\"x6\"", 7 },			/* LV_PLUGIN_STRING_ID_STRID_4X6 */ 
	{ "8\"x10\"", 8 },			/* LV_PLUGIN_STRING_ID_STRID_8X10 */ 
	{ "Письмо", 12 },			/* LV_PLUGIN_STRING_ID_STRID_LETTER */ 
	{ "11\"x17\"", 9 },			/* LV_PLUGIN_STRING_ID_STRID_11X17 */ 
	{ "A0", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A0 */ 
	{ "A1", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A1 */ 
	{ "A2", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A2 */ 
	{ "A3", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A3 */ 
	{ "A4", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A4 */ 
	{ "A5", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A5 */ 
	{ "A6", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A6 */ 
	{ "A7", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A7 */ 
	{ "A8", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A8 */ 
	{ "A9", 2 },			/* LV_PLUGIN_STRING_ID_STRID_A9 */ 
	{ "B0", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B0 */ 
	{ "B1", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B1 */ 
	{ "B2", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B2 */ 
	{ "B3", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B3 */ 
	{ "B4", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B4 */ 
	{ "B5", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B5 */ 
	{ "B6", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B6 */ 
	{ "B7", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B7 */ 
	{ "B8", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B8 */ 
	{ "B9", 2 },			/* LV_PLUGIN_STRING_ID_STRID_B9 */ 
	{ "Крен L", 10 },			/* LV_PLUGIN_STRING_ID_STRID_L_ROLLS */ 
	{ "Крен 2L", 11 },			/* LV_PLUGIN_STRING_ID_STRID_2L_ROLLS */ 
	{ "Крен 4", 10 },			/* LV_PLUGIN_STRING_ID_STRID_4_ROLLS */ 
	{ "Крен A4", 11 },			/* LV_PLUGIN_STRING_ID_STRID_A4_ROLLS */ 
	{ "Тип бумаги", 19 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_TYPE */ 
	{ "Фотобумага", 20 },			/* LV_PLUGIN_STRING_ID_STRID_PHOTO_PAPER */ 
	{ "Обычная бумага", 27 },			/* LV_PLUGIN_STRING_ID_STRID_PLAIN_PAPER */ 
	{ "Быстрое фото", 23 },			/* LV_PLUGIN_STRING_ID_STRID_FAST_PHOTO */ 
	{ "Тип файла", 17 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_TYPE */ 
	{ "Exif/JPEG", 9 },			/* LV_PLUGIN_STRING_ID_STRID_EXIF_JPEG */ 
	{ "Exif", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EXIF */ 
	{ "JPEG", 4 },			/* LV_PLUGIN_STRING_ID_STRID_JPEG */ 
	{ "Печатать дату", 25 },			/* LV_PLUGIN_STRING_ID_STRID_DATE_PRINT */ 
	{ "Печатать наименование файла", 52 },			/* LV_PLUGIN_STRING_ID_STRID_FILENAME_PRINT */ 
	{ "Оптимизировать изображение", 51 },			/* LV_PLUGIN_STRING_ID_STRID_IMAGE_OPTIMIZE */ 
	{ "Разметка страниц", 31 },			/* LV_PLUGIN_STRING_ID_STRID_LAYOUT */ 
	{ "STRID_1UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_1UP */ 
	{ "STRID_2UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_2UP */ 
	{ "STRID_3UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_3UP */ 
	{ "STRID_4UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_4UP */ 
	{ "STRID_5UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_5UP */ 
	{ "STRID_6UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_6UP */ 
	{ "STRID_7UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_7UP */ 
	{ "STRID_8UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_8UP */ 
	{ "STRID_9UP", 9 },			/* LV_PLUGIN_STRING_ID_STRID_9UP */ 
	{ "STRID_10UP", 10 },			/* LV_PLUGIN_STRING_ID_STRID_10UP */ 
	{ "STRID_250UP", 11 },			/* LV_PLUGIN_STRING_ID_STRID_250UP */ 
	{ "Индек", 10 },			/* LV_PLUGIN_STRING_ID_STRID_INDEX */ 
	{ "Без полей", 17 },			/* LV_PLUGIN_STRING_ID_STRID_1UP_BORDERLESS */ 
	{ "Установленный размер", 39 },			/* LV_PLUGIN_STRING_ID_STRID_FIXED_SIZE */ 
	{ "2.5\"x3.25\"", 12 },			/* LV_PLUGIN_STRING_ID_STRID_25X325 */ 
	{ "3.5\"x5\"", 9 },			/* LV_PLUGIN_STRING_ID_STRID_35X5 */ 
	{ "254x178", 7 },			/* LV_PLUGIN_STRING_ID_STRID_254X178 */ 
	{ "110x74", 6 },			/* LV_PLUGIN_STRING_ID_STRID_110X74 */ 
	{ "89x55", 5 },			/* LV_PLUGIN_STRING_ID_STRID_89X55 */ 
	{ "6x8", 3 },			/* LV_PLUGIN_STRING_ID_STRID_6X8 */ 
	{ "7x10", 4 },			/* LV_PLUGIN_STRING_ID_STRID_7X10 */ 
	{ "9x13", 4 },			/* LV_PLUGIN_STRING_ID_STRID_9X13 */ 
	{ "13x18", 5 },			/* LV_PLUGIN_STRING_ID_STRID_13X18 */ 
	{ "15x21", 5 },			/* LV_PLUGIN_STRING_ID_STRID_15X21 */ 
	{ "18x24", 5 },			/* LV_PLUGIN_STRING_ID_STRID_18X24 */ 
	{ "Вырезать", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CROPPING */ 
	{ "Ошибка печати", 25 },			/* LV_PLUGIN_STRING_ID_STRID_PRINT_ERROR */ 
	{ "Принтер может быть отключен", 51 },			/* LV_PLUGIN_STRING_ID_STRID_PRINTER_DISCONNECTABLE */ 
	{ "Ошибка бумаги", 25 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_ERROR */ 
	{ "Бумага закончилась ", 36 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_OUT */ 
	{ "Бумага не загружена", 36 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_LOAD_ERROR */ 
	{ "Бумана не выпущена", 34 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_EJECT_ERROR */ 
	{ "Бумага не распознана", 38 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_MEDIA_ERROR */ 
	{ "Зажатие бумаги", 27 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_JAMMED */ 
	{ "Бумага заканчивается", 39 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_NEAR_EMPTY */ 
	{ "Формат бумаги не поддерживается", 59 },			/* LV_PLUGIN_STRING_ID_STRID_PAPER_NOT_SUPPORT */ 
	{ "Ошибка краски ", 26 },			/* LV_PLUGIN_STRING_ID_STRID_INK_ERROR */ 
	{ "Краска закончилась", 35 },			/* LV_PLUGIN_STRING_ID_STRID_INK_EMPTY */ 
	{ "Краска заканчивается", 39 },			/* LV_PLUGIN_STRING_ID_STRID_INK_LOW */ 
	{ "Ошибка краски ", 26 },			/* LV_PLUGIN_STRING_ID_STRID_INK_WASTE */ 
	{ "Ошибка принтера", 29 },			/* LV_PLUGIN_STRING_ID_STRID_HW_ERROR */ 
	{ "Среьезная ошибка принтера", 48 },			/* LV_PLUGIN_STRING_ID_STRID_HW_FATAL */ 
	{ "Свяжитесь с центром по ремонту", 56 },			/* LV_PLUGIN_STRING_ID_STRID_HW_SERVICE_CALL */ 
	{ "Принтер не доступен", 36 },			/* LV_PLUGIN_STRING_ID_STRID_HW_UNAVAILABLE */ 
	{ "Принтер занят", 25 },			/* LV_PLUGIN_STRING_ID_STRID_HW_BUSY */ 
	{ "Ошибка принтера", 29 },			/* LV_PLUGIN_STRING_ID_STRID_HW_LEVER */ 
	{ "Открыта крышка", 27 },			/* LV_PLUGIN_STRING_ID_STRID_HW_COVER_OPEN */ 
	{ "Ошибка принтера", 29 },			/* LV_PLUGIN_STRING_ID_STRID_HW_NO_MARKING_AGENT */ 
	{ "Крышка краски открыта", 40 },			/* LV_PLUGIN_STRING_ID_STRID_HW_INK_COVER_OPEN */ 
	{ "Картридж краски не установлен", 55 },			/* LV_PLUGIN_STRING_ID_STRID_HW_NO_INK_CARTRIDGE */ 
	{ "Ошибка файла", 23 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_ERROR */ 
	{ "Ошибка информации печати", 46 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_PRINT_INFO */ 
	{ "Ошибка раскодирования файла", 52 },			/* LV_PLUGIN_STRING_ID_STRID_FILE_DECODE_ERROR */ 
	{ "Неизвестная ошибка", 35 },			/* LV_PLUGIN_STRING_ID_STRID_UNKNOW_ERROR */ 
	{ "Ошибка  XML", 17 },			/* LV_PLUGIN_STRING_ID_STRID_XML_SYNTAX_ERROR */ 
	{ "Датчик движения", 29 },			/* LV_PLUGIN_STRING_ID_STRID_MOTION_DET */ 
	{ "Распознавание лица", 35 },			/* LV_PLUGIN_STRING_ID_STRID_FACE_DET */ 
	{ "Распознавание улыбки", 39 },			/* LV_PLUGIN_STRING_ID_STRID_SMILE_DET */ 
	{ "Стабилизация", 24 },			/* LV_PLUGIN_STRING_ID_STRID_ANTI_SHAKING */ 
	{ "Нет видео", 17 },			/* LV_PLUGIN_STRING_ID_STRID_NO_MOVIE */ 
	{ "MP3", 3 },			/* LV_PLUGIN_STRING_ID_STRID_MP3PLAY */ 
	{ "Нет МР3 файла", 23 },			/* LV_PLUGIN_STRING_ID_STRID_NO_MP3FILE */ 
	{ "Поворот изображения", 37 },			/* LV_PLUGIN_STRING_ID_STRID_SENSOR_ROTATE */ 
	{ "Показатель видео", 31 },			/* LV_PLUGIN_STRING_ID_STRID_RECORD */ 
	{ "Рекордное аудио", 29 },			/* LV_PLUGIN_STRING_ID_STRID_RECORD_AUDIO */ 
	{ "Установка светильника", 41 },			/* LV_PLUGIN_STRING_ID_STRID_LED_SETTING */ 
	{ "до свидания", 21 },			/* LV_PLUGIN_STRING_ID_STRID_GOOD_BYE */ 
	{ "Пожалуйста, вставьте TF-КАРТЫ", 52 },			/* LV_PLUGIN_STRING_ID_STRID_PLEASE_INSERT_SD */ 
	{ "IR LED", 6 },			/* LV_PLUGIN_STRING_ID_STRID_IR_LED */ 
	{ "микрофон", 16 },			/* LV_PLUGIN_STRING_ID_STRID_MICROPHONE */ 
	{ "Custer size wrong.\nPlease format", 33 },			/* LV_PLUGIN_STRING_ID_STRID_CLUSTER_WRONG */ 
	{ "TF card write speed too slow,please replace a higher speed card.", 64 },			/* LV_PLUGIN_STRING_ID_STRID_SD_CLASS10 */ 
	{ "Need Class6 or Higher TF Card", 29 },			/* LV_PLUGIN_STRING_ID_STRID_SD_CLASS6 */ 
	{ "Need Class4 or Higher TF Card", 29 },			/* LV_PLUGIN_STRING_ID_STRID_SD_CLASS4 */ 
	{ "HDR", 3 },			/* LV_PLUGIN_STRING_ID_STRID_HDR */ 
	{ "GPS", 3 },			/* LV_PLUGIN_STRING_ID_STRID_GPS */ 
	{ "G-Sensor", 8 },			/* LV_PLUGIN_STRING_ID_STRID_GSENSOR */ 
	{ "хранитель экрана", 31 },			/* LV_PLUGIN_STRING_ID_STRID_SCREEN_SAVER */ 
	{ "Low Sensitivity", 15 },			/* LV_PLUGIN_STRING_ID_STRID_LOW_SENSITIVITY */ 
	{ "Middle Sensitivity", 18 },			/* LV_PLUGIN_STRING_ID_STRID_MIDDLE_SENSITIVITY */ 
	{ "High Sensitivity", 16 },			/* LV_PLUGIN_STRING_ID_STRID_HIGH_SENSITIVITY */ 
	{ "CarNo", 5 },			/* LV_PLUGIN_STRING_ID_STRID_CARNO */ 
	{ "Camera Mode", 11 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA_MODE */ 
	{ "Colock  1Min", 12 },			/* LV_PLUGIN_STRING_ID_STRID_COLOCK_1MIN */ 
	{ "Colock  3Min", 12 },			/* LV_PLUGIN_STRING_ID_STRID_COLOCK_3MIN */ 
	{ "Backlight Off", 13 },			/* LV_PLUGIN_STRING_ID_STRID_LCD_BACKLIGHT_OFF */ 
	{ "_", 1 },			/* LV_PLUGIN_STRING_ID_STRID_UNDERLINE */ 
	{ "Интервальная съемка", 37 },			/* LV_PLUGIN_STRING_ID_STRID_TIMER_LAPSE */ 
	{ "1 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_1_HOUR */ 
	{ "2 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_2_HOUR */ 
	{ "3 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_3_HOUR */ 
	{ "Camera Mode Off", 15 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA_MODE_OFF */ 
	{ "Driving,not used Camera Mode", 28 },			/* LV_PLUGIN_STRING_ID_STRID_NOT_USED_CAMERA_MODE */ 
	{ "Change to Normal Mode", 21 },			/* LV_PLUGIN_STRING_ID_STRID_CHANGE_TO_NORMAL_MODE */ 
	{ "Use motion detection, \nyou can not use this mode", 49 },			/* LV_PLUGIN_STRING_ID_STRID_NOT_USED_CAMERA_MODE_IN_MOTIONDET */ 
	{ "Inorder to ensure driving safety,Please format TF Card and reset the system time.", 81 },			/* LV_PLUGIN_STRING_ID_STRID_PLEASE_RESETING_DATE */ 
	{ "Auto Calibration", 16 },			/* LV_PLUGIN_STRING_ID_STRID_GSENSOR_ADJUST */ 
	{ "Format Warning", 14 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING */ 
	{ "15 Days", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_15_DAY */ 
	{ "30 Days", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_30_DAY */ 
	{ "60 Days", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING_60_DAY */ 
	{ "Play List", 9 },			/* LV_PLUGIN_STRING_ID_STRID_PLAY_FILE */ 
	{ "Video File", 10 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FLIE */ 
	{ "Photo File", 10 },			/* LV_PLUGIN_STRING_ID_STRID_PHOTO_FILE */ 
	{ "Video File List", 15 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FILE_LIST */ 
	{ "Photo File List", 15 },			/* LV_PLUGIN_STRING_ID_STRID_PHOTO_FILE_LIST */ 
	{ "Чтобы файлы сохранялись правильно периодически форматируйте SD-карту.", 128 },			/* LV_PLUGIN_STRING_ID_STRID_FORMAT_WARNING1 */ 
	{ "Play", 4 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIEWND_PLAYBACK */ 
	{ "Set", 3 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIEWND_SETTING */ 
	{ "Panel", 5 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIEWND_CLOSELCD */ 
	{ "OK", 2 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIEWND_OK */ 
	{ "Play List", 9 },			/* LV_PLUGIN_STRING_ID_STRID_PLAYBACK_PLAY_LIST */ 
	{ "For your own safety.\r\nDo not operate the device\r\nwhile driving.", 67 },			/* LV_PLUGIN_STRING_ID_STRID_LOGOL_OPEN */ 
	{ "Thank you for choosing\r\nour product.\r\nGoodbye.", 50 },			/* LV_PLUGIN_STRING_ID_STRID_LOGOL_BYE */ 
	{ "The Shutdown Count 10", 21 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_10S */ 
	{ "The Shutdown Count 9", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_9S */ 
	{ "The Shutdown Count 8", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_8S */ 
	{ "The Shutdown Count 7", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_7S */ 
	{ "The Shutdown Count 6", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_6S */ 
	{ "The Shutdown Count 5", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_5S */ 
	{ "The Shutdown Count 4", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_4S */ 
	{ "The Shutdown Count 3", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_3S */ 
	{ "The Shutdown Count 2", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_2S */ 
	{ "The Shutdown Count 1", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_1S */ 
	{ "The Shutdown Count 0", 20 },			/* LV_PLUGIN_STRING_ID_STRID_POWER_OFF_0S */ 
	{ "Parking guard", 13 },			/* LV_PLUGIN_STRING_ID_STRID_PARKINGGUARD */ 
	{ "Часовые пояса", 25 },			/* LV_PLUGIN_STRING_ID_STRID_TIME_ZONE */ 
	{ "GMT -12", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N12 */ 
	{ "GMT -11", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N11 */ 
	{ "GMT -10", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N10 */ 
	{ "GMT -9", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N9 */ 
	{ "GMT -8", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N8 */ 
	{ "GMT -7", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N7 */ 
	{ "GMT -6", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N6 */ 
	{ "GMT -5", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N5 */ 
	{ "GMT -4", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N4 */ 
	{ "GMT -3", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N3 */ 
	{ "GMT -2", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N2 */ 
	{ "GMT -1", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N1 */ 
	{ "GMT 0", 5 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N0 */ 
	{ "GMT +1", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P1 */ 
	{ "GMT +2", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P2 */ 
	{ "GMT +3", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P3 */ 
	{ "GMT +4", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P4 */ 
	{ "GMT +5", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P5 */ 
	{ "GMT +6", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P6 */ 
	{ "GMT +7", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P7 */ 
	{ "GMT +8", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P8 */ 
	{ "GMT +9", 6 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P9 */ 
	{ "GMT +10", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P10 */ 
	{ "GMT +11", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P11 */ 
	{ "GMT +12", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P12 */ 
	{ "GMT +13", 7 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P13 */ 
	{ "GMT -3:30", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N330 */ 
	{ "GMT +3:30", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P330 */ 
	{ "GMT +4:30", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P430 */ 
	{ "GMT +5:30", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P530 */ 
	{ "GMT +9:30", 9 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P930 */ 
	{ "GMT +10:30", 10 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P1030 */ 
	{ "Безопасность вождения", 41 },			/* LV_PLUGIN_STRING_ID_STRID_CAR_SAFE */ 
	{ "Распозн. дорожных знаков", 45 },			/* LV_PLUGIN_STRING_ID_STRID_TSR */ 
	{ "ЗАПИСЬ:", 13 },			/* LV_PLUGIN_STRING_ID_STRID_REC */ 
	{ "Стоп и пуск", 20 },			/* LV_PLUGIN_STRING_ID_STRID_SNG */ 
	{ "Усталость за рулем", 34 },			/* LV_PLUGIN_STRING_ID_STRID_FATIGUE_DRIVING */ 
	{ "Напоминание о фарах", 36 },			/* LV_PLUGIN_STRING_ID_STRID_REMIND_LIGHT */ 
	{ "30 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_FATIGUE_30MIN */ 
	{ "1 час", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FATIGUE_1HOUR */ 
	{ "2 часа", 10 },			/* LV_PLUGIN_STRING_ID_STRID_FATIGUE_2HOUR */ 
	{ "4 часа", 10 },			/* LV_PLUGIN_STRING_ID_STRID_FATIGUE_4HOUR */ 
	{ "Единица скорости", 31 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED_UNIT */ 
	{ "MPH", 3 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED_MPH */ 
	{ "KM/H", 4 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED_KPH */ 
	{ "C0", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C0 */ 
	{ "C1", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C1 */ 
	{ "C2", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C2 */ 
	{ "C3", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C3 */ 
	{ "C4", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C4 */ 
	{ "C5", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C5 */ 
	{ "C6", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C6 */ 
	{ "C7", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C7 */ 
	{ "C8", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C8 */ 
	{ "C9", 2 },			/* LV_PLUGIN_STRING_ID_STRID_C9 */ 
	{ "D0", 2 },			/* LV_PLUGIN_STRING_ID_STRID_D0 */ 
	{ "Detect Led", 10 },			/* LV_PLUGIN_STRING_ID_STRID_LED_DET */ 
	{ "1080P30,1080P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_1080P30_1080P30 */ 
	{ "One Camera", 10 },			/* LV_PLUGIN_STRING_ID_STRID_ONE_CAMERA */ 
	{ "Two Camera", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TWO_CAMERA */ 
	{ "Display Mode", 12 },			/* LV_PLUGIN_STRING_ID_STRID_DISPLAY_MODE */ 
	{ "Фронтальная камера", 35 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_CAMERA */ 
	{ "Фронтальная камера", 35 },			/* LV_PLUGIN_STRING_ID_STRID_MIDDLE_CAMERA */ 
	{ "Дополнительная камера", 41 },			/* LV_PLUGIN_STRING_ID_STRID_BACK_CAMERA */ 
	{ "Картинка в картинке", 36 },			/* LV_PLUGIN_STRING_ID_STRID_PICTURE_IN_PICTURE */ 
	{ "", 0 },			/* LV_PLUGIN_STRING_ID_STRID_FILL_ASCII */ 
	{ "20%", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PERCENT20 */ 
	{ "40%", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PERCENT40 */ 
	{ "60%", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PERCENT60 */ 
	{ "80%", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PERCENT80 */ 
	{ "100%", 4 },			/* LV_PLUGIN_STRING_ID_STRID_PERCENT100 */ 
	{ "Выкл.", 9 },			/* LV_PLUGIN_STRING_ID_STRID_MUTE */ 
	{ "Camera1", 7 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA1 */ 
	{ "Camera2", 7 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA2 */ 
	{ "Normal", 6 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA_NORMAL */ 
	{ "Inverted", 8 },			/* LV_PLUGIN_STRING_ID_STRID_CAMERA_INVERTED */ 
	{ "WiFi", 4 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI */ 
	{ "WiFi_OFF", 8 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_OFF */ 
	{ "Refresh", 7 },			/* LV_PLUGIN_STRING_ID_STRID_REFRESH */ 
	{ "AP mode", 7 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_AP_MODE */ 
	{ "Client mode", 11 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_CLIENT_MODE */ 
	{ "SSID", 4 },			/* LV_PLUGIN_STRING_ID_STRID_SSID */ 
	{ "Автозапуск Wi-Fi", 26 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_AUTO */ 
	{ "задержка загрузки", 33 },			/* LV_PLUGIN_STRING_ID_STRID_BOOT_DELAY */ 
	{ "15 сек.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_15SEC */ 
	{ "30 сек.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_30SEC */ 
	{ "Штамп GPS", 14 },			/* LV_PLUGIN_STRING_ID_STRID_GPS_STAMP */ 
	{ "Координаты", 20 },			/* LV_PLUGIN_STRING_ID_STRID_COORDINATES */ 
	{ "Cкорость", 15 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED */ 
	{ "Координаты+Cкорость", 36 },			/* LV_PLUGIN_STRING_ID_STRID_COORDINATES_SPEED */ 
	{ "GPS Status", 10 },			/* LV_PLUGIN_STRING_ID_STRID_GPS_STATUS */ 
	{ "2160P24  2880x2160", 18 },			/* LV_PLUGIN_STRING_ID_STRID_2160P24 */ 
	{ "1440P30  2560x1440", 18 },			/* LV_PLUGIN_STRING_ID_STRID_1440P30 */ 
	{ "1296P30  2304x1296", 18 },			/* LV_PLUGIN_STRING_ID_STRID_1296P30 */ 
	{ "1080P60  1920x1080", 18 },			/* LV_PLUGIN_STRING_ID_STRID_1080P60 */ 
	{ "1080P30  1920x1080", 18 },			/* LV_PLUGIN_STRING_ID_STRID_1080P30 */ 
	{ "720P120  1280x720", 17 },			/* LV_PLUGIN_STRING_ID_STRID_720P120 */ 
	{ "EV фронт", 13 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_EV */ 
	{ "EV фронт", 13 },			/* LV_PLUGIN_STRING_ID_STRID_MIDDLE_EV */ 
	{ "EV задний", 15 },			/* LV_PLUGIN_STRING_ID_STRID_REAR_EV */ 
	{ "Video Format", 12 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT */ 
	{ "MP4", 3 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_MP4 */ 
	{ "Super MP4", 9 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_SUPER_MP4 */ 
	{ "TS", 2 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FORMAT_TS */ 
	{ "Middle Camera Mirror", 20 },			/* LV_PLUGIN_STRING_ID_STRID_MIDDLE_CAMERA_MIRROR */ 
	{ "Rear Camera Mirror", 18 },			/* LV_PLUGIN_STRING_ID_STRID_REAR_CAMERA_MIRROR */ 
	{ "Tire Setup", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_SET */ 
	{ "Parameter Setting", 17 },			/* LV_PLUGIN_STRING_ID_STRID_PARM_SETTING */ 
	{ "Tire Status", 11 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_STATUS */ 
	{ "Press Unit", 10 },			/* LV_PLUGIN_STRING_ID_STRID_PRESSURE_UNIT */ 
	{ "Temp Unit", 9 },			/* LV_PLUGIN_STRING_ID_STRID_TEMP_UNIT */ 
	{ "Front/ Rear Wheel", 17 },			/* LV_PLUGIN_STRING_ID_STRID_SERIAL_PORT */ 
	{ "High Press", 10 },			/* LV_PLUGIN_STRING_ID_STRID_HIGH_PRESSURE */ 
	{ "Low Press", 9 },			/* LV_PLUGIN_STRING_ID_STRID_LOW_PRESSURE */ 
	{ "High Temp", 9 },			/* LV_PLUGIN_STRING_ID_STRID_HIGH_TEMP */ 
	{ "Inflating Programming", 21 },			/* LV_PLUGIN_STRING_ID_STRID_INFLATING_PROGRAMMING */ 
	{ "Tire Swap", 9 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_SWAP */ 
	{ "psi", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_PSI */ 
	{ "bar", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_BAR */ 
	{ "°C", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_C */ 
	{ "°F", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_F */ 
	{ "Front Wheel", 11 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_FW */ 
	{ "Rear Wheel", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_RW */ 
	{ "Please check TPMS!", 18 },			/* LV_PLUGIN_STRING_ID_STRID_TPMS_SIGNAL_UNNORMAL */ 
	{ "Key disable while connecting", 28 },			/* LV_PLUGIN_STRING_ID_STRID_DISABLECONNECTING */ 
	{ "Tire pairing,Please wait", 24 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING */ 
	{ "Tire pairing success", 20 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING_OK */ 
	{ "Tire pairing fail", 17 },			/* LV_PLUGIN_STRING_ID_STRID_TIRE_PAIRING_FAIL */ 
	{ "TPMS", 4 },			/* LV_PLUGIN_STRING_ID_STRID_TPMS */ 
	{ "Ambiance Light", 14 },			/* LV_PLUGIN_STRING_ID_STRID_AMBIANCE_LIGHT */ 
	{ "Breathing Light", 15 },			/* LV_PLUGIN_STRING_ID_STRID_BREATHING_LIGHT */ 
	{ "Permanent Light", 15 },			/* LV_PLUGIN_STRING_ID_STRID_PERMANENT_LIGHT */ 
	{ "Atmosphere Light", 16 },			/* LV_PLUGIN_STRING_ID_STRID_HORSE_RACE_LIGHT */ 
	{ "Host Light", 10 },			/* LV_PLUGIN_STRING_ID_STRID_HOST_LIGHT */ 
	{ "Trunk Light", 11 },			/* LV_PLUGIN_STRING_ID_STRID_TRUNK_LIGHT */ 
	{ "Video Coding", 12 },			/* LV_PLUGIN_STRING_ID_STRID_CODEC */ 
	{ "WDR", 3 },			/* LV_PLUGIN_STRING_ID_STRID_WDR */ 
	{ "Manual wifi is required when HDR is on.", 39 },			/* LV_PLUGIN_STRING_ID_STRID_HDR_WIFI_ON_WRN */ 
	{ "GPS Module", 10 },			/* LV_PLUGIN_STRING_ID_STRID_GPS_MODULE */ 
	{ "MGC-3", 5 },			/* LV_PLUGIN_STRING_ID_STRID_MGC_3 */ 
	{ "MGC-2", 5 },			/* LV_PLUGIN_STRING_ID_STRID_MGC_2 */ 
	{ "RO Video File", 13 },			/* LV_PLUGIN_STRING_ID_STRID_VIDEO_FLIE_RO */ 
	{ "Voice Notification", 18 },			/* LV_PLUGIN_STRING_ID_STRID_SPEEDLIMIT_VOICE */ 
	{ "Alarm", 5 },			/* LV_PLUGIN_STRING_ID_STRID_SPEEDLIMIT_BEEP */ 
	{ "HDR ON", 6 },			/* LV_PLUGIN_STRING_ID_STRID_HDR_ON */ 
	{ "HDR OFF", 7 },			/* LV_PLUGIN_STRING_ID_STRID_HDR_OFF */ 
	{ "HDR Timer", 9 },			/* LV_PLUGIN_STRING_ID_STRID_HDR_TIMER */ 
	{ "Disable GPS in Parking Mode", 27 },			/* LV_PLUGIN_STRING_ID_STRID_DISABLE_GPS_IN_PARKINGMODE */ 
	{ "Распознавание речи", 35 },			/* LV_PLUGIN_STRING_ID_STRID_ASR */ 
	{ "Standard", 8 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_STANDARD */ 
	{ "Голосовое содержание.", 40 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_CONTENT */ 
	{ "Сделать фото", 23 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TAKEPHOTO */ 
	{ "записать на видеомагнитофон", 52 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_VIDEOSTART */ 
	{ "Открыть звукозапись", 37 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNONAUDIO */ 
	{ "Закрыть звукозапись", 37 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFAUDIO */ 
	{ "Включить экран", 27 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNONSCREEN */ 
	{ "Выключить экран", 29 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFSCREEN */ 
	{ "Открыть модем", 25 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNONHOTSPOT */ 
	{ "Закрыть модем", 25 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFHOTSPOT */ 
	{ "Блокировка видео", 31 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_LOCKVIDEO */ 
	{ "Включить Wifi", 21 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNONWIFI */ 
	{ "Выключить Wifi", 23 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_TURNOFFWIFI */ 
	{ "Video  Stop", 11 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_VIDEOSTOP */ 
	{ "Открыть фронтальную камеру", 50 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_FRONT_CAMERA */ 
	{ "Открыть заднюю камеру", 40 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_REAR_CAMERA */ 
	{ "Проверить все", 25 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_SHOW_BOTH_CAMERAS */ 
	{ "Открыть встроенную камеру", 48 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_INSIDE_VIDEO_ON */ 
	{ "Открыть встроенную камеру", 48 },			/* LV_PLUGIN_STRING_ID_STRID_ASR_BACK_TO_HOMEPAGE */ 
	{ "90 сек.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_90SEC */ 
	{ "12 часа", 11 },			/* LV_PLUGIN_STRING_ID_STRID_12HOUR */ 
	{ "24 часа", 11 },			/* LV_PLUGIN_STRING_ID_STRID_24HOUR */ 
	{ "48 часа", 11 },			/* LV_PLUGIN_STRING_ID_STRID_48HOUR */ 
	{ "72 часа", 11 },			/* LV_PLUGIN_STRING_ID_STRID_72HOUR */ 
	{ "Съёмка с 1 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_1FPS */ 
	{ "Съёмка с 2 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_2FPS */ 
	{ "Съёмка с 3 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_3FPS */ 
	{ "Съёмка с 4 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_4FPS */ 
	{ "Съёмка с 5 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_5FPS */ 
	{ "Съёмка с 6 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_6FPS */ 
	{ "Съёмка с 7 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_7FPS */ 
	{ "Съёмка с 8 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_8FPS */ 
	{ "Съёмка с 9 к/с", 23 },			/* LV_PLUGIN_STRING_ID_STRID_TL_9FPS */ 
	{ "Съёмка с 10 к/с", 24 },			/* LV_PLUGIN_STRING_ID_STRID_TL_10FPS */ 
	{ "Парковочный G-сенсор", 37 },			/* LV_PLUGIN_STRING_ID_STRID_PARKING_GSENSOR */ 
	{ "Парковочный датчик движ-я", 47 },			/* LV_PLUGIN_STRING_ID_STRID_PARKING_MOTION_DET */ 
	{ "H.264", 5 },			/* LV_PLUGIN_STRING_ID_STRID_H264 */ 
	{ "H.265", 5 },			/* LV_PLUGIN_STRING_ID_STRID_H265 */ 
	{ "Таймер режима парковки", 42 },			/* LV_PLUGIN_STRING_ID_STRID_SHUTDOWN_TIMER */ 
	{ "задержка въезда на парковку", 51 },			/* LV_PLUGIN_STRING_ID_STRID_ENTERPARKING_TIMER */ 
	{ "Режим парковки", 27 },			/* LV_PLUGIN_STRING_ID_STRID_PARKING_MODE */ 
	{ "Автоматическое обнаружение", 51 },			/* LV_PLUGIN_STRING_ID_STRID_AUTO_EVENT_DETECTION */ 
	{ "Запись с низким битрейтом", 47 },			/* LV_PLUGIN_STRING_ID_STRID_LOW_BITRATE */ 
	{ "To turn this on, \r\nset the frame rate\r\n to 30 or below.", 59 },			/* LV_PLUGIN_STRING_ID_STRID_CAN_NOT_BE_SET */ 
	{ "EIS", 3 },			/* LV_PLUGIN_STRING_ID_STRID_EIS */ 
	{ "in the process", 14 },			/* LV_PLUGIN_STRING_ID_STRID_IN_PREPARATION */ 
	{ "2.4GHz", 6 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_24G */ 
	{ "5GHz", 4 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_5G */ 
	{ "5.2GHz", 6 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_52G */ 
	{ "5.8GHz", 6 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_58G */ 
	{ "Зеркальное изображение", 43 },			/* LV_PLUGIN_STRING_ID_STRID_IMAGE_MIRROR */ 
	{ "Display Mirror", 14 },			/* LV_PLUGIN_STRING_ID_STRID_DISPLAY_MIRROR */ 
	{ "Video Setting", 13 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIE_SETTING */ 
	{ "Camera Setting", 14 },			/* LV_PLUGIN_STRING_ID_STRID_SYSTEM_SETTING */ 
	{ "Detect Setting", 14 },			/* LV_PLUGIN_STRING_ID_STRID_DETECT_SETTING */ 
	{ "Boot Sound", 10 },			/* LV_PLUGIN_STRING_ID_STRID_START_SOUND */ 
	{ "Scenario Mode", 13 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE_MODE */ 
	{ "General", 7 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_GENERAL */ 
	{ "Metropolitan", 12 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_CITY */ 
	{ "Motocross", 9 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_MOTOCROSS */ 
	{ "Professional", 12 },			/* LV_PLUGIN_STRING_ID_STRID_SCENE_MODE_PRO */ 
	{ "Mon", 3 },			/* LV_PLUGIN_STRING_ID_STRID_MON */ 
	{ "Tue", 3 },			/* LV_PLUGIN_STRING_ID_STRID_TUE */ 
	{ "Wed", 3 },			/* LV_PLUGIN_STRING_ID_STRID_WED */ 
	{ "Thu", 3 },			/* LV_PLUGIN_STRING_ID_STRID_THU */ 
	{ "Fri", 3 },			/* LV_PLUGIN_STRING_ID_STRID_FRI */ 
	{ "Sat", 3 },			/* LV_PLUGIN_STRING_ID_STRID_SAT */ 
	{ "Sun", 3 },			/* LV_PLUGIN_STRING_ID_STRID_SUN */ 
	{ "Speed Alert", 11 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED_ALERT */ 
	{ "Time Display", 12 },			/* LV_PLUGIN_STRING_ID_STRID_TIME_DISPLAY */ 
	{ "Turn off WiFi before proceeding", 31 },			/* LV_PLUGIN_STRING_ID_STRID_WARN_OFF_WIFI */ 
	{ "Rear camera error", 17 },			/* LV_PLUGIN_STRING_ID_STRID_REAR_ERROR */ 
	{ "Light Control", 13 },			/* LV_PLUGIN_STRING_ID_STRID_LIGHT_CTRL */ 
	{ "Light  Brightness", 17 },			/* LV_PLUGIN_STRING_ID_STRID_BRGITHNESS_LEVEL */ 
	{ "Buzzer Volume", 13 },			/* LV_PLUGIN_STRING_ID_STRID_BUZZER_VOLUME */ 
	{ "Reverse Alarm Sound", 19 },			/* LV_PLUGIN_STRING_ID_STRID_REVERSE_ALARM_SOUND */ 
	{ "Speeding Alert Sound", 20 },			/* LV_PLUGIN_STRING_ID_STRID_SPEED_ALERT_SOUND */ 
	{ "Main Unit Position", 18 },			/* LV_PLUGIN_STRING_ID_STRID_MACHINE_POS */ 
	{ "Flat-Horizontal in Trunk", 24 },			/* LV_PLUGIN_STRING_ID_STRID_BOTTOM_HORIZONTAL */ 
	{ "Flat-Vertical in Trunk ", 23 },			/* LV_PLUGIN_STRING_ID_STRID_BOTTOM_VERTICAL */ 
	{ "Trunk Side-Horizontal", 21 },			/* LV_PLUGIN_STRING_ID_STRID_SIDE_HORIZONTAL */ 
	{ "Trunk Side-Vertical", 19 },			/* LV_PLUGIN_STRING_ID_STRID_SIDE_VERTICAL */ 
	{ "Trunk Back-Horizontal", 21 },			/* LV_PLUGIN_STRING_ID_STRID_BACK_HORIZONTAL */ 
	{ "Trunk Back-Vertical", 19 },			/* LV_PLUGIN_STRING_ID_STRID_BACK_VERTICAL */ 
	{ "Gsensor calibration", 19 },			/* LV_PLUGIN_STRING_ID_STRID_GSENSOR_CAL */ 
	{ "Tilt Angle Alert", 16 },			/* LV_PLUGIN_STRING_ID_STRID_ACCIDENT_ALARM */ 
	{ "Tilt Alert", 10 },			/* LV_PLUGIN_STRING_ID_STRID_REVERSE_ALARM */ 
	{ "Please calibrate", 16 },			/* LV_PLUGIN_STRING_ID_STRID_GSENSOR_CAL_WARN */ 
	{ "Use the \nsurveillance cable", 28 },			/* LV_PLUGIN_STRING_ID_STRID_REQUIRE_ACC_HW_CABLE */ 
	{ "Hold 3s to Toggle Alarm", 23 },			/* LV_PLUGIN_STRING_ID_STRID_HOLD3S_TOGGLE_ALARM */ 
	{ "Headway Monitoring Warning", 26 },			/* LV_PLUGIN_STRING_ID_STRID_HMW */ 
	{ "Pedestrian Collison Warning", 27 },			/* LV_PLUGIN_STRING_ID_STRID_PCW */ 
	{ "Rear Collision Warning", 22 },			/* LV_PLUGIN_STRING_ID_STRID_RCW */ 
	{ "Blind Spot Detection", 20 },			/* LV_PLUGIN_STRING_ID_STRID_BSD */ 
	{ "К-ль разметки LDWS", 29 },			/* LV_PLUGIN_STRING_ID_STRID_LDWS */ 
	{ "К-ль дистанции FCWS", 31 },			/* LV_PLUGIN_STRING_ID_STRID_FCW */ 
	{ "Virtual Bumper", 14 },			/* LV_PLUGIN_STRING_ID_STRID_VIRTUAL_BUMPER */ 
	{ "Lane Change Assist", 18 },			/* LV_PLUGIN_STRING_ID_STRID_LCWS */ 
	{ "ADAS Calibration", 16 },			/* LV_PLUGIN_STRING_ID_STRID_ADAS_CALIBRATION */ 
	{ "Cordon", 6 },			/* LV_PLUGIN_STRING_ID_STRID_ADAS_CORDON */ 
	{ "Align with the horizon and align the \nvertical line with the middle of the front of the car", 92 },			/* LV_PLUGIN_STRING_ID_STRID_ADAS_CORDON_LINE */ 
	{ "App is Connecting…", 20 },			/* LV_PLUGIN_STRING_ID_STRID_APP_CONNECTTING */ 
	{ "ADAS", 4 },			/* LV_PLUGIN_STRING_ID_STRID_ADAS */ 
	{ "1080P60,720x480P30", 18 },			/* LV_PLUGIN_STRING_ID_STRID_1080P60_D1P30 */ 
	{ "800", 3 },			/* LV_PLUGIN_STRING_ID_STRID_ISO800 */ 
	{ "1600", 4 },			/* LV_PLUGIN_STRING_ID_STRID_ISO1600 */ 
	{ "3200", 4 },			/* LV_PLUGIN_STRING_ID_STRID_ISO3200 */ 
	{ "60 мин.", 10 },			/* LV_PLUGIN_STRING_ID_STRID_60MIN */ 
	{ "Screen Save", 11 },			/* LV_PLUGIN_STRING_ID_STRID_SCREEN_SAVE */ 
	{ "Dual Record", 11 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_REC */ 
	{ "Интервальная съемка", 37 },			/* LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_REC */ 
	{ "Интервальная съемка", 37 },			/* LV_PLUGIN_STRING_ID_STRID_TIMELAPSE_CAP */ 
	{ "Make Movie by Photo", 19 },			/* LV_PLUGIN_STRING_ID_STRID_MAKE_MOVIE */ 
	{ "Обработка…", 21 },			/* LV_PLUGIN_STRING_ID_STRID_PROCESSING */ 
	{ "Time Lapse", 10 },			/* LV_PLUGIN_STRING_ID_STRID_TIME_LPASE */ 
	{ "100 ms", 6 },			/* LV_PLUGIN_STRING_ID_STRID_100MS */ 
	{ "200 ms", 6 },			/* LV_PLUGIN_STRING_ID_STRID_200MS */ 
	{ "500 ms", 6 },			/* LV_PLUGIN_STRING_ID_STRID_500MS */ 
	{ "_", 1 },			/* LV_PLUGIN_STRING_ID_STRID_UNDERSCORE */ 
	{ "Switch Mode", 11 },			/* LV_PLUGIN_STRING_ID_STRID_MODE_SWITCH */ 
	{ "2880x2160P24", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2880X2160P24 */ 
	{ "2560x1440P30", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2560X1440P30 */ 
	{ "2304x1296P30", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2304X1296P30 */ 
	{ "1080P96", 7 },			/* LV_PLUGIN_STRING_ID_STRID_1080P96 */ 
	{ "1080P_DUAL", 10 },			/* LV_PLUGIN_STRING_ID_STRID_1080P_DUAL */ 
	{ "720P120", 7 },			/* LV_PLUGIN_STRING_ID_STRID_720P120WXH */ 
	{ "RSC", 3 },			/* LV_PLUGIN_STRING_ID_STRID_RSC */ 
	{ "G Sensor", 8 },			/* LV_PLUGIN_STRING_ID_STRID_G_SENSOR */ 
	{ "1 Sec", 5 },			/* LV_PLUGIN_STRING_ID_STRID_1SEC */ 
	{ "1 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_1HOUR */ 
	{ "2 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_2HOUR */ 
	{ "3 Hour", 6 },			/* LV_PLUGIN_STRING_ID_STRID_3HOUR */ 
	{ "1 Day", 5 },			/* LV_PLUGIN_STRING_ID_STRID_1DAY */ 
	{ "IR Cut", 6 },			/* LV_PLUGIN_STRING_ID_STRID_IRCUT */ 
	{ "Dual Cam Display", 16 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_CAM */ 
	{ "Front", 5 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT */ 
	{ "Behind", 6 },			/* LV_PLUGIN_STRING_ID_STRID_BEHIND */ 
	{ "Both", 4 },			/* LV_PLUGIN_STRING_ID_STRID_BOTH */ 
	{ "PTZ", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PTZ */ 
	{ "Auto Urgent Protect", 19 },			/* LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_AUTO */ 
	{ "Manual Urgent Protect", 21 },			/* LV_PLUGIN_STRING_ID_STRID_URGENT_PROTECT_MANUAL */ 
	{ "PIM", 3 },			/* LV_PLUGIN_STRING_ID_STRID_PIM */ 
	{ "DDD", 3 },			/* LV_PLUGIN_STRING_ID_STRID_DDD */ 
	{ "File Recovery", 13 },			/* LV_PLUGIN_STRING_ID_STRID_REC_RECOVERY */ 
	{ "Self Timer", 10 },			/* LV_PLUGIN_STRING_ID_STRID_SELFTIMER */ 
	{ "Portrial", 8 },			/* LV_PLUGIN_STRING_ID_STRID_PORTRIAL */ 
	{ "Landscpe", 8 },			/* LV_PLUGIN_STRING_ID_STRID_LANDSCPE */ 
	{ "0", 1 },			/* LV_PLUGIN_STRING_ID_STRID_0 */ 
	{ "1", 1 },			/* LV_PLUGIN_STRING_ID_STRID_1 */ 
	{ "2", 1 },			/* LV_PLUGIN_STRING_ID_STRID_2 */ 
	{ "3", 1 },			/* LV_PLUGIN_STRING_ID_STRID_3 */ 
	{ "4", 1 },			/* LV_PLUGIN_STRING_ID_STRID_4 */ 
	{ "5", 1 },			/* LV_PLUGIN_STRING_ID_STRID_5 */ 
	{ "6", 1 },			/* LV_PLUGIN_STRING_ID_STRID_6 */ 
	{ "7", 1 },			/* LV_PLUGIN_STRING_ID_STRID_7 */ 
	{ "8", 1 },			/* LV_PLUGIN_STRING_ID_STRID_8 */ 
	{ "9", 1 },			/* LV_PLUGIN_STRING_ID_STRID_9 */ 
	{ "10", 2 },			/* LV_PLUGIN_STRING_ID_STRID_10 */ 
	{ "Cloud", 5 },			/* LV_PLUGIN_STRING_ID_STRID_CLOUD */ 
	{ "Firmware Update", 15 },			/* LV_PLUGIN_STRING_ID_STRID_FW_UPDATE */ 
	{ "UVC", 3 },			/* LV_PLUGIN_STRING_ID_STRID_UVC */ 
	{ "Resume", 6 },			/* LV_PLUGIN_STRING_ID_STRID_RESUME */ 
	{ "MCTF", 4 },			/* LV_PLUGIN_STRING_ID_STRID_MCTF */ 
	{ "Edge", 4 },			/* LV_PLUGIN_STRING_ID_STRID_EDGE */ 
	{ "NR", 2 },			/* LV_PLUGIN_STRING_ID_STRID_NR */ 
	{ "WiFi/ETH", 8 },			/* LV_PLUGIN_STRING_ID_STRID_WIFI_ETH */ 
	{ "6400", 4 },			/* LV_PLUGIN_STRING_ID_STRID_ISO6400 */ 
	{ "12800", 5 },			/* LV_PLUGIN_STRING_ID_STRID_ISO12800 */ 
	{ "UHD P50", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P50 */ 
	{ "UHD P30", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_3840X2160P30 */ 
	{ "UHD P24", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2880X2160P24 */ 
	{ "2.7K P60", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2704X2032P60 */ 
	{ "QHD P80", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P80 */ 
	{ "QHD P60", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P60 */ 
	{ "QHD P30", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1440P30 */ 
	{ "3MHD P30", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2304X1296P30 */ 
	{ "FHD P120", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P120 */ 
	{ "FHD P96", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P96 */ 
	{ "FHD P60", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P60 */ 
	{ "FHD P30", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1920X1080P30 */ 
	{ "HD P240", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P240 */ 
	{ "HD P120", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P120 */ 
	{ "HD P60", 6 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P60 */ 
	{ "HD P30", 6 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_1280X720P30 */ 
	{ "WVGA P30", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_848X480P30 */ 
	{ "VGA P240", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P240 */ 
	{ "VGA P30", 7 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_640X480P30 */ 
	{ "QVGA P30", 8 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_320X240P30 */ 
	{ "QHD P30+HD P30", 14 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1280X720P30 */ 
	{ "QHD P30+FHD P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_2560X1440P30_1920X1080P30 */ 
	{ "3MHD P30+HD P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_2304X1296P30_1280X720P30 */ 
	{ "FHD P30+FHD P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_1080P30_1080P30 */ 
	{ "FHD P30+HD P30", 14 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_1280X720P30 */ 
	{ "FHD P30+WVGA P30", 16 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_1920X1080P30_848X480P30 */ 
	{ "FHD P30+FHD P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1920X1080P30 */ 
	{ "FHD P30+HD P30", 14 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_1280X720P30 */ 
	{ "QHD P30+WVGA P30", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_2560X1440P30_848X480P30 */ 
	{ "3MHD P30+WVGA P30", 17 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_2304X1296P30_848X480P30 */ 
	{ "FHD P60+WVGA P30", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_848X480P30 */ 
	{ "FHD P60+VGA P30", 15 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P60_640X360P30 */ 
	{ "FHD P30+WVGA P30", 16 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_1920X1080P30_848X480P30 */ 
	{ "2048x2048 P30 + 480x480 P30", 27 },			/* LV_PLUGIN_STRING_ID_STRID_CLONE_2048X2048P30_480X480P30 */ 
	{ "Both2", 5 },			/* LV_PLUGIN_STRING_ID_STRID_BOTH2 */ 
	{ "SideBySide", 10 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_SIDE */ 
	{ "Burst 30", 8 },			/* LV_PLUGIN_STRING_ID_STRID_CAP_BURST_30 */ 
	{ "5M 2992x1696", 12 },			/* LV_PLUGIN_STRING_ID_STRID_5MWXH_USR */ 
	{ "MJPG", 4 },			/* LV_PLUGIN_STRING_ID_STRID_MJPG */ 
	{ "2880X2160P50", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2880X2160P50 */ 
	{ "3840X2160P30", 12 },			/* LV_PLUGIN_STRING_ID_STRID_3840X2160P30 */ 
	{ "18HOUR", 6 },			/* LV_PLUGIN_STRING_ID_STRID_18HOUR */ 
	{ "2560X1440P60", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2560X1440P60 */ 
	{ "2560X1440P80", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2560X1440P80 */ 
	{ "2704X2032P60", 12 },			/* LV_PLUGIN_STRING_ID_STRID_2704X2032P60 */ 
	{ "4HOUR", 5 },			/* LV_PLUGIN_STRING_ID_STRID_4HOUR */ 
	{ "6HOUR", 5 },			/* LV_PLUGIN_STRING_ID_STRID_6HOUR */ 
	{ "8HOUR", 5 },			/* LV_PLUGIN_STRING_ID_STRID_8HOUR */ 
	{ "COLOR_MONO", 10 },			/* LV_PLUGIN_STRING_ID_STRID_COLOR_MONO */ 
	{ "CUSTOMIZE", 9 },			/* LV_PLUGIN_STRING_ID_STRID_CUSTOMIZE */ 
	{ "DUAL_1080P60_1080P60", 20 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_1080P60_1080P60 */ 
	{ "DUAL_3840x2160P30_1920x1080P30", 30 },			/* LV_PLUGIN_STRING_ID_STRID_DUAL_3840X2160P30_1920X1080P30 */ 
	{ "FRONT_2304X1296P60", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2304X1296P60 */ 
	{ "FRONT_2560X1080P30", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1080P30 */ 
	{ "FRONT_2560X1080P60", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1080P60 */ 
	{ "FRONT_2560X1600P30", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2560X1600P30 */ 
	{ "FRONT_2592X1944P30", 18 },			/* LV_PLUGIN_STRING_ID_STRID_FRONT_2592X1944P30 */ 
	{ "GMT_N230", 8 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_N230 */ 
	{ "GMT_P630", 8 },			/* LV_PLUGIN_STRING_ID_STRID_GMT_P630 */ 
	{ "IR_CAMERA_COLOR", 15 },			/* LV_PLUGIN_STRING_ID_STRID_IR_CAMERA_COLOR */ 
	{ "IR_COLOR", 8 },			/* LV_PLUGIN_STRING_ID_STRID_IR_COLOR */ 
	{ "LANG_AZ", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_AZ */ 
	{ "LANG_CZ", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_CZ */ 
	{ "LANG_NL", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_NL */ 
	{ "LANG_NO", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_NO */ 
	{ "LANG_RO", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_RO */ 
	{ "LANG_SK", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_SK */ 
	{ "LANG_TR", 7 },			/* LV_PLUGIN_STRING_ID_STRID_LANG_TR */ 
	{ "LIVESTREAM", 10 },			/* LV_PLUGIN_STRING_ID_STRID_LIVESTREAM */ 
	{ "MODEL_STAMP", 11 },			/* LV_PLUGIN_STRING_ID_STRID_MODEL_STAMP */ 
	{ "MOVIE_BITRATE", 13 },			/* LV_PLUGIN_STRING_ID_STRID_MOVIE_BITRATE */ 
	{ "PERIPHERAL", 10 },			/* LV_PLUGIN_STRING_ID_STRID_PERIPHERAL */ 
	{ "PM_15FPS", 8 },			/* LV_PLUGIN_STRING_ID_STRID_PM_15FPS */ 
	{ "QUAD_1920x1080P30", 17 },			/* LV_PLUGIN_STRING_ID_STRID_QUAD_1920X1080P30 */ 
	{ "RSC_EFFECT", 10 },			/* LV_PLUGIN_STRING_ID_STRID_RSC_EFFECT */ 
	{ "SUPER_HIGH", 10 },			/* LV_PLUGIN_STRING_ID_STRID_SUPER_HIGH */ 
	{ "TPMS_PRSR_UNIT", 14 },			/* LV_PLUGIN_STRING_ID_STRID_TPMS_PRSR_UNIT */ 
	{ "TPMS_TEMP_UNIT", 14 },			/* LV_PLUGIN_STRING_ID_STRID_TPMS_TEMP_UNIT */ 
	{ "TRI_1920x1080P30", 16 },			/* LV_PLUGIN_STRING_ID_STRID_TRI_1920X1080P30 */ 
	{ "TRI_2560x1440P30_1920x1080P30_1920x1080P30", 42 },			/* LV_PLUGIN_STRING_ID_STRID_TRI_2560X1440P30_1920X1080P30_1920X1080P30 */ 
};



