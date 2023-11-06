cmake_minimum_required(VERSION 3.22)
project(Player)
#set(CMAKE_PREFIX_PATH "/Qt/6.5.3/gcc_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(PkgConfig)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

qt_add_executable(Player 
headers/MainWindow.hpp
headers/gstreamer_mgr.hpp
src/main.cpp
src/MainWindow.cpp
src/gstreamer_mgr.cpp
resources.qrc 
)
#qt_add_executable(Player src/MainWindow.cpp)

target_include_directories(Player PRIVATE ${GST_INCLUDE_DIRS})
target_include_directories(Player PRIVATE headers)

target_link_libraries(Player PRIVATE Qt::Widgets)
target_link_libraries(Player PRIVATE Qt::Core)
target_link_libraries(Player PRIVATE Qt::Gui)
target_link_libraries(Player PRIVATE ${GST_LIBRARIES})