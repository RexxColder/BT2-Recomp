cmake_minimum_required(VERSION 3.16)
project(bt2-setup LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Tipo de build" FORCE)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
find_package(Threads REQUIRED)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../port/third_party/imgui")
if(NOT EXISTS "${IMGUI_DIR}/imgui.cpp")
    message(FATAL_ERROR "No está Dear ImGui en ${IMGUI_DIR} (se usa el vendorizado del repo).")
endif()

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)
set_source_files_properties(${IMGUI_SOURCES} PROPERTIES COMPILE_OPTIONS "-w")
# snprintf trunca a propósito los mensajes que incluyen rutas largas; el warning es un falso positivo.
set_source_files_properties(src/install.c PROPERTIES COMPILE_OPTIONS "-Wno-format-truncation")

add_executable(bt2-setup
    src/main.cpp
    src/gui.cpp
    src/paths.cpp
    src/launch.cpp
    src/iso.c
    src/sha1.c
    src/install.c
    ${IMGUI_SOURCES}
)

target_include_directories(bt2-setup PRIVATE src ${IMGUI_DIR})
target_compile_definitions(bt2-setup PRIVATE _FILE_OFFSET_BITS=64 _POSIX_C_SOURCE=200809L)
target_compile_options(bt2-setup PRIVATE -Wall -Wextra -Wno-unused-parameter)
target_link_libraries(bt2-setup PRIVATE PkgConfig::SDL3 Threads::Threads ${CMAKE_DL_LIBS})

# El binario queda en setup/build/bt2-setup (el directorio de build es setup/build/).
set_target_properties(bt2-setup PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
install(TARGETS bt2-setup RUNTIME DESTINATION bin)
