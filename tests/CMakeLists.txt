SET(PROJECT_TEST ${PROJECT_NAME}-tests)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    DatabaseConfigTest.h
    DatabaseConfigTest.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE ${PROJECT_NAME}-lib Qt6::Test)

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
set_property(TEST ${PROJECT_TESTS} PROPERTY FAIL_REGULAR_EXPRESSION "FAIL!")
