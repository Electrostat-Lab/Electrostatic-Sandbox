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

package com.serial4j.core.terminal;

/**
 * Provides the POSIX file permissions values for the
 * operative methods (open, create, mkdir, mknod).
 *
 * @author pavl_g
 * @see FilePermissions.OperativeConst
 */
public final class NativeFilePermissions {

    private NativeFilePermissions() {
    }

    /**
     * Provides the read-only flag for opening file with read-only (Access mode flag).
     * permissions.
     *
     * @return the "O_RDONLY" value
     */
    static native int getReadOnly();

    /**
     * Provides the write-only flag for opening files with write-only (Access mode flag).
     *
     * @return the "O_WRONLY" value
     */
    static native int getWriteOnly();

    /**
     * Provides the read-write flag for opening files with read/write permissions (Access mode flag).
     *
     * @return the "O_RDWR" value
     */
    static native int getReadWrite();

    /**
     * Provides the no-controlling terminal device flag (Open-time flag).
     * <p>
     * If the named file is a terminal device, don’t make it the controlling terminal for the
     * process.
     * </p>
     *
     * @return the "O_NOCTTY" value
     */
    static native int getNoControlTerminalDevice();

    /**
     * Provides the terminal-non-blocking behavior as a part of open-time flags.
     * <p>
     * This prevents open from blocking for a “long time” to open the file. This is only
     * meaningful for some kinds of files, usually devices such as serial ports; when it is
     * not meaningful, it is harmless and ignored. Often, opening a port to a modem blocks
     * until the modem reports carrier detection; if "O_NONBLOCK" is specified, open will return
     * immediately without a carrier.
     * </p>
     *
     * @return the "O_NONBLOCK" value
     */
    static native int getTerminalNonBlock();

    /**
     * Provides the creating ability to the {@link NativeTerminalDevice#openPort(String, int)}.
     *
     * @return the "O_CREAT" value
     */
    static native int getCreateFile();
}