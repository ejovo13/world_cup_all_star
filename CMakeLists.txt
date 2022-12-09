project(world_cup)

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


include_directories(${wc_inc})
add_subdirectory(${wc_lib})
add_subdirectory(${wc_src})
add_subdirectory(test)