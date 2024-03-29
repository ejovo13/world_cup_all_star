# ====== Manual unit testing ===================================
# NM is the NAME of the source file, dropping the '_test' suffix
# i.e. add_wc_test(Hello) adds the source file `Hello_test.cpp`
# ==============================================================
function(add_wc_test NM ) 
    set(SRC "${NM}_test.cpp")
    set(TNM "${NM}_test")
    add_executable(${TNM} ${SRC})
    target_link_libraries(${TNM} all_star sfml-graphics)
    add_test(NAME ${TNM}
             COMMAND ${TNM})
endfunction()

include(GoogleTest)

# ====== GoogleTest framework ==================================
function(add_google_test TEST_NAME) 
    set(SRC_FILE "${TEST_NAME}_test.cpp")
    set(FULL_NAME "${TEST_NAME}_test")
    add_executable(${FULL_NAME} ${SRC_FILE})
    target_link_libraries(${FULL_NAME} GTest::gtest_main world_cup)
    gtest_discover_tests(${FULL_NAME})
endfunction()

copy_file(world_cup_stats.csv)
copy_file(arial.ttf)
copy_file(ball.png)

# ====== Add tests ==============================================
add_wc_test(hi)
add_wc_test(defense)
add_google_test(wc)


## Smfl test window
add_executable(sfml_test sfml_hello_world.cpp)
target_link_libraries(sfml_test sfml-graphics sfml-audio)

## Camille Offense
add_executable(offense_test offense_game.cpp)
target_link_libraries(offense_test all_star)