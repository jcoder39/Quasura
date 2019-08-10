cmake_minimum_required(VERSION 3.11)

set(TEST_NAME ecs_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES *.cpp)

add_executable(${TEST_NAME} ${SOURCE_FILES})

target_link_libraries(${TEST_NAME} gtest quasura-ecs)

add_test(NAME ${TEST_NAME}
        COMMAND ${TEST_NAME})