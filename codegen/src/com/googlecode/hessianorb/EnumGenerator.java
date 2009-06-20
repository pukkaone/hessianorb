// $Id$
package com.googlecode.hessianorb;

import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for enum.
 */
public class EnumGenerator {
    
    private GeneratorConfig config;
    private StringTemplateGroup group;
    
    public EnumGenerator(GeneratorConfig config) {
        this.config = config;
        
        group =  new StringTemplateGroup("enumGroup");
    }

    private StringTemplate getTemplate(
            String templateName,
            Class<? extends Enum<?>> enumClass,
            Headers headers)
    {
        StringTemplate template = group.getInstanceOf(templateName);
        template.setAttribute("headers", headers);
        template.setAttribute("namespace", config.getNamespace());
        template.setAttribute("class", enumClass.getSimpleName());
        for (Enum<?> constant : enumClass.getEnumConstants()) {
            template.setAttribute("enumerator", constant.name());
        }
        return template;
    }
    
    private void generateHeader(Class<? extends Enum<?>> enumClass) {
        String enumName = enumClass.getSimpleName();
        
        StringTemplate header = getTemplate("enumHeader", enumClass, new Headers());
        header.setAttribute("guard", config.guardName(enumName));
        
        String code = header.toString();
        config.writeHeaderFile(enumName, code);
    }
    
    private void generateSource(Class<? extends Enum<?>> enumClass) {
        String enumName = enumClass.getSimpleName();

        Headers myHeaders = new Headers();
        myHeaders.addHeader(config.headerFileName(enumName));
        
        StringTemplate source = getTemplate("enumSource", enumClass, myHeaders);
        source.setAttribute("javaClass", enumClass.getName());
        
        String code = source.toString();
        config.writeSourceFile(enumName, code);
    }

    /**
     * Generates C++ code for Hessian list.
     * 
     * @param enumClass
     *            enum description
     */
    public void generate(Class<? extends Enum<?>> enumClass) {
        generateHeader(enumClass);
        generateSource(enumClass);
    }
}
