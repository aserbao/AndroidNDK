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
JNIEXPORT jlong JNICALL
Java_com_example_androidndk_CarJNI_testNewJavaDate(JNIEnv *env, jobject instance) {
    jclass  class_date = env->FindClass("java/util/Date");
    jmethodID  a_method = env->GetMethodID(class_date,"<init>","()V");
    jobject  a_date_obj = env->NewObject(class_date,a_method);
    jmethodID  date_get_time = env->GetMethodID(class_date,"getTime","()J");
    jlong get_time = env->CallLongMethod(a_date_obj,date_get_time);
//    printf("%I64d",get_time);
    return get_time;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_CarJNI_testCallMethod(JNIEnv *env, jobject instance) {
    jclass  a_class = env->GetObjectClass(instance);
    jmethodID  a_method = env->GetMethodID(a_class,"describe","()Ljava/lang/String");

    jstring pring= (jstring)(env)->CallObjectMethod(a_class,a_method);

    char *print=(char*)(env)->GetStringUTFChars(pring,0);
    return env->NewStringUTF(print);
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidndk_CarJNI_testNewRandom(JNIEnv *env, jobject instance) {
    jclass  class_random = env->FindClass("java/util/Random");//注意这里路径要换成/,不然会报illegal class name
    jmethodID  a_method = env->GetMethodID(class_random,"<init>","()V");
    jobject  a_random_obj = env->NewObject(class_random,a_method);
    jmethodID a_next_int_method = env->GetMethodID(class_random,"nextInt","()I");
    jint  random_value = env->CallIntMethod(a_random_obj,a_next_int_method,10,NULL,NULL);
    return random_value;
}



extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_CarJNI_testCallMethodParamList(JNIEnv *env, jobject instance, jint num,
                                                 jstring str_, jint num2) {
    //获取java传递的参数
    const char *strCont = env->GetStringUTFChars(str_, 0);
    //通过反射获取java类
    jclass ccallj = env->FindClass("com/example/androidndk/CarJNI");
    //实例化该类
    jobject jobj = env->AllocObject(ccallj);
    //得到方法id
    //参数列表：反射类，方法名称，方法签名;
    //I:int类类型签名，Ljava/lang/String;是String的签名
    jmethodID methodId = env->GetMethodID(ccallj, "paramListMethod",
                                          "(ILjava/lang/String;I)Ljava/lang/String;");
    //调用方法
    jstring result = (jstring) env->CallObjectMethod(jobj, methodId, num,
                                                     env->NewStringUTF(strCont), num2);
    env->ReleaseStringUTFChars(str_, strCont);


    return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidndk_CarJNI_testNewRandomParam(JNIEnv *env, jobject instance, jint random) {
    jclass  class_random = env->FindClass("java/util/Random");//注意这里路径要换成/,不然会报illegal class name
    jmethodID  a_method = env->GetMethodID(class_random,"<init>","()V");
    jobject  a_random_obj = env->NewObject(class_random,a_method);
    jmethodID a_next_int_method = env->GetMethodID(class_random,"nextInt","()I");
    jint  random_value = env->CallIntMethod(a_random_obj,a_next_int_method,random);
    return random_value;

}

