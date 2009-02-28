// $Id$
package com.googlecode.hessianorb;

import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.util.ArrayList;

/**
 * C++ function.
 */
public class Function {

    private String returnType;
    private String name;
    private ArrayList<Parameter> parameters = new ArrayList<Parameter>();
    
    public Function(Method javaMethod, GeneratorConfig config, Headers headers) {
        SerializableGenerator serializableGenerator =
                new SerializableGenerator(config);
        
        returnType = config.toCppType(javaMethod.getGenericReturnType());
        serializableGenerator.generate(javaMethod.getGenericReturnType(), headers);
        
        name = javaMethod.getName();
        
        int parameterCount = 0;
        for (Type parameterType : javaMethod.getGenericParameterTypes()) {
            ++parameterCount;
            parameters.add(new Parameter(
                    config.toCppParameterType(parameterType),
                    "param" + parameterCount));
            
            serializableGenerator.generate(parameterType, headers);
        }
    }

    public String getReturnType() {
        return returnType;
    }

    public String getName() {
        return name;
    }

    public ArrayList<Parameter> getParameters() {
        return parameters;
    }
}
