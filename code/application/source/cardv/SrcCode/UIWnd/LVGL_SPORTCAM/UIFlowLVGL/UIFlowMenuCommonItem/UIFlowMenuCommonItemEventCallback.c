
#include "PrjInc.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include "UIApp/Network/UIAppNetwork.h"
#include <kwrap/debug.h>
#include "DxInput.h"

#define PAGE           4

#define MENU_KEY_PRESS_MASK        (FLGKEY_UP|FLGKEY_DOWN|FLGKEY_ENTER|FLGKEY_LEFT)
#define MENU_KEY_RELEASE_MASK      (FLGKEY_UP|FLGKEY_DOWN|FLGKEY_ENTER|FLGKEY_LEFT)
#define MENU_KEY_CONTINUE_MASK     (FLGKEY_UP|FLGKEY_DOWN|FLGKEY_ENTER|FLGKEY_LEFT)

static TM_MENU *g_pItemMenu = 0;
static lv_group_t* gp = NULL;
static lv_obj_t* menu_item = NULL;
static lv_obj_t* label_menu_item_title = NULL;
static lv_obj_t* label_menu_item_page_num = NULL;

static void set_indev_keypad_group(lv_obj_t* obj)
{
	if(gp == NULL){
		gp = lv_group_create();
		lv_group_add_obj(gp, obj);
	}

	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_group(indev, gp);
}

static void MenuCommonItem_SetCurrentMenu(TM_MENU *pMenu)
{
	g_pItemMenu = pMenu;
}
static TM_MENU *MenuCommonItem_GetCurrentMenu(void)
{
	return g_pItemMenu;
}
static UINT8 g_PageNumBuf[8];

void MenuCommonItem_CalcPageInfo(void)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
    UINT32  i, uiItem, uiCurrItem, uiTotalItem, uiTotalItemOri;
    UINT32  uiItemPerPage, uiCurrPage, uiTotalPage;

	pMenu = MenuCommonItem_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];

    uiItem = pPage->SelItem;          	// current item number in menu (include disabled items)
    uiItemPerPage = PAGE;				// items per page
    uiTotalItemOri = pPage->Count;  	// total item number

    // check total item number and current item number (skip disabled items)
    uiCurrItem = 0;
    uiTotalItem = 0;
    for (i = 0; i < uiTotalItemOri; i++)
    {
    	//check item if disable
    	pItem = &pPage->pItems[i];
        //if (UxMenu_GetItemData(pCtrl, i, MNUITM_STATUS) == STATUS_ENABLE)
		if(((pItem->Status) & TM_ITEM_STATUS_MASK)==TM_ITEM_ENABLE)
        {
            uiTotalItem++;
            if (i < uiItem)
                uiCurrItem++;
        }
    }

    uiCurrPage = (uiCurrItem / uiItemPerPage) + 1;
    uiTotalPage = ((uiTotalItem % uiItemPerPage) == 0) ? (uiTotalItem / uiItemPerPage) : (uiTotalItem / uiItemPerPage + 1);

    sprintf((char *)g_PageNumBuf, "%02d/%02d", uiCurrPage, uiTotalPage);
	lv_label_set_text_fmt(label_menu_item_page_num, "%s",g_PageNumBuf);	
	lv_obj_set_hidden(label_menu_item_page_num,FALSE);
}
static void MenuCommonItem_UpdateContent(TM_MENU *pMenu);

