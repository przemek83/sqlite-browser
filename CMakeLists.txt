cmake_minimum_required(VERSION 3.16)

project(sqlite-browser
        LANGUAGES CXX
        VERSION 1.0.0
        DESCRIPTION "Simple SQLite DB browser in Qt"
        HOMEPAGE_URL "https://github.com/przemek83/sqlite-browser")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Collect coverage" OFF)

if(CODE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Sql)
qt_standard_project_setup()

set(${PROJECT_NAME}_SOURCES
    src/AddRowDialog.cpp
    src/AddRowDialog.h
    src/DatabaseConfig.cpp
    src/DatabaseConfig.h
    src/MainWindow.cpp
    src/MainWindow.h
)
qt_add_resources(${PROJECT_NAME}_SOURCES res/icons.qrc)

set(UI
    src/AddRowDialog.ui
    src/MainWindow.ui
)
source_group("UI Files" FILES ${UI})

add_library (${PROJECT_NAME}-lib STATIC ${${PROJECT_NAME}_SOURCES} ${UI})
target_link_libraries(${PROJECT_NAME}-lib PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib Qt6::Widgets)

# enable_testing()
# include(Tests.cmake)
# add_subdirectory(test)