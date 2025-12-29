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

import com.serial4j.core.errno.Errno;
import com.serial4j.core.errno.ErrnoToException;
import com.serial4j.core.modem.ModemControllerFlag;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.terminal.control.BaudRate;
import com.serial4j.core.terminal.control.TerminalFlag;
import java.lang.reflect.Field;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * The main entry class for the native terminal device for Serial4j api.
 *
 * @author pavl_g.
 */
public final class TerminalDevice {

    private static final Logger LOGGER = Logger.getLogger(TerminalDevice.class.getName());
    final NativeTerminalDevice nativeTerminalDevice = new NativeTerminalDevice();

    private FilePermissions filePermissions = (FilePermissions) FilePermissions.build().append(
            FilePermissions.OperativeConst.O_RDWR,
            FilePermissions.OperativeConst.O_NOCTTY
    );
    private boolean loggingEnabled;

    /**
     * Instantiates a Unix terminal device object.
     */
    public TerminalDevice() {
    }

    /**
     * Sets up the jvm pointer from jni environment pointer on the heap for the global
     * multithreaded reference.
     *
     * <p>
     * Note: Native and jvm threads can access the jni pointer from the global jvm pointer without
     * referencing one of the local jni env pointers stored on another thread stack (as this leads to a thread-transition error).
     * </p>
     */
    @Deprecated
    private static void setupJniEnvironment() {
        final int errno = NativeTerminalDevice.setupJniEnvironment();
        ErrnoToException.throwFromErrno(errno);
    }

    /**
     * Opens this device's serial port using the path from [serialPort] instance.
     *
     * @param serialPort the serial port instance to open.
     */
    public void openPort(final SerialPort serialPort) {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Opening serial device " + serialPort.getPath());
        }
        try {
            // set the Java ioFlag from the FilePermissions utilities to be passed to the native routines
            final Field ioFlagField = serialPort.getClass().getDeclaredField("ioFlag");
            ioFlagField.setAccessible(true);
            ioFlagField.setInt(serialPort, filePermissions.getValue());
        } catch (NoSuchFieldException | IllegalAccessException e) {
            LOGGER.log(Level.SEVERE, e.getMessage(), e);
        }

