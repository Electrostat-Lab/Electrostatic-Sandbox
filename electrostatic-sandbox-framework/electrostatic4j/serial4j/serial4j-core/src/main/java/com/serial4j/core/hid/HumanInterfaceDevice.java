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

package com.serial4j.core.hid;

import com.serial4j.core.hid.device.dataframe.DataFrameDevice;
import java.util.function.Function;

/**
 * A Human Interface Device is an abstract interactive interface that
 * defines standards of sending and receiving data packets between
 * devices wherein a report descriptor {@link ReportDescriptor}
 * represents the raw data packets in which data is organized generally
 * as [address = data] or [address, data], a {@link ReportDescriptor.Decoder}
 * is capable of decoding/encoding data packets after which attached listeners could
 * be dispatched to receive those post-processed packets.
 *
 * <p>
 * This simple API is based on the linux hid, for more use:
 * <a href="https://docs.kernel.org/hid">Linux-HID</a>
 * </p>
 *
 * @param <D> a type-arg for the decoded (concrete) post-processed data
 * @author pavl_g
 * @see DataFrameDevice Demo Joystick Serial-HID
 */
@SuppressWarnings("all")
public abstract class HumanInterfaceDevice<E, D> implements AutoCloseable, Cloneable {

    /**
     * An associated report descriptor that provides descriptive
     * data for IO packets.
     */
    protected ReportDescriptor reportDescriptor;

    /**
     * An associated listener to be dispatched as a part of the
     * post-processing encoding/decoding operations performed by
     * the associated decoder {@link HumanInterfaceDevice#decoder},
     * typically utilized as a user-code.
     */
    protected ReportDescriptor.DecoderListener<E, D> decoderListener;

    /**
     * An associated decoder that provides the interface for the
     * liberty of assigning decoding/encoding algorithms that would
     * run as a part of post raw IO operations, and before the dispatch
     * of the {@link HumanInterfaceDevice#decoderListener}, typically
     * utilized as a part of the defined HID standards (API code).
     */
    protected ReportDescriptor.Decoder<E, D> decoder;

    /**
     * Not directly instantiable class, inheritance
     * is required to provide full-functionality.
     */
    protected HumanInterfaceDevice() {
    }

    /**
     * Retrieves the reference to the report descriptor.
     *
     * @return the reference to the device-associated report descriptor
     */
    public ReportDescriptor getReportDescriptor() {
        return reportDescriptor;
    }

    /**
     * Sets the report descriptor object, the report descriptor is the data packet
     * for the I/O operations.
     *
     * @param reportDescriptor a report descriptor object
     */
    public void setReportDescriptor(ReportDescriptor reportDescriptor) {
        this.reportDescriptor = reportDescriptor;
    }

    /**
     * Retrieves the decoder listeners, listeners are getting dispatched
     * as a part of the decoder post-processing operations, typically
     * utilized in user-code.
     *
     * @return a reference to the decoder listener component
     */
    public ReportDescriptor.DecoderListener<E, D> getDecoderListener() {
        return decoderListener;
    }

    /**
     * Sets the decoder listeners, listeners are getting dispatched
     * as a part of the decoder post-processing operations, typically
     * utilized in user-code.
     *
     * @param decoderListener a reference to the decoder listener
     */
    public void setDecoderListener(ReportDescriptor.DecoderListener<E, D> decoderListener) {
        this.decoderListener = decoderListener;
    }

    /**
     * Retrieves the report decoder object associated with
     * this device, the decoder job is decode/encode data
     * packets (reports) after/before being received/sent,
     * respectively.
     *
     * @return a reference to the report descriptor decoder instance
     */
    public ReportDescriptor.Decoder<E, D> getDecoder() {
        return decoder;
    }

    /**
     * Sets the report descriptor decoder instance.
     *
     * @param decoder the new decoder instance used for encoding/decoding data
     */
    protected void setDecoder(ReportDescriptor.Decoder<E, D> decoder) {
        this.decoder = decoder;
    }

    /**
     * Override to provide initialization code for this device,
     *
     * <p>
     * Initialization code could include: opening the device, sending
     * feature reports, initializing line-speeds, and more.
     * </p>
     */
    public abstract void init();