#if 1
static void MenuItem_OnNext(lv_obj_t* obj)
{
    TM_MENU    *pMenu;
    TM_PAGE    *pPage;
    UINT8       currentPagePos;

    pMenu = MenuCommonItem_GetCurrentMenu();
    pPage = &pMenu->pPages[pMenu->SelPage];
    
    // »ñÈ¡µ±Ç°ÔÚÒ³ÃæÖÐµÄÎ»ÖÃ£¨0-3£©
    currentPagePos = pPage->SelItem % PAGE;
    
    pPage->SelItem++;
    //check item if disable
    TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);
    
    if (pPage->SelItem == pPage->Count) {
        // Ñ­»·»ØÈÆµ½µÚÒ»¸ö
        pPage->SelItem = 0;
        
        // ¹Ø¼ü£ºÔÚ¸üÐÂÄÚÈÝÇ°£¬ÏÈ°Ñ¸ßÁÁÒÆµ½µÚÒ»¸öÎ»ÖÃ
        lv_plugin_menu_select_item(menu_item, 0);
        
        MenuCommonItem_UpdateContent(pMenu);
        
        // ÔÙ´ÎÈ·ÈÏ¸ßÁÁÔÚµÚÒ»¸öÎ»ÖÃ
        lv_plugin_menu_select_item(menu_item, 0);
        MenuCommonItem_CalcPageInfo();
    } else {
        // ¼ì²éÊÇ·ñ´ÓÒ³Ãæ×îºóÒ»¸öÎ»ÖÃÒÆ³ö
        if (currentPagePos == PAGE - 1) {
            // ·­Ò³µÄÇé¿ö
            // ÏÈÇå³ýµ±Ç°Ò³ÃæµÄ¸ßÁÁ
            lv_plugin_menu_select_item(menu_item, 0);  // ÏÈÒÆµ½µÚÒ»¸ö
            MenuCommonItem_UpdateContent(pMenu);
            // ¸ßÁÁÓ¦¸ÃÔÚÐÂÒ³ÃæµÄµÚÒ»¸öÎ»ÖÃ
            lv_plugin_menu_select_item(menu_item, 0);
        } else {
            // Í¬Ò»Ò³ÄÚÒÆ¶¯
            MenuCommonItem_UpdateContent(pMenu);
            lv_plugin_menu_select_next_item(menu_item);
        }
        MenuCommonItem_CalcPageInfo();
    }
    
    DBG_IND("555pPage->SelItem=%d,pPage->Count=%d, currentPagePos=%d\r\n",pPage->SelItem, pPage->Count, currentPagePos);
}

#else
static void MenuItem_OnNext(lv_obj_t* obj)
{

	TM_MENU    *pMenu;
	TM_PAGE    *pPage;

	pMenu = MenuCommonItem_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pPage->SelItem++;
	//check item if disable
	TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);
	if (pPage->SelItem == pPage->Count) {//8--->9,==>0
		//lv_plugin_scr_close(obj, NULL);
		pPage->SelItem = 0;
		MenuCommonItem_UpdateContent(pMenu);
		//lv_plugin_menu_select_next_item(menu_item);
		lv_plugin_menu_select_item(menu_item,0);//first
		MenuCommonItem_CalcPageInfo();
	} else {
		MenuCommonItem_UpdateContent(pMenu);
		lv_plugin_menu_select_next_item(menu_item);
		MenuCommonItem_CalcPageInfo();
	}
	
	DBG_DUMP("555pPage->SelItem=%d,pPage->Count=%d\r\n",pPage->SelItem,pPage->Count);
}
#endif
static void MenuItem_OnPrev(lv_obj_t* obj)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;


	pMenu = MenuCommonItem_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	if (pPage->SelItem == 0) {
		// Close current UI Window now
//		Ux_CloseWindow(&MenuCommonItemCtrl, 0);
		#if 0
		lv_plugin_scr_close(obj, NULL);
		#else
		pPage->SelItem = pPage->Count-1;
		MenuCommonItem_UpdateContent(pMenu);
		lv_plugin_menu_select_prev_item(menu_item);
		MenuCommonItem_CalcPageInfo();
		DBG_IND("4444pPage->SelItem=%d,pPage->Count=%d\r\n",pPage->SelItem,pPage->Count);
		#endif
	} else {
		pPage->SelItem--;
		//check item if disable
		TM_CheckItemStatus(pMenu, &pPage->SelItem, FALSE);
		if (pPage->SelItem == pPage->Count) {
			#if 0
			lv_plugin_scr_close(obj, NULL);
			#else
			
			DBG_IND("1111pPage->SelItem=%d,pPage->Count=%d\r\n",pPage->SelItem,pPage->Count);
			MenuCommonItem_UpdateContent(pMenu);
			lv_plugin_menu_select_prev_item(menu_item);
			MenuCommonItem_CalcPageInfo();
			#endif
		} else {
			MenuCommonItem_UpdateContent(pMenu);
			lv_plugin_menu_select_prev_item(menu_item);
			MenuCommonItem_CalcPageInfo();
			DBG_IND("3333pPage->SelItem=%d,pPage->Count=%d\r\n",pPage->SelItem,pPage->Count);
		}
	}
}

static void MenuItem_OnSelected(lv_obj_t* obj)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;


	pMenu = MenuCommonItem_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];
