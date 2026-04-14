# Feature Specification: LVGL Menu Parity with SPORTCAM

**Feature Branch**: `001-lvgl-menu-parity`  
**Created**: 2026-04-14  
**Status**: Draft  
**Input**: User description: "把 @code/application/source/cardv/SrcCode/UIWnd/SPORTCAM 移植为 @code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/，要保证 GUI 和逻辑功能一样，比如现在进入 LVGL 原始菜单，显示内容和 SPORTCAM 的不一致，没有分辨率等设置，要做成和 SPORTCAM 一样。LVGL 已经有一个完整的项目可以参考 code/application/source/MX200WGS_cardv/"

---

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Access Full Settings Menu (Priority: P1)

A user navigating the LVGL-based dash camera UI enters the Settings menu and expects to find the same configuration options available in the legacy SPORTCAM UI — including video resolution, recording codec, bitrate, parking mode, GPS settings, ADAS settings, and other advanced options currently absent from the LVGL menu.

**Why this priority**: The absence of core settings (e.g., video resolution) is immediately visible and blocks basic device configuration. This is the most user-impacting gap.

**Independent Test**: Navigate to the Settings/Movie menu in the LVGL UI on target hardware. Verify that all settings present in the SPORTCAM MenuMovie are reachable and functional.

**Acceptance Scenarios**:

1. **Given** the device is running the LVGL UI, **When** the user opens the Movie settings menu, **Then** all settings from SPORTCAM UIMenuMovie are present: Video Resolution, Cyclic Recording, HDR, WDR, Motion Detection, Audio Recording, Date Imprint, RSC, RSC Effect, G-Sensor, Time-lapse, IR Cut, Sensor Rotate, Urgent Protection, PIM, LDWS, FCW, DDD, ADAS Calibration, ADAS Menu, Dual Camera, Codec, Movie Bitrate, Video Format, IR Rear Color, Rear Sensor Mirror.
2. **Given** the user selects a setting (e.g., Video Resolution), **When** they choose a new value, **Then** the device applies the change and the new value is displayed correctly.
3. **Given** the LVGL UI is active, **When** the user enters a sub-menu (e.g., ADAS Menu), **Then** all ADAS sub-items (LDWS, FCW, SNG, PCW, RCW, LCAWS, Virtual Bumper) are present and selectable.

---

### User Story 2 - Access Full Setup Menu (Priority: P2)

A user navigating Setup settings expects to find all system configuration options from SPORTCAM, including GPS, Speed Unit, GPS Stamp, Model Stamp, Boot Delay, LED, Format Warning, Parking Mode, Parking G-Sensor, Parking Motion Detection, Shutdown Timer, Enter Parking Timer, Ambiance Light, and E-Dog Mode.

**Why this priority**: Setup settings affect global device behavior. Missing items prevent users from configuring GPS logging, parking mode, LED behavior, and other essential functions.

**Independent Test**: Navigate to Setup menu in LVGL UI. Verify every item present in SPORTCAM UIMenuSetup is accessible and functional.

**Acceptance Scenarios**:

1. **Given** the LVGL UI is active, **When** the user enters the Setup menu, **Then** all settings from SPORTCAM UIMenuSetup are present: Auto Power Off, Beep, Volume, Language, EV, TV Mode, Frequency, Screen Saver, GPS, Time Zone, Speed Unit, LED, Format Warning, WiFi, Boot Delay, GPS Stamp, Model Stamp, Parking Mode, Parking G-Sensor, Parking Motion Detection, Shutdown Timer, Enter Parking Timer, Ambiance Light, E-Dog Mode, Format, Default Settings, Version.
2. **Given** the user toggles Parking Mode, **When** they return to the Setup menu, **Then** the updated state is shown correctly.
3. **Given** GPS is enabled, **When** the user enters the GPS status screen, **Then** current GPS data (satellite count, speed, etc.) is displayed as in SPORTCAM.

---

### User Story 3 - Consistent Menu Visual Layout (Priority: P3)

When navigating the LVGL menu, the visual grouping, ordering, and naming of all menu items should match the SPORTCAM UI so that users familiar with the legacy UI can orient themselves immediately.

**Why this priority**: Functional parity is more critical; visual consistency improves usability but does not block feature usage.

**Independent Test**: Side-by-side comparison of SPORTCAM menu screenshots vs LVGL menu screenshots. All items in same category, same order.

**Acceptance Scenarios**:

1. **Given** both UIs are available, **When** navigating the Movie menu, **Then** items appear in the same logical order as in SPORTCAM.
2. **Given** the user navigates a sub-menu like ADAS, **When** they see the list, **Then** the grouping (LDWS, FCW, SNG, PCW, RCW, LCAWS, Virtual Bumper) matches SPORTCAM exactly.

---

### Edge Cases

