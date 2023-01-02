cmake_policy(SET CMP0048 NEW)

project(all_star VERSION 0.0.1)

#======== Dependencies ==========================
#================================================
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

enable_testing(ON)

set(ALL_STAR_INC ${CMAKE_SOURCE_DIR}/inc)
set(ALL_STAR_LIB ${CMAKE_SOURCE_DIR}/lib)
set(ALL_STAR_SRC ${CMAKE_SOURCE_DIR}/src)

set(wc_inc ${ALL_STAR_SRC}/world_cup)
set(wc_lib ${ALL_STAR_lib}/world_cup)
# set(wc_src ${ALL_STAR_SRC}/world_cup)

add_compile_options(
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-Wall>
)

# Add a macro
macro(copy_file F)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${F}
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro()

set(CMAKE_CXX_STANDARD 20)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${ALL_STAR_INC})
add_subdirectory(${ALL_STAR_LIB})
add_subdirectory(${ALL_STAR_SRC})
add_subdirectory(test)
add_subdirectory(resources)