cmake_minimum_required(VERSION 3.20)
project(qcustomplot-lib)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 components required for this module
find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

set(SOURCE_LIB qcustomplot.cpp)

add_library(qcustomplot STATIC ${SOURCE_LIB})

target_link_libraries(qcustomplot PRIVATE Qt6::Widgets Qt6::PrintSupport)
