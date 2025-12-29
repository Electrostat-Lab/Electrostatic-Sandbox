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

package com.serial4j.core.hid.device.standard.component.analog;

import com.serial4j.core.hid.HumanInterfaceDevice;
import com.serial4j.core.hid.StandardSerialDevice;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.util.Constants;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Represents a standard specification for the analog serial-based
 * devices with robust resolutions of 8-bit data or more.
 *
 * @author pavl_g
 */
public class AnalogModuleDevice extends StandardSerialDevice<Integer, AnalogRegistry> {

    /**
     * Provides a global/heap input buffer to accumulate data in a 32-bit
     * report for the decoder.
     */
    protected final AtomicInteger inputBuffer = new AtomicInteger(0);

    /**
     * Provides a clock counter analogy to clock-in and clock-out data
     * to and from the MCU data register.
     */
    protected final AtomicInteger inputClock = new AtomicInteger(0);

    /**
     * Instantiates an analog serial-based device with a terminal
     * and a serial port. Analog serial devices are special-purpose
     * terminal devices for reading/writing analog data.
     *
     * @param terminalDevice the associated terminal device
     * @param serialPort the device port
     */
    public AnalogModuleDevice(TerminalDevice terminalDevice,
                              SerialPort serialPort) {
        super(terminalDevice, serialPort);
    }

    @Override
    public void init() {
        super.init();
        setReportDescriptor(new ReportDescriptor());
        setDecoder(new AnalogRegistry.Decoder());
    }

    @Override
    public void receive() {
        super.decode(dataRegisterBufferLength -> {
            for (int frame = 0; terminalDevice.iread(dataRegisterBufferLength) > 0 &&
                    frame < reportDescriptor.getReportLength(); frame++, inputClock.incrementAndGet()) {
                final int data = terminalDevice.getBuffer()[0];
                // obtain a shift-value scaled according to the current frame to place
                // the bits in their right position
                final int bits = frame * Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH;
                // replace the bits to the left aka. from LSB to MSB
                // add the bits
                inputBuffer.set(inputBuffer.intValue() | (data << bits));
                // if the input clocks completed sending the report, flush the input and return the result
                if (inputClock.get() == (reportDescriptor.getReportLength() - 1)) {
                    final int value = inputBuffer.get();
                    inputBuffer.set(0); // flush the input buffer
                    inputClock.set(0);
                    return value;
                }
            }
            return null; // skip the decoder dispatch if no end-character is found
        });
    }

    @Override
    public void transmit(AnalogRegistry decoded) {
        super.encode(encoded -> {
            final int[] buffer = new int[reportDescriptor.getReportLength()];
            // shifting-out (clocking-out) data algorithm
            for (int frame = (buffer.length - 1); frame > 0; frame--) {
                final int bits = frame * Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH;
                encoded >>= bits; // move bits to the LSB locations to avoid data truncation
                buffer[frame] = encoded; // fill the data frames buffer
            }
            return terminalDevice.write(buffer);
        }, decoded);
    }

    @Override
    public String getVendor() {
        return "AnalogDevice-Serial-HID";
    }

    @Override
    public void close() {
        inputClock.set(0);
        inputBuffer.set(0); // flush the input buffer
        super.close(); // close the port and release native resources
    }

    /**
     * Retrieves the ADC resolution in bits unit, default is 8-bit.
     *
     * @return the adc resolution in bits unit
     */
    public int getResolution() {
        return ((ReportDescriptor) reportDescriptor).getResolution();
    }

    /**
     * Adjusts the ADC resolution in bits unit (e.g: 8 for 8-bit resolution).
     *
     * <p>
     * Resolution should be a result of power of two, the minimum value and the default is 8-bit.
     * </p>
     *
     * @param resolution the adc resolution in bits unit
     */
    public void setResolution(int resolution) {
        if (resolution % 8 != 0) {
            throw new InvalidResolutionException("Resolution " + resolution + "-bits is not a power of two!");
        }
        ((ReportDescriptor) this.reportDescriptor).setResolution(resolution);
    }

    /**
     * Retrieves a reference to the input buffer that accumulates
     * data for the input report to be utilized by the decoder.
     *
     * @return a reference to the input buffer being used
     */
    public AtomicInteger getInputBuffer() {
        return inputBuffer;
    }

    /**
     * Analog Report with decoder and decoder listener.
     */
    public static class ReportDescriptor implements HumanInterfaceDevice.ReportDescriptor {

        /**
         * The ADC resolution in bits unit.
         */
        protected int resolution = Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH;

        public void setResolution(int resolution) {
            this.resolution = resolution;
        }

        public int getResolution() {
            return resolution;
        }

        @Override
        public int getReportLength() {
            return resolution / Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH; // the total report length (short item)
        }

        @Override
        public int getDataRegisterBufferLength() {
            return 1; // data received per clock transmission
        }

        /**
         * Decoder type alias for the analog device.
         */
        public interface Decoder extends HumanInterfaceDevice.ReportDescriptor.Decoder<Integer, AnalogRegistry> {
        }

        /**
         * Decoder-listener type alias for the analog device.
         */
        public interface DecoderListener extends HumanInterfaceDevice.ReportDescriptor.DecoderListener<Integer, AnalogRegistry> {
        }
    }
}
