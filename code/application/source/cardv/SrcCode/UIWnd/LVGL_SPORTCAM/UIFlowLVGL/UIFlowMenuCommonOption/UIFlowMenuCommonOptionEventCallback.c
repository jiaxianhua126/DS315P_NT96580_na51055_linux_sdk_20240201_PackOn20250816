
#include "PrjInc.h"
#include "UIFlowLVGL/UIFlowLVGL.h"
#include "UIApp/Network/UIAppNetwork.h"
#include <kwrap/debug.h>

#define PAGE           4


static lv_group_t* gp = NULL;
static lv_obj_t* menu_item = NULL;
static lv_obj_t* label_menu_option_title = NULL;//menu option title
static lv_obj_t* label_menu_option_page_num = NULL;//menu option page num
static TM_MENU *g_pOptionMenu = 0;
static UINT16   SelectOption = 0;
static UINT16   SelectCount = 0;
static void set_indev_keypad_group(lv_obj_t* obj)
{
	if(gp == NULL){
		gp = lv_group_create();
		lv_group_add_obj(gp, obj);
	}

	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
	lv_indev_set_group(indev, gp);
}

static void MenuCommonOption_SetCurrentMenu(TM_MENU *pMenu)
{
	g_pOptionMenu = pMenu;
}

static TM_MENU *MenuCommonOption_GetCurrentMenu(void)
{
	return g_pOptionMenu;
}
static UINT8  g_Option_PageNumBuf[8];
void MenuCommonOption_SelIcon_ShowInit(void)
{
	lv_obj_set_hidden(image_select0_scr_uiflowmenucommonoption,true);
	lv_obj_set_hidden(image_select1_scr_uiflowmenucommonoption,true);
	lv_obj_set_hidden(image_select2_scr_uiflowmenucommonoption,true);
	lv_obj_set_hidden(image_select3_scr_uiflowmenucommonoption,true);
}

void MenuCommonOption_CalcPageInfo(UINT32 Sel)
{
    UINT32  i, uiItem, uiCurrItem, uiTotalItem, uiTotalItemOri;
    UINT32  uiItemPerPage, uiCurrPage, uiTotalPage;

    TM_MENU*    pMenu = MenuCommonOption_GetCurrentMenu();
    TM_PAGE*    pPage;
    TM_ITEM*    pItem;
	TM_OPTION  *pOption;

    pPage = &pMenu->pPages[pMenu->SelPage];
    pItem = &pPage->pItems[pPage->SelItem];
    uiItem = SelectOption;          					 // current item number in menu (include disabled items)
    uiItemPerPage = PAGE; 								 // items per page
    uiTotalItemOri = pItem->Count;  					 // total item number

    // check total item number and current item number (skip disabled items)
    uiCurrItem = 0;
    uiTotalItem = 0;

    for (i = 0; i < uiTotalItemOri; i++) {
		pOption = &pItem->pOptions[i];
        //if (UxMenu_GetItemData(pCtrl, i, MNUITM_STATUS) == STATUS_ENABLE) {
        if ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_ENABLE) {
            uiTotalItem++;
            if (i < uiItem)
                uiCurrItem++;
        }
    }

    uiCurrPage = (uiCurrItem / uiItemPerPage) + 1;
    uiTotalPage = ((uiTotalItem % uiItemPerPage) == 0) ? (uiTotalItem / uiItemPerPage) : (uiTotalItem / uiItemPerPage + 1);

 
    sprintf((char *)g_Option_PageNumBuf, "%02d/%02d", uiCurrPage, uiTotalPage);
	lv_label_set_text_fmt(label_menu_option_page_num, "%s",g_Option_PageNumBuf);	

}

