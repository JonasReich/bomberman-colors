
cmake_minimum_required(VERSION 3.8)

project(bomber_clone_tcp CXX)

message("platform: ${CMAKE_GENERATOR_PLATFORM}")

add_subdirectory(external)

add_library(gameplay STATIC)
target_include_directories(gameplay PUBLIC ${CMAKE_SOURCE_DIR}/src/gameplay/public)
target_sources(gameplay PRIVATE
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/color_debug.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/game_io.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/game_sim.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/game_state.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/game_state_io.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/global_state.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/level_grid.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/player.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/unit.cpp
    ${CMAKE_SOURCE_DIR}/src/gameplay/private/unit_manager.cpp
)

add_library(network STATIC)
target_include_directories(network PUBLIC ${CMAKE_SOURCE_DIR}/src/network/public)
target_sources(network PRIVATE
     ${CMAKE_SOURCE_DIR}/src/network/private/address.cpp
     ${CMAKE_SOURCE_DIR}/src/network/private/net_shared.cpp
)
target_link_libraries(network PUBLIC external::sdl2net)

# Client Application
add_executable(bomber_clone_client ${CMAKE_SOURCE_DIR}/src/client/bomber_clone_client.cpp)
target_include_directories(bomber_clone_client PUBLIC ${CMAKE_SOURCE_DIR}/src/client)
target_link_libraries(bomber_clone_client gameplay network external::sdl2main user32 advapi32 winmm)
set_target_properties(bomber_clone_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/client
)

# Uncomment this to enforce certain compiler features like c++17 standard
# target_compile_features(bomber_clone_client PRIVATE cxx_std_17)

# Host Application
add_executable(bomber_clone_server)
target_include_directories(bomber_clone_server PUBLIC ${CMAKE_SOURCE_DIR}/src/client)
target_sources(bomber_clone_server PRIVATE
    ${CMAKE_SOURCE_DIR}/src/server/bomber_clone_server.cpp
)
target_link_libraries(bomber_clone_server gameplay network external::sdl2main user32 advapi32 winmm)
set_target_properties(bomber_clone_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/server
)

add_custom_command(TARGET bomber_clone_client POST_BUILD
    # Copy dlls for client
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2_dll}" $<TARGET_FILE_DIR:bomber_clone_client>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2net_dll}" $<TARGET_FILE_DIR:bomber_clone_client>

    # Copy dlls for server
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2_dll}" $<TARGET_FILE_DIR:bomber_clone_server>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${sdl2net_dll}" $<TARGET_FILE_DIR:bomber_clone_server>
)

if(MSVC)
    target_compile_options(bomber_clone_client PRIVATE /W4)
    target_compile_options(bomber_clone_server PRIVATE /W4)
endif()
