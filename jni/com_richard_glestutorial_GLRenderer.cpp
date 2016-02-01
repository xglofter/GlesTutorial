#include "com_richard_glestutorial_GLRenderer.h"
#include "../core/AppMacros.h"
#include "../core/Director.h"

JNIEXPORT void JNICALL Java_com_richard_glestutorial_GLRenderer_nativeInit
  (JNIEnv *env, jclass thiz)
{
	Director::getInstance();
}


JNIEXPORT void JNICALL Java_com_richard_glestutorial_GLRenderer_nativeOnReSize
  (JNIEnv *env, jclass thiz, jint width, jint height)
{

	Director::getInstance()->setFrameSize(width, height);
}


JNIEXPORT void JNICALL Java_com_richard_glestutorial_GLRenderer_nativeUpdate
  (JNIEnv *env, jclass thiz)
{
	Director::getInstance()->mainLoop();
}


JNIEXPORT void JNICALL Java_com_richard_glestutorial_GLRenderer_nativeOnPause
  (JNIEnv *env, jclass thiz)
{
	Director::getInstance()->onEnterBackground();
}


JNIEXPORT void JNICALL Java_com_richard_glestutorial_GLRenderer_nativeOnResume
  (JNIEnv *env, jclass thiz)
{
	Director::getInstance()->onEnterForeground();
}
