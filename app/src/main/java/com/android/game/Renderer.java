package com.android.game;

import com.android.game.utils.Vec2;

public class Renderer {

    private int id;

    protected Renderer(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void render() {
        render(id);
    }

    public void setPosition(float x, float y) {
        setPosition(id, x, y);
    }

    public void setPosition(Vec2 center) {
        setPosition(id, center.x, center.y);
    }

    static {
        System.loadLibrary("onehundredballs");
    }

    private static native void render(int id);

    private static native void setPosition(int id, float x, float y);

    protected static native int createTextureRenderer(String fileName, float w, float h);
}
