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

/**
 * Defines an interface for the POSIX terminal flags.
 *
 * @author pavl_g
 */
public final class NativeTerminalFlags {

    private NativeTerminalFlags() {
    }

    /**
     * Input flags.
     */
    public static final class InputFlags {

        private InputFlags() {
        }

        static native int getSignalInterrupt();

        static native int getMapCarriageReturnToNewLine();

        static native int getIgnoreBreakCondition();

        static native int getIgnoreCarriageReturn();

        static native int getIgnoreCharsWithParityErrors();

        static native int getRingBell();

        static native int getMapNewLineToCarriageReturn();

        static native int getEnableParityChecking();

        static native int getStripHighBit();

        static native int getInputIsUnicode8();

        static native int getMapUppercaseToLowercase();

        static native int getAllowToRestartStoppedOutput();

        static native int getEnableInputFlowControl();

        static native int getEnableOutputFlowControl();

        static native int getMarkParityErrors();
    }

    /**
     * Output Flags.
     */
    public static final class OutputFlags {

        private OutputFlags() {
        }

        /**
         * The "BSDLY" flag is the backspace delay mask (BS0, BS1).
         *
         * @return the value of the "BSDLY" flag
         */
        static native int getBackspaceDelayMask();

        static native int getCarriageReturnDelayMask();

        static native int getFormFeedDelayMask();

        static native int getNewLineDelayMask();

        static native int getMapCarriageReturnToNewLine();

        /**
         * Uses DEL (0177) as fill character; otherwise NUL (0).
         * <p>
         * The "OFDEL" output flag, is an obsolete flag.
         * </p>
         *
         * @return the value of the "OFDEL" flag
         */
        static native int getUsePredefinedFillCharacters();

        static native int getUseFillCharacters();

        static native int getMapLowercaseToUppercase();

        static native int getMapNewLineToCarriageReturn();

        static native int getNewLineAsCarriageReturn();

        static native int getNoCarriageReturnDuplicateOutput();

        static native int getPerformOutputPostProcessing();

        static native int getHorizontalTabDelayMask();

        static native int getVerticalTabDelayMask();

        public static final class MaskBits {
            private MaskBits() {
            }

            static native int getBackspace0();

            static native int getBackspace1();

            static native int getCarriageReturn0();

            static native int getCarriageReturn1();

            static native int getCarriageReturn2();

            static native int getCarriageReturn3();

            static native int getFormFeed0();

            static native int getFormFeed1();

            static native int getNewLineDelay0();

            static native int getNewLineDelay1();

            static native int getHorizontalTabDelay0();

            static native int getHorizontalTabDelay1();

            static native int getHorizontalTabDelay2();

            static native int getHorizontalTabDelay3();

            static native int getVerticalTabDelay0();

            static native int getVerticalTabDelay1();
        }
    }

    /**
     * Control Flags.
     */
    public static final class ControlFlags {
        private ControlFlags() {
        }

        static native int getBaudMask();

        static native int getExtendedBaudMask();

        static native int getInputBaudRate();

        static native int getIgnoreModemStatusLines();

        static native int getUseStickParity();

        static native int getAllowInput();

        static native int getEnableHardwareFlowControl();

        static native int getCharacterSizeMask();

        static native int getUse2StopBitsPerCharacter();

        static native int getHangUpOnLastClose();

        static native int getParityEnable();

        static native int getUseOddParity();

        public static final class MaskBits {
            private MaskBits() {
            }

            /* CBAUD mask bits */
            static native int getBaud0();
            static native int getBaud50();
            static native int getBaud75();
            static native int getBaud110();
            static native int getBaud134();
            static native int getBaud150();
            static native int getBaud200();
            static native int getBaud300();
            static native int getBaud600();
            static native int getBaud1200();
            static native int getBaud1800();
            static native int getBaud2400();
            static native int getBaud4800();
            static native int getBaud9600();
            static native int getBaud19200();
            static native int getBaud38400();

            /* CBAUDEX Mask bits */
            static native int getBaud57600();
            static native int getBaud115200();
            static native int getBaud230400();
            static native int getBaud460800();
            static native int getBaud500000();
            static native int getBaud576000();
            static native int getBaud921600();
            static native int getBaud1000000();
            static native int getBaud1152000();
            static native int getBaud1500000();
            static native int getBaud2000000();
            static native int getBaud2500000();
            static native int getBaud3000000();
            static native int getBaud3500000();
            static native int getBaud4000000();

            /* CSIZE mask bits*/
            static native int getCharacterSize5bits();

            static native int getCharacterSize6bits();

            static native int getCharacterSize7bits();

            static native int getCharacterSize8bits();
        }
    }


    /**
     * Local Flags.
     */
    public static final class LocalFlags {
        private LocalFlags() {
        }

        static native int getEchoInputCharacters();

        static native int getEchoControlCharacters();

        static native int getEchoErase();

        static native int getEchoKill();

        static native int getDisableNewLineAfterEchoKill();

        static native int getEchoNewLine();

        static native int getEchoDeletedCharactersBackward();

        static native int getOutputBeingFlushed();

        static native int getCanonicalModeInput();

        static native int getEnableExtendedProcessingOfInput();

        static native int getEnableSignalGeneratingCharacters();

        static native int getDisableFlushing();

        static native int getRedisplayPendingInput();

        /**
         * The "TOSTOP" flag, when enabled it provides an extra protection for the terminal
         * by terminating the background processes that try to write to it via signaling a "SIGTTOU"
         * standing for "Signal Teletype Output".
         *
         * @return the value of the "TOSTOP" flag
         */
        static native int getGenerateTerminateSignalForBackgroundProcess();

        static native int getCanonicalPresentation();

    }
}
