# CMakeList.txt: progetto CMake per My2DEngine. Includere l'origine e definire
# qui la logica specifica del progetto.
#

# Aggiungere l'origine all'eseguibile di questo progetto.
add_executable(My2DEngine "My2DEngine.cpp" "My2DEngine.h" "GameEngine.cpp" "GameEngine.h" "Components.h" "MovementSystem.cpp" "MovementSystem.h" ) # Dentro le parentesi in caso si aggiunge (... "New.cpp" "New.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET My2DEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Aggiungere i test e, se necessario, installare le destinazioni.

# ==========================================
# COLLEGAMENTO DEL MOTORE SDL3 E SDL3_IMAGE
# ==========================================

# 1. Diciamo al compilatore dove trovare i file .h da includere nel codice
target_include_directories(My2DEngine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/include"
)

# 2. Diciamo al linker dove trovare i file di libreria (.lib) per architettura 64 bit
target_link_directories(My2DEngine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/lib/x64"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/lib/x64"
)

# 3. Colleghiamo ufficialmente le due librerie al nostro programma
target_link_libraries(My2DEngine PRIVATE SDL3 SDL3_image)

# 4. IL TRUCCO FONDAMENTALE: Copia automatica delle DLL
# Copia le librerie dinamiche (.dll) nella cartella dove nasce l'eseguibile (.exe)
add_custom_command(TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:My2DEngine>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_image/lib/x64/SDL3_image.dll"
        $<TARGET_FILE_DIR:My2DEngine>
)

# Ordiniamo a CMake: "Ogni volta che finisci di compilare My2DEngine con successo,
# prendi la versione più recente di settings.ini e copiala di fianco all'eseguibile!"
add_custom_command(
    TARGET My2DEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/Settings.ini"
    "$<TARGET_FILE_DIR:My2DEngine>"
)