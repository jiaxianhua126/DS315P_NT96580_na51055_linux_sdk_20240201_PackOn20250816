# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **Novatek NA51055 Linux SDK** for a dash camera (CARDV) platform. It contains a complete embedded Linux system: bootloader (U-Boot), Linux kernel, BusyBox root filesystem, device drivers, shared libraries, and the CARDV application with an LVGL-based UI.

## Build Environment

Initialize before any build:
```bash
source build/envsetup.sh
lunch Linux cfg_580_CARDV_EVB arm-ca9-linux-gnueabihf-6.5
```

Key make targets:
```bash
make cfg        # generate DTB, ModelConfig.mk, verify config — run after any config change
make all        # full SDK build and image packing
make app        # build application packages only
make library    # build shared/static libraries only
make driver     # build driver modules only
make rootfs     # assemble target root filesystem
make pack       # package final firmware images
make clean      # clean all generated outputs
make listpackage # inspect app/library package names
```

C style checker (after sourcing the environment):
```bash
build/nvt-tools/nvt_check_cstyle.sh <path>
```

Component-local tests (run only when modifying those components):
```bash
# ASR library tests
code/lib/source/libASR/test/

# LVGL tests
code/lib/source/lvgl/lvgl/tests/
```

## Repository Structure

- **BSP/** — Board Support Package: `linux-kernel/`, `u-boot/`, `busybox/`, `root-fs/`
- **code/application/source/cardv/** — Main CARDV application (see below)
- **code/lib/source/** — Shared libraries (LVGL, OpenFileDB, Live555, libASR, etc.)
- **code/driver/source/** — Device drivers (Bluetooth, g-sensor, LCD, USB, network)
- **code/hdal/** — Novatek Hardware Abstraction Layer (HDAL)
- **code/vos/** — Novatek Virtual OS abstraction layer
- **configs/Linux/** — Board/product configuration variants (18+ configs: V70, Q80, NS2, EVB, etc.)
- **build/** — Build tooling: `envsetup.sh`, `definitions.mk`, `nvt-tools/`
- **output/** — Generated firmware images (`FWDS315P.bin`, `FW96580T.bin`, kernel, rootfs)
- **tools/** — Target-side utilities (gdb, htop, i2c-tools, iperf, memtester)

## CARDV Application Architecture

The application under `code/application/source/cardv/SrcCode/` is layered:

| Layer | Directory | Purpose |
|-------|-----------|---------|
| **Startup** | `Startup/` | ARM init, linker sections, binary info |
| **System** | `System/` | State machine, main loop, power/video/audio/storage management |
| **Device-specific** | `Dx/` | One subfolder per board variant (e.g., `Dx_580_CARDV_EVB/`) |
| **Generic hardware** | `Gx/` | Platform-agnostic hardware interface (display, input, power, storage, USB) |
| **HAL** | `HAL/` | Remote control (24G IR) |
| **UI Application** | `UIApp/` | Feature modules: `Movie/`, `Photo/`, `Play/`, `Setup/`, `Network/`, `Bluez/`, etc. |
| **UI Windows** | `UIWnd/LVGL_SPORTCAM/` | Active LVGL UI implementation |
| **LVGL drivers** | `lv_drivers/` | Display and input device drivers for LVGL |

`UIWnd/` also contains legacy implementations (`SPORTCAM/`, `SPORTCAM_TOUCH/`) and `ALEXA/` integration — `LVGL_SPORTCAM/` is the current active UI.

`PrjCfg*.h` headers at the `cardv/` root select features per product variant.

## Coding Style

- Follow the existing style per subsystem — do not reformat vendor code.
- Use tabs where the file already uses tabs; otherwise 4-space indentation.
- Preserve naming patterns: `Makefile`, `Source.mk`, `cfg_580_*` config folders, lowercase module dirs under `code/lib/source/` and `code/driver/source/`.

## Commit and PR Guidelines

- Short imperative commit subjects, scoped where useful (e.g., `lvgl: fix menu scroll bounds`).
- PRs must state the affected board/product config and list build targets run.
- Link any JIRA issue.
- Attach screenshots for UI changes under `cardv/` or LVGL code.

## Active Technologies
- C (embedded, arm-ca9-linux-gnueabihf-6.5 toolchain) + LVGL (code/lib/source/lvgl/), Novatek HDAL/VOS, TMDEF macro system (lvgl)
- Persistent device config via `FL_*` system flags, written through `Ux_SendEvent` (lvgl)

## Recent Changes
- lvgl: Added C (embedded, arm-ca9-linux-gnueabihf-6.5 toolchain) + LVGL (code/lib/source/lvgl/), Novatek HDAL/VOS, TMDEF macro system
