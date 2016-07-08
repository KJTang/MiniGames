#pragma once

#include "cocos2d.h"
#include "ArmerSprite.h"

using namespace cocos2d;

class SmartArmer : public ArmerSprite
{
private:
	Size visibleSize;
public:
	SmartArmer();
	~SmartArmer();

	static SmartArmer* create(const std::string& filename);
	bool init();
	void onEnter();
	void update(float dt);

	void setAction();
};
