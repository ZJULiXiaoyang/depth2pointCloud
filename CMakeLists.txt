cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(depth2cloud)

find_package(PCL 1.2 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${PCL_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS} ${OPENCV_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS} ${OPENCV_DEFINITIONS})

add_executable (depth2cloud depth2cloud.cpp)
target_link_libraries (depth2cloud ${PCL_LIBRARIES} ${OpenCV_LIBS})
