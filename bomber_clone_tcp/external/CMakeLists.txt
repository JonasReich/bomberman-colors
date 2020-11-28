# CMakeLists.txt for external libraries

cmake_minimum_required(VERSION 3.8)

add_library(sdl2 SHARED IMPORTED GLOBAL)
target_include_directories(sdl2 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.5/include
)
set(sdl2_dll "${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.5/lib/x64/SDL2.dll" PARENT_SCOPE)
set_target_properties(sdl2 PROPERTIES
    IMPORTED_LOCATION "${sdl2_dll}"
    IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.5/lib/x64/SDL2.lib"
)

add_library(sdl2main STATIC IMPORTED GLOBAL)
# Include dirs are shared with sdl2 so no further includes required
set_target_properties(sdl2main PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/SDL2-2.0.5/lib/x64/SDL2main.lib"
)
# All libs that need sdl2main also need sdl2
target_link_libraries(sdl2main INTERFACE sdl2)

add_library(sdl2net SHARED IMPORTED GLOBAL)
target_include_directories(sdl2net INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/SDL2_net-2.0.1/include
)
set(sdl2net_dll "${CMAKE_CURRENT_LIST_DIR}/SDL2_net-2.0.1/lib/x64/SDL2_net.dll" PARENT_SCOPE)
set_target_properties(sdl2net PROPERTIES
    IMPORTED_LOCATION "${sdl2net_dll}"
    IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/SDL2_net-2.0.1/lib/x64/SDL2_net.lib"
)
# All libs that need sdl2net also need sdl2
target_link_libraries(sdl2net INTERFACE sdl2)

### Export aliases to the three libs in here:
add_library(external::sdl2 ALIAS sdl2)
add_library(external::sdl2net ALIAS sdl2net)
add_library(external::sdl2main ALIAS sdl2main)
