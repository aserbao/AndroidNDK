#include <jni.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <android/log.h>
#define TAG "learn JNI" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_TestJNIBean_testLogInJNI(JNIEnv *env, jclass type) {
    LOGE("my name is %s\n", "aserbao");//简约型
    __android_log_print(ANDROID_LOG_INFO, "android", "my name is %s\n", "aserbao"); //log i类型
}

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
Java_com_example_androidndk_TestJNIBean_testChangeField(JNIEnv *env, jobject instance) {
    jclass  a_class = env->GetObjectClass(instance);                // 获取当前对象的类
    jfieldID  a_field = env->GetFieldID(a_class,"modelNumber","I"); // 提取类中的属性
    env->SetIntField(instance,a_field,100);                         // 重新给属性赋值
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
    jstring  result = (jstring) env->CallNonvirtualObjectMethod(mFather,clazz_father,use_call_non_virtual);// 如果调用父类方法用CallNonvirtual***Method
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
    jstring  result = (jstring) env->CallObjectMethod(mFather,use_call_non_virtual);// 如果调用父类方法用Call***Method
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testCallMethod(JNIEnv *env, jobject instance) {
    jclass  a_class = env->GetObjectClass(instance);                                   //因为是非静态的，所以要通过GetObjectClass获取对象
    jmethodID  a_method = env->GetMethodID(a_class,"describe","()Ljava/lang/String;");// 通过GetMethod方法获取方法的methodId.
    jobject jobj = env->AllocObject(a_class);                                         // 对jclass进行实例，相当于java中的new
    jstring pring= (jstring)(env)->CallObjectMethod(jobj,a_method);                 // 类调用类中的方法
    char *print=(char*)(env)->GetStringUTFChars(pring,0);                           // 转换格式输出。
    return env->NewStringUTF(print);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testStaticCallMethod(JNIEnv *env, jclass type) {
    jmethodID  a_method = env->GetMethodID(type,"describe","()Ljava/lang/String;"); // 通过GetMethod方法获取方法的methodId.
    jobject jobj = env->AllocObject(type);                                          // 对jclass进行实例，相当于java中的new
    jstring pring= (jstring)(env)->CallObjectMethod(jobj,a_method);                 // 类调用类中的方法
    char *print=(char*)(env)->GetStringUTFChars(pring,0);                           // 转换格式输出。
    return env->NewStringUTF(print);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testStaticCallStaticMethod(JNIEnv *env, jclass type) {
    jmethodID  a_method = env->GetStaticMethodID(type,"staticDescribe","()Ljava/lang/String;"); // 通过GetStaticMethodID方法获取方法的methodId.
    jstring pring= (jstring)(env)->CallStaticObjectMethod(type,a_method);                       // 类调用类中的方法
    char *print=(char*)(env)->GetStringUTFChars(pring,0);                                       // 转换格式输出。
    return env->NewStringUTF(print);
}

// NewString测试
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testNewString(JNIEnv *env, jclass type) {
    jchar* data = new jchar[7];
    data[0] = 'a';
    data[1] = 's';
    data[2] = 'e';
    data[3] = 'r';
    data[4] = 'b';
    data[5] = 'a';
    data[6] = '0';
    return env->NewString(data, 5);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testNewStringUTF(JNIEnv *env, jclass type) {
    std::string learn="learn android from aserbao";
    return env->NewStringUTF(learn.c_str());//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同.;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_androidndk_TestJNIBean_testStringLength(JNIEnv *env, jclass type,
                                                         jstring inputString_) {
    jint result = env -> GetStringLength(inputString_);
    jint resultUTF = env -> GetStringUTFLength(inputString_);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testGetStringRegion(JNIEnv *env, jclass type,
                                                            jstring inputString_) {
    jint length = env -> GetStringUTFLength(inputString_);
    jint half = length /2;
    jchar* chars = new jchar[half];
    env -> GetStringRegion(inputString_,0,length/2,chars);
    return env->NewString(chars,half);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testGetStringUTFRegion(JNIEnv *env, jclass type,
                                                               jstring inputString_) {
    jint length = env -> GetStringUTFLength(inputString_);
    jint half = length /2;
    char* chars = new char[half];
    env -> GetStringUTFRegion(inputString_,0,length/2,chars);
    return env->NewStringUTF(chars);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_androidndk_TestJNIBean_testChangeString(JNIEnv *env, jclass type,
                                                         jstring inputString_) {
    const char *inputString = env->GetStringUTFChars(inputString_, 0);

    jint stringLength = env -> GetStringUTFLength(inputString_);
    char* chars = new char[stringLength];

    env->ReleaseStringUTFChars(inputString_, inputString);

    return env->NewStringUTF(inputString);
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


extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_TestJNIBean_testGetTArrayElement(JNIEnv *env, jobject instance) {
    jclass  jclazz = env -> GetObjectClass(instance);
    //获取Java中数组属性arrays的id
    jfieldID fid_arrays = env-> GetFieldID(jclazz , "testArrays","[I") ;
    //获取Java中数组属性arrays的对象
    jintArray jint_arr = (jintArray) env->GetObjectField(instance, fid_arrays) ;

    //获取arrays对象的指针
    jint* int_arr = env->GetIntArrayElements(jint_arr, NULL) ;
    //获取数组的长度
    jsize len = env->GetArrayLength(jint_arr) ;
    LOGD("---------------获取到的原始数据为---------------");
    for(int i = 0; i < len; i++){
        LOGD("len %d",int_arr[i]);
    }

    //新建一个jintArray对象
    jintArray jint_arr_temp = env->NewIntArray (len) ;
    //获取jint_arr_temp对象的指针
    jint* int_arr_temp = env->GetIntArrayElements (jint_arr_temp , NULL) ;
    //计数
    jint count = 0;

    LOGD("---------------打印其中是奇数---------------");
    //奇数数位存入到int_ _arr_ temp内存中
    for (jsize j=0;j<len;j++) {
        jint result = int_arr[j];
        if (result % 2 != 0) {
            int_arr_temp[count++] = result;
        }
    }
    //打印int_ _arr_ temp内存中的数组
    for(int k = 0; k < count; k++){
        LOGD("len %d",int_arr_temp[k]);
    }

    LOGD("---------------打印前两位---------------");
    //将数组中一段(1-2)数据拷贝到内存中，并且打印出来
    jint* buffer = new jint[len] ;
    //获取数组中从0开始长度为2的一段数据值
    env->GetIntArrayRegion(jint_arr,0,2,buffer) ;

    for(int z=0;z<2;z++){
        LOGD("len %d",buffer[ z]);
    }

    LOGD("---------------重新赋值打印---------------");
    //创建一个新的int数组
    jint* buffers = new jint[3];
    jint start = 100;
    for (int n = start; n < 3+start ; ++n) {
        buffers[n-start] = n+1;
    }
    //重新给jint_arr数组中的从第1位开始往后3个数赋值
    env -> SetIntArrayRegion(jint_arr,1,3,buffers);
    //从新获取数据指针
    int_arr = env -> GetIntArrayElements(jint_arr,NULL);
    for (int i = 0; i < len; ++i) {
        LOGD("重新赋值之后的结果为 %d",int_arr[i]);
    }

    LOGD("---------------排序---------------");

    std::sort(int_arr,int_arr+len);
    for (int i = 0; i < len; ++i) {
        LOGD("排序结果为 %d",int_arr[i]);
    }

    LOGD("---------------数据处理完成---------------");

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_androidndk_TestJNIBean_testThrowException(JNIEnv *env, jobject instance) {

    jclass jclazz = env -> GetObjectClass(instance);
    jmethodID  throwExc = env -> GetMethodID(jclazz,"throwException","()V");
    if (throwExc != NULL) return;
    env -> CallVoidMethod(instance,throwExc);
    jthrowable excOcc = env -> ExceptionOccurred();
    if (excOcc){
        jclass  newExcCls ;
        env -> ExceptionDescribe();//打印异常堆栈信息
        env -> ExceptionClear();
        jclass newExcClazz = env -> FindClass("java/lang/IllegalArgumentException");
        if (newExcClazz == NULL) return;
        env -> ThrowNew(newExcClazz,"this is a IllegalArgumentException");
    }

}