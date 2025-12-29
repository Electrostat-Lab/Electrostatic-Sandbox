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

import java.util.Arrays;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;
import com.serial4j.core.terminal.FilePermissions;
import com.serial4j.core.terminal.ReadConfiguration;
import com.serial4j.core.terminal.control.*;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.TerminalDevice;

/**
 * An example for Serial4j showing Native terminal control and
 * native file io on a serial port using a java binding to <fcntl.h> and <unistd.h> read (...) and write (...).
 *
 * @author pavl_g.
 */
public final class HelloNativeSerial4J implements Runnable {

	/**
	 * Provides a java binding to a native terminal device.
	 */
	private final TerminalDevice ttyDevice = new TerminalDevice();

	public static void main(String[] args) {
		new HelloNativeSerial4J().run();
	}
	@Override
	public void run() {
		System.out.println(Thread.currentThread());
		System.out.println("Started native io example: ");
		ttyDevice.setSerial4jLoggingEnabled(true);
		/* set port permissions */
		final FilePermissions filePermissions = (FilePermissions) FilePermissions.build()
				.append(FilePermissions.OperativeConst.O_RDWR)
				.append(FilePermissions.OperativeConst.O_NOCTTY);
		ttyDevice.setOperativeFilePermissions(filePermissions);

		final TerminalFlag TCF_VALUE = (TerminalFlag) TerminalFlag.build().append(TerminalControlFlag.CSIZE)
																	  .append(TerminalControlFlag.MaskBits.CS8,
																			  TerminalControlFlag.CLOCAL, TerminalControlFlag.CREAD);

		/* define terminal flags */
		final TerminalFlag TLF_VALUE = (TerminalFlag) TerminalFlag.build().disable(TerminalLocalFlag.ECHO, TerminalLocalFlag.ECHOK,
																	TerminalLocalFlag.ECHOE, TerminalLocalFlag.ECHOKE,
																	TerminalLocalFlag.ECHONL, TerminalLocalFlag.ECHOPRT,
																	TerminalLocalFlag.ECHOCTL, TerminalLocalFlag.ISIG,
																	TerminalLocalFlag.IEXTEN, TerminalLocalFlag.ICANON);
		final TerminalFlag TOF_VALUE = (TerminalFlag) TerminalFlag.build()
															.disable(TerminalOutputFlag.OPOST, TerminalOutputFlag.ONLCR);
		final TerminalFlag TIF_VALUE = TerminalFlag.build();
		/* open the serial port using the path or the name */
		ttyDevice.openPort(new SerialPort("/dev/ttyUSB0"));
		/* initialize the terminal IO with the default terminal flags */
		ttyDevice.initTerminal();
		/* print the initial terminal control flags as long value */
		System.out.println(ttyDevice.getTerminalControlFlag().getValue());
		/* set and update the new terminal flags */
		ttyDevice.setTerminalControlFlag(TCF_VALUE);
		ttyDevice.setTerminalLocalFlag(TLF_VALUE);
		ttyDevice.setTerminalOutputFlag(TOF_VALUE);
		ttyDevice.setTerminalInputFlag(TIF_VALUE);
		/* print the new terminal control flag */
		System.out.println(ttyDevice.getTerminalControlFlag().getValue());
		/* set the baud rate (bits/second) */
		ttyDevice.setBaudRate(BaudRate.B57600);
		/* set the reading mode config to interbyte timeout of delay 510 bytes and delay of 5ms between each charachter */
		ttyDevice.setReadConfigurationMode(ReadConfiguration.BLOCKING_READ_ONE_CHAR, 0, 9);

		/* print the port file descriptor */
		if (ttyDevice.getSerialPort().getFd() > 0) {
			System.out.println("Port Opened with " + ttyDevice.getSerialPort().getFd());
		}
		System.out.println(ttyDevice.getReadConfigurationMode().getMode().toString());
		System.out.println(Arrays.toString(ttyDevice.getSerialPorts()) + " " + ttyDevice.getSerialPorts().length);

		/* start the R/W threads */
		startReadThread(ttyDevice, 0);
		startWriteThread(ttyDevice, 10000);

	}

    /**
     * Uses the [extern ssize_t read (int __fd, void *__buf, size_t __nbytes) __wur] provided by <unistd.h> base posix api
	 * to read from the pre-initialized port in a new thread.
     *
     * @param ttyDevice the terminal device object to read the data from.
     * @param millis a delay before the reading operation starts in ms.
     */
	private void startReadThread(final TerminalDevice ttyDevice, final long millis) {
		new Thread(new Runnable() {
			public void run() {
				try {
					Thread.sleep(millis);
					long read;
					while(true) {
						/* read data and get the buffer */
						if ((read = ttyDevice.sread()) > 0) {
							System.out.println("Total number of read bytes = " + read);
							System.out.println("Serial stream data = " + (ttyDevice.getReadBuffer()));
							ttyDevice.closePort();
						}
					}
				} catch(Exception e) {
					Logger.getLogger(getClass().getName())
							.log(Level.SEVERE, "Reading has failed!", e);
				}
			}
		}).start();
	}

    /**
     * Uses the [extern ssize_t write (int __fd, const void *__buf, size_t __n) __wur] provided by <unistd.h> base posix api
	 * to write to the pre-initialized port in a new thread.
     *
     * @param ttyDevice the terminal device object to write the data to.
     * @param millis a delay before the writing operation starts in ms.
     */
	private void startWriteThread(final TerminalDevice ttyDevice, final long millis) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.sleep(millis);
					/* write a buffer (array of chars) and close the port */
					ttyDevice.write(new int[] {'S', 'e', 'r', 'i', 'a', 'l', '4', 'j', '\0'});
				} catch (Exception e) {
					Logger.getLogger(getClass().getName())
							.log(Level.SEVERE, "Writing has failed!", e);
				}
			}
		}).start();
	}
}
