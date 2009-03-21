// $Id$
#include "hessian/Hessian1OutputStream.h"

namespace hessian {

const std::string::size_type CHUNK_MAX = 65535;

void
Hessian1OutputStream::write (hessian::Long value)
{
    write(static_cast<char>((value >> 56) & 0xFF));
    write(static_cast<char>((value >> 48) & 0xFF));
    write(static_cast<char>((value >> 40) & 0xFF));
    write(static_cast<char>((value >> 32) & 0xFF));
    write(static_cast<char>((value >> 24) & 0xFF));
    write(static_cast<char>((value >> 16) & 0xFF));
    write(static_cast<char>((value >> 8) & 0xFF));
    write(static_cast<char>(value & 0xFF));
}

void
Hessian1OutputStream::write (
        std::string::size_type length,
        const char* pBegin,
        const char* pEnd)
{
    write(static_cast<char>((length >> 8) & 0xFF));
    write(static_cast<char>(length & 0xFF));
    buffer_.sputn(pBegin, pEnd - pBegin);
}

void
Hessian1OutputStream::beginList ()
{
    write('V');
}

void
Hessian1OutputStream::endList ()
{
    write('z');
}

void
Hessian1OutputStream::beginObject (
        const char* pTypeName, std::string::size_type typeNameLength)
{
    write('M');
    if (pTypeName != 0 && typeNameLength > 0) {
        write('t');
        write(typeNameLength, pTypeName);
    }
}

void
Hessian1OutputStream::endObject ()
{
    write('z');
}

void
Hessian1OutputStream::beginCall (
        const char* pMethodName, std::string::size_type methodNameLength)
{
    write('c');
    write('\x01');
    write('\x00');
    write('m');
    write(methodNameLength, pMethodName);
}

void
Hessian1OutputStream::endCall ()
{
    write('z');
}

Hessian1OutputStream&
Hessian1OutputStream::operator<< (const hessian::Binary& value)
{
    const char *pValue = &value[0];
    std::string::size_type nBytes = value.size();
    while (nBytes > CHUNK_MAX) {
        write('b');
        write(CHUNK_MAX, pValue);

        pValue += CHUNK_MAX;
        nBytes -= CHUNK_MAX;
    }

    write('B');
    write(nBytes, pValue);
    return *this;
}

Hessian1OutputStream&
Hessian1OutputStream::operator<< (bool value)
{
    write(value ? 'T' : 'F');
    return *this;
}

Hessian1OutputStream&
Hessian1OutputStream::operator<< (hessian::Date value)
{
    write('d');
    write(value.timeInMillis());
    return *this;
}

Hessian1OutputStream&
Hessian1OutputStream::operator<< (double value)
{
    write('D');
    buffer_.sputn(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}
    
Hessian1OutputStream&
Hessian1OutputStream::operator<< (hessian::Int value)
{
    write('I');
    write(static_cast<char>((value >> 24) & 0xFF));
    write(static_cast<char>((value >> 16) & 0xFF));
    write(static_cast<char>((value >> 8) & 0xFF));
    write(static_cast<char>(value & 0xFF));
    return *this;
}

Hessian1OutputStream&
Hessian1OutputStream::operator<< (hessian::Long value)
{
    write('L');
    write(value);
    return *this;
}

namespace {

// Counts the number of UTF-8 encoded characters until the end of the range
// or the maximum chunk length is reached.  Assumes char is signed.
// Return pointer to byte after last byte examined.

const char*
countUTF8Char (
        const char* pSrc,
        const char* pEnd,
        std::string::size_type& retCount)
{
    std::string::size_type count = 0;

    while (pSrc < pEnd && *pSrc >= 0) {
ascii:
        ++pSrc;

        if (++count >= CHUNK_MAX) {
            retCount = count;
            return pSrc;
        }
    }

    while (pSrc < pEnd) {
        if (*pSrc >= 0) {
            goto ascii;
        } else {
            switch (*pSrc & 0xF0) {
            case 0xE0:
                pSrc += 3;
                break;
            case 0xF0:
                pSrc += 4;
                break;
            default:
                pSrc += 2;
            }
        }

        if (++count >= CHUNK_MAX) {
            break;
        }
    }

    retCount = count;
    return pSrc;
}

}//namespace

Hessian1OutputStream&
Hessian1OutputStream::operator<< (const std::string& value)
{
    const char* pSrcBegin = value.data();
    const char* pSrcEnd = pSrcBegin + value.size();
    do {
        std::string::size_type count;
        const char* pEnd = countUTF8Char(pSrcBegin, pSrcEnd, count);
        write((pEnd < pSrcEnd) ? 's' : 'S');
        write(count, pSrcBegin, pEnd);

        pSrcBegin = pEnd;
    } while (pSrcBegin < pSrcEnd);

    return *this;
}

}//namespace hessian
