package com.serial4j.build;

import org.gradle.api.DefaultTask;
import org.gradle.api.tasks.Input;

/**
 * Compiles a x86 binary to a specific system.
 *
 * @author pavl_g
 */
public class CompileX86 extends UnixScriptRunner {

    /** Placeholders for gradle properties */
    @Input
    protected String compileWindowsX86 = "";
    
    @Input
    protected String compileMacX86 = "";
    
    @Input
    protected String compileLinuxX86 = "";

    protected final boolean isWindows = System.getProperty("os.name").contains("Windows");
    protected final boolean isMacos = System.getProperty("os.name").contains("Mac");
    protected final boolean isLinux = System.getProperty("os.name").contains("Linux");

    @Override
    protected void scriptExecution() {
        boolean isCompileWindowsX86 = getConditionFromValue(compileWindowsX86);
        boolean isCompileMacX86 = getConditionFromValue(compileMacX86);
        boolean isCompileLinuxX86 = getConditionFromValue(compileLinuxX86);

        if (isWindows && !isCompileWindowsX86) {
            /* terminate when on windows if the compile flag is disabled */
            return;    
        } 
        
        if (isMacos && !isCompileMacX86) {
            /* terminate when on MacOS if the compile flag is disabled */
            return;    
        } 
        
        if (isLinux && !isCompileLinuxX86) {
            /* terminate when on linux if the compile flag is disabled */
            return;
        }

        super.scriptExecution();
    }

    private boolean getConditionFromValue(final String value) {
        return value.equals("true");
    }

    public String getCompileLinuxX86() {
        return compileLinuxX86;
    }

    public String getCompileWindowsX86() {
        return compileWindowsX86;
    }

    public String getCompileMacX86() {
        return compileMacX86;
    }

}
