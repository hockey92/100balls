package com.android.game;

public class TextureRenderer extends Renderer {
    public TextureRenderer(String fileName, float w, float h) {
        super(createTextureRenderer(fileName, w, h));
    }
}
