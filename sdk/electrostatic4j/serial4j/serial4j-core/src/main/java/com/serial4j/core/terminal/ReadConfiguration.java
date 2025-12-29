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
 * Provides a Unix terminal read configuration for the specified serial port of the
 * terminal device.
 *
 * @author pavl_g.
 */
public enum ReadConfiguration {

    /**
     * Busy loop polling read the requested bytes without blocking.
     * <p>
     * If data is available at the time of the call,
     * then read() returns immediately with the least number of bytes available or
     * the number of bytes requested. If no bytes are available, read() completes immediately, returning 0.
     * </p>
     */
    POLLING_READ(new Mode((short) 0, (short) 0), "Polling Read"),

    /**
     * Blocking read without polling in a busy loop.
     * <p>
     * The read() blocks (possibly indefinitely) until the lesser of the number of bytes
     * requested or MIN bytes are available, and returns the lesser of the two values.
     * </p>
     */
    BLOCKING_READ_ONE_CHAR(new Mode((short) 0, (short) 1), "Blocking read one character at a time"),

    /**
     * Polling read the requested bytes with a timeout.
     * <p>
     * A timer is started when read() is called. The call returns as soon as at least 1 byte is
     * available, or when TIME tenths of a second have elapsed. In the latter case, read()
     * returns 0.
     * </p>
     */
    READ_WITH_TIMEOUT(new Mode((short) 1, (short) 0), "Polling Read with timeout"),

    /**
     * Blocking read the requested bytes or the MIN with a timeout.
     * <p>
     * After the initial byte of input becomes available, a timer is restarted as each further
     * byte is received. The read() returns when either the lesser of MIN bytes or the number
     * of bytes requested have been read, or when the time between receiving successive
     * bytes exceeds TIME tenths of a second. Since the timer is started only after the initial
     * byte becomes available, at least 1 byte is returned. (A read() can block indefinitely
     * for this case.)
     * </p>
     */
    READ_WITH_INTERBYTE_TIMEOUT(new Mode((short) 1, (short) 1), "Blocking read with timeout");

    private final String description;
    private Mode mode;

    ReadConfiguration(final Mode mode, final String description) {
        this.mode = mode;
        this.description = description;
    }

    /**
     * Creates a read configuration from the native values.
     *
     * @param nativeReadConfig the native values
     * @return a new instance of read configuration reflecting the native values
     */
    public static ReadConfiguration getFromNativeReadConfig(final Mode nativeReadConfig) {
        ReadConfiguration readConfiguration;
        if (nativeReadConfig.TIME_OUT < 1 && nativeReadConfig.MIN >= 1) {
            readConfiguration = ReadConfiguration.BLOCKING_READ_ONE_CHAR;
        } else if ((nativeReadConfig.TIME_OUT | nativeReadConfig.MIN) == 0) {
            readConfiguration = ReadConfiguration.POLLING_READ;
        } else if (nativeReadConfig.TIME_OUT >= 1 && nativeReadConfig.MIN >= 1) {
            readConfiguration = ReadConfiguration.READ_WITH_INTERBYTE_TIMEOUT;
        } else {
            readConfiguration = ReadConfiguration.READ_WITH_TIMEOUT;
        }
        /* update the mode value with the native readConfig value */
        readConfiguration.mode = nativeReadConfig;
        return readConfiguration;
    }

    /**
     * Retrieves the reading mode in a block form.
     *
     * @return the reading mode, the minimum number of bytes available and the
     * timeout for the reading operation
     */
    public Mode getMode() {
        return mode;
    }

    /**
     * Retrieves the summative description of this mode.
     *
     * @return the summative description of this mode
     */
    public String getDescription() {
        return description;
    }

    /**
     * Defines a reading configuration mode with the minimum bytes available
     * and a timeout value for the read() operation.
     *
     * @param TIME_OUT the timeout is a step-down counter in a tenth of a second unit,
     *                 specifying [0] will disable the timeout.
     * @param MIN      the minimum number of bytes requested to return the read() operation,
     *                 specifying [0] will disable this analogy and the reading operation
     *                 will busy loop until polling the requested number of bytes is successful.
     */
    public record Mode(short TIME_OUT, short MIN) {
        @Override
        public String toString() {
            return "[TIME_OUT, MIN] = [" + TIME_OUT + ", " + MIN + "]";
        }
    }
}
