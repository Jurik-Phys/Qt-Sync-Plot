cmake_minimum_required(VERSION 3.20)
project(qt-sync-plot-src)
# Find Qt6 components required for this module
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
# LSL
find_package(LSL REQUIRED
    HINTS ${LSL_INSTALL_ROOT}
    "${CMAKE_CURRENT_LIST_DIR}/../liblsl/build/"
    "${CMAKE_CURRENT_LIST_DIR}/../liblsl/build/install"
    "${CMAKE_CURRENT_LIST_DIR}/../liblsl/out/build/x64-Release"
    "${CMAKE_CURRENT_LIST_DIR}/../liblsl/out/install/x64-Release"
    PATH_SUFFIXES share/LSL
)

set(SOURCE_LIB  pltCartesian.cpp \\
                pltPolarian.cpp  \\
                eegLocalRawData.cpp \\
                aleDataProvider.cpp \\
                lslDataProvider.cpp \\
                qRootWindow.cpp \\
                lslFindWindow.cpp \\
                pltDataProvider.cpp)
add_library(src STATIC ${SOURCE_LIB})

add_subdirectory(qcustomplot)

target_link_libraries(src PRIVATE qcustomplot Qt6::Widgets Qt6::Network LSL::lsl)
