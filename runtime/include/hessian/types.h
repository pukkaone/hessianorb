// $Id$
#ifndef HESSIAN_TYPES_H
#define HESSIAN_TYPES_H

#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>

namespace hessian {

// Hessian to C++ type mapping:
//      Hessian         C++
//      -------         ---
//      binary          std::vector<char>
//      boolean         bool
//      date            hessian::Date
//      double          double
//      int             hessian::Int
//      list            std::vector<E>
//      long            hessian::Long
//      map             struct
//      string          std::string

typedef std::vector<char> Binary;
typedef int32_t Int;
typedef int64_t Long;

/**
 * Instant in time represented as number of milliseconds since epoch.
 */
class Date
{
    hessian::Long millis_;

public:
    Date (hessian::Long millis):
        millis_(millis)
    { } 

    hessian::Long timeInMillis () const
    { return millis_; }
};

/**
 * Indicates an error in the received data.
 */
class ProtocolException: public std::runtime_error
{
public:
    ProtocolException (const std::string& message):
        std::runtime_error(message)
    { }

    ~ProtocolException () throw ()
    { }
};

/**
 * Indicates data does not conform to expected format.
 */
class MarshallException: public ProtocolException
{
public:
    MarshallException (const std::string& message):
        ProtocolException(message)
    { }

    ~MarshallException () throw ()
    { }
};

/**
 * Thrown when method call reply is a fault.
 */
class Fault: public std::runtime_error
{
    std::string code_;

public:
    Fault (const std::string& code, const std::string& message):
        std::runtime_error(message),
        code_(code)
    { }

    ~Fault () throw ()
    { }
    
    const std::string& code () const
    { return code_; }
};

}//namespace hessian
#endif
