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

package com.serial4j.core.errno;

import com.serial4j.core.serial.throwable.NotInterpretableErrnoError;
import com.serial4j.core.serial.throwable.SerialThrowable;

/**
 * Reflects C native "errno" into real java exceptions.
 * 
 * @author pavl_g.
 */
public final class ErrnoToException {
    
    private ErrnoToException() {
    }

    /**
     * Throws a Java exception from a native errno.
     * 
     * @param errno the native error code to which the exception will be thrown against.
     * @see SerialThrowable
     */
    public static void throwFromErrno(final int errno) {
        /* linearly matches the native errno with the pre-defined exceptions */
        for (Errno errnoObj : Errno.class.getEnumConstants()) {
            SerialThrowable throwable;
            if (errnoObj.getValue() != errno) {
                continue;
            }
            if ((throwable = errnoObj.getAssociatedThrowable()) == null) {
                return;
            }
            throw throwable;
        }
        throw new NotInterpretableErrnoError(errno);
    }
}