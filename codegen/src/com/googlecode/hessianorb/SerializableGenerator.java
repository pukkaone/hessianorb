// $Id$
package com.googlecode.hessianorb;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for Hessian serializable class.
 */
public class SerializableGenerator extends AbstractClassGenerator {
    
    private GeneratorFactory config;
    private Class<?> serializableClass;
    private StringTemplateGroup group;
    
    public SerializableGenerator(
            GeneratorFactory config, Class<?> serializableClass)
    {
        this.config = config;
        this.serializableClass = serializableClass;
        
        group =  new StringTemplateGroup("serializableGroup");
    }

    // Generates C++ code for any serializable fields of the class.
    private void generateSerializableFields(Class<?> serializableClass, Headers headers) {
        Class<?> superClass = serializableClass.getSuperclass();
        if (superClass != null) {
            generateSerializableFields(superClass, headers);
        }
        
        for (Field field : serializableClass.getDeclaredFields()) {
            int modifiers = field.getModifiers();
            if (!Modifier.isStatic(modifiers)
             && !Modifier.isTransient(modifiers))
            {
                config.generate(field.getGenericType(), headers);
            }
        }
    }

    private void addFields(StringTemplate template, Class<?> serializableClass) {
        Class<?> superClass = serializableClass.getSuperclass();
        if (superClass != null) {
            addFields(template, superClass);
        }
        
        for (Field field : serializableClass.getDeclaredFields()) {
            int modifiers = field.getModifiers();
            if (!Modifier.isStatic(modifiers)
             && !Modifier.isTransient(modifiers))
            {
                Generator fieldGenerator = config.getGenerator(
                        field.getGenericType());
                template.setAttribute(
                        "dataMember",
                        new Parameter(
                                fieldGenerator.getCppType(),
                                field.getName()));
            }
        }
    }
    
    private StringTemplate getTemplate(
            String templateName,
            Class<?> serializableClass,
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
    
    private void generateHeader(Class<?> serializableClass, Headers headers) {
        String className = serializableClass.getSimpleName();
        
        StringTemplate serializableHeader = getTemplate(
                "serializableHeader", serializableClass, headers);
        serializableHeader.setAttribute("guard", config.guardName(className));
        
        String code = serializableHeader.toString();
        config.writeHeaderFile(className, code);
    }
    
    private void generateSource(Class<?> serializableClass) {
        String className = serializableClass.getSimpleName();

        Headers myHeaders = new Headers();
        myHeaders.addHeader(config.headerFileName(serializableClass.getSimpleName()));
        
        StringTemplate serializableSource = getTemplate(
                "serializableSource", serializableClass, myHeaders);
        
        String code = serializableSource.toString();
        config.writeSourceFile(className, code);
    }

    @Override
    public String getCppType() {
        return config.getNamespace() + "::" + serializableClass.getSimpleName();
    }

    @Override
    public void includeHeader(Headers headers) {
        headers.addHeader(
                config.headerFileName(serializableClass.getSimpleName()));
    }
    
    @Override
    public void generate() {
        Headers myHeaders = new Headers();
        myHeaders.addHeader("hessian/types.h");
        
        generateSerializableFields(serializableClass, myHeaders);
        
        generateHeader(serializableClass, myHeaders);

        generateSource(serializableClass);
    }
}
