add_subdirectory(./lib/googletest-main)
set(gtest_SOURCE_DIR "./lib/googletest-main/")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/runAllTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TodoListTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TodoFixture.cpp
        )

add_executable(TodoTests ${TEST_SOURCE_FILES})
target_link_libraries(TodoTests gtest gtest_main core)

enable_testing()
add_test(NAME unitTests COMMAND TodoTests)