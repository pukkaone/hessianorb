// $Id$
package com.googlecode.hessianorb;

/**
 * Generates code from a Java type.
 */
public interface Generator {

    /**
     * Gets C++ type.
     * 
     * @return C++ type specifier
     */
    String getCppType();
    
    /**
     * Gets C++ type when used as a function parameter.
     * 
     * @return C++ type specifier
     */
    String getCppParameterType();
    
    /**
     * Adds any C++ header defining this C++ type to the header collection.
     * 
     * @param headers
     *            collection to which will be added any C++ header defining the
     *            C++ type
     */
    void includeHeader(Headers headers);
    
    /**
     * Generates code.
     */
    void generate();
}
