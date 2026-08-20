# CMakeLists.txt: CMake project for My2DEngine.

# ==========================================
# DEFINING THE PROJECT AND ITS SOURCES
# ==========================================
add_executable(My2DEngine 
    "My2DEngine.h" 
    "My2DEngine.cpp" 
    "GameEngine.h" 
    "GameEngine.cpp" 
    "Components.h" 
    "MovementSystem.h" 
    "MovementSystem.cpp" 
    "FileManager.h"
    "FileManager.cpp" 
    "RenderSystem.h" 
    "RenderSystem.cpp"
    "InputManager.h"
    "InputManager.cpp"
    "CollisionSystem.h"
    "CollisionSystem.cpp" "PhysicsSystem.h" "PhysicsSystem.cpp") 

# Set C++ standard to C++20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET My2DEngine PROPERTY CXX_STANDARD 20)
endif()

# ==========================================
# FETCHCONTENT: DOWNLOAD & AUTOMATIC BUILD
# ==========================================
include(FetchContent)

# Download & automatic build SDL3 library
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.12
)
FetchContent_MakeAvailable(SDL3)

# Download & automatic build SDL3_image library
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.4.4
)
FetchContent_MakeAvailable(SDL3_image)

# ==========================================
# LINKING THE LIBRARIES TO THE ENGINE
# ==========================================
target_link_libraries(My2DEngine PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# ==========================================
# POST-BUILD COMMANDS
# ==========================================
# Copy all .dll files (SDL3, SDL3_image) next to the executable
add_custom_command(
    TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:My2DEngine>
    $<TARGET_FILE_DIR:My2DEngine>
    COMMAND_EXPAND_LISTS
)

# Copy the Settings.ini file to the output directory of the executable
add_custom_command(
    TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/Settings.ini"
    "$<TARGET_FILE_DIR:My2DEngine>"
)

