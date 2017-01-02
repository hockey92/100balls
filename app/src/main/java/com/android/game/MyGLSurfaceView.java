package com.android.game;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import com.android.game.menu.ScreenElementEvent;
import com.android.game.menu.ScreenElementEventType;
import com.android.game.menu.ScreenManager;
import com.android.game.utils.Vec2;

public class MyGLSurfaceView extends GLSurfaceView {

    public MyGLSurfaceView(Context context) {
        super(context);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        ScreenElementEventType eventType = ScreenElementEventType.convertEvent(e.getAction());
        if (eventType != null) {
            int pointerIndex = e.getActionIndex();
            Vec2 pos = ScreenService.convertToGameCoordinates(e.getX(pointerIndex), e.getY(pointerIndex));
            ScreenManager.getInstance().handleEvent(new ScreenElementEvent(eventType, pos));
        }
        return true;
    }
}
