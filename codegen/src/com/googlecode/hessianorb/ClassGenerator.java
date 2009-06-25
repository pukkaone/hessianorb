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
            
    public String getCppType() {
        return cppType;
    }
    
    public String getHeaderFileName() {
        return headerFileName;
    }

    public void generate() {
    }
}
