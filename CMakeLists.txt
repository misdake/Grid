cmake_minimum_required(VERSION 3.7)
project(Grid)

set(CMAKE_CXX_STANDARD 11)

set(MACHINE_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../Machine/build/include")
set(MACHINE_LIBRARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../Machine/build/lib")
include_directories(Grid ${MACHINE_INCLUDE_DIRECTORY})
find_library(MACHINE_LIBRARIES NAMES Machine PATHS ${MACHINE_LIBRARY_DIRECTORY})

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)
FILE(GLOB_RECURSE HEADER_FILES src/*.h)

add_executable(Grid ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Grid ${MACHINE_LIBRARIES})