#if 0
static void MenuCommonOption_UpdateContent(TM_MENU *pMenu)
{
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	TM_OPTION  *pOption;
	UINT32      i;
	UINT16      startIndex = 0;
	UINT16      itemIndex = 0;
	UINT16      SelOption = 0;
	DBG_DUMP("%s\r\n", __func__);

	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];
	SelOption = SysGetFlag(pItem->SysFlag);
	TM_CheckOptionStatus(pMenu, &SelOption, TRUE);
	SysSetFlag(pItem->SysFlag, SelOption); //SelOption might change

	pOption = &pItem->pOptions[SelOption];

	if (pItem->Count) {
		lv_plugin_label_set_text(label_menu_option_page_num, pOption->TextId);
		lv_plugin_label_update_font(label_menu_option_page_num, LV_OBJ_PART_MAIN);

	} else {
		if (pItem->ItemId == IDM_VERSION) {
			lv_plugin_label_set_text(label_menu_option_page_num, LV_PLUGIN_RES_ID_NONE);
			lv_label_set_text(label_menu_option_page_num, Prj_GetVersionString());
			lv_plugin_label_update_font(label_menu_option_page_num, LV_OBJ_PART_MAIN);

		} else {
			lv_plugin_label_set_text(label_menu_option_page_num, LV_PLUGIN_STRING_ID_STRID_NULL_);
			lv_plugin_label_update_font(label_menu_option_page_num, LV_OBJ_PART_MAIN);
		}
	}
	lv_plugin_label_set_text(label_menu_option_title, pItem->TextId);
	lv_plugin_label_update_font(label_menu_option_title, LV_OBJ_PART_MAIN);

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
#else
static void Option_Findstartindex(TM_MENU *pMenu, UINT16 pageitem, UINT16 *startindex)
{
	UINT32 enableCount = 0;
	UINT16 index = 0;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	TM_OPTION  *pOption;
    
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];

	if (SelectCount == 1) {
		*startindex = SelectOption;
	} else {
	        DBG_IND("Option_FindStartIndex.SelectOption=%d\r\n",SelectOption);
		for (index = 0; index <= SelectOption; index++) {
             pOption = &pItem->pOptions[index];
//			if (((&pPage->pItems[index])->Status & TM_ITEM_STATUS_MASK) == TM_ITEM_ENABLE) {
            if ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_ENABLE){
				enableCount++;
				if ((enableCount % pageitem) == 1) {
					*startindex = index;
                    DBG_IND("Option_FindStartIndex.index=%d\r\n",index);
				}
			}
		}
	}
}

static void MenuCommonOption_UpdateContent(TM_MENU *pMenu)
{
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	TM_OPTION  *pOption;
	UINT32      i;
    	
	UINT16      startOptionIndex = 0;
	UINT16      OptionIndex = 0;
	
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];
			
	lv_plugin_label_set_text(label_menu_option_title, pItem->TextId);
	lv_plugin_label_update_font(label_menu_option_title, LV_OBJ_PART_MAIN);

    Option_Findstartindex(pMenu, PAGE, &startOptionIndex);
        
	//draw item form startIndex
	OptionIndex = startOptionIndex;
	DBG_IND("startOptionIndex =%d \r\n",startOptionIndex);
    DBG_IND("pItem->Count =%d \r\n",pItem->Count);
	for (i = 0; i < PAGE; i++) {
		//check item if disable
		pOption = &pItem->pOptions[OptionIndex];
#if 1
	        DBG_IND("pOption->Status =%d \r\n",(pOption->Status));
	        DBG_IND("(pOption->Status) & TM_OPTION_STATUS_MASK =%d \r\n",(pOption->Status) & TM_OPTION_STATUS_MASK);
		while (((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT)&&(OptionIndex< pItem->Count)) {
        	        DBG_DUMP("OptionIndex =%d \r\n",OptionIndex);
			if (++OptionIndex ==pItem->Count) {
				break;
			}
			pOption = &pItem->pOptions[OptionIndex];
		}
#endif

   	        DBG_IND("OptionIndex =%d ,pItem->Count = %d i=%d\r\n",OptionIndex,pItem->Count,i);
		if ((OptionIndex == pItem->Count) && (i < PAGE)) {
//			lv_plugin_menu_set_item_string_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pOption->TextId);
			lv_plugin_menu_set_item_hidden(menu_item, i, true);
		} else {
//			pItem = &pPage->pItems[OptionIndex];
			lv_plugin_menu_set_item_string_id(menu_item, i, LV_PLUGIN_MENU_ITEM_VISIBLE_STATE_NUM, pOption->TextId);
			lv_plugin_menu_set_item_hidden(menu_item, i, false);
			OptionIndex++;
	        DBG_IND("%d,MenuCommon_UpdateContent.pMenu->Status =%d OptionIndex =%d SysGetFlag(pItem->SysFlag) =%dSelectOption =%d \r\n",pMenu->Status,OptionIndex,SysGetFlag(pItem->SysFlag),SelectOption);
            if (pMenu->Status == TMS_ON_ITEM){
                if(OptionIndex ==(SysGetFlag(pItem->SysFlag)+1))
                {
                    DBG_IND("11111i =%d  OptionIndex = %d SysGetFlag(pItem->SysFlag) = %d\r\n",i,OptionIndex,SysGetFlag(pItem->SysFlag));
                    lv_plugin_menu_select_item(menu_item, i);
                }
            }else{
                if(OptionIndex ==(SelectOption+1))
                {
                	DBG_IND("222222i =%d \r\n",i);
                    lv_plugin_menu_select_item(menu_item, i);
                }
            }
		}
	}

}

