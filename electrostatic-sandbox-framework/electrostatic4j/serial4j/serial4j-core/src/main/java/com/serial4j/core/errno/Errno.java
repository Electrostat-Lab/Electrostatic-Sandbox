/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package com.serial4j.core.errno;

import com.serial4j.core.serial.throwable.BadFileDescriptorException;
import com.serial4j.core.serial.throwable.BadFileNumberException;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.FileAlreadyOpenedException;
import com.serial4j.core.serial.throwable.FileIsDirectoryException;
import com.serial4j.core.serial.throwable.FileTableOverflowException;
import com.serial4j.core.serial.throwable.FileTooLargeException;
import com.serial4j.core.serial.throwable.IllegalSeekException;
import com.serial4j.core.serial.throwable.InputOutputException;
import com.serial4j.core.serial.throwable.InterruptedSystemCallException;
import com.serial4j.core.serial.throwable.InvalidArgumentException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoAvailableTtyDevicesException;
import com.serial4j.core.serial.throwable.NoSpaceLeftException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.NoSuchFileException;
import com.serial4j.core.serial.throwable.NotTtyDeviceException;
import com.serial4j.core.serial.throwable.OperationFailedException;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.core.serial.throwable.ReadOnlyFileSystemException;
import com.serial4j.core.serial.throwable.SerialThrowable;
import com.serial4j.core.serial.throwable.TooManyOpenedFilesException;
import com.serial4j.core.serial.throwable.TryAgainException;

/**
 * Interprets the native methods bad return values into error codes,
 * used by the java {@link com.serial4j.core.errno.ErrnoToException}
 * to throw exceptions against the JRE.
 *
 * @author pavl_g.
 */
public enum Errno {
    /* The API business errors. */

    /**
     * Signifies an invalid serial port in an attempt to initialize a non-serial device.
     */
    ERR_INVALID_PORT(NativeErrno.getInvalidPortErrno(),
            new InvalidPortException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getInvalidPortErrno()))),

    /**
     * Signifies an operation failure.
     */
    ERR_OPERATION_FAILED(NativeErrno.getOperationFailedErrno(),
            new OperationFailedException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getOperationFailedErrno()))),

    /**
     * Signifies an operation succession, has no associated throwable, ignored by ErrnoToException.
     */
    OPERATION_SUCCEEDED(NativeErrno.getOperationSucceededCode(), null),

    /**
     * Signifies that there are no available typewriter devices in an attempt to fetch available serial devices.
     */
    ERR_NO_AVAILABLE_TTY_DEVICES(NativeErrno.getNoAvailableTtyDevicesErrno(),
            new NoAvailableTtyDevicesException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getNoAvailableTtyDevicesErrno()))),

    /* Error codes for open(const char*, int), file names and IO. */

    /**
     * Signifies a permission denial error in an attempt to especially trying to write to a non-writable device.
     */

    EACCES(NativeErrno.getPermissionDeniedErrno(),
            new PermissionDeniedException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getPermissionDeniedErrno()))),

    EEXIST(NativeErrno.getFileAlreadyOpenedErrno(),
            new FileAlreadyOpenedException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getFileAlreadyOpenedErrno()))),

    EINTR(NativeErrno.getInterruptedSystemCallErrno(),
            new InterruptedSystemCallException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getInterruptedSystemCallErrno()))),

    EISDIR(NativeErrno.getFileIsDirectoryErrno(),
            new FileIsDirectoryException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getFileIsDirectoryErrno()))),

    EMFILE(NativeErrno.getTooManyOpenedFilesErrno(),
            new TooManyOpenedFilesException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getTooManyOpenedFilesErrno()))),

    ENFILE(NativeErrno.getFileTableOverflowErrno(),
            new FileTableOverflowException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getFileTableOverflowErrno()))),

    ENOENT(NativeErrno.getNoSuchFileErrno(),
            new NoSuchFileException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getNoSuchFileErrno()))),

    ENOSPC(NativeErrno.getNoSpaceLeftErrno(),
            new NoSpaceLeftException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getNoSpaceLeftErrno()))),

    ENXIO(NativeErrno.getNoSuchDeviceErrno(),
            new NoSuchDeviceException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getNoSuchDeviceErrno()))),

    EROFS(NativeErrno.getReadOnlyFileSystemErrno(),
            new ReadOnlyFileSystemException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getReadOnlyFileSystemErrno()))),

    EPIPE(NativeErrno.getBrokenPipeErrno(),
            new BrokenPipeException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getBrokenPipeErrno()))),

    ESPIPE(NativeErrno.getIllegalSeekErrno(),
            new IllegalSeekException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getIllegalSeekErrno()))),

    /**
     * Error codes for tcgetattr(int, struct termios*) and tcsetattr(int, struct termios*).
     */
    EBADFD(NativeErrno.getBadFileDescriptorErrno(),
            new BadFileDescriptorException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getBadFileDescriptorErrno()))),

    EBADF(NativeErrno.getBadFileNumberErrno(),
            new BadFileNumberException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getBadFileNumberErrno()))),

    ENOTTY(NativeErrno.getNotTtyDeviceErrno(),
            new NotTtyDeviceException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getNotTtyDeviceErrno()))),

    /**
     * tcsetattr(int, struct termios*) only.
     */
    EINVAL(NativeErrno.getInvalidArgumentErrno(),
            new InvalidArgumentException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getInvalidArgumentErrno()))),

    /**
     * Additional error codes for basic R/W from <fcntl.h>
     */
    EAGAIN(NativeErrno.getTryAgainErrno(),
            new TryAgainException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getTryAgainErrno()))),

    EIO(NativeErrno.getInputOutputErrno(),
            new InputOutputException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getInputOutputErrno()))),

    /**
     * For write(int, void*, int); only.
     */
    EFBIG(NativeErrno.getFileTooLargeErrno(),
            new FileTooLargeException(NativeErrno.ErrnoMessage.getMessageFromStdErrno(NativeErrno.getFileTooLargeErrno())));

    private final int value;
    private final SerialThrowable associatedThrowable;

    /**
     * Creates an error code constant with a value and a description.
     *
     * @param value               the errno value.
     * @param associatedThrowable the associated throwable.
     */
    Errno(final int value, final SerialThrowable associatedThrowable) {
        this.value = value;
        this.associatedThrowable = associatedThrowable;
    }

    /**
     * Gets the native error code of the Err.
     *
     * @return an integer reference to the error code.
     */
    public int getValue() {
        return value;
    }

    /**
     * Retrieves the pre-defined throwable object for this
     * particular native errno value.
     *
     * @return a reference to the throwable object implementation
     */
    public SerialThrowable getAssociatedThrowable() {
        return associatedThrowable;
    }
}
