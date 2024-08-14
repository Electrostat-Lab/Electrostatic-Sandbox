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

package com.serial4j.core.hid.device.dataframe;

import com.serial4j.core.hid.HumanInterfaceDevice;
import com.serial4j.core.hid.StandardSerialDevice;
import com.serial4j.core.hid.device.dataframe.registry.JoystickRegistry;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.TerminalDevice;

/**
 * A shift-avr joystick serial interface device providing a data
 * descriptor decoder that decodes raw reports into {X} and {Y} values
 * based on the {@link JoystickRegistry}.
 *
 * @author pavl_g
 */
public class DataFrameDevice<D> extends StandardSerialDevice<String, D> {

    /**
     * A Global Input buffer for decoding operations.
     *
     * <p>
     * <b>Global V.S. Local Buffers:</b> The use of global/heap buffer here
     * is attributed to the reading configuration (Polling read) being utilized by the
     * serial-based HIDs, which enforces immediate termination if there were no characters
     * available at the input queue buffer at the time of dispatching the read() operation,
     * rendering incomplete dataframe reports in case of using a local input buffer instead of the heap buffer.
     * On the contrary, utilizing a heap buffer enables the receiver software to accumulate data, whenever available,
     * from the Data-Communication-Equipment device (DCE) data register before reaching a Line-Feed/Return-Carriage compound
     * characters, after which the input buffer is flushed, and the decoder is dispatched, eventually dispatching the user code
     * with the decoded data structure.
     * </p>
     */
    protected final StringBuffer inputBuffer = new StringBuffer();

    /**
     * Instantiates a serial shift-avr device that is capable of
     * reading descriptor reports composed of max-line "[x = 1023, y = 1023]\n\r".
     *
     * @param terminalDevice the associated terminal device
     * @param serialPort     the serial port of the connected device
     */
    public DataFrameDevice(TerminalDevice terminalDevice, SerialPort serialPort) {
        super(terminalDevice, serialPort);
    }

    @Override
    @SuppressWarnings("unchecked")
    public void init() {
        super.init();
        decoder = (HumanInterfaceDevice.ReportDescriptor.Decoder<String, D>) new JoystickRegistry.Decoder();
        setDecoder(decoder);
        setReportDescriptor(new ReportDescriptor());
    }

    @Override
    public void receive() {
        // reads a frame terminated by LF-CR, Line feed - Carriage return ("\n\r")
        // then finishes by dispatching the decoder implementation
        // after which the decoding listeners come into play
        // terminating the loop thereafter.
        // Note: as a part of loop control:
        // the loop self-terminates with an exception if the
        // reading exceeds 1024 (1 << 10 or 2^10) bytes without dispatching the decoder
        super.decode(dataRegisterLength -> {
            for (int chars = 0; getTerminalDevice().iread(dataRegisterLength) > 0; chars++) {
                inputBuffer.append(getTerminalDevice().getBuffer());
                if (inputBuffer.toString().endsWith(Character.toString(reportDescriptor.getReportLength()))) {
                    final String data = inputBuffer.toString(); // create a new local pointer
                    inputBuffer.delete(0, inputBuffer.length()); // flush the input buffer
                    return data;
                } else if (chars > (0x01 << 0x0A)) {
                    throw new NotDataFrameDeviceException();
                }
            }
            return null; // return null as of no value
        });
    }

    @Override
    public void transmit(D decoded) {
        // sends the encoded values plus a '\n' for data framing
        super.encode(encoded ->
                terminalDevice.write(encoded + reportDescriptor.getReportLength()), decoded);
    }

    @Override
    public String getVendor() {
        return "DataFrame-Serial-HID";
    }

    @Override
    public void close() {
        inputBuffer.delete(0, inputBuffer.length()); // flush the input buffer
        super.close(); // close the port and release resources
    }

    /**
     * Retrieves the input buffer being in-use.
     *
     * @return the input buffer holding data frames
     */
    public final StringBuffer getInputBuffer() {
        return inputBuffer;
    }

    /**
     * Provides a descriptor for the report, this includes the report length and
     * the data register buffer length.
     */
    public static class ReportDescriptor implements HumanInterfaceDevice.ReportDescriptor {

        /**
         * Instantiates a report descriptor with the default
         * Line Feed (0x0A) as a report length, and a 1-byte
         * data register buffer length.
         */
        public ReportDescriptor() {
        }

        @Override
        public int getReportLength() {
            return 0x0A; // LF or '\n'
        }

        @Override
        public int getDataRegisterBufferLength() {
            return 1; // 1-byte data for 8-bit based registers
        }

        /**
         * Defines an alias type for the decoder interface
         * specialized for this standard.
         *
         * @param <D> the type of the decoded data.
         * @see JoystickRegistry
         */
        public interface Decoder<D> extends HumanInterfaceDevice.ReportDescriptor.Decoder<String, D> {
        }

        /**
         * Defines a dispatch listener that is dispatched
         * when decoding/encoding completes, usually this
         * is a user-side API.
         *
         * @param <D> the type of the decoded data packets
         */
        public interface DecoderListener<D> extends HumanInterfaceDevice.ReportDescriptor.DecoderListener<String, D> {
        }
    }
}