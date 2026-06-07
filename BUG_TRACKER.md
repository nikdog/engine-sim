# Engine Simulator (Agentic Fork) - Bug Tracker

### Resolved Bugs
- [x] **Missing Linux Audio**
  - **Issue**: Complete lack of audio backend after removing legacy Windows DirectSound8.
  - **Fix**: Implemented native `ysSdlAudioSystem`, `ysSdlAudioDevice`, `ysSdlAudioBuffer`, and `ysSdlAudioSource` using SDL3. Hooked up continuous stream polling with `ysAudioSource::Mode::Loop` compatibility.
- [x] **Buffer Overflow & Segfaults during Engine Loop**
  - **Issue**: Random segmentation faults, double-free crashes, and assertions like `malloc.c:4241 (_int_malloc)` while running.
  - **Fix**: Corrected initialization of the circular audio buffer in `ysSdlAudioDevice::CreateSource()`. It was improperly setting the underlying `ysAudioSource::m_bufferSize` to the memory size in *bytes* instead of *samples*, causing `LockBufferSegment()` to allow boundary violations and `memcpy` heap corruptions.
- [x] **Severely Degraded Framerate (9-12 FPS)**
  - **Issue**: App ran incredibly slow out of the box on Linux.
  - **Fix**: The default `CMakeLists.txt` build configuration defaults to `Debug` without optimizations (`-O0`). Rerouting through `-DCMAKE_BUILD_TYPE=Release` utilizes `-O3` and stabilizes performance to 60+ FPS.
- [x] **Compilation Errors (Shadowed Members & Missing Standard Libraries)**
  - **Issue**: G++ aggressively flagged `delta-studio` physics components with `-Werror=changes-meaning` and missing `<limits>` header definitions.
  - **Fix**: Addressed standard library includes, and set `-fpermissive` alongside disabling specific legacy warnings to allow the Delta Studio submodule to cleanly compile cross-platform.
- [x] **Missing Input Maps**
  - **Issue**: `Shift`, `Down`, `<, >, -, =` and other application-specific keys were unresponsive on SDL.
  - **Fix**: Mapped `SDL_SCANCODE` equivalents into `ysSdlKeyMaps` to properly invoke view layer controls and engine functions.
- [x] **Startup UI Segmentation Faults**
  - **Issue**: Crash immediately after loading `main.mr`.
  - **Fix**: Added null-guard bounds checking in `load_simulation_cluster.cpp` to verify `m_simulator` isn't accessed uninitialized by the rendering thread.

- [x] **Shift key**
  - **Issue**: Did not fully engage clutch (Shift + Space) under some configurations.
  - **Fix**: Adjusted SDL held state logic and mapping properly.
- [x] **Down Arrow key**
  - **Issue**: Downshifting failed to register properly.
  - **Fix**: Corrected the event firing properly in tandem with the clutch logic.
- [x] **Enter key (Reload Script)**
  - **Issue**: Caused a segfault when `loadScript()` re-initialized the engine.
  - **Fix**: Handled SDL3 resource releases and Piranha execution to prevent memory leaks during script reloads.

### Open Issues / Known Limitations
- [ ] **Fullscreen Toggle (F key)**: F now actually toggles fullscreen, but the UI doesn't scale correctly when toggling. `SDL_SetWindowFullscreen` is applying but might require window recreation or manual UI resizing updates.
