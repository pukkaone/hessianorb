// $Id$
package com.googlecode.hessianorb.sample;

import java.io.Serializable;

/**
 * Personal information
 */
public class Person implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private String firstName;
    private String lastName;
    private PostalAddress homeAddress;

    public Person(
            String firstName,
            String lastName,
            String street,
            String city,
            String province,
            String postalCode)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.homeAddress = new PostalAddress(street, city, province, postalCode);
    }
    
    public String getFirstName() {
        return firstName;
    }
    
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }
    
    public String getLastName() {
        return lastName;
    }
    
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public PostalAddress getHomeAddress() {
        return homeAddress;
    }

    public void setHomeAddress(PostalAddress homeAddress) {
        this.homeAddress = homeAddress;
    }
}