#if 1
	lv_obj_set_hidden(label_menu_item_page_num,TRUE);
	if (pItem->Count != 0 && pItem->SysFlag != 0) 
	{
		lv_plugin_scr_open(UIFlowMenuCommonOption, g_pItemMenu);
	}
	else
	{
		g_pItemMenu->Status = TMS_ON_CUSTOM;
		TM_ITEM_CALLBACK(pItem, TMM_CONFIRM_OPTION, pItem->ItemId); 
	}
#else
	if (pItem->Count != 0 && pItem->SysFlag != 0 && pItem->ItemId != IDM_COMMON_CLOUD) {
		SelOption = SysGetFlag(pItem->SysFlag);

		SelOption++;
		if (SelOption >= pItem->Count) {
			SelOption = 0;
		}

		SysSetFlag(pItem->SysFlag, SelOption);

		// toggle icon's string
		pOption = &pItem->pOptions[SelOption];

		lv_plugin_label_set_text(label_menu_item_page_num, pOption->TextId);
		lv_plugin_label_update_font(label_menu_item_page_num, LV_OBJ_PART_MAIN);

		TM_MENU_CALLBACK(pMenu, TMM_CONFIRM_OPTION, MAKE_LONG(pItem->ItemId, SelOption));
	} else {
		if (pItem->SysFlag == FL_COMMON_MODE) {
			// Enter 2nd level menu and pop up various memu item.
			lv_plugin_scr_open(UIFlowMenuCommonOption, &gModeMenu);

		} else if (pItem->SysFlag == FL_COMMON_MENU) {
#if (PHOTO_MODE == ENABLE)
			// Enter 2nd level menu and pop up current mode's menu lists
			if (System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PHOTO) {
				pNextMenu = &gPhotoMenu;
#if (PLAY_MODE == ENABLE)
			} else if (System_GetState(SYS_STATE_CURRMODE) == PRIMARY_MODE_PLAYBACK) {
				pNextMenu = &gPlaybackMenu;
#endif
			} else {
				pNextMenu = &gMovieMenu;
			}
#else
				pNextMenu = &gMovieMenu;
#endif
			lv_plugin_scr_open(UIFlowMenuCommonOption, pNextMenu);

		} else if (pItem->SysFlag == FL_COMMON_SETUP) {
			// Enter 2nd level menu and pop up various memu item.
			lv_plugin_scr_open(UIFlowMenuCommonOption, &gSetupMenu);

		} else if (pItem->SysFlag == FL_COMMON_EXT_SETUP) {
			#if _TODO
			// Enter 2nd level menu and pop up various memu item.
//			Ux_OpenWindow(&MenuCommonOptionCtrl, 1, &gExtSetupMenu);
			#endif
		} else {
			DBG_ERR("not supp %d\r\n", pItem->SysFlag);
		}
	}
#endif
}

void MenuItem_OnClose(lv_obj_t* obj)
{
	INT32 curMode = System_GetState(SYS_STATE_CURRMODE);
	Input_SetKeyMask(KEY_PRESS, FLGKEY_KEY_MASK_DEFAULT);
	Input_SetKeyMask(KEY_RELEASE, FLGKEY_KEY_MASK_DEFAULT);
	Input_SetKeyMask(KEY_CONTINUE, FLGKEY_KEY_MASK_DEFAULT);
#if (MOVIE_MODE==ENABLE)
	//#NT#2016/08/19#Lincy Lin#[0106935] -begin
	//#NT# Support change WDR, SHDR, RSC setting will change mode after exit menu
	BOOL bReOpenMovie = FlowMovie_CheckReOpenItem();
	BOOL bReOpenPhoto = 0;
#if (PHOTO_MODE==ENABLE)
	bReOpenPhoto = FlowPhoto_CheckReOpenItem();
#endif
	if(bReOpenMovie)
		DBG_DUMP("RESTART_MODE_YES\r\n");
	else
		DBG_DUMP("RESTART_MODE_NO\r\n");
	if (bReOpenMovie || bReOpenPhoto || (curMode == PRIMARY_MODE_MOVIE) || (curMode == PRIMARY_MODE_PHOTO))
    //#NT#2016/08/19#Lincy Lin -end
    {
        if ((curMode == PRIMARY_MODE_MOVIE) || (curMode == PRIMARY_MODE_PHOTO)) {
            Save_MenuInfo();
        }
        Ux_PostEvent(NVTEVT_SYSTEM_MODE, 1, System_GetState(SYS_STATE_CURRMODE));
    }
#endif

}

