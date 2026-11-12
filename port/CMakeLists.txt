# Native PC build of Dragon Ball Z: Budokai Tenkaichi 2: PS2Recomp's runtime + the code translated by port/recomp.toml.
#   cmake -S port -B port/build/native -G Ninja -DCMAKE_BUILD_TYPE=Release && ninja -C port/build/native
cmake_minimum_required(VERSION 3.20)
project(bt2_native C CXX)

# PS2Recomp uses SSE4.1 intrinsics (_mm_extract_epi32/64) for 128-bit registers.
add_compile_options(-msse4.1)
# Hybrid port (PS2X_IDENTITY_RDRAM): guest RAM at its own addresses, so rdram is the null pointer and every access
# is null + offset; keep the compiler from treating that as undefined and deleting checks.
add_compile_options(-fno-delete-null-pointer-checks)

set(PS2RECOMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../tools/PS2Recomp" CACHE PATH "PS2Recomp checkout")
set(RECOMP_OUT "${CMAKE_CURRENT_SOURCE_DIR}/build/recomp")

set(PS2X_BUILD_RECOMP OFF CACHE BOOL "" FORCE)
set(PS2X_BUILD_ANALYZER OFF CACHE BOOL "" FORCE)
set(PS2X_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(PS2X_BUILD_STUDIO OFF CACHE BOOL "" FORCE)
set(PS2X_ENABLE_AGRESSIVE_LOGS OFF CACHE BOOL "" FORCE)
set(PS2X_ENABLE_DEBUG_UI OFF CACHE BOOL "" FORCE)
add_subdirectory("${PS2RECOMP_DIR}" ps2recomp EXCLUDE_FROM_ALL)

file(GLOB BT2_RECOMP_SRC CONFIGURE_DEPENDS "${RECOMP_OUT}/*.cpp")
add_executable(bt2 ${BT2_RECOMP_SRC} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/movie.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/identity.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/coltrace.cpp"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/callcount.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/watchaddr.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/storewatch.cpp")
target_include_directories(bt2 PRIVATE "${RECOMP_OUT}")
target_link_libraries(bt2 PRIVATE ps2_runtime ffmpeg)
# 13k generated files: batch them (unity build) and keep optimisation cheap.
set_target_properties(bt2 PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 64)
target_compile_options(bt2 PRIVATE -O2 -w)
set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/movie.cpp"
                            "${CMAKE_CURRENT_SOURCE_DIR}/src/identity.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/coltrace.cpp"
                            "${CMAKE_CURRENT_SOURCE_DIR}/src/callcount.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/watchaddr.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/storewatch.cpp"
                            PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)

# Hybrid port: functions whose C was proven equal to the original (scripts/fn_diff.py) run as native code
# (port/tools/gen_native.py -> build/gen). Their globals are absolute symbols at the PS2 addresses and guest RAM is
# at its own host addresses (PS2X_IDENTITY_RDRAM=1), so the program is not position-independent and is placed at
# 1 GB, above the 32 MB of guest RAM. BT2_NATIVE=1 at run time switches the native functions on.
set(NATIVE_GEN "${CMAKE_CURRENT_SOURCE_DIR}/build/gen")
if(EXISTS "${NATIVE_GEN}/native_wrappers.cpp" AND EXISTS "${NATIVE_GEN}/libbt2native.a")
    target_sources(bt2 PRIVATE "${NATIVE_GEN}/native_wrappers.cpp")
    set_source_files_properties("${NATIVE_GEN}/native_wrappers.cpp" PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)
    target_link_libraries(bt2 PRIVATE "${NATIVE_GEN}/libbt2native.a" "${NATIVE_GEN}/native_syms.ld")
    target_compile_definitions(bt2 PRIVATE BT2_HAVE_NATIVE=1)
endif()
target_link_options(bt2 PRIVATE -no-pie -Wl,-Ttext-segment=0x40000000)
