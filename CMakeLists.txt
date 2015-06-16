project(fiber)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

include_directories(
)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

% file(COPY textures DESTINATION /)
add_executable(fiber
src/main.cpp)


target_link_libraries(main


${CMAKE_SOURCE_DIR}/include/glew-1.11.0/lib/Release/x64/glew32s.lib
opengl32.lib
)