void MenuItem_OnOpen(lv_obj_t* obj)
{
	DBG_DUMP("MenuItem_OnOpen\r\n");

	TM_MENU    *pMenu = NULL;
	TM_PAGE    *pPage = NULL;
	//TM_ITEM    *pItem = NULL;
	//TM_OPTION  *pOption = NULL;
	//TM_ITEM    *pModeItem = NULL;

	Input_SetKeyMask(KEY_PRESS, MENU_KEY_PRESS_MASK);
	Input_SetKeyMask(KEY_RELEASE, MENU_KEY_RELEASE_MASK);
	Input_SetKeyMask(KEY_CONTINUE, MENU_KEY_CONTINUE_MASK);

	//MenuCommonItem_SetCurrentMenu(&gCommonMenu);
	MenuCommonItem_SetCurrentMenu(&gMovieMenu);
	pMenu = MenuCommonItem_GetCurrentMenu();

	pMenu->Status = TMS_ON_ITEM;
	pMenu->SelPage = 0;         // reset page to 0

	pPage = &pMenu->pPages[pMenu->SelPage];
	pPage->SelItem = 0;           // reset item to 0
	//check item if disable
	TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);
	
	#if 0
	pItem = &pPage->pItems[pPage->SelItem];

	if(pItem->Count){
		pOption = &pItem->pOptions[SysGetFlag(pItem->SysFlag)];
		lv_plugin_label_set_text(label_menu_item_page_num, pOption->TextId);
		lv_plugin_label_update_font(label_menu_item_page_num, LV_OBJ_PART_MAIN);
	}
	#endif
	/* check menu item is init */
	if(!lv_plugin_menu_item_cnt(menu_item)){
		/* allocate menu item */
		lv_plugin_menu_init_items(menu_item, PAGE);
	}
	#if 0
	lv_plugin_label_set_text(label_menu_item_title, pPage->TextId);
	lv_plugin_label_update_font(label_menu_item_title, LV_OBJ_PART_MAIN);
	#endif
	
	MenuCommonItem_UpdateContent(pMenu);
	lv_plugin_menu_select_item(menu_item, 0);
	MenuCommonItem_CalcPageInfo();

	Input_SetKeyMask(KEY_PRESS, MENU_KEY_PRESS_MASK);
	Input_SetKeyMask(KEY_RELEASE, MENU_KEY_PRESS_MASK);
	Input_SetKeyMask(KEY_CONTINUE, MENU_KEY_PRESS_MASK);
	Input_SetKeySoundMask(KEY_PRESS, MENU_KEY_PRESS_MASK);

}

static void MenuCommonItem_UpdateContent(TM_MENU *pMenu)
{
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	//TM_OPTION  *pOption;
	UINT32      i;
	UINT16      startIndex = 0;
	UINT16      itemIndex = 0;

	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];
	//pOption = &pItem->pOptions[SysGetFlag(pItem->SysFlag)];

	#if 0
	if (pItem->Count) {
		lv_plugin_label_set_text(label_menu_item_page_num, pOption->TextId);
		lv_plugin_label_update_font(label_menu_item_page_num, LV_OBJ_PART_MAIN);
	} else if (pItem->ItemId == IDM_COMMON_MENU) {
		lv_plugin_label_set_text(label_menu_item_page_num, LV_PLUGIN_STRING_ID_STRID_SETUP);
		lv_plugin_label_update_font(label_menu_item_page_num, LV_OBJ_PART_MAIN);
	} else {
		lv_plugin_label_set_text(label_menu_item_page_num, LV_PLUGIN_STRING_ID_STRID_NULL_);
		lv_plugin_label_update_font(label_menu_item_page_num, LV_OBJ_PART_MAIN);
	}

	lv_plugin_label_set_text(label_menu_item_title, pItem->TextId);
	lv_plugin_label_update_font(label_menu_item_title, LV_OBJ_PART_MAIN);
	#endif

	//find startIndex
	TM_FindStartIndex(pMenu, PAGE, &startIndex);

	//draw item form startIndex
	itemIndex = startIndex;
	for (i = 0; i < PAGE; i++) {
		//check item if disable
		TM_CheckItemStatus(pMenu, &itemIndex, TRUE);
		if ((itemIndex == pPage->Count) && (i < PAGE)) {
			lv_plugin_menu_set_item_string_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pItem->TextId);
			lv_plugin_menu_set_item_img_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pItem->IconId);
			lv_plugin_menu_set_item_hidden(menu_item, i, true);
		} else {
			pItem = &pPage->pItems[itemIndex];

			lv_plugin_menu_set_item_string_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pItem->TextId);
			lv_plugin_menu_set_item_img_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pItem->IconId);
			lv_plugin_menu_set_item_hidden(menu_item, i, false);

			itemIndex++;
		}
	}
}



