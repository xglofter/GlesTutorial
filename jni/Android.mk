
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := gltutorial

LOCAL_LDLIBS    := -llog -lGLESv2
LOCAL_CFLAGS    := -Werror
LOCAL_CPPFLAGS  := -std=c++11

LOCAL_SRC_FILES := \
com_richard_glestutorial_GLRenderer.cpp \
../core/Director.cpp
                
LOCAL_C_INCLUDES := \
$(LOCAL_PATH)

include $(BUILD_SHARED_LIBRARY)


