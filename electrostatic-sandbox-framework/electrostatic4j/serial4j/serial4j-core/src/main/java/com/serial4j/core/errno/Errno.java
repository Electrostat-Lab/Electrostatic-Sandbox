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

import com.serial4j.core.serial.throwable.*;

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
    ERR_INVALID_PORT(NativeErrno.getInvalidPortErrno(), new InvalidPortException("Invalid Port")),

    /**
     * Signifies an operation failure.
     */
    ERR_OPERATION_FAILED(NativeErrno.getOperationFailedErrno(), new OperationFailedException("Operation Failed")),

    /**
     * Signifies an operation succession, has no associated throwable, ignored by ErrnoToException.
     */
    OPERATION_SUCCEEDED(NativeErrno.getOperationSucceededCode(),null),

    /**
     * Signifies that there are no available typewriter devices in an attempt to fetch available serial devices.
     */
    ERR_NO_AVAILABLE_TTY_DEVICES(NativeErrno.getNoAvailableTtyDevicesErrno(), new NoAvailableTtyDevicesException("No available teletype devices")),

    /* Error codes for open(const char*, int), file names and IO. */

    /**
     * Signifies a permission denial error in an attempt to especially trying to write to a non-writable device.
     */
    EACCES(NativeErrno.getPermissionDeniedErrno(), new PermissionDeniedException("Permission denied")),
    EEXIST(NativeErrno.getFileAlreadyOpenedErrno(), new FileAlreadyOpenedException("File exists")),
    EINTR(NativeErrno.getInterruptedSystemCallErrno(), new InterruptedSystemCallException("Interrupted system call")),
    EISDIR(NativeErrno.getFileIsDirectoryErrno(), new FileIsDirectoryException("Is a directory")),
    EMFILE(NativeErrno.getTooManyOpenedFilesErrno(), new TooManyOpenedFilesException("Too many open files")),
    ENFILE(NativeErrno.getFileTableOverflowErrno(), new FileTableOverflowException("File table overflow")),
    ENOENT(NativeErrno.getNoSuchFileErrno(), new NoSuchFileException("No Such file or directory")),
    ENOSPC(NativeErrno.getNoSpaceLeftErrno(), new NoSpaceLeftException("No space left on device")),
    ENXIO(NativeErrno.getNoSuchDeviceErrno(), new NoSuchDeviceException("No such device or address")),
    EROFS(NativeErrno.getReadOnlyFileSystemErrno(), new ReadOnlyFileSystemException("Read-only file system")),
    EPIPE(NativeErrno.getBrokenPipeErrno(), new BrokenPipeException("Broken pipe")),
    ESPIPE(NativeErrno.getIllegalSeekErrno(), new IllegalSeekException("Illegal File Seeking operation")),

    /**
     * Error codes for tcgetattr(int, struct termios*) and tcsetattr(int, struct termios*).
     */
    EBADFD(NativeErrno.getBadFileDescriptorErrno(), new BadFileDescriptorException("File descriptor in bad state")),

    EBADF(NativeErrno.getBadFileNumberErrno(), new BadFileNumberException("Bad file number")),
    ENOTTY(NativeErrno.getNotTtyDeviceErrno(), new NotTtyDeviceException("Not a typewriter device")),

    /**
     * tcsetattr(int, struct termios*) only.
     */
    EINVAL(NativeErrno.getInvalidArgumentErrno(), new InvalidArgumentException("Invalid argument")),

    /**
     * Additional error codes for basic R/W from <fcntl.h>
     */
    EAGAIN(NativeErrno.getTryAgainErrno(), new TryAgainException("Try again")),
    EIO(NativeErrno.getInputOutputErrno(), new InputOutputException("I/O Error")),

    /**
     * For write(int, void*, int); only.
     */
    EFBIG(NativeErrno.getFileTooLargeErrno(), new FileTooLargeException("File too large"));

    private final int value;
    private final SerialThrowable associatedThrowable;

    /**
     * Creates an error code constant with a value and a description.
     * 
     * @param value the errno value.
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
