/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The Arithmos Project.
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

package com.serial4j.example.exception;

import com.serial4j.core.errno.ErrnoToException;
import com.serial4j.core.serial.throwable.NotInterpretableErrnoError;
import com.serial4j.util.loader.NativeImageLoader;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Isolates and examines the interpreter pattern of the {@link ErrnoToException},
 * this example demonstrates the capability to detect non-defined error codes.
 *
 * @author pavl_g
 */
public final class TestNotInterpretableErrnoError {

    /*
     * Static initializer: Loads the native image when this object is created or referenced.
     */
    static {
        NativeImageLoader.loadSerial4jNatives();
    }

    public static void main(String[] args) {
        try {
            ErrnoToException.throwFromErrno(Byte.MAX_VALUE);
        } catch (NotInterpretableErrnoError error) {
            Logger.getLogger(TestNoSuchFileException.class.getName())
                    .log(Level.SEVERE, error.getMessage(), error);
        }
    }
}
