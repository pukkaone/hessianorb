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
     * Adds header file name.  If the name is surrounded by angle brackets,
     * adds the name exactly as given to the collection, otherwise surrounds
     * the name with quotes before adding to the collection.
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
}
