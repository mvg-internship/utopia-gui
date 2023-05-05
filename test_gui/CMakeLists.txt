cmake_minimum_required(VERSION 3.16)

project(test_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

set(SOURCES
tst_qttest.cpp
../codeeditor.cpp
../mainwindow.cpp
../windowrun.cpp
)

set(HEADERS
../codeeditor.h
../mainwindow.h
../windowrun.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
Qt5::Core
Qt5::Gui
Qt5::Widgets
Qt5::Test
gvc
cgraph
)
