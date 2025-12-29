package com.serial4j.core.serial.throwable;

import com.serial4j.core.errno.Errno;

public class FileTooLargeException extends SerialThrowable {
    
    public FileTooLargeException(final String additionalText) {
        super(additionalText);
    }
    
    @Override
    public Errno getCausingErrno() {
        return Errno.EFBIG;
    }
}