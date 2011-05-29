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
    
    /**
     * Constructor
     * 
     * @param javaMethod
     *            Java method definition
     * @param config
     *            generator factory
     * @param headers
     *            collection to which will be added any C++ header defining the
     *            mapped C++ type
     */
    public Function(Method javaMethod, GeneratorFactory config, Headers headers) {
        Generator returnGenerator = config.getGenerator(javaMethod.getGenericReturnType());
        
        returnType = returnGenerator.getCppType();
        config.generate(javaMethod.getGenericReturnType(), headers);
        
        name = javaMethod.getName();
        
        int parameterCount = 0;
        for (Type parameterType : javaMethod.getGenericParameterTypes()) {
            ++parameterCount;
            
            Generator parameterGenerator = config.getGenerator(parameterType);
            parameters.add(new Parameter(
                    parameterGenerator.getCppParameterType(),
                    "param" + parameterCount));
            
            config.generate(parameterType, headers);
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
