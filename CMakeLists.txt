cmake_minimum_required(VERSION 3.25)
project(TCMS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(TCMS main.cpp Personnel.cpp Personnel.h EquipmentData.cpp EquipmentData.h Shipment.cpp Shipment.h)
target_link_libraries(TCMS
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

