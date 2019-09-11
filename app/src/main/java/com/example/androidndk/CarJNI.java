package com.example.androidndk;


import java.util.Date;
import java.util.Random;

public class CarJNI {

    private static final String TAG = "CarJNI";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public  int modelNumber;

    public String getCuurTime(){
        long time = new Date().getTime();
        return String.valueOf(time);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String carNameFromJNI();

    public native void showCardFromJNI();

    public native String testCallMethod();

    public native void testChangeField();

    public native long testNewJavaDate();


    public native int testNewRandomParam(int random);


    public int getRandom(int range){
        return new Random().nextInt(range);
    }

    /**
     * 测试调用带参数的方法
     */
    public native String testCallMethodParamList(int num, String str, int num2);

    public String paramListMethod(int num1, String str, int num2) {
        return str + " 年龄：" + num1 + " 成绩为：" + num2;
    }

    public  String describe(){
        return "this is a beautiful car";
    }

}
