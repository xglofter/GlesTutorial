package com.richard.glestutorial;

import android.app.Activity;
import android.os.Bundle;

public class AppActivity extends Activity
{
    protected AppSurfaceView mView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mView = new AppSurfaceView(getApplication());
        setContentView(mView);
    }

	@Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
    }

	@Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
