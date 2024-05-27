cmake_minimum_required(VERSION 3.20)

project(qt-sync-plot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/Qt/6.4.1/gcc_64/")

find_package(Qt6 REQUIRED COMPONENTS Widgets)


set(SOURCE_EXE main.cpp)

add_subdirectory(src)

add_executable(qt-sync-plot ${SOURCE_EXE})

target_link_libraries(qt-sync-plot PRIVATE src Qt6::Widgets)
