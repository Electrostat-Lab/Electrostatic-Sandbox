package electrostatic4j.examples;

import electrostatic.snaploader.LoadingCriterion;
import electrostatic4j.NativeLibrary;
import electrostatic4j.util.loader.NativeImageLoader;

public class Launcher {
    
    static {
        /* always load with clean extract from the libs/bin folder */
        NativeImageLoader.setDefaultLoadingCriterion(LoadingCriterion.CLEAN_EXTRACTION);
        NativeImageLoader.setExtractionPathFromUserDir("libs", "bin");
    }
    
    public static void main(String[] args) {
        NativeLibrary.open("/dev/ttyS0");
    }
}