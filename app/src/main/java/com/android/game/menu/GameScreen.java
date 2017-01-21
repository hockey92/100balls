package com.android.game.menu;

import com.android.game.GameService;
import com.android.game.MainActivity;
import com.android.game.MyGLSurfaceView;
import com.android.game.ScreenService;
import com.android.game.TextureRenderer;
import com.android.game.utils.Vec2;

public class GameScreen extends ScreenElement {

    private final Button pauseButton;
    private Thread thread;
    private static long prevTime;

    private static float tm = -1;

    private static float acc = 0;

//    private long startTime;

    public GameScreen() {
        super(GameScreen.class.getName());

        prevTime = System.nanoTime();

//        startTime = System.nanoTime();

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

        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                int h = 0;
                GameScreen.prevTime = System.nanoTime();
                long prevTime = GameScreen.prevTime;
                float acc = 0.f;
                float dt = 0.016f;
                while (true) {

                    long currentTime = System.nanoTime();
                    float frameTime = ((float) (currentTime - prevTime) / (float) 1000000000);
                    acc += frameTime;
                    if (acc >= dt) {
                        while (acc >= dt) {
                            GameService.nextFrame(dt);
                            acc -= dt;
                        }
                        h++;
                        while (true) {
                            if (MainActivity.stop) {
                                MainActivity.stop = false;
                                MainActivity.glSurfaceView.requestRender();
                                break;
                            }
                        }
//                        MainActivity.glSurfaceView.requestRender();
                        System.out.println("time " + (float) (System.nanoTime() - prevTime) / (float) 1000000000);
                    }
                    prevTime = currentTime;
//                    try {
//                        Thread.sleep(5);
//                    } catch (InterruptedException e) {
//                        e.printStackTrace();
//                    }
                }
            }
        });
        thread.setDaemon(true);
//        thread.start();
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
//        System.out.println("gl loop time " + (System.currentTimeMillis() - prevTime));
//        prevTime = System.currentTimeMillis();

//        long startPhysicsTime = System.currentTimeMillis();
//        GameService.nextFrame(0.016f);
//        long physicsTime = System.currentTimeMillis() - startPhysicsTime;

        float dt = 0.016f;
        if (tm < 0) {
            tm = (float) System.nanoTime()  / (float) 1000000000;
        }

        float currentTime = (float) System.nanoTime() / (float) 1000000000;
        acc += currentTime - tm;

        while (acc >= dt) {
            acc -= dt;
            GameService.nextFrame(dt);
        }

//        long startDrawTime = System.currentTimeMillis();
        float delta = (float) (System.nanoTime() - prevTime) / (float) 1000000000;
        GameService.draw(delta);
//        long drawTime = System.currentTimeMillis() - startDrawTime;

        System.out.println("dela  " + delta);

        tm = (float) System.nanoTime()  / (float) 1000000000;
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
