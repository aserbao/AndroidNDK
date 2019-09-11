package com.example.androidndk.base.viewHolder;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.widget.CardView;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.TextView;

import com.example.androidndk.R;
import com.example.androidndk.base.ASourceUtil;
import com.example.androidndk.base.beans.BaseRecyclerBean;

import butterknife.BindView;
import butterknife.ButterKnife;

public class ClassViewHolder extends RecyclerView.ViewHolder {
        @BindView(R.id.item_tv)
        public TextView mItemTv;
        @BindView(R.id.item_card_view)
        public CardView mItemCardView;
        public ClassViewHolder(View itemView) {
            super(itemView);
            ButterKnife.bind(this, itemView);
        }

        public void setDataSource(final Activity mActivity, final BaseRecyclerBean classBean){
            mItemCardView.setBackgroundResource(ASourceUtil.getRandomImageId());
            mItemTv.setText(classBean.getName());
            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Intent intent = new Intent(mActivity, classBean.getClazz());
                    mActivity.startActivity(intent);
                }
            });
        }
    }