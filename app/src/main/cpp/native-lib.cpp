#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_carNameFromJNI(
        JNIEnv* env,
        jobject obj) {
    std::string hello = "Hello from C++";
    printf("this is %s",hello.c_str());
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_TestJNIBean_showCardFromJNI(JNIEnv *env, jobject instance) {
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
JNIEXPORT jlong JNICALL
Java_com_example_androidndk_TestJNIBean_testNewJavaDate(JNIEnv *env, jobject instance) {
    jclass  class_date = env->FindClass("java/util/Date");//注意这里路径要换成/,不然会报illegal class name
    jmethodID  a_method = env->GetMethodID(class_date,"<init>","()V");
    jobject  a_date_obj = env->NewObject(class_date,a_method);
    jmethodID  date_get_time = env->GetMethodID(class_date,"getTime","()J");
    jlong get_time = env->CallLongMethod(a_date_obj,date_get_time);
    return get_time;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidndk_TestJNIBean_testNewStaticRandomParam(JNIEnv *env, jclass type,
                                                                 jint random) {
    jmethodID jmethodID1 = env -> GetMethodID(type,"getRandom","(I)I");
    jint  result = env -> CallIntMethod(type,jmethodID1,100);
    return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidndk_TestJNIBean_testNewRandomParam(JNIEnv *env, jobject instance, jint random) {
    jclass  class_random = env->FindClass("java/util/Random");//注意这里路径要换成/,不然会报illegal class name
    jmethodID  a_method = env->GetMethodID(class_random,"<init>","()V");
    jobject  a_random_obj = env->NewObject(class_random,a_method);
    jmethodID a_next_int_method = env->GetMethodID(class_random,"nextInt","()I");
    jint  random_value = env->CallIntMethod(a_random_obj,a_next_int_method,random);
    return random_value;
}

/*
 * 修改属性
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_TestJNIBean_testChangeField(JNIEnv *env, jobject instance,
                                                        jint modelNumber) {
    jclass  a_class = env->GetObjectClass(instance);                // 获取当前对象的类
    jfieldID  a_field = env->GetFieldID(a_class,"modelNumber","I"); // 提取类中的属性
    modelNumber ++;                                                 // 修改属性值
    env->SetIntField(instance,a_field,modelNumber);                 // 重新给属性赋值
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallFatherMethod(JNIEnv *env, jobject instance) {
    jclass clazz = env -> GetObjectClass(instance);
    jfieldID  father_field = env -> GetFieldID(clazz,"father","Lcom/example/androidndk/Father;");
    jobject  mFather = env -> GetObjectField(instance,father_field);
    jclass  clazz_father = env -> FindClass("com/example/androidndk/Father");
    jmethodID  use_call_non_virtual = env -> GetMethodID(clazz_father,"toString","()Ljava/lang/String;");
//    jstring  result = (jstring) env->CallObjectMethod(mFather,use_call_non_virtual);
    jstring  result = (jstring) env->CallNonvirtualObjectMethod(mFather,clazz_father,use_call_non_virtual);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallChildMethod(JNIEnv *env, jobject instance) {
    jclass clazz = env -> GetObjectClass(instance);
    jfieldID  father_field = env -> GetFieldID(clazz,"father","Lcom/example/androidndk/Father;");
    jobject  mFather = env -> GetObjectField(instance,father_field);
    jclass  clazz_father = env -> FindClass("com/example/androidndk/Father");
    jmethodID  use_call_non_virtual = env -> GetMethodID(clazz_father,"toString","()Ljava/lang/String;");
    jstring  result = (jstring) env->CallObjectMethod(mFather,use_call_non_virtual);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallMethod(JNIEnv *env, jobject instance) {
    jclass  a_class = env->GetObjectClass(instance);
    jmethodID  a_method = env->GetMethodID(a_class,"describe","()Ljava/lang/String;");
    jobject jobj = env->AllocObject(a_class);
    jstring pring= (jstring)(env)->CallObjectMethod(jobj,a_method);

    char *print=(char*)(env)->GetStringUTFChars(pring,0);
    return env->NewStringUTF(print);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testStaticCallMethod(JNIEnv *env, jclass type) {

    jmethodID  a_method = env->GetMethodID(type,"describe","()Ljava/lang/String;");
    jobject jobj = env->AllocObject(type);
    jstring pring= (jstring)(env)->CallObjectMethod(jobj,a_method);

    char *print=(char*)(env)->GetStringUTFChars(pring,0);
    return env->NewStringUTF(print);

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallMethodParamList2(JNIEnv *env, jobject instance, jint num,
                                                 jstring str_, jint num2) {
    //获取java传递的参数
    const char *strCont = env->GetStringUTFChars(str_, 0);
    //通过反射获取java类
    jclass ccallj = env->FindClass("com/example/androidndk/TestJNIBean");
    //实例化该类
    jobject jobj = env->AllocObject(ccallj);
    //得到方法id
    //参数列表：反射类，方法名称，方法签名;
    //I:int类类型签名，Ljava/lang/String;是String的签名
    jmethodID methodId = env->GetMethodID(ccallj, "paramListMethod2",
                                          "(ILjava/lang/String;I)Ljava/lang/String;");
    //调用方法
    jstring result = (jstring) env-> CallObjectMethod(jobj, methodId, num,env->NewStringUTF(strCont), num2);
    env->ReleaseStringUTFChars(str_, strCont);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallMethodParamList(JNIEnv *env, jobject instance) {
    jvalue* args = new jvalue[3];
    args[0].i = 18;
    args[1].d = 180.8;
    args[2].c = L'a'; // 这里因为Java中的字符是Unicode双字节的，而C++中的类型参数是单字节的，所以要变成宽字符，即在前面添加一个L。
    jclass  test_Jni_bean_clazz = env -> GetObjectClass(instance);
    jobject jobj = env->AllocObject(test_Jni_bean_clazz);   // 实例化该类
    jmethodID  paramListMethod_id = env -> GetMethodID(test_Jni_bean_clazz,"paramListMethod","(IDC)Ljava/lang/String;");
    jstring result = (jstring)env -> CallObjectMethod(jobj,paramListMethod_id,args);
//    jstring result = (jstring)env -> CallObjectMethod(jobj,paramListMethod_id,18,180.8,L'a');
    delete[] args;
    return result;
}