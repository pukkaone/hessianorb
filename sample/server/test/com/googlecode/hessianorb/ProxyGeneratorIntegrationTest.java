// $Id$
package com.googlecode.hessianorb;

import org.junit.Test;

public class ProxyGeneratorIntegrationTest {

    @Test
    public void testGenerateProxy() {
        final String GENERATED_DIR =
                "/branches/release/cpp/hessianorb/sample/cpp/test/generated/";
        ProxyGenerator generator = new ProxyGenerator(
                "sample", GENERATED_DIR + "include", GENERATED_DIR + "src");
        
        generator.generate(com.googlecode.hessianorb.sample.SampleService.class);
    }
}
