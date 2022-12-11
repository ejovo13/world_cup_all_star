add_executable(load_teams load_teams.cpp)
target_link_libraries(load_teams world_cup)

copy_file(world_cup_stats.csv)