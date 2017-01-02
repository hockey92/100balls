package com.android.game.menu;

import com.android.game.utils.Vec2;

public class ScreenElementFactory {
    public static Button createButton(String id, float w, float h, Vec2 center) {
        return new Button(id, w, h, center);
    }
}
