cmake_minimum_required(VERSION 3.5)
project(CipmodbusQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialBus)

qt_standard_project_setup()

qt_add_executable(CipmodbusQt
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(CipmodbusQt PRIVATE Qt6::Core Qt6::Widgets Qt6::SerialBus)
