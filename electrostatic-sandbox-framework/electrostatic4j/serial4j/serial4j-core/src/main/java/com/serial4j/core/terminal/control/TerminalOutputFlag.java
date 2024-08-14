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
package com.serial4j.core.terminal.control;

import com.serial4j.core.flag.FlagConst;

/**
 * Provides the POSIX constants that control the terminal
 * driver output queue.
 *
 * @author pavl_g
 */
public enum TerminalOutputFlag implements FlagConst {
    BSDLY(NativeTerminalFlags.OutputFlags.getBackspaceDelayMask()),
    CRDLY(NativeTerminalFlags.OutputFlags.getCarriageReturnDelayMask()),
    FFDLY(NativeTerminalFlags.OutputFlags.getFormFeedDelayMask()),
    NLDLY(NativeTerminalFlags.OutputFlags.getNewLineDelayMask()),
    OCRNL(NativeTerminalFlags.OutputFlags.getMapCarriageReturnToNewLine()),
    OFDEL(NativeTerminalFlags.OutputFlags.getUsePredefinedFillCharacters()),
    OFILL(NativeTerminalFlags.OutputFlags.getUseFillCharacters()),
    OLCUC(NativeTerminalFlags.OutputFlags.getMapLowercaseToUppercase()),
    ONLCR(NativeTerminalFlags.OutputFlags.getMapNewLineToCarriageReturn()),
    ONLRET(NativeTerminalFlags.OutputFlags.getNewLineAsCarriageReturn()),
    ONOCR(NativeTerminalFlags.OutputFlags.getNoCarriageReturnDuplicateOutput()),
    OPOST(NativeTerminalFlags.OutputFlags.getPerformOutputPostProcessing()),
    TABDLY(NativeTerminalFlags.OutputFlags.getHorizontalTabDelayMask()),
    VTDLY(NativeTerminalFlags.OutputFlags.getVerticalTabDelayMask());

    private final int value;

    private TerminalOutputFlag(final int value) {
        this.value = value;
    }

    @Override
    public int getValue() {
        return value;
    }

    @Override
    public String getDescription() {
        return null;
    }

    public enum MaskBits implements FlagConst {
        BS0(NativeTerminalFlags.OutputFlags.MaskBits.getBackspace0()),
        BS1(NativeTerminalFlags.OutputFlags.MaskBits.getBackspace1()),
        CR0(NativeTerminalFlags.OutputFlags.MaskBits.getCarriageReturn0()),
        CR1(NativeTerminalFlags.OutputFlags.MaskBits.getCarriageReturn1()),
        CR2(NativeTerminalFlags.OutputFlags.MaskBits.getCarriageReturn2()),
        CR3(NativeTerminalFlags.OutputFlags.MaskBits.getCarriageReturn3()),
        FF0(NativeTerminalFlags.OutputFlags.MaskBits.getFormFeed0()),
        FF1(NativeTerminalFlags.OutputFlags.MaskBits.getFormFeed1()),
        NL0(NativeTerminalFlags.OutputFlags.MaskBits.getNewLineDelay0()),
        NL1(NativeTerminalFlags.OutputFlags.MaskBits.getNewLineDelay1()),
        TAB0(NativeTerminalFlags.OutputFlags.MaskBits.getHorizontalTabDelay0()),
        TAB1(NativeTerminalFlags.OutputFlags.MaskBits.getHorizontalTabDelay1()),
        TAB2(NativeTerminalFlags.OutputFlags.MaskBits.getHorizontalTabDelay2()),
        TAB3(NativeTerminalFlags.OutputFlags.MaskBits.getHorizontalTabDelay3()),
        VT0(NativeTerminalFlags.OutputFlags.MaskBits.getVerticalTabDelay0()),
        VT1(NativeTerminalFlags.OutputFlags.MaskBits.getVerticalTabDelay1());

        private final int value;

        MaskBits(final int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }

        @Override
        public String getDescription() {
            return null;
        }
    }
}
