package com.android.game.menu;

import com.android.game.utils.Vec2;

public class ScreenElementEvent {
    public final ScreenElementEventType type;
    public final Vec2 point;

    public ScreenElementEvent(ScreenElementEventType type, Vec2 point) {
        this.type = type;
        this.point = point;
    }
}
