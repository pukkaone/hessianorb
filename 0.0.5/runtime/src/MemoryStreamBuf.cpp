// $Id$
#include "hessian/MemoryStreamBuf.h"

namespace hessian {

MemoryStreamBuf::MemoryStreamBuf (std::streamsize initialSize):
    buffer_(initialSize)
{
    setp(&buffer_[0], &buffer_[buffer_.size()]);
}

MemoryStreamBuf::int_type
MemoryStreamBuf::overflow (MemoryStreamBuf::int_type c)
{
    DifferenceType putOffset = pptr() - &buffer_[0];

    // Expand buffer size to accommodate the character.
    if (putOffset >= buffer_.size()) {
        buffer_.resize(putOffset + 1);
        buffer_.resize(buffer_.capacity());
    }

    // Insert the character
    if (c != traits_type::eof()) {
        buffer_[putOffset++] = traits_type::to_char_type(c);
    }

    setp(&buffer_[putOffset], &buffer_[buffer_.size()]);
    return traits_type::not_eof(c);
}

}//namespace hessian
