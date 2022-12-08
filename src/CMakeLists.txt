add_executable(load_teams load_teams.cpp)
target_link_libraries(load_teams world_cup)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/world_cup_stats.csv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})