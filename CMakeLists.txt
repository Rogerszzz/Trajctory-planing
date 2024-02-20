cmake_minimum_required(VERSION 3.5)

project(main C)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/Lib/include)
add_subdirectory(Lib)

set(source ${PROJECT_SOURCE_DIR}/main.c)
add_executable(main ${source})

target_link_libraries(main SPG_lib)
