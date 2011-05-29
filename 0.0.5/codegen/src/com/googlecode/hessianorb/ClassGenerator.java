// $Id$
package com.googlecode.hessianorb;

/**
 * Generates code for C++ class.
 */
public class ClassGenerator extends AbstractClassGenerator {

    private String cppType;
    private String headerFileName;

    /**
     * Constructor
     * 
     * @param cppType
     *            C++ type specifier
     * @param headerFileName
     *            C++ header file name which defines the C++ type
     */
    public ClassGenerator(String cppType, String headerFileName) {
        this.cppType = cppType;
        this.headerFileName = headerFileName;
    }
        
    @Override
    public String getCppType() {
        return cppType;
    }
    
    @Override
    public void includeHeader(Headers headers) {
        if (headerFileName != null) {
            headers.addHeader(headerFileName);
        }
    }

    @Override
    public void generate() {
    }
}
