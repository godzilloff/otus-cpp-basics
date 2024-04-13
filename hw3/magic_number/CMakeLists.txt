cmake_minimum_required(VERSION 3.5)

project(hw3)

add_executable(
	magic_number
	main.cpp
	types.h
	argument.h
	argument.cpp
	game.h
	game.cpp
	high_scores.h
	high_scores.cpp
)

set_target_properties(magic_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# === assign it as a startup project VS ===
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT magic_number
)

# === hide VS projects: ALL_BUILD and ZERO_CHECK ===
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

