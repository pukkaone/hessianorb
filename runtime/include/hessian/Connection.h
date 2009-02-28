// $Id$
#ifndef HESSIAN_CONNECTION_H
#define HESSIAN_CONNECTION_H

#include "hessian/MemoryStreamBuf.h"
#include <stdexcept>

namespace hessian {

/**
 * Indicates an error occurred trying to transfer data across the network.
 */
class ConnectionException: public std::runtime_error
{
public:
    ConnectionException (const std::string& message):
        std::runtime_error(message)
    { }
};

/**
 * Interface to send request and receive response.
 */
class Connection
{
public:
    virtual ~Connection();

    /**
     * Sends request and receives response.
     *
     * @param pRequestContent
     *          stream buffer containing request data to send
     * @return stream buffer which the caller must read to extract the response
     *          data
     * @throws ConnectionException if data cannot be transferred
     */
    virtual std::streambuf* send(const MemoryStreamBuf* pRequestContent) = 0;
};

}//namespace hessian
#endif
