package com.android.game;

import android.content.res.AssetManager;

public class ServiceManager {

    static {
        System.loadLibrary("onehundredballs");
    }

    public static native void init(AssetManager assetManager);

}
