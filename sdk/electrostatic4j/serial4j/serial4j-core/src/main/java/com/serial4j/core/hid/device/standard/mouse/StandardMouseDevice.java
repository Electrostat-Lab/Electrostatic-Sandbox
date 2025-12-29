package com.serial4j.core.hid.device.standard.mouse;

import com.serial4j.core.hid.HumanInterfaceDevice;
import com.serial4j.core.hid.StandardSerialDevice;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.util.Constants;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Defines a standard for the mouse devices with 3 buttons,
 * and a pointer (X and Y values).
 *
 * @author pavl_g
 */
public class StandardMouseDevice extends StandardSerialDevice<Integer, MouseRegistry> {

    protected final AtomicInteger inputBuffer = new AtomicInteger(0);
    protected final AtomicInteger inputClock = new AtomicInteger(0);

    public StandardMouseDevice(TerminalDevice terminalDevice, SerialPort serialPort) {
        super(terminalDevice, serialPort);
    }

    @Override
    public void init() {
        super.init();
        setReportDescriptor(new ReportDescriptor());
        setDecoder(new MouseRegistry.Decoder());
    }

    @Override
    public void receive() {
        super.decode(dataRegisterBufferLength -> {
            for (int frame = 0; terminalDevice.iread(dataRegisterBufferLength) > 0 &&
                    frame < reportDescriptor.getReportLength(); frame++, inputClock.incrementAndGet()) {
                final int data = terminalDevice.getBuffer()[0];
                final int bits = frame * Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH;
                inputBuffer.set(inputBuffer.get() | (data << bits));
                if (inputClock.get() == (reportDescriptor.getReportLength() - 1)) {
                    final int value = inputBuffer.get();
                    inputBuffer.set(0); // flush the input buffer
                    inputClock.set(0);
                    return value;
                }
            }
            return null;
        });
    }

    @Override
    public void transmit(MouseRegistry decoded) {
        throw new UnsupportedOperationException("Writing data is not supported by default!");
    }

    @Override
    public String getVendor() {
        return "Mouse-Serial-HID";
    }

    @Override
    public void close() {
        inputClock.set(0);
        inputBuffer.set(0); // flush the input buffer
        super.close(); // close the port and release the native resources
    }

    public AtomicInteger getInputBuffer() {
        return inputBuffer;
    }

    public static class ReportDescriptor implements HumanInterfaceDevice.ReportDescriptor {
        @Override
        public int getReportLength() {
            // 4 bytes of data (short item)
            return Constants.STANDARD_MOUSE_BITS / Constants.DEFAULT_DATA_REGISTER_BUFFER_LENGTH;
        }

        @Override
        public int getDataRegisterBufferLength() {
            return 1;
        }

        public interface Decoder extends HumanInterfaceDevice.ReportDescriptor.Decoder<Integer, MouseRegistry> {
        }

        public interface DecoderListener extends HumanInterfaceDevice.ReportDescriptor.DecoderListener<Integer, MouseRegistry> {
        }
    }
}
