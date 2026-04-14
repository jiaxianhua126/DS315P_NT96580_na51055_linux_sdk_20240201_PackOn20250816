# Implementation Plan: LVGL Menu Parity with SPORTCAM

**Branch**: `lvgl` (spec: `001-lvgl-menu-parity`) | **Date**: 2026-04-14 | **Spec**: [spec.md](spec.md)  
**Input**: Feature specification from `specs/001-lvgl-menu-parity/spec.md`

## Summary

Port all menu items present in `UIWnd/SPORTCAM/UIMenu/` (Movie, Setup, Photo, Play, USB, WiFi) into `UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/` using the existing `TMDEF_*` macro system. No new screens are required for standard items — only option definitions, item registrations, callback cases, and `MenuId.h` mapping entries. Custom-screen items (GPS status, ADAS calibration) require `lv_plugin_scr_open()` wrappers. Visibility `#if` guards from SPORTCAM are copied verbatim.

---

## Technical Context

**Language/Version**: C (embedded, arm-ca9-linux-gnueabihf-6.5 toolchain)  
**Primary Dependencies**: LVGL (code/lib/source/lvgl/), Novatek HDAL/VOS, TMDEF macro system  
**Storage**: Persistent device config via `FL_*` system flags, written through `Ux_SendEvent`  
**Testing**: Build verification (`make app` zero errors/warnings in LVGL_SPORTCAM sources) + on-device UI walkthrough  
**Target Platform**: Novatek NA51055, board config `cfg_580_CARDV_EVB`  
**Project Type**: Embedded UI feature port  
**Performance Goals**: No frame-rate regression; menu open/close must remain within existing timing  
**Constraints**: Constitution Principles I–V (source isolation, LVGL-native, no legacy modification, style preservation, Source.mk registration)  
**Scale/Scope**: ~12 Movie menu items + ~10–15 Setup menu items + Photo/Play/USB/WiFi audit

---

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

| Principle | Status | Notes |
|-----------|--------|-------|
| I. Source Isolation | ✅ PASS | All changes are inside `LVGL_SPORTCAM`. SPORTCAM files are read-only references. |
| II. LVGL-Native | ✅ PASS | Only `TMDEF_*` macros and `lv_plugin_scr_open()` are used. No legacy `Ux_OpenWindow()`. |
| III. Existing Code Preservation | ✅ PASS | `SPORTCAM/`, `MX200WGS/` directories are not modified. |
| IV. Vendor Style Preservation | ✅ PASS | `Menu*.c` files are edited in-place, preserving existing formatting. Style checker only on new files. |
| V. Build System Consistency | ✅ PASS | `Source.mk` updated whenever a new `.c` file is added (no new files expected for this task — only edits to existing `Menu*.c` and `MenuId.h`). |

*Post-design re-check*: No architectural changes introduced. All principles remain satisfied.

---

## Project Structure

### Documentation (this feature)

```text
specs/001-lvgl-menu-parity/
├── plan.md              # This file
├── spec.md              # Feature specification
├── research.md          # Phase 0 research
├── data-model.md        # Phase 1 data model
├── quickstart.md        # Phase 1 developer quickstart
├── checklists/
│   └── requirements.md  # Spec quality checklist
└── tasks.md             # Phase 2 output (/speckit.tasks — NOT created by /speckit.plan)
```

### Source Code (files to modify)

```text
code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/
└── UIFlowLVGL/
    └── UIFlowMenuCommonItem/
        ├── MenuId.h          ← Add missing IDS/IDI/IDF enum entries (if any)
        ├── MenuMovie.c       ← Add missing Movie menu options, items, callbacks
        ├── MenuSetup.c       ← Add missing Setup menu options, items, callbacks
        ├── MenuPhoto.c       ← Audit + add missing Photo items (lower priority)
        ├── MenuPlayback.c    ← Audit + add missing Playback items (lower priority)
        └── (TabMenu.c, MenuMode.c — audit only, likely no changes needed)
```

**No new `.c` files are expected.** All changes are edits to existing files. If a new `.c` is ever required (e.g., a new custom screen), `Source.mk` in the same directory must be updated.

---

## Implementation Phases

### Phase A: Movie Menu — Standard Items

**Files**: `MenuMovie.c`, `MenuId.h`  
**Items to add** (12 items, in priority order):

