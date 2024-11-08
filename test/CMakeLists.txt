SET(PROJECT_TEST ${PROJECT_NAME}-test)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    check.h
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE ${PROJECT_NAME}-lib Qt6::Test)

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
