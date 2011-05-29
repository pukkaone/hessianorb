// $Id$
#ifndef HESSIAN_HTTPCONNECTIONIMPL_H
#define HESSIAN_HTTPCONNECTIONIMPL_H

#include "hessian/Connection.h"
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <sstream>

namespace hessian {

/**
 * Sends request and receives reply over HTTP.
 */
class HttpConnectionImpl: public Connection
{
    CURL* pCurl_;
    struct curl_slist* pHeaders_;
    char errorBuffer_[CURL_ERROR_SIZE];
    std::stringbuf responseBuffer_;

    static size_t writeData(
            void* pBuffer, size_t elementSize, size_t numElements, void* pUser);

    int post(const char* pContent, size_t contentSize, std::streambuf* pResponse);

public:
    HttpConnectionImpl(const std::string& url);
    ~HttpConnectionImpl();

    // Implement Connection interface.
    std::streambuf* send(const MemoryStreamBuf* pRequestContent);
};

}//namespace hessian
#endif
