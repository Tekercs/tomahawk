
set(HEADERS core/Server.h core/ClientConnection.h core/Response.h core/Request.h)

#file(REMOVE ${PROJECT_SOURCE_DIR}/build/lib/*.h)
file(COPY ${HEADERS} DESTINATION ${PROJECT_SOURCE_DIR}/build/lib)

set(CORE_LIB_FILES
        core/Server.cpp
        core/Request.cpp
        core/ClientConnection.cpp
        core/Response.cpp core/Server.h core/ClientConnection.h core/Response.h core/Request.h)

add_library(core SHARED ${CORE_LIB_FILES})
target_link_libraries (core ${CMAKE_THREAD_LIBS_INIT})


