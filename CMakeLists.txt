cmake_minimum_required(VERSION 2.8)
project(CartoonifierDesktop)
find_package(OpenCV REQUIRED)
SET(SRC
    src/main_desktop.cpp
    src/cartoon.cpp
)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(CartoonifierDesktop ${SRC})
target_link_libraries(CartoonifierDesktop ${OpenCV_LIBS})

