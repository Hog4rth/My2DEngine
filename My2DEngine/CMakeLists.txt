# CMakeLists.txt: CMake project for My2DEngine. Add source files and define
# project-specific logic here.
#

# Add the source files to this project's executable.
add_executable(My2DEngine "My2DEngine.cpp" "My2DEngine.h" "GameEngine.cpp" "GameEngine.h" ) # Inside the parentheses add files like (... "New.cpp" "New.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET My2DEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and, if necessary, install targets.

# ==========================================
# LINKING THE SDL3 AND SDL3_image LIBRARIES
# ==========================================

# 1. Tell the compiler where to find the .h include files used by the code
target_include_directories(My2DEngine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/include"
)

# 2. Tell the linker where to find the library (.lib) files for x64 architecture
target_link_directories(My2DEngine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/lib/x64"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/lib/x64"
)

# 3. Officially link the two libraries to our program
target_link_libraries(My2DEngine PRIVATE SDL3 SDL3_image)

# 4. THE KEY TRICK: Automatic copying of DLLs
# Copy the dynamic libraries (.dll) to the folder where the executable (.exe) is placed
add_custom_command(TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:My2DEngine>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/lib/x64/SDL3_image.dll"
        $<TARGET_FILE_DIR:My2DEngine>
)

# Instruct CMake: "Every time My2DEngine finishes building successfully,
# take the most recent Settings.ini and copy it next to the executable!"
add_custom_command(
    TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/Settings.ini"
    "$<TARGET_FILE_DIR:My2DEngine>"
)