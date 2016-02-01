package com.richard.glestutorial;

import android.content.Context;
import android.opengl.GLSurfaceView;

public class AppSurfaceView extends GLSurfaceView {

	protected GLRenderer mRender;

    public AppSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        
        mRender = new GLRenderer();
        setRenderer(mRender);
    }

    @Override
    public void onPause() {
        super.onPause();
        mRender.handleOnPause();
    }

    @Override
    public void onResume() {
        super.onResume();
        mRender.handleOnResume();
    }
}
