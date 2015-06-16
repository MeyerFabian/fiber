project(fiber)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)
find_package(VTK REQUIRED)


INCLUDE(${VTK_USE_FILE})
#set(VTK_DIR "PATH/TO/VTK/BUILD/DIRECTORY")
include_directories(${VTK_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

add_executable(fiber
src/main.cpp)


target_link_libraries(fiber
${VTK_LIBRARIES}
opengl32.lib
)