#endif
static void MenuItem_OnOpen(lv_obj_t* obj, TM_MENU *data)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	//TM_OPTION  *pOption;
	//UINT16      SelOption = 0;
	DBG_DUMP("%s\r\n", __func__);

	#if 1
	if(NULL == data)
		return;
	MenuCommonOption_SetCurrentMenu(data);
	pMenu = MenuCommonOption_GetCurrentMenu();
	pMenu->Status = TMS_ON_OPTION;
	//pMenu->SelPage = 0;
	pPage = &pMenu->pPages[pMenu->SelPage];
	//pPage->SelItem = 0;
	//check item if disable
	TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);
	
	pItem = &pPage->pItems[pPage->SelItem];
	SelectOption = SysGetFlag(pItem->SysFlag);
	SelectCount = pItem->Count;
	
	DBG_DUMP("MenuOptionYnd_OnOpen.SysGetFlag(pItem->SysFlag)=%d\r\n",SysGetFlag(pItem->SysFlag));
	DBG_DUMP("MenuOptionYnd_OnOpen.SysGetFlag(pItem->SysFlag)..OPTIONPAGE=%d\r\n",SysGetFlag(pItem->SysFlag)%PAGE);
	/* check menu item is init */
	if(!lv_plugin_menu_item_cnt(menu_item)){
		/* allocate menu item */
		lv_plugin_menu_init_items(menu_item, PAGE);
	}	
	MenuCommonOption_SelIcon_ShowInit();
	MenuCommonOption_UpdateContent(pMenu);
	lv_plugin_menu_select_item(menu_item, SelectOption);
	MenuCommonOption_CalcPageInfo(SelectOption);

	#else// TBD
	if(NULL == data)
		return;

	MenuCommonOption_SetCurrentMenu(data);
	pMenu = MenuCommonOption_GetCurrentMenu();
	pMenu->Status = TMS_ON_OPTION;
	pMenu->SelPage = 0;

	pPage = &pMenu->pPages[pMenu->SelPage];
	pPage->SelItem = 0;
	//check item if disable
	TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);
	pItem = &pPage->pItems[pPage->SelItem];
	if (pItem->Count > 0) {
		SelOption = SysGetFlag(pItem->SysFlag);
		//check option if disable
		TM_CheckOptionStatus(pMenu, &SelOption, TRUE);
		SysSetFlag(pItem->SysFlag, SelOption); //SelOption might change

		pOption = &pItem->pOptions[SelOption];

		lv_plugin_label_set_text(label_menu_option_page_num, pOption->TextId);
		lv_plugin_label_update_font(label_menu_option_page_num, LV_OBJ_PART_MAIN);
	}

	/* check menu item is init */
	if(!lv_plugin_menu_item_cnt(menu_item)){
		/* allocate menu item */
		lv_plugin_menu_init_items(menu_item, PAGE);
	}

	MenuCommonOption_UpdateContent(pMenu);

	lv_plugin_menu_select_item(menu_item, 0);
	#endif
    #if _TODO
//		UI_SetDisplayPalette(LAYER_OSD1, 0, 256, gDemoKit_PaletteOption_Palette);
    #endif
