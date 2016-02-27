add_subdirectory(lib/gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src)

add_executable(tests
        RequestTest.cpp ResponseTest.cpp)

target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests core)
