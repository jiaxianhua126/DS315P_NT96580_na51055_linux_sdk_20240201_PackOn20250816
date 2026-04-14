<!--
SYNC IMPACT REPORT
==================
Version change: N/A (initial fill) → 1.0.0
Modified principles: N/A (first ratification)
Added sections:
  - Core Principles (5 principles)
  - Source Isolation Policy
  - Development Workflow
  - Governance

Templates requiring updates:
  - .specify/templates/plan-template.md ✅ Compatible — Constitution Check gates apply
  - .specify/templates/spec-template.md ✅ Compatible — no new mandatory sections
  - .specify/templates/tasks-template.md ✅ Compatible — task types align with principles
  - No command files found under .specify/templates/commands/

Follow-up TODOs:
  - TODO(RATIFICATION_DATE): Use 2026-04-14 as project-start date (SDK checked in prior to this).
    Confirm with team if a formal earlier date should be used.
-->

# NA51055 CARDV LVGL UI Constitution

## Core Principles

### I. Source Isolation (NON-NEGOTIABLE)

The `LVGL_SPORTCAM` UI implementation MUST be fully self-contained.
It MUST NOT `#include` or otherwise reference source files from `SPORTCAM`,
`SPORTCAM_TOUCH`, `MX200WGS`, or any other legacy UI directory.
If logic from those directories is required, it MUST be copied into
`LVGL_SPORTCAM` and maintained independently.

**Rationale**: Cross-directory `#include` paths create hidden coupling that
breaks build reproducibility when the legacy trees are eventually removed and
makes it impossible to reason about which UI variant is active at compile time.

### II. LVGL-Native Implementation

All UI screens, widgets, and layout logic inside `LVGL_SPORTCAM` MUST be
implemented using LVGL APIs (`lv_obj_*`, `lv_style_*`, `lv_plugin_*`, etc.).
Non-LVGL rendering primitives from legacy display layers MUST NOT be introduced.

**Rationale**: Mixing rendering paradigms produces visual artifacts and prevents
the LVGL style/theme system from working correctly across the full screen tree.

### III. Existing Code Preservation

Legacy UI directories (`SPORTCAM`, `SPORTCAM_TOUCH`, `MX200WGS`, `ALEXA`) MUST
NOT be modified when porting features to `LVGL_SPORTCAM`. They remain the
authoritative source for any board variant that still targets them.

**Rationale**: Other product configs (non-EVB board variants) may still compile
against the legacy trees. Silent modification of shared code is a regression risk.

### IV. Vendor Code Style Preservation

When copying files from a legacy source tree into `LVGL_SPORTCAM`, the original
file formatting and naming conventions MUST be preserved. No reformatting,
renaming, or style normalization passes are permitted on copied files unless the
change is directly required by the port.

**Rationale**: Gratuitous reformatting obscures the true diff between the
original and the ported version, making future rebases and bug comparisons
difficult. This follows the project-wide rule in CLAUDE.md: "do not reformat
vendor code."

### V. Build System Consistency

Every new `.c` source file added to `LVGL_SPORTCAM` MUST be listed in the
corresponding `Source.mk` (or equivalent `Makefile` fragment) within the same
directory. Object files (`.o`) MUST NOT be committed. Generated/intermediate
build outputs are covered by `.gitignore`.

**Rationale**: Uncommitted `Source.mk` entries produce silent link failures that
only surface on clean builds, not incremental ones. The SDK uses explicit
`Source.mk` enumeration — glob patterns are not used.

## Source Isolation Policy

The following cross-directory `#include` patterns are explicitly **prohibited**:

```c
// PROHIBITED — any of these in LVGL_SPORTCAM sources:
#include "UIWnd/SPORTCAM/..."
#include "UIWnd/SPORTCAM_TOUCH/..."
#include "UIWnd/MX200WGS/..."
#include "../SPORTCAM/..."
```

Permitted include roots for `LVGL_SPORTCAM` sources:

- Headers within `UIWnd/LVGL_SPORTCAM/` itself
- SDK-wide shared headers under `SrcCode/` (e.g., `System/`, `UIApp/`, `Gx/`)
- LVGL library headers from `code/lib/source/lvgl/`
- Platform headers from `code/hdal/` and `code/vos/`

When a helper (e.g., `MenuCommon.c`, `UIInfo.c`) is needed from a legacy tree,
the procedure is:

1. Copy the file into the appropriate subdirectory of `LVGL_SPORTCAM`.
2. Update `#include` paths inside the copy to resolve from the new location.
3. Do **not** modify the original file in the legacy tree.

## Development Workflow

- **Build verification**: After any port task, run `make app` (after sourcing
  `build/envsetup.sh` with `lunch Linux cfg_580_CARDV_EVB arm-ca9-linux-gnueabihf-6.5`).
  A clean `make app` with zero warnings in `LVGL_SPORTCAM` sources is the
  minimum acceptance bar.
- **Style check**: Run `build/nvt-tools/nvt_check_cstyle.sh` on any newly
  written (not copied) `.c`/`.h` files in `LVGL_SPORTCAM`.
- **Commit scope**: Each commit MUST target a single logical unit (one screen
  ported, one menu wired, one helper copied). Commit subjects follow
  `lvgl: <imperative verb> <what>` (e.g., `lvgl: port UIFlowWndPlay to LVGL`).
- **PR requirements**: State the board/product config, list `make` targets run,
  and attach a screenshot for any visible UI change. Link any related JIRA issue.
- **Reference implementation**: `code/application/source/MX200WGS` may be
  consulted as a reference for patterns (e.g., how a menu callback is wired)
  but MUST NOT be modified and MUST NOT be `#include`d from `LVGL_SPORTCAM`.

## Governance

This constitution supersedes any informal conventions previously applied to
`UIWnd/LVGL_SPORTCAM`. Amendments require:

1. A written rationale in the PR description.
2. Update to this file with an incremented version and `Last Amended` date.
3. A sync impact review: check whether `plan-template.md`, `spec-template.md`,
   and `tasks-template.md` require corresponding updates.

**Versioning policy** (semantic):
- MAJOR — removes or redefines an existing principle in a backward-incompatible way.
- MINOR — adds a new principle, section, or materially expands guidance.
- PATCH — clarifications, wording fixes, non-semantic refinements.

All PRs and code reviews for `UIWnd/LVGL_SPORTCAM` MUST verify compliance with
Principles I–V above before approval.

**Version**: 1.0.0 | **Ratified**: 2026-04-14 | **Last Amended**: 2026-04-14