//		Ux_DefaultEvent(pCtrl, NVTEVT_OPEN_WINDOW, paramNum, paramArray);

}

static void MenuItem_OnNext(lv_obj_t* obj)
#if 1
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	TM_OPTION  *pOption;
	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];

    SelectOption++;
    DBG_IND("Menu_OnNext.SelectOption = %d ,SelectCount = %d\r\n",SelectOption,SelectCount);
    if (SelectOption == SelectCount)
	{
        SelectOption = 0;
        pOption = &pItem->pOptions[SelectOption];
		while ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT) {
			if (++SelectOption ==SelectCount) {
				SelectOption=0;
			}
			pOption = &pItem->pOptions[SelectOption];
		}
        DBG_IND("Menu_OnPrev.TMS_ON_OPTION.SelectOption = %d \r\n",SelectOption);                    
        MenuCommonOption_UpdateContent(pMenu);
		MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
    }
	else
	{
        pOption = &pItem->pOptions[SelectOption];
		while ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT) {
			if (++SelectOption ==SelectCount) {
				SelectOption=0;
			}
			pOption = &pItem->pOptions[SelectOption];
		}
        DBG_IND("Menu_OnPrev.TMS_ON_OPTION.SelectOption = %d \r\n",SelectOption);                    
        MenuCommonOption_UpdateContent(pMenu);
		MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
    }
}

#else
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
//	TM_ITEM    *pItem;
	DBG_DUMP("%s\r\n", __func__);


	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
//	pItem = &pPage->pItems[pPage->SelItem];

	//pPage->SelItem++;
	//check item if disable
	TM_CheckItemStatus(pMenu, &pPage->SelItem, TRUE);

	if (pPage->SelItem == pPage->Count) {
		#if 0
		lv_plugin_scr_close(obj, NULL);
		#else
		pPage->SelItem = 0;
		MenuCommonOption_UpdateContent(pMenu);
		lv_plugin_menu_select_next_item(menu_item);
		#endif
	} else {
		MenuCommonOption_UpdateContent(pMenu);
		lv_plugin_menu_select_next_item(menu_item);
	}
}
#endif
static void MenuItem_OnPrev(lv_obj_t* obj)
#if 1
{ 
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	TM_OPTION  *pOption;
	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];


    if (SelectOption == 0){
        SelectOption = SelectCount - 1;
        pOption = &pItem->pOptions[SelectOption];
		while ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT) 
		{
			if (--SelectOption ==0) {
				SelectOption=SelectCount - 1;
			}
			pOption = &pItem->pOptions[SelectOption];
		}
        DBG_IND("Menu_OnPrev.TMS_ON_OPTION.SelectOption = %d \r\n",SelectOption);
        MenuCommonOption_UpdateContent(pMenu);
		MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
    }
	else
	{
		SelectOption--;
		if (SelectOption == SelectCount) 
		{
	        SelectOption=0;
			MenuCommonOption_UpdateContent(pMenu);
			MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
		} 
		else if (SelectOption == 0)
		{
            pOption = &pItem->pOptions[SelectOption];
			while ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT)
			{
	            if(SelectOption ==0)
				{
	                 SelectOption=SelectCount - 1;
	            }
				else
	            {
	    			if (--SelectOption ==0) 
					{
	    				SelectOption=SelectCount - 1;
	    			}
	            }
				pOption = &pItem->pOptions[SelectOption];
			}
            DBG_IND("Menu_OnPrev.TMS_ON_OPTION.SelectOption = %d \r\n",SelectOption);
            MenuCommonOption_UpdateContent(pMenu);
			MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
	    }
		else
		{
            pOption = &pItem->pOptions[SelectOption];
    		while ((pOption->Status & TM_OPTION_STATUS_MASK) == TM_OPTION_NOT_SUPPORT) {
    			if (--SelectOption ==0) {
    				SelectOption=SelectCount - 1;
    			}
    			pOption = &pItem->pOptions[SelectOption];
    		}
            DBG_IND("Menu_OnPrev.TMS_ON_OPTION.SelectOption = %d \r\n",SelectOption);
			MenuCommonOption_UpdateContent(pMenu);
			MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));
		}
    }
}