    /**
     * Override to provide stream/IO/memory release operations.
     */
    @Override
    public void close() {
        reportDescriptor = null;
        decoderListener = null;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * Override to provide receiving and decoding algorithms,
     * usually a call to {@link HumanInterfaceDevice#decode(Function)} is made
     * with different parameter sets according to the device standards.
     */
    public abstract void receive();

    /**
     * Override to provide encoding and transmitting algorithms,
     * usually a call to {@link HumanInterfaceDevice#encode(Function, Object)} is made
     * with different parameter sets according to the device standards.
     *
     * @param decoded the decoded report to encode and send
     */
    public abstract void transmit(final D decoded);

    /**
     * Device vendor data.
     *
     * @return the device vendors in string format
     */
    public abstract String getVendor();

    /**
     * Defines a default algorithm for executing decoding post-read operations.
     *
     * <p>
     * A call to this function dispatches the function
     * {@link ReportDescriptor.DecoderListener#onDecodingCompleted(Object)}
     * as a part of post-processing user operations.
     * </p>
     *
     * @param read a reference to the device read() function to dispatch
     */
    protected final void decode(final Function<Integer, E> read) {
        // read report with data register buffer length
        final E encoded = read.apply(reportDescriptor.getDataRegisterBufferLength());
        if (encoded == null) {
            return;
        }
        final D concreteData = decoder.decode(encoded);
        if (decoderListener != null) {
            decoderListener.onDecodingCompleted(concreteData);
        }
    }

    /**
     * Defines a default algorithm for encoding data packets before
     * being sent.
     *
     * <p>
     * A call to this function dispatches the function
     * {@link ReportDescriptor.DecoderListener#onEncodingCompleted(Object)}
     * as a part of post-processing user operations.
     * </p>
     *
     * @param write    a reference to the device write() function to dispatch
     * @param decoded a decoded (concrete) data packet to be encoded before
     *                 being sent to the device
     */
    protected final long encode(final Function<E, Long> write, final D decoded) {
        final E encoded = decoder.encode(decoded);
        if (encoded == null) {
            return 0;
        }
        final long bytes = write.apply(encoded);
        if (decoderListener != null && bytes > 0) {
            decoderListener.onEncodingCompleted(encoded);
        }
        return bytes;
    }

    /**
     * Defines the simplest form of the
     * report type with a length attribute in bytes units.
     */
    protected interface ReportDescriptor {

        /**
         * Defines the total report length in "bytes".
         *
         * <p>
         * Example: 1 for 1 byte (char), 4 for 4 bytes (int).
         * </p>
         *
         * @return report length in bytes
         */
        int getReportLength();

        /**
         * Defines the size of the data register buffer
         * required for reading operations in "bytes".
         *
         * <p>
         * For 8-bit microcontrollers, this should be 1-byte (aka. 8-bits).
         * Unlike the report length, this attribute defines the data length
         * per frame (per single clock transmission).
         * </p>
         *
         * @return the input buffer length in bytes
         */
        int getDataRegisterBufferLength();

        /**
         * Defines a standard to decode/encode data
         * packets for this report descriptor.
         *
         * @param <D> the type of the decoded data packets
         */
        interface Decoder<E, D> {

            /**
             * Encodes concrete data packets before sending
             * to the device.
             *
             * @param decoded the data data packet to encode.
             * @return an encoded version of the data packet ready to send
             * to the I/O pipeline
             */
            E encode(D decoded);

            /**
             * Decodes received raw data packets into a concrete version.
             *
             * @param encoded the raw received data packets
             * @return a decoded version of the received data packets
             */
            D decode(E encoded);
        }

        /**
         * Defines a dispatch listener that is dispatched
         * when decoding/encoding completes, usually this
         * is a user-side API.
         *
         * @param <D> the type of the decoded data packets
         */
        interface DecoderListener<E, D> {

            /**
             * Dispatched when encoding a data packet completes
             * before sending it to the device.
             *
             * @param encoded the raw data packets
             */
            void onEncodingCompleted(E encoded);

            /**
             * Dispatched when decoding a received data packet completes.
             *
             * @param decoded the decoded data packets
             */
            void onDecodingCompleted(D decoded);
        }
    }
}