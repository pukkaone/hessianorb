// $Id$
package com.googlecode.hessianorb;

import java.io.Serializable;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for Hessian serializable class.
 */
public class SerializableGenerator {
    private GeneratorConfig config;
    private StringTemplateGroup group;
    
    public SerializableGenerator(GeneratorConfig config) {
        this.config = config;
        
        group =  new StringTemplateGroup("serializableGroup");
    }

    // Generates C++ code for any serializable fields of the class.
    private void generateSerializableFields(Class serializableClass, Headers headers) {
        Class superClass = serializableClass.getSuperclass();
        if (superClass != null) {
            generateSerializableFields(superClass, headers);
        }
        
        for (Field field : serializableClass.getDeclaredFields()) {
            int modifiers = field.getModifiers();
            if (!Modifier.isStatic(modifiers)
             && !Modifier.isTransient(modifiers))
            {
                generate(field.getGenericType(), headers);
            }
        }
    }

    private void addFields(StringTemplate template, Class serializableClass) {
        Class superClass = serializableClass.getSuperclass();
        if (superClass != null) {
            addFields(template, superClass);
        }
        
        for (Field field : serializableClass.getDeclaredFields()) {
            int modifiers = field.getModifiers();
            if (!Modifier.isStatic(modifiers)
             && !Modifier.isTransient(modifiers))
            {
                template.setAttribute(
                        "dataMember",
                        new Parameter(
                                config.toCppType(field.getGenericType()),
                                field.getName()));
            }
        }
    }
    
    private StringTemplate getTemplate(
            String templateName,
            Class serializableClass,
            Headers headers)
    {
        String className = serializableClass.getSimpleName();
        
        StringTemplate template = group.getInstanceOf(templateName);
        template.setAttribute("headers", headers);
        template.setAttribute("namespace", config.getNamespace());
        template.setAttribute("class", className);
        template.setAttribute("javaClass", serializableClass.getName());
        addFields(template, serializableClass);
        return template;
    }
    
    private void generateHeader(Class serializableClass, Headers headers) {
        String className = serializableClass.getSimpleName();
        
        StringTemplate serializableHeader = getTemplate(
                "serializableHeader", serializableClass, headers);
        serializableHeader.setAttribute("guard", config.guardName(className));
        
        String code = serializableHeader.toString();
        config.writeHeaderFile(className, code);
    }
    
    private void generateSource(Class serializableClass) {
        String className = serializableClass.getSimpleName();

        Headers myHeaders = new Headers();
        myHeaders.addHeader(config.headerFileName(serializableClass.getSimpleName()));
        
        StringTemplate serializableSource = getTemplate(
                "serializableSource", serializableClass, myHeaders);
        
        String code = serializableSource.toString();
        config.writeSourceFile(className, code);
    }
    
    private void generate(Class serializableClass) {
        Headers myHeaders = new Headers();
        myHeaders.addHeader("hessian/types.h");
        
        generateSerializableFields(serializableClass, myHeaders);
        
        generateHeader(serializableClass, myHeaders);

        generateSource(serializableClass);
    }
    
    /**
     * If the type is a serializable class, generates the C++ code for it.
     * 
     * @param type
     *            type description
     * @param headers
     *            collection to which will be added any headers needed to use
     *            the serializable class
     */
    public void generate(Type type, Headers headers) {
        if (type == Boolean.TYPE
         || type == Character.TYPE
         || type == Double.TYPE
         || type == Float.TYPE
         || type == Integer.TYPE
         || type == Long.TYPE
         || type == String.class
         || type == Void.TYPE)
        {
            // do nothing
            
        } else if (type instanceof ParameterizedType) {
            ParameterizedType pt = (ParameterizedType) type;  
            Type elementType = pt.getActualTypeArguments()[0];
            
            ListGenerator generator = new ListGenerator(config);
            generator.generate(elementType);
            
            String header = config.headerFileName(config.listClassName(elementType));
            headers.addHeader(header);
        
        } else if (type instanceof Serializable) {
            Class serializableClass = (Class) type;
            if (config.isByteArray(serializableClass) == false) {
                generate(serializableClass);
                
                String header = config.headerFileName(serializableClass.getSimpleName());
                headers.addHeader(header);
            }
        }
    }
}
