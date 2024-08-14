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

import com.serial4j.core.flag.AppendableFlag;
import com.serial4j.core.flag.FlagConst;

/**
 * A GPIO module composed of 8-bits.
 *
 * @author pavl_g
 */
public class GpioModule extends AppendableFlag {

    public GpioModule(int value, String description) {
        super(value, description);
    }

    public static GpioModule build() {
        return (GpioModule) AppendableFlag.build(GpioModule.class);
    }

    public record Pin(int value) implements FlagConst {
        public static Pin GPIO_0 = new Pin(0x00);
        public static Pin GPIO_1 = new Pin(0x01);
        public static Pin GPIO_2 = new Pin(0x02);
        public static Pin GPIO_3 = new Pin(0x03);
        public static Pin GPIO_4 = new Pin(0x04);
        public static Pin GPIO_5 = new Pin(0x05);
        public static Pin GPIO_6 = new Pin(0x06);
        public static Pin GPIO_7 = new Pin(0x07);

        @Override
        public int getValue() {
            return value;
        }

        @Override
        public String getDescription() {
            return "Gpio-Module-Pin";
        }
    }
}
