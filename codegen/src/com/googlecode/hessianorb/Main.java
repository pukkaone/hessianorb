// $Id$
package com.googlecode.hessianorb;

/**
 * Code generator main entry point
 */
public class Main {

    private static final String OPTION_HEADER_DEST = "-header-dest";
    private static final String OPTION_SOURCE_DEST = "-source-dest";

    /** exit code on success */
    public static final int EXIT_SUCCESS = 0;

    /** exit code on error */
    public static final int EXIT_FAILURE = 1;

    private void usage() {
        System.out.println(
                "usage: hessianc [options] <namespace> <javaInterface>...\n" +
                "\n" +
                "options:\n" +
                "\n" +
                OPTION_HEADER_DEST + " <directory>\n" +
                "    Specify directory where C++ header files will be generated.\n" +
                "    Default is the current working directory.\n" +
                "\n" +
                OPTION_SOURCE_DEST + " <directory>\n" +
                "    Specify directory where C++ source files will be generated.\n" +
                "    Default is the current working directory.\n");
    }
    
    private void run(String[] args) {
        String headerDestDir = ".";
        String sourceDestDir = ".";
        
        int i = 0;
        for (; i < args.length; ++i) {
            if (args[i].equals(OPTION_HEADER_DEST)) {
                if (i == args.length - 1) {
                    throw new RuntimeException(
                            OPTION_HEADER_DEST + " option must be followed by a directory name.");
                }
                headerDestDir = args[++i];
            } else if (args[i].equals(OPTION_SOURCE_DEST)) {
                if (i == args.length - 1) {
                    throw new RuntimeException(
                            OPTION_SOURCE_DEST + " option must be followed by a directory name.");
                }
                sourceDestDir = args[++i];
            } else if (args[i].startsWith("-")) {
                usage();
                return;
            } else {
                break;
            }
        }

        if (args.length - i < 2) {
            usage();
            return;
        }
        
        String namespace = args[i++];

        ProxyGenerator generator =
                new ProxyGenerator(namespace, headerDestDir, sourceDestDir);
        for (; i < args.length; ++i) {
            try {
                Class<?> remoteInterface =
                        Thread.currentThread().getContextClassLoader().loadClass(args[i]);
                generator.generate(remoteInterface);
            }
            catch (ClassNotFoundException e) {
                throw new RuntimeException(e);
            }
        }
    }
    
    /**
     * Main entry point
     * 
     * @param args
     *            command line arguments
     */
    public static void main(String[] args) {
        int exitCode = EXIT_SUCCESS;
        try {
            Main application = new Main();
            application.run(args);
        }
        catch (RuntimeException e) {
            exitCode = EXIT_FAILURE;
            String message = e.getMessage();
            if (message == null) {
                message = e.toString();
            }
            System.err.println(message);
        }
        catch (Throwable t) {
            exitCode = EXIT_FAILURE;
            t.printStackTrace(System.err);
        }
        
        if (exitCode != 0) {
            System.exit(exitCode);
        }
    }
}
