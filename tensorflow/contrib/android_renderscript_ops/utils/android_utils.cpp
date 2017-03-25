#include "android_utils.h"

#define  LOG_TAG_MY    "TF_ANDROID_LOG"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG_MY,__VA_ARGS__)

void android_log_print(const char* a)
{
    LOGI("%s\n", a);
}
