project(fiber)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

include_directories(
)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

add_executable(fiber
src/main.cpp)


target_link_libraries(fiber

opengl32.lib
)
