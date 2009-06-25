// $Id$
package com.googlecode.hessianorb;

/**
 * Generates code from Java primitive type.
 */
public class PrimitiveGenerator implements Generator {

    private String cppType;
    
    public PrimitiveGenerator(String cppType) {
        this.cppType = cppType;
    }
            
    public String getCppType() {
        return cppType;
    }

    public String getCppParameterType() {
        return getCppType();
    }

    public void includeHeader(Headers headers) {
    }

    public void generate() {
    }
}
