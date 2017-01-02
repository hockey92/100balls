package com.android.game;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import com.android.game.menu.MainMenu;
import com.android.game.menu.ScreenManager;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity {

    GLSurfaceView glSurfaceView;

    Thread thread = null;

    @Override
    public void onBackPressed() {
        GameService.setState(GameService.GameState.PAUSED);
        ScreenManager.getInstance().setCurrentScreenId(MainMenu.class.getName());
    }

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        ServiceManager.init(getAssets());
        glSurfaceView = new MyGLSurfaceView(getApplication());
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                ScreenService.surfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                ScreenService.surfaceChanged(width, height);
//                if (thread != null) return;
//                thread = new Thread(new Runnable() {
//                    @Override
//                    public void run() {
//                        try {
//                            Thread.sleep(1000);
//                        } catch (InterruptedException e) {
//                            e.printStackTrace();
//                        }
//                        GameService.nextFrame();
//                        try {
//                            Thread.sleep(1000 / 60);
//                        } catch (InterruptedException e) {
//                            e.printStackTrace();
//                        }
//                    }
//                });
//                thread.setDaemon(true);
//                thread.start();
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                ScreenService.beforeDraw();
                ScreenManager.getInstance().draw();

            }
        });
        setContentView(glSurfaceView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
        GameService.setState(GameService.GameState.PAUSED);
        ScreenManager.getInstance().setCurrentScreenId(MainMenu.class.getName());
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
    }

    public String loadJSONFromAsset(String fileName) {
        String json;
        try {
            InputStream is = getAssets().open(fileName);
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            json = new String(buffer, "UTF-8");
        } catch (IOException ex) {
            ex.printStackTrace();
            return null;
        }
        return json;
    }
}
