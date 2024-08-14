package com.serial4j.core.hid.device.standard.mouse;

import com.serial4j.core.flag.FlagConst;

/**
 * A mouse registry represents a standardized data
 * structure that contains decoded ready-to-operate-on data.
 *
 * @param buttons the mouse buttons
 * @param deviceSpecific the device specific bits
 * @param pointer the mouse pointer data (X and Y)
 */
public record MouseRegistry(Buttons buttons,
                            DeviceSpecific deviceSpecific,
                            Pointer pointer) {

    /**
     * A registry component consisting of 3 buttons.
     *
     * @param button1 the first button
     * @param button2 the second button
     * @param button3 the third button
     */
    public record Buttons(int button1, int button2, int button3) {
    }

    /**
     * A registry component representing the mouse pointer
     * (relative X and Y variables).
     *
     * @param x the x-coordinate value
     * @param y the y-coordinate value
     */
    public record Pointer(int x, int y) {
    }

    /**
     * Device specific bits for validations.
     *
     * @param spec1 first byte
     * @param spec2 second byte
     */
    public record DeviceSpecific(int spec1, int spec2) {
    }

    public static class Decoder implements StandardMouseDevice.ReportDescriptor.Decoder {

        @Override
        public Integer encode(MouseRegistry decoded) {
            throw new UnsupportedOperationException("Cannot send data!");
        }

        @Override
        public MouseRegistry decode(Integer encoded) {
            return new MouseRegistry(
                  new Buttons(Bits.BUTTON_1.value & encoded, Bits.BUTTON_2.value & encoded, Bits.BUTTON_3.value & encoded),
                  new DeviceSpecific(Bits.DEVICE_1.value & encoded, Bits.DEVICE_2.value & encoded),
                  new Pointer(Bits.X_POINTER.value & encoded, Bits.Y_POINTER.value & encoded)
            );
        }
    }

    public record Bits(int value) implements FlagConst {
        public static final Bits BUTTON_1 = new Bits(0x00000000);
        public static final Bits BUTTON_2 = new Bits(0x00000001);
        public static final Bits BUTTON_3 = new Bits(0x00000002);
        public static final Bits DEVICE_1 = new Bits(0x000000F0);
        public static final Bits X_POINTER = new Bits(0x0000FF00);
        public static final Bits Y_POINTER = new Bits(0x00FF0000);
        public static final Bits DEVICE_2 = new Bits(0xFF000000);

        @Override
        public int getValue() {
            return value;
        }

        @Override
        public String getDescription() {
            return "Mouse-Bits";
        }
    }
}
