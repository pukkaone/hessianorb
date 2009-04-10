// $Id$
package com.googlecode.hessianorb;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Serializable;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;

/**
 * Controls details of how code is generated based on configuration settings. 
 */
public class GeneratorConfig {
    private static final String NEWLINE = System.getProperty("line.separator");
    private static final String HEADER_SUFFIX = ".h";
    private static final String SOURCE_SUFFIX = ".cpp";

    private String namespace;
    private File headerDir;
    private File sourceDir;

    public GeneratorConfig(
            String namespace, String headerDir, String sourceDir)
    {
        this.namespace = namespace;
        this.headerDir = new File(headerDir);
        this.sourceDir = new File(sourceDir);
    }
    
    private String getHeaderSuffix() {
        return HEADER_SUFFIX;
    }
    
    private String getSourceSuffix() {
        return SOURCE_SUFFIX;
    }

    public String getNamespace() {
        return namespace;
    }

    private File getHeaderDir() {
        return headerDir;
    }

    private File getSourceDir() {
        return sourceDir;
    }
    
    /**
     * Constructs a header file name based on a class name.
     * 
     * @param className
     *            base class name
     * @return header file name
     */
    public String headerFileName(String className) {
        return getNamespace() + '/' + className + getHeaderSuffix();
    }

    /**
     * Constructs a guard macro name based on a class name.
     * 
     * @param className
     *            base class name
     * @return guard macro name
     */
    public String guardName(String className) {
        String guard = headerFileName(className).toUpperCase();
        return guard.replaceAll("[^A-Z]", "_");
    }
    
    private String sourceFileName(String className) {
        return className + getSourceSuffix();
    }

    private String capitalize(String name) {
        return name.substring(0, 1).toUpperCase() + name.substring(1);
    }
    
    public String listClassName(Type elementType) {
        String baseName = toCppType(elementType);
        String[] parts = baseName.split("::");
        return capitalize(parts[parts.length - 1]) + "List";
    }
    
    public String listHeaderFileName(Type elementType) {
        return headerFileName(listClassName(elementType));
    }
    
    public String toCppContainerType(Type elementType) {
        return ListGenerator.CONTAINER + '<' + toCppType(elementType) + '>';
    }
    
    /**
     * Checks if the {@code Class} represents a byte array.
     */
    public boolean isByteArray(Class clazz) {
        return clazz.isArray() && clazz.getComponentType() == Byte.TYPE;
    }

    public String toCppType(Type type) {
        if (type == Boolean.TYPE || type == Boolean.class) {
            return "bool";
            
        } else if (type == Character.TYPE || type == Character.class
                || type == String.class)
        {
            return "std::string";
            
        } else if (type == Byte.TYPE || type == Byte.class
                || type == Integer.TYPE || type == Integer.class
                || type == Short.TYPE || type == Short.class)
        {
            return "hessian::Int";
            
        } else if (type == Double.TYPE || type == Double.class
                || type == Float.TYPE || type == Float.class)
        {
            return "double";
            
        } else if (type == Long.TYPE || type == Long.class) {
            return "hessian::Long";
            
        } else if (type == Void.TYPE) {
            return "void";
            
        } else if (type instanceof ParameterizedType) {
            ParameterizedType pt = (ParameterizedType) type;  
            Type elementType = pt.getActualTypeArguments()[0];  
            return toCppContainerType(elementType);
            
        } else if (type instanceof Serializable) {
            Class serializableClass = (Class) type;
            if (isByteArray(serializableClass)) {
                return "hessian::Binary";
            }
            return getNamespace() + "::" + serializableClass.getSimpleName();
            
        } else {
            throw new GeneratorException("Cannot map type " + type + " to C++");
        }
    }

    /**
     * Checks if the Java type maps to a C++ primitive type.
     * 
     * @param type
     *            Java type
     * @return true if type is primitive
     */
    public boolean isCppPrimitive(Type type) {
        return type == Boolean.TYPE || type == Boolean.class
            || type == Double.TYPE || type == Double.class
            || type == Float.TYPE || type == Float.class
            || type == Integer.TYPE || type == Integer.class
            || type == Long.TYPE || type == Long.class
            || type == Short.TYPE || type == Short.class;
    }

    /**
     * Maps Java type to C++ parameter type.
     * 
     * @param type
     *            Java type
     * @return C++ type specifier
     */
    public String toCppParameterType(Type type) {
        if (isCppPrimitive(type)) {
            return toCppType(type);
        }
        
        return "const " + toCppType(type) + '&';
    }

    public void createGeneratedDirectories() {
        File headerPath = new File(getHeaderDir(), getNamespace());
        headerPath.mkdirs();
        
        getSourceDir().mkdirs();
    }

    private void writeFile(File directory, String name, String content) {
        File file = new File(directory, name);
        try {
            FileWriter writer = new FileWriter(file);
            writer.write(content);
            writer.write(NEWLINE);
            writer.close();
        }
        catch (IOException e) {
            throw new GeneratorException(e);
        }
    }
    
    public void writeHeaderFile(String className, String content) {
        writeFile(getHeaderDir(), headerFileName(className), content);
    }
    
    public void writeSourceFile(String className, String content) {
        writeFile(getSourceDir(), sourceFileName(className), content);
    }
}
