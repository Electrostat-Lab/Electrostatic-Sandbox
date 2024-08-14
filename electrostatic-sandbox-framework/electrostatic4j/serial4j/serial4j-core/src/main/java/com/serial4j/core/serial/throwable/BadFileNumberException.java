package com.serial4j.core.serial.throwable;

import com.serial4j.core.errno.Errno;

public final class BadFileNumberException extends SerialThrowable {
    public BadFileNumberException(String message) {
        super(message);
    }

    @Override
    public Errno getCausingErrno() {
        return Errno.EBADF;
    }
}
