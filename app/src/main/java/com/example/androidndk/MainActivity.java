package com.example.androidndk;

import android.view.View;

import com.example.androidndk.base.BaseRecyclerViewActivity;
import com.example.androidndk.base.beans.BaseRecyclerBean;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends BaseRecyclerViewActivity {
    private static final String TAG = "MainActivity";
    private TestJNIBean mTestJNIBean;
    public static final int TEST_LOG_IN_JNI = 0;
    public static final int JNI_CALL_MOTHOD = 1;
    public static final int JNI_CALL_DATE = 2;
    public static final int JNI_CALL_RANDOM = 3;
    public static final int JNI_STATIC_CALL_RANDOM = 4;
    public static final int JNI_CALL_POLYMORPHISM = 5;
    public static final int JNI_CALL_STRING = 6;
    public static final int JNI_ARRAT = 7;
    public static final int JNI_EXCEPTION = 8;



    @Override
    public void initGetData() {
        mTestJNIBean = new TestJNIBean();
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中打印日志 ",TEST_LOG_IN_JNI));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的Date对象 ",JNI_CALL_DATE));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的静态Random带参数 ",JNI_STATIC_CALL_RANDOM));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的Random带参数 ",JNI_CALL_RANDOM));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的方法", JNI_CALL_MOTHOD));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中带多参数的第一种方法 ",2));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中带多参数的第二种方法 ",21));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI修改Java对象的属性值",3));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中多态的调用",JNI_CALL_POLYMORPHISM));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中调用Java中String",JNI_CALL_STRING));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中调用Java中String",JNI_CALL_STRING));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中调用Java中基本数组",JNI_ARRAT));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI中异常处理",JNI_EXCEPTION));


    }

    @Override
    public void itemClickBack(View view, int position, boolean isLongClick) {
        switch (position){
            case TEST_LOG_IN_JNI:
                TestJNIBean.testLogInJNI();
                break;
            case JNI_CALL_DATE:
                long newJavaDate = mTestJNIBean.testNewJavaDate();
                Date myDate = new Date(newJavaDate);
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                mBaseRecyclerTv.setText(df.format(myDate));
                break;
            case JNI_STATIC_CALL_RANDOM:
                long newJavaDateStatic = TestJNIBean.testNewStaticRandomParam(100);
                mBaseRecyclerTv.setText("JNI中获取的随机数为："+String.valueOf(newJavaDateStatic));
                break;
            case JNI_CALL_RANDOM:
                int testNewRandomParam = mTestJNIBean.testNewRandomParam(100);
                mBaseRecyclerTv.setText("JNI中获取的随机数为："+String.valueOf(testNewRandomParam));
                break;
            case JNI_CALL_MOTHOD:
                String staticCallMethod = mTestJNIBean.testStaticCallMethod();
                String staticCallStaticMethod = mTestJNIBean.testStaticCallStaticMethod();
                mBaseRecyclerTv.setText("JNI调用Java中的方法：非静态结果："+ mTestJNIBean.testCallMethod()
                        + "\n 静态结果：" + staticCallMethod
                        + "\n JNI中调用Java中的静态方法 = "  + staticCallStaticMethod) ;
                break;
            case JNI_ARRAT:
                mTestJNIBean.testGetTArrayElement();
                break;
            case 21:
                String methodParamList = mTestJNIBean.testCallMethodParamList2(18, "aserbao", 100);
                mBaseRecyclerTv.setText(methodParamList);
                break;
            case JNI_CALL_POLYMORPHISM:
                String callChildMethod = mTestJNIBean.testCallChildMethod();
                String callFatherMethod = mTestJNIBean.testCallFatherMethod();
                mBaseRecyclerTv.setText("JNI调用子类对象的方法："+ callChildMethod + "\n 调用父类对象方法的结果为：" + callFatherMethod);
                break;
            case JNI_CALL_STRING:
                String aserbao = TestJNIBean.testChangeString("aserbao");
                mBaseRecyclerTv.setText(aserbao);
                break;
            case JNI_EXCEPTION:
                mTestJNIBean.testThrowException();
                break;
        }
    }
}
