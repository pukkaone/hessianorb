# $Id$
cmake_minimum_required(VERSION 2.4)

project(hessianorb)
include(macros.cmake)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

enable_testing()

# testing framework
include_directories(testing/include)
add_subdirectory(testing/src)

# common Ant scripts
copy_file(default.properties ${PROJECT_BINARY_DIR}/default.properties)
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

# Get last committed repository revision.  Use svnversion because it outputs
# the M flag if the working copy has uncommitted modifications.
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
set(CPACK_PACKAGE_VERSION 0.0.4)
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}.${SVN_REVISION})
set(CPACK_SOURCE_IGNORE_FILES "/\\\\.svn/;/build/")
if(WIN32)
    set(CPACK_GENERATOR ZIP)
    set(CPACK_SOURCE_GENERATOR ZIP)
else(WIN32)
    set(CPACK_GENERATOR TGZ)
    set(CPACK_SOURCE_GENERATOR TGZ)
endif(WIN32)
include(CPack)

# Target "promote" creates a Subversion tag for the release.
find_package(Subversion)
if(Subversion_FOUND AND NOT (SVN_REVISION STREQUAL "exported"))
    Subversion_WC_INFO(${CMAKE_SOURCE_DIR} SVN)
    add_custom_target(promote
            COMMAND svn copy -m "Release ${CPACK_PACKAGE_VERSION}"
                    ${SVN_WC_URL}
                    ${SVN_WC_ROOT}/tags/release-${CPACK_PACKAGE_VERSION})
endif()
