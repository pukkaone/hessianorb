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
     * Gets C++ header file name that defines this C++ type.
     * 
     * @return header file name, or {@code null} if this C++ type does not have
     *         a header file
     */
    String getHeaderFileName();
    
    /**
     * Generates code.
     */
    void generate();
}