| # | Item ID | Type | Visibility Guard | Backend Event |
|---|---------|------|-----------------|---------------|
| 1 | `MOVIE_ADAS` | TEXTID | `#if (ADAS_FUNC == ENABLE)` | `NVTEVT_EXE_MOVIE_ADAS` |
| 2 | `PARKING_MODE` | TEXTID | `#if (PARKING_FUNC == ENABLE)` | `NVTEVT_EXE_PARKING_MODE` |
| 3 | `REAR_SENSOR_MIRROR` | TEXTID | `#if (DUAL_CAM == ENABLE)` | `NVTEVT_EXE_REAR_SENSOR_MIRROR` |
| 4 | `SPEED_UNIT` | TEXTID | `#if (GPS_FUNCTION == ENABLE)` | `NVTEVT_EXE_SPEED_UNIT` |
| 5 | `GPS_STAMP` | TEXTID | `#if (GPS_FUNCTION == ENABLE)` | `NVTEVT_EXE_GPS_STAMP` |
| 6 | `TIME_ZONE` | TEXTID | `#if (GPS_FUNCTION == ENABLE)` | `NVTEVT_EXE_TIME_ZONE` |
| 7 | `FORMAT_WARNING` | TEXTID | always | `NVTEVT_EXE_FORMAT_WARNING` |
| 8 | `VOLUME` | TEXTID | always | `NVTEVT_EXE_VOLUME` |
| 9 | `ASR` | TEXTID | `#if (ASR_FUNC == ENABLE)` | `NVTEVT_EXE_ASR` |
| 10 | `ASR_CONTENT` | TEXTID | `#if (ASR_FUNC == ENABLE)` | `NVTEVT_EXE_ASR_CONTENT` |

**Process for each item**:
1. Read SPORTCAM `MenuMovie.c` to extract exact option values and `#if` guards.
2. Verify `IDM_*`, `IDS_*`, `IDI_*`, `IDF_*` exist in `MenuId.h`; add any missing entries.
3. Add `TMDEF_BEGIN_OPTIONS` / `TMDEF_END_OPTIONS` block in LVGL `MenuMovie.c`.
4. Add `TMDEF_ITEM_TEXTID` inside `TMDEF_BEGIN_ITEMS(MOVIE)` with same `#if` guard.
5. Add `case IDM_*: Ux_SendEvent(...); break;` in the callback.
6. Run `make app`; verify zero errors/warnings in `LVGL_SPORTCAM`.

### Phase B: Movie Menu — Custom Screen Items

**Files**: `MenuMovie.c`  
**Items to add** (2 items):

| # | Item ID | Custom Screen | Trigger |
|---|---------|--------------|---------|
| 1 | `MOVIE_ADAS_CORDON` | ADAS calibration screen | `#if (ADAS_FUNC == ENABLE)` |
| 2 | `GPS_STATUS1` | GPS status screen | `#if (GPS_FUNCTION == ENABLE)` |

**Process for each item**:
1. Verify the target LVGL screen (`UIFlowWndAdasCal`, `UIFlowWndGpsStatus`) exists or check MX200WGS for reference.
2. Add `static int MenuCustom_Xxx(...)` with `lv_plugin_scr_open()`.
3. Add `TMDEF_ITEM_CUSTOM(ID, MenuCustom_Xxx)` to items block.
4. Run `make app`.

### Phase C: Setup Menu Full Audit + Port

**Files**: `MenuSetup.c`, `MenuId.h`  
**Process**:
1. Open SPORTCAM `MenuSetup.c` and LVGL `MenuSetup.c` side-by-side.
2. Produce a definitive diff of missing items.
3. For each missing item, follow the same 6-step process as Phase A.
4. Confirmed candidates from spec FR-004: `GPS`, `PARKING_GSENSOR`, `PARKING_MOTION_DET`, `SHUTDOWN_TIMER`, `ENTER_PARKING_TIMER`, `LED`, `BOOT_DELAY`, `MODEL_STAMP`, `AMBIANCE_LIGHT`, `EDOG_MODE`.

### Phase D: Photo / Play / USB / WiFi Menus Audit

**Files**: `MenuPhoto.c`, `MenuPlayback.c`, `MenuMode.c`  
**Process**: Same audit-then-port pattern. Lower priority; do after A–C are complete and validated.

### Phase E: String / Icon Completeness Check

**Files**: `MenuId.h`, `LanguageTable.csv`  
After all items are wired:
1. Verify every new `IDS_*` entry has a corresponding string in `LanguageTable.csv` for all supported languages.
2. Verify every new `IDI_*` entry has a corresponding icon in `Resource/`.
3. Run `make app` again on a fully clean build.

---

## Complexity Tracking

No constitution violations. No complexity justification required.
