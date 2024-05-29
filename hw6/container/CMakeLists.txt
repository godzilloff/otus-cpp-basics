cmake_minimum_required(VERSION 3.29)

project(hw6_container)

add_executable(container         
	main.cpp
	container_serial.hpp
	container_list.hpp
)

set_target_properties(container
	PROPERTIES 
	CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON)


if (MSVC)

# === hide VS projects: ALL_BUILD and ZERO_CHECK ===
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# === assign it as a startup project VS ===
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT container
)

endif ()
