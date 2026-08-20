# My2DEngine 🎮

Welcome to **My2DEngine**, a custom 2D Game Engine built entirely from scratch using **C++** and **SDL3**. 

## 🎯 Project Ambition & Goals
This project was born primarily as a hands-on learning experience. The main goal is to deeply understand and master **C++** programming by tackling one of the most complex software architectures: a Game Engine. 

Rather than relying on pre-built commercial engines (like Unity or Unreal), this project aims to build the core systems from the ground up. The ultimate goal is to evolve this project into a lightweight, fully functional **Data-Driven 2D Engine** capable of powering fast-paced, highly responsive games (such as precision platformers with tight physics and kinematics).

### Core Architecture Focus:
*   **Entity-Component-System (ECS):** Separating data from logic for a clean, scalable architecture.
*   **Data-Driven Design:** Moving hardcoded values out of the codebase and into configuration files (like `Settings.ini` and future level files).
*   **Custom Physics & Kinematics:** Implementing organic movement systems featuring acceleration, friction, and velocity clamping.

---

## 🚧 Developer Notes: Code Conventions

As this is a continuous learning process, the codebase is constantly evolving. 
If you are reading the source code, please note the following conventions:

*   `// ** [comment] **` 
    Any comment enclosed between double asterisks highlights a **temporary section**, a workaround, or a piece of code that is guaranteed to be refactored and updated in the future. It acts as a customized "Work In Progress" or "TODO" tag.

---

## 🛠️ Tech Stack & Build
*   **Language:** C++
*   **Graphics & Windowing:** SDL3
*   **Build System:** CMake

### How to Build (CMake)
This project uses CMake for cross-platform compilation. To build the engine, generate the build files using CMake and compile through your preferred IDE (like Visual Studio) or via the command line:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```