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

import java.io.InputStream;

/**
 * Adapts the low-level native file IO API to Java Input Stream.
 *
 * @author pavl_g
 */
public class NativeBufferInputStream extends InputStream {

    /**
     * The terminal device associated with this stream.
     */
    protected final TerminalDevice terminalDevice;

    /**
     * Instantiates a Java input stream on top of a terminal
     * device.
     *
     * @param terminalDevice the terminal device holding the FD to associate
     *                       this Java stream with
     */
    public NativeBufferInputStream(final TerminalDevice terminalDevice) {
        this.terminalDevice = terminalDevice;
    }

    /**
     * @deprecated use {@link NativeBufferInputStream#read()} instead.
     */
    @Deprecated
    @Override
    public int available() {
        throw new UnsupportedOperationException("No longer supported in this native stream!");
    }

    /**
     * Seeks the stream back to its start position.
     *
     * <p>
     * Side-effect: a dispatch to this function in a real {@link TerminalDevice} context (not virtual) will
     * crash the application with the exception {@link com.serial4j.core.serial.throwable.IllegalSeekException}.
     * </p>
     */
    @Override
    public void reset() {
        terminalDevice.seek(0, NativeTerminalDevice.FileSeekCriterion.SEEK_SET);
    }

    @Override
    public int read(byte[] b, int off, int len) {
        final char[] buffer = new char[b.length];
        for (int i = 0; i < b.length; i++) {
            buffer[i] = (char) b[i];
        }
        return (int) read(buffer, off, len);
    }

    /**
     * Reads the next byte and saves it to the buffer.
     *
     * <p>
     * Note: a dispatch to this method produces a side effect, it
     * basically replaces all the elements in the buffer with
     * the read byte.
     * </p>
     *
     * <p>
     * Note: a dispatch to this method produces another side effect, the stream IO operation
     * is being sought forward towards its end, to negate this side effect, a dispatch to
     * {@link NativeTerminalDevice#seek(long, int)} or {@link NativeBufferInputStream#reset()} is a must.
     * </p>
     *
     * @return the next byte in this input stream
     */
    @Override
    public int read() {
        return (int) terminalDevice.iread(1);
    }

    /**
     * Reads bytes into the main buffer and copies them to the user buffer.
     *
     * <p>
     * Note: a dispatch to this method produces a side effect, it
     * basically replaces all the elements in the buffer with
     * the read bytes.
     * </p>
     *
     * <p>
     * Note: a dispatch to this method produces another side effect, the stream IO operation
     * is being sought forward towards its end, to negate this side effect, a dispatch to
     * {@link NativeTerminalDevice#seek(long, int)} or {@link NativeBufferInputStream#reset()} is a must.
     * </p>
     *
     * @param buffer the user buffer that the data will be copied to
     * @param offset the start position of the reading operation
     * @param length the end position of the reading operation
     * @return the number of bytes read
     */
    public long read(char[] buffer, int offset, int length) {
        try {
            return readOffset(offset, length);
        } finally {
            System.arraycopy(getBuffer(), 0, buffer, 0, buffer.length);
        }
    }

    /**
     * Reads bytes into the main buffer with a start position
     * and an end position determined by the offset and the length.
     *
     * <p>
     * Note: a dispatch to this method produces a side effect, it
     * basically replaces all the elements in the buffer with
     * the read bytes.
     * </p>
     *
     * <p>
     * Note: a dispatch to this method produces another side effect, the stream IO operation
     * is being sought forward towards its end, to negate this side effect, a dispatch to
     * {@link NativeTerminalDevice#seek(long, int)} or {@link NativeBufferInputStream#reset()} is a must.
     * </p>
     *
     * @param offset the start position of the read operation
     * @param length the end position of the read operation
     * @return the number of the read bytes
     */
    public long readOffset(int offset, int length) {
        // seek to an offset
        terminalDevice.seek(offset, NativeTerminalDevice.FileSeekCriterion.SEEK_SET);
        // read from that offset into a buffer
        return terminalDevice.iread(length);
    }

    @Override
    public void close() {
        terminalDevice.closePort();
    }

    /**
     * Retrieves the read buffer.
     *
     * @return the buffer of the read data
     */
    public char[] getBuffer() {
        return terminalDevice.getBuffer();
    }
}
