# $Id$

# Configure shell scripts.
configure_files(
        ${CMAKE_CURRENT_SOURCE_DIR}/template/bin
        ${EXECUTABLE_OUTPUT_PATH})

# Create JAR file.
add_custom_target(hessianc.jar ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ant dist
        COMMAND ${CMAKE_COMMAND} -E copy dist/hessianc.jar ${LIBRARY_OUTPUT_PATH}/hessianc.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/antlr.jar ${LIBRARY_OUTPUT_PATH}/antlr.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/stringtemplate.jar ${LIBRARY_OUTPUT_PATH}/stringtemplate.jar
)
