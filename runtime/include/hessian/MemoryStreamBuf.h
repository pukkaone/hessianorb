// $Id$
#ifndef HESSIAN_MEMORYSTREAMBUF_H
#define HESSIAN_MEMORYSTREAMBUF_H

#include <streambuf>
#include <vector>

namespace hessian {

/**
 * A streambuf implementation similar to std::strstreambuf except you don't
 * have to remember to unfreeze the buffer to prevent a memory leak.
 */
class MemoryStreamBuf: public std::streambuf
{
    std::vector<char> buffer_;
    typedef std::vector<char>::difference_type DifferenceType;

protected:
    int_type overflow(int_type c = traits_type::eof());

public:
    MemoryStreamBuf(std::streamsize initialSize);

    const char* str() const
    { return &buffer_[0]; }

    std::streamsize pcount() const
    { return pptr() - &buffer_[0]; }
};

}//namespace hessian
#endif