        this.nativeTerminalDevice.setSerialPort(serialPort);
        final int returnValue = nativeTerminalDevice.openPort();
        if (isOperationFailed(returnValue)) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno(),
                                            String.format("%s:%s", "Device Port is ", serialPort.getPath()));
        }
        /* update port data natively */
        /* ... */
    }

    public void setModemBitsStatus(final ModemControllerFlag flag) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        int returnValue = nativeTerminalDevice.setModemBitsStatus(flag.getValue());
        if (isOperationFailed(returnValue)) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
    }

    public ModemControllerFlag getModemBitsStatus() {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        final int[] nativeStatus = new int[1]; // allocate pointer on the stack
        final int returnValue = nativeTerminalDevice.getModemBitsStatus(nativeStatus);
        if (isOperationFailed(returnValue)) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        return ModemControllerFlag.from(nativeStatus[0]);
    }

    /**
     * Initializes this terminal device with the default flags and the default
     * read timeout configuration.
     */
    public void initTerminal() {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Initializing serial device " + getSerialPort().getPath());
        }
        int returnValue = nativeTerminalDevice.initTerminal();
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    /**
     * Realtime changes the file mode access permissions for the owner's processes.
     *
     * @param modeAccessPermissions the file mode access permissions
     * @see TerminalDevice#setOperativeFilePermissions(FilePermissions)
     */
    public void chmod(final FilePermissions modeAccessPermissions) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        final int returnValue = NativeFileAccessPermissions.fileChmod(nativeTerminalDevice.getSerialPort().getFd(),
                modeAccessPermissions.getValue());
        if (isOperationFailed(returnValue)) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
    }

    public TerminalFlag getTerminalControlFlag() {
        final TerminalFlag TCF = TerminalFlag.build();
        final int returnValue = nativeTerminalDevice.getTerminalControlFlag();
        if (isOperationFailed(returnValue)) {
            /* Warning: Force cast the errno to (int) */
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        TCF.setValue(returnValue);
        return TCF;
    }

    /**
     * Adjusts the terminal control flag of the termios, the terminal control flag controls the
     * characters behavior in the local terminal.
     *
     * @param flag the terminal control flag to adjust.
     */
    public void setTerminalControlFlag(final TerminalFlag flag) {
        int returnValue = nativeTerminalDevice.setTerminalControlFlag(flag.getValue());
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    public TerminalFlag getTerminalLocalFlag() {
        final TerminalFlag TLF = TerminalFlag.build();
        final int returnValue = nativeTerminalDevice.getTerminalLocalFlag();
        /* Warning: Force cast the errno to (int) */
        if (isOperationFailed(returnValue)) {
            /* Warning: Force cast the errno to (int) */
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        TLF.setValue(returnValue);
        return TLF;
    }

    /**
     * Adjusts the terminal local flag of the termios, the terminal local flag controls how the
     * terminal interprets the characters on the local console.
     *
     * @param flag the local flag to adjust.
     */
    public void setTerminalLocalFlag(final TerminalFlag flag) {
        int returnValue = nativeTerminalDevice.setTerminalLocalFlag(flag.getValue());
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    public TerminalFlag getTerminalInputFlag() {
        final TerminalFlag TIF = TerminalFlag.build();
        final int returnValue = nativeTerminalDevice.getTerminalInputFlag();
        /* Warning: Force cast the errno to (int) */
        if (isOperationFailed(returnValue)) {
            /* Warning: Force cast the errno to (int) */
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        TIF.setValue(returnValue);
        return TIF;
    }

    /**
     * Adjusts the terminal input flag for the termios, the terminal input flag controls how
     * the terminal interpret the characters at the input from the terminal device.
     *
     * @param flag the terminal input flag to adjust.
     */
    public void setTerminalInputFlag(final TerminalFlag flag) {
        int returnValue = nativeTerminalDevice.setTerminalInputFlag(flag.getValue());
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    public TerminalFlag getTerminalOutputFlag() {
        final TerminalFlag TOF = TerminalFlag.build();
        final int returnValue = nativeTerminalDevice.getTerminalOutputFlag();
        /* Warning: Force cast the errno to (int) */
        if (isOperationFailed(returnValue)) {
            /* Warning: Force cast the errno to (int) */
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        TOF.setValue(returnValue);
        return TOF;
    }

    /**
     * Adjusts the terminal output flag for this terminal device, the terminal output flag controls
     * how the terminal interpret the characters at the output to the terminal device.
     */
    public void setTerminalOutputFlag(final TerminalFlag flag) {
        int returnValue = nativeTerminalDevice.setTerminalOutputFlag(flag.getValue());
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    /**
     * Retrieves the file permissions used for operations.
     *
     * @return the file permissions instance
     */
    public FilePermissions getPermissions() {
        return filePermissions;
    }

    /**
     * Adjusts the operative mode file permissions used for operation such as (open, create, mkdir, mknod).
     *
     * @param filePermissions the permissions for the file descriptor that determines its read/write/execute capabilities
     * @see TerminalDevice#chmod(FilePermissions)
     */
    public void setOperativeFilePermissions(final FilePermissions filePermissions) {
        this.filePermissions = filePermissions;
    }

    public void setReadConfigurationMode(final ReadConfiguration readConfiguration,
                                         final int timeoutValue, final int minimumBytes) {

        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Setting reading config to " + readConfiguration.getDescription());
        }
        final short timeoutByteValue = (short) (readConfiguration.getMode().TIME_OUT() * timeoutValue);
        final short minimumBytesValue = (short) (readConfiguration.getMode().MIN() * minimumBytes);
        final int errno = nativeTerminalDevice.setReadConfigurationMode((short) Math.min(255, timeoutByteValue),
                (short) Math.min(255, minimumBytesValue));
        ErrnoToException.throwFromErrno(errno);
    }

    public ReadConfiguration getReadConfigurationMode() {
        final short[] mode = nativeTerminalDevice.getReadConfigurationMode();
        return ReadConfiguration.getFromNativeReadConfig(new ReadConfiguration.Mode(mode[0], mode[1]));
    }

    public long write(final String buffer) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        final long numberOfWrittenBytes = nativeTerminalDevice.write(buffer, buffer.length());
        if (numberOfWrittenBytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue());
        } else if (numberOfWrittenBytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        return numberOfWrittenBytes;
    }

    public long write(final int data) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }

        final long numberOfWrittenBytes = nativeTerminalDevice.write(data);
        if (numberOfWrittenBytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue());
        } else if (numberOfWrittenBytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
        return numberOfWrittenBytes;
    }

    public long write(final int[] data) {
        long numberOfWrittenBytes = 0;
        for (int datum : data) {
            numberOfWrittenBytes += this.write(datum);
            if (numberOfWrittenBytes <= 0) {
                break;
            }
        }
        return numberOfWrittenBytes;
    }

    public long sread() {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        long bytes = nativeTerminalDevice.sread();
        if (bytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue());
        } else if (bytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }

        return bytes;
    }

    public long sread(final int length) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        long bytes = nativeTerminalDevice.sread(length);
        if (bytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue(), String.format("%s:%s", "Device Port is ", nativeTerminalDevice.getSerialPort().getPath()));
        } else if (bytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno(), String.format("%s:%s", "Device Port is ", nativeTerminalDevice.getSerialPort().getPath()));
        }

        return bytes;
    }

    public long iread(final int length) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }
        long bytes = nativeTerminalDevice.iread(length);
        if (bytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue(), String.format("%s:%s", "Device Port is ", nativeTerminalDevice.getSerialPort().getPath()));
        } else if (bytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno(), String.format("%s:%s", "Device Port is ", nativeTerminalDevice.getSerialPort().getPath()));
        }

        return bytes;
    }

    /**
     * Moves the current file-system position by a 64-bit offset value
     * forwardly or backwardly according to the file-seek criterion (the "whence" parameter).
     *
     * @param offset    the number of bytes to seek with; based on the criterion applied
     * @param criterion the file seeking criterion
     * @return the number of sought bytes in a 64-bit integer format
     */
    public long seek(long offset, NativeTerminalDevice.FileSeekCriterion criterion) {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad or not initialized serial port!");
        }
        long bytes = nativeTerminalDevice.seek(offset, criterion.getWhence());
        if (bytes == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue());
        } else if (bytes <= 0) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }

        return bytes;
    }

    /**
     * Retrieves the string literal buffer, the output
     * of the operation {@link TerminalDevice#sread()}
     * and {@link TerminalDevice#sread(int)}.
     *
     * @return the string literal buffer
     */
    public String getReadBuffer() {
        return nativeTerminalDevice.getReadBuffer();
    }

    /**
     * Retrieves the character literal buffer, the
     * output of the operation {@link TerminalDevice#iread(int)}.
     *
     * @return the character literal buffer
     */
    public char[] getBuffer() {
        return nativeTerminalDevice.getBuffer();
    }

    public int getBaudRate() {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Getting device baud");
        }
        final int errno = nativeTerminalDevice.getBaudRate();
        ErrnoToException.throwFromErrno(errno);
        return errno;
    }

    /**
     * Adjusts the baud rate of the terminal device after opening and initializing it.
     *
     * @param baudRate the baud rate (bits/seconds) value
     */
    public void setBaudRate(final BaudRate baudRate) {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Setting device baud rate to " + baudRate.getRealBaud());
        }
        int returnValue = nativeTerminalDevice.setBaudRate(baudRate.getBaudRate());
        if (isOperationFailed(returnValue)) {
            returnValue = nativeTerminalDevice.getErrno();
        }
        ErrnoToException.throwFromErrno(returnValue);
    }

    /**
     * Retrieves the available serial ports.
     *
     * @return an array of strings representing the available ports
     */
    public String[] getSerialPorts() {
        fetchSerialPorts();
        return nativeTerminalDevice.getSerialPorts();
    }

    /**
     * Closes the port and releases the resources held by this device.
     */
    public void closePort() {
        if (nativeTerminalDevice.getSerialPort() == null) {
            throw new InvalidPortException("Bad serial port!");
        }

        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Closing port: " + getSerialPort().getPath());
        }
        final int returnValue = nativeTerminalDevice.closePort();
        // sanity check for the business error code
        if (returnValue == Errno.ERR_INVALID_PORT.getValue()) {
            ErrnoToException.throwFromErrno(Errno.ERR_INVALID_PORT.getValue());
        } else if (returnValue < Errno.OPERATION_SUCCEEDED.getValue()) {
            ErrnoToException.throwFromErrno(nativeTerminalDevice.getErrno());
        }
    }

    /**
     * Tests whether logging is enabled.
     *
     * @return true as enabled, false otherwise
     */
    public boolean isSerial4jLoggingEnabled() {
        return loggingEnabled;
    }

    /**
     * Adjusts the logging capabilities of serial4j.
     *
     * @param loggingEnabled true to enable, false otherwise
     */
    public void setSerial4jLoggingEnabled(final boolean loggingEnabled) {
        this.loggingEnabled = loggingEnabled;
    }

    /**
     * Retrieves the serial port associated with terminal device.
     *
     * @return the serial port instance for this device
     */
    public SerialPort getSerialPort() {
        return nativeTerminalDevice.getSerialPort();
    }

    private void fetchSerialPorts() {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Fetching Serial ports.");
        }
        // throwing the return value here
        final int returnValue = nativeTerminalDevice.fetchSerialPorts();
        ErrnoToException.throwFromErrno(returnValue);
    }

    private boolean isOperationFailed(final int returnValue) {
        return returnValue == Errno.ERR_OPERATION_FAILED.getValue();
    }
}