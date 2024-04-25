cmake_minimum_required(VERSION 3.5)

project(SPG_lib C)
message(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
set(source ${PROJECT_SOURCE_DIR}/src/SegmentedTrajectory.c)

add_library(SPG_lib SHARED ${source})
target_link_libraries(SPG_lib m)