#else
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
//	TM_ITEM    *pItem;

	DBG_DUMP("%s\r\n", __func__);

	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
//	pItem = &pPage->pItems[pPage->SelItem];
	if (pPage->SelItem == 0) {
		// Close current UI Window now
//		Ux_CloseWindow(&MenuCommonOptionCtrl, 2, pItem->ItemId, 0);
		#if 0
		lv_plugin_scr_close(obj, NULL);
		#else
		pPage->SelItem = pPage->Count;
		MenuCommonOption_UpdateContent(pMenu);
		lv_plugin_menu_select_prev_item(menu_item);
		#endif
	} else{
		//pPage->SelItem--;
		//check item if disable
		TM_CheckItemStatus(pMenu, &pPage->SelItem, FALSE);
		if (pPage->SelItem == pPage->Count - 1) {
			#if 0
			lv_plugin_scr_close(obj, NULL);
			#else
			MenuCommonOption_UpdateContent(pMenu);
			lv_plugin_menu_select_prev_item(menu_item);
			#endif
		} else {
			if(pPage->SelItem == 0)
			{
				pPage->SelItem = pPage->Count - 1;
				MenuCommonOption_UpdateContent(pMenu);
//				MenuCommonOption_UpdatePosition();
//				Ux_SendEvent(pCtrl, NVTEVT_PREVIOUS_ITEM, 0);
				lv_plugin_menu_select_prev_item(menu_item);
			}
			else
			{
				MenuCommonOption_UpdateContent(pMenu);
//				MenuCommonOption_UpdatePosition();
//				Ux_SendEvent(pCtrl, NVTEVT_PREVIOUS_ITEM, 0);
				lv_plugin_menu_select_prev_item(menu_item);
			}
		}
	}
}
#endif
static void MenuOption_OnSelectedExit(lv_obj_t* obj)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	// UIFlowMenuWndCustomerConfirm_Set_Text_Param param = {0};
		
	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];

	TM_CheckOptionStatus(pMenu, &SelectOption, TRUE);
	DBG_DUMP("Menu_OnSelected.SelectOption = %d \r\n",SelectOption);
	
	SysSetFlag(pItem->SysFlag, SelectOption);
	switch (pItem->ItemId){
        default:
            // Close current UI Window now
			lv_plugin_scr_close(UIFlowMenuCommonOption, gen_nvtmsg_data(NVTEVT_NULL, 0));
			DBG_DUMP("Menu_OnSelected.SysGetFlag(pItem->SysFlag) = %d \r\n",SysGetFlag(pItem->SysFlag));
			TM_MENU_CALLBACK(pMenu, TMM_CONFIRM_OPTION, MAKE_LONG(pItem->ItemId, SelectOption));
            break;
        }
}

static void UIFlowMenuCommonOption_ScrClose(lv_obj_t* obj)
{
	DBG_IND("%s\r\n", __func__);
}

static void UIFlowMenuCommonOption_ChildScrClose(lv_obj_t* obj)
{
	TM_MENU    *pMenu;
	TM_PAGE    *pPage;
	TM_ITEM    *pItem;
	pMenu = MenuCommonOption_GetCurrentMenu();
	pPage = &pMenu->pPages[pMenu->SelPage];
	pItem = &pPage->pItems[pPage->SelItem];

	DBG_DUMP("%s\r\n", __func__);

	set_indev_keypad_group(obj);
    MenuCommonOption_UpdateContent(pMenu);
	MenuCommonOption_CalcPageInfo(SysGetFlag(pItem->SysFlag));

}

static void UIFlowMenuCommonOption_ScrOpen(lv_obj_t* obj, const void *data)
{

	DBG_DUMP("%s\r\n", __func__);

	/***********************************************************************************
	 * Add Menu Screen into group and set group to keypad indev
	 ***********************************************************************************/
//	if(gp == NULL){
//		gp = lv_group_create();
//		lv_group_add_obj(gp, obj);
//	}
//
//	lv_indev_t* indev = lv_plugin_find_indev_by_type(LV_INDEV_TYPE_KEYPAD);
//	lv_indev_set_group(indev, gp);
//	lv_group_focus_obj(obj);

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
		menu_item = lv_plugin_menu_create(obj, container_main_menu_scr_uiflowmenucommonoption);
		lv_plugin_menu_set_wrap(menu_item, true);
	}

	if(label_menu_option_title == NULL)
		label_menu_option_title = label_menu_title_scr_uiflowmenucommonoption;

	if(label_menu_option_page_num == NULL)
		label_menu_option_page_num = label_menu_page_num_scr_uiflowmenucommonoption;

    MenuItem_OnOpen(obj, (TM_MENU *)data);

}

