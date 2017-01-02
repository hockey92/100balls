package com.android.game;

import com.android.game.utils.Vec2;

import java.util.ArrayList;
import java.util.List;

public class ScreenService {

    private static Vec2 realSize = null;
    private static Vec2 gameCoords = null;
    private static float scale = 1.0f;

    private static List<ISurfaceChangedHandler> surfaceChangedHandlers = new ArrayList<>();

    public static Vec2 getRealSize() {
        return realSize;
    }

    public static Vec2 getGameCoords() {
        return gameCoords;
    }

    public static native void surfaceCreated();

    public static void addSurfaceChangedHandler(ISurfaceChangedHandler surfaceChangedHandler) {
        surfaceChangedHandlers.add(surfaceChangedHandler);
    }

    public static void surfaceChanged(int width, int height) {
        surfaceChangedNative(width, height);
        realSize = new Vec2(width, height);
        gameCoords = new Vec2(1.f, (float) height / (float) width);
        for (ISurfaceChangedHandler surfaceChangedHandler : surfaceChangedHandlers) {
            surfaceChangedHandler.handle(width, height);
        }
    }

    public static Vec2 convertToGameCoordinates(Vec2 v) {
        return convertToGameCoordinates(v.x, v.y);
    }

    public static Vec2 convertToGameCoordinates(float x, float y) {

        float rel = realSize.x / realSize.y;

        return new Vec2(
                -1.f * scale + x / realSize.x * 2.f * scale,
                1.f * scale / rel - y / realSize.y * 2.f * scale / rel
        );
    }

    static {
        System.loadLibrary("onehundredballs");
    }

//    private static native void add(int id);

    private static native void surfaceChangedNative(int width, int height);

    public static native void beforeDraw();

    public interface ISurfaceChangedHandler {
        void handle(float width, float height);
    }
}
