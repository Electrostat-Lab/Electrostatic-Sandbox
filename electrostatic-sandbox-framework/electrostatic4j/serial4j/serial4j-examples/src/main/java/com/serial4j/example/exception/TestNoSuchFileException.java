/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The Arithmos Project.
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

package com.serial4j.example.exception;

import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.throwable.SerialThrowable;
import com.serial4j.core.terminal.TerminalDevice;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Examines and tests the {@link com.serial4j.core.serial.throwable.NoSuchFileException}
 * thrown if the code tries to open a non-existing serial port file.
 *
 * @author pavl_g
 */
public final class TestNoSuchFileException {

    public static void main(String[] args) {
        final TerminalDevice ttyDevice = new TerminalDevice();
        try {
            ttyDevice.openPort(new SerialPort(args[0]));
        } catch (SerialThrowable e) {
            Logger.getLogger(TestNoSuchFileException.class.getName())
                            .log(Level.SEVERE, e.getMessage() + " " + ttyDevice.getSerialPort().getPath(), e);
            System.exit(e.getCausingErrno().getValue());
        } finally {
            /* dispatched if the application didn't crash */
            ttyDevice.closePort();
        }
    }
}
