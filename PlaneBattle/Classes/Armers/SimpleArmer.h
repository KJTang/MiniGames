#pragma once

#include "cocos2d.h"
#include "ArmerSprite.h"

using namespace cocos2d;

class SimpleArmer : public ArmerSprite
{
private:
	Size visibleSize;
public:
	SimpleArmer();
	~SimpleArmer();

	static SimpleArmer* create(const std::string& filename);
	bool init();
	void onEnter();
	void update(float dt);

	void setAction();
};
