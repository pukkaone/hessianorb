// $Id$
package com.googlecode.hessianorb;

/**
 * C++ function parameter.
 */
public class Parameter {
   
    private String type;
    private String name;
    
    public Parameter(String type, String name) {
        this.type = type;
        this.name = name;
    }
    
    public String getType() {
        return type;
    }
    
    public String getName() {
        return name;
    }
    
    public String toString() {
        return type + ' ' + name;
    }
}
