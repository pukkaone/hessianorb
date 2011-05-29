# $Id$

if(NOT CURL_FOUND)
    find_package(CURL REQUIRED)
endif(NOT CURL_FOUND)

include_directories(${CURL_INCLUDE_DIRS})

add_library(hessianorb
        Connection.cpp
        Hessian1InputStream.cpp
        Hessian1OutputStream.cpp
        HttpConnection.cpp
        HttpConnectionImpl.cpp
        MemoryStreamBuf.cpp
)
target_link_libraries(hessianorb ${CURL_LIBRARIES})
