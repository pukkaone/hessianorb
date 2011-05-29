// $Id$
package com.googlecode.hessianorb.sample;

import java.io.Serializable;

/**
 * User information
 */
public class User extends Person implements Serializable {
    private static final long serialVersionUID = 1L;

    private long id;

    public User(
            long id,
            String firstName,
            String lastName,
            String street,
            String city,
            String province,
            String postalCode)
    {
        super(firstName, lastName, street, city, province, postalCode);
        this.id = id;
    }
    
    public long getId() {
        return id;
    }
    
    public void setId(long id) {
        this.id = id;
    }
}
