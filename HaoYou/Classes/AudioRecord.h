#ifndef __AUDIO_RECORD_H__
#define __AUDIO_RECORD_H__

#include "cocos2d.h"

USING_NS_CC;

class AudioRecord : public Layer
{
public:
    virtual bool init();
    
	CREATE_FUNC(AudioRecord);

	static AudioRecord* getInst();

	void update(float dt);
	
    int t;

    float vol;

	float all_vol;

	float ave_vol;

};
static AudioRecord* _audiorecord;
#endif