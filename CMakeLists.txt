# $Id$
cmake_minimum_required(VERSION 2.4)

project(hessianorb)
include(macros.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# testing framework
include_directories(testing/include)
add_subdirectory(testing/src)

# common Ant scripts
copy_file(default.properties ${PROJECT_BINARY_DIR}/default.properties)
copy_file(property.xml ${PROJECT_BINARY_DIR}/property.xml)
copy_file(target.xml ${PROJECT_BINARY_DIR}/target.xml)

# code generator
set(HESSIANC_EXE ${EXECUTABLE_OUTPUT_PATH}/hessianc)
add_subdirectory(codegen)

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

# Target "package_source" creates source distribution.
set(VERSION 0.0.0)
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${VERSION}.${SVN_REVISION})
set(CPACK_SOURCE_IGNORE_FILES "/\\\\.svn/;/build/;/dist/")
if(WIN32)
    set(CPACK_SOURCE_GENERATOR ZIP)
else(WIN32)
    set(CPACK_SOURCE_GENERATOR TGZ)
endif(WIN32)
include(CPack)
