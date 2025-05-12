cmake_minimum_required(VERSION 3.16)

project(test1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

add_executable(test1
  main.cpp
  Student.h Student.cpp
  StudentQuery.h StudentQuery.cpp
  GlobleApp.h GlobleApp.cpp
)
target_link_libraries(test1 threaddblib Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

include(GNUInstallDirs)
install(TARGETS test1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_subdirectory(threaddblib)
