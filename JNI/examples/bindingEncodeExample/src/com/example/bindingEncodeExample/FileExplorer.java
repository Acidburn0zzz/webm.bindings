// Author:hkuang@google.com (Hangyu Kuang)

package com.example.bindingEncodeExample;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class FileExplorer extends ListActivity {
    private static final String TAG = "FileExplorer";
    private List<String> mItem = null;
    private List<String> mPath = null;
    private String mRoot;
    private TextView mCurPath;
    private Boolean mChoosingVideoFile = false;
    private Boolean mChoosingAudioFile = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.file_explore);

        Bundle extras = getIntent().getExtras();
        String value1 = extras.getString(Intent.EXTRA_TEXT);
        if (value1.equals("choosingVideo")) {
            mChoosingVideoFile = true;
        } else {
            mChoosingAudioFile = true;
        }

        mCurPath = (TextView) findViewById(R.id.path);
        mRoot = Environment.getExternalStorageDirectory().getPath();
        getDir(mRoot);
    }

    private void getDir(String dirPath) {
        mCurPath.setText("Path: " + dirPath);
        mItem = new ArrayList<String>();
        mPath = new ArrayList<String>();
        File dir = new File(dirPath);
        File[] files = dir.listFiles();

        if (!dirPath.equals(mRoot)) {
            mItem.add(mRoot);
            mPath.add(mRoot);
            mItem.add("../");
            mPath.add(dir.getParent());
        }

        for (int i = 0; i < files.length; i++) {
            File file = files[i];

            if (!file.isHidden() && file.canRead()) {
                mPath.add(file.getPath());
                if (file.isDirectory()) {
                    mItem.add(file.getName() + "/");
                } else {
                    mItem.add(file.getName());
                }
            }
        }

        ArrayAdapter<String> fileList = new ArrayAdapter<String>(this, R.layout.rows, mItem);
        setListAdapter(fileList);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        File file = new File(mPath.get(position));

        if (file.isDirectory()) {
            if (file.canRead()) {
                getDir(mPath.get(position));
            } else {
                new AlertDialog.Builder(this).setIcon(R.drawable.ic_launcher)
                .setTitle("[" + file.getName() + "] folder can't be read!")
                .setPositiveButton("OK", null).show();
            }
        } else {
            String filePath = file.getAbsolutePath();
            if (mChoosingVideoFile == true) {
                VideoEncoderSetting.mVideoFilePath = filePath;
                mChoosingVideoFile = false;
            } else {
                AudioEncoderSetting.mAduioFilePath = filePath;
                mChoosingAudioFile = false;
            }
            finish();
        }
    }
}