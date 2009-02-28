// $Id$
package com.googlecode.hessianorb;

import java.lang.reflect.Method;
import org.antlr.stringtemplate.StringTemplate;
import org.antlr.stringtemplate.StringTemplateGroup;

/**
 * Generates C++ code for Hessian client proxy.
 */
public class ProxyGenerator {
    private static final String PROXY_SUFFIX = "Proxy";
    
    private GeneratorConfig config;
    private StringTemplateGroup group;
    private Headers headers = new Headers();
    
    public ProxyGenerator(
            String namespace, String headerDir, String sourceDir)
    {
        config = new GeneratorConfig(namespace, headerDir, sourceDir);
        group =  new StringTemplateGroup("proxyGroup");
        headers.addHeader("hessian/types.h");
    }

    private StringTemplate getTemplate(
            String templateName, Class interfaceClass, Headers headers)
    {
        String interfaceName = interfaceClass.getSimpleName();
        
        StringTemplate template = group.getInstanceOf(templateName);
        template.setAttribute("headers", headers);
        template.setAttribute("namespace", config.getNamespace());
        template.setAttribute("interface", interfaceName);

        for (Method method : interfaceClass.getMethods()) {
            template.setAttribute(
                    "function", new Function(method, config, headers));
        }
        return template;
    }
    
    private void generateInterfaceHeader(Class interfaceClass) {
        String interfaceName = interfaceClass.getSimpleName();

        StringTemplate interfaceHeader = getTemplate(
                "interfaceHeader", interfaceClass, headers);
        interfaceHeader.setAttribute("guard", config.guardName(interfaceName));
        
        String code = interfaceHeader.toString();
        config.writeHeaderFile(interfaceName, code);
    }
    
    private void generateProxyHeader(Class interfaceClass) {
        String interfaceName = interfaceClass.getSimpleName();
        String className = interfaceName + PROXY_SUFFIX;
        
        Headers myHeaders = new Headers(headers);
        myHeaders.addHeader(config.headerFileName(interfaceName));
        
        StringTemplate proxyHeader = getTemplate(
                "proxyHeader", interfaceClass, myHeaders);
        proxyHeader.setAttribute("guard", config.guardName(className));
        proxyHeader.setAttribute("class", className);
        
        String code = proxyHeader.toString();
        config.writeHeaderFile(className, code);
    }
    
    private void generateProxySource(Class interfaceClass) {
        String interfaceName = interfaceClass.getSimpleName();
        String className = interfaceName + PROXY_SUFFIX;
        
        Headers myHeaders = new Headers();
        myHeaders.addHeader(config.headerFileName(className));
        
        StringTemplate proxySource = getTemplate(
                "proxySource", interfaceClass, myHeaders);
        proxySource.setAttribute("class", className);
        
        String code = proxySource.toString();
        config.writeSourceFile(className, code);
    }
    
    public void generate(Class remoteInterface) {
        config.createGeneratedDirectories();
        generateInterfaceHeader(remoteInterface);
        generateProxyHeader(remoteInterface);
        generateProxySource(remoteInterface);
    }
}
