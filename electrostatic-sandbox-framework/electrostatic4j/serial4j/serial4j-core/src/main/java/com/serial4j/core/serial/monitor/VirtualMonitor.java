package com.serial4j.core.serial.monitor;

import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.entity.impl.SerialReadEntity;
import com.serial4j.core.serial.entity.impl.SerialWriteEntity;
import com.serial4j.core.serial.throwable.*;
import com.serial4j.core.terminal.FilePermissions;
import com.serial4j.core.terminal.NativeBufferInputStream;
import com.serial4j.core.terminal.NativeBufferOutputStream;
import com.serial4j.core.terminal.control.BaudRate;

/**
 * A virtual monitor isolates the {@link SerialReadEntity} and the {@link SerialWriteEntity}
 * actions from the terminal based operations, the virtual monitor can act on both regular and
 * terminal files, as well, it just isolates the native IO operations.
 *
 * <p>
 * The virtual monitor is a unit test API by itself that should be
 * used to assert the correctness of the changes to the terminal IO API before pushing changes.
 *
 * @author pavl_g
 */
public class VirtualMonitor extends SerialMonitor {

    /**
     * Instantiates a new virtual monitor with a name (acting on filesystem only).
     * <p>
     * Use {@link SerialMonitor#startDataMonitoring(String, BaudRate, FilePermissions)} to initialize and start
     * data monitoring.
     * </p>
     *
     * @param monitorName the name for this monitor.
     */
    public VirtualMonitor(String monitorName) {
        super(monitorName);
    }

    @Override
    public void startDataMonitoring(String port, BaudRate baudRate, FilePermissions filePermissions) throws NoSuchDeviceException,
            PermissionDeniedException, BrokenPipeException, InvalidPortException, NoAvailableTtyDevicesException {

        terminalDevice.setSerial4jLoggingEnabled(true);
        if (filePermissions != null) {
            terminalDevice.setOperativeFilePermissions(filePermissions);
        }

        readEntityStream = new NativeBufferInputStream(terminalDevice);
        writeEntityStream = new NativeBufferOutputStream(terminalDevice);

        serialWriteEntity = new SerialWriteEntity(this);
        serialReadEntity = new SerialReadEntity(this);

        terminalDevice.openPort(new SerialPort(port));

        final FilePermissions userAccessPermissions = (FilePermissions) FilePermissions.build()
                                                .append(FilePermissions.AccessModeConst.S_IRWXU);

        terminalDevice.chmod(userAccessPermissions);

        monitorThread = new Thread(() -> {
            while (!isTerminate()) {
                /* change mode access and start data monitoring */
                serialWriteEntity.run();
                serialReadEntity.run();
            }
        }, monitorName);

        monitorThread.start();
    }
}