/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022-2024, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
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

package electrostatic4j.util.loader;

import com.avrsandbox.snaploader.LibraryInfo;
import com.avrsandbox.snaploader.LoadingCriterion;
import com.avrsandbox.snaploader.NativeBinaryLoader;
import com.avrsandbox.snaploader.platform.NativeVariant;
import com.avrsandbox.snaploader.platform.PropertiesProvider;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Utilizes jSnapLoader to extract and load native images.
 *
 * @author pavl_g
 */
public class NativeImageLoader {

    private static String jarPath = null;
    private static String extractionPath = null;
    private static LoadingCriterion defaultLoadingCriterion =
            LoadingCriterion.INCREMENTAL_LOADING;

    private NativeImageLoader() {
    }

    /**
     * Incrementally extracts and loads the platform-specific native image.
     */
    public static void loadLibrary() {
        /* sanity check the existence of the extraction path */
        final File dir = new File(getExtractionPath());

        if (!dir.exists()) {
            if (dir.mkdir()) {
                Logger.getLogger(NativeBinaryLoader.class.getName())
                        .log(Level.INFO, "Created extraction directory!");
            }
        }

        final LibraryInfo libraryInfo =
                new LibraryInfo(getJarPath(), null, getLibraryBaseName(), getExtractionPath());

        final NativeBinaryLoader loader = new NativeBinaryLoader(libraryInfo)
                .initPlatformLibrary();
        loader.setLoggingEnabled(true);
        loader.setRetryWithCleanExtraction(true);
        try {
            loader.loadLibrary(defaultLoadingCriterion);
        } catch (IOException e) {
            Logger.getLogger(NativeBinaryLoader.class.getName())
                    .log(Level.SEVERE, "Loading the native image has failed!", e);
        }
    }

    public static void setDefaultLoadingCriterion(LoadingCriterion defaultLoadingCriterion) {
        NativeImageLoader.defaultLoadingCriterion = defaultLoadingCriterion;
    }

    /**
     * Sets the jar path from the current user directory.
     *                                                                                                                                                                                                                                                                                                                                                                                                              
     * @param parts the path parts in string format without file separators
     */
    public static void setJarPathFromUserDir(String... parts) {
        NativeImageLoader.jarPath = PropertiesProvider.USER_DIR.getSystemProperty();
        for (String part : parts) {
            NativeImageLoader.jarPath += PropertiesProvider.FILE_SEPARATOR.getSystemProperty() + part;
        }
    }

    /**
     * Sets the extraction path from the current user directory.
     *
     * @param path the path parts
     */
    public static void setExtractionPathFromUserDir(String... path) {
        NativeImageLoader.extractionPath = PropertiesProvider.USER_DIR.getSystemProperty();
        for (String part : path) {
            NativeImageLoader.extractionPath += PropertiesProvider.FILE_SEPARATOR.getSystemProperty() + part;
        }
    }

    /**
     * Retrieves the native library extraction path or
     * the default {@link NativeImageLoader#getDefaultExtractionPath()}
     * if the user extraction path is "null".
     *
     * @return the native library extraction path in an absolute format
     */
    public static String getExtractionPath() {
        if (extractionPath != null) {
            return extractionPath;
        }
        return getDefaultExtractionPath();
    }

    /**
     * Sets the extraction path, that is the directory for extracting the native
     * library.
     * <p>
     * Default path is {@link NativeImageLoader#getDefaultExtractionPath()}.
     * </p>
     *
     * @param parts the path parts in string format without file separators
     */
    public static void setExtractionPath(String... parts) {
        NativeImageLoader.extractionPath = "";
        for (String part : parts) {
            NativeImageLoader.extractionPath += PropertiesProvider.FILE_SEPARATOR.getSystemProperty() + part;
        }
    }

    /**
     * Retrieves the jar path to locate the jar file from which
     * the native library will be extracted or the default {@link NativeImageLoader#getDefaultJarPath()}
     * if the user jar path is "null".
     *
     * @return the jar file absolute path
     */
    public static String getJarPath() {
        if (jarPath != null) {
            return jarPath;
        }
        return getDefaultJarPath();
    }

    /**
     * Sets the jar absolute path, that is the source to extract the
     * native library from.
     * <p>
     * Default path to use the classpath to
     * locate the native library to extract.
     * </p>
     *
     * @param parts the path parts starting from the root directory without file separators
     */
    public static void setJarPath(String... parts) {
        NativeImageLoader.jarPath = "";
        for (String part : parts) {
            NativeImageLoader.jarPath += PropertiesProvider.FILE_SEPARATOR.getSystemProperty() + part;
        }
    }

    /**
     * Assigns and retrieves the default extraction path directory to
     * the extractionPath field, as "current-user-dir/libs".
     *
     * @return the default extraction path directory in absolute format
     */
    public static String getDefaultExtractionPath() {
        setExtractionPathFromUserDir("libs");
        return extractionPath;
    }

    /**
     * Assigns and retrieves the default absolute jar path,
     * as "current-user-dir/libs", to locate the jar file to extract the native library from.
     *
     * @return the default jar path in absolute format
     */
    public static String getDefaultJarPath() {
        setJarPathFromUserDir("libs");
        return jarPath + PropertiesProvider.FILE_SEPARATOR.getSystemProperty()
                + getJarFile();
    }

    /**
     * Provides a platform independent constant value for the loader jar file.
     *
     * @return the name of the jar file containing
     * the native dynamic libraries to extract and load
     */
    public static String getJarFile() {
        return "electrostatic4j-native-" + NativeVariant.NAME.getProperty().toLowerCase() + ".jar";
    }

    /**
     * Provides a constant value for the library basename.
     *
     * @return the library basename in string format
     */
    public static String getLibraryBaseName() {
        return "electrostatic4j";
    }
}
