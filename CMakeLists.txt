cmake_minimum_required(VERSION 3.16)

project(sqlite-browser
        LANGUAGES CXX
        VERSION 1.0.0
        DESCRIPTION "Simple SQLite DB browser in Qt"
        HOMEPAGE_URL "https://github.com/przemek83/sqlite-browser")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Sql)
qt_standard_project_setup()

set(SOURCES
    src/AddRowDialog.cpp
    src/DatabaseConfig.cpp
    src/MainWindow.cpp
    src/main.cpp
)
qt_add_resources(SOURCES res/icons.qrc)

set(HEADERS
    src/AddRowDialog.h
    src/DatabaseConfig.h
    src/MainWindow.h
 )

set(UI
    src/AddRowDialog.ui
    src/MainWindow.ui
)
source_group("UI Files" FILES ${UI})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)
