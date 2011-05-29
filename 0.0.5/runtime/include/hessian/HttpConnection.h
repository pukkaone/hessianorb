// $Id$
#ifndef HESSIAN_HTTPCONNECTION_H
#define HESSIAN_HTTPCONNECTION_H

#include "hessian/Connection.h"

namespace hessian {

class HttpConnectionImpl;

/**
 * Sends request and receives reply over HTTP.
 */
class HttpConnection: public Connection
{
    HttpConnectionImpl *pImpl_;

public:
    HttpConnection(const std::string& url);
    ~HttpConnection();

    // Implement Connection interface.
    std::streambuf* send(const MemoryStreamBuf* pRequestContent);
};

}//namespace hessian
#endif
