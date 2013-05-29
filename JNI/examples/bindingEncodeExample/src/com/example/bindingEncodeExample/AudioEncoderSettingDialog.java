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

public class AudioEncoderSettingDialog extends Activity {

    // UI stuff.
    private Button mAudioBitrateButton;
    private Button mMinAudioBitrateButton;
    private Button mMaxAudioBitrateButton;
    private TextView mAudioBitrateInput;
    private TextView mMinAudioBitrateInput;
    private TextView mMaxAudioBitrateInput;

    final Context context = this;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.audio_dialog_settings);

        // Setup audio bitrate display and button handler.
        mAudioBitrateInput = (TextView) findViewById(R.id.audioBitrateResult);
        mAudioBitrateInput.setText(String.valueOf(AudioEncoderSetting.mAudioBitrate));
        mAudioBitrateButton = (Button) findViewById(R.id.audioBitrateBtn);
        mAudioBitrateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(context);
                View promptsView = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
                alertDialogBuilder.setView(promptsView);

                final EditText userInput = (EditText) promptsView.findViewById(R.id.userInput);

                // set dialog message
                alertDialogBuilder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mAudioBitrateInput.setText(userInput.getText());
                                AudioEncoderSetting.mAudioBitrate =
                                        Integer.parseInt(mAudioBitrateInput.getText().toString());
                            }
                        }).setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

                // create alert dialog
                AlertDialog alertDialog = alertDialogBuilder.create();

                // show it
                alertDialog.show();
            }
        });

        // SetupSet up minAudioBitrate display and button handler.
        mMinAudioBitrateInput = (TextView) findViewById(R.id.minAudioBitrateResult);
        mMinAudioBitrateInput.setText(String.valueOf(AudioEncoderSetting.mMinAudioBitRate));
        mMinAudioBitrateButton = (Button) findViewById(R.id.minAudioBitrateBtn);
        mMinAudioBitrateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(context);
                View promptsView = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
                alertDialogBuilder.setView(promptsView);

                final EditText userInput = (EditText) promptsView.findViewById(R.id.userInput);

                // set dialog message
                alertDialogBuilder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mMinAudioBitrateInput.setText(userInput.getText());
                                AudioEncoderSetting.mMinAudioBitRate =
                                        Integer.parseInt(
                                                mMinAudioBitrateInput.getText().toString());
                            }
                        }).setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });

                // create alert dialog
                AlertDialog alertDialog = alertDialogBuilder.create();

                // show it
                alertDialog.show();
            }
        });

        // Set up maxAudioBitrate display and button handler.
        mMaxAudioBitrateInput = (TextView) findViewById(
                R.id.maxAudioBitrateResult);
        mMaxAudioBitrateInput.setText(
                String.valueOf(AudioEncoderSetting.mMaxAudioBitrate));
        mMaxAudioBitrateButton = (Button) findViewById(R.id.maxAudioBitrateBtn);
        mMaxAudioBitrateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                LayoutInflater inflater = LayoutInflater.from(context);
                View promptsView = inflater.inflate(R.layout.alert_diag, null);
                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
                alertDialogBuilder.setView(promptsView);

                final EditText userInput = (EditText) promptsView.findViewById(R.id.userInput);

                // set dialog message
                alertDialogBuilder.setCancelable(false).setPositiveButton(
                        "OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                mMaxAudioBitrateInput.setText(userInput.getText());
                                AudioEncoderSetting.mMaxAudioBitrate =
                                        Integer.parseInt(
                                                mMaxAudioBitrateInput.getText().toString());
                            }
                        }).setNegativeButton(
                                "Cancel", new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int id) {
                                        dialog.cancel();
                                    }
                                });

                // create alert dialog
                AlertDialog alertDialog = alertDialogBuilder.create();

                // show it
                alertDialog.show();
            }
        });
    }
}