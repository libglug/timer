#include <jni.h>

static jint JNI_VERSION = JNI_VERSION_1_8;

jmethodID allocator_malloc_field, allocator_free_field;
jfieldID time_sec_field, time_nsec_field;

#ifdef GLUG_STATIC
jint JNI_OnLoad_glug_timer(JavaVM *vm, void *)
#else
jint JNICALL JNI_OnLoad(JavaVM *vm, void *)
#endif
{
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION) != JNI_OK)
    {
        return JNI_ERR;
    }

    jclass class_temp;

    // store Allocator fields
    class_temp = env->FindClass("org/glug/timer/Allocator");

    allocator_malloc_field = env->GetMethodID(class_temp, "malloc", "(I)Ljava/nio/ByteBuffer;");
    allocator_free_field = env->GetMethodID(class_temp, "free", "(Ljava/nio/ByteBuffer;)V");

    env->DeleteLocalRef(class_temp);

    // store Time fields
    class_temp = env->FindClass("org/glug/timer/Time");

    time_sec_field = env->GetFieldID(class_temp, "sec", "I");
    time_nsec_field = env->GetFieldID(class_temp, "nsec", "I");

    env->DeleteLocalRef(class_temp);

    return JNI_VERSION;
}

#ifdef GLUG_STATIC
void JNI_JNI_OnUnload_glug_timer(JavaVM *vm, void *)
#else
void JNICALL JNI_OnUnload(JavaVM *vm, void *)
#endif
{
    JNIEnv *env;
    vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION);
}
