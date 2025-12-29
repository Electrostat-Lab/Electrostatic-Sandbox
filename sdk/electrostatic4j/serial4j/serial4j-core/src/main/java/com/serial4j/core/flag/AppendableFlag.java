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

package com.serial4j.core.flag;

import java.lang.reflect.InvocationTargetException;
import java.util.concurrent.ConcurrentHashMap;

/**
 * The base class for appendable native flags.
 *
 * @author pavl_g
 */
public class AppendableFlag implements FlagConst {

    /**
     * The value of this flag.
     */
    protected int value;

    /**
     * The description associated with this flag.
     */
    protected String description;

    /**
     * The appended flag constants.
     */
    protected final ConcurrentHashMap<String, String> descriptions = new ConcurrentHashMap<>();

    /**
     * Wraps a POSIX IO flag using an integer value.
     *
     * @param value       the value of the flag.
     * @param description the description of the flag.
     */
    public AppendableFlag(final int value, final String description) {
        this.value = value;
        this.description = description;
    }

    /**
     * Builds a concrete instance from a bootstrap class.
     *
     * @param clazz the target class, must be an appendable flag
     * @return an abstract reference to the created instance
     */
    public static AppendableFlag build(Class<? extends AppendableFlag> clazz) {
        try {
            return clazz.getDeclaredConstructor(int.class, String.class).newInstance(0, "");
        } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Appends a new flag constant to this flag.
     *
     * @param flag a flag constant to append
     * @return this flag object with the new appended value.
     */
    public AppendableFlag append(final FlagConst flag) {
        /* append new values */
        this.value |= flag.getValue();
        if (flag.getDescription() != null && descriptions.get(flag.getDescription()) == null) {
            descriptions.put(flag.getDescription(), flag.getDescription());
        }
        return this;
    }

    /**
     * Appends some new flag constants to this flag.
     *
     * @param flags an array args of the new flags to append.
     * @return this flag object with the new appended values.
     */
    public AppendableFlag append(final FlagConst... flags) {
        for (FlagConst flag : flags) {
            append(flag);
        }
        return this;
    }

    /**
     * Disables the flags specified by this parameter.
     *
     * @param flag the flag to disable
     * @return this instance for chained calls
     */
    public AppendableFlag disable(FlagConst flag) {
        this.value &= ~flag.getValue();
        if (flag.getDescription() != null) {
            descriptions.remove(flag.getDescription());
        }
        return this;
    }

    /**
     * Disables the flags specified by the varargs.
     *
     * @param flags the flags to disable
     * @return this instance for chained calls
     */
    public AppendableFlag disable(FlagConst... flags) {
        for (FlagConst flag : flags) {
            disable(flag);
        }
        return this;
    }

    /**
     * Test whether a flag constant exists in this flag.
     *
     * @param flag the flag constant to test against
     * @return true if the flag exists, or false otherwise
     */
    public boolean hasFlag(FlagConst flag) {
        return (value & flag.getValue()) == flag.getValue();
    }

    /**
     * Adjusts the value of the specified termios flag.
     *
     * @param value the value of the terminal flag.
     */
    public void setValue(final int value) {
        this.value = value;
    }

    @Override
    public int getValue() {
        return value;
    }

    @Override
    public String getDescription() {
        final String[] description = new String[1];
        final int[] tracker = new int[1];
        description[0] = "";

        descriptions.forEach((key, description1) -> {
            ++tracker[0];

            description[0] += description1;
            if (tracker[0] < descriptions.values().size()) {
                description[0] += " - ";
            }
        });
        return description[0];
    }

    @Override
    public String toString() {
        return "AppendableFlag{" +
                "value=" + getValue() +
                ", description='" + getDescription() + '\'' +
                '}';
    }
}
