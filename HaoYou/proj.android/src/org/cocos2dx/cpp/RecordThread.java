package org.cocos2dx.cpp;

import android.util.Log;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;

public class RecordThread extends Thread {
	private AudioRecord ar;
	private int bs;
	private static int SAMPLE_RATE_IN_HZ = 8000;
	private boolean isRun = false;
	private int vol;
	public static RecordThread _rt;
	static public RecordThread getInstance()
	{
		if(_rt==null)_rt=new RecordThread();
		return _rt;

	}
	public RecordThread() {
		super(); 
		bs = AudioRecord.getMinBufferSize(SAMPLE_RATE_IN_HZ, AudioFormat.CHANNEL_CONFIGURATION_MONO, AudioFormat.ENCODING_PCM_16BIT);
		ar = new AudioRecord(MediaRecorder.AudioSource.MIC, SAMPLE_RATE_IN_HZ, AudioFormat.CHANNEL_CONFIGURATION_MONO, AudioFormat.ENCODING_PCM_16BIT, bs);

	}
	public void run(){
		super.run();
		ar.startRecording();
		byte[] buffer = new byte[bs];
		isRun = true;
		while (isRun) 
		{
			int r = ar.read(buffer, 0, bs);
			int v = 0;
			for (int i = 0; i < buffer.length; i++)
			{
				v += Math.sqrt(buffer[i] * buffer[i]); 
			}
			vol = (int)(v/r);
			try
     		{
				sleep(10);
			}
			catch (InterruptedException localInterruptedException)
			{}
			finally
			{}
		}
		ar.stop();
	}
	public void pause()
	{
		isRun = false;
	}
	public void start()
	{
		if(!isRun)
		{
			super.start();
		}
	}
	public static int getVol()
	{
		return RecordThread.getInstance().vol;
	}
	public static void go()
	{
		RecordThread.getInstance().start();
	}
}