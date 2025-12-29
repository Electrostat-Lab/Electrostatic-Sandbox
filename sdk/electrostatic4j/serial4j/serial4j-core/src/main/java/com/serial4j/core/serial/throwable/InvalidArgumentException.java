package com.serial4j.core.serial.throwable;

import com.serial4j.core.errno.Errno;

public class InvalidArgumentException extends SerialThrowable {
    
    public InvalidArgumentException(final String additionalText) {
        super(additionalText);
    }
    
    @Override
    public Errno getCausingErrno() {
        return Errno.EINVAL;
    }
}