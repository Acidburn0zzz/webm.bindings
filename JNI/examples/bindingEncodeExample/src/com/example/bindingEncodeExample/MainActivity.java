// Author:hkuang@google.com (Hangyu Kuang)

package com.example.bindingEncodeExample;

import android.app.Activity;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnVideoSizeChangedListener;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import com.google.libvorbis.AudioFrame;
import com.google.libvorbis.VorbisEncConfig;
import com.google.libvorbis.VorbisEncoderC;
import com.google.libvorbis.VorbisException;
import com.google.libvpx.LibVpxEnc;
import com.google.libvpx.LibVpxEncConfig;
import com.google.libvpx.Rational;
import com.google.libvpx.VpxCodecCxPkt;
import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.utils.WavReader;
import com.google.utils.Y4MReader;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends Activity
implements OnVideoSizeChangedListener, OnCompletionListener {
    private static final String TAG = "bindingEncodeExample";

    // Constants.
    private static final int VIDEO_FILE_CHOOSE = 1;
    private static final int AUDIO_FILE_CHOOSE = 2;
    private static final int VIDEO_CONFIG = 3;
    private static final int AUDIO_CONFIG = 4;

    // UI stuff.
    private int mVideoWidth = 0;
    private int mVideoHeight = 0;
    private SurfaceView mSurfaceView;
    private SurfaceHolder mSurfaceHolder;
    private Button mVideoConfigButton;
    private Button mAudioConfigButton;
    private Button mStartEncodeButton;
    private Button mPlayVideoButton;
    private Button mVideoSrcButton;
    private Button mAudioSrcButton;
    private TextView mVideoSrcDispView;
    private TextView mAudioSrcDispView;
    private TextView mOutputFilePathView;
    private TextView mVideoConfigDispView;
    private TextView mAudioConfigDispView;
    private TextView mEncodingStatsDispView;
    private TextView mPlayingStatsDispView;

    // Mediaplayer for video playback.
    private MediaPlayer mMediaPlayer;

    // Output Webm file path.
    private String mWebmFileOutputPath =
            Environment.getExternalStorageDirectory().getAbsolutePath() + "/out.webm";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Setup all the view to display information.
        mSurfaceView = (SurfaceView) findViewById(R.id.surface);
        mVideoSrcDispView = (TextView) findViewById(R.id.videoSrcDisp);
        mAudioSrcDispView = (TextView) findViewById(R.id.audioSrcDisp);
        mEncodingStatsDispView = (TextView) findViewById(R.id.EncodingStatsDisp);
        mPlayingStatsDispView = (TextView) findViewById(R.id.PlayingStatsDisp);
        mVideoConfigDispView = (TextView) findViewById(R.id.videoEncodeConfigDisp);
        mAudioConfigDispView = (TextView) findViewById(R.id.audioEncodeConfigDisp);
        mOutputFilePathView = (TextView) findViewById(R.id.fileOutputDisp);

        // Setup mediaplayer for video playback.
        mMediaPlayer = new MediaPlayer();
        mMediaPlayer.setOnVideoSizeChangedListener(this);
        mMediaPlayer.setOnCompletionListener(this);

        /**
         * Initialize all the buttons.
         */
        // Setup video file select button.
        mVideoSrcButton = (Button) findViewById(R.id.videoSrcBtn);
        mVideoSrcButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(getApplicationContext(),
                        com.example.bindingEncodeExample.FileExplorer.class);
                intent.putExtra(android.content.Intent.EXTRA_TEXT, "choosingVideo");
                startActivityForResult(intent, VIDEO_FILE_CHOOSE);
            }
        });

        // Setup audio file select button.
        mAudioSrcButton = (Button) findViewById(R.id.audioSrcBtn);
        mAudioSrcButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(getApplicationContext(),
                        com.example.bindingEncodeExample.FileExplorer.class);
                intent.putExtra(android.content.Intent.EXTRA_TEXT, "choosingAudio");
                startActivityForResult(intent, AUDIO_FILE_CHOOSE);
            }
        });

        // Setup video config button.
        mVideoConfigButton = (Button) findViewById(R.id.videoEncodeConfigBtn);
        mVideoConfigButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent settingIntent = new Intent();
                settingIntent.setClass(getApplicationContext(),
                        com.example.bindingEncodeExample.VideoEncoderSettingDialog.class);
                startActivityForResult(settingIntent, VIDEO_CONFIG);
            }
        });

        // Setup audio config button.
        mAudioConfigButton = (Button) findViewById(R.id.audioEncodeConfigBtn);
        mAudioConfigButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent settingIntent = new Intent();
                settingIntent.setClass(getApplicationContext(),
                        com.example.bindingEncodeExample.AudioEncoderSettingDialog.class);
                startActivityForResult(settingIntent, AUDIO_CONFIG);
            }
        });

        // Setup start encode button.
        mStartEncodeButton = (Button) findViewById(R.id.StartEncodeBtn);
        mStartEncodeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Start an aysnc encoder task in the background.
                new EncodeY4mWavTask().execute((Void) null);
            }
        });

        // Setup play video button.
        mPlayVideoButton = (Button) findViewById(R.id.PlayVideoBtn);
        mPlayVideoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mPlayingStatsDispView.setText("Playing Video");
                try {
                    mMediaPlayer.setDataSource(mWebmFileOutputPath);
                    mSurfaceHolder = mSurfaceView.getHolder();
                    mSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
                    mMediaPlayer.setDisplay(mSurfaceHolder);
                    mMediaPlayer.prepare();
                } catch (IllegalArgumentException e) {
                    e.printStackTrace();
                } catch (IllegalStateException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                mMediaPlayer.start();
            }
        });

        // Display the default video/audio configuration.
        updateVideoConfigDisplay();
        updateAudioConfigDisplay();

        // Display the file output path.
        mOutputFilePathView.setText(mWebmFileOutputPath);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    protected void onActivityResult(
            int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
        case VIDEO_FILE_CHOOSE:
            // Update video source file path.
            mVideoSrcDispView.setText(VideoEncoderSetting.mVideoFilePath);
            break;

        case AUDIO_FILE_CHOOSE:
            // Update audio source file path.
            mAudioSrcDispView.setText(AudioEncoderSetting.mAduioFilePath);
            break;
        case VIDEO_CONFIG:
            // Update video encoder configuration.
            updateVideoConfigDisplay();
            break;
        case AUDIO_CONFIG:
            // Update audio encoder configuration.
            updateAudioConfigDisplay();
            break;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onVideoSizeChanged(MediaPlayer mp, int width, int height) {
        Log.v(TAG, "onVideoSizeChanged called");
        if (width == 0 || height == 0) {
            Log.e(TAG, "invalid video width(" + width + ") or height(" + height + ")");
            return;
        }
        // Update the video size and surface size.
        mVideoWidth = width;
        mVideoHeight = height;
        mSurfaceHolder.setFixedSize(mVideoWidth, mVideoHeight);
    }

    @Override
    public void onCompletion(MediaPlayer mp) {
        mPlayingStatsDispView.setText("Done playing video");
    }

    // Display video configuration on the text view.
    private void updateVideoConfigDisplay() {
        String str;
        str = "thread:" + VideoEncoderSetting.mThreadNum + " " + "bitrate:"
                + VideoEncoderSetting.mTargetBitrate + " " + "minQuantizer:"
                + VideoEncoderSetting.mMinQuantizer + " " + "maxQuantizer:"
                + VideoEncoderSetting.mMaxQuantizer + " " + "kfMinDist:"
                + VideoEncoderSetting.mKfMinDist + " " + "kfMaxDist:"
                + VideoEncoderSetting.mKfMaxDist + " " + "cpu::"
                + VideoEncoderSetting.mCpuUsed;
        mVideoConfigDispView.setText(str);
    }

    // Display audio configuration on the text view.
    private void updateAudioConfigDisplay() {
        String str;
        str = "AudioBitrate:" + AudioEncoderSetting.mAudioBitrate + " "
                + "MinAudioBitrate:" + AudioEncoderSetting.mMinAudioBitRate + " "
                + "MaxAudioBitrate:" + AudioEncoderSetting.mMaxAudioBitrate;
        mAudioConfigDispView.setText(str);
    }

    // WebM encoder task running in the background.
    private class EncodeY4mWavTask extends AsyncTask<Void, String, String> {
        /*
         * This function will encode an audio and video WebM file. The source
         * video must be a Y4M file with raw i420 frames. The source audio must
         * be a WAV file with raw PCM data. On success, it will return
         * "Encoding Done". On failure, it will return error string.
         */
        @Override
        protected String doInBackground(Void... params) {
            StringBuilder error = new StringBuilder();
            String y4mName = VideoEncoderSetting.mVideoFilePath;
            String wavName = AudioEncoderSetting.mAduioFilePath;
            int framesToEncode = 500; // maximum frames to encode.

            LibVpxEncConfig vpxConfig = null;
            LibVpxEnc vpxEncoder = null;
            VorbisEncoderC vorbisEncoder = null;
            VorbisEncConfig vorbisConfig = null;
            MkvWriter mkvWriter = null;

            try {
                if (y4mName == null) {
                    error.append("Please select video file using above button");
                    return error.toString();
                }

                File y4mFile = new File(y4mName);
                Y4MReader y4mReader;
                try {
                    y4mReader = new Y4MReader(y4mFile);
                } catch (IOException e) {
                    error.append("Invalid y4m file:" + y4mName);
                    return error.toString();
                }

                vpxConfig = new LibVpxEncConfig(
                        y4mReader.getWidth(), y4mReader.getHeight());
                vpxEncoder = new LibVpxEnc(vpxConfig);

                // libwebm expects nanosecond units
                vpxConfig.setTimebase(1, 1000000000);

                // setup video encoder configuration.
                vpxConfig.setThreads(VideoEncoderSetting.mThreadNum);
                vpxConfig.setRCTargetBitrate(VideoEncoderSetting.mTargetBitrate);
                vpxConfig.setRCMinQuantizer(VideoEncoderSetting.mMinQuantizer);
                vpxConfig.setRCMaxQuantizer(VideoEncoderSetting.mMaxQuantizer);
                vpxConfig.setRCTargetBitrate(VideoEncoderSetting.mKfMinDist);
                vpxConfig.setRCTargetBitrate(VideoEncoderSetting.mKfMaxDist);
                vpxConfig.setRCTargetBitrate(VideoEncoderSetting.mCpuUsed);

                Rational timeBase = vpxConfig.getTimebase();
                Rational timeMultiplier = timeBase.multiply(y4mReader.getFrameRate()).reciprocal();
                int framesIn = 1;

                if (y4mName == null) {
                    error.append("Please select audio file using above button");
                    return error.toString();
                }

                File pcmFile = new File(wavName);
                WavReader wavReader = null;
                try {
                    wavReader = new WavReader(pcmFile);
                } catch (Exception e) {
                    error.append("Invalid wav file:" + wavName);
                    return error.toString();
                }

                final int channels = wavReader.nChannels();
                final int sampleRate = wavReader.nSamplesPerSec();

                try {
                    vorbisConfig = new VorbisEncConfig(channels,
                            sampleRate, wavReader.wBitsPerSample());
                    vorbisConfig.setTimebase(1, 1000000000);
                    vorbisConfig.setAverageBitrate(AudioEncoderSetting.mAudioBitrate);
                    vorbisConfig.setMinimumBitrate(AudioEncoderSetting.mMinAudioBitRate);
                    vorbisConfig.setMaximumBitrate(AudioEncoderSetting.mMaxAudioBitrate);
                    vorbisEncoder = new VorbisEncoderC(vorbisConfig);
                } catch (VorbisException e) {
                    error.append("Error creating Vorbis encoder.");
                    return error.toString();
                }

                mkvWriter = new MkvWriter();
                if (!mkvWriter.open(mWebmFileOutputPath)) {
                    error.append("WebM Output name is invalid or error while opening.");
                    return error.toString();
                }

                Segment muxerSegment = new Segment();
                if (!muxerSegment.init(mkvWriter)) {
                    error.append("Could not initialize muxer segment.");
                    return error.toString();
                }

                SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
                muxerSegmentInfo.setWritingApp("y4mwavEncodeSample");

                // Add video Track
                long newVideoTrackNumber = muxerSegment.addVideoTrack(
                        vpxConfig.getWidth(), vpxConfig.getHeight(), 0);
                if (newVideoTrackNumber == 0) {
                    error.append("Could not add video track.");
                    return error.toString();
                }

                // Add audio Track
                long newAudioTrackNumber = muxerSegment.addAudioTrack(sampleRate, channels, 0);
                if (newAudioTrackNumber == 0) {
                    error.append("Could not add audio track.");
                    return error.toString();
                }

                AudioTrack muxerTrack =
                        (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
                if (muxerTrack == null) {
                    error.append("Could not get audio track.");
                    return error.toString();
                }

                byte[] buffer = vorbisEncoder.CodecPrivate();
                if (buffer == null) {
                    error.append("Could not get audio private data.");
                    return error.toString();
                }
                if (!muxerTrack.setCodecPrivate(buffer)) {
                    error.append("Could not add audio private data.");
                    return error.toString();
                }

                final int maxSamplesToRead = 1000;
                AudioFrame vorbisFrame = null;
                ArrayList<VpxCodecCxPkt> encPkt = null;
                VpxCodecCxPkt pkt = null;
                int pktIndex = 0;
                boolean audioDone = false;
                boolean videoDone = false;
                boolean encoding = true;
                while (encoding) {
                    // Prime the audio encoder.
                    while (vorbisFrame == null) {
                        final int samplesLeft = wavReader.samplesRemaining();
                        final int samplesToRead = Math.min(samplesLeft, maxSamplesToRead);
                        if (samplesToRead > 0) {
                            // Read raw audio data.
                            byte[] pcmArray = null;
                            try {
                                pcmArray = wavReader.readSamples(samplesToRead);
                            } catch (Exception e) {
                                error.append("Could not read audio samples.");
                                return error.toString();
                            }

                            if (!vorbisEncoder.Encode(pcmArray)) {
                                error.append("Error encoding audio samples.");
                                return error.toString();
                            }

                            vorbisFrame = vorbisEncoder.ReadCompressedFrame();
                        } else {
                            audioDone = true;
                            break;
                        }
                    }

                    if (encPkt == null) {
                        // Read raw video data.
                        byte[] rawVideoArray = y4mReader.getUncompressedFrame();
                        if (rawVideoArray != null) {
                            long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
                            long nextFrameStart = timeMultiplier.multiply(framesIn++).toLong();

                            encPkt = vpxEncoder.encodeFrame(rawVideoArray,
                                    LibVpxEnc.VPX_IMG_FMT_I420, frameStart,
                                    nextFrameStart - frameStart);

                            // Get the first vpx encoded frame.
                            pktIndex = 0;
                            pkt = encPkt.get(pktIndex++);
                        } else {
                            videoDone = true;
                        }
                    }

                    if (audioDone || videoDone || framesIn >= framesToEncode) break;

                    if (!videoDone && (audioDone || pkt.pts <= vorbisFrame.pts)) {
                        final boolean isKey = (pkt.flags & 0x1) == 1;
                        String stats;
                        stats = "Encoding " + (framesIn-1) + " frame";
                        publishProgress(stats);
                        if (!muxerSegment.addFrame(pkt.buffer, newVideoTrackNumber, pkt.pts,
                                isKey)) {
                            error.append("Could not add video frame.");
                            return error.toString();
                        }

                        // Get the next vpx encoded frame.
                        if (pktIndex < encPkt.size()) {
                            pkt = encPkt.get(pktIndex++);
                        } else {
                            // Read the next raw video frame.
                            encPkt = null;
                        }
                    } else if (!audioDone) {
                        if (!muxerSegment.addFrame(vorbisFrame.buffer, newAudioTrackNumber,
                                vorbisFrame.pts, true)) {
                            error.append("Could not add audio frame.");
                            return error.toString();
                        }
                        vorbisFrame = vorbisEncoder.ReadCompressedFrame();
                    }
                }

                if (!muxerSegment.finalizeSegment()) {
                    error.append("Finalization of segment failed.");
                    return error.toString();
                }

            } catch (Exception e) {
                error.append("Caught error in main encode loop.");
                return error.toString();
            } finally {
                if (mkvWriter != null) {
                    mkvWriter.close();
                }
            }

            return "Encoding Done";
        }

        @Override
        protected void onPreExecute() {
            // Update the status on display.
            mEncodingStatsDispView.setText("Start Encoding Video");
        }

        @Override
        protected void onProgressUpdate(String... values) {
            // Update the encoding status on display.
            mEncodingStatsDispView.setText(values[0]);
        }

        @Override
        protected void onPostExecute(String result) {
            // Update the result on display.
            mEncodingStatsDispView.setText(result);
        }
    }
}