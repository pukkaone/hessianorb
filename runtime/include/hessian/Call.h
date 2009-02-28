// $Id$
#ifndef HESSIAN_CALL_H
#define HESSIAN_CALL_H

#include "hessian/Connection.h"
#include "hessian/HessianInputStream.h"
#include "hessian/HessianOutputStream.h"

namespace hessian {

/**
 * Encodes Hessian method call and decodes reply.
 */
template<typename T>
class Call: public HessianOutputStream
{
    T value_;

public:
    /**
     * Constructs call to the named method.
     */
    Call (const char* pMethodName, std::string::size_type methodNameLength)
    {
        beginCall(pMethodName, methodNameLength);
    }

    /**
     * Invoke method by sending request over the connection and receiving the
     * reply.
     */
    T& invoke (Connection& connection)
    {
        endCall();

        HessianInputStream in(connection.send(rdbuf()));
        in.beginReply();
        in >> value_;
        in.endReply();
        return value_;
    }
};

/**
 * Specialize template for void return type.
 */
template<>
class Call<void>: public HessianOutputStream
{
public:
    Call (const char* pMethodName, std::string::size_type methodNameLength)
    {
        beginCall(pMethodName, methodNameLength);
    }

    void invoke (Connection& connection)
    {
        endCall();

        HessianInputStream in(connection.send(rdbuf()));
        in.beginReply();
        in.readNull();
        in.endReply();
    }
};

}//namespace hessian
#endif
