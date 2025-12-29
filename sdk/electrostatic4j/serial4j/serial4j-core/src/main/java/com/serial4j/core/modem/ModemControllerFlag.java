/*
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

package com.serial4j.core.modem;

import com.serial4j.core.flag.AppendableFlag;
import com.serial4j.core.flag.FlagConst;

/**
 * Manipulates and controls the modem lines for the original RS232 interface.
 *
 * @author pavl_g
 */
public final class ModemControllerFlag extends AppendableFlag {


    /**
     * Wraps a POSIX modem controller flag.
     *
     * @param value       the value of the flag.
     * @param description the description of the flag.
     */
    public ModemControllerFlag(int value, String description) {
        super(value, description);
    }

    /**
     * Builds a new empty modem controller flag.
     *
     * @return a new instance
     */
    public static ModemControllerFlag build() {
        return (ModemControllerFlag) AppendableFlag.build(ModemControllerFlag.class);
    }

    /**
     * Builds a new modem controller flag from a 32-bit integer substrate.
     *
     * @param substrate the 32-bit integer substrate
     * @return a new instance holding the values of the substrate
     */
    public static ModemControllerFlag from(final int substrate) {
        final ModemControllerFlag mcf = ModemControllerFlag.build();
        mcf.value = substrate;

        if (mcf.isLEEnabled()) {
            mcf.append(ModemBits.TIOCM_LE);
        }
        if (mcf.isDTREnabled()) {
            mcf.append(ModemBits.TIOCM_DTR);
        }
        if (mcf.isRTSEnabled()) {
            mcf.append(ModemBits.TIOCM_RTS);
        }
        if (mcf.isSTEnabled()) {
            mcf.append(ModemBits.TIOCM_ST);
        }
        if (mcf.isSREnabled()) {
            mcf.append(ModemBits.TIOCM_SR);
        }
        if (mcf.isCTSEnabled()) {
            mcf.append(ModemBits.TIOCM_CTS);
        }
        if (mcf.isCAREnabled()) {
            mcf.append(ModemBits.TIOCM_CAR);
        }
        if (mcf.isRNGEnabled()) {
            mcf.append(ModemBits.TIOCM_RNG);
        }
        if (mcf.isDSREnabled()) {
            mcf.append(ModemBits.TIOCM_DSR);
        }

        return mcf;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_LE} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isLEEnabled() {
        return (value & ModemBits.TIOCM_LE.value) ==
                ModemBits.TIOCM_LE.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_DTR} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isDTREnabled() {
        return (value & ModemBits.TIOCM_DTR.value) ==
                ModemBits.TIOCM_DTR.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_RTS} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isRTSEnabled() {
        return (value & ModemBits.TIOCM_RTS.value) ==
                ModemBits.TIOCM_RTS.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_ST} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isSTEnabled() {
        return (value & ModemBits.TIOCM_ST.value) ==
                ModemBits.TIOCM_ST.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_SR} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isSREnabled() {
        return (value & ModemBits.TIOCM_SR.value) ==
                ModemBits.TIOCM_SR.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_CTS} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isCTSEnabled() {
        return (value & ModemBits.TIOCM_CTS.value) ==
                ModemBits.TIOCM_CTS.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_CAR} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isCAREnabled() {
        return (value & ModemBits.TIOCM_CAR.value) ==
                ModemBits.TIOCM_CAR.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_RNG} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isRNGEnabled() {
        return (value & ModemBits.TIOCM_RNG.value) ==
                ModemBits.TIOCM_RNG.value;
    }

    /**
     * Tests whether the {@link ModemBits#TIOCM_DSR} is enabled
     * in this flag.
     *
     * @return true if enabled, or false otherwise
     */
    public boolean isDSREnabled() {
        return (value & ModemBits.TIOCM_DSR.value) ==
                ModemBits.TIOCM_DSR.value;
    }

    /**
     * Defines the modem bits (pins) covered by the standard RS232 DB-25 Standard.
     */
    public enum ModemBits implements FlagConst {

        /**
         * DSR Line enable bit.
         */
        TIOCM_LE(NativeModemBits.getDatasetReadyLineEnable(), "DSR (data set ready/line enable)"),

        /**
         * The DTR bit should be set to HIGH when the DTE (terminal) has been initialized.
         */
        TIOCM_DTR(NativeModemBits.getDataTerminalReady(), "DTR (data terminal ready)"),

        /**
         * The RTS bit should be set to HIGH when the DTE (terminal) has some data to transmit out of the
         * terminal output queue.
         */
        TIOCM_RTS(NativeModemBits.getRequestToSend(), "RTS (request to send)"),

        /**
         * Reserved for the standard DB-25.
         */
        TIOCM_ST(NativeModemBits.getSecondaryTransmit(), "Secondary TXD (transmit)"),

        /**
         * Reserved for the standard DB-25.
         */
        TIOCM_SR(NativeModemBits.getSecondaryReceive(), "Secondary RXD (receive)"),

        /**
         * In response to RTS, when the modem has room to store
         * the data it is to receive, it sends out signal CTS to the DTE (PC) to indicate
         * that it can receive the data now. This input signal to the DTE is used by the
         * DTE to start transmission.
         */
        TIOCM_CTS(NativeModemBits.getClearToSend(), "CTS (clear to send)"),

        /**
         * The modem asserts signal DCD to inform the DTE
         * (PC) that a valid carrier has been detected and that contact between it and the
         * other modem is established.
         */
        TIOCM_CAR(NativeModemBits.getDataCarrierDetect(), "DCD (data carrier detect)"),

        /**
         * An output from the modem (DCE) and an input to a PC
         * (DTE) indicates that the telephone is ringing
         */
        TIOCM_RNG(NativeModemBits.getRingSignal(), "RNG (ring)"),

        /**
         * The DSR bit should be set to HIGH when the DCE (modem) is ready to communicate.
         */
        TIOCM_DSR(NativeModemBits.getDataSetReady(), "DSR (data set ready)");

        private final int value;
        private final String description;

        ModemBits(final int value, final String description) {
            this.value = value;
            this.description = description;
        }

        @Override
        public int getValue() {
            return value;
        }

        @Override
        public String getDescription() {
            return description;
        }
    }
}
