// $Id$
package com.googlecode.hessianorb;

import java.util.TreeSet;

/**
 * Set of header file names.
 */
public class Headers extends TreeSet<String> {
    private static final long serialVersionUID = 1L;

    public Headers() {
    }
    
    /**
     * Constructs copy of headers
     * 
     * @param right
     *            headers to copy
     */
    public Headers(Headers right) {
        addAll(right);
    }
    
    /**
     * Adds header file name.
     * 
     * @param name
     *            header file name.
     */
    public void addHeader(String name) {
        if (name.startsWith("<")) {
            add(name);
        } else {
            add('"' + name + '"');
        }
    }
    
    /**
     * Adds system-defined header file name.
     * 
     * @param name
     *            header file name.
     */
    public void addStandardHeader(String name) {
        add('<' + name + '>');
    }
}
