# Data Model: LVGL Menu Parity with SPORTCAM

**Feature**: `specs/001-lvgl-menu-parity`  
**Date**: 2026-04-14

---

## Core Entities

### MenuItemDef

Represents one row in a menu category (Movie, Setup, Photo, Play, USB, WiFi).

| Field | Type | Description |
|-------|------|-------------|
| `id` | `MENU_ID` enum | Unique item identifier (e.g., `IDM_PARKING_MODE`) |
| `type` | `TEXTID \| CUSTOM` | TEXTID = driven by options list; CUSTOM = opens a screen or runs logic |
| `options` | `MenuOptionDef[]` | Ordered list of selectable values (TEXTID items only) |
| `callback` | function pointer | Invoked when user confirms a selection |
| `visibility_flag` | compile-time `#if` or runtime check | Condition under which item appears |

### MenuOptionDef

One selectable value within a `MenuItemDef`.

| Field | Type | Description |
|-------|------|-------------|
| `value_id` | `MENU_ID` enum | Enum value passed to callback (e.g., `IDM_PARKING_MODE_OFF`) |
| `string_id` | `MENU_IDS` enum | Display string reference (maps to `LV_PLUGIN_STRING_ID_STRID_*`) |
| `state` | `TM_OPTION_ENABLE \| TM_OPTION_NOT_SUPPORT` | Whether option is selectable |

### MenuCategory

A named group of `MenuItemDef` entries rendered on one menu screen.

| Category | Source file | Corresponding LVGL screen |
|----------|-------------|--------------------------|
| Movie | `MenuMovie.c` | `UIFlowWndMovie` |
| Setup | `MenuSetup.c` | `UIFlowWndSetup` (or merged in Movie screen — verify) |
| Photo | `MenuPhoto.c` | `UIFlowWndPhoto` |
| Playback | `MenuPlayback.c` | `UIFlowWndPlay` |
| USB | `MenuMode.c` | `UIFlowWndUSB` |
| WiFi | `MenuMode.c` / WiFi screen | `UIFlowWndMovieWiFi` |

---

## ID Mapping Entities

These are static lookup tables in `MenuId.h`:

### _MENU_ID (enum)
Maps logical item/option names → integer discriminators used throughout the menu system.

### _MENU_IDS (enum)
Maps `IDM_*` → `LV_PLUGIN_STRING_ID_STRID_*` so the LVGL plugin can resolve display strings from the language table.

### _MENU_IDI (enum)
Maps `IDM_*` → `LV_PLUGIN_IMG_ID_ICON_*` for sidebar icons.

### _MENU_IDF (enum)
Maps `IDM_*` → `FL_*` system flag constants used by event handlers to update device state.

---

## State Transitions

A menu item selection triggers this flow:

```
User selects option
    → TMDEF callback in Menu*.c
        → case IDM_ITEM: Ux_SendEvent(&ControlObj, NVTEVT_EXE_*, 1, uwOption)
            → UIApp event handler (e.g., UISetupObjCtrl, CustomMovieObjCtrl)
                → writes persistent config / activates hardware
                    → menu redraws with updated current value
```

For CUSTOM items (GPS status, ADAS calibration, etc.):
```
User selects item
    → TMDEF callback → MenuCustom_Xxx()
        → lv_plugin_scr_open(UIFlowXxxScreen, NULL)
            → dedicated LVGL screen opens
                → user exits screen → returns to menu
```

---

## Visibility Conditions (Feature Flags)

Items that appear/hide based on build-time or runtime conditions. These must be preserved exactly as in SPORTCAM:

| Item | Condition |
|------|-----------|
| `MOVIE_ADAS`, `MOVIE_ADAS_CORDON` | `#if (ADAS_FUNC == ENABLE)` |
| `GPS_STAMP`, `GPS_STATUS1` | `#if (GPS_FUNCTION == ENABLE)` |
| `SPEED_UNIT` | `#if (GPS_FUNCTION == ENABLE)` |
| `REAR_SENSOR_MIRROR` | `#if (DUAL_CAM == ENABLE)` or rear-cam detect |
| `ASR`, `ASR_CONTENT` | `#if (ASR_FUNC == ENABLE)` |
| `PARKING_MODE` and sub-items | `#if (PARKING_FUNC == ENABLE)` |
| `AMBIANCE_LIGHT` | `#if (AMBIANCE_LIGHT_FUNC == ENABLE)` |
| `EDOG_MODE` | `#if (EDOG_FUNC == ENABLE)` |

**Source of truth**: SPORTCAM `MenuMovie.c` and `MenuSetup.c` `#if` guards — copy them verbatim.
