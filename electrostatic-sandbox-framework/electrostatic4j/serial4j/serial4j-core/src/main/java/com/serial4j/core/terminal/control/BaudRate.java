/*
 * termios type and macro definitions.  Linux version.
 * Copyright (C) 1993-2019 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * The GNU C Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/>.
 *
 *  -----------------------------------------------------------------------
 *
 * BSD 3-Clause License for Serial4j from the AVR-Sandbox Project.
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
package com.serial4j.core.terminal.control;

import com.serial4j.core.terminal.control.NativeTerminalFlags.ControlFlags.MaskBits;

/**
 * Represents codes for the POSIX Systems baud rates and their real values
 * defined from "/usr/include/x86_64-linux-gnu/bits/termios.h".
 *
 * @author pavl_g.
 */
public enum BaudRate {

    /* Baud-rates for POSIX systems as defined by "termios.h" */
    B0(MaskBits.getBaud0(), 0),
    B50(MaskBits.getBaud50(), 50),
    B75(MaskBits.getBaud75(), 75),
    B110(MaskBits.getBaud110(), 110),
    B134(MaskBits.getBaud134(), 134),
    B150(MaskBits.getBaud150(), 150),
    B200(MaskBits.getBaud200(), 200),
    B300(MaskBits.getBaud300(), 300),
    B600(MaskBits.getBaud600(), 600),
    B1200(MaskBits.getBaud1200(), 1200),
    B1800(MaskBits.getBaud1800(), 1800),
    B2400(MaskBits.getBaud2400(), 2400),
    B4800(MaskBits.getBaud4800(), 4800),
    B9600(MaskBits.getBaud9600(), 9600),
    B19200(MaskBits.getBaud19200(), 19200),
    B38400(MaskBits.getBaud38400(), 38400),
    B57600(MaskBits.getBaud57600(), 57600),
    B115200(MaskBits.getBaud115200(), 115200),
    B230400(MaskBits.getBaud230400(), 230400),
    B460800(MaskBits.getBaud460800(), 460800),
    B500000(MaskBits.getBaud500000(), 500000),
    B576000(MaskBits.getBaud576000(), 576000),
    B921600(MaskBits.getBaud921600(), 921600),
    B1000000(MaskBits.getBaud1000000(), 1000000),
    B1152000(MaskBits.getBaud1152000(), 1152000),
    B1500000(MaskBits.getBaud1500000(), 1500000),
    B2000000(MaskBits.getBaud2000000(), 2000000),
    B2500000(MaskBits.getBaud2500000(), 2500000),
    B3000000(MaskBits.getBaud3000000(), 3000000),
    B3500000(MaskBits.getBaud3500000(), 3500000),
    B4000000(MaskBits.getBaud4000000(), 4000000),
    MAX_BAUD(B4000000.getBaudRate(), B4000000.getRealBaud());

    private final int baudRate;
    private final int realBaud;

    /**
     * Defines a basic structure for POSIX baud rates.
     *
     * @param baudRate the baud rate representative POSIX code.
     * @param realBaud the real baud value.
     */
    BaudRate(final int baudRate, final int realBaud) {
        this.baudRate = baudRate;
        this.realBaud = realBaud;
    }

    /**
     * Retrieves the real baud rate value from the baud
     * rate structure defined by the POSIX code.
     *
     * @return the real baud rate.
     */
    public int getRealBaud() {
        return realBaud;
    }

    /**
     * Retrieves the baud rate code defined from "termios.h" for
     * POSIX systems.
     *
     * @return the code for this baud rate.
     */
    public int getBaudRate() {
        return baudRate;
    }
}
