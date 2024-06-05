package com.serial4j.build.actions;

import org.gradle.api.resources.MissingResourceException;
import com.serial4j.build.util.ConsoleUtils;
import com.serial4j.build.UnixScriptRunner;
import java.util.Arrays;
import java.util.ArrayList;
import java.lang.Process;
import org.gradle.api.Task;
import java.io.IOException;
import java.lang.InterruptedException;

/**
 * A task that executes a script and print its stream. 
 *
 * @author pavl_g 
 */
public final class ScriptExecutor {
   
    public void execute(Task task) {
        final UnixScriptRunner runner = ((UnixScriptRunner) task);
        if (runner.getScript() == null || runner.getScript().equals("")) {
            throw new MissingResourceException("Cannot find a script to execute !");
        }
        try {
            executeScript(runner.getScript(), (ArrayList<String>) Arrays.asList(runner.getScriptArgs()));
        } catch(IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void executeScript(final String script, final ArrayList<String> args) throws IOException, InterruptedException {
        ArrayList<String> command = new ArrayList<>();
        command.add(getBash());
        command.add(script);
        
        /* copy the args into the shell command */
        for (int i = 0; i < args.size(); i++) {
            command.add(args.get(i));
        }
        
        Process run = Runtime.getRuntime().exec((String[]) command.toArray());
        
        if (run.waitFor() == 1) {
            System.out.println("Run Failed !");
        }

        ConsoleUtils.printConsoleInput(run);
        ConsoleUtils.printConsoleError(run);

        /* release resources */
        run.destroy();
        run = null;
        command.clear();
        command = null;
    }
    
    /**
     * Retrieves the system specific bash binary.
     * 
     * @return a string representation of the bash (bourne-again-shell)
     */
    private String getBash() {
        if (!System.getProperty("os.name").contains("Windows")) {
            return "bash";
        }
        return "C:\\Program Files\\Git\\bin\\bash.exe";
    }

}
