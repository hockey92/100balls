package com.android.game.menu;

public class ScreenManager extends ScreenElement {

    private String currentScreenId;
    private static ScreenManager instance;

    static {
        instance = new ScreenManager();
        instance.add(new MainMenu());
        instance.add(new GameScreen());

        instance.currentScreenId = MainMenu.class.getName();
    }

    public static ScreenManager getInstance() {
        return instance;
    }

    private ScreenManager() {
        super(ScreenManager.class.getName());
    }

    public void setCurrentScreenId(String id) {
        this.currentScreenId = id;
    }

    @Override
    public void draw() {
        getScreenElementById(currentScreenId).draw();
    }

    @Override
    public boolean handleEvent(ScreenElementEvent event) {
        return getScreenElementById(currentScreenId).handleEvent(event);
    }
}
