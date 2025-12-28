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

/**
 * Provides the native error code that can be
 * utilized by the API.
 *
 * @author pavl_g
 * @see Errno
 * @see ErrnoToException
 */
public final class NativeErrno {

    private NativeErrno() {
    }

    static native int getBadFileNumberErrno();

    static native int getBadFileDescriptorErrno();

    static native int getBrokenPipeErrno();

    static native int getFileAlreadyOpenedErrno();

    static native int getFileIsDirectoryErrno();

    static native int getFileTableOverflowErrno();

    static native int getFileTooLargeErrno();

    static native int getInputOutputErrno();

    static native int getInterruptedSystemCallErrno();

    static native int getInvalidArgumentErrno();

    static native int getInvalidPortErrno();

    static native int getNoAvailableTtyDevicesErrno();

    static native int getNoSpaceLeftErrno();

    static native int getNoSuchDeviceErrno();

    static native int getNoSuchFileErrno();

    static native int getNotTtyDeviceErrno();

    static native int getOperationFailedErrno();

    static native int getOperationSucceededCode();

    static native int getPermissionDeniedErrno();

    static native int getReadOnlyFileSystemErrno();

    static native int getTooManyOpenedFilesErrno();

    static native int getTryAgainErrno();

    static native int getIllegalSeekErrno();

    public static final class ErrnoMessage {
        private ErrnoMessage() {
        }

        static native String getMessageFromStdErrno(int errno);
    }
}