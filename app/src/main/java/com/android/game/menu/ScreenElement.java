package com.android.game.menu;

import com.android.game.utils.Vec2;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ScreenElement {
    private List<ScreenElement> screenElements;
    private ScreenElement parent;
    private final String id;
    private static Map<String, ScreenElement> screenElementsMap = new ConcurrentHashMap<>();
    private boolean hidden = false;

    public ScreenElement(String id) {
        this.id = id;
        screenElementsMap.put(id, this);
    }

    public static ScreenElement getScreenElementById(String id) {
        return screenElementsMap.get(id);
    }

    public void add(ScreenElement screenElement) {
        if (screenElements == null) {
            screenElements = new ArrayList<>();
        }
        screenElement.parent = this;
        screenElements.add(screenElement);
    }

    protected boolean containsPoint(Vec2 point) {
        return true;
    }

    public boolean handleEvent(ScreenElementEvent event) {
        if (containsPoint(event.point)) {
            if (innerHandleEvent(event)) {
                return true;
            }
            if (screenElements != null) {
                for (ScreenElement screenElement : screenElements) {
                    if (screenElement.handleEvent(event)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    protected boolean innerHandleEvent(ScreenElementEvent event) {
        return false;
    }

    protected void innerDraw() {

    }

    public void draw() {
        if (hidden) {
            return;
        }

        innerDraw();

        if (screenElements != null) {
            for (ScreenElement screenElement : screenElements) {
                screenElement.draw();
            }
        }
    }

    public String getId() {
        return id;
    }


    public List<ScreenElement> getScreenElements() {
        return screenElements;
    }

    public ScreenElement getParent() {
        return parent;
    }

    public boolean isHidden() {
        return hidden;
    }

    public ScreenElement setHidden(boolean hidden) {
        this.hidden = hidden;
        return this;
    }
}
