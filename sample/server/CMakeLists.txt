# $Id$

add_custom_target(sample.jar ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ant dist
        DEPENDS src/com/googlecode/hessianorb/sample/SampleService.java
)
