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

package com.serial4j.core.hid.device.dataframe.registry;

import com.serial4j.core.hid.device.dataframe.DataFrameDevice;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * The shift-avr Joystick interface device report descriptor provides
 * the standard decoder that decodes raw string data into
 * {X} and {Y} readings.
 *
 * <p>
 * The descriptor report is defined by a data frame of max
 * number of bytes and byte-order as following: [x = 1023, y = 1023]\n\r
 * </p>
 *
 * @param x the decoded X-coordinate value
 * @param y the decoded Y-coordinate value
 * @author pavl_g
 */
public record JoystickRegistry(int x, int y, int b) {

    @Override
    public String toString() {
        return "JoystickRegistry = [" +
                "x=" + x +
                ", y=" + y +
                ", b=" + b +
                ']';
    }

    /**
     * The Report descriptor decoder that is dispatched by the
     * {@link DataFrameDevice} to decode the data reports into {@link JoystickRegistry}s.
     */
    public static class Decoder implements DataFrameDevice.ReportDescriptor.Decoder<JoystickRegistry> {
        private static int getPotentiometerValue(String frame, int index, char delimiter) {
            final StringBuilder data = new StringBuilder();
            for (int i = index; frame.charAt(i) != delimiter; i++) {
                data.append(frame.charAt(i));
            }
            return Integer.parseInt(data.toString());
        }

        @Override
        public String encode(JoystickRegistry data) {
            throw new UnsupportedOperationException("The Joystick HID is a read-only device!");
        }

        @Override
        public JoystickRegistry decode(String raw) {
            final String frame = raw.replace("\n\r", "");
            System.out.println(frame);
            int x = 0;
            int y = 0;
            int b = 0;

            try {
                for (int i = 0; i < frame.length(); i++) {
                    if (frame.charAt(i) == 'x') {
                        // i + 4 is the delimiter between the x and the value of x
                        x = getPotentiometerValue(frame, i + 4, ',');
                    } else if (frame.charAt(i) == 'y') {
                        // i + 4 is the delimiter between the 'y' and the value of y
                        y = getPotentiometerValue(frame, i + 4, ',');
                    } else if (frame.charAt(i) == 'b') {
                        b = getPotentiometerValue(frame, i + 4, ']');
                    }
                }
            } catch (Exception e) {
                x = 0;
                y = 0;
                b = 0;
                Logger.getLogger(DataFrameDevice.class.getName())
                        .log(Level.WARNING, "Decoding Fails with '" + e.getMessage() + "'", e.getCause());
            }

            return new JoystickRegistry(x, y, b);
        }
    }
}