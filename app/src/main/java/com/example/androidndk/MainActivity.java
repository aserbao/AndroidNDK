package com.example.androidndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.androidndk.base.BaseRecyclerViewActivity;
import com.example.androidndk.base.beans.BaseRecyclerBean;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends BaseRecyclerViewActivity {
    private static final String TAG = "MainActivity";
    private CarJNI mCarJNI;


    @Override
    public void initGetData() {
        mBaseRecyclerBeen.add(new BaseRecyclerBean("JNI构造Java中的Date",0));
        mCarJNI = new CarJNI();
    }

    @Override
    public void itemClickBack(View view, int position, boolean isLongClick) {
        switch (position){
            case 0:
                long newJavaDate = mCarJNI.testNewJavaDate();
                Date myDate = new Date(newJavaDate);
                SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                mBaseRecyclerTv.setText(df.format(myDate));
                break;
        }
    }
}
