// $Id$
package com.googlecode.hessianorb;

/**
 * Exception thrown when code generator fails.
 */
public class GeneratorException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    public GeneratorException(Throwable cause) {
        super(cause);
    }
    
    public GeneratorException(String message) {
        super(message);
    }
}
