# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

WellStudio (XStudio) is a geology/geosteering desktop application written in C++ with Qt and OpenSceneGraph. It is a Visual Studio 2017 solution (`WellStudio.sln`) targeting **x64** (an x86 config exists but x64 is the real target). UI code is Qt 5.13.2 via the Qt VS Tools add-in (`.ui` files, moc/uic generated into each project's `GeneratedFiles/`).

## Build

Build with VS2017 or MSBuild; set platform to `x64`, Debug or Release:

```sh
msbuild WellStudio.sln /p:Configuration=Release /p:Platform=x64
```

Build one project (with its solution dependencies) via its target name:

```sh
msbuild WellStudio.sln /t:xgui /p:Configuration=Release /p:Platform=x64
```

Prerequisites (see README.md):
- Qt 5.13.2 (msvc2017_64), registered in Qt VS Tools (Qt Options)
- Third-party OSG and LAPACK builds. System environment variables must be set:
  - `LAPACK`, `OSG_INCLUDE`, `OSG_LIB` pointing into the 3rdparty archive
  - `PATH` must include `%LAPACK%\bin` and the OSG `bin` directory (next to `OSG_LIB`) for runtime DLLs

The solution contains 18 projects; **XStudio** is its only executable. Everything else is a DLL or static library, so a build of XStudio transitively builds the whole stack. **XLicense** (license tool, depends only on xbasic) has a `.vcxproj` in its directory but is **not in the solution** — build it separately with `msbuild XLicense\XLicense.vcxproj`. `TMInversion/` and `TMProj/` are stale leftovers (only `.vcxproj.user` + build output), not projects.

There is no test framework in this repository.

## Architecture

Layered dependency chain (bottom → top), documented per-module in `Documents/迁移日志.md`:

```
xbasic  xdata  xdataplus  xgeomodel  xalgorithm
   └→ xbasicui → xgui → xguiplus
                    xgraphicview (depends only on xgui's xscene, xdata, xbasic)
   viewer DLLs: xlogview, xcrossplot, xhistogramplot, xsectionwindow,
                x3dwindow (heaviest deps), xbasemapwindow (depends on x3dwindow)
   gsviewer (static lib, geological-stress views built on xbasemapwindow)
   └→ xconsole (ties together nearly everything) → XStudio
```

- **xbasic**: math/geometry foundation — interpolation, matrices, octree/kdtree, axes, logging, license-check stubs. Depends on Qt Core only in spirit; per the migration log it should not, but does.
- **xdata**: domain data model. Files use the `gs*` prefix (geosteering/geological-stress model: horizons, faults, sections, rose diagrams, stress maps, grids). Note: xdata contains UI code despite being a data layer — a known coupling problem.
- **xdataplus**: numerical methods wrapping MKL/LAPACK; mixes C-style APIs with STL.
- **xgui / xguiplus**: the largest widget module set. `xscene` in xgui is the central 3D/2D scene abstraction that xgraphicview and the viewer windows build on.
- **Viewer projects** (`xlogview`, `xcrossplot`, `xhistogramplot`, `xsectionwindow`, `x3dwindow`, `xbasemapwindow`, `gsviewer`): each is a self-contained window type (log curves, cross plots, histograms, 2D sections, 3D, base map) registered into the app via **xconsole**'s `xwindowmanager` / `xmaintreewidget` tree console.
- **XStudio**: main window, data loaders (`mainloader`), licensing (`aes256`, `simple_license`), resource data (`.tdb`, `.dic`, `.pal`, `.xmt` templates).
- `shader/` holds GLSL (`surface.vert/frag`, `section.vert/frag`) loaded at runtime; `fonts/`, `Icon/` are assets.

Naming convention: `x*` = generic framework classes, `gs*` = geological-stress/geosteering domain classes. Each DLL project has an `*_global.h` with the export macro.

## Known pitfalls (from 迁移日志.md)

- `xbasic/xmathmacro.h` and `xbasic/xglobal.h` are widely-included "poison" headers (macro math + global function grab-bag) — avoid expanding them; prefer templates/splitting when refactoring.
- Warning levels can't be raised in xbasic without a flood of warnings; xdataplus's MKL interop generates many warnings by design.
- The dependency graph is not clean (xdata pulls Qt UI; xgeomodel uses OSG vectors) — respect existing includes rather than "fixing" layering casually.
