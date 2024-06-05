package electrostatic4j.examples;

import com.avrsandbox.snaploader.LoadingCriterion;
import electrostatic4j.util.loader.NativeImageLoader;
import electrostatic4j.NativeLibrary;

public class Launcher {
    
    static {
        /* always load with clean extract from the libs/bin folder */
        NativeImageLoader.setDefaultLoadingCriterion(LoadingCriterion.CLEAN_EXTRACTION);
        NativeImageLoader.setExtractionPathFromUserDir("libs", "bin");
    }
    
    public static void main(String args[]) {
        NativeLibrary.open("/dev/ttyS0");
    }
}