static void UIFlowMenuCommonItem_ScrOpen(lv_obj_t* obj)
{
	DBG_DUMP("UIFlowMenuCommonItem_ScrOpen\r\n");


	/***********************************************************************************
	 * Add Menu Screen into group and set group to keypad indev
	 ***********************************************************************************/
	set_indev_keypad_group(obj);


    /***********************************************************************************
     * create a plugin menu, the menu should contains below widgets :
     *
     *  container (parent)
     *
     *  	btn or imgbtn (item1)
     *  		label + img (item1's label and img)
     *
     *  	btn or imgbtn (item2)
     *  		label + img (item2's label and img)
     *
     *  	....
     *
     *	those widgets styles and number of buttons are configured in the builder,
     *	btn's label or img is not mandatory
     *
     **********************************************************************************/
	if(menu_item == NULL){
		menu_item = lv_plugin_menu_create(obj, container_main_menu_scr_uiflowmenucommonitem);
		lv_plugin_menu_set_wrap(menu_item, true);
	}

	if(label_menu_item_title == NULL)
		label_menu_item_title = label_menu_title_scr_uiflowmenucommonitem;

	if(label_menu_item_page_num == NULL)
		label_menu_item_page_num = label_menu_page_num_scr_uiflowmenucommonitem;

    MenuItem_OnOpen(obj);

}

static void UIFlowMenuCommonItem_Key(lv_obj_t* obj, uint32_t key)
{

	switch(key)
	{
	case LV_KEY_DOWN:
	case LV_USER_KEY_NEXT:
	{
		MenuItem_OnNext(obj);
		break;
	}

	case LV_KEY_UP:
	case LV_USER_KEY_PREV:
	{
		MenuItem_OnPrev(obj);
		break;
	}
	case LV_KEY_ENTER:
	case LV_USER_KEY_SELECT:
	{
		MenuItem_OnSelected(obj);
		break;
	}

	case LV_KEY_LEFT:
	case LV_USER_KEY_SHUTTER2:
	{
		lv_plugin_scr_close(obj, NULL);
		break;
	}

	}

}

static void UIFlowMenuCommonItem_ScrClose(lv_obj_t* obj)
{
	DBG_DUMP("%s\r\n", __func__);

	MenuItem_OnClose(obj);
}


static void UIFlowMenuCommonItem_ChildScrClose(lv_obj_t* obj,const LV_USER_EVENT_NVTMSG_DATA* msg)
{
	DBG_DUMP("%s\r\n", __func__);

	set_indev_keypad_group(obj);
	MenuCommonItem_CalcPageInfo();
}


void container_main_menu_callback(lv_obj_t* obj, lv_event_t event)
{
	DBG_DUMP("%s\r\n", __func__);
}

void UIFlowMenuCommonItemEventCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{
	case LV_PLUGIN_EVENT_SCR_OPEN:
	{
		UIFlowMenuCommonItem_ScrOpen(obj);
		break;
	}

	case LV_PLUGIN_EVENT_SCR_CLOSE:
	{
		UIFlowMenuCommonItem_ScrClose(obj);
		break;
	}

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
	{
		UIFlowMenuCommonItem_ChildScrClose(obj,(const LV_USER_EVENT_NVTMSG_DATA*)lv_event_get_data());

		break;
	}

	case LV_EVENT_PRESSED:

		break;

	case LV_EVENT_RELEASED:
		break;

	case LV_EVENT_CLICKED:
		break;

	case LV_EVENT_KEY:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();
		DBG_IND("menu item LV_EVENT_KEY============item\r\n");
		/* handle key event */
		UIFlowMenuCommonItem_Key(obj, *key);

		/***********************************************************************************
		 * IMPORTANT!!
		 *
		 * calling lv_indev_wait_release to avoid duplicate event in long pressed key state
		 * the event will not be sent again until released
		 *
		 ***********************************************************************************/
		if(*key != LV_KEY_ENTER)
			lv_indev_wait_release(lv_indev_get_act());
		break;
	}

	default:
		break;

	}

}
