// $Id$
package com.googlecode.hessianorb;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.StringTokenizer;

/**
 * Allows setting a user class path while starting an application.
 */
public class Launcher {
    
    /** main class to run */
    private static final String MAIN_CLASS_NAME = Main.class.getName();

    /**
     * Converts classpath expression to list of URLs.
     * 
     * @param path
     *            classpath expression to parse
     * @return list of URLs
     */
    private URL[] getJarUrls(String path) throws MalformedURLException, FileNotFoundException {
        ArrayList<URL> urls = new ArrayList<URL>();
        
        StringTokenizer tokenizer = new StringTokenizer(path, File.pathSeparator);
        while (tokenizer.hasMoreElements()) {
            String elementName = tokenizer.nextToken();
            File file = new File(elementName);
            if (!file.exists()) {
                throw new FileNotFoundException(elementName + " not found");
            }
            
            urls.add(file.toURI().toURL());
        }
        
        return urls.toArray(new URL[urls.size()]);
    }

    /**
     * Processes command line arguments and launches application.
     * 
     * @param args
     *            the command line arguments
     * @throws MalformedURLException
     *             if the URLs required for the classloader cannot be created.
     */
    private void run(String[] args) throws MalformedURLException, FileNotFoundException {
        String classpathString = null;
        String mainClassName = MAIN_CLASS_NAME;
        
        ArrayList<String> filteredArgs = new ArrayList<String>();
        for (int i = 0; i < args.length; ++i) {
            if (args[i].equals("-classpath")) {
                if (i == args.length - 1) {
                    throw new RuntimeException(
                            "The -classpath option must be followed by a classpath expression.");
                }
                classpathString = args[++i];
            } else if (args[i].equals("-main")) {
                if (i == args.length - 1) {
                    throw new RuntimeException(
                            "The -main option must be followed by a class name.");
                }
                mainClassName = args[++i];
            } else {
                filteredArgs.add(args[i]);
            }
        }

        String[] newArgs = filteredArgs.toArray(new String[filteredArgs.size()]);

        // Create class loader for user specified classpath.
        ClassLoader loader;
        if (classpathString != null) {
            URL[] jars = getJarUrls(classpathString);
            loader = new URLClassLoader(jars);
            Thread.currentThread().setContextClassLoader(loader);
        } else {
            loader = Thread.currentThread().getContextClassLoader();
        }
        
        try {
            Class mainClass = loader.loadClass(mainClassName);
            Method mainMethod = mainClass.getMethod("main", newArgs.getClass());
            mainMethod.invoke(null, (Object) newArgs);
        }
        catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Main entry point
     * 
     * @param args
     *            command line arguments
     */
    public static void main(String[] args) {
        int exitCode = Main.EXIT_SUCCESS;
        try {
            Launcher launcher = new Launcher();
            launcher.run(args);
        }
        catch (Exception e) {
            exitCode = Main.EXIT_FAILURE;
            System.err.println(e.getMessage());
        }
        catch (Throwable t) {
            exitCode = Main.EXIT_FAILURE;
            t.printStackTrace(System.err);
        }
        
        if (exitCode != 0) {
            System.exit(exitCode);
        }
    }
}
