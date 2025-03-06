add_subdirectory(./lib/googletest-main)
set(gtest_SOURCE_DIR, ./lib/googletest-main/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp TaskTest.cpp TodoListTest.cpp TodoFixture.cpp)
add_executable(TodoTests ${TEST_SOURCE_FILES})
target_link_libraries(TodoTests gtest gtest_main core)