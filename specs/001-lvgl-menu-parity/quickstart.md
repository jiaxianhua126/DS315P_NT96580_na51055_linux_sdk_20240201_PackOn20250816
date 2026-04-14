# Quick-Start: LVGL Menu Parity with SPORTCAM

**Feature**: `specs/001-lvgl-menu-parity`  
**Date**: 2026-04-14

---

## Prerequisites

```bash
# Source the build environment (run once per shell session)
source build/envsetup.sh
lunch Linux cfg_580_CARDV_EVB arm-ca9-linux-gnueabihf-6.5
```

---

## Key Directories

| Purpose | Path |
|---------|------|
| LVGL menu items (edit here) | `code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/` |
| LVGL menu ID / string / icon maps | `...UIFlowMenuCommonItem/MenuId.h` |
| SPORTCAM reference (read-only) | `code/application/source/cardv/SrcCode/UIWnd/SPORTCAM/UIMenu/` |
| MX200WGS LVGL reference (read-only) | `code/application/source/MX200WGS_cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/` |

---

## Adding a Missing Menu Item (Standard Pattern)

All 12 missing Movie items and all missing Setup items follow these same steps.

### Step 1 — Define options (in `MenuMovie.c` or `MenuSetup.c`)

```c
TMDEF_BEGIN_OPTIONS(PARKING_MODE)
    TMDEF_OPTION_TEXT_S(PARKING_MODE_OFF,    TM_OPTION_ENABLE)
    TMDEF_OPTION_TEXT_S(PARKING_MODE_ON_1FPS, TM_OPTION_ENABLE)
TMDEF_END_OPTIONS()
```

### Step 2 — Add item to the items block

```c
TMDEF_BEGIN_ITEMS(MOVIE)
    // ... existing items ...
    #if (PARKING_FUNC == ENABLE)
    TMDEF_ITEM_TEXTID(PARKING_MODE)
    #endif
TMDEF_END_ITEMS()
```

### Step 3 — Add callback case

```c
case IDM_PARKING_MODE:
    Ux_SendEvent(&UISetupObjCtrl, NVTEVT_EXE_PARKING_MODE, 1, uwOption);
    break;
```

### Step 4 — Verify `MenuId.h` entries exist

Check that `IDM_PARKING_MODE`, `IDM_PARKING_MODE_OFF`, `IDM_PARKING_MODE_ON_1FPS`,
`IDS_PARKING_MODE`, `IDI_PARKING_MODE`, and `IDF_PARKING_MODE` are all defined.
If any are missing, add them following the existing enum pattern in `MenuId.h`.

### Step 5 — Build and verify

```bash
make app 2>&1 | grep -E "error:|warning:.*LVGL_SPORTCAM"
```

Zero errors and zero warnings from `LVGL_SPORTCAM` sources = acceptance bar.

---

## Adding a Custom Screen Item (e.g., GPS Status)

```c
// 1. Static callback in MenuMovie.c
static int MenuCustom_GpsStatus(UINT32 uiMessage, UINT32 uiParam)
{
    (void)uiMessage;
    (void)uiParam;
    lv_plugin_scr_open(UIFlowWndGpsStatus, NULL);
    return TMF_PROCESSED;
}

// 2. Register in items block
TMDEF_ITEM_CUSTOM(GPS_STATUS1, MenuCustom_GpsStatus)

// No callback case needed — CUSTOM items are fully handled by the callback fn.
```

---

## Commit Convention

```
lvgl: add PARKING_MODE to Movie menu
lvgl: add GPS_STATUS1 custom screen to Movie menu
lvgl: add Setup menu parking sub-items (PARKING_GSENSOR, PARKING_MOTION_DET)
```

One logical unit per commit. Run `make app` before each commit.

---

## Style Check (newly written files only)

```bash
build/nvt-tools/nvt_check_cstyle.sh \
    code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/MenuMovie.c
```

Do **not** run the style checker on files copied verbatim from legacy trees.
