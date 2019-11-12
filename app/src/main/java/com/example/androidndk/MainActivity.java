package com.example.androidndk;

import android.view.View;

import com.example.androidndk.base.BaseRecyclerViewActivity;
import com.example.androidndk.base.beans.BaseRecyclerBean;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends BaseRecyclerViewActivity {
    private static final String TAG = "MainActivity";
    private TestJNIBean mTestJNIBean;


    @Override
    public void initGetData() {
        mTestJNIBean = new TestJNIBean();
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的Date对象 ",0));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的静态Random带参数 ",10));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的Random带参数 ",1));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中带多参数的第一种方法 ",2));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中带多参数的第二种方法 ",21));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI修改Java对象的属性值",3));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用子类对象的方法",4));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用父类对象的方法",5));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的方法",6));
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI调用Java中的静态方法",61));

    }

    @Override
    public void itemClickBack(View view, int position, boolean isLongClick) {
        switch (position){
            case 0:
                long newJavaDate = mTestJNIBean.testNewJavaDate();
                Date myDate = new Date(newJavaDate);
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                mBaseRecyclerTv.setText(df.format(myDate));
                break;
            case 10:
                long newJavaDateStatic = TestJNIBean.testNewStaticRandomParam(100);
                mBaseRecyclerTv.setText("JNI中获取的随机数为："+String.valueOf(newJavaDateStatic));
                break;
            case 1:
                int testNewRandomParam = mTestJNIBean.testNewRandomParam(100);
                mBaseRecyclerTv.setText("JNI中获取的随机数为："+String.valueOf(testNewRandomParam));
                break;
            case 2:
                String result = mTestJNIBean.testCallMethodParamList();
//                String result = mTestJNIBean.paramListMethod(18,180.8d,'a');
                mBaseRecyclerTv.setText(result);
                break;
            case 21:
                String methodParamList = mTestJNIBean.testCallMethodParamList2(18, "aserbao", 100);
                mBaseRecyclerTv.setText(methodParamList);
                break;
            case 3:
                mTestJNIBean.testChangeField(mTestJNIBean.modelNumber);
                mBaseRecyclerTv.setText("修改属性modelNumber后的值为："+ mTestJNIBean.modelNumber);
                break;
            case 4:
                mBaseRecyclerTv.setText("JNI调用子类对象的方法："+ mTestJNIBean.testCallChildMethod());
                break;
            case 5:
                mBaseRecyclerTv.setText("JNI调用父类对象的方法："+ mTestJNIBean.testCallFatherMethod());
                break;
            case 6:
                mBaseRecyclerTv.setText("JNI调用Java中的方法："+ mTestJNIBean.testCallMethod());
                break;
            case 61:
                mBaseRecyclerTv.setText("JNI调用Java中的方法："+ mTestJNIBean.testStaticCallMethod());
                break;
        }
    }
}
