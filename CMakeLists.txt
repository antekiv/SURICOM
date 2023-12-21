cmake_minimum_required(VERSION 3.22.1)
project( text_recognition )

set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(camera Camera.cpp)

target_link_libraries(camera
        ${OpenCV_LIBS}
)

