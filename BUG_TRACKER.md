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

### Open Issues / Known Limitations
- [ ] **Shift key**: Does not fully engage clutch (Shift + Space) under some configurations. Check if `Shift` needs to be kept pressed and whether SDL is correctly sending held state, or if the `Variation` (Left/Right) mapping needs further adjustments within Delta Studio.
- [ ] **Down Arrow key**: Downshifting may fail to register properly if the event isn't firing correctly in tandem with the clutch logic.
- [ ] **Fullscreen Toggle (F key)**: Updates status text but doesn't transition window natively. `SDL_SetWindowFullscreen` is called, but might require window recreation or resizing updates to apply via SDL3 video systems.
- [ ] **Enter key (Reload Script)**: May cause a segfault when `loadScript()` re-initializes the engine. Potentially related to the SDL3 audio backend failing to cleanly release resources, or Piranha script execution memory leaks.