static void UIFlowMenuCommonOption_Key(lv_obj_t* obj, uint32_t key)
{
	DBG_IND("%s\r\n", __func__);

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
		MenuOption_OnSelectedExit(obj);
		break;
	}

	case LV_KEY_LEFT:
	case LV_USER_KEY_SHUTTER2:
	{
		lv_plugin_scr_close(UIFlowMenuCommonOption, NULL);
		break;
	}


	}

}
static void UIFlowMenuCommonOption_KeyRelease(lv_obj_t* obj, uint32_t key)
{

	switch(key)
	{

	case LV_USER_KEY_DOWN:
	{
		DBG_IND("UIFlowMenuCommonOption_KeyRelease.LV_USER_KEY_DOWN \r\n");	
		break;
	}

	case LV_USER_KEY_UP:
	{
		DBG_IND("UIFlowMenuCommonOption_KeyRelease.LV_USER_KEY_UP \r\n");	
		break;
	}
	case LV_USER_KEY_MENU:
	{
		DBG_IND("UIFlowMenuCommonOption_KeyRelease.LV_USER_KEY_MENU \r\n");	
		break;
	}
	case LV_USER_KEY_SHUTTER2:
	{
		DBG_IND("UIFlowMenuCommonOption_KeyRelease.LV_USER_KEY_SHUTTER2 \r\n");	
		break;
	}

	}

}

void UIFlowMenuCommonOptionEventCallback(lv_obj_t* obj, lv_event_t event)
{

	switch(event)
	{
	case LV_PLUGIN_EVENT_SCR_OPEN:
	{
		UIFlowMenuCommonOption_ScrOpen(obj, lv_event_get_data());
		break;
	}

	case LV_PLUGIN_EVENT_SCR_CLOSE:
	{
		UIFlowMenuCommonOption_ScrClose(obj);
		break;
	}

	case LV_PLUGIN_EVENT_CHILD_SCR_CLOSE:
	{
		UIFlowMenuCommonOption_ChildScrClose(obj);
		break;
	}

	case LV_EVENT_PRESSED:
		DBG_IND("menu option LV_EVENT_RELEASED==\r\n");
		//lv_plugin_menu_set_selected_item_pressed(menu_item);
		break;

	case LV_EVENT_RELEASED:
		DBG_IND("menu option LV_EVENT_RELEASED==\r\n");
		//lv_plugin_menu_set_selected_item_released(menu_item);
		break;

	case LV_EVENT_CLICKED:
		DBG_IND("menu option LV_EVENT_CLICKED========\r\n");
		//MenuOption_OnSelected(obj);
		break;

	case LV_EVENT_KEY:
	{
		uint32_t* key = (uint32_t*)lv_event_get_data();
		DBG_IND("LV_EVENT_KEY============\r\n");
		/* handle key event */
		UIFlowMenuCommonOption_Key(obj, *key);


		/***********************************************************************************
		 * IMPORTANT!!
		 *
		 * calling lv_indev_wait_release to avoid duplicate event in long pressed key state
		 * the event will not be sent again until released
		 *
		 ***********************************************************************************/
		//if(*key != LV_KEY_ENTER)
		if(key && *key != LV_KEY_ENTER){
			lv_indev_wait_release(lv_indev_get_act());
		}
		break;
	}
	case LV_USER_EVENT_KEY_RELEASE:
	{
		
		uint32_t* key = (uint32_t*)lv_event_get_data();
		DBG_IND("LV_USER_EVENT_KEY_RELEASE============\r\n");
		UIFlowMenuCommonOption_KeyRelease(obj, *key);

		break;
	}

	default:
		break;

	}

}
