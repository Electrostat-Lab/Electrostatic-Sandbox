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
package com.serial4j.example;

import electrostatic.snaploader.LoadingCriterion;
import com.serial4j.util.loader.NativeImageLoader;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * The entry point of the API modular test cases, it reflectively runs
 * the "main" method from a selected test case with the selected port, and
 * it's fully compatible with a headless CI/CD interface.
 *
 * <p>
 * To run a test case, use this format from your command-line:
 * └──╼ $./gradlew :serial4j-examples:run --args="com.serial4j.example.monitor.HelloSerialMonitor  /dev/ttyUSB0"
 * </p>
 *
 * <p>
 * The arguments are delimited by an empty white space.
 * </p>
 * 
 * @author pavl_g.
 */
public final class Launcher {

    static {
        /* always load with clean extract from the libs/bin folder */
        NativeImageLoader.setDefaultLoadingCriterion(LoadingCriterion.CLEAN_EXTRACTION);
        NativeImageLoader.setExtractionPathFromUserDir("libs", "bin");
    }

    public static void main(String[] args) throws ClassNotFoundException
            , NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        final Class<?> clazz = Class.forName(args[0]);
        final Method method = clazz.getMethod("main", String[].class);
        final String[] args0 = new String[] { args[1] };
        method.invoke(null, (Object) args0);
    }
}