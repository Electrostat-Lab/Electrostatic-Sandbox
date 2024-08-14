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
package com.serial4j.example.serial4j;

import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.core.terminal.control.BaudRate;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * An example showing serial and terminal io using java.io API.
 *
 * @author pavl_g.
 */
public final class HelloSerial4jIO implements Runnable {

    /**
     * Provides a java binding to the native terminal device.
     */
    private final TerminalDevice ttyDevice = new TerminalDevice();

    public static void main(String[] args) {
        new HelloSerial4jIO().run();
    }

    /**
     * Uses the {@link java.io.FileOutputStream} to write to the pre-initialized port in a new thread.
     *
     * @param ttyDevice the terminal device object to get the {@link FileOutputStream} from.
     * @param millis    a delay before the writing operation starts in ms.
     */
    private static void startWriteThread(final TerminalDevice ttyDevice, final long millis) {
        new Thread(() -> {
            try {
                Thread.sleep(millis);
                /* uses the java io to write to the serial port */
                ttyDevice.write('A');
                ttyDevice.write('D');
                ttyDevice.closePort();
            } catch (InterruptedException e) {
                Logger.getLogger(HelloSerial4jIO.class.getName())
                        .log(Level.SEVERE, "Writing has failed!", e);
            }
        }).start();
    }

    /**
     * Uses the {@link java.io.FileInputStream} to read from the pre-initialized port in a new thread.
     *
     * @param ttyDevice the terminal device object to get the {@link FileInputStream} from.
     * @param millis    a delay before the writing operation starts in ms.
     */
    private static void startReadThread(final TerminalDevice ttyDevice, final long millis) {
        new Thread(() -> {
            try {
                Thread.sleep(millis);
                while (true) {
                    /* check for the number of the available charachters to read */
                    if (ttyDevice.iread(1) > 0) {
                        System.out.print(ttyDevice.getBuffer());
                    }
                }
            } catch (InterruptedException e) {
                Logger.getLogger(HelloSerial4jIO.class.getName())
                        .log(Level.SEVERE, "Reading has failed!", e);
            }
        }).start();
    }

    @Override
    public void run() {
        try {
            System.out.println("Started java io example: ");
            /* disable native logger */
            /* enable java logger */
            ttyDevice.setSerial4jLoggingEnabled(true);
            ttyDevice.openPort(new SerialPort(ttyDevice.getSerialPorts()[0]));
            if (ttyDevice.getSerialPort().getFd() > 0) {
                System.out.println("Port Opened with " + ttyDevice.getSerialPort().getFd());
            } else {
                System.err.println("Cannot open serial port" + " " + ttyDevice.getSerialPort().getFd());
            }
            /* initialize terminal io base POSIX library with the default terminal flags */
            ttyDevice.initTerminal();
            /* set and apply the baud rate to determine transmission speed */
            ttyDevice.setBaudRate(BaudRate.B57600);
            System.out.println("Available serial ports: " + Arrays.toString(ttyDevice.getSerialPorts()) + " " + ttyDevice.getSerialPorts().length);
            /* start R/W threads */
            startReadThread(ttyDevice, 0);
            startWriteThread(ttyDevice, 1000);
        } catch (NoSuchDeviceException |
                 PermissionDeniedException |
                 BrokenPipeException |
                 InvalidPortException e) {
            Logger.getLogger(HelloSerial4jIO.class.getName())
                    .log(Level.SEVERE, "Monitor has failed!", e);
        }
    }
}
