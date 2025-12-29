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
package com.serial4j.core.serial.entity;

import com.serial4j.core.terminal.TerminalDevice;
import com.serial4j.core.serial.monitor.SerialDataListener;
import com.serial4j.core.serial.monitor.SerialMonitor;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Logger;
import java.util.logging.Level;
import java.io.Closeable;
import java.io.IOException;

/**
 * Represents the base implementation for serial monitor Read and Write entities.
 *
 * @author pavl_g.
 * @see com.serial4j.core.serial.entity.impl.SerialWriteEntity
 * @see com.serial4j.core.serial.entity.impl.SerialReadEntity
 */
public abstract class SerialMonitorEntity implements Runnable {

    /**
     * Provides thread-safety for the serial IO streaming operations.
     */
    protected final ReentrantLock reentrantLock = new ReentrantLock();

    private final Logger entityLogger;
    private final SerialMonitor serialMonitor;
    private final String entityName;
    private boolean hasLoggedMonitor;

    /**
     * Defines a serial monitor basic entity.
     *
     * @param serialMonitor the monitor object.
     * @param entityName    the entity name.
     */
    public SerialMonitorEntity(SerialMonitor serialMonitor, String entityName) {
        this.serialMonitor = serialMonitor;
        this.entityName = entityName;

        entityLogger = Logger.getLogger(entityName);
    }

    @Override
    public void run() {
        /* using re-entrant block to be optimized by the new v-threads system */
        try {
            reentrantLock.lock();
            logStart();
            onDataMonitored(getSerialMonitor());
        } finally {
            reentrantLock.unlock();
        }
    }

    /**
     * Provides a JUL logger object for descendant objects to re-use.
     *
     * @return this entity logger instance.
     */
    protected Logger getEntityLogger() {
        return entityLogger;
    }

    /**
     * Terminates this entity by closing the entity stream and the serial port.
     */
    protected void terminate() {
        try {
            getEntityStream().close();
            hasLoggedMonitor = false;
            entityLogger.log(Level.WARNING, "Terminated data monitoring for " + entityName + " thread " + Thread.currentThread());
        } catch (IOException e) {
            Logger.getLogger(SerialMonitorEntity.class.getName())
                    .log(Level.SEVERE, "Termination has failed!", e);
        }
        synchronized (SerialMonitorEntity.class) {
            if (getTerminalDevice().getSerialPort().isPortOpened()) {
                try {
                    getTerminalDevice().closePort();
                } catch (Exception e) {
                    Logger.getLogger(SerialMonitorEntity.class.getName())
                            .log(Level.SEVERE, "Port closure has failed!", e);
                }
            }
        }
    }

    private void logStart() {
        if (!hasLoggedMonitor) {
            return;
        }
        entityLogger.log(Level.INFO,
                "Started data monitoring for " + entityName + " thread " + Thread.currentThread());
        hasLoggedMonitor = false; // shut down logging
    }

    /**
     * Tests whether return carriage [\n\r] and new line is enabled.
     *
     * @return true if [\n\r] check is enabled, default value is [true].
     */
    protected boolean isProcessLinefeedCarriageReturn() {
        return getSerialMonitor().isProcessLinefeedCarriageReturn();
    }

    /**
     * Tests whether serial data monitoring has started.
     *
     * @return true if data monitor has started, default value is [false].
     */
    protected boolean isMonitoringStarted() {
        return getSerialMonitor().isMonitoringStarted;
    }

    /**
     * Sets the monitor started state.
     *
     * @param state true to indicate the monitor has started and to start the data
     *              writing, false otherwise.
     */
    protected void setMonitoringStarted(boolean state) {
        getSerialMonitor().isMonitoringStarted = state;
    }

    /**
     * Retrieves the {@link SerialMonitor} instance.
     *
     * @return the serial monitor object that holds this entity.
     */
    public SerialMonitor getSerialMonitor() {
        return serialMonitor;
    }

    /**
     * Retrieves the {@link TerminalDevice} instance used for creating the communication.
     *
     * @return a serial port instance.
     */
    protected TerminalDevice getTerminalDevice() {
        return getSerialMonitor().getTerminalDevice();
    }

    /**
     * Retrieves the serial data listener.
     *
     * @return a reference to the serial data listener instance
     */
    protected SerialDataListener getSerialDataListener() {
        return getSerialMonitor().getSerialDataListener();
    }

    /**
     * Tests whether the serial monitor holding this entity terminated.
     *
     * @return true if the serial monitor has been terminated by the user, default value is false.
     * @see SerialMonitor#setTerminate()
     */
    protected boolean isTerminate() {
        return getSerialMonitor().isTerminate();
    }

    /**
     * Fired on each update run.
     *
     * @param serialMonitor the serial monitor that holds this entity.
     */
    protected abstract void onDataMonitored(final SerialMonitor serialMonitor);

    /**
     * Gets the entity status listener.
     *
     * @return the serial entity status listener.
     */
    protected abstract EntityStatus<? extends SerialMonitorEntity> getSerialEntityStatusListener();

    /**
     * Tests whether the entity is initialized.
     *
     * @return true if the serial entity has been initialized, false otherwise, default value is false.
     */
    protected abstract boolean isSerialEntityInitialized();

    /**
     * Sets the serial entity initialized status.
     *
     * @param state a state to set.
     * @see SerialMonitor#isReadSerialEntityInitialized
     * @see SerialMonitor#isWriteSerialEntityInitialized
     */
    protected abstract void setSerialEntityInitialized(boolean state);

    /**
     * Retrieves the entity stream provided by the {@link com.serial4j.core.serial.SerialPort},
     * either {@link java.io.OutputStream} or {@link java.io.InputStream}.
     *
     * @return a stream provided by the SerialPort.
     */
    protected abstract Closeable getEntityStream();
}
