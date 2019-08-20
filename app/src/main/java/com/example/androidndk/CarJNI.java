package com.example.androidndk;


import java.util.Date;

public class CarJNI {

    private static final String TAG = "CarJNI";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public  int modelNumber;

    public void showDetailAboutCar(int level, int modelNumber, int price) {
        String result = "CarJNI{" +
                "level=" + level +
                ", modelNumber='" + modelNumber + '\'' +
                ", price=" + price +
                '}';
        System.out.println(result);
        Date date = new Date();
    };

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

    public native void testChangeField();

    public native void testNewJavaBean();


}
