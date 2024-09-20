package com.serial4j.core.filesystem;

public final class AbstractFilesystem {
    private AbstractFilesystem() {
    }

    /**
     * Tests whether a port filesystem exists.
     *
     * @param port the port to test.
     * @return (1) if the device on this port exists, (0) otherwise.
     */
    public static native int isExistential(String port);
}
