package com.android.game.menu;

import android.view.MotionEvent;

public enum ScreenElementEventType {
    DOWN, UP, MOVE;

    public static ScreenElementEventType convertEvent(int motionEvent) {
        switch (motionEvent) {
            case MotionEvent.ACTION_DOWN:
                return ScreenElementEventType.DOWN;
            case MotionEvent.ACTION_UP:
                return ScreenElementEventType.UP;
            case MotionEvent.ACTION_MOVE:
                return ScreenElementEventType.MOVE;
        }
        return null;
    }
}
