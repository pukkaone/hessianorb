// $Id$
package com.googlecode.hessianorb.sample;

import java.io.Serializable;

/**
 * Postal address
 */
public class PostalAddress implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private String street;
    private String city;
    private String province;
    private String postalCode;
    
    public PostalAddress(
            String street,
            String city,
            String province,
            String postalCode)
    {
        this.street = street;
        this.city = city;
        this.province = province;
        this.postalCode = postalCode;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getProvince() {
        return province;
    }

    public void setProvince(String province) {
        this.province = province;
    }

    public String getPostalCode() {
        return postalCode;
    }

    public void setPostalCode(String postalCode) {
        this.postalCode = postalCode;
    }
}
