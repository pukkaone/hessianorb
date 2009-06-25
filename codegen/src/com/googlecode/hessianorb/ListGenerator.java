// $Id$
package com.googlecode.hessianorb;

import java.lang.reflect.Type;
import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for Hessian list.
 */
public class ListGenerator extends AbstractClassGenerator {
    
    /** C++ container used to represent Hessian list */
    private static final String CONTAINER = "std::vector";
    
    /** header file for C++ container used to represent Hessian list */
    private static final String CONTAINER_HEADER = "vector";
    
    private GeneratorFactory config;
    private Type elementType;
    private Generator elementGenerator;
    private StringTemplateGroup group;
    
    /**
     * Constructor
     * 
     * @param config
     *            generator factory
     * @param elementType
     *            list element Java type
     */
    public ListGenerator(GeneratorFactory config, Type elementType) {
        this.config = config;
        this.elementType = elementType;
        this.elementGenerator = config.getGenerator(elementType);
        
        group =  new StringTemplateGroup("listGroup");
    }

    private StringTemplate getTemplate(String templateName, Headers headers) {
        StringTemplate template = group.getInstanceOf(templateName);
        template.setAttribute("headers", headers);
        template.setAttribute("namespace", config.getNamespace());
        return template;
    }

    private String capitalize(String name) {
        return name.substring(0, 1).toUpperCase() + name.substring(1);
    }
    
    private String getHeaderFileBaseName() {
        String baseName = getCppElementType();
        String[] parts = baseName.split("::");
        return capitalize(parts[parts.length - 1]) + "List";
    }

    private String getCppElementType() {
        return config.getGenerator(elementType).getCppType();
    }
    
    private void generateHeader() {
        String headerFileBaseName = getHeaderFileBaseName();
        String cppElementType = getCppElementType();
        String cppContainerType = getCppType();

        Headers headers = new Headers();
        String elementHeader = elementGenerator.getHeaderFileName(); 
        if (elementHeader != null) {
            headers.addHeader(elementHeader);
        }
        headers.addStandardHeader(CONTAINER_HEADER);
        
        StringTemplate header = getTemplate("listHeader", headers);
        header.setAttribute("guard", config.guardName(headerFileBaseName));
        header.setAttribute("elementType", cppElementType);
        header.setAttribute("containerType", cppContainerType);
        
        String code = header.toString();
        config.writeHeaderFile(headerFileBaseName, code);
    }

    @Override
    public String getCppType() {
        Generator elementGenerator = config.getGenerator(elementType);
        return CONTAINER + '<' + elementGenerator.getCppType() + '>';
    }
    
    @Override
    public String getHeaderFileName() {
        return config.headerFileName(getHeaderFileBaseName());
    }
    
    @Override
    public void generate() {
        generateHeader();
    }
}
