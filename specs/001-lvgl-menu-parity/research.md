# Research: LVGL Menu Parity with SPORTCAM

**Feature**: `specs/001-lvgl-menu-parity`  
**Date**: 2026-04-14

---

## Decision 1: Menu Item Definition Pattern

**Decision**: Use the existing `TMDEF_*` macro system already used in `UIFlowMenuCommonItem/MenuMovie.c`.

**Rationale**: All existing LVGL menu items use this pattern. The macros abstract the underlying LVGL plugin string/icon ID lookups. The pattern is consistent with MX200WGS_cardv's LVGL implementation.

**Pattern (6 steps to add one item)**:
1. Add `TMDEF_BEGIN_OPTIONS(ITEM_NAME)` / `TMDEF_OPTION_TEXT_S(...)` / `TMDEF_END_OPTIONS()` block in the relevant `Menu*.c`
2. Verify `IDM_ITEM_NAME` exists in `MenuId.h` enum `_MENU_ID` (most already defined)
3. Verify string ID mapping `IDS_ITEM_NAME = LV_PLUGIN_STRING_ID_STRID_*` in `MenuId.h` enum `_MENU_IDS`
4. Verify icon ID mapping in `MenuId.h` enum `_MENU_IDI`
5. Add `TMDEF_ITEM_TEXTID(ITEM_NAME)` inside the `TMDEF_BEGIN_ITEMS(MOVIE|SETUP|...)` block
6. Add `case IDM_ITEM_NAME: Ux_SendEvent(...); break;` in the menu callback switch

**Alternatives considered**:
- Direct LVGL widget code without macros: rejected — violates existing style, harder to maintain.

---

## Decision 2: Which Items Are Missing

Cross-reference of SPORTCAM `MenuMovie.c` vs LVGL `MenuMovie.c`:

### Movie Menu — Missing Items (need to add to LVGL)

| ID | Notes |
|----|-------|
| `MOVIE_ADAS` | ADAS settings textid item |
| `MOVIE_ADAS_CORDON` | ADAS calibration — custom handler → `lv_plugin_scr_open` |
| `PARKING_MODE` | Parking mode selection |
| `REAR_SENSOR_MIRROR` | Rear camera mirror flag |
| `SPEED_UNIT` | km/h vs mph |
| `GPS_STAMP` | GPS coordinate on-screen stamp |
| `TIME_ZONE` | Time zone selection |
| `GPS_STATUS1` | Custom GPS status screen |
| `FORMAT_WARNING` | SD format threshold warning |
| `ASR` | Voice recognition toggle |
| `ASR_CONTENT` | ASR command set selection |
| `VOLUME` | Audio playback volume |

**Note**: `MOVIE_VOICE` appears in both lists — already present in LVGL, not missing.

### Setup Menu — Items requiring audit

A full `MenuSetup.c` diff was not done in this research pass. Based on the spec's FR-004 and SPORTCAM `MenuSetup.c`, the following are confirmed as requiring audit/addition:

| Category | Suspected missing IDs |
|----------|----------------------|
| GPS | `GPS_STATUS1` (may be in Movie or Setup), `GPS` enable/disable |
| Parking | `PARKING_GSENSOR`, `PARKING_MOTION_DET`, `SHUTDOWN_TIMER`, `ENTER_PARKING_TIMER` |
| Hardware | `LED`, `BOOT_DELAY`, `AMBIANCE_LIGHT` |
| Stamping | `MODEL_STAMP` |
| ADAS UI | `MOVIE_ADAS` sub-menu items (LDWS, FCW, SNG, PCW, RCW, LCAWS, Virtual Bumper) |
| E-Dog | `EDOG_MODE` |

**Action**: During implementation, read `MenuSetup.c` in both SPORTCAM and LVGL side-by-side to produce the definitive per-item diff before coding.

---

## Decision 3: Custom Screen Handlers

**Decision**: For items with custom screens (GPS status, ADAS calibration, DateTime, WiFi, Format), use `lv_plugin_scr_open(UIFlowXxx, NULL)` — the same pattern used in existing LVGL custom items.

**Rationale**: MX200WGS LVGL implementation uses identical pattern. SPORTCAM uses `Ux_OpenWindow()` which is a legacy non-LVGL call and must NOT be copied directly.

**Translation table**:
```
SPORTCAM                          → LVGL_SPORTCAM
Ux_OpenWindow(&UIMenuWndXxx, ...)  → lv_plugin_scr_open(UIFlowXxx, NULL)
STRID_*                            → LV_PLUGIN_STRING_ID_STRID_*
IDI_*                              → LV_PLUGIN_IMG_ID_ICON_*
```

---

## Decision 4: MenuId.h Completeness

**Decision**: Most `IDM_*`, `IDS_*`, `IDF_*`, `IDI_*` entries for the missing items are already defined in `MenuId.h` (the file is 1230 lines). No new enum values need to be added for standard items — only wiring them into the `Menu*.c` option/item lists and callbacks is required.

**Exceptions**: ADAS sub-menu items (LDWS, FCW, SNG, PCW, RCW, LCAWS, Virtual Bumper) need verification against `MenuId.h` before assuming they exist.

**Alternatives considered**: Adding new IDs from scratch — unnecessary if they already exist; premature if not confirmed.

---

## Decision 5: Build Registration

**Decision**: Every new `.c` file added must be listed in `Source.mk` in the same directory. No glob patterns.

**Rationale**: Constitution Principle V. The existing `Source.mk` in `UIFlowMenuCommonItem/` lists each file explicitly.

**Action**: After each new file addition, update `Source.mk` in the same directory before verifying with `make app`.

---

## Decision 6: Scope of Photo / Play / USB / WiFi Menus

**Decision**: Defer Photo, Play, USB, and WiFi menu audits to separate tasks after Movie and Setup menus are complete. These menus have fewer expected gaps and can be verified independently.

**Rationale**: The user-reported discrepancy is specifically about Movie/Setup (resolution, ADAS, parking). Starting there delivers highest value first (FR-001 priority ordering).

---

## Resolved Clarifications

All spec `[NEEDS CLARIFICATION]` markers were already absent. No open questions remain.