- What happens when a setting is conditionally visible (e.g., LDWS only shows when GPS is enabled)? The LVGL implementation must replicate the same visibility conditions as SPORTCAM.
- What happens when the target hardware lacks a feature (e.g., no rear camera)? Items dependent on unavailable hardware must be hidden or shown as disabled, same as SPORTCAM behavior.
- What happens when a setting value set via LVGL is read back by another system component? Values must use the same data representations as SPORTCAM.
- What if SPORTCAM and MX200WGS LVGL implementations differ for the same menu item? The SPORTCAM definition is authoritative; MX200WGS LVGL is used only as a reference for LVGL coding patterns.

---

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: The LVGL_SPORTCAM menu system MUST expose all menu items currently present in SPORTCAM UIMenuMovie, UIMenuPhoto, UIMenuSetup, UIMenuPlay, UIMenuUSB, and UIMenuWiFi.
- **FR-002**: Each menu item in LVGL_SPORTCAM MUST invoke the same underlying system action (function call, state change, or configuration write) as its counterpart in SPORTCAM.
- **FR-003**: The LVGL_SPORTCAM menu MUST include the following currently missing Movie items: LDWS, FCW, DDD, ADAS Menu (with all sub-items), Movie Bitrate, Video Format, IR Rear Color, Rear Sensor Mirror.
- **FR-004**: The LVGL_SPORTCAM menu MUST include the following currently missing Setup items: GPS, Speed Unit, GPS Stamp, Model Stamp, Boot Delay, LED, Format Warning, Parking Mode, Parking G-Sensor, Parking Motion Detection, Shutdown Timer, Enter Parking Timer, Ambiance Light, E-Dog Mode.
- **FR-005**: Conditional visibility rules (feature flags, hardware capability checks) MUST be ported identically from SPORTCAM so items appear or hide under the same conditions.
- **FR-006**: The MX200WGS_cardv LVGL_SPORTCAM implementation MUST be used as the coding reference for LVGL widget patterns, event callbacks, and screen definitions; any menu items already implemented there for similar settings should be reused or adapted.
- **FR-007**: String labels for all menu items and options MUST match SPORTCAM's LanguageTable entries (or the LVGL LanguageTable.csv equivalent), preserving all supported languages.
- **FR-008**: The Photo menu in LVGL_SPORTCAM MUST match SPORTCAM UIMenuPhoto in terms of available settings and options.
- **FR-009**: The Playback, USB, and WiFi menus in LVGL_SPORTCAM MUST match SPORTCAM UIMenuPlay, UIMenuUSB, and UIMenuWiFi respectively.
- **FR-010**: After each setting change made through the LVGL menu, the displayed current value MUST immediately refresh to reflect the new selection.

### Key Entities

- **Menu Item**: A configurable setting exposed to the user; has an ID, label, list of options, current value, and a handler that applies the change.
- **Menu Option**: A single selectable value for a Menu Item; has a display string, an internal enum/integer value, and optional visibility condition.
- **UIFlow Screen**: An LVGL screen definition (`.lvglscr`) and its associated C logic file pair that renders and handles a menu category.
- **LanguageTable**: The CSV/header mapping menu labels and option strings to all supported locales.
- **Feature Flag / Condition**: A compile-time or runtime condition that determines whether a Menu Item is visible (e.g., `ADAS_FUNC`, `GPS_FUNCTION`, hardware detect).

---

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: 100% of menu items present in SPORTCAM's Movie, Photo, Setup, Play, USB, and WiFi menus are reachable through the LVGL_SPORTCAM UI.
- **SC-002**: Every setting change made via the LVGL menu produces the identical system state change as the same action performed through the SPORTCAM menu, with zero functional regressions on settings that already work.
- **SC-003**: A user already familiar with the SPORTCAM menu can locate any setting in the LVGL menu within the same number of navigation steps.
- **SC-004**: All conditional visibility rules are preserved — no setting appears for hardware/features it should not apply to, and no setting is hidden when it should be available.
- **SC-005**: All menu item strings are correctly localized in all languages previously supported by SPORTCAM.

---

## Assumptions

- The LVGL framework version in use (`code/lib/source/lvgl/`) is compatible with the patterns used in MX200WGS_cardv's LVGL_SPORTCAM; no LVGL API migration is required.
- Feature flags controlling ADAS, GPS, Parking Mode, etc. are already present in the build configuration for the `cfg_580_CARDV_EVB` target; only the UI layer needs updating.
- The SPORTCAM menu definitions in `UIWnd/SPORTCAM/` are the authoritative source of truth for which items should exist and what values they take.
- The MX200WGS_cardv LVGL implementation is a valid coding reference for LVGL screen/event patterns but is not required to be a drop-in replacement — adaptation per the cardv codebase structure is expected.
- Out of scope: Adding any new settings not already present in SPORTCAM; changing the visual design/theme beyond what is needed to render the ported items; modifying non-menu UI flows (recording, playback, WiFi streaming).
- The target board for validation is `cfg_580_CARDV_EVB` unless otherwise specified.
