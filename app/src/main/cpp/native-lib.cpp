#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_androidndk_CarJNI_carNameFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Hello from C++";
    printf("this is %s",hello.c_str());
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_CarJNI_showCardFromJNI(JNIEnv *env, jobject instance) {
    jclass carClass = env->GetObjectClass(instance);
    jmethodID  method_func = env->GetMethodID(carClass,"showDetailAboutCar","(III)V");
    env->CallVoidMethod(instance,method_func,5,5,500);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_CarJNI_test(JNIEnv *env, jobject instance) {
    jclass carClass = env->GetObjectClass(instance);
    jmethodID  method_func = env->GetMethodID(carClass,"function","(ILjava/util/Date;[I)I");
    env->CallIntMethod(instance,method_func,0,NULL,NULL);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_CarJNI_testChangeField(JNIEnv *env, jobject instance) {
    jclass  a_class = env->GetObjectClass(instance);
    jfieldID  a_field = env->GetFieldID(a_class,"modelNumber","I");
//    jint model_number = env->GetIntField(instance,a_field);
    env->SetIntField(instance,a_field,50);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_CarJNI_testNewJavaBean(JNIEnv *env, jobject instance) {
    jclass  class_date = env->FindClass("java/util/Date");
    jmethodID  a_method = env->GetMethodID(class_date,"<init>","()V");
    jobject  a_date_obj = env->NewObject(class_date,a_method);
    jmethodID  date_get_time = env->GetMethodID(class_date,"getTime","()J");
    jlong get_time = env->CallLongMethod(a_date_obj,date_get_time);
//    printf("%I64d",get_time);
    printf("%lld",get_time);
}