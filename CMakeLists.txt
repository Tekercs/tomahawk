cmake_minimum_required(VERSION 3.3)
project(tomahawk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file(GLOB MY_PUBLIC_HEADERS
        "core/*.h")

file(COPY ${MY_PUBLIC_HEADERS} DESTINATION build/lib)

set(CORE_LIB_FILES
        core/Server.cpp
        core/Request.cpp
        core/ClientConnection.cpp)

set(MAIN_FILES
        build/main.cpp)

add_library(core SHARED ${CORE_LIB_FILES})
target_link_libraries (core ${CMAKE_THREAD_LIBS_INIT})

add_executable(main ${MAIN_FILES})
target_link_libraries(main core)


set_target_properties( core main
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/lib"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")