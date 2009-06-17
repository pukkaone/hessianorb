// $Id$
package com.googlecode.hessianorb;

import java.lang.reflect.Type;
import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for Hessian list.
 */
public class ListGenerator {
    /** C++ container used to represent Hessian list */
    public static final String CONTAINER = "std::vector";
    
    /** header file for C++ container used to represent Hessian list */
    private static final String CONTAINER_HEADER = "vector";
    
    private GeneratorConfig config;
    private StringTemplateGroup group;
    
    public ListGenerator(GeneratorConfig config) {
        this.config = config;
        
        group =  new StringTemplateGroup("listGroup");
    }

    private StringTemplate getTemplate(String templateName, Headers headers) {
        StringTemplate template = group.getInstanceOf(templateName);
        template.setAttribute("headers", headers);
        template.setAttribute("namespace", config.getNamespace());
        return template;
    }
    
    private void addElementHeader(Headers headers, Type elementType) {
        if (config.isCppPrimitive(elementType)) {
            return;
        }
        if (elementType == Character.class || elementType == String.class) {
            headers.addStandardHeader("string");
        } else {
            Class<?> elementClass = (Class<?>) elementType;
            headers.addHeader(config.headerFileName(elementClass.getSimpleName()));
        }
    }
    
    private void generateHeader(Type elementType) {
        String className = config.listClassName(elementType);
        String cppElementType = config.toCppType(elementType);
        String cppContainerType = config.toCppContainerType(elementType);

        Headers headers = new Headers();
        addElementHeader(headers, elementType);
        headers.addStandardHeader(CONTAINER_HEADER);
        
        StringTemplate header = getTemplate("listHeader", headers);
        header.setAttribute("guard", config.guardName(className));
        header.setAttribute("elementType", cppElementType);
        header.setAttribute("containerType", cppContainerType);
        
        String code = header.toString();
        config.writeHeaderFile(className, code);
    }

    /**
     * Generates C++ code for Hessian list.
     * 
     * @param elementType
     *            list element Java type
     */
    public void generate(Type elementType) {
        generateHeader(elementType);
    }
}
