copy_file(world_cup_stats.csv)
copy_file(arial.ttf)
copy_file(cartoon_soccer_field.png)

add_executable(load_teams load_teams.cpp)
target_link_libraries(load_teams $<TARGET_OBJECTS:world_cup>)

add_executable(all_star_game all_star.cpp)
target_link_libraries(all_star_game all_star)