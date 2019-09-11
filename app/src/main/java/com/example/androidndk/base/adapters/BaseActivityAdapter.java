package com.example.androidndk.base.adapters;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


import com.example.androidndk.R;
import com.example.androidndk.base.beans.ClassBean;
import com.example.androidndk.base.viewHolder.ClassViewHolder;

import java.util.ArrayList;
import java.util.List;

/**
 * description:
 * Created by aserbao on 2018/1/25.
 */


public class BaseActivityAdapter extends RecyclerView.Adapter<ClassViewHolder> {

    private Context mContext;
    private Activity mActivity;
    private List<ClassBean> mClassBeen = new ArrayList<>();

    public BaseActivityAdapter(Context context, Activity activity, List<ClassBean> classBeen) {
        mContext = context;
        mActivity = activity;
        mClassBeen = classBeen;
    }

    @Override
    public ClassViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.base_recycler_view_class_item, parent, false);
        return new ClassViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ClassViewHolder holder, int position) {
        final ClassBean classBean = mClassBeen.get(position);
        holder.mItemCardView.setBackgroundResource(R.drawable.mm_5);
        holder.mItemTv.setText(classBean.getName());
        holder.mItemCardView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(mActivity, classBean.getClazz());
                if (classBean.getFlag() >= 0){
                    intent.setFlags(classBean.getFlag());
                }
                mActivity.startActivity(intent);
            }
        });
    }

    @Override
    public int getItemCount() {
        int ret = 0;
        if (mClassBeen.size() > 0) {
            ret = mClassBeen.size();
        }
        return ret;
    }


}
