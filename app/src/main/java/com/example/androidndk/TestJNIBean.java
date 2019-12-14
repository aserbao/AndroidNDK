package com.example.androidndk;


import java.util.Random;

/**
 *
 */
public class TestJNIBean{
    public static final String LOGO = "learn android with aserbao";
    private static final String TAG = "TestJNIBean";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public static native void testLogInJNI();


    public native long testNewJavaDate();
    public native int testNewRandomParam(int random);
    public static native int testNewStaticRandomParam(int random);
    public static int getRandom(int range){
        return new Random().nextInt(range);
    }
    public native String testCallMethodParamList();
    public String paramListMethod(int age,double height,char name){
        return "帅气的"+name + " 年龄：" + age + " 身高为：" + height;
    }
    /**
     * 测试调用带多个参数的方法
     */
    public native String testCallMethodParamList2(int num, String str, int num2);
    public String paramListMethod2(int num1, String str, int num2) {
        return "帅气的"+str + " 年龄：" + num1 + " 成绩为：" + num2;
    }

    //==================测试如何调用父类方法？
    public Father father = new Child();
    public native String testCallFatherMethod();
    public native String testCallChildMethod();


    public int modelNumber = 1;
    /**
     * 修改modelNumber属性
     */
    public native void testChangeField();


    /**
     * 在C/C++中操作Java字符
     */
    public static native String testNewString();
    public static native String testNewStringUTF();
    public static native int testStringLength(String inputString);
    public static native String testGetStringRegion(String inputString);
    public static native String testGetStringUTFRegion(String inputString);
    public static native String testChangeString(String inputString);

    /**
     * 测试在C/C++中操作Java中的基本数组
     */
    int[] testArrays = {1,2,3,4,5,8,6};
    public native void testGetTArrayElement();

    public native void testThrowException();
    private void throwException() throws NullPointerException{
        throw new NullPointerException("this is an NullPointerException");
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String carNameFromJNI();

    public native void showCardFromJNI();

    public native String testCallMethod();

    public static native String testStaticCallMethod();

    public static native String testStaticCallStaticMethod();

    public  String describe(){
        return LOGO + "非静态方法";
    }

    public static String staticDescribe(){
        return LOGO + "静态方法";
    }

}
