#ifndef GLUG_JNI_JALLOC_CONTEXT_HPP
#define GLUG_JNI_JALLOC_CONTEXT_HPP

#include <jni.h>
#include <stddef.h>

struct jalloc_context {
    JNIEnv *env;
    jobject jallocator;
    size_t alloc_size;
};

#endif // GLUG_JNI_JALLOC_CONTEXT_HPP
