---
description: "Task list for LVGL Menu Parity with SPORTCAM feature implementation"
---

# Tasks: LVGL Menu Parity with SPORTCAM

**Input**: Design documents from `/specs/001-lvgl-menu-parity/`
**Prerequisites**: plan.md, spec.md, research.md, data-model.md, quickstart.md

**Tests**: Not requested in specification - implementation and build verification only

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions

## Path Conventions

All paths relative to repository root: `/home/e/Code/Haotek/DS315P/na51055_linux_sdk_20240201_PackOn20250816/`

Primary working directory: `code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/`

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Build environment initialization and reference material preparation

- [X] T001 Source build environment: `source build/envsetup.sh && lunch Linux cfg_580_CARDV_EVB arm-ca9-linux-gnueabihf-6.5`
- [X] T002 Verify baseline build: `make app` with zero errors in LVGL_SPORTCAM sources
- [X] T003 [P] Read SPORTCAM reference MenuMovie.c at code/application/source/cardv/SrcCode/UIWnd/SPORTCAM/UIMenu/MenuMovie.c
- [X] T004 [P] Read MX200WGS LVGL reference at code/application/source/MX200WGS_cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/MenuMovie.c (N/A - does not exist in this repo)

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented

**⚠️ CRITICAL**: No user story work can begin until this phase is complete

- [X] T005 Read current LVGL MenuId.h at code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/MenuId.h
- [X] T006 Read current LVGL MenuMovie.c at code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/MenuMovie.c
- [X] T007 Read current LVGL MenuSetup.c at code/application/source/cardv/SrcCode/UIWnd/LVGL_SPORTCAM/UIFlowLVGL/UIFlowMenuCommonItem/MenuSetup.c
- [X] T008 Create side-by-side diff of SPORTCAM vs LVGL MenuMovie.c to identify all missing items
- [X] T009 Create side-by-side diff of SPORTCAM vs LVGL MenuSetup.c to identify all missing items

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - Access Full Settings Menu (Priority: P1) 🎯 MVP

**Goal**: Port all missing Movie menu items from SPORTCAM to LVGL so users can access video resolution, ADAS, parking mode, GPS, and other critical recording settings

**Independent Test**: Navigate to Movie settings menu in LVGL UI on target hardware. Verify all settings from SPORTCAM MenuMovie are present and functional. Run `make app` with zero errors/warnings in LVGL_SPORTCAM sources.

### Implementation for User Story 1 - Movie Menu Standard Items

- [X] T010 [P] [US1] Add MOVIE_ADAS options and item to MenuMovie.c with `#if (ADAS_FUNC == ENABLE)` guard
- [X] T011 [P] [US1] Add PARKING_MODE options and item to MenuMovie.c with `#if (PARKING_FUNC == ENABLE)` guard
- [X] T012 [P] [US1] Add REAR_SENSOR_MIRROR options and item to MenuMovie.c with `#if (DUAL_CAM == ENABLE)` guard
- [X] T013 [P] [US1] Add SPEED_UNIT options and item to MenuMovie.c with `#if (GPS_FUNCTION == ENABLE)` guard
- [X] T014 [P] [US1] Add GPS_STAMP options and item to MenuMovie.c with `#if (GPS_FUNCTION == ENABLE)` guard
- [X] T015 [P] [US1] Add TIME_ZONE options and item to MenuMovie.c with `#if (GPS_FUNCTION == ENABLE)` guard
- [X] T016 [P] [US1] Add FORMAT_WARNING options and item to MenuMovie.c (always visible)
- [X] T017 [P] [US1] Add VOLUME options and item to MenuMovie.c (always visible)
- [X] T018 [P] [US1] Add ASR options and item to MenuMovie.c with `#if (ASR_FUNC == ENABLE)` guard
- [X] T019 [P] [US1] Add ASR_CONTENT options and item to MenuMovie.c with `#if (ASR_FUNC == ENABLE)` guard
- [X] T020 [US1] Add callback cases for all 10 standard Movie items in MenuMovie.c switch statement
- [X] T021 [US1] Verify all IDM_*, IDS_*, IDI_*, IDF_* entries exist in MenuId.h for Movie items, add any missing
- [X] T022 [US1] Build verification: `make app` with zero errors/warnings in LVGL_SPORTCAM

### Implementation for User Story 1 - Movie Menu Custom Screen Items

- [X] T023 [US1] Add MOVIE_ADAS_CORDON custom screen handler with lv_plugin_scr_open in MenuMovie.c
- [X] T024 [US1] Add GPS_STATUS1 custom screen handler with lv_plugin_scr_open in MenuMovie.c
- [X] T025 [US1] Register MOVIE_ADAS_CORDON and GPS_STATUS1 as TMDEF_ITEM_CUSTOM in MenuMovie.c items block
- [X] T026 [US1] Build verification: `make app` with zero errors/warnings in LVGL_SPORTCAM

**Checkpoint**: At this point, User Story 1 should be fully functional - all Movie menu items from SPORTCAM are present in LVGL

---

