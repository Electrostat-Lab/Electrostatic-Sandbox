package com.serial4j.build;

import org.gradle.api.tasks.TaskAction;
import org.gradle.api.DefaultTask;
import org.gradle.api.tasks.Input;
import com.serial4j.build.actions.Permissioning;
import com.serial4j.build.actions.ScriptExecutor;

/**
 * The abstract entity for running unix scripts in bash shell environments.
 * It consists of 2 sequential tasks: a [permissioning] task and a [script-executor] task.
 * 
 * @author pavl_g
 */
public class UnixScriptRunner extends DefaultTask {

    /**
     * The unix script to execute.
     */
    @Input
    protected String script = "";

    @Input
    protected String[] scriptArgs;

    @TaskAction
    protected void scriptExecution() {
        final ScriptExecutor executor = new ScriptExecutor();
        executor.execute(this);
    }

    @TaskAction
    protected void permissioning() {
        final Permissioning permissioningTask = new Permissioning();
        permissioningTask.execute(this);
    }

    /**
     * Sets the unix-script to run.
     *
     * @param script a string representing the absolute path to the script ending with the script name and file extension
     */
    public void setScript(final String script) {
        this.script = script;
    }

    public final String getScript() {
        return script;
    }

    public void setScriptArgs(final String[] scriptArgs) {
        this.scriptArgs = scriptArgs;
    }

    public String[] getScriptArgs() {
        return scriptArgs;
    }
}
