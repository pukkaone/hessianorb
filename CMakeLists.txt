# $Id$
cmake_minimum_required(VERSION 2.4)

project(hessianorb)
include(macros.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# code generator
set(HESSIANC_EXE ${EXECUTABLE_OUTPUT_PATH}/hessianc)
add_subdirectory(codegen)

# testing framework
include_directories(testing/include)
add_subdirectory(testing/src)

# runtime library
include_directories(runtime/include)
add_subdirectory(runtime/src)
add_subdirectory(runtime/test)

# sample application
add_subdirectory(sample)

# Get last committed repository revision.
find_program(SVNVERSION_EXECUTABLE svnversion
        DOC "svnversion command line client")
if(SVNVERSION_EXECUTABLE)
    execute_process(
            COMMAND svnversion -c ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE SVN_REVISION_RANGE
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REGEX REPLACE "^[0-9]+:" "" SVN_REVISION ${SVN_REVISION_RANGE})
else(SVNVERSION_EXECUTABLE)
    set(SVN_REVISION UNKNOWN)
endif(SVNVERSION_EXECUTABLE)
