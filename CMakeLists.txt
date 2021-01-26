cmake_minimum_required (VERSION 3.0.2)
project(base128_demo)

add_compile_options(-std=c++11)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/hbk/software/opencv-3.4.0/build")

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
FILE(GLOB HEADS *.h)

find_package(OpenCV REQUIRED)
add_executable(demo ${SRC_LIST} ${HEADS})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo ${OpenCV_LIBS})



