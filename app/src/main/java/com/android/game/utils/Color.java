package com.android.game.utils;

/**
 * Created by qwerty on 03.12.16.
 */

public class Color {
    public final float r;
    public final float g;
    public final float b;
    public final float a;

    public static final Color WHITE = new Color(1.f, 1.f, 1.f, 1.f);
    public static final Color RED = new Color(1.f, 0.f, 0.f, 1.f);
    public static final Color GREEN = new Color(0.f, 1.f, 0.f, 1.f);
    public static final Color BLUE = new Color(0.f, 0.f, 1.f, 1.f);

    public Color(float r, float g, float b, float a) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }
}
