// $Id$
#ifndef HESSIAN_HESSIAN1INPUTSTREAM_H
#define HESSIAN_HESSIAN1INPUTSTREAM_H

#include "hessian/types.h"
#include <streambuf>

namespace hessian {

/**
 * Decodes values from Hessian protocol format.
 */
class Hessian1InputStream
{
    std::streambuf* pBuffer_;

    void throwMarshallException(const std::string& message, int actualTag);
    void expect(int expectedTag, int actualTag);
    void expect(int expectedTag);

    // Extracts next byte from input.
    int read ()
    { return pBuffer_->sbumpc(); }
    
    // Reads bytes, and appends to value.
    void read(hessian::Binary& value);

    // Reads 32-bit integer.
    void read(hessian::Int& value);

    // Reads 64-bit integer.
    void read(hessian::Long& value);

    // Reads UTF-8 encoded string, and appends to value.
    void read(std::string& value);

    // Reads fault.
    void readFault(std::string& code, std::string& message);

public:
    Hessian1InputStream (std::streambuf* pBuffer):
        pBuffer_(pBuffer)
    { }

    /**
     * Gets next byte from input without consuming it.
     */
    int peek ()
    { return pBuffer_->sgetc(); }

    void beginList();
    void endList();

    void beginObject();
    void endObject();
    void throwUnknownPropertyException(const std::string& key);

    void beginReply();
    void endReply();

    void readNull();

    Hessian1InputStream& operator>>(hessian::Binary& value);
    Hessian1InputStream& operator>>(bool& value);
    Hessian1InputStream& operator>>(hessian::Date& value);
    Hessian1InputStream& operator>>(double& value);
    Hessian1InputStream& operator>>(hessian::Int& value);
    Hessian1InputStream& operator>>(hessian::Long& value);
    Hessian1InputStream& operator>>(std::string& value);
};

}//namespace hessian
#endif
