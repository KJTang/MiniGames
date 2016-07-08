#pragma once

#include "cocos2d.h"
#include "RectMovingSprite.h"

using namespace cocos2d;

class BonusSprite : public RectMovingSprite
{
private:
	Size visibleSize;
public:
	BonusSprite();
	~BonusSprite();
	static BonusSprite* create(const std::string& filename);

	Rect getRect();
};
