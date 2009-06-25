// $Id$
package com.googlecode.hessianorb;

/**
 * Generates C++ parameter type as a const reference. 
 */
public abstract class AbstractClassGenerator implements Generator {

    public String getCppParameterType() {
        return "const " + getCppType() + '&';
    }
}
