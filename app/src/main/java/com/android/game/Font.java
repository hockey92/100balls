package com.android.game;

public class Font {

    public static native void render(String text, float x, float y);

    static {
        System.loadLibrary("onehundredballs");
    }
}
