cmake_minimum_required(VERSION 3.25)
project(LongNumber)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(CountPi src/longnumber.cpp src/countpi.cpp)
add_executable(Test src/longnumber.cpp tests/test.cpp)

add_custom_target(test
    COMMAND Test
    DEPENDS Test
)

add_custom_target(pi
    COMMAND CountPi
    DEPENDS CountPi
)