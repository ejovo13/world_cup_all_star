project(world_cup)

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(wc_src ${CMAKE_SOURCE_DIR}/src)
set(wc_lib ${CMAKE_SOURCE_DIR}/lib)
set(wc_inc ${CMAKE_SOURCE_DIR}/inc)


include_directories(${wc_inc})
add_subdirectory(${wc_lib})
add_subdirectory(${wc_src})