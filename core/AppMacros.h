#ifndef _APPMACROS_H__
#define _APPMACROS_H__

#include <android/log.h>

#define  LOG_TAG    "GLES-Tutorial"

#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


#endif
