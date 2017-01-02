package com.android.game.menu;

import com.android.game.GameService;
import com.android.game.ScreenService;
import com.android.game.TextureRenderer;
import com.android.game.utils.Vec2;

public class GameScreen extends ScreenElement {

    private final Button pauseButton;

    public GameScreen() {
        super(GameScreen.class.getName());

        pauseButton = new Button("pauseButton", 0.2f, 0.2f, new Vec2(0.f, 0.f)) {
            TextureRenderer renderer = new TextureRenderer("pause_button.tga", 0.2f, 0.2f);

            @Override
            public void innerDraw() {
                Vec2 center = getCenter();
                renderer.setPosition(center.x, center.y);
                renderer.render();
            }
        }.setButtonEventHandler(new Button.ButtonEventHandler() {
            @Override
            public void handle(ScreenElementEvent event) {
                GameService.setState(GameService.GameState.PAUSED);
                ScreenManager.getInstance().setCurrentScreenId(MainMenu.class.getName());
            }
        });

        setPauseButtonPosition(pauseButton);

        ScreenService.addSurfaceChangedHandler(new ScreenService.ISurfaceChangedHandler() {
            @Override
            public void handle(float width, float height) {
                setPauseButtonPosition(pauseButton);
            }
        });

        add(pauseButton);
    }

    private void setPauseButtonPosition(Button pauseButton) {
        Vec2 gameCoords = ScreenService.getGameCoords();
        pauseButton.setPosition(
                gameCoords.x - 0.05f - pauseButton.getW() / 2.f,
                gameCoords.y - 0.05f - pauseButton.getH() / 2.f
        );
    }

    @Override
    protected void innerDraw() {
        GameService.nextFrame();
        GameService.draw();
    }

    @Override
    protected boolean innerHandleEvent(ScreenElementEvent event) {
        if (pauseButton.handleEvent(event)) {
            return true;
        }
        if (event.type == ScreenElementEventType.DOWN) {
            GameService.open();
        } else if (event.type == ScreenElementEventType.UP) {
            GameService.close();
        }
        return true;
    }
}