## Phase 4: User Story 2 - Access Full Setup Menu (Priority: P2)

**Goal**: Port all missing Setup menu items from SPORTCAM to LVGL so users can configure GPS, parking mode, LED, format warnings, and other system-level settings

**Independent Test**: Navigate to Setup menu in LVGL UI on target hardware. Verify all settings from SPORTCAM MenuSetup are present and functional. Run `make app` with zero errors/warnings.

### Implementation for User Story 2 - Setup Menu Items

- [ ] T027 [P] [US2] Add GPS enable/disable options and item to MenuSetup.c with `#if (GPS_FUNCTION == ENABLE)` guard
- [ ] T028 [P] [US2] Add PARKING_GSENSOR options and item to MenuSetup.c with `#if (PARKING_FUNC == ENABLE)` guard
- [ ] T029 [P] [US2] Add PARKING_MOTION_DET options and item to MenuSetup.c with `#if (PARKING_FUNC == ENABLE)` guard
- [ ] T030 [P] [US2] Add SHUTDOWN_TIMER options and item to MenuSetup.c with `#if (PARKING_FUNC == ENABLE)` guard
- [ ] T031 [P] [US2] Add ENTER_PARKING_TIMER options and item to MenuSetup.c with `#if (PARKING_FUNC == ENABLE)` guard
- [ ] T032 [P] [US2] Add LED options and item to MenuSetup.c (verify visibility condition from SPORTCAM)
- [ ] T033 [P] [US2] Add BOOT_DELAY options and item to MenuSetup.c (always visible)
- [ ] T034 [P] [US2] Add MODEL_STAMP options and item to MenuSetup.c (always visible)
- [ ] T035 [P] [US2] Add AMBIANCE_LIGHT options and item to MenuSetup.c with `#if (AMBIANCE_LIGHT_FUNC == ENABLE)` guard
- [ ] T036 [P] [US2] Add EDOG_MODE options and item to MenuSetup.c with `#if (EDOG_FUNC == ENABLE)` guard
- [ ] T037 [US2] Add callback cases for all Setup items in MenuSetup.c switch statement
- [ ] T038 [US2] Verify all IDM_*, IDS_*, IDI_*, IDF_* entries exist in MenuId.h for Setup items, add any missing
- [ ] T039 [US2] Build verification: `make app` with zero errors/warnings in LVGL_SPORTCAM

**Checkpoint**: At this point, User Stories 1 AND 2 should both work independently - all Movie and Setup menu items are complete

---

## Phase 5: User Story 3 - Consistent Menu Visual Layout (Priority: P3)

**Goal**: Ensure menu item ordering, grouping, and naming match SPORTCAM exactly so users familiar with legacy UI can navigate immediately

**Independent Test**: Side-by-side comparison of SPORTCAM menu screenshots vs LVGL menu screenshots. All items in same category, same order.

### Implementation for User Story 3 - Menu Ordering and Grouping

- [ ] T040 [US3] Verify Movie menu item order in MenuMovie.c TMDEF_BEGIN_ITEMS block matches SPORTCAM MenuMovie.c order
- [ ] T041 [US3] Verify Setup menu item order in MenuSetup.c TMDEF_BEGIN_ITEMS block matches SPORTCAM MenuSetup.c order
- [ ] T042 [US3] Verify ADAS sub-menu items (LDWS, FCW, SNG, PCW, RCW, LCAWS, Virtual Bumper) are grouped correctly
- [ ] T043 [US3] Verify parking-related items are grouped together in Setup menu
- [ ] T044 [US3] Build verification: `make app` with zero errors/warnings in LVGL_SPORTCAM

**Checkpoint**: All user stories should now be independently functional - Movie and Setup menus have full parity with SPORTCAM

---

## Phase 6: Polish & Cross-Cutting Concerns

**Purpose**: Improvements that affect multiple user stories and final validation

- [ ] T045 [P] Audit MenuPhoto.c against SPORTCAM UIMenuPhoto, identify and add any missing items
- [ ] T046 [P] Audit MenuPlayback.c against SPORTCAM UIMenuPlay, identify and add any missing items
- [ ] T047 [P] Audit MenuMode.c (USB/WiFi) against SPORTCAM UIMenuUSB/UIMenuWiFi, identify and add any missing items
- [ ] T048 Verify all new IDS_* entries have corresponding strings in LanguageTable.csv for all supported languages
- [ ] T049 Verify all new IDI_* entries have corresponding icons in Resource/ directory
- [ ] T050 Full clean build: `make clean && make all` with zero errors/warnings
- [ ] T051 On-device validation: Boot target hardware, navigate all Movie/Setup menus, verify all items appear and respond
- [ ] T052 Run style checker on any newly created files: `build/nvt-tools/nvt_check_cstyle.sh <path>`
- [ ] T053 Run quickstart.md validation: Follow all steps in quickstart.md to verify documentation accuracy

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: No dependencies - can start immediately
- **Foundational (Phase 2)**: Depends on Setup completion - BLOCKS all user stories
- **User Stories (Phase 3-5)**: All depend on Foundational phase completion
  - User Story 1 (Movie menu): Can start after Foundational - No dependencies on other stories
  - User Story 2 (Setup menu): Can start after Foundational - No dependencies on other stories
  - User Story 3 (Visual layout): Depends on US1 and US2 completion
