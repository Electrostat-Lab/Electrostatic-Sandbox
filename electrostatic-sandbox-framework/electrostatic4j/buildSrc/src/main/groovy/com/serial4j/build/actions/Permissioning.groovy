package com.serial4j.build.actions;

import org.gradle.api.resources.MissingResourceException;
import com.serial4j.build.util.ConsoleUtils;
import com.serial4j.build.UnixScriptRunner;
import java.lang.Process;
import org.gradle.api.Task;
import java.io.IOException;
import java.lang.InterruptedException;

/**
 * A task that gives a [+rwx] permission to a script.
 *
 * @author pavl_g
 */
public final class Permissioning {
    
    public void execute(Task task) {
        final UnixScriptRunner runner = ((UnixScriptRunner) task);
        if (runner.getScript() == null || runner.getScript().equals("")) {
            throw new MissingResourceException("Cannot find a script to permissionize !");
        }
        try {
            permissionizeScript(runner.getScript());
        } catch(IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void permissionizeScript(final String script) throws IOException, InterruptedException {
        String[] chmod = new String[] { "chmod", "+rwx" };
        /* execute the shell script in a unix process that inheirt from the current environment */
        Process permissioning = Runtime.getRuntime().exec(new String[] { chmod[0], chmod[1], script });

        permissioning.waitFor();

        ConsoleUtils.printConsoleInput(permissioning);
        ConsoleUtils.printConsoleError(permissioning);
        
        /* release resources */
        permissioning.destroy(); 
        permissioning = null;
        chmod = null;
    }
}
