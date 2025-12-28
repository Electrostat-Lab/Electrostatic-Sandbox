/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project
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

package com.serial4j.core.hid;

import com.serial4j.core.hid.device.dataframe.DataFrameDevice;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.FilePermissions;
import com.serial4j.core.terminal.ReadConfiguration;
import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.core.terminal.control.BaudRate;

/**
 * Provides a standard implementation for a serial-based HID.
 *
 * <p>
 * Any serial-based HID is associated with a {@link TerminalDevice}
 * instance that opens the port, initializes terminal IO, without handling
 * raw read/write operations, in addition to the decoder algorithms
 * which is left as an open-ended API for the serial-based devices, wherein
 * each serial-based HID should define its standard report descriptor through these
 * algorithms, see {@link DataFrameDevice} as an example.
 * </p>
 *
 * @param <E> the type-arg of the encoded data packets
 * @param <D> the type-arg of the decoded data packets
 * @author pavl_g
 */
public abstract class StandardSerialDevice<E, D> extends HumanInterfaceDevice<E, D> {

    /**
     * The associated terminal device instance for handling terminal
     * operations.
     */
    protected TerminalDevice terminalDevice;

    /**
     * The serial port this device is connected to.
     */
    protected SerialPort serialPort;

    /**
     * The file permissions for this serial port filesystem operations.
     */
    protected FilePermissions operativePermissions;

    /**
     * Instantiates a serial-based human-interface-device (HID) with a terminal device to handle
     * terminal IO and line-speed operations, and a serial port to which this device is connected to.
     *
     * @param terminalDevice the associated terminal device
     * @param serialPort     the serial port to which this device is connected to
     */
    public StandardSerialDevice(final TerminalDevice terminalDevice, final SerialPort serialPort) {
        this.terminalDevice = terminalDevice;
        this.serialPort = serialPort;
    }

    @Override
    public void init() {
        terminalDevice.setOperativeFilePermissions(operativePermissions);
        terminalDevice.openPort(serialPort);
        terminalDevice.initTerminal();
        terminalDevice.setBaudRate(BaudRate.B9600);
        // POLLING requested bytes out of the IO pipeline queue
        // this makes the read() returns immediately in case
        // of there are no bytes are in the terminal input queue
        getTerminalDevice().setReadConfigurationMode(
                ReadConfiguration.POLLING_READ,
                0,
                0
        );
    }

    @Override
    public void close() {
        terminalDevice.closePort();
        terminalDevice = null;
        serialPort = null;
        operativePermissions = null;
        super.close();
    }

    /**
     * Retrieves a reference to the terminal device used
     * for the read/write and terminal line-speed operations.
     *
     * @return a reference to the terminal device operations
     */
    public TerminalDevice getTerminalDevice() {
        return terminalDevice;
    }

    /**
     * Adjusts the file permissions for this application process (open/read/write operations)
     * invoked by the terminal device on the filesystem associated with
     * this device.
     *
     * @param operativePermissions the file permissions for this process open/read/write operations
     */
    public void setOperativePermissions(FilePermissions operativePermissions) {
        this.operativePermissions = operativePermissions;
    }
}