package org.axmol.app;

import android.view.KeyEvent;

import java.util.HashMap;
import java.util.Map;
public class KeyMappings
{
    public static final Map<Integer, Integer> ANDROID_TO_AXMOL_MAPPING = new HashMap<>();
    static {
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_A, 1004);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_B, 1005);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_X, 1007);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_Y, 1008);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_DPAD_UP, 1010);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_DPAD_DOWN, 1011);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_DPAD_LEFT, 1012);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_DPAD_RIGHT, 1013);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_R1, 1016);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_L1, 1015);
        ANDROID_TO_AXMOL_MAPPING.put(KeyEvent.KEYCODE_BUTTON_START, 1015);
    }
}