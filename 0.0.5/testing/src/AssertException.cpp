// $Id$
#include "testing/AssertException.h"

namespace testing {

AssertException::AssertException (
        char const* description,
        char const* filename,
        int lineNumber):
    std::runtime_error(description),
    m_filename(filename),
    m_lineNumber(lineNumber)
{ }

AssertException::~AssertException() throw()
{ }

}//namespace testing
