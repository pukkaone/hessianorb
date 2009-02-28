// $Id$
#include "hessian/Hessian1OutputStream.h"

namespace {

// Counts number of UTF-8 encoded characters.  Assumes char is signed.

std::string::size_type
countUTF8Char (const std::string& s)
{
    std::string::size_type count = 0;

    std::string::size_type iBeginAscii = 0;
    std::string::size_type i = 0;
    std::string::size_type size = s.size();
    while (i < size && s[i] >= 0) {
ascii:
        ++i;
    }

    count += (i - iBeginAscii);

    while (i < size) {
        if (s[i] >= 0) {
            iBeginAscii = i;
            goto ascii;
        } else {
            switch (s[i] & 0xF0) {
            case 0xE0:
                i += 3;
                break;
            case 0xF0:
                i += 4;
                break;
            default:
                i += 2;
            }
        }
        ++count;
    }

    return count;
}

}//namespace

namespace hessian {

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
        std::string::size_type nBytes,
        const char* pBytes)
{
    write(static_cast<char>((length >> 8) & 0xFF));
    write(static_cast<char>(length & 0xFF));
    buffer_.sputn(pBytes, nBytes);
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
    const std::string::size_type CHUNK_MAX = 65535;

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

Hessian1OutputStream&
Hessian1OutputStream::operator<< (const std::string& value)
{
    // TODO: Allow sending more than 65535 Unicode characters in a string.
    write('S');
    write(countUTF8Char(value), value.size(), value.data());
    return *this;
}

}//namespace hessian
