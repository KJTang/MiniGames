#include "SocketTest.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

bool SocketTest::init()
{

	return true;
}
void SocketTest::FirstStart()
{
	
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","get","()I");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        jint x = info.env->CallStaticIntMethod(info.classID,info.methodID);
		
    }
	
	#endif
}

void SocketTest::NextStart()
{
	

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","send","(II)V");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID,0,1);
    }

	#endif
	
}

int SocketTest::FirstAtk(int atk)
{
	int h;
	
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","get","()I");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        jint x = info.env->CallStaticIntMethod(info.classID,info.methodID);
		
        h=x;
    }
	
	#endif
	

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
	ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","send","(II)V");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID,atk,1);
    }
	
	#endif


	return h;
}
int SocketTest::NextAtk(int atk)
{
	int h;
	

	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
    JniMethodInfo info;

    bool ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","send","(II)V");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        info.env->CallStaticVoidMethod(info.classID,info.methodID,atk,2);
    }
	
	#endif
	
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
 
	ret = JniHelper::getStaticMethodInfo(info,"org/cocos2dx/cpp/UdpTest","get","()I");
    if(ret)
    {
        log("call void func1() succeed");
        //传入类ID和方法ID，小心方法名写错，第一个字母是大写
        jint x = info.env->CallStaticIntMethod(info.classID,info.methodID);
		
        h=x;
    }
	
	#endif
	

	return h;
}