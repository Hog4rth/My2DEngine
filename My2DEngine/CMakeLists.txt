# CMakeLists.txt: CMake project for My2DEngine.

# ==========================================
# DEFINING THE PROJECT AND ITS SOURCES
# ==========================================
add_library(EngineCore STATIC  
    "GameEngine.h" "GameEngine.cpp" 
    "Components.h" 
    "MovementSystem.h" "MovementSystem.cpp" 
    "FileManager.h" "FileManager.cpp" 
    "RenderSystem.h" "RenderSystem.cpp"
    "InputSystem.h" "InputSystem.cpp"
    "CollisionSystem.h" "CollisionSystem.cpp"
	"PhysicsSystem.h" "PhysicsSystem.cpp") 

add_executable(My2DEngine "My2DEngine.cpp" )

# Set C++ standard to C++20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EngineCore PROPERTY CXX_STANDARD 20)
  set_property(TARGET My2DEngine PROPERTY CXX_STANDARD 20)
endif()

# ==========================================
# CODE COVERAGE (GCC/Clang/MSVC)
# ==========================================
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)
add_library(CoverageFlags INTERFACE)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(CoverageFlags INTERFACE --coverage -O0 -g)
        if(COMMAND target_link_options)
            target_link_options(CoverageFlags INTERFACE --coverage)
        else()
            target_link_libraries(CoverageFlags INTERFACE --coverage)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        # Visual Studio Native Code Coverage requires the /PROFILE linker flag
        if(COMMAND target_link_options)
            target_link_options(CoverageFlags INTERFACE /PROFILE)
        else()
            target_link_libraries(CoverageFlags INTERFACE /PROFILE)
        endif()
    endif()
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

set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF" FORCE)

FetchContent_MakeAvailable(SDL3_image)

# ==========================================
# LINKING THE LIBRARIES TO THE ENGINE
# ==========================================
target_link_libraries(EngineCore PUBLIC SDL3::SDL3 SDL3_image::SDL3_image CoverageFlags)
target_link_libraries(My2DEngine PRIVATE EngineCore)

# ==========================================
# UNIT TESTING (Google Test)
# ==========================================
enable_testing()

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Create and link a separate executable strictly for running tests
add_executable(EngineTests "tests/FileManagerTest.cpp" "tests/CollisionSystemTest.cpp" "tests/InputSystemTest.cpp" "tests/MovementSystemTest.cpp")
target_link_libraries(EngineTests PRIVATE EngineCore GTest::gtest_main)
set_property(TARGET EngineTests PROPERTY CXX_STANDARD 20)

# ==========================================
# POST-BUILD COMMANDS
# ==========================================
# Copy all .dll files (GTest) next to the executable
add_custom_command(
    TARGET EngineTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:EngineTests>
    $<TARGET_FILE_DIR:EngineTests>
    COMMAND_EXPAND_LISTS
)
include(GoogleTest)
add_test(NAME test_example COMMAND EngineTests)

# Copy all .dll files (SDL3, SDL3_image) next to the executable
add_custom_command(
    TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:My2DEngine>
    $<TARGET_FILE_DIR:My2DEngine>
    COMMAND_EXPAND_LISTS
)
