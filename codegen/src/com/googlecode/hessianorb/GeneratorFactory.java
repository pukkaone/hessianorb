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
public class GeneratorFactory {
    private static final String LINE_SEPARATOR = System.getProperty("line.separator");
    private static final String HEADER_SUFFIX = ".h";
    private static final String SOURCE_SUFFIX = ".cpp";

    private String namespace;
    private File headerDir;
    private File sourceDir;

    public GeneratorFactory(
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
     * Constructs a header file name from a base name by prepending a directory
     * path and appending a file name extension.
     * 
     * @param baseName
     *            base file name
     * @return header file name
     */
    public String headerFileName(String baseName) {
        return getNamespace() + '/' + baseName + getHeaderSuffix();
    }

    /**
     * Constructs a guard macro name from base name.
     * 
     * @param baseName
     *            base name
     * @return guard macro name
     */
    public String guardName(String baseName) {
        String guard = headerFileName(baseName).toUpperCase();
        return guard.replaceAll("[^A-Z0-9_]", "_");
    }
    
    private String sourceFileName(String className) {
        return className + getSourceSuffix();
    }
    
    /**
     * Checks if the {@code Class} represents a byte array.
     */
    public boolean isByteArray(Class<?> clazz) {
        return clazz.isArray() && clazz.getComponentType() == Byte.TYPE;
    }

    @SuppressWarnings("unchecked")
    public Generator getGenerator(Type type) {
        if (type == Boolean.TYPE || type == Boolean.class) {
            return new PrimitiveGenerator("bool");
            
        } else if (type == Character.TYPE || type == Character.class
                || type == String.class)
        {
            return new ClassGenerator("std::string", "<string>");
            
        } else if (type == Byte.TYPE || type == Byte.class
                || type == Integer.TYPE || type == Integer.class
                || type == Short.TYPE || type == Short.class)
        {
            return new PrimitiveGenerator("hessian::Int");
            
        } else if (type == Double.TYPE || type == Double.class
                || type == Float.TYPE || type == Float.class)
        {
            return new PrimitiveGenerator("double");
            
        } else if (type == Long.TYPE || type == Long.class) {
            return new PrimitiveGenerator("hessian::Long");
            
        } else if (type == Void.TYPE) {
            return new PrimitiveGenerator("void");
            
        } else if (type instanceof ParameterizedType) {
            ParameterizedType pt = (ParameterizedType) type;  
            Type elementType = pt.getActualTypeArguments()[0];  
            return new ListGenerator(this, elementType);
            
        } else if (type instanceof Serializable) {
            Class<?> serializableClass = (Class<?>) type;

            if (isByteArray(serializableClass)) {
                return new ClassGenerator("hessian::Binary", null);
            }

            if (serializableClass.isEnum()) {
                return new EnumGenerator(
                        this, (Class<? extends Enum<?>>) serializableClass);
            }
            return new SerializableGenerator(this, serializableClass);

        } else {
            throw new GeneratorException("Cannot map type " + type + " to C++");
        }
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
            writer.write(LINE_SEPARATOR);
            writer.close();
        }
        catch (IOException e) {
            throw new GeneratorException(e);
        }
    }
    
    public void writeHeaderFile(String baseName, String content) {
        writeFile(getHeaderDir(), headerFileName(baseName), content);
    }
    
    public void writeSourceFile(String baseName, String content) {
        writeFile(getSourceDir(), sourceFileName(baseName), content);
    }
    
    /**
     * Generates code for the given Java type.
     * 
     * @param type
     *            type description
     * @param headers
     *            collection to which will be added any C++ header defining the
     *            mapped C++ type
     */
    public void generate(Type type, Headers headers) {
        Generator generator = getGenerator(type);
        generator.generate();
                
        String header = generator.getHeaderFileName();
        if (header != null) {
            headers.addHeader(header);
        }
    }
}
