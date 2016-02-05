ndk-build  &&
ant debug  &&
adb install -r bin/GlesTutorial-debug.apk  &&
adb shell am start com.richard.glestutorial/.AppActivity 

