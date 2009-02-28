// $Id$
#include "hessian/Hessian1InputStream.h"
#include <sstream>

namespace hessian {

void
Hessian1InputStream::throwMarshallException (
        const std::string& message, int actualTag)
{
    std::ostringstream what;
    what << message << " at 0x" << std::hex << actualTag;
    throw MarshallException(what.str());
}

void
Hessian1InputStream::expect (int expectedTag, int actualTag)
{
    if (expectedTag != actualTag) {
        std::ostringstream message;
        message << "expected 0x" << std::hex << expectedTag;
        throwMarshallException(message.str(), actualTag);
    }
}

void
Hessian1InputStream::expect (int expectedTag)
{
    expect(expectedTag, read());
}

void
Hessian1InputStream::read (hessian::Binary& value)
{
    std::string::size_type nBytes = ((read() & 0xFF) << 8) | (read() & 0xFF);
    std::string::size_type offset = value.size();
    value.resize(offset + nBytes);
    pBuffer_->sgetn(&value[offset], nBytes);
}

void
Hessian1InputStream::read (hessian::Int& value)
{
    value = ((read() & 0xFF) << 24) |
            ((read() & 0xFF) << 16) |
            ((read() & 0xFF) << 8) |
            (read() & 0xFF);
}

void
Hessian1InputStream::read (hessian::Long& value)
{
    value = (static_cast<hessian::Long>(read() & 0xFF) << 56) |
            (static_cast<hessian::Long>(read() & 0xFF) << 48) |
            (static_cast<hessian::Long>(read() & 0xFF) << 40) |
            (static_cast<hessian::Long>(read() & 0xFF) << 32) |
            (static_cast<hessian::Long>(read() & 0xFF) << 24) |
            (static_cast<hessian::Long>(read() & 0xFF) << 16) |
            (static_cast<hessian::Long>(read() & 0xFF) << 8) |
            static_cast<hessian::Long>(read() & 0xFF);
}

void
Hessian1InputStream::read (std::string& value)
{
    std::string::size_type nChar = ((read() & 0xFF) << 8) | (read() & 0xFF);
    for (std::string::size_type i = 0; i < nChar; ++i) {
        int ch = read();
        value.append(1, static_cast<char>(ch));

        if (ch >= 0x80) {
            switch (ch & 0xF0) {
            case 0xF0:
                value.append(1, static_cast<char>(read()));
                // FALL THROUGH
            case 0xE0:
                value.append(1, static_cast<char>(read()));
                // FALL THROUGH
            default:
                value.append(1, static_cast<char>(read()));
            }
        }
    }
}

void
Hessian1InputStream::readFault (std::string& code, std::string& message)
{
    expect('f');

    // Skip key "code".
    std::string key;
    *this >> key;
    // Read code value.
    *this >> code;

    // Skip key "message".
    *this >> key;
    // Read message value.
    *this >> message;

    // Ignore remaining input.
}

void
Hessian1InputStream::beginList ()
{
    expect('V');
    int tag = peek();
    if (tag == 't') {
        read();
        std::string typeName;
        read(typeName);

        tag = peek();
    }

    if (tag == 'l') {
        read();
        Int length;
        read(length);
    }
}

void
Hessian1InputStream::endList ()
{
    expect('z');
}

void
Hessian1InputStream::beginObject ()
{
    expect('M');
    int tag = peek();
    if (tag == 't') {
        read();
        std::string typeName;
        read(typeName);
    }
}

void
Hessian1InputStream::endObject ()
{
    expect('z');
}

void
Hessian1InputStream::throwUnknownPropertyException (
        const std::string& key)
{
    std::ostringstream what;
    what << "Unknown object property " << key;
    throw MarshallException(what.str());
}

void
Hessian1InputStream::beginReply ()
{
    expect('r');
    read(); // major
    read(); // minor

    int tag = peek();
    if (tag == 'f') {
        std::string code, message;
        readFault(code, message);
        throw Fault(code, message);
    }
}

void
Hessian1InputStream::endReply ()
{
    expect('z');
}

void
Hessian1InputStream::readNull ()
{
    expect('N');
}

Hessian1InputStream&
Hessian1InputStream::operator>> (hessian::Binary& value)
{
    int tag = read();
    if (tag != 'b' && tag != 'B') {
        throwMarshallException("expected binary", tag);
    }

    value.clear();
    while (tag == 'b') {
        read(value);
        tag = read();
    }

    expect('B', tag);
    read(value);
    return *this;
}

Hessian1InputStream&
Hessian1InputStream::operator>> (bool& value)
{
    int tag = read();
    switch (tag) {
    case 'F':
        value = false;
        break;
    case 'T':
        value = true;
        break;
    default:
        throwMarshallException("expected boolean", tag);
    }
    return *this;
}

Hessian1InputStream&
Hessian1InputStream::operator>> (hessian::Date& value)
{
    expect('d');
    hessian::Long millis;
    read(millis);
    value = hessian::Date(millis);
    return *this;
}

Hessian1InputStream&
Hessian1InputStream::operator>> (double& value)
{
    expect('D');
    pBuffer_->sgetn(reinterpret_cast<char*>(&value), sizeof(value));
    return *this;
}
    
Hessian1InputStream&
Hessian1InputStream::operator>> (hessian::Int& value)
{
    expect('I');
    value = ((read() & 0xFF) << 24) |
            ((read() & 0xFF) << 16) |
            ((read() & 0xFF) << 8) |
            (read() & 0xFF);
    return *this;
}

Hessian1InputStream&
Hessian1InputStream::operator>> (hessian::Long& value)
{
    expect('L');
    read(value);
    return *this;
}

Hessian1InputStream&
Hessian1InputStream::operator>> (std::string& value)
{
    int tag = read();
    if (tag == 'N') {
        value.clear();
        return *this;
    }

    if (tag != 's' && tag != 'S') {
        throwMarshallException("expected string", tag);
    }

    value.clear();
    while (tag == 's') {
        read(value);
        tag = read();
    }

    expect('S', tag);
    read(value);
    return *this;
}

}//namespace hessian
