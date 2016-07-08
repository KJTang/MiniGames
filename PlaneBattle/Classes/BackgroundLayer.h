#pragma once

#include "cocos2d.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace cocos2d;

class BackgroundLayer : public Layer
{
private:
	Size visibleSize;
	Sprite *bg1, *bg2;
public:
	BackgroundLayer();
	~BackgroundLayer();

	virtual bool init();
	void update(float dt);
	void onEnter();
	CREATE_FUNC(BackgroundLayer);
};
