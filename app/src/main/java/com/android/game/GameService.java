package com.android.game;

public class GameService {
    static {
        System.loadLibrary("onehundredballs");
    }

    private static GameState gameState = GameState.PROCESSING;//GameState.STOPPED;

    private static long prev = System.currentTimeMillis();

    public static GameState getState() {
        return gameState;
    }

    public static void setState(GameState gameState) {
        GameService.gameState = gameState;
    }

    public static native void draw(float time);

    public static void reset() {
        gameState = GameState.STOPPED;
        resetNative();
        closeNative();
    }

    public static void nextFrame(float dt) {
        if (gameState == GameState.PROCESSING) {

            long newTime = System.currentTimeMillis();
            System.out.println("nextFrameTime " + (newTime - prev));
            prev = newTime;

            nextFrameNative(dt);
        }
    }

    private static native void resetNative();

    private static native void nextFrameNative(float dt);

    public static void open() {
        if (gameState == GameState.PROCESSING) {
            openNative();
        }
    }

    public static void close() {
        if (gameState == GameState.PROCESSING) {
            closeNative();
        }
    }

    private static native void openNative();

    private static native void closeNative();

    public enum GameState {
        PROCESSING, STOPPED, PAUSED
    }
}
