package com.richard.glestutorial;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class GLRenderer implements Renderer {

	static {
        System.loadLibrary("gltutorial");
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	GLRenderer.nativeInit();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
    	GLRenderer.nativeOnReSize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
    	GLRenderer.nativeUpdate();
    }

    public void handleOnPause() {
    	GLRenderer.nativeOnPause();
    }

    public void handleOnResume() {
    	Log.v("GLES Tutorial", "nativeOnResume");
    	GLRenderer.nativeOnResume();
    }
	
    // ------------------------------------------------------------
    // Native Method

    private static native void nativeInit();

    private static native void nativeOnReSize(int width, int height);

    private static native void nativeUpdate();

    private static native void nativeOnPause();

    private static native void nativeOnResume();
}
