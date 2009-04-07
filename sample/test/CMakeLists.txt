# $Id$

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
set(GENERATED_HEADER_DIR ${GENERATED_DIR}/include)
set(GENERATED_SOURCE_DIR ${GENERATED_DIR}/src)

set(GENERATED_SOURCES
        ${GENERATED_SOURCE_DIR}/PostalAddress.cpp
        ${GENERATED_SOURCE_DIR}/SampleServiceProxy.cpp
        ${GENERATED_SOURCE_DIR}/Season.cpp
        ${GENERATED_SOURCE_DIR}/User.cpp
)

set_source_files_properties(${SAMPLE_JAR} PROPERTIES GENERATED 1)

add_custom_command(
        OUTPUT ${GENERATED_SOURCES}
        COMMAND ${HESSIANC_EXE} -classpath ${SAMPLE_JAR} -header-dest ${GENERATED_HEADER_DIR} -source-dest ${GENERATED_SOURCE_DIR} sample com.googlecode.hessianorb.sample.SampleService
        DEPENDS ${SAMPLE_JAR}
)

include_directories(${GENERATED_HEADER_DIR})

add_executable(sampleIntegrationTests
        ${GENERATED_SOURCES}
        SampleServiceProxyTest.cpp
        runAllTests.cpp
)
target_link_libraries(sampleIntegrationTests hessianorb testing)
