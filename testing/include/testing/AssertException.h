// $Id$
#ifndef TESTING_ASSERTEXCEPTION_H
#define TESTING_ASSERTEXCEPTION_H

#include <stdexcept>

namespace testing {

class AssertException: public std::runtime_error
{
	std::string m_filename;
    int m_lineNumber;

public:
    AssertException(
            char const* description, char const* filename, int lineNumber);
    ~AssertException() throw();

	const char* Filename () const
	{ return m_filename.c_str(); }

    int LineNumber () const
    { return m_lineNumber; }
};

}//namespace testing
#endif
