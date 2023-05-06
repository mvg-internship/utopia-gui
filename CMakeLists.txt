cmake_minimum_required(VERSION 3.5)

project(Utopia VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Find Graphviz libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GVC REQUIRED IMPORTED_TARGET libgvc)
pkg_check_modules(CGRAPH REQUIRED IMPORTED_TARGET libcgraph)

set(PROJECT_SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
  codeeditor.cpp
  codeeditor.h
  windowrun.h
  windowrun.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(Utopia
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )
else()
  add_executable(Utopia
    ${PROJECT_SOURCES}
  )
endif()

target_link_libraries(Utopia PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  PkgConfig::GVC
  PkgConfig::CGRAPH
)
add_subdirectory(test_gui)
set_target_properties(Utopia PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

install(TARGETS Utopia
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(Utopia)
endif()
