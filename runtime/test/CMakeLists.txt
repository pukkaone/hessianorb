# $Id$

add_executable(hessianUnitTests
        Hessian1OutputStreamTest.cpp
        runAllTests.cpp
)
target_link_libraries(hessianUnitTests hessianorb testing)
