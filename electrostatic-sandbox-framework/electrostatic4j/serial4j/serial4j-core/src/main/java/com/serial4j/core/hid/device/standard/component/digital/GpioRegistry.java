package com.serial4j.core.hid.device.standard.component.digital;

public record GpioRegistry(int pin0, int pin1, int pin2, int pin3,
                           int pin4, int pin5, int pin6, int pin7) {
    public static class Decoder implements Gpio8ModuleDevice.GpioReportDescriptor.Decoder {
        @Override
        public Integer encode(GpioRegistry decoded) {
            final GpioModule gpioModule = GpioModule.build();
            gpioModule.append(
                    new GpioModule.Pin(decoded.pin0), new GpioModule.Pin(decoded.pin1),
                    new GpioModule.Pin(decoded.pin2), new GpioModule.Pin(decoded.pin3),
                    new GpioModule.Pin(decoded.pin4), new GpioModule.Pin(decoded.pin5),
                    new GpioModule.Pin(decoded.pin6), new GpioModule.Pin(decoded.pin7)
            );
            return gpioModule.getValue();
        }

        @Override
        public GpioRegistry decode(Integer encoded) {
            return new GpioRegistry(
                encoded & GpioModule.Pin.GPIO_0.getValue(),
                encoded & GpioModule.Pin.GPIO_1.getValue(),
                encoded & GpioModule.Pin.GPIO_2.getValue(),
                encoded & GpioModule.Pin.GPIO_3.getValue(),
                encoded & GpioModule.Pin.GPIO_4.getValue(),
                encoded & GpioModule.Pin.GPIO_5.getValue(),
                encoded & GpioModule.Pin.GPIO_6.getValue(),
                encoded & GpioModule.Pin.GPIO_7.getValue()
            );
        }
    }
}
