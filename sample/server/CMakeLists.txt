# $Id$

add_custom_target(sample_jar ALL)
add_custom_command(
        TARGET sample_jar
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ant dist
        DEPENDS src/com/googlecode/hessianorb/sample/SampleService.java
)
