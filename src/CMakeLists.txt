
file(REMOVE ${PROJECT_SOURCE_DIR}/build/lib/core.h)
file(COPY core/core.h DESTINATION ${PROJECT_SOURCE_DIR}/build/lib)

set(CORE_LIB_FILES
        core/Server.cpp
        core/Request.cpp
        core/ClientConnection.cpp
        core/Response.cpp)

add_library(core SHARED ${CORE_LIB_FILES})
target_link_libraries (core ${CMAKE_THREAD_LIBS_INIT})


