project(fiber)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(VTK REQUIRED)
find_package(Qt5Widgets)

INCLUDE(${VTK_USE_FILE} ${QT_USE_FILE})

#set(VTK_DIR "PATH/TO/VTK/BUILD/DIRECTORY")
include_directories(${VTK_INCLUDE_DIRS} ${QT_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

QT5_WRAP_UI(FORMS_HEADERS ${FORMS})

add_executable(fiber
src/main.cpp
src/Rendering/QVTKWrapper.cpp
src/Rendering/QVTKWrapper.h
src/Rendering/ImagePlaneView.cpp
src/Rendering/ImagePlaneView.h
src/Rendering/View.h
src/Rendering/View.cpp
src/Rendering/BoxView.cpp
src/Rendering/BoxView.h
src/GUI/ui_mainwindow.h
src/GUI/FileMenu.h
src/GUI/FileMenu.cpp
src/TensorComputations/TensorComputations.cpp
src/TensorComputations/TensorComputations.h
${FORMS_HEADERS})


target_link_libraries(fiber
${VTK_LIBRARIES}
Qt5::Widgets
opengl32.lib
)
