cmake_policy(SET CMP0048 NEW)

project(world_cup VERSION 0.0.1)

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

enable_testing(ON)

set(wc_src ${CMAKE_SOURCE_DIR}/src)
set(wc_lib ${CMAKE_SOURCE_DIR}/lib)
set(wc_inc ${CMAKE_SOURCE_DIR}/inc)

add_compile_options($<$<CONFIG:Debug>:-g>)

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

include_directories(${wc_inc})
add_subdirectory(${wc_lib})
add_subdirectory(${wc_src})
add_subdirectory(test)