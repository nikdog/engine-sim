# Engine Simulator (Agentic Engineered Fork)
![Alt text](docs/public/screenshots/screenshot_v01.png?raw=true)

---
> **Disclaimer:** This repository is an **Agentic Engineered Fork** of the original Engine Simulator created by [Ange Yaghi (AngeTheGreat)](https://github.com/ange-yaghi/engine-sim). This version has been modernized to run natively on Linux and other platforms via a complete **SDL3 cross-platform conversion**.
> 
> All credit for the underlying engine physics, thermodynamics, and audio synthesis models goes to Ange Yaghi and the open-source community. If you are looking for the original Windows binary releases, please refer to the [original repository](https://github.com/ange-yaghi/engine-sim).
---

## What is this?
This is a real-time internal combustion engine simulation **designed specifically to produce engine audio and simulate engine response characteristics.** It is NOT a scientific tool and cannot be expected to provide accurate figures for the purposes of engineering or engine tuning.

## Changelog: SDL3 Cross-Platform Migration
This fork implements a massive architectural overhaul to decouple the engine simulator from proprietary Windows APIs (specifically DirectSound8) and modernize the build system.
- **SDL3 Migration:** Converted all window management, input polling, and audio streaming to use the SDL3 API.
- **Audio Subsystem Overhaul:** Created custom native `ysSdlAudioSystem`, `ysSdlAudioDevice`, `ysSdlAudioSource`, and `ysSdlAudioBuffer` classes to handle circular buffer continuous audio streaming via `SDL_AudioStream`.
- **Buffer Overflow Fixes:** Corrected severe C++ memory corruption errors involving audio buffer synchronization units (samples vs bytes).
- **Build System:** Rewrote `CMakeLists.txt` for `delta-studio`, `simple-2d-constraint-solver`, and `engine-sim` to properly link SDL3, OpenGL, and standard C++ libraries.
- **Key Mappings:** Mapped SDL3 scan codes natively to the custom `delta-studio` key configurations.

## How do I use it?
The UI is extremely minimalistic and there are only a few controls used to interact with the engine:

| Key/Input | Action |
| :---: | :---: |
| A | Toggle ignition |
| S | Hold for starter |
| D | Enable dyno |
| H | Enable RPM hold (see below for instructions) |
| G + Scroll | Change hold speed |
| F | Enter fullscreen mode |
| I | Display dyno stats in the information panel |
| Shift | Clutch (hold spacebar at the same time to slowly engage/disengage) |
| Up Arrow | Up Gear | 
| Down Arrow | Down Gear | 
| Z + Scroll | Volume |
| X + Scroll | Convolution Level |
| C + Scroll | High frequency gain |
| V + Scroll | Low frequency noise |
| B + Scroll | High frequency noise |
| N + Scroll | Simulation frequency |
| M | Increase view layer |
| , | Decrease view layer |
| Enter | Reload engine script |
| Escape | Exit the program |
| Q, W, E, R | Change throttle position |
| Space + Scroll | Fine throttle adjustment |
| 1, 2, 3, 4, 5 | Simulation time warp |
| Tab | Change screen |

### Using the RPM hold
The RPM hold feature will hold the engine at a specific RPM and also measure the engine's horsepower and torque at that RPM. You can enable RPM hold by pressing the `H` key. **You must then enable the dynomometer** (press the `D` key) in order for the RPM hold to take effect. To change the hold speed, hold the `G` key and scroll with the mouse wheel. The RPM hold will be shown on the `DYNO. SPEED` gauge in the lower left of the screen.

## How do I build it?
### Step 1 - Clone the repository
```bash
git clone --recurse-submodules https://github.com/nikdog/engine-sim
```

### Step 2 - Install Dependencies
You will need to install the following dependencies on your system:
- **SDL3** (development headers)
- **Boost**
- **Flex and Bison**
- **CMake**

### Step 3 - Build and Run
From the root directory of the project, run the following commands to configure an optimized release build:

```bash
mkdir build-release
cd build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

Run the application:
```bash
./engine-sim-app
```

## Acknowledgements

The original engine physics, thermodynamics modeling, and baseline architecture were created by [Ange Yaghi](https://github.com/ange-yaghi).

The original project was made possible by the generous donations of Ange's Patreon supporters. For a full list of the original supporters who funded the foundational engine development, please see the [original repository](https://github.com/ange-yaghi/engine-sim).
