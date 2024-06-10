cmake_minimum_required(VERSION 3.29)

project(hw6_container)

find_package(GTest)

add_executable(container         
        src/main.cpp
        src/container_serial.hpp
        src/container_list.hpp
)

add_executable(test_container         
        test/main_test.cpp
        test/ContainerList_tests.cpp
        test/ContainerSerial_tests.cpp
        src/container_serial.hpp
        src/container_list.hpp
)

set_target_properties(container
        PROPERTIES 
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED ON)

set_target_properties(test_container
        PROPERTIES 
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED ON)

# Add src to the include directories for the test target
target_include_directories(
        test_container PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
        test_container PRIVATE
        ${GTEST_BOTH_LIBRARIES}
)

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_BOTH_LIBRARIES})



# enable pedantic compiler modes 
if (MSVC)
        target_compile_options(container PUBLIC /W4 /WX)
        target_compile_options(test_container PUBLIC /W4 /WX)

        target_include_directories(
           test_container PRIVATE
           "c:/lib/googletest/include"
        )

        target_link_libraries(
           test_container PRIVATE
           "c:/lib/googletest/lib/gtest.lib"
        )

else()
        target_compile_options(container PUBLIC -Wall -Wextra -Werror -pedantic)
        target_compile_options(test_container PUBLIC -Wall -Wextra -Werror -pedantic)
endif()


if (MSVC)

# === hide VS projects: ALL_BUILD and ZERO_CHECK ===
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# === assign it as a startup project VS ===
set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT test_container
)

endif ()
