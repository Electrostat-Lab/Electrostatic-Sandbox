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

package com.serial4j.example.monitor;

import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.FilePermissions;
import com.serial4j.core.terminal.NativeTerminalDevice;
import com.serial4j.core.terminal.TerminalDevice;

/**
 * Examines and tests a raw virtual monitor on the native low-level file-system API
 * {@link com.serial4j.core.terminal.NativeTerminalDevice}.
 *
 * @author pavl_g
 */
public final class TestRawVirtualMonitor {
    public static void main(String[] args) throws InterruptedException {

        final TerminalDevice ttyDevice = new TerminalDevice();
        final FilePermissions filePermissions = (FilePermissions) FilePermissions.build()
                .append(FilePermissions.OperativeConst.O_RDWR)
                .append(FilePermissions.OperativeConst.O_CREATE);
        final FilePermissions accessModePermissions = (FilePermissions) FilePermissions.build().append(
                FilePermissions.AccessModeConst.S_IRUSR,
                FilePermissions.AccessModeConst.S_IWUSR,
                FilePermissions.AccessModeConst.S_IXUSR
        );
        ttyDevice.setOperativeFilePermissions(filePermissions);
        ttyDevice.openPort(new SerialPort(args[0]));
        ttyDevice.chmod(accessModePermissions);

        int x = 0;
        int y = 0;
        String frame = String.format("[x = %d, y = %d]", x, y);

        for (;;) {
            if (x >= 1023) {
                x = 0;
            }
            if (y >= 1023) {
                y = 0;
            }
            ttyDevice.seek(0, NativeTerminalDevice.FileSeekCriterion.SEEK_SET);
            ttyDevice.write(frame);
            Thread.sleep(1000);
            ttyDevice.seek(0, NativeTerminalDevice.FileSeekCriterion.SEEK_SET);
            if (ttyDevice.sread(frame.length()) > 0) {
                if (ttyDevice.getReadBuffer() != null) {
                    System.out.println(ttyDevice.getReadBuffer());
                }
            }
            ttyDevice.seek(0, NativeTerminalDevice.FileSeekCriterion.SEEK_SET);
            x += 12;
            y += 10;
            frame = String.format("[x = %d, y = %d]", x, y);
        }
    }
}

