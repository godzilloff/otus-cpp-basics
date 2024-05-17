cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(statistics statistics.cpp)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(random_shuffle random_shuffle.cpp)
set_target_properties(random_shuffle PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(chrono_example chrono_example.cpp)
set_target_properties(chrono_example PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)



if (MSVC)

# === hide VS projects: ALL_BUILD and ZERO_CHECK ===
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# === assign it as a startup project VS ===
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT statistics
)

endif ()

