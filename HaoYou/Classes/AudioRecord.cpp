#include "AudioRecord.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

AudioRecord* AudioRecord::getInst()
{
	return _audiorecord;
}

bool AudioRecord::init()
{
	_audiorecord = this;

    t = 0;
    vol = 0;
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/RecordThread","go","()V");
    if(ret)
    {
        log("call void func1() succeed");
        //������ID�ͷ���ID��С�ķ�����д����һ����ĸ�Ǵ�д
        info.env->CallStaticVoidMethod(info.classID,info.methodID);

    }
	
	#endif

    this->scheduleUpdate();

	return true;
}

void AudioRecord::update(float dt)
{
    t++;
	
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/RecordThread","getVol","()I");
    if(ret)
    {
        log("call void func1() succeed");
        //������ID�ͷ���ID��С�ķ�����д����һ����ĸ�Ǵ�д
        jint x = info.env->CallStaticIntMethod(info.classID,info.methodID);

        vol=x;
    }
	
	#endif

	all_vol+=vol;

	ave_vol = all_vol/t;

}