// $Id$
package com.googlecode.hessianorb.sample;

import java.util.List;
import java.util.Map;

/**
 * Sample service interface used for testing.
 */
public interface SampleService {
    byte[] echoBinary(byte[] value);

    boolean echoBoolean(boolean value);
    List<Boolean> echoBooleanList(List<Boolean> value);
    
    char echoChar(char value);
    List<Character> echoCharList(List<Character> value);
    
    Season echoEnum(Season value);
    List<Season> echoEnumList(List<Season> value);
    
    int echoInt(int value);
    List<Integer> echoIntList(List<Integer> value);
    
    String echoString(String value);
    List<String> echoStringList(List<String> value);

    Map<String, String> echoMap(Map<String, String> map);
    
    User echoUser(User user);
    List<User> echoUserList(List<User> users);
    
    List<User> findUsers(String firstName, String lastName);
    User getUser(int id);
}
