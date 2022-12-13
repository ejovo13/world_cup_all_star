add_subdirectory(game_mgr)
add_subdirectory(world_cup)
add_subdirectory(mini_games)

add_library(all_star $<TARGET_OBJECTS:game_mgr> $<TARGET_OBJECTS:world_cup>)
target_link_libraries(all_star sfml-graphics)