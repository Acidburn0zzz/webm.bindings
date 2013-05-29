// Author:hkuang@google.com (Hangyu Kuang)

package com.example.bindingEncodeExample;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class VideoEncoderSettingDialog extends Activity {

    // UI stuff.
    private Button mThreadNumButton;
    private Button mTargetBitrateButton;
    private Button mMinQuantizerButton;
    private Button mMaxQuantizerButton;
    private Button mKfMinDistButton;
    private Button mKfMaxDistButton;
    private Button mCpuUsedButton;
    private TextView mThreadNumInput;
    private TextView mTargetBitrateInput;
    private TextView mMinQuantizerInput;
    private TextView mMaxQuantizerInput;
    private TextView mKfMinDistInput;
    private TextView mKfMaxDistInput;
    private TextView mCpuUsedInput;

    final Context mContext = this;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.video_dialog_settings);

        // Setup thread number display and button handler.
        mThreadNumInput = (TextView) findViewById(R.id.threadNumsResult);
        mThreadNumInput.setText(String.valueOf(VideoEncoderSetting.mThreadNum));
        mThreadNumButton = (Button) findViewById(R.id.threadNumsBtn);
        mThreadNumButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mThreadNumInput.setText(userInput.getText());
                                VideoEncoderSetting.mThreadNum =
                                        Integer.parseInt(mThreadNumInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup target bitrate display and button handler.
        mTargetBitrateInput = (TextView) findViewById(R.id.targetBitrateResult);
        mTargetBitrateInput.setText(String.valueOf(VideoEncoderSetting.mTargetBitrate));
        mTargetBitrateButton = (Button) findViewById(R.id.targetBitrateBtn);
        mTargetBitrateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mTargetBitrateInput.setText(userInput.getText());
                                VideoEncoderSetting.mTargetBitrate =
                                        Integer.parseInt(mTargetBitrateInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup minQuantizer display and button handler.
        mMinQuantizerInput = (TextView) findViewById(R.id.minQuantizerResult);
        mMinQuantizerInput.setText(String.valueOf(VideoEncoderSetting.mMinQuantizer));
        mMinQuantizerButton = (Button) findViewById(R.id.minQuantizerBtn);
        mMinQuantizerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mMinQuantizerInput.setText(userInput.getText());
                                VideoEncoderSetting.mMinQuantizer =
                                        Integer.parseInt(mMinQuantizerInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup maxQuantizer display and button handler.
        mMaxQuantizerInput = (TextView) findViewById(R.id.maxQuantizerResult);
        mMaxQuantizerInput.setText(String.valueOf(VideoEncoderSetting.mMaxQuantizer));
        mMaxQuantizerButton = (Button) findViewById(R.id.maxQuantizerBtn);
        mMaxQuantizerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mMaxQuantizerInput.setText(userInput.getText());
                                VideoEncoderSetting.mMaxQuantizer =
                                        Integer.parseInt(mMaxQuantizerInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup kfMinDist display and button handler.
        mKfMinDistInput = (TextView) findViewById(R.id.kfMinDistResult);
        mKfMinDistInput.setText(String.valueOf(VideoEncoderSetting.mKfMinDist));
        mKfMinDistButton = (Button) findViewById(R.id.kfMinDistBtn);
        mKfMinDistButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mKfMinDistInput.setText(userInput.getText());
                                VideoEncoderSetting.mKfMinDist =
                                        Integer.parseInt(mKfMinDistInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup kfMaxDist display and button handler.
        mKfMaxDistInput = (TextView) findViewById(R.id.kfMaxDistResult);
        mKfMaxDistInput.setText(String.valueOf(VideoEncoderSetting.mKfMaxDist));
        mKfMaxDistButton = (Button) findViewById(R.id.kfMaxDistBtn);
        mKfMaxDistButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mKfMaxDistInput.setText(userInput.getText());
                                VideoEncoderSetting.mKfMaxDist =
                                        Integer.parseInt(mKfMaxDistInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });

        // Setup cpuUsed display and button handler.
        mCpuUsedInput = (TextView) findViewById(R.id.cpuUsedResult);
        mCpuUsedInput.setText(String.valueOf(VideoEncoderSetting.mCpuUsed));
        mCpuUsedButton = (Button) findViewById(R.id.cpuUsedBtn);
        mCpuUsedButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(mContext);
                View view = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setView(view);

                final EditText userInput = (EditText) view.findViewById(R.id.userInput);

                // set dialog message
                builder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mCpuUsedInput.setText(userInput.getText());
                                VideoEncoderSetting.mCpuUsed = Integer.parseInt(
                                        mCpuUsedInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = builder.create();

                // show it
                alertDialog.show();
            }
        });
    }
}
