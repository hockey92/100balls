package com.android.game.menu;

import com.android.game.Font;
import com.android.game.utils.Color;
import com.android.game.utils.Vec2;


public class Button extends ScreenElement {
    private float h;
    private float w;
    private Vec2 center;
    //    private GLObject rectangle;
    private Color color = Color.WHITE;
    private String label;
    private ButtonRenderer buttonRenderer;
    private ButtonEventHandler buttonEventHandler;

    private boolean pushed = false;

    private Object data;
    private Class<?> dataClass;
    private String methodName;
    private String screenElementId;

    public Button(String id, float w, float h, Vec2 center) {
        super(id);
        this.w = w;
        this.h = h;
        this.center = center;
//        this.rectangle = GLObject.createRectangle(w, h);
    }

    public Button setButtonRenderer(ButtonRenderer buttonRenderer) {
        this.buttonRenderer = buttonRenderer;
        return this;
    }

    public Button setDataClass(Class<?> dataClass) {
        this.dataClass = dataClass;
        return this;
    }

    public Button setMethodName(String methodName) {
        this.methodName = methodName;
        return this;
    }

    public Button setScreenElementId(String screenElementId) {
        this.screenElementId = screenElementId;
        return this;
    }

    public Button setData(Object data) {
        this.data = data;
        return this;
    }

    @Override
    protected boolean innerHandleEvent(ScreenElementEvent event) {
        if (event.type == ScreenElementEventType.DOWN) {
            setColor(Color.GREEN);
            pushed = true;
        } else if (event.type == ScreenElementEventType.UP) {
            if (pushed) {

                if (buttonEventHandler != null) {
                    buttonEventHandler.handle(event);
                }

//                try {
//                    Method method = ScreenManager.class.getMethod(methodName, dataClass);
//                    method.invoke(getScreenElementById(screenElementId), data);
//                } catch (Exception e) {
//                    e.printStackTrace();
//                }

            }
            setColor(Color.WHITE);
            pushed = false;
        }
        return true;
    }

    public Button setButtonEventHandler(ButtonEventHandler buttonEventHandler) {
        this.buttonEventHandler = buttonEventHandler;
        return this;
    }

    @Override
    protected void innerDraw() {
//        ScreenService.resetMatrix();
//        ScreenService.transpose(center.x, center.y, 0);
//        if (color != null) {
//            ScreenService.setColor(color);
//        }
//        ScreenService.drawGLObject(rectangle);

        if (buttonRenderer != null) {
            buttonRenderer.render();
            return;
        }

        if (label != null) {
            Font.render(label, 0, center.y);
        }
    }

    @Override
    protected boolean containsPoint(Vec2 point) {

        return !(center.x - w / 2.f >= point.x || center.x + w / 2.f <= point.x
                || center.y - h / 2.f >= point.y || center.y + h / 2.f <= point.y);
    }

    public Button setColor(Color color) {
        this.color = color;
        return this;
    }

    public Button setLabel(String label) {
        this.label = label;
        return this;
    }

    public Button setPosition(float x, float y) {
        center = new Vec2(x, y);
        return this;
    }

    public Button setPosition(Vec2 center) {
        this.center = center;
        return this;
    }

    public Vec2 getCenter() {
        return center;
    }

    public interface ButtonRenderer {
        void render();
    }

    public float getW() {
        return w;
    }

    public float getH() {
        return h;
    }

    public interface ButtonEventHandler {
        void handle(ScreenElementEvent event);
    }

}
