// $Id$
#include "testing/Config.h"

#ifdef TESTING_POSIX
    #include "testing/Posix/TimeHelpers.h"
#else
    #include "testing/Win32/TimeHelpers.h"
#endif
