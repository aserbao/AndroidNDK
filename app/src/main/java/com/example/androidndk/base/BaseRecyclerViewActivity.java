package com.example.androidndk.base;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import com.example.androidndk.R;
import com.example.androidndk.base.adapters.BaseRecyclerViewActivityAdapter;
import com.example.androidndk.base.beans.BaseRecyclerBean;
import com.example.androidndk.base.interfaces.IBaseRecyclerItemClickListener;
import com.example.androidndk.common.StaticFinalValues;

import java.util.ArrayList;
import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;

/**
 * 功能:
 *
 * @author aserbao
 * @date : On 2019/2/19 4:40 PM
 * @email: this is empty email
 * @project:AserbaosAndroid
 * @package:com.aserbao.aserbaosandroid.base
 */
public abstract class BaseRecyclerViewActivity extends AppCompatActivity implements IBaseRecyclerItemClickListener {


    @BindView(R.id.base_recycler_tv)
    public TextView mBaseRecyclerTv;
    @BindView(R.id.show_data_content_rv)
    public RecyclerView mShowDataContentRv;
    @BindView(R.id.base_recycler_view)
    public RecyclerView mOpenglRecyclerView;
    @BindView(R.id.base_recycler_view_fl)
    public RelativeLayout mBaseRecyclerViewFl;
    @BindView(R.id.base_recycler_empty_container)
    public FrameLayout mBaseRecyclerEmptyContainer;

    protected Context mContext;
    @BindView(R.id.base_up_tv)
    TextView mBaseUpTv;
    @BindView(R.id.base_down_tv)
    TextView mBaseDownTv;


    private LinearLayoutManager mLinearLayoutManager;
    public BaseRecyclerViewActivityAdapter mCommonAdapter;
    public int mOrientation = LinearLayoutManager.VERTICAL;
    public List<BaseRecyclerBean> mBaseRecyclerBeen = new ArrayList<>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTranslations();
        setContentView(R.layout.base_recyclerview_activity);
        ButterKnife.bind(this);
        mContext = this;
        initGetData();
        initViewForLinear();

    }

    public void setTranslations() {
    }

    private int mMode = StaticFinalValues.LINEAR_LAYOUTMANAGER_VERTICAL;

    public void setMode(int mode) {
        mMode = mode;
        switch (mMode) {
            case StaticFinalValues.LINEAR_LAYOUTMANAGER_VERTICAL:
                mOrientation = LinearLayout.VERTICAL;
                break;
            case StaticFinalValues.LINEAR_LAYOUTMANAGER_HORIZONTAL:
                mOrientation = LinearLayout.HORIZONTAL;
                break;
        }
        initViewForLinear();
    }

    public abstract void initGetData();


    public void initViewForLinear() {
        mCommonAdapter = new BaseRecyclerViewActivityAdapter(this, this, mBaseRecyclerBeen, this);
        if (mMode == StaticFinalValues.GRID_LAYOUTMANAGER) {
            mLinearLayoutManager = new GridLayoutManager(this, 3);
        } else {
            mLinearLayoutManager = new LinearLayoutManager(this, mOrientation, false);
        }
        mOpenglRecyclerView.setLayoutManager(mLinearLayoutManager);
        mOpenglRecyclerView.setAdapter(mCommonAdapter);
        mBaseRecyclerViewFl.setBackgroundResource(ASourceUtil.getRandomImageId());

        mOpenglRecyclerView.post(new Runnable() {
            @Override
            public void run() {
                int lastVisibleItemPosition = mLinearLayoutManager.findLastVisibleItemPosition();
                if (lastVisibleItemPosition <= 8) {
                    mBaseUpTv.setVisibility(View.GONE);
                    mBaseDownTv.setVisibility(View.GONE);
                } else {
                    mBaseUpTv.setVisibility(View.VISIBLE);
                    mBaseDownTv.setVisibility(View.VISIBLE);
                }
            }
        });

        mBaseUpTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mLinearLayoutManager.findFirstVisibleItemPosition() == 0) return;
                mOpenglRecyclerView.smoothScrollToPosition(0);
            }
        });

        mBaseDownTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mOpenglRecyclerView.smoothScrollToPosition(mCommonAdapter.getItemCount() - 1);
            }
        });
    }


    public void addViewToFrameLayout(View view){
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT);
        view.setLayoutParams(layoutParams);
        mBaseRecyclerEmptyContainer.setVisibility(View.VISIBLE);
        mBaseRecyclerEmptyContainer.removeAllViews();
        mBaseRecyclerEmptyContainer.addView(view);
    }

    public void addViewToFrameLayoutFullScreen(View view){
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT);
        view.setLayoutParams(layoutParams);
        ViewGroup.LayoutParams layoutParams1 = mBaseRecyclerEmptyContainer.getLayoutParams();
        if (layoutParams1 instanceof ViewGroup.MarginLayoutParams){
            ((ViewGroup.MarginLayoutParams) layoutParams1).setMargins(0,0,0,0);
        }
        mBaseRecyclerEmptyContainer.setLayoutParams(layoutParams1);
        mBaseRecyclerEmptyContainer.setVisibility(View.VISIBLE);
        mBaseRecyclerEmptyContainer.removeAllViews();

        ViewGroup parent = (ViewGroup)view.getParent();
        if (parent != null) parent.removeAllViews();
        mBaseRecyclerEmptyContainer.addView(view);
    }

    @Override
    public void onBackPressed() {
        if (mBaseRecyclerEmptyContainer.getChildCount() > 0){
            mBaseRecyclerEmptyContainer.removeAllViews();
            return;
        }
        super.onBackPressed();
    }



}
