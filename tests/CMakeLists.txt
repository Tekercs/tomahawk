add_subdirectory(lib/gtest)

FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/)
FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build/test)


include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src)

add_executable(tests
        RequestTest.cpp ResponseTest.cpp)

target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests core)

set_target_properties( tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/test)
