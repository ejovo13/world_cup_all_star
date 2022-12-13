# add_library(world_cup team.cpp rng.cpp bracket.cpp)
add_library(world_cup OBJECT team.cpp rng.cpp bracket.cpp match.cpp)