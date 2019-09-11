package com.example.androidndk.base.viewHolder;

import android.support.annotation.NonNull;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.androidndk.R;
import com.example.androidndk.base.ASourceUtil;
import com.example.androidndk.base.beans.BaseRecyclerBean;
import com.example.androidndk.base.interfaces.IBaseRecyclerItemClickListener;

import butterknife.BindView;

public class ImageViewHolder extends BaseClickViewHolder {
        @BindView(R.id.image_view_item)
        ImageView mImageViewItem;

        @BindView(R.id.common_text_view)
        TextView mCommonTextView;

        public ImageViewHolder(@NonNull View itemView) {
            super(itemView);
        }

        public void setDataSource(BaseRecyclerBean classBean, int position, IBaseRecyclerItemClickListener mIBaseRecyclerItemClickListener){
            super.setDataSource(position,mIBaseRecyclerItemClickListener);

            int tag = classBean.getTag();
            String name = classBean.getName();
            if (tag >= 0) {
                itemView.setTag(tag);
                name = name + " "+ tag;
            }else{
                name = name + " "+ position;
            }
            mCommonTextView.setText(name);

            mImageViewItem.setImageResource(classBean.getImageSrc());


        }

    }