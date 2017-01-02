package com.android.game.menu;

import com.android.game.GameService;
import com.android.game.utils.Vec2;

public class MainMenu extends ScreenElement {
    public MainMenu() {
        super(MainMenu.class.getName());
        add(new Button("continueButton", 1.8f, 0.2f, new Vec2(0.f, 0.3f)) {
            @Override
            public void innerDraw() {
                if (GameService.getState() != GameService.GameState.STOPPED) {
                    super.innerDraw();
                }
            }
        }.setButtonEventHandler(new Button.ButtonEventHandler() {
            @Override
            public void handle(ScreenElementEvent event) {
                ScreenManager.getInstance().setCurrentScreenId(GameScreen.class.getName());
                GameService.setState(GameService.GameState.PROCESSING);
            }
        }).setLabel("CONTINUE"));

        add(new Button("startButton", 1.8f, 0.2f, new Vec2(0.f, 0.f))
                .setLabel("NEW GAME")
                .setButtonEventHandler(new Button.ButtonEventHandler() {
                    @Override
                    public void handle(ScreenElementEvent event) {
                        ScreenManager.getInstance().setCurrentScreenId(GameScreen.class.getName());
                        GameService.reset();
                        GameService.setState(GameService.GameState.PROCESSING);
                    }
                }));
        add(new Button("exitButton", 1.8f, 0.2f, new Vec2(0.f, -0.3f))
                .setLabel("EXIT"));
    }
}
