package com.android.game;

public class GameService {
    static {
        System.loadLibrary("onehundredballs");
    }

    private static GameState gameState = GameState.STOPPED;

    public static GameState getState() {
        return gameState;
    }

    public static void setState(GameState gameState) {
        GameService.gameState = gameState;
    }

    public static native void draw();

    public static void reset() {
        gameState = GameState.STOPPED;
        resetNative();
        closeNative();
    }

    public static void nextFrame() {
        if (gameState == GameState.PROCESSING) {
            nextFrameNative();
        }
    }

    private static native void resetNative();

    private static native void nextFrameNative();

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
