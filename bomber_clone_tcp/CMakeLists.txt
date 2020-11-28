
cmake_minimum_required(VERSION 3.8)

project(bomber_clone_tcp CXX)
set(CMAKE_CXX_STANDARD 17)

message("platform: ${CMAKE_GENERATOR_PLATFORM}")

add_library(sdl2 SHARED IMPORTED)
target_include_directories(sdl2 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/SDL2-2.0.5/include
)
set(sdl2_dll "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.5/lib/x64/SDL2.dll")
set_target_properties(sdl2 PROPERTIES
    IMPORTED_LOCATION "${sdl2_dll}"
    IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.5/lib/x64/SDL2.lib"
)

add_library(sdl2main STATIC IMPORTED)
# Include dirs are shared with sdl2 so no further includes required
set_target_properties(sdl2main PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/SDL2-2.0.5/lib/x64/SDL2main.lib"
)
# All libs that need sdl2main also need sdl2
target_link_libraries(sdl2main INTERFACE sdl2)

add_library(sdl2net SHARED IMPORTED GLOBAL)
target_include_directories(sdl2net INTERFACE
    ${CMAKE_SOURCE_DIR}/external/SDL2_net-2.0.1/include
)
set(sdl2net_dll "${CMAKE_SOURCE_DIR}/external/SDL2_net-2.0.1/lib/x64/SDL2_net.dll")
set_target_properties(sdl2net PROPERTIES
    IMPORTED_LOCATION "${sdl2net_dll}"
    IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/external/SDL2_net-2.0.1/lib/x64/SDL2_net.lib"
)
# All libs that need sdl2net also need sdl2
target_link_libraries(sdl2net INTERFACE sdl2)

add_library(gameplay STATIC)
target_include_directories(gameplay PUBLIC ${CMAKE_SOURCE_DIRECTORY}/src/gameplay)
target_sources(gameplay PRIVATE
    ${CMAKE_SOURCE_DIR}/src/gameplay/array2d.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/game_io.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/game_play.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/game_sim.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/game_state.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/game_state_io.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/global_state.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/level_grid.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/local_state.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/player.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/tile.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/unit.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/unit_manager.cpp
)

add_library(network STATIC)
target_include_directories(network PUBLIC ${CMAKE_SOURCE_DIR}/src/network/)
target_sources(network PRIVATE
     ${CMAKE_SOURCE_DIR}/src/network/address.cpp
     ${CMAKE_SOURCE_DIR}/src/network/net_shared.cpp
)
target_link_libraries(network PUBLIC sdl2 sdl2net)

add_library(custom STATIC)
target_include_directories(custom PUBLIC ${CMAKE_SOURCE_DIR}/src/custom)
target_sources(custom PRIVATE
     ${CMAKE_SOURCE_DIR}/src/custom/color_debug.cpp
)

add_executable(bomber_clone_client ${CMAKE_SOURCE_DIR}/src/client/bomber_clone_client.cpp)
target_include_directories(bomber_clone_client PRIVATE ${CMAKE_SOURCE_DIR}/src/client)
target_link_libraries(bomber_clone_client gameplay custom network sdl2main user32 advapi32 winmm)
set_target_properties(bomber_clone_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

add_custom_command(TARGET bomber_clone_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2_dll}" $<TARGET_FILE_DIR:bomber_clone_client>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2net_dll}" $<TARGET_FILE_DIR:bomber_clone_client>
)
