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

package com.serial4j.core.hid.device.standard.component.digital;

import com.serial4j.core.hid.StandardSerialDevice;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.TerminalDevice;

/**
 * Defines a specification for a GPIO module device composed of 8
 * I/O pins.
 *
 * @author pavl_g
 */
public class Gpio8ModuleDevice extends StandardSerialDevice<Integer, GpioRegistry> {

    public Gpio8ModuleDevice(TerminalDevice terminalDevice, SerialPort serialPort) {
        super(terminalDevice, serialPort);
    }

    @Override
    public void init() {
        super.init();
        setReportDescriptor(new GpioReportDescriptor());
        setDecoder(new GpioRegistry.Decoder());
    }

    @Override
    public void receive() {
        super.decode(dataRegisterBufferLength -> {
            if (terminalDevice.iread(dataRegisterBufferLength) == 0) {
                return null;
            }
            final int[] data = new int[] { 
                terminalDevice.getBuffer()[0] 
            };
            return data[0];
        });
    }

    @Override
    public void transmit(GpioRegistry decoded) {
        super.encode(encoded -> terminalDevice.write(new int[] { encoded }), decoded);
    }

    @Override
    public String getVendor() {
        return "GPIO-Module-Serial-HID";
    }

    public static class GpioReportDescriptor implements ReportDescriptor {

        @Override
        public int getReportLength() {
            return 1; // 1 byte report
        }

        @Override
        public int getDataRegisterBufferLength() {
            return 1;
        }


        public interface Decoder extends ReportDescriptor.Decoder<Integer, GpioRegistry> {
        }

        public interface DecoderListener extends ReportDescriptor.DecoderListener<Integer, GpioRegistry> {
        }
    }
}
