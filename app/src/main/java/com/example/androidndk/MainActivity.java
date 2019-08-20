package com.example.androidndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @BindView(R.id.sample_text)
    TextView mSampleText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
    }


    @OnClick({R.id.method_one, R.id.method_two})
    public void onViewClicked(View view) {
        CarJNI carJNI = new CarJNI();
        switch (view.getId()) {
            case R.id.method_one:
                mSampleText.setText(carJNI.carNameFromJNI());
                break;
            case R.id.method_two:
//                carJNI.showCardFromJNI();
//                testChangeJavaField();
                testNewJavaBean();
                break;

        }
    }

    /**
     * ---------------修改类的属性值
     */
    private void testChangeJavaField() {
        CarJNI carJNI1 = new CarJNI();
        carJNI1.testChangeField();
        Log.e(TAG, "onViewClicked: " + carJNI1.modelNumber);
    }

    private void testNewJavaBean(){
        CarJNI carJNI1 = new CarJNI();
        carJNI1.testNewJavaBean();
    }
}
