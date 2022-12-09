function(add_wc_test NM ) 
    set(SRC "test_${NM}.cpp")
    set(TNM "test_${NM}")
    add_executable(${TNM} ${SRC})
    target_link_libraries(${TNM} world_cup)
    add_test(NAME ${TNM}
             COMMAND ${TNM})
endfunction()

add_wc_test(hi)
copy_file(world_cup_stats.csv)