package com.example.androidndk;


import java.util.Random;

public class TestJNIBean{

    private static final String TAG = "TestJNIBean";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

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



    public int modelNumber = 100;
    /**
     * 修改modelNumber属性
     */
    public native void testChangeField(int modelNumber);
    //==================测试如何调用父类方法？
    public Father father = new Child();
    public native String testCallFatherMethod();
    public native String testCallChildMethod();



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String carNameFromJNI();

    public native void showCardFromJNI();

    public native String testCallMethod();
    public static native String testStaticCallMethod();







    public  String describe(){
        return "this is a beautiful car";
    }

}
