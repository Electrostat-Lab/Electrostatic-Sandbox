package com.serial4j.core.serial.throwable;

import com.serial4j.core.errno.Errno;

/**
 * An equivalent recoverable exception for the business native error
 * {@link Errno#ERR_OPERATION_FAILED}.
 *
 * @author pavl_g
 */
public final class OperationFailedException extends SerialThrowable {
    public OperationFailedException(String message) {
        super(message);
    }

    @Override
    public Errno getCausingErrno() {
        return Errno.ERR_OPERATION_FAILED;
    }
}
