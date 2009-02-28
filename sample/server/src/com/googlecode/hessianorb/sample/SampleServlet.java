// $Id$
package com.googlecode.hessianorb.sample;

import com.caucho.hessian.server.HessianServlet;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.mortbay.jetty.Server;
import org.mortbay.jetty.servlet.Context;
 
public class SampleServlet extends HessianServlet implements SampleService {
    private static final long serialVersionUID = 1L;

    public SampleServlet() {
        setDebug(true);
    }
    
    private static final List<User> USERS = Arrays.asList(
            new User(1, "Bruce", "Banner", "1 Alpha", "Alphaville", "AA", "A1A1A1"),
            new User(2, "Johnny", "Storm", "2 Bravo", "Bravoville", "BB", "B2B2B2"),
            new User(3, "Reed", "Richards", "3 Charlie", "Charlieville", "CC", "C3C3C3")); 
    
    @Override
    public boolean echoBoolean(boolean value) {
        return value;
    }

    @Override
    public List<Boolean> echoBooleanList(List<Boolean> value) {
        return value;
    }
    
    @Override
    public char echoChar(char value) {
        return value;
    }

    @Override
    public List<Character> echoCharList(List<Character> value) {
        return value;
    }
    
    @Override
    public int echoInt(int value) {
        return value;
    }

    @Override
    public List<Integer> echoIntList(List<Integer> value) {
        return value;
    }

    @Override
    public String echoString(String value) {
        return value;
    }

    @Override
    public List<String> echoStringList(List<String> value) {
        return value;
    }

    @Override
    public User echoUser(User user) {
        return user;
    }

    @Override
    public List<User> echoUserList(List<User> users) {
        return users;
    }

    @Override
    public List<User> findUsers(String firstName, String lastName) {
        ArrayList<User> users = new ArrayList<User>();
        for (User user : USERS) {
            if (firstName != null
             && firstName.length() > 0
             && !user.getFirstName().equals(firstName))
            {
                continue;
            }
            
            if (lastName != null
             && lastName.length() > 0
             && !user.getLastName().equals(lastName))
            {
               continue;
            }
            
            users.add(user);
        }
        return users;
    }

    @Override
    public User getUser(int id) {
        for (User user : USERS) {
            if (user.getId() == id) {
                return user;
            }
        }
        return null;
    }

    public static void main (String [] args) throws Exception {
        Server server = new Server(8888);  
        Context context = new Context(server, "/", Context.SESSIONS);
        context.addServlet(SampleServlet.class, "/sample/remoting/SampleService");
        server.start();
    }
}