- **Polish (Phase 6)**: Depends on all user stories being complete

### User Story Dependencies

- **User Story 1 (P1)**: Can start after Foundational (Phase 2) - No dependencies on other stories
- **User Story 2 (P2)**: Can start after Foundational (Phase 2) - No dependencies on other stories (independent from US1)
- **User Story 3 (P3)**: Depends on US1 and US2 completion - verifies ordering and grouping

### Within Each User Story

- **User Story 1**: Standard items (T010-T022) can be done in parallel, then custom items (T023-T026)
- **User Story 2**: All Setup items (T027-T039) can be done in parallel
- **User Story 3**: Ordering verification tasks (T040-T044) must be done sequentially after US1 and US2

### Parallel Opportunities

- All Setup tasks (T001-T004) can run in parallel
- All Foundational read tasks (T005-T007) can run in parallel
- All Movie menu standard items (T010-T019) can be added in parallel - different option blocks in same file
- All Setup menu items (T027-T036) can be added in parallel - different option blocks in same file
- Photo/Play/USB audits (T045-T047) can run in parallel
- String/icon verification (T048-T049) can run in parallel

---

## Parallel Example: User Story 1 - Movie Menu Standard Items

```bash
# Launch all Movie menu standard item additions together:
Task: "Add MOVIE_ADAS options and item to MenuMovie.c"
Task: "Add PARKING_MODE options and item to MenuMovie.c"
Task: "Add REAR_SENSOR_MIRROR options and item to MenuMovie.c"
Task: "Add SPEED_UNIT options and item to MenuMovie.c"
Task: "Add GPS_STAMP options and item to MenuMovie.c"
Task: "Add TIME_ZONE options and item to MenuMovie.c"
Task: "Add FORMAT_WARNING options and item to MenuMovie.c"
Task: "Add VOLUME options and item to MenuMovie.c"
Task: "Add ASR options and item to MenuMovie.c"
Task: "Add ASR_CONTENT options and item to MenuMovie.c"

# Then add all callback cases together (T020)
# Then verify MenuId.h completeness (T021)
# Then build (T022)
```

---

## Parallel Example: User Story 2 - Setup Menu Items

```bash
# Launch all Setup menu item additions together:
Task: "Add GPS enable/disable options and item to MenuSetup.c"
Task: "Add PARKING_GSENSOR options and item to MenuSetup.c"
Task: "Add PARKING_MOTION_DET options and item to MenuSetup.c"
Task: "Add SHUTDOWN_TIMER options and item to MenuSetup.c"
Task: "Add ENTER_PARKING_TIMER options and item to MenuSetup.c"
Task: "Add LED options and item to MenuSetup.c"
Task: "Add BOOT_DELAY options and item to MenuSetup.c"
Task: "Add MODEL_STAMP options and item to MenuSetup.c"
Task: "Add AMBIANCE_LIGHT options and item to MenuSetup.c"
Task: "Add EDOG_MODE options and item to MenuSetup.c"

# Then add all callback cases together (T037)
# Then verify MenuId.h completeness (T038)
# Then build (T039)
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. Complete Phase 1: Setup
2. Complete Phase 2: Foundational (CRITICAL - blocks all stories)
3. Complete Phase 3: User Story 1 (Movie menu)
4. **STOP and VALIDATE**: Test Movie menu on device, verify all items functional
5. Deploy/demo if ready

### Incremental Delivery

1. Complete Setup + Foundational → Foundation ready
2. Add User Story 1 (Movie menu) → Test independently → Deploy/Demo (MVP!)
3. Add User Story 2 (Setup menu) → Test independently → Deploy/Demo
4. Add User Story 3 (Visual layout) → Test independently → Deploy/Demo
5. Each story adds value without breaking previous stories

### Parallel Team Strategy

With multiple developers:

1. Team completes Setup + Foundational together
2. Once Foundational is done:
   - Developer A: User Story 1 (Movie menu)
   - Developer B: User Story 2 (Setup menu)
3. Developer C: User Story 3 (Visual layout) after A and B complete
4. Stories complete and integrate independently

---

## Notes

- [P] tasks = different option blocks in same file or different files, no dependencies
- [Story] label maps task to specific user story for traceability
- Each user story should be independently completable and testable
- Commit after each logical group of items (e.g., all GPS-related items, all parking items)
- Stop at any checkpoint to validate story independently on target hardware
- All `#if` visibility guards must be copied verbatim from SPORTCAM to preserve feature flag behavior
- No new `.c` files expected - all changes are edits to existing MenuMovie.c, MenuSetup.c, MenuId.h
- If any new `.c` file is created, update Source.mk in the same directory before building
- Build acceptance bar: `make app` with zero errors and zero warnings from LVGL_SPORTCAM sources
