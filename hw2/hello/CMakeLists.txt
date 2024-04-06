cmake_minimum_required(VERSION 3.29)

project(hw2)

add_executable(hello_world 
    hello_world.cpp
    example.cpp
    example.h
    move_me_out.cpp
    move_me_out.h
)

set_target_properties(hello_world PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# === assign it as a startup project VS ===
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT hello_world
)

# === hide VS projects: ALL_BUILD and ZERO_CHECK ===
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

