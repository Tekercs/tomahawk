
file(GLOB MY_PUBLIC_HEADERS
        "src/core/*.h")

file(COPY ${MY_PUBLIC_HEADERS} DESTINATION ../build/lib)

set(CORE_LIB_FILES
        core/Server.cpp
        core/Request.cpp
        core/ClientConnection.cpp)


add_library(core SHARED ${CORE_LIB_FILES})
target_link_libraries (core ${CMAKE_THREAD_LIBS_INIT})


