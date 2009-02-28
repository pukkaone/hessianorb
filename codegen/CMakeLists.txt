# $Id$

# Configure shell scripts.
configure_files(
        ${CMAKE_CURRENT_SOURCE_DIR}/template/bin
        ${EXECUTABLE_OUTPUT_PATH})

add_custom_target(hessianc_jar ALL)

add_custom_command(
        TARGET hessianc_jar
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ant dist
        COMMAND ${CMAKE_COMMAND} -E copy dist/hessianc.jar ${LIBRARY_OUTPUT_PATH}/hessianc.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/antlr.jar ${LIBRARY_OUTPUT_PATH}/antlr.jar
        COMMAND ${CMAKE_COMMAND} -E copy lib/stringtemplate.jar ${LIBRARY_OUTPUT_PATH}/stringtemplate.jar
)
