package com.serial4j.build.util;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.lang.Process;

/**
 * Some useful console io utils to provide log errors and info.
 * 
 * @author pavl_g
 */
public final class ConsoleUtils {
    private ConsoleUtils() {
    }

    /**
     * Prints the process input-stream to the [stdout].
     * 
     * @param process a {@link java.lang.Process} process
     */
    public static void printConsoleInput(final Process process) {
        try {
            printInputStream(process.getInputStream(), System.out);
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Prints the process input-stream to the [stderr].
     * 
     * @param process a {@link java.lang.Process} process
     */
    public static void printConsoleError(final Process process) {
        try {
            printInputStream(process.getErrorStream(), System.err);
        } catch(IOException e) {
            e.printStackTrace();
        }    
    }

    /**
     * Prints an input-stream content to a stream [e.g: stdout, stderr].
     * 
     * @param in an input-stream to print its content
     * @param stream an output-stream to print on it
     */
    public static int printInputStream(final InputStream in, final PrintStream stream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(in));
        try {
            for (String out = null; (out = reader.readLine()) != null;) {
                stream.println(out);
            }
        } finally {
            reader.close();
            in.close();
            reader = null;
        }
        return 0;
    }
}
