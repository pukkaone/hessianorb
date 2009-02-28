// $Id$
package com.googlecode.hessianorb.sample;

import java.util.List;

/**
 * Test service interface
 */
public interface SampleService {
    boolean echoBoolean(boolean value);
    List<Boolean> echoBooleanList(List<Boolean> value);
    
    char echoChar(char value);
    List<Character> echoCharList(List<Character> value);
    
    int echoInt(int value);
    List<Integer> echoIntList(List<Integer> value);
    
    String echoString(String value);
    List<String> echoStringList(List<String> value);
    
    User echoUser(User user);
    List<User> echoUserList(List<User> users);
    
    List<User> findUsers(String firstName, String lastName);
    User getUser(int id);
}
