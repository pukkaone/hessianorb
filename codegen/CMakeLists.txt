# $Id$

# Configure shell scripts.
configure_files(
        ${CMAKE_CURRENT_SOURCE_DIR}/template/bin
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Create JAR file.
add_custom_target(hessianc.jar ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ant dist
        COMMAND ${CMAKE_COMMAND} -E copy dist/hessianc.jar ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/hessianc.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/antlr.jar ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/antlr.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/stringtemplate.jar ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/stringtemplate.jar
)
