cmake_minimum_required(VERSION 3.20)
project(qt-sync-plot-src)
# Find Qt6 components required for this module
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(SOURCE_LIB  qmainwindow.cpp \\
                eegLocalRawData.cpp \\
                clkTimer.cpp \\
                fakeData.cpp \\
                procData.cpp)
add_library(src STATIC ${SOURCE_LIB})

add_subdirectory(qcustomplot)

target_link_libraries(src PRIVATE qcustomplot Qt6::Widgets)
