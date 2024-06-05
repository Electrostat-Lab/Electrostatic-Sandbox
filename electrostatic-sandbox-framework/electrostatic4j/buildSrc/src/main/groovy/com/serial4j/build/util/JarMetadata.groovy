package com.serial4j.build.util;

public enum JarMetadata {
    BASE_NAME("serial4j"), VERSION("0.1-A"), EXT(".jar"), TARGET("desktop");
    
    String data;

    JarMetadata(final String data) {
        this.data = data;
    }

    public void setData(final String data) {
        this.data = data;
    }

    public String getData() {
        return data;
    }
}
